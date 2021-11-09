#pragma once

#include "GameObjects.h"
#include "GameProcess.h"

#define DEFINE_SET_INV_FLOAT(name, desc) DEFINE_COMMAND_PLUGIN(name, desc, 0, 2, kParams_OneFloat_OneOptionalObjectID);
#define DEFINE_GET_INV_COND(name, alt, desc) DEFINE_CMD_ALT_COND_PLUGIN(name, alt, desc, false, kParams_OneOptionalObjectID);
#define DEFINE_SET_INV_INT(name, alt, desc) DEFINE_COMMAND_ALT_PLUGIN(name, alt, desc, false, 2, kParams_OneInt_OneOptionalObjectID);

DEFINE_SET_INV_FLOAT(SetWeaponAnimJamTime, sets the duration fOr weapons jam animation);
DEFINE_SET_INV_FLOAT(SetWeaponAnimReloadTime, sets the duration fOr weapons reload animation);
DEFINE_SET_INV_FLOAT(SetWeaponAnimShotsPerSec, sets animshotspersec);
DEFINE_SET_INV_FLOAT(SetWeaponFireDelayMin, sets firedelaymin);
DEFINE_SET_INV_FLOAT(SetWeaponFireDelayMax, sets firedelaymax);
DEFINE_SET_INV_FLOAT(SetWeaponRumbleDuration, sets rumble duration);
DEFINE_SET_INV_FLOAT(SetWeaponRumbleRightMotor, sets right motor strength);
DEFINE_SET_INV_FLOAT(SetWeaponRumbleLeftMotor, sets left motor strength);
DEFINE_SET_INV_FLOAT(SetWeaponRumbleWavelength, sets rumble wavelength);
DEFINE_GET_INV_COND(GetArmorARAlt, GetArmorArmorRatingAlt, returns the armor rating of the specified armor.);
DEFINE_SET_INV_INT(SetArmorARAlt, SetArmorArmorRatingAlt, sets the armor rating of the armor.);

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

TESForm* Extract_IntAndForm(COMMAND_ARGS, UInt32& intVal)
{
	TESForm* pForm = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &intVal, &pForm)) {
		pForm = pForm->TryGetREFRParent();
		if (!pForm) {
			if (thisObj) {
				pForm = thisObj->baseForm;
			}
		}
	}
	return pForm;
}

#if RUNTIME
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

//copied from nvse, just changed the result to be / by 100
bool Cmd_GetArmorARAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = NULL;

	if (!ExtractArgs(EXTRACT_ARGS, &pForm)) return true;
	pForm = pForm->TryGetREFRParent();
	if (!pForm) {
		if (!thisObj) return true;
		pForm = thisObj->baseForm;
	}

	TESObjectARMO* pArmor = DYNAMIC_CAST(pForm, TESForm, TESObjectARMO);
	if (pArmor) {
		*result = ((pArmor->armorRating) / 100);
	}
	return true;
}
bool Cmd_GetArmorARAlt_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	TESForm* pForm = NULL;

	if (arg1) {
		pForm = (TESForm*)arg1;
	}
	else if (thisObj) {
		pForm = thisObj->baseForm;
	}
	else return true;

	TESObjectARMO* pArmor = DYNAMIC_CAST(pForm, TESForm, TESObjectARMO);
	if (pArmor) {
		*result = ((pArmor->armorRating) / 100);
	}
	return true;
}

bool Cmd_SetArmorARAlt_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 nuAR = 0;
	TESForm* pForm = Extract_IntAndForm(PASS_COMMAND_ARGS, nuAR);
	if (pForm) {
		TESObjectARMO* pArmor = DYNAMIC_CAST(pForm, TESForm, TESObjectARMO);
		if (pArmor) {
			pArmor->armorRating = (nuAR * 100);
		}
	}
	return true;
}

#endif