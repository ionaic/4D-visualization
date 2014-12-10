#version 330

in vec4 position;
in vec4 color;
in vec2 texcoord;

uniform mat4 modelViewProjectionMatrix;

//uniform mat4 modelMatrix;
//uniform mat4 viewMatrix;
//uniform mat4 projectionMatrix;

out vec4 vs_Color;
out vec4 vs_Pos;

void main(void) {
    vs_Pos = position;
    // w values will end up doing weird things as it makes the coords non-homogenous
    vs_Pos.w = 1.0; 
    gl_Position = modelViewProjectionMatrix * vs_Pos;
    if (position.w > 0.1) {
        gl_Position.x = gl_Position.x + 200.0f;
        gl_Position.y = gl_Position.y + 200.0f;
    }

    vs_Color = color;
}
