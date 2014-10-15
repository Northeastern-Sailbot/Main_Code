/*****************************************************************************************
*    Author:                      Justin Hynes-Bruell
*    Filename:                    Sail_Bot_Outline.cpp
*    Assignment:                  Free Lance
*    Date Last Edited:            9/19/2014     
*                  1. Specifications:  Does the overall Function of Sail Bot
*                  2. Input:    Current GPS Coords, Desiered GPS Coords, Wind Direction, Compass Heading
*                  3. Output    Turn Boat Clockwise/CounterClockwise, Trim Sails, Tack Sails
*
******************************************************************************************/
/*
Description and Flow of Program
Takes current XY (Longitiude/Latitude) coordinates and first converst them to Polar coordinates,
As of right now it gives the degrees clockwise from North the desired location is. It then compares
these degrees to the direction the current wind is appoaching from (In degrees Clockwise from North).
With this Comparison it decides wheather to Run the "Trim" or "Tack Program" based on weather the 
desired heading is into the wind or not. For now, "Into the wind" is wheather it is +-45 degrees of 
the current wind direction

Goals:
      * Modular Function Design
      * Simulation Abilties
      * Finishing Tacking Function

*/



#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib> //For Random Numbers
#include <cstdio>
#include <ctime>
#include <cmath>
#define pi 3.1415926
using namespace std;

void To_Polar_Clock(double &X, double &Y);

void TackingFunction();

void TrimmingFunction();

int TackOrTrim(double Boat_GPS_X, double Boat_GPS_Y,double Des_GPS_X,double Des_GPS_Y, int Wind_Dir);

int main(void)
{
     double Boat_GPS_X, Boat_GPS_Y, Des_GPS_X, Des_GPS_Y;
     int Wind_Dir;
     
     cout << "The following program emulates the functions used for the Sail Bot V1\n\n";
              //Get Values
     cout << "Current Coordinates:\n";
     cout << "\nPlease Enter an X value:\n";
     cin >> Boat_GPS_X;   //Replace this with current GPS "X" Pull
     cout << "\nPleaser Enter a Y value:\n";
     cin >>  Boat_GPS_Y;  //Replace this with current GPS "Y" Pull
             
     cout << "\n\nDesired Coordinates:\n";
     cout << "\nPlease Enter an X value:\n";
     cin >> Des_GPS_X;
     cout << "\nPlease Enter a Y value:\n";
     cin >> Des_GPS_Y;
         
         //This is the direction wind is hitting the boat
     cout << "\nPlease enter Current Wind Direction (Degrees Clockwise from North):\n" << endl;
     cin >> Wind_Dir;
    
     if (TackOrTrim(Boat_GPS_X, Boat_GPS_Y, Des_GPS_X, Des_GPS_Y, Wind_Dir) == 0)
       TackingFunction();
     else
       TrimmingFunction();      
         
    system("pause");
    return(0);
}




void TackingFunction(){
     
     /*
     To do this use the code of the trimming function to turn the servo to the desired heading
     whitch is 45 degrees clock or counterclockwise of the direction so that the boat is following
     a good angle aginst the wind. 
     */
     cout << "Tack\n";

}

void TrimmingFunction(){
     //Turn Boat to correct heading
     double Compass_Heading; //Current heading of boat in DEGREES CLOCKWISE FROM NORTH!!!
     double X, Y;
     To_Polar_Clock(X, Y);   //Y is the Desired heading of the Boat
     
     cout << "Please Enter Current heading in degrees clockwise from North\n";
     cin >> Compass_Heading;
     
     //--------------Run Trim Sails Function Here---------------
     
     if ((Y - Compass_Heading < -180) || (Y - Compass_Heading > 0)){
            cout << "\nBoat is Turning Clockwise\n";
            //Turn Clockwise
            }
     if ((Y - Compass_Heading > -180) && (Y - Compass_Heading < 0)){
            cout << "\nBoat is Turning Counter Clockwise\n";
            //Turn Counter Clockwise
            }
}

void To_Polar_Clock(double &X, double &Y)
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
     Y = 360 - Y; //Makes degrees Clockwise 
}

int TackOrTrim(double Boat_GPS_X, double Boat_GPS_Y,double Des_GPS_X,double Des_GPS_Y, int Wind_Dir){
         
         int Ubound, Lbound;
         double X, Y;
         
         Des_GPS_Y = Des_GPS_Y + .000000001;  //To Correct for Zero Error y
         Des_GPS_X = Des_GPS_X + .000000001;  //To Correct for Zero Error x
         
         
         /*
         //get the following from sensors, this is not going to use "cin"
         cin >> Compass_Heading; */
         
         Y = Des_GPS_Y - Boat_GPS_Y;
         X = Des_GPS_X - Boat_GPS_X;
         
         To_Polar_Clock(X, Y); //Y = degrees heading (in 360)  Clockwise
         

         Ubound = (Wind_Dir + 45) % 360; //Sets upper bound

         Lbound = (Wind_Dir - 45) % 360; //Sets Lower Bound


         cout << "\nHeading in Degress: " << Y << endl;
         
         //         cout << "\nTurn the Boat " << Y << " Degrees from North\n\n";
         cout << "\nThe Upper bound is: " << Ubound << endl;
         cout << "\nThe Lower bound is: " << Lbound << endl;

         //Determine wheather or not to tack or trim
         if (Y <= Ubound && Y >= Lbound){
            cout << "\nTacking Function:\n--------------------------------\n";
            return 0;
            }
         else
            cout << "\nTrimming Function:\n--------------------------------\n";
            return 1;
}
