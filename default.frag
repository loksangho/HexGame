#version 120
// Imports the texture coordinates from the Vertex Shader
varying vec3 crntPos;

// Imports the normal from the Vertex Shader
varying vec3 Normal;
// Imports the color from the Vertex Shader
varying vec3 color;
// Imports the current position from the Vertex Shader
varying vec2 texCoord;


// Gets the Texture Unit from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;


vec4 pointLight()
{
        // used in two variables so I calculate it here to not have to do it twice
        vec3 lightVec = lightPos - crntPos;

        // intensity of light with respect to distance
        float dist = length(lightVec);
        float a = 3.0;
        float b = 0.7;
        float inten = 1.0 / (a * dist * dist + b * dist + 1.0);

        // ambient lighting
        float ambient = 0.20;

        // diffuse lighting
        vec3 normal = normalize(Normal);
        vec3 lightDirection = normalize(lightVec);
        float diffuse = max(dot(normal, lightDirection), 0.0);

        // specular lighting
        float specularLight = 0.50;
        vec3 viewDirection = normalize(camPos - crntPos);
        vec3 reflectionDirection = reflect(-lightDirection, normal);
        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16.0);
        float specular = specAmount * specularLight;

        return (texture2D(diffuse0, texCoord) * (diffuse * inten + ambient) + texture2D(specular0, texCoord).r * specular * inten) * lightColor * vec4(color,1.0);
}

vec4 direcLight()
{
        // ambient lighting
        float ambient = 1.20f;

        // diffuse lighting
        vec3 normal = normalize(Normal);
        vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
        float diffuse = max(dot(normal, lightDirection), 0.0f);

        // specular lighting
        float specularLight = 0.50f;
        vec3 viewDirection = normalize(camPos - crntPos);
        vec3 reflectionDirection = reflect(-lightDirection, normal);
        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16.0f);
        float specular = specAmount * specularLight;

        return (texture2D(diffuse0, texCoord) * (diffuse + ambient) + texture2D(specular0, texCoord).r * specular) * lightColor * vec4(color,1.0);
}

vec4 spotLight()
{
        // controls how big the area that is lit up is
        float outerCone = 0.90;
        float innerCone = 0.95;

        // ambient lighting
        float ambient = 0.20;

        // diffuse lighting
        vec3 normal = normalize(Normal);
        vec3 lightDirection = normalize(lightPos - crntPos);
        float diffuse = max(dot(normal, lightDirection), 0.0);

        // specular lighting
        float specularLight = 0.50;
        vec3 viewDirection = normalize(camPos - crntPos);
        vec3 reflectionDirection = reflect(-lightDirection, normal);
        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16.0);
        float specular = specAmount * specularLight;

        // calculates the intensity of the crntPos based on its angle to the center of the light cone
        float angle = dot(vec3(0.0, -1.0, 0.0), -lightDirection);
        float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0, 1.0);

        return (texture2D(diffuse0, texCoord) * (diffuse * inten + ambient) + texture2D(specular0, texCoord).r * specular * inten) * lightColor * vec4(color,1.0);
}

float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth)
{
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth, float steepness, float offset)
{
    float zVal = linearizeDepth(depth);
    return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()
{
    //float depth = logisticDepth(gl_FragCoord.z, 0.5, 5.0);
    gl_FragColor = direcLight(); // * (1.0 - depth) + vec4(depth * vec3(0.85, 0.85, 0.90), 1.0);
        // outputs final color
        //gl_FragColor = direcLight();
    //gl_FragColor = vec4(0.0,1.0,0.0,1.0);
}

