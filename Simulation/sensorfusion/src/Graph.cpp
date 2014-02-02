//
//  Graph.cpp
//  sensorfusion
//
//  Created by Corey Hoard on 1/22/14.
//
//

#include "Graph.h"

Graph::Graph() {
	bounds = ofVec2f(100.0f, 100.0f);
	range = ofVec2f(-1.0f, 1.0f);
	buffer_size = 10;
}

Graph::Graph(ofVec2f _b, ofVec2f _r, int _s) {
	bounds = _b;
	range = ofVec2f(min(_r.x,_r.y), max(_r.x,_r.y));
	buffer_size = _s;
}

void Graph::plot(float v) {
	buffer.push_back(v);
	if (buffer.size() > buffer_size) {
		buffer.pop_front();
	}
}

void Graph::draw(ofVec2f origin, ofColor c) {
	ofNoFill();
	ofSetColor(84);
	ofSetLineWidth(1);

	ofPushMatrix();
	ofTranslate(origin);
	ofRect(ofVec2f::zero(), bounds.x, bounds.y);

	// zero axis
	ofSetColor(64);
	if ((0.0f > range.x) && (0.0f < range.y)) {
		ofLine(map2d(0.0f, 0.0f),
			   map2d(1.0f, 0.0f));
	}

	// plot line
	ofSetColor(c);
	ofSetLineWidth(5.0f);
	for (int i = 1; i < buffer.size(); i++) {
		ofLine(map2d((float)(i-1)/(buffer_size - 1),buffer[i-1]),
			   map2d((float)i/(buffer_size - 1),buffer[i]));
	}
	ofPopMatrix();
}

ofVec2f Graph::map2d(float x, float y) {
	return ofVec2f(x * bounds.x,
				   ofMap(y, range.x, range.y, bounds.y, 0.0f));
}