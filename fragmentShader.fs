#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 normal;
in vec3 Lpos;
in vec3 FragPos;
struct material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shine;
};
uniform material mat;
struct material2 {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform material2 matt2;
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;
// texture sampler
uniform sampler2D texture1;
uniform bool useTexture;
uniform vec3 u_Color;

void main()
{
    //making vectors
    vec3 norm=normalize(normal);
		vec3 lightdir=normalize(Lpos-FragPos);
         float ambient_power=0.5f;
         float diff=max(dot(norm,lightdir),0.0f);
	if(useTexture){
		
        //-----------------------------------------
        //ambient
       
        vec3 ambience=vec3(ambient_power*texture(mat.diffuse,TexCoord)*light.ambient);
        //----------------------------------------------------------------
        //diffuse
        
        vec3 diffuse = vec3(diff*texture(mat.diffuse,TexCoord)*light.diffuse);
        //---------------------------------------------------------------------
        vec3 result=ambience+diffuse;
        FragColor=vec4(result,1.0f);
		//FragColor = texture(texture1, TexCoord);
	} else {
        vec3 ambience=vec3(ambient_power*light.ambient);
        vec3 diffuse = (diff*matt2.diffuse)*light.diffuse;
        vec3 result=(ambience+diffuse)*u_Color;
        FragColor=vec4(result,1.0f);
		//FragColor = vec4(u_Color,1.0f);

	}
}