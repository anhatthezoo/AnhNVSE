#pragma once

#include <nvse/ScriptUtils.h>
#include <algohol/algTypes.h>

typedef NVSEArrayVarInterface::Array NVSEArrayVar;
typedef NVSEArrayVarInterface::Element NVSEArrayElement;

static ParamInfo kParams_OneArray[1] = {
	{"array", kParamType_Integer, 0}
};

static ParamInfo kParams_TwoArrays[2] = {
	{"array", kParamType_Integer, 0},
	{"array", kParamType_Integer, 0}
};

static ParamInfo kParams_OneArray_OneFloat[2] = {
	{"array", kParamType_Integer, 0},
	{"float", kParamType_Float, 0}
};

static ParamInfo kParams_TwoArrays_OneFloat_OneInt[4] = {
	{"array", kParamType_Integer, 0},
	{"float", kParamType_Float, 0},
	{"int", kParamType_Integer, 0}
};

//lnk2001 moment
void V3Normalize(Vector3& v)
{
	float len = v.Magnitude();
	if (len > 0.0f)
		len = 1.0f / len;
	else
		len = 0.0f;
	v.x *= len;	v.y *= len;	v.z *= len;
} 

Vector3 V3Crossproduct(Vector3 va, Vector3 vb)
{
	Vector3 out;
	out.x = vb.y * va.z - vb.z * va.y;
	out.y = vb.z * va.x - vb.x * va.z;
	out.z = vb.x * va.y - vb.y * va.x;
	return out;
}

void Quat::normalize(void)
{
	float len = sqrtf(w * w + x * x + y * y + z * z);
	if (len > 0.0f)
		len = 1.0f / len;
	else
		len = 0.0f;
	w *= len;	x *= len;	y *= len;	z *= len;
}

Quat fromAxisAngle(Vector3 axis, float angle)
{
	V3Normalize(axis);
	angle /= 2 * 57.2957795131;
	float s = sinf(angle);
	return Quat(cosf(angle),
		axis.x * s,
		axis.y * s,
		axis.z * s);
}

float QDotproduct(Quat q1, Quat q2)
{
	return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
}

Quat nlerp(Quat q1, Quat q2, float t)
{
	float cosHalfTheta = QDotproduct(q1, q2);
	if (cosHalfTheta < 0)
	{
		q1.w = -q1.w;
		q1.x = -q1.x;
		q1.y = -q1.y;
		q1.z = -q1.z;
	}

	Quat out = q1 + (q2 - q1) * t;
	out.normalize();
	return out;
}

Quat slerp(Quat q1, Quat q2, float t)
{
	q1.normalize();
	q2.normalize();
	float cosHalfTheta = QDotproduct(q1, q2);

	if (fabs(cosHalfTheta) >= 1.0f)
		return q1;

	if (cosHalfTheta < 0)
	{
		q1.w = -q1.w;
		q1.x = -q1.x;
		q1.y = -q1.y;
		q1.z = -q1.z;
	}

	float halfTheta = acosf(cosHalfTheta);
	float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

	if (fabs(sinHalfTheta) < 0.001f)
		return q1 * 0.5f + q2 * 0.5f;

	float ratioA = sinf((1.0f - t) * halfTheta) / sinHalfTheta;
	float ratioB = sinf(t * halfTheta) / sinHalfTheta;
	return q1 * ratioA + q2 * ratioB;
}

float VDotproduct(Vector3 v1, Vector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
//snig

DEFINE_COMMAND_PLUGIN(V3Normalize_Alt, "", 0, 1, kParams_OneArray);
DEFINE_COMMAND_PLUGIN(V3Crossproduct_Alt, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(QMultQuatQuat_Alt, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(QMultQuatVector3_Alt, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(QNormalize_Alt, "", 0, 1, kParams_OneArray);
DEFINE_COMMAND_PLUGIN(QFromAxisAngle_Alt, "", 0, 2, kParams_OneArray_OneFloat);
DEFINE_COMMAND_PLUGIN(QInterpolate_Alt, "", 0, 4, kParams_TwoArrays_OneFloat_OneInt);
DEFINE_COMMAND_PLUGIN(V3Dotproduct, "", 0, 2, kParams_TwoArrays);

#if RUNTIME
bool Cmd_V3Normalize_Alt_Execute(COMMAND_ARGS){
	*result = 0;
	UInt32 arrID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &arrID)) {
		NVSEArrayVar* srcArr = g_arrInterface->LookupArrayByID(arrID);
		UInt32 srcArrSize = g_arrInterface->GetArraySize(srcArr);
		if (srcArr && (srcArrSize == 3)) {
			Vector3 v;
			NVSEArrayElement* elements = new NVSEArrayElement[srcArrSize];
			g_arrInterface->GetElements(srcArr, elements, NULL);
			v.x = elements[0].Number();	  v.y = elements[1].Number();	v.z = elements[2].Number();
			V3Normalize(v);
			NVSEArrayElement* newElements = new NVSEArrayElement[srcArrSize];
			newElements[0] = v.x;	newElements[1] = v.y;	newElements[2] = v.z;
			NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElements, srcArrSize, scriptObj);
			g_arrInterface->AssignCommandResult(newArr, result);
		}
		return true;
	}
	return true;
}

bool Cmd_V3Crossproduct_Alt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID1, srcID2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcID1, &srcID2)) {
		NVSEArrayVar* srcArr1 = g_arrInterface->LookupArrayByID(srcID1);
		NVSEArrayVar* srcArr2 = g_arrInterface->LookupArrayByID(srcID2);
		UInt32 size1 = g_arrInterface->GetArraySize(srcArr1);
		UInt32 size2 = g_arrInterface->GetArraySize(srcArr2);
		if (srcArr1 && srcArr2 && (size1 == 3) && (size2 == 3)) {
			Vector3 v1, v2;
			NVSEArrayElement* elements = new NVSEArrayElement[size1];
			g_arrInterface->GetElements(srcArr1, elements, NULL);
			v1.x = elements[0].Number();	  v1.y = elements[1].Number();	v1.z = elements[2].Number();
			g_arrInterface->GetElements(srcArr2, elements, NULL);
			v2.x = elements[0].Number();	  v2.y = elements[1].Number();	v2.z = elements[2].Number();
			Vector3 out = V3Crossproduct(v1, v2);
			NVSEArrayElement* outElements = new NVSEArrayElement[size1];
			outElements[0] = out.x;	outElements[1] = out.y;	outElements[2] = out.z;
			NVSEArrayVar* outArr = g_arrInterface->CreateArray(outElements, size1, scriptObj);
			g_arrInterface->AssignCommandResult(outArr, result);
		}
		return true;
	}
	return true;
}

bool Cmd_QMultQuatQuat_Alt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID1, srcID2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcID1, &srcID2)) {
		NVSEArrayVar* srcArr1 = g_arrInterface->LookupArrayByID(srcID1);
		NVSEArrayVar* srcArr2 = g_arrInterface->LookupArrayByID(srcID2);
		UInt32 size1 = g_arrInterface->GetArraySize(srcArr1);
		UInt32 size2 = g_arrInterface->GetArraySize(srcArr2);
		if (srcArr1 && srcArr2 && (size1 == 4) && (size2 == 4)) {
			Quat q1, q2;
			NVSEArrayElement* elements = new NVSEArrayElement[size1];
			g_arrInterface->GetElements(srcArr1, elements, NULL);
			q1.w = elements[0].Number();	q1.x = elements[0].Number();	q1.y = elements[0].Number();	q1.z = elements[0].Number();
			g_arrInterface->GetElements(srcArr2, elements, NULL);
			q2.w = elements[0].Number();	q2.x = elements[0].Number();	q2.y = elements[0].Number();	q2.z = elements[0].Number();
			Quat out = q1 * q2;
			NVSEArrayElement* outElements = new NVSEArrayElement[size1];
			outElements[0] = out.w;	outElements[1] = out.x;	outElements[2] = out.y; outElements[3] = out.z;
			NVSEArrayVar* outArr = g_arrInterface->CreateArray(outElements, size1, scriptObj);
			g_arrInterface->AssignCommandResult(outArr, result);
		}
		return true;
	}
	return true;
}

bool Cmd_QMultQuatVector3_Alt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID1, srcID2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcID1, &srcID2)) {
		NVSEArrayVar* srcArr1 = g_arrInterface->LookupArrayByID(srcID1);
		NVSEArrayVar* srcArr2 = g_arrInterface->LookupArrayByID(srcID2);
		UInt32 size1 = g_arrInterface->GetArraySize(srcArr1);
		UInt32 size2 = g_arrInterface->GetArraySize(srcArr2);
		if (srcArr1 && srcArr2 && (size1 == 4) && (size2 == 3)) {
			Quat q; Vector3 v;
			NVSEArrayElement* elements = new NVSEArrayElement[size1];
			g_arrInterface->GetElements(srcArr1, elements, NULL);
			q.w = elements[0].Number();	q.x = elements[1].Number();	q.y = elements[2].Number();	q.z = elements[3].Number();
			g_arrInterface->GetElements(srcArr2, elements, NULL);
			v.x = elements[0].Number();	v.y = elements[1].Number();	v.z = elements[2].Number();
			Vector3 out = q * v;
			NVSEArrayElement* outElements = new NVSEArrayElement[size1];
			outElements[0] = out.x;	outElements[1] = out.y; outElements[2] = out.z;
			NVSEArrayVar* outArr = g_arrInterface->CreateArray(outElements, size1, scriptObj);
			g_arrInterface->AssignCommandResult(outArr, result);
		}
		return true;
	}
	return true;
}

bool Cmd_QNormalize_Alt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcID)) {
		NVSEArrayVar* srcArr = g_arrInterface->LookupArrayByID(srcID);
		UInt32 size = g_arrInterface->GetArraySize(srcArr);
		if (srcArr && (size == 4)) {
			Quat q;
			NVSEArrayElement* elements = new NVSEArrayElement[size];
			g_arrInterface->GetElements(srcArr, elements, NULL);
			q.w = elements[0].Number();	q.x = elements[1].Number();	q.y = elements[2].Number();	q.z = elements[3].Number();
			q.normalize();
			NVSEArrayElement* outElements = new NVSEArrayElement[size];
			outElements[0] = q.w;	outElements[1] = q.x; outElements[2] = q.y; outElements[3] = q.z;
			NVSEArrayVar* outArr = g_arrInterface->CreateArray(outElements, size, scriptObj);
			g_arrInterface->AssignCommandResult(outArr, result);
		}
		return true;
	}
	return true;
}

bool Cmd_QFromAxisAngle_Alt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID;
	float angle;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcID, &angle)) {
		NVSEArrayVar* srcArr = g_arrInterface->LookupArrayByID(srcID);
		UInt32 size = g_arrInterface->GetArraySize(srcArr);
		if (srcArr && (size == 4)) {
			Vector3 axis;
			NVSEArrayElement* elements = new NVSEArrayElement[size];
			g_arrInterface->GetElements(srcArr, elements, NULL);
			axis.x = elements[0].Number();	axis.y = elements[1].Number();	axis.z = elements[2].Number();	
			Quat out = fromAxisAngle(axis, angle);
			NVSEArrayElement* outElements = new NVSEArrayElement[size];
			outElements[0] = out.w;	outElements[1] = out.x; outElements[2] = out.y; outElements[3] = out.z;
			NVSEArrayVar* outArr = g_arrInterface->CreateArray(outElements, size, scriptObj);
			g_arrInterface->AssignCommandResult(outArr, result);
		}
		return true;
	}
	return true;
}

bool Cmd_QInterpolate_Alt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID1, srcID2;
	float t;
	int slerpFlag;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcID1, &srcID2, &t, &slerpFlag)) {
		NVSEArrayVar* srcArr1 = g_arrInterface->LookupArrayByID(srcID1);
		UInt32 size1 = g_arrInterface->GetArraySize(srcArr1);
		NVSEArrayVar* srcArr2 = g_arrInterface->LookupArrayByID(srcID2);
		UInt32 size2 = g_arrInterface->GetArraySize(srcArr2);
		if (srcArr1 && srcArr2 && (size1 == 4) && (size2 == 4)) {
			Quat q1, q2;
			NVSEArrayElement* elements = new NVSEArrayElement[size1];
			g_arrInterface->GetElements(srcArr1, elements, NULL);
			q1.w = elements[0].Number();	q1.x = elements[1].Number();	q1.y = elements[2].Number();	q1.z = elements[3].Number();
			g_arrInterface->GetElements(srcArr2, elements, NULL);
			q2.w = elements[0].Number();	q2.x = elements[1].Number();	q2.y = elements[2].Number();	q2.z = elements[3].Number();

			Quat out;
			if (!slerpFlag)
				out = nlerp(q1, q2, t);
			else
				out = slerp(q1, q2, t);

			NVSEArrayElement* outElements = new NVSEArrayElement[size1];
			outElements[0] = out.w;	outElements[1] = out.x; outElements[2] = out.y; outElements[3] = out.z;
			NVSEArrayVar* outArr = g_arrInterface->CreateArray(outElements, size1, scriptObj);
			g_arrInterface->AssignCommandResult(outArr, result);
		}
		return true;
	}
	return true;
}

bool Cmd_V3Dotproduct_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID1, srcID2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcID1, &srcID2)) {
		NVSEArrayVar* srcArr1 = g_arrInterface->LookupArrayByID(srcID1);
		UInt32 size1 = g_arrInterface->GetArraySize(srcArr1);
		NVSEArrayVar* srcArr2 = g_arrInterface->LookupArrayByID(srcID2);
		UInt32 size2 = g_arrInterface->GetArraySize(srcArr2);
		if (srcArr1 && srcArr2 && (size1 == 3) && (size2 == 3)) {
			Vector3 v1, v2;
			NVSEArrayElement* elements = new NVSEArrayElement[size1];
			g_arrInterface->GetElements(srcArr1, elements, NULL);
			v1.x = elements[0].Number();	v1.y = elements[1].Number();	v1.z = elements[2].Number();	
			g_arrInterface->GetElements(srcArr2, elements, NULL);
			v2.x = elements[0].Number();	v2.y = elements[1].Number();	v2.z = elements[2].Number();	
			*result = VDotproduct(v1, v2);
		}
		return true;
	}
	return true;
}
#endif