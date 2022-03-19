#version 330

// TODO: get values from fragment shader
//in vec3 frag_normal;
in vec3 frag_pos;
in vec3 frag_normal;

in vec2 frag_coord;
in vec3 frag_color;

layout(location = 0) out vec4 out_pos;
layout(location = 1) out vec4 out_normal;

layout(location = 2) out vec3 out_coord;
layout(location = 3) out vec4 out_color;



void main()
{	
	// TODO: write pixel out color

	out_pos = vec4(frag_color, 1);

	//out_color = vec4(frag_color, 1);

	out_color = vec4(frag_color, 1);

	out_coord = vec3(frag_coord, 1);
	//out_normal= vec4(frag_normal, 1);

	out_normal= vec4(frag_color, 1);


	 
}