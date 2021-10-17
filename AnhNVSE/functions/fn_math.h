#pragma once

#include <math.h>

static ParamInfo kParams_OneDouble[] = {
	{	"Double", kParamType_Double, 0	}
};

DEFINE_COMMAND_PLUGIN(DegToRad, "Converts degrees to radians", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(RadToDeg, "Converts radians to degrees", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(GetAngleQuadrant, "Returns the quadrant of an angle (radian)", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(Sinh, "Hyperbolic sin of angle", 0, 1, kParams_OneDouble)
DEFINE_COMMAND_PLUGIN(Cosh, "Hyperbolic cos of angle", 0, 1, kParams_OneDouble)
DEFINE_COMMAND_PLUGIN(Tanh, "Hyperbolic tan of angle", 0, 1, kParams_OneDouble)

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

#endif 


