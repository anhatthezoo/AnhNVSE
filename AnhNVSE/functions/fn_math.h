#pragma once

#include <math.h>
#include <algohol/algTypes.h>

Vector3 V3Lerp(Vector3 vecA, Vector3 vecB, float t) {
	vecB.x *= t;
	vecB.y *= t;
	vecB.z *= t;

	vecA.x *= (1.f - t);
	vecA.y *= (1.f - t);
	vecA.z *= (1.f - t);

	return vecA + vecB;
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

DEFINE_COMMAND_PLUGIN(V3NormalizeAlt, "", 0, 1, kParams_OneArray);
DEFINE_COMMAND_PLUGIN(V3CrossproductAlt, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(QMultQuatQuatAlt, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(QMultQuatVector3Alt, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(QNormalizeAlt, "", 0, 1, kParams_OneArray);
DEFINE_COMMAND_PLUGIN(QFromAxisAngleAlt, "", 0, 2, kParams_OneArray_OneFloat);
DEFINE_COMMAND_PLUGIN(QInterpolateAlt, "", 0, 4, kParams_TwoArrays_OneFloat_OneInt);
DEFINE_COMMAND_PLUGIN(V3Dotproduct, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(DegToRad, "Converts degrees to radians", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(RadToDeg, "Converts radians to degrees", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(GetAngleQuadrant, "Returns the quadrant of an angle (radian)", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(Sinh, "Hyperbolic sin of angle", 0, 1, kParams_OneDouble)
DEFINE_COMMAND_PLUGIN(Cosh, "Hyperbolic cos of angle", 0, 1, kParams_OneDouble)
DEFINE_COMMAND_PLUGIN(Tanh, "Hyperbolic tan of angle", 0, 1, kParams_OneDouble)
DEFINE_COMMAND_PLUGIN(V3Lerp, "", 0, 3, kParams_TwoArrays_OneFloat)
DEFINE_COMMAND_PLUGIN(GenerateBezierPoint, "", 0, 4, kParams_ThreeArrays_OneFloat);
DEFINE_COMMAND_PLUGIN(V3Mult, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(V3MultByScalar, "", 0, 2, kParams_OneArray_OneFloat);

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

bool Cmd_V3NormalizeAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &arrID)) {
		NVSEArrayVar* srcArr = g_arrInterface->LookupArrayByID(arrID);
		UInt32 srcArrSize = g_arrInterface->GetArraySize(srcArr);
		if (srcArr && (srcArrSize == 3)) {
			Vector3 v;
			NVSEArrayElement* elements = new NVSEArrayElement[srcArrSize];
			g_arrInterface->GetElements(srcArr, elements, NULL);
			v.x = elements[0].Number();
			v.y = elements[1].Number();
			v.z = elements[2].Number();

			V3Normalize(v);
			ArrayElementL newElem[3] = { v.x, v.y, v.z };
			NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, srcArrSize, scriptObj);
			g_arrInterface->AssignCommandResult(newArr, result);

			delete[] elements;
		}

	}
	return true;
}

bool Cmd_V3CrossproductAlt_Execute(COMMAND_ARGS) {
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
			v1.x = elements[0].Number();
			v1.y = elements[1].Number();
			v1.z = elements[2].Number();

			g_arrInterface->GetElements(srcArr2, elements, NULL);
			v2.x = elements[0].Number();
			v2.y = elements[1].Number();
			v2.z = elements[2].Number();

			Vector3 out = V3Crossproduct(v1, v2);
			ArrayElementL newElem[3] = { out.x, out.y, out.z };
			NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
			g_arrInterface->AssignCommandResult(newArr, result);

			delete[] elements;
		}

	}
	return true;
}

bool Cmd_QMultQuatQuatAlt_Execute(COMMAND_ARGS) {
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
			q1.w = elements[0].Number();
			q1.x = elements[0].Number();
			q1.y = elements[0].Number();
			q1.z = elements[0].Number();

			g_arrInterface->GetElements(srcArr2, elements, NULL);
			q2.w = elements[0].Number();
			q2.x = elements[0].Number();
			q2.y = elements[0].Number();
			q2.z = elements[0].Number();

			Quat out = q1 * q2;
			ArrayElementL newElem[4] = { out.w, out.x, out.y, out.z };
			NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 4, scriptObj);
			g_arrInterface->AssignCommandResult(newArr, result);

			delete[] elements;
		}

	}
	return true;
}

bool Cmd_QMultQuatVector3Alt_Execute(COMMAND_ARGS) {
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
			q.w = elements[0].Number();
			q.x = elements[1].Number();
			q.y = elements[2].Number();
			q.z = elements[3].Number();

			g_arrInterface->GetElements(srcArr2, elements, NULL);
			v.x = elements[0].Number();
			v.y = elements[1].Number();
			v.z = elements[2].Number();

			Vector3 out = q * v;
			ArrayElementL newElem[3] = { out.x, out.y, out.z };
			NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
			g_arrInterface->AssignCommandResult(newArr, result);

			delete[] elements;
		}

	}
	return true;
}

bool Cmd_QNormalizeAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &srcID)) {
		NVSEArrayVar* srcArr = g_arrInterface->LookupArrayByID(srcID);
		UInt32 size = g_arrInterface->GetArraySize(srcArr);
		if (srcArr && (size == 4)) {
			Quat q;
			NVSEArrayElement* elements = new NVSEArrayElement[size];
			g_arrInterface->GetElements(srcArr, elements, NULL);
			q.w = elements[0].Number();
			q.x = elements[1].Number();
			q.y = elements[2].Number();
			q.z = elements[3].Number();

			q.normalize();
			ArrayElementL newElem[4] = { q.w, q.x, q.y, q.z };
			NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 4, scriptObj);
			g_arrInterface->AssignCommandResult(newArr, result);

			delete[] elements;
		}

	}
	return true;
}

bool Cmd_QFromAxisAngleAlt_Execute(COMMAND_ARGS) {
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
			axis.x = elements[0].Number();
			axis.y = elements[1].Number();
			axis.z = elements[2].Number();

			Quat out = fromAxisAngle(axis, angle);
			ArrayElementL newElem[4] = { out.w, out.x, out.y, out.z };
			NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 4, scriptObj);
			g_arrInterface->AssignCommandResult(newArr, result);

			delete[] elements;
		}

	}
	return true;
}

bool Cmd_QInterpolateAlt_Execute(COMMAND_ARGS) {
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
			q1.w = elements[0].Number();
			q1.x = elements[1].Number();
			q1.y = elements[2].Number();
			q1.z = elements[3].Number();

			g_arrInterface->GetElements(srcArr2, elements, NULL);
			q2.w = elements[0].Number();
			q2.x = elements[1].Number();
			q2.y = elements[2].Number();
			q2.z = elements[3].Number();

			Quat out;
			if (!slerpFlag)
				out = nlerp(q1, q2, t);
			else
				out = slerp(q1, q2, t);

			ArrayElementL newElem[4] = { out.w, out.x, out.y, out.z };
			NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 4, scriptObj);
			g_arrInterface->AssignCommandResult(newArr, result);

			delete[] elements;
		}

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
			v1.x = elements[0].Number();
			v1.y = elements[1].Number();
			v1.z = elements[2].Number();

			g_arrInterface->GetElements(srcArr2, elements, NULL);
			v2.x = elements[0].Number();
			v2.y = elements[1].Number();
			v2.z = elements[2].Number();
			*result = VDotproduct(v1, v2);

			delete[] elements;
		}

	}
	return true;
}

bool Cmd_GenerateBezierPoint_Execute(COMMAND_ARGS) {
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
		ArrayElementL newElem[3] = { newVec.x, newVec.y, newVec.z };
		NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
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

		ArrayElementL newElem[3] = { lerpVec.x, lerpVec.y, lerpVec.z };
		NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
		g_arrInterface->AssignCommandResult(newArr, result);

		delete[] elements;
	}
	return true;
}

bool Cmd_V3Mult_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID1, arrID2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &arrID1, &arrID2)) {
		NVSEArrayVar* srcArr1 = g_arrInterface->LookupArrayByID(arrID1);
		NVSEArrayVar* srcArr2 = g_arrInterface->LookupArrayByID(arrID2);

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

		Vector3 newVec = v1 * v2;
		ArrayElementL newElem[3] = { newVec.x, newVec.y, newVec.z };
		NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
		g_arrInterface->AssignCommandResult(newArr, result);

		delete[] elements;
	}
	return true;
}

bool Cmd_V3MultByScalar_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID;
	float t;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &arrID, &t)) {
		NVSEArrayVar* srcArr1 = g_arrInterface->LookupArrayByID(arrID);

		Vector3 v1, newVec;
		NVSEArrayElement* elements = new NVSEArrayElement[3];
		g_arrInterface->GetElements(srcArr1, elements, NULL);
		v1.x = elements[0].Number();
		v1.y = elements[1].Number();
		v1.z = elements[2].Number();

		newVec.x *= abs(t);
		newVec.y *= abs(t);
		newVec.z *= abs(t);
		ArrayElementL newElem[3] = { newVec.x, newVec.y, newVec.z };
		NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
		g_arrInterface->AssignCommandResult(newArr, result);

		delete[] elements;
	}
	return true;
}

#endif 


