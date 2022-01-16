#pragma once

#include <string>

DEFINE_COMMAND_PLUGIN(ScancodeToChar, "Converts a scancode int to string", 0, 1, kParams_OneInt)
DEFINE_COMMAND_PLUGIN(Sv_PadStart, "Pad a character to the start of a string", 0, 3, kParams_OneString_OneInt_OneString)
DEFINE_COMMAND_PLUGIN(Sv_PadEnd, "Pad a character to the end of a string", 0, 3, kParams_OneString_OneInt_OneString)
DEFINE_COMMAND_PLUGIN(Sv_Capitalize, "", 0, 1, kParams_OneString);

#if RUNTIME
bool Cmd_Sv_PadStart_Execute(COMMAND_ARGS) {
	*result = 0;
	int targetLen;
	char srcString1[0x80], srcString2[0x80];
	char newChar[0x80];

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcString1, &targetLen, &srcString2)) {
		std::string src1 = std::string(srcString1);
		std::string src2 = std::string(srcString2);
		std::string tempStr;
		for (int i = src1.length(); i < targetLen; i++) {
			tempStr.insert(0, src2);
		}
		src1.insert(0, tempStr.substr(0, (targetLen - src1.length())));
		strcpy(newChar, src1.c_str());
		g_stringvarInterface->Assign(PASS_COMMAND_ARGS, newChar);
	
	}

	return true;
} 

bool Cmd_Sv_PadEnd_Execute(COMMAND_ARGS) {
	*result = 0;
	int targetLen;
	char srcString1[0x80], srcString2[0x80];
	char newChar[0x80];

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcString1, &targetLen, &srcString2)) {
		std::string src1 = std::string(srcString1);
		std::string src2 = std::string(srcString2);
		std::string tempStr;
		for (int i = src1.length(); i < targetLen; i++) {
			tempStr.append(src2);
		}
		src1.append(tempStr.substr(0, (targetLen - src1.length())));
		strcpy(newChar, src1.c_str());
		g_stringvarInterface->Assign(PASS_COMMAND_ARGS, newChar);
	
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
	
	}
	return true;
}

bool Cmd_Sv_Capitalize_Execute(COMMAND_ARGS) {
	*result = 0;
	char srcString[0x80];

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcString)) {
		std::string src1 = std::string(srcString);
		src1[0] = std::toupper(src1[0]);
		g_stringvarInterface->Assign(PASS_COMMAND_ARGS, src1.c_str());
	}

	return true;
}

#endif

