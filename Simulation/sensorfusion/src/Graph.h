//
//  Graph.h
//  sensorfusion
//
//  Created by Corey Hoard on 1/22/14.
//
//

#ifndef __sensorfusion__Graph__
#define __sensorfusion__Graph__

#include <iostream>
#include "ofMain.h"

class Graph {
private:
	int buffer_size;
	std::deque<float> buffer;


	ofVec2f map2d(float x, float y);

public:
	ofVec2f bounds;
	ofVec2f range;

	Graph();
	Graph(ofVec2f _b, ofVec2f _r, int _s);

	void plot(float v);

	void draw(ofVec2f origin, ofColor c);
};


#endif /* defined(__sensorfusion__Graph__) */
