#version 130

uniform sampler2D texture;
uniform float tick;
uniform float direction;

void main()
{
	vec4 pixel = vec4(0.0, 0.0, 0.0, 0.0);

    gl_FragColor = pixel;
}