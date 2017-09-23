#version 130

uniform sampler2D texture;
uniform float tick;
uniform float modifiableValue;

void main()
{
	float hueScale = 0.1 + modifiableValue * cos(tick/10+3.14159);
	float travelSpeed = 0.2;
	float stroboSpeed = 0.2;
	float stroboVaryTime = 1;
	float waveLengthVariator = 10;
	float waveLengthVariationSpeed = 1;
	float centerDistancevariator = 0.3 + 0.3 * sin(tick);
	vec2 effectCenter = vec2(0.5+centerDistancevariator*sin(17*tick*travelSpeed), 0.5+centerDistancevariator*cos(7*tick*travelSpeed));
	vec2 distVec = effectCenter - gl_TexCoord[0].xy;
	float dist = length(distVec);
	float animDist = (dist+tick*stroboSpeed)*sin(tick*stroboVaryTime);

	vec4 prePixel = texture2D(texture, gl_TexCoord[0].xy);

	prePixel.r = prePixel.r * (1.0 - hueScale + hueScale * sin((100 + waveLengthVariator * sin(tick * waveLengthVariationSpeed))*animDist));
	prePixel.g = prePixel.g * (1.0 - hueScale + hueScale * sin((200 + waveLengthVariator * sin(tick * waveLengthVariationSpeed))*animDist));
	prePixel.b = prePixel.b * (1.0 - hueScale + hueScale * sin((300 + waveLengthVariator * sin(tick * waveLengthVariationSpeed))*animDist));
	prePixel.a = prePixel.a * (1);

    gl_FragColor = prePixel;
}