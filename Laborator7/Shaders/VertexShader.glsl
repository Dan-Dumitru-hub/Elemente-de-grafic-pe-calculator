#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

// Output value to fragment shader
out vec3 color;

void main()
{
	// TODO: compute world space vectors
	vec3 world_pos = (Model * vec4(v_position,1)).xyz;
	vec3 world_normal = normalize( mat3(Model) * v_normal );
	vec3 L = normalize( light_position - world_pos );
	vec3 V = normalize( eye_position - world_pos );
	vec3 H = normalize( L + V );
	 vec3 R = reflect (-L, world_normal);
	 int primesteLumina=0;
	 if(dot(world_normal, L)>0){
	 primesteLumina =1;
	 }
	 float Ke=material_kd;

	

	// TODO: define ambient light component
	float ambient_light =Ke * 0.25;

	// TODO: compute diffuse light component
	float diffuse_light =material_kd * material_shininess * max (dot(world_normal,L), 0);

	// TODO: compute specular light component
	float specular_light =  material_ks * material_shininess * primesteLumina * pow(max(dot(world_normal, H), 0), 64);

	if (diffuse_light > 0)
	{
	}
	

	// TODO: compute light
	float factorAtenuare = 1/(dot(world_normal,light_position)* dot(world_normal,light_position)* dot(world_normal,light_position)* dot(world_normal,light_position));
	
	float intensitate = Ke + ambient_light + factorAtenuare * ( diffuse_light + specular_light );

	// TODO: send color light output to fragment shader
	
	color = object_color * (Ke + intensitate * (ambient_light + factorAtenuare * ( diffuse_light + specular_light ))); 

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
