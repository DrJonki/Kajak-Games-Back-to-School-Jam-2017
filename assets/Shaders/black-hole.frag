#version 130

uniform sampler2D texture;
uniform float tick;
uniform float direction;
uniform vec2 primeVec;
uniform float mass;
uniform float horizon;
// uniform vec2 holepos[5];

void main()
{
	float holeSpeed = 0.05;
	vec2 holePosition = vec2(0.5,0.5) + vec2(0.5*sin(holeSpeed*primeVec.x*tick), 0.5*cos(holeSpeed*primeVec.y*tick));
	float massWobbly = mass*(1+0.5*sin(tick));
	float horizonDist = horizon * (1 + 0.2 * sin(tick));
	vec2 driver = holePosition - gl_TexCoord[0].xy;
	float originalLength = length(driver);
	driver = normalize(driver);


	vec2 displacement = (direction * 0.05/(originalLength + massWobbly) - horizonDist)* driver;
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