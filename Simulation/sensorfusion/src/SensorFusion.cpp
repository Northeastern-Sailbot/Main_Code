//
//  SensorFusion.cpp
//  sensorfusion
//
//  Created by Corey Hoard on 1/22/14.
//
//

#include "SensorFusion.h"

SensorFusion::SensorFusion(void) {
	angle = 0.0f;
}

void SensorFusion::update(float dt, float gyro, ofVec2f acc, float alpha) {
	angle = alpha * (gyro * dt + angle) + (1.0f - alpha) * (atan2(acc.y, acc.x));
}


float SensorFusion::value(void) {
	return angle;
}