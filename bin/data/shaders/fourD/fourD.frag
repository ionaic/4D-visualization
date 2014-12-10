#version 330

uniform vec4 light_position;

in vec4 vs_Color;
in vec4 vs_Pos;

out vec4 out_Color;

void main(void) {
    //out_Color = vs_Color * dot(vs_Pos, light_position);
    out_Color = vs_Color;
}
