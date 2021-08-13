#version 120
attribute vec3 aPos;
attribute vec3 aNormal;
attribute vec3 aColor;
attribute vec2 aTex;





// Imports the camera matrix
uniform mat4 camMatrix;
// Imports the transformation matrices
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;


// Outputs the current position for the Fragment Shader
varying  vec3 crntPos;
// Outputs the normal for the Fragment Shader
varying vec3 Normal;
// Outputs the color for the Fragment Shader
varying vec3 color;
// Outputs the texture coordinates to the Fragment Shader
varying vec2 texCoord;


void main()
{
        // calculates current position
        crntPos = vec3(model * translation * rotation * scale * vec4(aPos, 1.0f));
        // Assigns the normal from the Vertex Data to "Normal"
        Normal = aNormal;
        // Assigns the colors from the Vertex Data to "color"
        color = aColor;
        // Assigns the texture coordinates from the Vertex Data to "texCoord"
        texCoord =  aTex;
        // Outputs the positions/coordinates of all vertices
        gl_Position = camMatrix * vec4(crntPos, 1.0f);

}
