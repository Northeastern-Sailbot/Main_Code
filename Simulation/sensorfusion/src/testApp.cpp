#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	real_angle = Graph(ofVec2f(ofGetWidth()-30.0f, 100.0f), ofVec2f(-HALF_PI	, HALF_PI), 500);
	real_vel = Graph(ofVec2f(ofGetWidth()-30.0f, 100.0f), ofVec2f(-1.5f * PI, 1.5f * PI), 500);
	gyro = Graph(ofVec2f(ofGetWidth()-30.0f, 100.0f), ofVec2f(-HALF_PI	, HALF_PI), 500);
	accel = Graph(ofVec2f(ofGetWidth()-30.0f, 100.0f), ofVec2f(-HALF_PI	, HALF_PI), 500);
	fusion = Graph(ofVec2f(ofGetWidth()-30.0f, 100.0f), ofVec2f(-HALF_PI	, HALF_PI), 500);

	simfeed = InputGenerator(0.5f, 0.3f);
	gi = GyroIntegrator();
	ac = AccelCalculator();
	sf = SensorFusion();

	timestep = 0.05f;
	t = 0.0f;
}

//--------------------------------------------------------------
void testApp::update(){
	//for (int i = 0; i < 5; i++) {
	t += timestep;
	simfeed.update(t);

	ofVec2f a = simfeed.accel();
	float g = simfeed.gyro();
	gi.update(timestep, g);
	ac.update(a);
	sf.update(timestep, g, a, 0.85f);

	real_angle.plot(simfeed.angle());
	real_vel.plot(simfeed.velocity());
	gyro.plot(gi.value());
	accel.plot(ac.value());
	//accel_ax.plot(exp(-0.1f * pow(ac.value()-sf.value(),2.0f)));

	// 0.0 -> 1.0
	// inf -> 0.0

	fusion.plot(sf.value());

	grms += pow(gi.value() - simfeed.angle(), 2.0f);
	arms += pow(ac.value() - simfeed.angle(), 2.0f);
	frms += pow(sf.value() - simfeed.angle(), 2.0f);
	//}
}

//--------------------------------------------------------------
void testApp::draw(){
	// graph 1
	real_vel.draw(ofVec2f(15.0f, 15.0f), ofColor::blue);
	real_angle.draw(ofVec2f(15.0f, 15.0f),ofColor::red);


	// graph 2
	real_angle.draw(ofVec2f(15.0f, 130.0f),ofColor(150));
	gyro.draw(ofVec2f(15.0f, 130.0f),ofColor::green);

	// graph 3
	real_angle.draw(ofVec2f(15.0f, 245.0f),ofColor(150));
	accel.draw(ofVec2f(15.0f, 245.0f),ofColor::purple);
	//accel_ax.draw(ofVec2f(15.0f, 245.0f),ofColor::yellow);
	//accel_ay.draw(ofVec2f(15.0f, 245.0f),ofColor::green);

	// graph 4
	real_angle.draw(ofVec2f(15.0f, 360.0f),ofColor(150));
	fusion.draw(ofVec2f(15.0f, 360.0f),ofColor::orange);

	// captions
	ofSetColor(0);
	ofDrawBitmapString("Real Values", 15.0f, 13.0f);
	ofDrawBitmapString("Gyroscope", 15.0f, 128.0f);
	ofDrawBitmapString("Accelerometer", 15.0f, 243.0f);
	ofDrawBitmapString("Sensor Fusion", 15.0f, 358.0f);
	ofDrawBitmapString(ofToString(sqrt(grms/t)), 215.0f, 128.0f);
	ofDrawBitmapString(ofToString(sqrt(arms/t)), 215.0f, 243.0f);
	ofDrawBitmapString(ofToString(sqrt(frms/t)), 215.0f, 358.0f);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
