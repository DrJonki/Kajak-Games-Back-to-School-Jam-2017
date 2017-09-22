#version 130

uniform sampler2D texture;
uniform float tick;

void main()
{
	/* try:
		float positionalWaveLengthX = 0.055;
		float positionalWaveLengthY = 0.01;
	*/
	float positionalWaveLengthX = 0.03;
	float positionalWaveLengthY = 0.22;

	float positionalWaveHeightX = 0.02;
	float positionalWaveHeightY = 0.02;

	float standingWaveHeightX = 0.04;
	float standingWaveHeightY = 0.06;

	float standingXFreq = 3.5;
	float standingYFreq = 1;

	float standingPartialY = standingWaveHeightY * sin(tick * standingYFreq);
	float standingPartialX = standingWaveHeightX * sin(tick * standingXFreq);

	float positionalCompressionX = 0.05 * sin(13 * gl_TexCoord[0].x);
	float positionalCompressionY = 0.03 * sin(11 * gl_TexCoord[0].y);

	float positionalPartialX = positionalWaveHeightY * sin(gl_TexCoord[0].y / positionalWaveLengthY) + positionalCompressionX;
	float positionalPartialY = positionalWaveHeightX * sin(gl_TexCoord[0].x / positionalWaveLengthX) + positionalCompressionY;

	float yWave = standingPartialY + positionalPartialY;
	float xWave = standingPartialX + positionalPartialX;

	 vec4 pixel = texture2D(texture, gl_TexCoord[0].xy + vec2(xWave, yWave));

    // multiply it by the color
    gl_FragColor = pixel;
}