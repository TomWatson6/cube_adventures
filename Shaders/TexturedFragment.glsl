# version 430 core

//uniform sampler2D water;
//uniform sampler2D cobblestone;
//uniform float current;
uniform float currentMap;
uniform float tileLength;
uniform float dimensions;
uniform float tileInfo[1000];
uniform vec3 cameraPos;
uniform vec4 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;
//uniform float tileInfo[dimensions * dimensions];

in Vertex{
	vec4 colour;
	vec2 texCoord;
	vec3 position;
	vec3 worldPos;
	vec3 normal;
} IN;

out vec4 gl_FragColor;

void main(void) {

	vec3 incident = normalize(lightPos - IN.worldPos);
	float lambert = max(0.0, dot(incident, IN.normal));

	float dist = length(lightPos - IN.worldPos);
	float atten = 1.0 - clamp(dist / lightRadius, 0.0, 1.0);

	vec3 viewDir = normalize(cameraPos - IN.worldPos);
	vec3 halfDir = normalize(incident + viewDir);

	float rFactor = max(0.0, dot(halfDir, IN.normal));
	float sFactor = pow(rFactor, 50.0);

	vec3 colour = (IN.colour.rgb * lightColour.rgb);
	colour += (lightColour.rgb * sFactor) * 0.33;
	gl_FragColor = vec4(colour * atten * lambert, IN.colour.a);
	gl_FragColor.rgb += (IN.colour.rgb * lightColour.rgb) * 0.1;

	//gl_FragColor = vec4(colour, 1);

	//gl_FragColor = vec4(1, 1, 0, 1);
	//gl_FragColor = IN.colour;
	
}