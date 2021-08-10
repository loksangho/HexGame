#version 120
attribute vec3 aNormal;
attribute vec3 aPos;

uniform mat4 model;
uniform mat4 camMatrix;

void main(void)
{
    gl_Position = camMatrix * model * vec4(aPos, 1.0);
}
