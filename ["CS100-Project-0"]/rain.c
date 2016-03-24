//This is Project0 by Miclain Keffeler, 9/11/2015
//This program uses basic functions to determine the weight, height, and total
//gallons of rain that fell on a county.
#include <stdio.h>
#include <math.h> 
#include <string.h>

//This Function determines # of gallons of rain
double gallonsrain(double a, double b, double c){
    double rain =  (a/12) * (c * 43560) * (b* .01);
    return rain* 7.480526;  //conversion factor for gallons
}

//This function weighs rain
double weight(double d){
    double rweight = d * 8.3430;
    return rweight/2000; //lbs per ton
}

//This function uses gallons of rain and calculates its area 
double height(double e){
    double rheight =  ((e/7.48052)/57600);
    return rheight/ 5280; //feet to miles conversion factor
}

int main(void){

    int countysize;

    printf("How big is the county in acres :"); //County size
    scanf("%d",&countysize);

    double rainfall;

    printf("How much rainfall was received in inches? :");
    //total rainfall
    scanf("%lf", &rainfall);
 
    int percent;

    printf("What percent of this county received this rainfall? :");
    //% of county that received this rain
    scanf("%d", &percent);

    double heightorain = height(gallonsrain(rainfall,percent,countysize));
    //Calling Height function

    double weightorain = weight(gallonsrain(rainfall,percent,countysize));
    //Calling Weight function

    double fallengallons = gallonsrain(rainfall, percent, countysize);
    //Calling GallonsRain function

    printf("The #  of gallons that fell is %f\n", fallengallons);
    printf("The weight of this rain in tons is %f\n", weightorain);
    printf("The ht. over a college football field = %f miles\n", heightorain);

    return 0;
}
