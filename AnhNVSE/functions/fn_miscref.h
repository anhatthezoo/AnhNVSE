#pragma once

ParamInfo kParams_OneString_ThreeFloats_OneOptionalInt[] =
{
	{"String", kParamType_String, 0},
	{"Float", kParamType_Float, 0},
	{"Float", kParamType_Float, 0},
	{"Float", kParamType_Float, 0},
	{"Integer", kParamType_Integer, 1}
};

DEFINE_COMMAND_PLUGIN(TestNifFunc, "", 1, 5, kParams_OneString_ThreeFloats_OneOptionalInt);

bool Cmd_TestNifFunc_Execute(COMMAND_ARGS) {
	char blockName[0x40];
	NiVector3 transltn;
	UInt32 pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &transltn.x, &transltn.y, &transltn.z, &pcNode))
	{
		NiAVObject* niBlock = GetNifBlock(thisObj, pcNode, blockName);
		if (niBlock)
		{
			Console_Print(std::to_string(niBlock->m_transformWorld.translate.x).c_str());
			Console_Print(std::to_string(niBlock->m_transformWorld.translate.y).c_str());
			Console_Print(std::to_string(niBlock->m_transformWorld.translate.z).c_str());
			niBlock->LocalTranslate() = transltn;
			niBlock->Update();
		}
	}
	return true;
}