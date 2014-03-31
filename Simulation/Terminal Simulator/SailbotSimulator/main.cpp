//
//  main.cpp
//  SailbotSimulator
//
//  Created by Corey Hoard on 3/26/14.
//  Copyright (c) 2014 Michael Janov, Corey Hoard. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <unistd.h>

struct weatherData {
	int speed;
	int direction;
};

weatherData getSimulatedWind(int condition)
{
	weatherData res;
	switch (condition) {
		case 0: // Dead
			res.speed = rand() % 2;
			res.direction = 223 + (rand() % 90);
			break;
		case 1: // Light
			res.speed = 4;
			res.direction = 238 + (rand() % 60);
			break;
		case 2: // Typical
			res.speed = 6 + (rand() % 3);
			res.direction = 258 + (rand() % 20);
			break;
		case 3: // Strong
			res.speed = 11 + (rand() % 2);
			res.direction = 263 + (rand() % 10);
			break;
		case 4: // Heavy
			res.speed = 18;
			res.direction = 263 + (rand() % 10);
			break;
		default:
			res.speed = 0;
			res.direction = 0;
			break;
	}
	return res;
}

int coerceAngle(int angle)  //Coerce an angle into [0, 360)
{
	if ((angle >= 0) && (angle < 360)) {
		return angle;
	} else if (angle < 0) {
		while(angle < 0) {
			angle += 360;
		}
	} else {
		while(angle > 360) {
			angle -= 360;
		}
	}
	return angle;
}

int calculateSensorReading(int boatHeading, int windDir) {
	return coerceAngle(windDir - boatHeading);
}

int doSim(void) {
	int conditionSelect(0);
	int boatHeading(0);

	weatherData windData;
	int sensorReading;

	bool validEntry = false;
	while (!validEntry) {
		std::cout << "Enter a wind condition (0-4): ";
		std::cin >> conditionSelect;
		std::cout << std::endl;
		if ((conditionSelect >= 0) && (conditionSelect < 5)) {
			validEntry = true;
		} else {
			std::cout << "Invalid entry." << std::endl;
		}
	}

	validEntry = false;
	while (!validEntry) {
		std::cout << "Enter a boat heading from N (0-359): ";
		std::cin >> boatHeading;
		std::cout << std::endl;
		if ((boatHeading >= 0) && (boatHeading < 360)) {
			validEntry = true;
		} else {
			std::cout << "Invalid entry." << std::endl;
		}
	}


	/*
	 std::string names[] = {"Dead", "Light", "Typical", "Strong", "Heavy"};
	 std::cout << "Simulating data for a " << names[conditionSelect] << " day" << std::endl;
	 */

	windData = getSimulatedWind(conditionSelect);
	sensorReading = calculateSensorReading(boatHeading, windData.direction);

	std::cout << "Simulation result:" << std::endl;
	std::cout << "\tWind Direction: " << windData.direction << " degrees from N" << std::endl;
	std::cout << "\tWind Speed: " << windData.speed << " mph" << std::endl;
	std::cout << "\tWindvane reading: +" << sensorReading << " degrees from bow" << std::endl;
	std::cout << std::endl;

	return 0;
}

int main(int argc, const char * argv[])
{
	std::cout << "\033[2J\033[1;1H";
	std::cout << std::endl << std::endl;
	std::cout << "Sailbot Simulator 2014 " << std::endl;
	std::cout << "© Michael Janov, Corey Hoard" << std::endl << std::endl;
	std::cout <<
	"\t++-----------------------++" << std::endl <<
	"\t|| Value ---- Conditions ||" << std::endl <<
	"\t++-----------------------++" << std::endl <<
	"\t||   0   ----    Dead    ||" << std::endl <<
	"\t||   1   ----    Light   ||" << std::endl <<
	"\t||   2   ----   Typical  ||" << std::endl <<
	"\t||   3   ----   Strong   ||" << std::endl <<
	"\t||   4   ----    Heavy   ||" << std::endl <<
	"\t++-----------------------++" << std::endl << std::endl;

	doSim();
	//Pass windData.speed and windData.direction to sailboat code
	//Receive response
	//Later down the line, we will
	return 0;
}
