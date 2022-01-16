#pragma once

DEFINE_COMMAND_PLUGIN(GetZoneMinLevel, "", 0, 1, kParams_OneForm)
DEFINE_COMMAND_PLUGIN(GetZoneMatchLevel, "", 0, 1, kParams_OneForm)
DEFINE_COMMAND_PLUGIN(GetZoneOwner, "", 0, 1, kParams_OneForm)
DEFINE_COMMAND_PLUGIN(GetZoneLevel, "", 0, 1, kParams_OneForm)
DEFINE_COMMAND_PLUGIN(SetZoneMinLevel, "", 0, 2, kParams_OneForm_OneInt)
DEFINE_COMMAND_PLUGIN(SetZoneOwner, "", 0, 2, kParams_TwoForms)

bool Cmd_GetZoneMinLevel_Execute(COMMAND_ARGS) {
	*result = -1;
	TESForm* form;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form)) {
		if (auto const zone = DYNAMIC_CAST(form, TESForm, BGSEncounterZone))
			*result = (zone->minLevel);
	}
	return true;
}

bool Cmd_GetZoneMatchLevel_Execute(COMMAND_ARGS) {
	*result = -1;
	TESForm* form;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form)) {
		if (auto const zone = DYNAMIC_CAST(form, TESForm, BGSEncounterZone))
			*result = (zone->zoneFlags & BGSEncounterZone::kEncounterZone_StrictMinimumLevel);
	}
	return true;
}

bool Cmd_GetZoneOwner_Execute(COMMAND_ARGS) {
	UInt32* refResult = (UInt32*)result;
	*refResult = 0;
	TESForm* form;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form)) {
		if (auto const zone = DYNAMIC_CAST(form, TESForm, BGSEncounterZone))
			if (zone->owner) *refResult = zone->owner->refID;
	}
	return true;
}

bool Cmd_GetZoneLevel_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* form;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form)) {
		if (auto const zone = DYNAMIC_CAST(form, TESForm, BGSEncounterZone))
			*result = zone->zoneLevel;
	}
	return true;
}

bool Cmd_SetZoneMinLevel_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* form;
	UInt8 level;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form, &level)) {
		if (auto const zone = DYNAMIC_CAST(form, TESForm, BGSEncounterZone))
			zone->minLevel = level;
	}
	return true;
}

/*bool Cmd_SetZoneMatchLevel_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* form;
	bool setMatchLvl;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form, &setMatchLvl)) {
		if (auto const zone = DYNAMIC_CAST(form, TESForm, BGSEncounterZone))
			
	}
	return true;
} */

bool Cmd_SetZoneOwner_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* zoneForm;
	TESForm* ownerForm;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &zoneForm, &ownerForm)) {
		if (auto const zone = DYNAMIC_CAST(zoneForm, TESForm, BGSEncounterZone))
			zone->owner = ownerForm;
	}
	return true;
}
