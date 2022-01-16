#pragma once

#include <nvse/ScriptUtils.h>

DEFINE_COMMAND_PLUGIN(Ar_Min, "", 0, 1, kParams_OneArray);
DEFINE_COMMAND_PLUGIN(Ar_Max, "", 0, 1, kParams_OneArray);
DEFINE_COMMAND_PLUGIN(Ar_RangeMath, "", 0, 1, kParams_OneArray);

#if RUNTIME
bool Cmd_Ar_Min_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &arrID)) {
		std::vector<float> tempArr;
		NVSEArrayVar* arr = g_arrInterface->LookupArrayByID(arrID);
		UInt32 size = g_arrInterface->GetArraySize(arr);
		NVSEArrayElement* el = new NVSEArrayElement[size];
		g_arrInterface->GetElements(arr, el, NULL);
		for (int i = 0; i < size; i++) {
			if (el[i].type == NVSEArrayVarInterface::kType_Numeric)
				tempArr.push_back(el[i].Number());
		}
		std::vector<float>::iterator min = std::min_element(tempArr.begin(), tempArr.end());
		*result = tempArr[std::distance(tempArr.begin(), min)];
	}
	return true;
}

bool Cmd_Ar_Max_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &arrID)) {
		std::vector<float> tempArr;
		NVSEArrayVar* arr = g_arrInterface->LookupArrayByID(arrID);
		UInt32 size = g_arrInterface->GetArraySize(arr);
		NVSEArrayElement* el = new NVSEArrayElement[size];
		g_arrInterface->GetElements(arr, el, NULL);
		for (int i = 0; i < size; i++) {
			if (el[i].type == NVSEArrayVarInterface::kType_Numeric)
				tempArr.push_back(el[i].Number());
		}
		std::vector<float>::iterator max = std::max_element(tempArr.begin(), tempArr.end());
		*result = tempArr[std::distance(tempArr.begin(), max)];
	}
	return true;
}

bool Cmd_Ar_RangeMath_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &arrID)) {
		std::vector<float> tempArr;
		NVSEArrayVar* arr = g_arrInterface->LookupArrayByID(arrID);
		UInt32 size = g_arrInterface->GetArraySize(arr);
		NVSEArrayElement* el = new NVSEArrayElement[size];
		g_arrInterface->GetElements(arr, el, NULL);
		for (int i = 0; i < size; i++) {
			if (el[i].type == NVSEArrayVarInterface::kType_Numeric)
				tempArr.push_back(el[i].Number());
		}
		std::vector<float>::iterator iter1 = std::max_element(tempArr.begin(), tempArr.end());
		std::vector<float>::iterator iter2 = std::min_element(tempArr.begin(), tempArr.end());
		float max = tempArr[std::distance(tempArr.begin(), iter1)],
			  min = tempArr[std::distance(tempArr.begin(), iter2)];
		*result = (max - min);
	}
	return true;
}
#endif
