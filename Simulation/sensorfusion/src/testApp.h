#pragma once

#include "ofMain.h"
#include "Graph.h"
#include "GyroIntegrator.h"
#include "AccelCalculator.h"
#include "SensorFusion.h"
#include "InputGenerator.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	Graph real_angle, real_vel;
	Graph gyro, accel, fusion;
	
	InputGenerator simfeed;
	GyroIntegrator gi;
	AccelCalculator ac;
	SensorFusion sf;

	float timestep;
	float t;

	float grms, arms, frms;
};
