#pragma once

#include <string>

static ParamInfo kParams_OneString_OneInt_OneString[3] =
{
	{	"string",	kParamType_String,	0	},
	{	"max_length",	kParamType_Integer,	0	},
	{	"string",	kParamType_String,	0	},
};

DEFINE_COMMAND_PLUGIN(ScancodeToChar, "Converts a scancode int to string", 0, 1, kParams_OneInt)
DEFINE_COMMAND_PLUGIN(Sv_PadStart, "Pad a character to the start of a string", 0, 3, kParams_OneString_OneInt_OneString)

#if RUNTIME
bool Cmd_Sv_PadStart_Execute(COMMAND_ARGS) {
	*result = 0;
	int targetLen;
	char srcString1[0x80], srcString2[0x80];
	char newChar[0x80];

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcString1, &targetLen, &srcString2)) {
		std::string src1 = std::string(srcString1);
		std::string src2 = std::string(srcString2);
		
		for (int i = src1.length(); i < targetLen; i++) {
			src1.append(src2);
		}
		strcpy(newChar, src1.c_str());
		g_stringvarInterface->Assign(PASS_COMMAND_ARGS, newChar);
		return true;
	}

	return true;
} 

bool Cmd_ScancodeToChar_Execute(COMMAND_ARGS) {
	*result = 0;
	int key;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &key)) {
		const char* tempChar;                                               //dirty way to do this but lol
		std::string tempString;                      
		tempString = std::to_string(key);
		for (int i = 0; i < (sizeof(ScanCodes) / sizeof(*ScanCodes)); i++) {	
			
			if (strcmp(tempString.c_str(), ScanCodes[i][1]) == 0) {
				tempChar = ScanCodes[i][0];
			}
		}
		g_stringvarInterface->Assign(PASS_COMMAND_ARGS, tempChar);
		return true;
	}
	return true;
}
#endif

