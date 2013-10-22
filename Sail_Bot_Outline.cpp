/***************************************************************************************** 
*    Author:                      Justin Hynes-Bruell 
*    Filename:                    Sail_Bot_Outline.cpp 
*    Assignment:                  Free Lance 
*    Description:                  
*                  1. Specifications:  Does the overall Function of Sail Bot 
*                  2. Input:      GPS Coords, Wind Vane, Compass
*                  3. Output      Rudder Servo, Sail Servo
*                  4. Functions:  Taking Function, To_Polar    
* 
******************************************************************************************/
//This program converts x,y coordinates to polar coordinates: degrees,radius 
  
#include <iostream> 
#include <fstream> 
#include <iomanip> 
#include <string> 
#include <cstdlib> //For Random Numbers 
#include <cstdio> 
#include <ctime> 
#include <cmath> 
#define pi 3.14159265359 
using namespace std; 
  
void Cartesian_To_Polar(double &X, double &Y); 
  
int main(void) 
{ 
    double x=0, y=0; 
    double Boat_GPS[2], Des_GPS[2]; 
    double Compass_Heading; 
    double Wind_Dir; 
    double Ubound, Lbound; 
    double X, Y; 
    cout << "The following program emulates the functions used for the Sail Bot\n\n"; 
    while(1==1) 
    { 
           
         //Get Values 
         cout << "Current Coordinates:\n"; 
         cout << "\nPlease Enter an X value:\n"; 
         cin >> Boat_GPS[0]; 
         cout << "\nPleaser Enter a Y value:\n"; 
         cin >>  Boat_GPS[1]; 
               
         cout << "\n\nDesired Coordinates:\n"; 
         cout << "\nPlease Enter an X value:\n"; 
         cin >> Des_GPS[0]; 
         cout << "\nPlease Enter a Y value:\n"; 
         cin >> Des_GPS[1]; 
           
         cout << "Please enter Current Wind Direction:\n" << endl; 
         cin >> Wind_Dir; 
           
           
         /* 
         //get the following from sensors, this is not going to use "cin" 
         cin >> Compass_Heading; */
           
         Y = Des_GPS[1] - Boat_GPS[1]; 
         X = Des_GPS[0] - Boat_GPS[0]; 
           
         Cartesian_To_Polar(X, Y); //Y = degrees heading (in 360) 
           
         Ubound = Y + 45; //Sets upper bound 
         Lbound = Y - 45; //Sets Lower Bound 
  
         if (Ubound > 360) 
         Ubound = Ubound - 360; 
  
         if (Lbound < 0) 
         Lbound = Lbound + 360; 
           
           
           

         cout << "\n\nThe Upper bound is: " << Ubound; 
         cout << "\nThe Lower bound is: " << Lbound;
         cout << "\nDesired Heading: " <<  Y;
         cout << "\nWind Direction: " <<  Wind_Dir;
         
         if (Ubound >= Wind_Dir && Lbound <= Wind_Dir)
         {
              cout << "\n\nTacking Fucntion\n";
         }
         
         if (Ubound < Wind_Dir || Lbound > Wind_Dir)
         {
              cout << "\n\nTrimming Fucntion\n";
         }
           
           
           
    }     
    system("pause"); 
    return(0); 
} 
  
void Cartesian_To_Polar(double &X, double &Y) 
{ 
     double RAD, DEG;  
     RAD = (sqrt(X*X+Y*Y)); 
       
     if(X > 0 && Y > 0) 
     DEG = (atan(Y/X)*(180/pi))+270; //Works 
       
     else if(X < 0 && Y > 0) 
     DEG = (((atan(Y/X))*-1)*(180/pi) - 90)*-1; //Works 
       
     else if(X < 0 && Y < 0) 
     DEG = ((atan(Y/X))*(180/pi)+90); 
       
     else if(X > 0 && Y < 0) 
     DEG = (((atan(X/Y))*(180/pi))*-1)+180; 
       
     /* 
     else if(X=0 && Y=0) 
     Y = 0; 
     */
     X = RAD; 
     Y = DEG;  
} 
