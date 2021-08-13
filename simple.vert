#version 140

in vec3 vertexPosition_modelspace;

void main(){
    gl_Position = vec4( vertexPosition_modelspace, 1.0);
    //gl_Position.w = 1.0;
}

