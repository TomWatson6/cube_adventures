# version 430 core

uniform vec3 cameraPos;
uniform vec4 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;
uniform mat4 modelMatrix;

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vertex{
	vec4 colour;
	vec2 texCoord;
	vec3 position;
	vec3 worldPos;
} IN[];

out Vertex{
	vec4 colour;
	vec2 texCoord;
	vec3 position;
	vec3 worldPos;
	vec3 normal;
} OUT;

void main() {

	vec3 n = cross(IN[1].position - IN[0].position, IN[2].position - IN[0].position);
	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
	
	for (int i = 0; i < gl_in.length(); ++i) {
		gl_Position = gl_in[i].gl_Position;
		
		//OUT.normal = normal;
		OUT.normal = -normalize(normalMatrix * normalize(n)); 
		OUT.colour = IN[i].colour;
		OUT.texCoord = IN[i].texCoord;
		OUT.position = IN[i].position;
		OUT.worldPos = IN[i].worldPos;
		EmitVertex();

	}
	EndPrimitive();
	
}