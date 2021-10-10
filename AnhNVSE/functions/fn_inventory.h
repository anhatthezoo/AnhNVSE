#pragma once

#include "GameObjects.h"
#include "GameProcess.h"

#define DEFINE_SET_INV_FLOAT(name, alt, desc) DEFINE_CMD_ALT(name, alt, desc, 0, 2, kParams_OneFloat_OneOptionalObjectID);

DEFINE_SET_INV_FLOAT(SetWeaponAnimJamTime, SetAnimJamTime, sets the duration fOr weapons jam animation);
DEFINE_SET_INV_FLOAT(SetWeaponAnimReloadTime, SetAnimReloadTime, sets the duration fOr weapons reload animation);
DEFINE_SET_INV_FLOAT(SetWeaponAnimShotsPerSec, SetAnimSPS, sets animshotspersec);
DEFINE_SET_INV_FLOAT(SetWeaponFireDelayMin, SetFireDelayMin, sets firedelaymin);
DEFINE_SET_INV_FLOAT(SetWeaponFireDelayMax, SetFireDelayMax, sets firedelaymax);
DEFINE_SET_INV_FLOAT(SetWeaponRumbleDuration, SetRumbleLength, sets rumble duration);
DEFINE_SET_INV_FLOAT(SetWeaponRumbleRightMotor, SetRumbleRMotr, sets right motor strength);
DEFINE_SET_INV_FLOAT(SetWeaponRumbleLeftMotor, SetRumbleLMotr, sets left motor strength);
DEFINE_SET_INV_FLOAT(SetWeaponRumbleWavelength, SetRumbleWavelength, sets rumble wavelength);

TESForm* Extract_FloatAndForm(COMMAND_ARGS, float& floatVal)
{
	TESForm* pForm = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &floatVal, &pForm)) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (thisObj) {
				pForm = thisObj->baseForm;
			}
		}
	}
	return pForm;
}

TESObjectWEAP* Extract_FloatAndWeapon(COMMAND_ARGS, float& floatVal) {
	TESObjectWEAP* pWeapon = NULL;
	TESForm* pForm = Extract_FloatAndForm(PASS_COMMAND_ARGS, floatVal);
	if (pForm) {
		pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
	}
	return pWeapon;
}

bool Cmd_SetWeaponAnimJamTime_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->animJamTime = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponAnimReloadTime_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->animReloadTime = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponAnimShotsPerSec_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->animShotsPerSec = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponFireDelayMin_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->semiAutoFireDelayMin = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponFireDelayMax_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->semiAutoFireDelayMax = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponRumbleDuration_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->rumbleDuration = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponRumbleRightMotor_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->rumbleRightMotor = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponRumbleLeftMotor_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->rumbleLeftMotor = floatVal;
	}
	return true;
}

bool Cmd_SetWeaponRumbleWavelength_Execute(COMMAND_ARGS)
{
	*result = 0;
	float floatVal = 0.0;
	TESObjectWEAP* pWeapon = Extract_FloatAndWeapon(PASS_COMMAND_ARGS, floatVal);
	if (pWeapon) {
		pWeapon->rumbleWavelength = floatVal;
	}
	return true;
}
