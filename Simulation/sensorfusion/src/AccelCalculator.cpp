//
//  AccelCalculator.cpp
//  sensorfusion
//
//  Created by Corey Hoard on 1/22/14.
//
//

#include "AccelCalculator.h"

AccelCalculator::AccelCalculator(void) {
	angle = 0.0f;
}

void AccelCalculator::update(ofVec2f acc) {
	angle = atan2(acc.y, acc.x);
}

float AccelCalculator::value(void) {
	return angle;
}