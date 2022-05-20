
//  Created by Lochan Basyal on 2/15/22.
//

#include <stdio.h> //header files
#include <math.h>


int main() {  // main function
    
    //Enter coordinates in latitude and longitude
    printf("Enter coordinates in decimal form\n");
    float latitude;
    printf("latitude =");
    scanf("%f",&latitude); //Enter the value of latitude
    if(latitude<-90 || latitude>90) // check the condition for entered latitude
    {
        printf("Please enter the value of latitude between -90 to 90 \n"); //incase the condition will not be satisfied
        printf("latitude ="); //again re-enter the value
        scanf("%f",&latitude);
    }
    float longitude;
    printf("longitude =");
    scanf("%f",&longitude); //Enter the value of longitude
    if(longitude<-180 || longitude>180) //check the condition for entered longitude
    {
        printf("Please enter the value of Longitude between -180 to 180 \n"); // incase the condition will not be satisfied
        printf("longitude ="); //again re-enter the value
        scanf("%f",&longitude);
    }
    
    
    
    // degree, minute and second calculation for latitude
    
     float la_minute= (latitude-floor(latitude))*60;
     float la_second = (la_minute-floor(la_minute))*60;
     int la_degrees = floor(latitude);
     int la_minutes= floor(la_minute);
    
    
    
    // degree, minute and second calculation for longitude
    
    float lo_minute= (longitude-floor(longitude))*60;
    float lo_second = (lo_minute-floor(lo_minute))*60;
    int lo_degrees = floor(longitude);
    int lo_minutes= floor(lo_minute);
    

    
    printf("latitude: %d degrees, %d minutes, %f seconds ",la_degrees,la_minutes, la_second); //print the output
  if(la_degrees>=-90 && la_degrees<=0)  // check the condition for south
    {
        printf("S\n");
    }
    if(la_degrees>=0 && la_degrees<=90)//check the condition for north
    {
        printf("N\n");
    }
    printf("longitude: %d degrees, %d minutes, %f seconds ",lo_degrees,lo_minutes, lo_second); //print the output
    if(lo_degrees>=-180 && lo_degrees<=0)  //check the condition for west
      {
          printf("W\n");
      }
      if(lo_degrees>=0 && lo_degrees<=180)// check the condition for north
      {
          printf("E\n");
      }

    return 0;
   
}

