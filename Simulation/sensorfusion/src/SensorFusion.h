//
//  SensorFusion.h
//  sensorfusion
//
//  Created by Corey Hoard on 1/22/14.
//
//

#ifndef __sensorfusion__SensorFusion__
#define __sensorfusion__SensorFusion__

#include <iostream>
#include "ofMain.h"

class SensorFusion {
public:
	SensorFusion(void);

	void update(float dt, float gyro, ofVec2f acc, float alpha);

	float value(void);

private:
	float angle;

};

#endif /* defined(__sensorfusion__SensorFusion__) */
