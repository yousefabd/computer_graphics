#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 normal;
in vec3 Lpos;
in vec3 FragPos;
//texture
struct material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shine;
};
//color
struct material2 {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;
uniform material mat;
uniform material2 matt2;
uniform sampler2D texture1;
uniform bool useTexture;
uniform vec3 u_Color;

void main()
{
    //making vectors
    vec3 norm=normalize(normal);
		vec3 lightdir=normalize(FragPos-light.position);
         float ambient_power=1.0f;
         float diff=max(dot(norm,lightdir),0.0f);
	if(useTexture){
        //-----------------------------------------
        //ambient 
        vec3 ambience = vec3(ambient_power*texture(mat.diffuse,TexCoord).rgb*light.ambient);
        //----------------------------------------------------------------
        //diffuse
        
        vec3 diffuse = light.diffuse*diff*texture(mat.diffuse,TexCoord).rgb;
        //---------------------------------------------------------------------
        vec3 result=ambience+diffuse;
        FragColor=vec4(result,1.0f);	
	} else {
		vec3 ambience=vec3(ambient_power*light.ambient);
        vec3 diffuse = (diff*matt2.diffuse)*light.diffuse;
        vec3 result=(ambience+diffuse)*u_Color;
        FragColor=vec4(result,1.0f);
	}
}