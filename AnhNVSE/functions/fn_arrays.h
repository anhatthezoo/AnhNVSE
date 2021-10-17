#pragma once

#include <nvse/ScriptUtils.h>
#include <algohol/algMath.h>
#include <string>

typedef NVSEArrayVarInterface::Array NVSEArrayVar;
typedef NVSEArrayVarInterface::Element NVSEArrayElement;

static ParamInfo kParams_OneArray[1] = {
	{"array", kParamType_Array, 0}
};

DEFINE_COMMAND_PLUGIN(V3_Normalized_Alt, "alt for a function", 0, 1, kParams_OneArray);

#if RUNTIME
bool Cmd_V3_Normalized_Alt_Execute(COMMAND_ARGS){
	*result = 0;
	UInt32 arrID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &arrID)) {
		Console_Print("hello");
		NVSEArrayVar* srcArr = g_arrInterface->LookupArrayByID(arrID);
		UInt32 srcArrSize = g_arrInterface->GetArraySize(srcArr);
		if (srcArr && (srcArrSize == 3)) {
			Vector3 v;
			//NVSEArrayElement* elements = new NVSEArrayElement[srcArrSize];
			NVSEArrayElement element;
			g_arrInterface->GetElement(srcArr, 2, element);
			float num = element.Number();
			const char* tempChar;
			std::string tempString;
			tempString = std::to_string(num);
			tempChar = tempString.c_str();
			Console_Print(tempChar);
			return true;
		}
		return true;
	}
	return true;
}
#endif