#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"functions.h"
#include"cJSON.h"

int main(){
  char *usr_zipcode = malloc(5 * sizeof(*usr_zipcode));
  printf("Welcome to Weather Tracker\nPlease Enter Your Area Zipcode:");
   scanf("%s",usr_zipcode);//Store user entered zipcode
   APIcall(usr_zipcode);//Make API call and generate a xml file with the location information
   readJson();

   DisplayData();
  int cases, next,initial;
   initial = 5;
   next = 10;
   
   do {
   	 
   	 printf("\nPlease choose from the following options");
   	 printf("\n1. Display the average temperature for next 24 hours:");
   	 printf("\n2. Display the informaion for next 5 times");
   	 
   	 printf("\n7. Exit the program\n");
   	 
  	 printf("\nYour choice: ");
  	 scanf("%d", &cases);
  	 
  	 if(cases >=1&& cases <=7)
  	 {
  	 
   	 switch (cases)
  	 {
   		case 1:
   		CalculateAverageTemp();
   		break;
   		
   		case 2:
   	 	if(next<= 40)
   	 	{
   		DisplayNext(initial, next);
   		initial +=5;
   		next+=5;
   		}
   		else
   		{
   			printf("There are no more data to be displayed\n");
   		}
   		break;
   		
   		case 3:
   		break;
   		
   		case 4:
   		break;
   		
   		case 5:
   		break;
   		
   		case 6:
   		break;
   		
   		
   		case 7:
   		printf("Bye!!!\n");
   		exit(0);
   		break;
   	}
   	
   	}
   	else
   	{
   		printf("Please enter a valid option(1-7)!!!!!!!!\n");
   	}
   		
  	 
 	}while(cases != 7);
   
   
    return 0;
    
   
  
}
