//
//  InputGenerator.cpp
//  sensorfusion
//
//  Created by Corey Hoard on 1/22/14.
//
//

#include "InputGenerator.h"

// Contrust a new InputGenerator
InputGenerator::InputGenerator(void) {
	t = 0.0f;
	setNoise(0.0f, 0.0f);
}
InputGenerator::InputGenerator(float _gn, float _an) {
	t = 0.0f;
	setNoise(_gn, _an);
}

// Update simulation time
void InputGenerator::update(float _t) {
	t = _t;
}


// Set sensor noise levels
void InputGenerator::setNoise(float _gn, float _an) {
	gyro_noise = _gn;
	accel_noise = _an;
}

// Read actual angle in radians
float InputGenerator::angle(void) {
	float res = 3.0f * cos(t);

	for (int i = 0; i < 20; i++) {
		res += ofNoise((float)i * 2.0f) * sin((float)i * t * 0.3f + (float)i * 0.8f);
	}

	return ofMap(res, -10.0f, 10.0f, -HALF_PI, HALF_PI);
}

// Read actual rotational velocity in radians/second
float InputGenerator::velocity(void) {
	float res = -3.0f * sin(t);

	for (int i = 0; i < 20; i++) {
		// partial derivative wrt time of angle function
		res += (float)i * 0.3f * ofNoise((float)i * 2.0f) * cos((float)i * t * 0.3f + (float)i * 0.8f);
	}

	return ofMap(res, -10.0f, 10.0f, -HALF_PI, HALF_PI);
}

// Simulate a reading from a gyroscope. Adds noise, deadband, and clamping
float InputGenerator::gyro(void) {
	float real = velocity();
	float deadband = 0.2f;
	float clamp = 3.0f;
	float res = real;
	res *= ((abs(real) < deadband) ? 0.0 : 1.0);
	res = ofClamp(res, -clamp, clamp);
	res += 2.0f * ofRandomf();
	return res;
}

// Similate a reading from an accelerometer. Adds noise.
ofVec2f InputGenerator::accel(void) {
	ofVec2f real = ofVec2f(cos(angle()), sin(angle()));
	ofVec2f rough = ofVec2f(ofRandomf(),ofRandomf());
	ofVec2f smooth = ofVec2f(ofSignedNoise(t, 21.0f), ofSignedNoise(t, 17.0f)) +
	ofVec2f(ofSignedNoise(0.5f * t, 13.0f), ofSignedNoise(0.5f * t, 43.0f));
	return real + 0.2f * rough + 0.5f * smooth;
}