//
//  GyroIntegrator.h
//  sensorfusion
//
//  Created by Corey Hoard on 1/22/14.
//
//

#ifndef __sensorfusion__GyroIntegrator__
#define __sensorfusion__GyroIntegrator__

#include <iostream>

class GyroIntegrator {
private:
	float accum;

public:
	GyroIntegrator(void);

	void update(float dt, float vel);
	float value(void);
};

#endif /* defined(__sensorfusion__GyroIntegrator__) */
