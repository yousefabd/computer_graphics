#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform bool useTexture;
uniform vec3 u_Color;

void main()
{
	if(useTexture){
		FragColor = texture(texture1, TexCoord);
	} else {
		FragColor = vec4(u_Color,1.0f);
	}
}