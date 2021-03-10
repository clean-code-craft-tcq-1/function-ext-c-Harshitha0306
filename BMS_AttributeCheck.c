/*
 *
 ***************************************************************************************************
 * Author:             Harshitha Subramani
 * Date:               11/03/2021
 * Filename:           BMS_AttributeCheck.c
 *
 ****************************************************************************************************
*
***************************************************************************************
* Includes
***************************************************************************************
*/

#include <stdio.h>
#include <assert.h>
#include "BMS_AttributeCheck.h"

/*
***************************************************************************************
* Methods
***************************************************************************************
*
 *This Function Checks if the Battery attribute value read is less than the defined Minimum limit
 * \param     attribute_value             Battery reading
 * \param     attribute                   This structure states attribute name , minimum and maximum limit
 * \return                                returns 1 if the Battery reading is less then the defined Minimum limit else returns 0     */

void DisplaybatteryStatus(struct attribute s_attribute,int IdxMessage){
    if (Sel_Language == ENGLISH)
    {
        printf("%s %s\n", s_attribute.attribute_name,BatteryStatus_English[IdxMessage]);
    }
    else{
        printf("%s %s\n", s_attribute.attribute_name,BatteryStatus_German[IdxMessage]);
    }
}

int Check_LowAttributeBreach(float attribute_value,struct attribute s_attribute){
    
    if(attribute_value < s_attribute.attribute_minvalue)
    {
        DisplaybatteryStatus(s_attribute,0);
        return 1;
    }
    else
    {
        return 0;
    }
}

 /*This Function Checks if the Battery attribute value read is greater than the defined Maximum limit
 * \param     attribute_value             Battery reading
 * \param     attribute                   This structure states attribute name , minimum and maximum limit
 * \return                                returns 1 if the Battery reading is greater then the defined Maximum limit else returns 0     */

int Check_HighAttributeBreach(float attribute_value,struct attribute s_attribute){
    if(attribute_value > s_attribute.attribute_maxvalue){
        DisplaybatteryStatus(s_attribute,1);
        return 1;
    }
    else
    {
        return 0;
    }
}

/*This Function Checks if the Battery attribute value read is approaching defined Minimum limit
* \param     attribute_value             Battery reading
* \param     attribute                   This structure states attribute name , minimum and maximum limit
* \return                                returns 1 if the Battery reading is approaching defined Minimum limit else returns 0     */

int Check_LowAttributeWarning(float attribute_value,struct attribute s_attribute){

   if((attribute_value <= s_attribute.attribute_LowWarning) && (attribute_value > s_attribute.attribute_minvalue))
   {
       DisplaybatteryStatus(s_attribute,2);
       return 1;
   }
   else
   {
       return 0;
   }
}

/*This Function Checks if the Battery attribute value read is approaching the defined Maximum limit
* \param     attribute_value             Battery reading
* \param     attribute                   This structure states attribute name , minimum and maximum limit
* \return                                returns 1 if the Battery reading is approaching the defined Maximum limit else returns 0     */

int Check_HighAttributeWarning(float attribute_value,struct attribute s_attribute){
   if((attribute_value >= s_attribute.attribute_HighWarning)&& (attribute_value < s_attribute.attribute_maxvalue)){
       DisplaybatteryStatus(s_attribute,3);
       return 1;
   }
   else
   {
       return 0;
   }
}
 /*This Function Checks if the Battery is normal or abnormal based on defined Maximum and Minimum limts of each attribute
 * \param     temperature, soc,chargeRate   Input Attributes
  * \return                                 returns 1 if the Battery reading is normal else returns 0                           */

int batteryIsOk(float temperature, float soc, float chargeRate)
{
    int temperature_check,soc_check,chargeRate_check =0;
    
    temperature_check =
    Check_LowAttributeBreach(temperature,s_temperature) + Check_HighAttributeBreach(temperature,s_temperature)+ Check_LowAttributeWarning(temperature,s_temperature) + Check_HighAttributeWarning(temperature,s_temperature);
    
    soc_check =
    Check_LowAttributeBreach(soc,s_soc) + Check_HighAttributeBreach(soc,s_soc)+Check_LowAttributeWarning(soc,s_soc) + Check_HighAttributeWarning(soc,s_soc);
    
    chargeRate_check =
    Check_LowAttributeBreach(chargeRate,s_chargeRate)+Check_HighAttributeBreach(chargeRate,s_chargeRate)+ Check_LowAttributeWarning(chargeRate,s_chargeRate)+Check_HighAttributeWarning(chargeRate,s_chargeRate);
    
    if((temperature_check + soc_check + chargeRate_check)==0)
    {
       DisplaybatteryStatus(s_attribute,4);
    }
    
    return!(temperature_check + soc_check + chargeRate_check);
   
}

int main() {
assert(batteryIsOk(40,70,0.7));    /*Battery is ok*/
assert(!batteryIsOk(50, 70, 0.7));  /*Temperature high limit breach*/
assert(!batteryIsOk(40, 85, 0.7));  /*SOC high limit breach*/
assert(!batteryIsOk(30, 30, 1));    /*ChargeRate high limit breach*/
assert(!batteryIsOk(-20, 70, 0.7));   /*Temperature low limit breach*/
assert(!batteryIsOk(40, 10, 0.7));  /*SOC low limit breach*/
assert(!batteryIsOk(30, 30, -1));    /*ChargeRate high limit breach*/
assert(!batteryIsOk(50,-1,-1));    /*All attributes breached*/
assert(!batteryIsOk(42.75, 70, 0.7));  /*Temperature high limit breach*/
assert(!batteryIsOk(40, 77, 0.7));  /*SOC high limit breach*/
assert(!batteryIsOk(30, 30, 0.77));    /*ChargeRate high limit breach*/
assert(!batteryIsOk(2, 70, 0.7));   /*Temperature low limit breach*/
assert(!batteryIsOk(40, 23, 0.7));  /*SOC low limit breach*/
assert(!batteryIsOk(30, 30, 0.02));    /*ChargeRate high limit breach*/
assert(!batteryIsOk(1.75,20,0.04)); /*All attributes on alert*/
}

