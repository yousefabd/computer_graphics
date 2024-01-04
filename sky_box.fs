#version 330 core
in vec3 TexCoords;
out vec4 FragColor;
uniform samplerCube sky;
void main()
{
	FragColor=texture(sky,TexCoords);
}