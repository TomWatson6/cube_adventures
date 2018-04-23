# version 150 core

//uniform sampler2D water;
//uniform sampler2D cobblestone;
//uniform float current;
uniform float currentMap;
uniform float tileLength;
uniform float dimensions;
uniform float tileInfo[1000];
//uniform float tileInfo[dimensions * dimensions];


in Vertex{
	vec4 colour;
	vec2 texCoord;
	vec3 position;
} IN;

out vec4 gl_FragColor;

void main(void) {

	/*vec2 cobblestoneOffset = IN.texCoord;
	cobblestoneOffset.x = cobblestoneOffset.x - current;*/

	/*vec4 waterText = texture (water, IN.texCoord);
	vec4 cobblestoneText = texture (cobblestone, cobblestoneOffset);*/
	vec4 land = IN.colour;
	vec4 water = IN.colour;

	vec4 mapColour = IN.colour;

	vec3 pos = IN.position;

	float x = pos.x / 160;
	float z = pos.z / 160;

	int a = int(z / tileLength);
	a = int(a * dimensions);
	int currentTile = int(x / tileLength);
	currentTile = currentTile + a;

	bool b = false;

	int mapMult = int(currentMap * dimensions * dimensions);

	//if(tileInfo[/*mapMult + */currentTile] == 1) {
	////if(pos.y < -20) {
	//	//if(pos.x - 1 >= 0) {
	//	//	int adjacentTile = (int((pos.x - 1) / tileLength)) + (int(int(pos.y / tileLength) * dimensions));
	//	//	if(tileInfo[adjacentTile * 2] != tileInfo[currentTile * 2]) {
	//	//		gl_FragColor = cobblestoneText;
	//	//	}
	//	//}
	//	//else if(pos.x + 1 <= dimensions * tileLength) {
	//	//	int adjacentTile = (int((pos.x + 1) / tileLength)) + (int(int(pos.y / tileLength) * dimensions));
	//	//	if(tileInfo[adjacentTile * 2] != tileInfo[currentTile * 2]) {
	//	//		gl_FragColor = cobblestoneText;
	//	//	}
	//	//}
	//	//else if(pos.y - 1 >= 0) {
	//	//	int adjacentTile = int(pos.x / tileLength) + int(int((pos.y - 1) / tileLength) * dimensions);
	//	//	if(tileInfo[adjacentTile * 2] != tileInfo[currentTile * 2]) {
	//	//		gl_FragColor = cobblestoneText;
	//	//	}
	//	//}
	//	//else if(pos.y + 1 <= dimensions * tileLength) {
	//	//	int adjacentTile = int(pos.x / tileLength) + int(int((pos.y + 1) / tileLength) * dimensions);
	//	//	if(tileInfo[adjacentTile * 2] != tileInfo[currentTile * 2]) {
	//	//		gl_FragColor = cobblestoneText;
	//	//	}
	//	//}
	//	//else {
	//		gl_FragColor = water;
	//	//}
	//}
	//else {
	//	gl_FragColor = land;
	//}

	gl_FragColor = mapColour;

	//if(pos.y > 0.0) {
	//	gl_FragColor = cobblestoneText;
		//gl_FragColor = orange;
	//}
	//else {
	//	gl_FragColor = waterText;
	//}

	//gl_FragColor = orange;

	//gl_FragColor = texture (diffuseTex, IN.texCoord);
	
}