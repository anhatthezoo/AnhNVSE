#pragma once

static ParamInfo kParams_OneString_OneInt_OneString[3] =
{
	{	"string",	kParamType_String,	0	},
	{	"max_length",	kParamType_Integer,	0	},
	{	"string",	kParamType_String,	0	},
};

DEFINE_COMMAND_PLUGIN(ScancodeToChar, "Converts a scancode int to string", 0, 1, kParams_OneInt)
//DEFINE_COMMAND_PLUGIN(Sv_PadStart, "Pad a character to the start of a string", 0, 3, kParams_OneString_OneInt_OneString)

#if RUNTIME
/*bool Cmd_Sv_PadStart_Execute(COMMAND_ARGS) {
	
	return true;
} */

bool Cmd_ScancodeToChar_Execute(COMMAND_ARGS) {
	int key;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &key)) {
		g_stringvarInterface->Assign(PASS_COMMAND_ARGS, ScanCodes[key]);
		return true;
	}
	return true;
}
#endif

