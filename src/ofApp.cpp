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
        vertices.push_back(idx % 2 * size);
        vertices.push_back(1.0f);
        //vertices.push_back(((float)(idx > 1)) * size);

        vertices.push_back(size);
        vertices.push_back(0.0);
        vertices.push_back(idx % 2 * size);
        vertices.push_back(1.0f);
        //vertices.push_back(((float)(idx > 1)) * size);

        vertices.push_back(size);
        vertices.push_back(size);
        vertices.push_back(idx % 2 * size);
        vertices.push_back(1.0f);
        //vertices.push_back(((float)(idx > 1)) * size);

        vertices.push_back(0.0);
        vertices.push_back(size);
        vertices.push_back(idx % 2 * size);
        vertices.push_back(1.0f);
        //vertices.push_back(((float)(idx > 1)) * size);
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
    generateHypercube(hcube_vert, hcube_idx, 100.0f);

    // the hypercube is white, non-hypercube is blue
    for (unsigned int idx = 0; idx < hcube_vert.size(); ++idx) {
        //unsigned int list_factor = (idx > hcube_vert.size()/2);
        unsigned int list_factor = 0.0f;
        ofFloatColor c((float)list_factor, (float)list_factor, 1.0f, 1.0f);
        hcube_color.push_back(c);
        //hcube_color.push_back((float) list_factor);
        //hcube_color.push_back((float) list_factor);
        //hcube_color.push_back(1.0f);
        //hcube_color.push_back(1.0f);
    }

    // trying to use a mesh to add the vertices instead and then modify the position attributes later
    for (std::vector<float>::iterator itr = hcube_vert.begin(); itr != hcube_vert.end(); ++itr) {
        ofVec3f vert;

        // set x
        vert.x = *itr;
        // set y
        if (itr != hcube_vert.end()) {
            vert.y = *(++itr);
        }
        // set z
        if (itr != hcube_vert.end()) {
            vert.z = *(++itr);
        }
        // ignore w
        if (itr != hcube_vert.end()) {
            ++itr;
        }
        cube_mesh.addVertex(vert);
        hcube_vert3f.push_back(vert);
    }

    //hcube_vbo.setMesh(cube_mesh, GL_STATIC_DRAW);

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
    for (std::vector<ofFloatColor>::iterator itr = hcube_color.begin(); itr != hcube_color.end(); ++itr) {
        std::cout << *itr << std::endl;
        //std::cout << "(" << *itr;
        //if (itr != hcube_color.end()) {
        //    std::cout << ", " << *(++itr);
        //}
        //if (itr != hcube_color.end()) {
        //    std::cout << ", " << *(++itr);
        //}
        //if (itr != hcube_color.end()) {
        //    std::cout << ", " << *(++itr) << ")" << std::endl;
        //}
    }

    hcube_vbo.setAttributeData(ofShader::POSITION_ATTRIBUTE, &hcube_vert[0], 4, hcube_vert.size(), GL_STATIC_DRAW);
    //hcube_vbo.setVertexData(&hcube_vert3f[0], hcube_vert3f.size(), GL_STATIC_DRAW);
    hcube_vbo.setColorData(&hcube_color[0], hcube_color.size(), GL_STATIC_DRAW);
    hcube_vbo.setIndexData(&hcube_idx[0], hcube_idx.size(), GL_STATIC_DRAW);

    //std::cout << hcube_vbo << std::endl;

    camera.setPosition(ofGetWidth()/2, ofGetHeight()/2, 1);
    camera.lookAt(ofVec3f(0.5, 0.5, 0.5));

    light.setSpotlight();
    light.setPosition(ofGetWidth()/2 + 100, ofGetHeight()/2 - 100, 1);
    light.lookAt(ofVec3f(0.5, 0.5, 0.5));

    glDisable(GL_CULL_FACE);

    sphere.setRadius(100.0f);
    sphere.setPosition(0.0, 0.0, 0.0);

    std::cout << hcube_vbo.getNumVertices()<< std::endl;
    std::cout << hcube_vbo.getNumIndices()<< std::endl;
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    camera.begin();

    light.enable();

    hcube_vbo.drawElements(GL_TRIANGLES, hcube_idx.size());
    //glPointSize(10.0f);
    //hcube_vbo.draw(GL_POINTS, 0, hcube_vbo.getNumVertices());
    //cube_mesh.draw(OF_MESH_POINTS);
    //sphere.draw();

    light.disable();

    camera.end();
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
