//
//  readXML.c
//  315
//
//  Created by Kevin Zhang on 4/23/20.
//  Copyright © 2020 CNIT255. All rights reserved.
//

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include"cJSON.h"




struct forecast{//different times of a location
    char* time;
    double windDirection;
    double windSpeed;
    double temperature;
    double feelsLike;
    double pressure;
    int humidity;
    char * weatherDes;
    
};



struct cityInformation{//the information about a location
    char* cityName;
    char* Country;
    int timeZone;
    struct forecast forecastInformation[40];//contain 40 different times
};

struct cityInformation cI;//createing a city structure

 char c[10] = "GMT";
 

int getTimezone(int a){//convert the time zone from seconds to hour
    a= a/3600;
    
    return a;

}
void readJson(){
    
    
    char jsonString[100000]="";//set string for the json
    FILE *jsonFile;//create a json file
    char ch;
    //2
    jsonFile = fopen("weather.Json", "r");//read the json file
    //3
    if (jsonFile == NULL)
    {
        printf("File is not found \n");
    }
    else
    {
        //4
        while ((ch = fgetc(jsonFile)) != EOF)//put the json file in to string
        {
            strncat(jsonString, &ch, 1);
        }
    }
    cJSON * json= cJSON_Parse(jsonString);//parse the file to a Json struct
    
    cJSON *NodeCity = NULL;
    
    NodeCity = cJSON_GetObjectItem(json,"city");//get the item named city.
    cJSON *temp;
    temp = cJSON_GetArrayItem(NodeCity, 0);//get the arrayed json item
    cI.cityName  =  temp->valuestring;//put the string in item in to the struct
    temp = cJSON_GetArrayItem(NodeCity, 2);//get the arrayed json item
    cI.Country  =  temp->valuestring;//put the string in item in to the struct
    temp = cJSON_GetArrayItem(NodeCity, 3);//get the arrayed json item
    cI.timeZone = temp->valueint;
    
    cJSON *Time = NULL;
    Time = cJSON_GetObjectItem(json,"list");
    
    
    for(int i=0;i<40;i++){//get the weather information from json to struct
        struct forecast Forecast;
        temp = cJSON_GetArrayItem(Time, i);
        cJSON *temp2;
        temp2 = temp->child;
        cJSON *a;
        a = cJSON_GetObjectItem(temp,"dt_txt");
        Forecast.time = a->valuestring;
        
        a = cJSON_GetObjectItem(temp,"weather");
        cJSON *b;
        b=cJSON_GetObjectItem(a->child,"description");
        Forecast.weatherDes = (b->valuestring);
        
        a = cJSON_GetObjectItem(temp,"main");
        b = cJSON_GetObjectItem(a,"temp");
        Forecast.temperature = b->valuedouble;
        b = cJSON_GetObjectItem(a,"humidity");
        Forecast.humidity = b->valueint;
        b = cJSON_GetObjectItem(a,"feels_like");
        Forecast.feelsLike = b->valuedouble;
        b = cJSON_GetObjectItem(a,"pressure");
        Forecast.pressure = b->valuedouble;

        
        
        a = cJSON_GetObjectItem(temp,"wind");
        b = cJSON_GetObjectItem(a,"speed");
        Forecast.windSpeed = b->valuedouble;
        b = cJSON_GetObjectItem(a,"deg");
        Forecast.windDirection = b->valuedouble;
        cI.forecastInformation[i] = Forecast;
        
        
    }

}


void DisplayData()
{
	 int i, tzone = 0;
	 double temp;

	 printf("Location Information\t  City name: %-20s", cI.cityName); //printf statements to display location information
	 printf("Country: %-10s", cI.Country);
	 tzone = getTimezone(cI.timeZone);
	 printf("TimeZone: GMT%d:00\n\n", tzone);
	 
	 printf("Date/Time:      ");
	 
	 for(int i=0;i<5;i++) //for loop to display contents of array
	 {
	 	printf("%-25s", cI.forecastInformation[i].time);
	 }
	 
	 printf("\nWeather:        ");
	 
	 for(int i=0;i<5;i++) //for loop to display contents of array
	 {
	 	printf("%-25s", cI.forecastInformation[i].weatherDes);
	 }
	 
	 printf("\nTemperature:    ");
	   
	  for(int i=0;i<5;i++) //for loop to display contents of array
	 {
	 	temp = cI.forecastInformation[i].temperature;
	 	temp = temp - 273.15; //convert kelvin to celsius
	 	printf("%-3.0f°C                    ", temp);
	 }
	 
	 printf("\nFeels Like:     ");
	 
	 for(int i=0;i<5;i++) //for loop to display contents of array
	 {
	 	temp = cI.forecastInformation[i].feelsLike;
	 	temp = temp - 273.15;
	 	printf("%-3.0f°C                    ", temp);
	 }
	 

	 printf("\nHumidity:       ");

	  for(int i=0;i<5;i++) //for loop to display contents of array
	 {
	 	printf("%-3i%%                     ", cI.forecastInformation[i].humidity);
	 	
	 }
	 
	 printf("\nPressure:       ");
	 
	 for(int i=0;i<5;i++) //for loop to display contents of array
	 {
	 	printf("%-5.0fhPa                 ", cI.forecastInformation[i].pressure);
	 }
	 
	 
	 printf("\nWindSpeed:      ");
	 
	  for(int i=0;i<5;i++) //for loop to display contents of array
	 {
	 	printf("%-5.2fm/h                 ", cI.forecastInformation[i].windSpeed);
	 }
	 
	 printf("\nWindDirection:  ");
	 
	 for(int i=0;i<5;i++) //for loop to display contents of array
	 {
	 	printf("%-3.0f°                     ", cI.forecastInformation[i].windDirection);
	 }

	printf("\n");
	
}

void CheckWeather() 
{
char weatherInput[10];
char weatherArray[6][30] = {"clear sky","scattered clouds","broken clouds","overcast clouds",
			"few clouds","light rain"};
int x = 0;
double temp;
char tem;
do{
printf("\nHere are the six different weather: clear sky; scattered clouds; broken clouds;");
printf("\novercast clouds; few clouds; light rain. Please select one for check: \n");
scanf("%c",&tem);
scanf("%[^\n]",weatherInput);
for(int j = 0; j<6;j++) {
	if(weatherInput[0]==weatherArray[j][0]) {
		x = 1;	
	for(int i=0;i<40;i++)
	{
	if(strcmp(cI.forecastInformation[i].weatherDes,weatherInput)==0){
		printf("Date/Time:      ");
		printf("%-25s", cI.forecastInformation[i].time);
		printf("Weather:        ");
		printf("%-25s", cI.forecastInformation[i].weatherDes);
		printf("Temperature:    ");
		temp = cI.forecastInformation[i].temperature;
	 	temp = temp - 273.15; //convert kelvin to celsius
	 	printf("%-3.0f°C                    \n", temp);
	}
}
		}
	}	
if(x == 0) {
printf("Sorry, can't figure out the input, please input again.");
}
}while(x==0);

}

void modeTemperature() {
double temp;
double modeTem;
double tem[40];
for(int i=0;i<40;i++){
temp = cI.forecastInformation[i].temperature;
temp = temp - 273.15;
tem[i] = temp;
}
int maxValue = 0, maxCount = 0, i, j;

   for (i = 0; i < 40; ++i) {
      int count = 0;
      
      for (j = 0; j < 40; ++j) {
         if (tem[j] == tem[i])
         ++count;
      }
      
      if (count > maxCount) {
         maxCount = count;
         maxValue = tem[i];
      }
   }

   modeTem = maxValue;
printf("The mode temperature is %-3.0f°C                    \n", modeTem);
}
	 printf("\n");

}




void CalculateAverageTemp()
{
	 //calculate the average temperature for the next 24 hours
	 
	 double temp,average = 0;
	 
	 for(int i=0;i<8;i++)
	 {
	 	temp = cI.forecastInformation[i].temperature;
	 	average = average + temp;
	 }
	 average = average/8 - 273.15;
	
	  printf("The average temperature for the next 24 hours is: %.1f°C\n", average);
	 
	
}


void DisplayNext(int b, int a)
{
	 int i, tzone;
	 double temp;


	 printf("Location Information\t  City name: %-20s", cI.cityName); //printf statements to display location information
	 printf("Country: %-10s", cI.Country);
	 tzone = getTimezone(cI.timeZone);
	 printf("TimeZone: GMT%d:00\n\n", tzone);
	 
	 printf("Date/Time:      ");
	 
	 for(i=b;i<a;i++) //for loop to display contents of array
	 {
	 	printf("%-25s", cI.forecastInformation[i].time);
	 }
	 
	 
	 printf("\nWeather:        ");
	 
	 for(i=b;i<a;i++) //for loop to display contents of array
	 {
	 	printf("%-25s", cI.forecastInformation[i].weatherDes);
	 }

	 
	 printf("\nTemperature:    ");
	   
	  for(i=b;i<a;i++) //for loop to display contents of array
	 {
	 	temp = cI.forecastInformation[i].temperature;
	 	temp = temp - 273.15; //convert kelvin to celsius
	 	printf("%-3.0f°C                    ", temp);
	 }
	 
	 printf("\nFeels Like:     ");
	 
	 for(i=b;i<a;i++) //for loop to display contents of array
	 {
	 	temp = cI.forecastInformation[i].feelsLike;
	 	temp = temp - 273.15;
	 	printf("%-3.0f°C                    ", temp);
	 }
	 
	 printf("\nHumidity:       ");
	 
	  for(i=b;i<a;i++) //for loop to display contents of array
	 {
	 	printf("%-3i%%                     ", cI.forecastInformation[i].humidity);
	 	
	 }
	 
	 printf("\nPressure:       ");
	 
	 for(i=b;i<a;i++) //for loop to display contents of array
	 {
	 	printf("%-5.0fhPa                 ", cI.forecastInformation[i].pressure);
	 }
	 
	 
	 printf("\nWindSpeed:      ");
	 
	  for(i=b;i<a;i++) //for loop to display contents of array
	 {
	 	printf("%-5.2fm/h                 ", cI.forecastInformation[i].windSpeed);
	 }
	 
	 printf("\nWindDirection:  ");
	 
	 for(i=b;i<a;i++) //for loop to display contents of array
	 {
	 	printf("%-3.0f°                     ", cI.forecastInformation[i].windDirection);
	 }
	 printf("\n");
	
	
}



