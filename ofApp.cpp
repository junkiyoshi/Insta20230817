#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->mesh.clear();

	ofColor color;
	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
	for (int i = 0; i < 12; i++) {

		for (int x = -300; x <= 300; x += 5) {

			auto base_y = ofMap(ofNoise(noise_seed.x, x * 0.001 + (ofGetFrameNum() + i * 10000) * 0.002), 0, 1, -300, 300);
			auto base_z = ofMap(ofNoise(noise_seed.y, x * 0.001 + (ofGetFrameNum() + i * 10000) * 0.002), 0, 1, -300, 300);

			auto y = base_y + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -30, 30);
			auto z = base_z + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -30, 30);
			this->mesh.addVertex(glm::vec3(x, y, z));

			color.setHsb(ofMap(i , 0, 12, 0, 255), 255, 255);
			this->mesh.addColor(color);
		}
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		auto min_distance = 30;
		for (int k = i + 1; k < this->mesh.getNumVertices(); k++) {

			float distance = glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k));
			if (distance < 30) {

				this->mesh.addIndex(i);
				this->mesh.addIndex(k);

				if (distance < min_distance) {

					min_distance = distance;
				}
			}
		}

		this->mesh.setColor(i, ofColor(this->mesh.getColor(i), ofMap(min_distance, 0, 30, 255, 64)));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	this->mesh.drawWireframe();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		ofSetColor(this->mesh.getColor(i));
		ofDrawSphere(this->mesh.getVertex(i), 4);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}