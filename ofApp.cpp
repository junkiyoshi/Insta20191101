#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	auto span = 1;
	auto len = 16;
	for (auto x = -100; x < 100; x += span) {

		auto angle_1 = ofMap(ofNoise(abs(x) * 0.02 + ofGetFrameNum() * 0.03), 0, 1, -PI, PI);
		auto rotation_1 = glm::rotate(glm::mat4(), angle_1, glm::vec3(1, 0, 0));

		auto angle_2 = ofMap(ofNoise(abs(x + span) * 0.02 + ofGetFrameNum() * 0.03), 0, 1, -PI, PI);
		auto rotation_2 = glm::rotate(glm::mat4(), angle_2, glm::vec3(1, 0, 0));


		this->mesh.addVertex(glm::vec4(len * 0.5, x, 0, 0) * rotation_1);
		this->mesh.addVertex(glm::vec4(len * -0.5, x, 0, 0) * rotation_1);
		this->mesh.addVertex(glm::vec4(len * -0.5, x + span, 0, 0) * rotation_2);
		this->mesh.addVertex(glm::vec4(len * 0.5, x + span, 0, 0) * rotation_2);

		auto index = this->mesh.getVertices().size() - 1;

		this->mesh.addIndex(index - 3);
		this->mesh.addIndex(index - 2);
		this->mesh.addIndex(index);

		this->mesh.addIndex(index - 2);
		this->mesh.addIndex(index - 1);
		this->mesh.addIndex(index);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->mesh.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}