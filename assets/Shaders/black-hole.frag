#version 130

uniform sampler2D texture;
uniform float tick;
uniform float direction;
// uniform vec2 holepos[5];

void main()
{
	float holeSpeed = 0.1;
	vec2 holePosition = vec2(0.5,0.5) + vec2(0.5*sin(holeSpeed*19*tick), 0.5*cos(holeSpeed*13*tick));
	float mass = 0.001 + 0.002 * sin(tick);
	float horizonDist = 0.04 + 0.01 * sin(tick);
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