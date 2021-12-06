#pragma once

#include <math.h>

static ParamInfo kParams_OneDouble[] = {
	{	"Double", kParamType_Double, 0	}
};

Vector3 V3Lerp(Vector3 vecA, Vector3 vecB, float t) {
	vecB.x *= t;
	vecB.y *= t;
	vecB.z *= t;

	vecA.x *= (1.f - t);
	vecA.y *= (1.f - t);
	vecA.z *= (1.f - t);

	return vecA + vecB;
};

DEFINE_COMMAND_PLUGIN(DegToRad, "Converts degrees to radians", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(RadToDeg, "Converts radians to degrees", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(GetAngleQuadrant, "Returns the quadrant of an angle (radian)", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(Sinh, "Hyperbolic sin of angle", 0, 1, kParams_OneDouble)
DEFINE_COMMAND_PLUGIN(Cosh, "Hyperbolic cos of angle", 0, 1, kParams_OneDouble)
DEFINE_COMMAND_PLUGIN(Tanh, "Hyperbolic tan of angle", 0, 1, kParams_OneDouble)
DEFINE_COMMAND_PLUGIN(V3Lerp, "", 0, 3, kParams_TwoArrays_OneFloat)
DEFINE_COMMAND_PLUGIN(GenerateBezierPoints, "", 0, 4, kParams_ThreeArrays_OneFloat);

#if RUNTIME
bool Cmd_RadToDeg_Execute(COMMAND_ARGS) {
	float rad;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &rad)) {
		*result = (rad * 57.2957795131);
	}
	return true;
}

bool Cmd_DegToRad_Execute(COMMAND_ARGS) {
	float deg;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &deg)) {
		*result = (deg * 0.0174532925);
	}
	return true;
}

bool Cmd_GetAngleQuadrant_Execute(COMMAND_ARGS) {
	float angle;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &angle)) {
		int tempAngle = (int)ceil(angle);
		tempAngle %= 360;
		if (tempAngle < 0) tempAngle += 360;
		*result = (tempAngle / 90) % 4 + 1;
		return true;
	}
	return true;
}

bool Cmd_Sinh_Execute(COMMAND_ARGS) {
	double angle;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &angle)) {
		*result = sinh(angle);
		return true;
	}
	return true;
}

bool Cmd_Cosh_Execute(COMMAND_ARGS) {
	double angle;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &angle)) {
		*result = cosh(angle);
		return true;
	}
	return true;
}

bool Cmd_Tanh_Execute(COMMAND_ARGS) {
	double angle;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &angle)) {
		*result = tanh(angle);
		return true;
	}
	return true;
}

bool Cmd_GenerateBezierPoints_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID1, arrID2, arrID3;
	float t;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &arrID1, &arrID2, &arrID3, &t)) {
		NVSEArrayVar* srcArr1 = g_arrInterface->LookupArrayByID(arrID1);
		NVSEArrayVar* srcArr2 = g_arrInterface->LookupArrayByID(arrID2);
		NVSEArrayVar* srcArr3 = g_arrInterface->LookupArrayByID(arrID3);
		Vector3 v1, v2, v3, newVec;
		NVSEArrayElement* elements = new NVSEArrayElement[3];
		g_arrInterface->GetElements(srcArr1, elements, NULL);
		v1.x = elements[0].Number();
		v1.y = elements[1].Number();
		v1.z = elements[2].Number();

		g_arrInterface->GetElements(srcArr2, elements, NULL);
		v2.x = elements[0].Number();
		v2.y = elements[1].Number();
		v2.z = elements[2].Number();

		g_arrInterface->GetElements(srcArr3, elements, NULL);
		v3.x = elements[0].Number();
		v3.y = elements[1].Number();
		v3.z = elements[2].Number();

		newVec = V3Lerp((V3Lerp(v1, v2, t)), (V3Lerp(v2, v3, t)), t);
		NVSEArrayElement* newElements = new NVSEArrayElement[3];
		newElements[0] = newVec.x;
		newElements[1] = newVec.y;
		newElements[2] = newVec.z;
		NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElements, 3, scriptObj);
		g_arrInterface->AssignCommandResult(newArr, result);
		
		delete[] elements;
	}
	return true;
} 

bool Cmd_V3Lerp_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID1, arrID2;
	float t;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &arrID1, &arrID2, &t)) {
		NVSEArrayVar* srcArr1 = g_arrInterface->LookupArrayByID(arrID1);
		NVSEArrayVar* srcArr2 = g_arrInterface->LookupArrayByID(arrID2);
		UInt32 size1 = g_arrInterface->GetArraySize(srcArr1);
		UInt32 size2 = g_arrInterface->GetArraySize(srcArr2);

		Vector3 v1, v2;
		NVSEArrayElement* elements = new NVSEArrayElement[3];
		g_arrInterface->GetElements(srcArr1, elements, NULL);
		v1.x = elements[0].Number();
		v1.y = elements[1].Number();
		v1.z = elements[2].Number();

		g_arrInterface->GetElements(srcArr2, elements, NULL);
		v2.x = elements[0].Number();
		v2.y = elements[1].Number();
		v2.z = elements[2].Number();
		Vector3 lerpVec = V3Lerp(v1, v2, t);

		NVSEArrayElement* newElements = new NVSEArrayElement[3];
		newElements[0] = lerpVec.x;
		newElements[1] = lerpVec.y;
		newElements[2] = lerpVec.z;
		NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElements, 3, scriptObj);
		g_arrInterface->AssignCommandResult(newArr, result);

		delete[] elements;
	}
	return true;
}

#endif 


