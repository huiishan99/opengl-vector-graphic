#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aTex;

// Outputs the color to the fragment shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

uniform mat4 camMatrix;

void main()
{
	// Output the position of the vertex
	gl_Position = camMatrix * vec4(aPos, 1.0);
	// Assign the color to the output
	color = aColor;
	texCoord = aTex;
}