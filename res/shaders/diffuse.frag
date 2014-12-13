#version 330 core

struct Light {
	vec3 position;
	vec3 color;
	vec3 attenuation;
};

uniform Light lights[100];
uniform int numLights;

uniform mat4 modelMatrix;

in vec3 pass_position;
in vec2 pass_texCoord;
in vec3 pass_normal;
in vec3 pass_tangent;

out vec4 out_Color;

void main(void) {
    vec3 refl = vec3(0, 0, 0);
    
	// Normals
	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    vec3 normal = normalize(normalMatrix * pass_normal);
	
	// Calculate the location of this fragment (pixel) in world coordinates
    vec4 position = modelMatrix * vec4(pass_position, 1);

    for(int i = 0; i < numLights; i++) {
        //Calculate the vector from this pixels surface to the light source
    	vec3 lightDir = lights[i].position - position.xyz;
    	float length = length(lightDir);
    	vec3 lightColor = lights[i].color;
    
    	float constantAtt  = lights[i].attenuation.x;
    	float linearAtt    = lights[i].attenuation.y;
    	float quadraticAtt = lights[i].attenuation.z;
    	
	    //Calculate the cosine of the angle of incidence (brightness)
	    float fDiffuse = dot(normal, normalize(lightDir));
	    float fAttTotal = 1 / (constantAtt + linearAtt * length + quadraticAtt * length * length);
	    refl.r += lightColor.r * fAttTotal * fDiffuse;
	    refl.g += lightColor.g * fAttTotal * fDiffuse;
	    refl.b += lightColor.b * fAttTotal * fDiffuse;
   }
	
	out_Color = vec4(refl, 1);
}
