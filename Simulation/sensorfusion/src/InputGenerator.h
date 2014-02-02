//
//  InputGenerator.h
//  sensorfusion
//
//  Created by Corey Hoard on 1/22/14.
//
//

#ifndef __sensorfusion__InputGenerator__
#define __sensorfusion__InputGenerator__

#include <iostream>
#include "ofMain.h"
class InputGenerator {
public:
	InputGenerator(float _gn, float _an);
	InputGenerator(void);

	void update(float _t);

	void setNoise(float _gn, float _an);

	float angle(void);
	float velocity(void);

	float gyro(void);
	ofVec2f accel(void);

private:
	float t;
	float gyro_noise;
	float accel_noise;
};

#endif /* defined(__sensorfusion__InputGenerator__) */
