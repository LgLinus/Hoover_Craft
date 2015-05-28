/*
 * values.c
 *
 *	File used to store variables used by mutliple files
 *
 * Created: 2015-05-07 13:52:03
 *  Author: Linus Granath
 */ 
#include "values.h"
#include <asf.h>
#include <inttypes.h>

int adc_value_back_left = 0;
int adc_value_front_right = 0;
int adc_value_front_left = 0;
int adc_value_back_right = 0;

/* Arrays used to convert voltage to distance for each inductor, the row indicates which table to use
 * The column indicates which inductor to use [0:3] and the page indicates which position*/
int voltage_to_distance_table[VOLTAGE_TO_DISTANCE_AMMOUNT][4][25] =		
												// 75 mA Plattan, negativ körriktning
											{{{2217,1624,1405,1344,1063,944,824,771,717,660,603,567,530,509,487,466,445,434,423,406,389,375,361,336,311},			// Front Left
											{2203,1777,1351,1144,936,794,652,561,469,423,337,315,252,220,187,162,137,123,109,98,86,77,68,64,59},					// Front Right
											{2258,2166,2075,1562,1048,945,841,797,753,681,609,590,570,514,458,444,429,417,405,400,394,378,361,359,356},				// Back Left
											{2256,1899,1542,1295,1048,931,815,748,681,634,587,553,519,492,466,444,423,408,393,380,367,353,339,319,299}},			// Back Right
											    // 75mA IIR
											{{2506,2255,1724,1370,1163,1006,918,836,768,700,666,623,597,571,553,532,517,500,479,469,457,443,432,426,391},			// Front Left
											{2446,1910,1453,1112,906,717,584,480,391,327,270,224,189,160,130,108,93,78,68,61,55,50,47,45,44},						// Front Right
											{2610,2204,1831,1617,1321,1227,1006,887,794,730,681,632,618,586,585,565,549,538,507,506,469,458,448,432,409},			// Back Left
											{1763,1423,1167,1021,912,809,710,654,597,548,524,500,470,439,421,404,373,363,344,324,310,287,254,233,229}},				// Back Right
												// 75mA FIR
											{{2027,1903,1600,1308,1106,965,863,799,746,711,661,621,590,557,544,511,486,479,457,441,433,419,400,369,360},			// Front Left
											{2082,2058,1604,1226,974,805,653,535,451,367,306,257,204,160,129,104,90,76,65,58,53,49,46,44,43},						// Front Right
											{2284,2212,1754,1465,1248,1083,949,848,772,708,649,604,571,535,509,487,467,445,430,415,405,387,364,347,316},			// Back Left
											{2035,1851,1301,1128,944,852,773,699,622,589,547,500,435,411,386,369,348,330,309,284,267,253,232,208,196}}};			// Back Right

// Arrays used to filter sensor
int filter_table[4][buffert_size];
// Back Filter Left
int filter_value;
int table = 0;
int current_buffert_back_left[buffert_size] = {0};
float temp = 0;


/* Converts the voltage to distance from the wire to the sensor	*/
int voltage_to_distance(int current_voltage, int inductor)
{	
	int value = 0;
	for(int i = 0; i < 25;i++){
		if(i==24){
			value = i*5;
			break;
		}
		/* Check if current voltage is closer to the current value in the table or the next one,		 *
		 * if it is closer to the current element [i] that one will be selected, otherwise keep on going *
		 * through the table																			 */
		else if(abs(current_voltage-voltage_to_distance_table[table][inductor][i])<abs(current_voltage-voltage_to_distance_table[table][inductor][i+1]))
		{
			value = i*5; // Transform voltage to distance
			break;
		}
	}
	return value;
}

/* Moving average filter, inductor decides which row in the table to modify */
int filter(int invalue, int inductor)
{
	/* Moving average filter */
	for(int i = buffert_size-1; i > 0;i--)
	{
		filter_table[inductor][i] = filter_table[inductor][i-1];
	}
	
	filter_table[inductor][0] = invalue;
	
	int sum_current_median_front_left = 0;
	
	/* Calculate median value */
	for(int i = 0; i < buffert_size;i++)
	{
		sum_current_median_front_left +=filter_table[inductor][i];
	}
	
	filter_value = sum_current_median_front_left/buffert_size;
	
	return filter_value;
}

/* IIR - filter, inductor decides which row in the table to modify*/
int iir_filter(int invalue, int inductor)
{	
	temp = 0;
	static float xbuff[4][buffert_size_iir-1] = {0};
	static float b[buffert_size_iir-1] = {0.1};
	static float ybuff[4][buffert_size_iir] = {0};
	static float a[buffert_size_iir] = {0,0.9};
	/* Make room for new value */
	for(int i = buffert_size_iir-1; i > 0;i--)
	{
		xbuff[inductor][i] = xbuff[inductor][i-1];
	}
	
	xbuff[inductor][0] =(float)invalue;
	
	/* Calculate median value */
	for(int i = 0; i < buffert_size_iir-1;i++)
	{
		temp +=b[i]*xbuff[inductor][i];
	}
	for(int i = 0; i < buffert_size_iir;i++)
	{
		temp +=a[i]*ybuff[inductor][i];
	}
	for(int i = buffert_size_iir-1; i > 0;i--)
	{
		ybuff[inductor][i] = ybuff[inductor][i-1];
	}
	
	
	ybuff[inductor][1] = temp;
	return (int)temp;
}

/* Select which voltage to distance table to used, used for calibration */
//int get_table(int val){
//for(int i = 0;i<VOLTAGE_TO_DISTANCE_AMMOUNT;i++){
//if (i==VOLTAGE_TO_DISTANCE_AMMOUNT-1)
//{
//table = i;
//break;
//}
///* Check which value the average sampled value is closest to in the tables */
//else if((abs(val-voltage_to_distance_table[i][0][12]))<(abs(val-voltage_to_distance_table[i+1][0][12]))){
//table = i;
//break;
//}
//}
//return table;
//}
