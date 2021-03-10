/*
 *
 ***************************************************************************************************
 * Author:             Harshitha Subramani
 * Date:               11/03/2021
 * Filename:           BMS_AttributeCheck.h
 *
 ****************************************************************************************************
*
***************************************************************************************
* Includes
***************************************************************************************
*/

#ifndef BMS_AttributeCheck_h
#define BMS_AttributeCheck_h

#include <stdio.h>

/*
***************************************************************************************
* Definitions
***************************************************************************************
*/
#define ENGLISH 1
#define GERMAN  2
int Sel_Language = ENGLISH;

struct attribute
{
    char attribute_name[20];
    float attribute_maxvalue;
    float attribute_minvalue;
    float attribute_HighWarning;
    float attribute_LowWarning;
   
}s_attribute;

struct attribute s_temperature ={"temperature",45,0,42.75,2.25};
struct attribute s_soc = {"soc",80,20,76,24};
struct attribute s_chargeRate = {"chargeRate",0.8,0,0.76,0.04};

/*
***************************************************************************************
* Declarations
***************************************************************************************
*/



int Check_LowAttributeBreach(float attribute_value,struct attribute s_attribute);
int Check_HighAttributeBreach(float attribute_value,struct attribute s_attribute);
int Check_LowAttributeWarning(float attribute_value,struct attribute s_attribute);
int Check_HighAttributeWarning(float attribute_value,struct attribute s_attribute);
int batteryIsOk(float temperature, float soc, float chargeRate);
#endif /* BMS_AttributeCheck_h */
