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
uniform int spotlight;

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
	 ambient_light =Ke * 1/100;

	// TODO: compute diffuse light component
	 diffuse_light =material_kd * material_shininess * max (dot(world_normal,L), 0);

	// TODO: compute specular light component
	 specular_light =  material_ks * material_shininess * primesteLumina * pow(max(dot(world_normal, H), 0), 128);

	// TODO: compute light
	float factorAtenuare = 1/(dot(world_normal,light_position)* dot(world_normal,light_position)* dot(world_normal,light_position)* dot(world_normal,light_position)* dot(world_normal,light_position)* dot(world_normal,light_position)* dot(world_normal,light_position)* dot(world_normal,light_position));
	
	float intensitate = Ke + ambient_light + factorAtenuare * ( diffuse_light + specular_light );

	// TODO: send color light output to fragment shader
	if(spotlight==1){
	float cut_off = radians(30);
float spot_light = dot(-L, light_direction);
if (spot_light < cos(cut_off))
{
	// fragmentul este iluminat de spot, deci se calculeaza valoarea luminii conform  modelului Phong
	// se calculeaza atenuarea luminii
	out_color = vec4(object_color * (Ke + intensitate * (ambient_light + factorAtenuare * ( diffuse_light + specular_light ))),1); 
}
else{
//float cut_off = radians(30);
///float spot_light = dot(-L, light_direction);
float spot_light_limit = cos(cut_off);
 
// Quadratic attenuation
float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
float light_att_factor = pow(linear_att, 2);

	
	out_color = vec4(object_color * (Ke + intensitate * (ambient_light + light_att_factor * ( diffuse_light + specular_light ))),1); 
	}}
	else 
	out_color = vec4(object_color * (Ke + intensitate * (ambient_light + factorAtenuare * ( diffuse_light + specular_light ))),1); 
	// TODO: compute light

	// TODO: write pixel out color
	//out_color = vec4(1);
}