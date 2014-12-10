#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::generateCubeIndices(std::vector<unsigned int> &dest,
    unsigned int f_l_b, // front left bottom
    unsigned int f_r_b, // front right bottom
    unsigned int f_r_t, // front right top
    unsigned int f_l_t, // front left top
    unsigned int b_l_b, // back left bottom
    unsigned int b_r_b, // back right bottom
    unsigned int b_r_t, // back right top
    unsigned int b_l_t  // back left top
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
void ofApp::generateHypercube(std::vector<float> &vertices, std::vector<unsigned int> &indices, float size) {
    // generate vertices
    for (unsigned int idx = 0; idx < 4; ++idx) {
        vertices.push_back(0.0);
        vertices.push_back(0.0);
        //vertices.push_back(idx % 2 * size + ((float)(idx > 1)) * size);
        //vertices.push_back(idx % 2 * size + ((float)(idx > 1)));
        vertices.push_back(idx % 2 * size);
        vertices.push_back(((float)(idx > 1)) * size);

        vertices.push_back(size);
        vertices.push_back(0.0);
        //vertices.push_back(idx % 2 * size + ((float)(idx > 1)) * size);
        //vertices.push_back(idx % 2 * size + ((float)(idx > 1)));
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
    testShader.load("shaders/fourD/fourD");

    fullscreen = false;
    randomMovement = false;
    rotate = false;

    screen_width = ofGetScreenWidth();
    screen_height = ofGetScreenHeight();

    lastMX = lastMY = 0;

    generateHypercube(hcube_vert, hcube_idx, 100.0f);

    // the hypercube is white, non-hypercube is blue
    for (unsigned int idx = 0; idx < hcube_vert.size(); idx+=4) {
        unsigned int list_factor = (idx > hcube_vert.size()/2);

        hcube_color.push_back((float)list_factor);
        hcube_color.push_back((float)list_factor);
        hcube_color.push_back(1.0f);
        hcube_color.push_back(1.0f);

        // assign random velocities (4d)
        hcube_vert_vel.push_back(ofRandom(0.0f, 20.0f));
        hcube_vert_vel.push_back(ofRandom(0.0f, 20.0f));
        hcube_vert_vel.push_back(ofRandom(0.0f, 20.0f));
        hcube_vert_vel.push_back(ofRandom(0.0f, 20.0f));
    }

    // debug print verts
    for (std::vector<float>::iterator itr = hcube_vert.begin(); itr != hcube_vert.end(); ++itr) {
        std::cout << "(" << *itr;
        if (itr != hcube_vert.end()) {
            std::cout << ", " << *(++itr);
        }
        if (itr != hcube_vert.end()) {
            std::cout << ", " << *(++itr);
        }
        if (itr != hcube_vert.end()) {
            std::cout << ", " << *(++itr) << ")" << std::endl;
        }
    }

    // debug print indices
    for (std::vector<unsigned int>::iterator itr = hcube_idx.begin(); itr != hcube_idx.end(); ++itr) {
        std::cout << "(" << *itr;
        if (itr != hcube_idx.end()) {
            std::cout << ", " << *(++itr);
        }
        if (itr != hcube_idx.end()) {
            std::cout << ", " << *(++itr);
        }
        if (itr != hcube_idx.end()) {
            std::cout << ", " << *(++itr);
        }
        if (itr != hcube_idx.end()) {
            std::cout << ", " << *(++itr);
        }
        if (itr != hcube_idx.end()) {
            std::cout << ", " << *(++itr) << ")" << std::endl;
        }
    }

    // debug print colors
    for (std::vector<float>::iterator itr = hcube_color.begin(); itr != hcube_color.end(); ++itr) {
        std::cout << "(" << *itr;
        if (itr != hcube_color.end()) {
            std::cout << ", " << *(++itr);
        }
        if (itr != hcube_color.end()) {
            std::cout << ", " << *(++itr);
        }
        if (itr != hcube_color.end()) {
            std::cout << ", " << *(++itr) << ")" << std::endl;
        }
    }

    hcube_vbo.setVertexData(&hcube_vert[0], 4, hcube_vert.size(), GL_STATIC_DRAW, sizeof(float) * 4);
    hcube_vbo.setColorData(&hcube_color[0], hcube_color.size(), GL_STATIC_DRAW, sizeof(float));
    hcube_vbo.setIndexData(&hcube_idx[0], hcube_idx.size(), GL_STATIC_DRAW);

    camera.setPosition(ofGetWidth()/2, ofGetHeight()/2, 1);
    camera.lookAt(ofVec3f(0.5, 0.5, 0.5));

    light.setSpotlight();
    light.setPosition(ofGetWidth()/2 + 100, ofGetHeight()/2 - 100, 1);
    light.lookAt(ofVec3f(0.5, 0.5, 0.5));

    std::cout << hcube_vbo.getNumVertices()<< std::endl;
    std::cout << hcube_vbo.getNumIndices()<< std::endl;
    std::cout << hcube_idx.size() << std::endl;
}

//--------------------------------------------------------------
void ofApp::update() {
    //if (rotate) {
    //    for (unsigned int idx = 0; idx < hcube_vert.size() - 4 && idx < hcube_vert.size() - 4; ++idx) {
    //        // ruh roh raggy, rhis ray re rull rut re're
    //        // r(k)etching ro rho rares! (this may be null but
    //        // we're sketching so who cares!)
    //        ofNode pos(hcube_vert[idx], hcube_vert[idx + 1], hcube_vert[idx + 2], hcube_vert[idx + 3]);
    //        pos.rotateAround(5, ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(0.0f, 0.0f, 0.0f));

    //        hcube_vert[idx] = pos.x;
    //        hcube_vert[idx + 1] = pos.y;
    //        hcube_vert[idx + 2] = pos.z;
    //        hcube_vert[idx + 3] = pos.w;
    //    }
    //}

    if (randomMovement) {
        // update the positions based on the velocity
        // ONE BIG MEDIEVAL MESS.  I blame iterator and scope
        // syntax
        for (std::vector<float>::iterator itr = hcube_vert.begin(), vitr = hcube_vert_vel.begin(); itr != hcube_vert.end() && vitr != hcube_vert_vel.end(); ++itr, ++vitr) {
            *itr += *vitr;
        }

        // collision detection, keep them within a certain
        // hypersphere of influence
        for (unsigned int idx = 0; idx < hcube_vert.size() - 4 && idx < hcube_vert_vel.size() - 4; ++idx) {
            // ruh roh raggy, rhis ray re rull rut re're
            // r(k)etching ro rho rares! (this may be null but
            // we're sketching so who cares!)
            ofVec4f pos(hcube_vert[idx], hcube_vert[idx + 1], hcube_vert[idx + 2], hcube_vert[idx + 3]);
            ofVec4f vel(hcube_vert_vel[idx], hcube_vert_vel[idx + 1], hcube_vert_vel[idx + 2], hcube_vert_vel[idx + 3]);
            // take the length of the vector, we're keeping this in a hypersphere centered at (0,0,0,0) with radius 500
            if (pos.length() > 500) {
                ofVec4f norm = pos * -1;
                norm.normalize();
                
                vel = vel - (2.0f * vel.dot(norm)) * norm;
            }

            hcube_vert_vel[idx] = vel.x;
            hcube_vert_vel[idx + 1] = vel.y;
            hcube_vert_vel[idx + 2] = vel.z;
            hcube_vert_vel[idx + 3] = vel.w;
        }

        hcube_vbo.updateVertexData(&hcube_vert[0], hcube_vert.size());
    } 
}

//--------------------------------------------------------------
void ofApp::draw() {
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    camera.begin();

    testShader.begin();

    hcube_vbo.drawElements(GL_TRIANGLES, hcube_vbo.getNumIndices());
    glPointSize(10.0f);
    hcube_vbo.draw(GL_POINTS, 0, hcube_vbo.getNumVertices());

    testShader.end();

    camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // toggle fullscreen
    switch(key) {
        case 'f':
        case 'F':
            // toggle fullscreen
            fullscreen = !fullscreen;
            ofSetFullscreen(fullscreen);
            break;
        case 'm':
        case 'M':
            // toggle random movement
            randomMovement = !randomMovement;
            break;
        case 'r':
        case 'R':
            // reset by re-running setup
            hcube_vert.clear();
            hcube_idx.clear();
            hcube_color.clear();
            hcube_vert_vel.clear();
            setup();
            break;
        case 's':
        case 'S':
            // rotate things because it'll look pretty
            rotate = !rotate;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    //std::cout << "Mouse button: " << button << std::endl;
    static ofVec3f center(0.0f, 0.0f, 0.0f);
    static ofVec3f up(0.0f, 1.0f, 0.0f);

    ofVec2f delta(x - lastMX, y - lastMY);
    ofVec3f toCenter = camera.getPosition() - center;
    ofVec3f right = toCenter.cross(up);

    switch (button) {
        case 0: // left
            // translate
            //camera.move(delta.x, delta.y, 0.0f);
            camera.move(right.x * delta.length(), right.y * delta.length(), 0.0f);
            break;
        case 1: // middle
            // zoom in and out with click/drag
            camera.move(0.0f, 0.0f, delta.x);
            break;
        case 2: // right
            // rotate around the object
            camera.rotateAround(360.0 * -1.0f * (delta.x / screen_width), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(0.0f, 0.0f, 0.0f));
            camera.rotateAround(360.0 * -1.0f * (delta.y / screen_height), ofVec3f(1.0f, 0.0f, 0.0f), ofVec3f(0.0f, 0.0f, 0.0f));
            camera.lookAt(ofVec3f(0.0f, 0.0f, 0.0f));
            break;
    }

    // once we're dragging, update
    lastMX = x;
    lastMY = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    // set these so that initially on click nothing moves
    lastMX = x;
    lastMY = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    screen_width = w;
    screen_height = h;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 

}
