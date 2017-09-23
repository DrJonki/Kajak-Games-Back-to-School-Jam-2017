#version 130

uniform sampler2D texture;
uniform float tick;
uniform float direction;
// uniform vec2 holepos[5];

void main()
{
	float holeSpeed = 0.05;
	vec2 holePosition = vec2(0.5*sin(holeSpeed*19*tick), 0.5*cos(holeSpeed*13*tick));
	float mass = 1.0;
	float horizonDist = 0.02;
	vec2 driver = holePosition - gl_TexCoord[0].xy;
	float originalLength = length(driver);
	driver = normalize(driver);


	vec2 displacement = (direction * 0.05/(originalLength + mass) - horizonDist)* driver;
	vec4 pixel;
	if(originalLength > horizonDist)
	{
		pixel = texture2D(texture, gl_TexCoord[0].xy + displacement);
	}
	else
	{
		pixel = vec4(0.0, 0.0, 0.0, 0.0);
	}

    gl_FragColor = pixel;
}