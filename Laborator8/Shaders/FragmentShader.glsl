#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;


layout(location = 0) out vec4 out_color;

void main()
{

	// TODO: define ambient light component
	float ambient_light = 0.25;

	// TODO: compute diffuse light component
	float diffuse_light = 0;

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
	}


	vec3 L = normalize( light_position - world_position );
	vec3 V = normalize( eye_position - world_position );
	vec3 H = normalize( L + V );
	 vec3 R = reflect (-L, world_normal);
	 int primesteLumina=0;
	 if(dot(world_normal, L)>0){
	 primesteLumina =1;
	 }
	 float Ke=material_kd;

	

	// TODO: define ambient light component
	 ambient_light =Ke * 0.25;

	// TODO: compute diffuse light component
	 diffuse_light =material_kd * material_shininess * max (dot(world_normal,L), 0);

	// TODO: compute specular light component
	 specular_light =  material_ks * material_shininess * primesteLumina * pow(max(dot(world_normal, H), 0), 64);

	if (diffuse_light > 0)
	{
	}
	

	// TODO: compute light
	float factorAtenuare = 1/(dot(world_normal,light_position)* dot(world_normal,light_position)* dot(world_normal,light_position)* dot(world_normal,light_position));
	
	float intensitate = Ke + ambient_light + factorAtenuare * ( diffuse_light + specular_light );

	// TODO: send color light output to fragment shader


	
	out_color = vec4(object_color * (Ke + intensitate * (ambient_light + factorAtenuare * ( diffuse_light + specular_light ))),1); 

	// TODO: compute light

	// TODO: write pixel out color
	//out_color = vec4(1);
}