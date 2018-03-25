#version 330 core

out vec4 FragColor;

void main()
{
	vec3 lampColor = vec3(1.0, 1.0, 1.0);
	FragColor = vec4(lampColor, 1.0);
}
