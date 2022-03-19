#version 330

// TODO: get vertex attributes from each location
//pncc
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;

layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 v_color;


//Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;


// TODO: output values to fragment shader
out vec3 frag_pos;
out vec3 frag_normal;

out vec2 frag_coord;
out vec3 frag_color;



void main()
{
	// TODO: send output to fragment shader
	frag_pos=v_position;
	frag_color=v_color;
	frag_coord=tex_coord;
	frag_normal=v_normal;

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
	// TODO: compute gl_Position
}
