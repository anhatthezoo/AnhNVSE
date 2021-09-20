#pragma once

DEFINE_COMMAND_PLUGIN(DegToRad, "Converts degrees to radians", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(RadToDeg, "Converts radians to degrees", 0, 1, kParams_OneFloat)

bool Cmd_DegToRad_Execute(COMMAND_ARGS);
bool Cmd_RadToDeg_Execute(COMMAND_ARGS);

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

#endif 