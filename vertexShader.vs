#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoord;
layout (location = 2) in vec3 aNormal;
out vec2 TexCoord;
out vec3 normal;
out vec3 FragPos;
out vec3 Lpos;
uniform vec3 lightpos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	normal=mat3(transpose(inverse(model*view)))*aNormal;
	FragPos=vec3(view*vec4(aPos,1.0f));
	Lpos=vec3(view*vec4(lightpos,1.0f));
}
