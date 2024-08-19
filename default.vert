#version 330 core

// Position/Coordinates
layout (location = 0) in vec3 aPos;
// Color
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aTex;

// Output the color to the fragment shader
out vec3 color;

out vec2 texCoord;

// Controls the scale of the vertices
uniform float scale;

void main()
{
	// Output the position/coordinates of all the vertex
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	// Assign the color from the vertex data to the "color"
	color = aColor;
	texCoord = aTex;
}

