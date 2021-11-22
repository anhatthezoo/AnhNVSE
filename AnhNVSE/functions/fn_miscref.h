#pragma once

static ParamInfo kParams_OneString_OneInt_ThreeFloats[5] =
{
	{	"string",	kParamType_String,	0	},
	{	"index",	kParamType_Integer,	0	},
	{	"float",	kParamType_Float,	0	},
	{	"float",	kParamType_Float,	0	},
	{	"float",	kParamType_Float,	0	}
};
DEFINE_COMMAND_PLUGIN(SetNifBlockVertexPosition, "lol", 1, 5, kParams_OneString_OneInt_ThreeFloats);

bool Cmd_SetNifBlockVertexPosition_Execute(COMMAND_ARGS) {
	//*result = 0;
	//char blockName[0x40];
	//int index;
	//NiVector3 translation;
	//if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &index, &translation.x, &translation.y, &translation.z)) {
		/*NiAVObject* niBlock = GetNifBlock(thisObj, 0, blockName);
		NiGeometry* niGeom = niBlock->GetNiGeometry();
		NiGeometryData* geoData = niGeom->geometryData;
		NiVector3* vertices = geoData->vertices;

		//vertices[index].x = translation.x;
		//vertices[index].y = translation.y;
		//vertices[index].z = translation.z;
		std::string temp = std::to_string(vertices[0].x);
		//Console_Print(temp.c_str());

		//niBlock->GetNiGeometry()->geometryData->vertices = vertices;
		//niBlock->Update();

		int tempInt = niBlock->m_transformLocal.scale;
		temp = std::to_string(tempInt);
		Console_Print(temp.c_str()); */
		//NiAVObject* niBlock = GetNifBlock(thisObj, 0, blockName);
		//if (niBlock) *result = niBlock->m_transformLocal.scale;
		//return true;
	//}
	//return true; */

	*result = 0;
	char blockName[0x40];
	UInt32 pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &pcNode))
	{
		NiAVObject* niBlock = GetNifBlock(thisObj, pcNode, blockName);
		
		if (niBlock) {
			Console_Print("s");
			*result = niBlock->m_transformLocal.scale;
		}
	}
	return true;
} 