#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec4 color1=texture2D(texture_1,texcoord);
	if(color1.a<0.5f)
	discard;
	vec4 color2=texture2D(texture_2,texcoord);
	if(color2.a<0.5f)
	discard;
	vec4 colorf=mix(color1,color2,0.5f);

	out_color = colorf;
}