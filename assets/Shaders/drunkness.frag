#version 130

uniform sampler2D texture;
uniform float tick;
uniform struct Drunkness
{
	vec2 positionalWaveLength;
	vec2 positionalWaveHeight;
	vec2 standingWaveHeight;
	vec2 standingFreq;
	vec2 positionalCompressionRates;
	float horizontalKnock;
	
} drunkness;

void main()
{

	vec2 standingPartial = vec2(
		drunkness.standingWaveHeight.x * sin(tick * drunkness.standingFreq.x) + drunkness.horizontalKnock * sin(12*gl_TexCoord[0].y),
		drunkness.standingWaveHeight.y * sin(tick * drunkness.standingFreq.y) + drunkness.horizontalKnock * sin(12*gl_TexCoord[0].x)
	);

	vec2 positionalCompression = vec2(
		drunkness.positionalCompressionRates.x * sin(13 * gl_TexCoord[0].x),
		drunkness.positionalCompressionRates.y * sin(11 * gl_TexCoord[0].y)
	);

	vec2 positionalPartial = vec2(
		drunkness.positionalWaveHeight.y * sin(gl_TexCoord[0].y / drunkness.positionalWaveLength.y) + positionalCompression.x,
		drunkness.positionalWaveHeight.x * sin(gl_TexCoord[0].x / drunkness.positionalWaveLength.x) + positionalCompression.y
	);

	vec2 wave = standingPartial + positionalPartial;
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy + wave);

    // multiply it by the color
    gl_FragColor = pixel;
}