//
//  AccelCalculator.h
//  sensorfusion
//
//  Created by Corey Hoard on 1/22/14.
//
//

#ifndef __sensorfusion__AccelCalculator__
#define __sensorfusion__AccelCalculator__

#include <iostream>
#include "ofMain.h"

class AccelCalculator {
public:
	AccelCalculator(void);

	void update(ofVec2f acc);

	float value(void);

private:
	float angle;
	
};

#endif /* defined(__sensorfusion__AccelCalculator__) */
