#pragma once

#include "ofMain.h"

#include <vector>

class ofApp : public ofBaseApp{

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

        void generateHypercube(std::vector<float> &vertices, std::vector<unsigned int> &indices, float size = 1.0f);
		
    private:
        void generateCubeIndices(std::vector<unsigned int> &dest,
            unsigned int f_l_b, // front left bottom
            unsigned int f_r_b, // front right bottom
            unsigned int f_r_t, // front right top
            unsigned int f_l_t, // front left top
            unsigned int b_l_b, // back left bottom
            unsigned int b_r_b, // back right bottom
            unsigned int b_r_t, // back right top
            unsigned int b_l_t  // back left top
        );
        
        std::vector<float> hcube_vert;
        std::vector<unsigned int> hcube_idx;

        unsigned int index4D = { 
             0,  1,  2,  0,  2,  3, // front w0
             1,  5,  6,  1,  6,  2, // right w0
             5,  4,  7,  5,  7,  6, // back w0
             4,  0,  3,  4,  3,  7, // left w0
             4,  5,  1,  4,  1,  0, // bottom w0
             3,  2,  6,  3,  6,  7, // top w0

             8,  9, 10,  8, 10, 11, // front w1
             9, 13, 14,  9, 14, 10, // right w1
            13, 12, 15, 13, 15, 14, // back w1
            12,  8, 11, 12, 11, 15, // left w1
            12, 13,  9, 12,  9,  8, // bottom w1
            11, 10, 14, 11, 14,  7, // top w1

             8,  9, 10,  8, 10, 11, // front (front w1)
             9,  1,  2,  9,  2, 10, // right w0/1
             1,  0,  3,  1,  3,  2, // back (front w0)
             0,  8, 11,  0, 11,  3, // left w0/1
             0,  1,  9,  0,  9,  8, // bottom w0/1
            11, 10,  2, 11,  2,  3, // top w0/1

             1,  9, 10,  1, 10,  2, // front w0/1
             9, 13, 14,  9, 14, 10, // right (right w1)
             13, 5,  6,  13, 6, 14, // back w0/1
             1,  5,  6,  1,  6,  2, // left (right w0)
             5, 13,  9,  5,  9,  1, // bottom w0/1
             2, 10, 14,  2, 14,  6, // top w0/1

             5,  4,  7,  5,  7,  6, // front (back w0)
             5, 13, 14,  5, 14,  6, // right w0/1
            13, 12, 15, 13, 15, 14, // back (back w1)
             5, 13, 14,  5, 14,  6, // left w0/1
        };
};
