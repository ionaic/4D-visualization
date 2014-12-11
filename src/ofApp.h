#pragma once

#include "ofMain.h"
#include <vector>

union Mat5x5 {
    struct {
        float _00, _01, _02, _03, _04,
              _10, _11, _12, _13, _14,
              _20, _21, _22, _23, _24,
              _30, _31, _32, _33, _34,
              _40, _41, _42, _43, _44;
    };
    float data[5][5];
    float data_v[25];
};

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

        ofShader testShader;
        
        std::vector<float> hcube_vert;
        std::vector<unsigned int> hcube_idx;
        std::vector<float> hcube_color;
        std::vector<float> hcube_vert_vel;

        Mat5x5 view4D;
        Mat5x5 proj4D;

        ofVbo hcube_vbo;
        ofLight light;
        ofCamera camera;

        bool fullscreen;
        bool randomMovement;
        bool rotate;

        int lastMX, lastMY;
        int screen_width, screen_height;

};
