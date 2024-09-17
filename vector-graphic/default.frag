#version 330 core

// Output colors in RGBA
out vec4 FragColor;

// Input from vertex shader
in vec3 color;

in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, texCoord);
}