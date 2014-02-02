//
//  GyroIntegrator.cpp
//  sensorfusion
//
//  Created by Corey Hoard on 1/22/14.
//
//

#include "GyroIntegrator.h"

GyroIntegrator::GyroIntegrator(void) {
	accum = 0.0f;
}

void GyroIntegrator::update(float dt, float vel) {
	accum += dt * vel;
}

float GyroIntegrator::value(void) {
	return accum;
}