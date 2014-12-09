#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::generateCubeIndices(std::vector<unsigned int> &dest,
    unsigned int f_l_b, 
    unsigned int f_r_b, 
    unsigned int f_r_t, 
    unsigned int f_l_t,
    unsigned int b_l_b, 
    unsigned int b_r_b, 
    unsigned int b_r_t, 
    unsigned int b_l_t
) {
    // front face
    dest.push_back(f_l_b);
    dest.push_back(f_r_b);
    dest.push_back(f_r_t);

    dest.push_back(f_l_b);
    dest.push_back(f_r_t);
    dest.push_back(f_l_t);

    // right face
    dest.push_back(f_r_b);
    dest.push_back(b_r_b);
    dest.push_back(b_r_t);

    dest.push_back(f_r_b);
    dest.push_back(b_r_t);
    dest.push_back(f_r_t);

    // back  face
    dest.push_back(b_r_b);
    dest.push_back(b_l_b);
    dest.push_back(b_l_t);

    dest.push_back(b_r_b);
    dest.push_back(b_l_t);
    dest.push_back(b_r_t);

    // left face
    dest.push_back(b_l_b);
    dest.push_back(f_l_b);
    dest.push_back(f_l_t);

    dest.push_back(b_l_b);
    dest.push_back(f_l_t);
    dest.push_back(b_l_t);

    // top face
    dest.push_back(f_l_t);
    dest.push_back(f_r_t);
    dest.push_back(b_r_t);

    dest.push_back(f_l_t);
    dest.push_back(b_r_t);
    dest.push_back(b_l_t);

    // bottom face
    dest.push_back(b_l_b);
    dest.push_back(b_r_b);
    dest.push_back(f_r_b);

    dest.push_back(b_l_b);
    dest.push_back(f_r_b);
    dest.push_back(f_l_b);
}

//--------------------------------------------------------------
void generateHypercube(std::vector<float> &vertices, std::vector<unsigned int> &indices, float size) {
    for (unsigned int idx = 0; idx < 4; ++idx) {
        vertices.push_back(0.0);
        vertices.push_back(0.0);
        vertices.push_back(idx % 2 * size);
        vertices.push_back(((float)(idx > 1)) * size);

        vertices.push_back(size);
        vertices.push_back(0.0);
        vertices.push_back(idx % 2 * size);
        vertices.push_back(((float)(idx > 1)) * size);

        vertices.push_back(size);
        vertices.push_back(size);
        vertices.push_back(idx % 2 * size);
        vertices.push_back(((float)(idx > 1)) * size);

        vertices.push_back(0.0);
        vertices.push_back(size);
        vertices.push_back(idx % 2 * size);
        vertices.push_back(((float)(idx > 1)) * size);
    }

    generateCubeIndices(indices, 0, 1, 2, 3, 5, 4, 7, 6); // main cube
    generateCubeIndices(indices, 8, 9, 10, 11, 13, 12, 15, 14); // super cube
    generateCubeIndices(indices, 8, 9, 10, 11, 1, 0, 3, 2); // front cube
    generateCubeIndices(indices, 4, 5, 6, 7, 13, 12, 15, 14); // back cube
    generateCubeIndices(indices, 1, 9, 10, 2, 13, 5, 6, 14); // right cube
    generateCubeIndices(indices, 8, 0, 3, 11, 4, 12, 15, 7); // left cube
    generateCubeIndices(indices, 3, 2, 10, 11, 6, 7, 15, 14); // top cube
    generateCubeIndices(indices, 8, 9, 1, 0, 13, 12, 4, 5); // bottom cube
}

//--------------------------------------------------------------
void ofApp::setup() {
    
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 

}
