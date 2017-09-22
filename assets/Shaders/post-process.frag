#version 130

uniform sampler2D texture;
// uniform float tick;

void main()
{
/*
	int waveCountX = 4;
	int waveCountY = 3;

	int waveHeightX = 100;
	int waveHeightY = 60;

	// standing wave parameters
	int standingWaveLoopTime = 100;
	float standingWaveHeight = Math.sin();

	int screenWidth = 1920;
	int	screenHeight = 1080;

	float xDifferential = gl_TexCoord[0].x + waveHeightX * Math.sin(waveCount * gl_TexCoord[0].x / screenWidth);
	float yDifferential = gl_TexCoord[0].y + waveHeightY * Math.sin(waveCount * gl_TexCoord[0].y / screenHeight);

	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy + vec2(xDifferential,yDifferential));
	*/

    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    gl_FragColor = pixel;
}