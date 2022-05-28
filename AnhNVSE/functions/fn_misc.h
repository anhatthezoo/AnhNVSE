#pragma once

// 10
class ExtraEncounterZone : public BSExtraData
{
public:
	ExtraEncounterZone();
	virtual ~ExtraEncounterZone();

	BGSEncounterZone* zone;		// 0C
};


DEFINE_COMMAND_ALT_PLUGIN(GetZoneMinLevel, WhatsTheMinimumRequiredLevelToBeInTheZone, "", 0, 1, kParams_OneForm)
DEFINE_COMMAND_ALT_PLUGIN(GetZoneMatchLevel, AreWeAMatchInTheZoneOrWillIBeFriendZoned, "", 0, 1, kParams_OneForm)
DEFINE_COMMAND_ALT_PLUGIN(GetZoneOwner, WhosTheZoner, "", 0, 1, kParams_OneForm)
DEFINE_COMMAND_ALT_PLUGIN(GetZoneLevel, ImInTheZoneButIWantToKnowMyLevel, "", 0, 1, kParams_OneForm)
DEFINE_COMMAND_ALT_PLUGIN(SetZoneMinLevel, IfYouWannaBeInTheZoneYouGottaBeThisLevelMinimum, "", 0, 2, kParams_OneForm_OneInt)
DEFINE_COMMAND_ALT_PLUGIN(SetZoneOwner, ImTheZoner, "", 0, 2, kParams_OneForm_OneOptionalForm)

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
			*result = (zone->zoneFlags & BGSEncounterZone::kEncounterZone_StrictMinimumLevel) != 0;
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

bool Cmd_SetZoneOwner_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* zoneForm;
	TESForm* ownerForm;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &zoneForm, &ownerForm)) {
		if (auto const zone = DYNAMIC_CAST(zoneForm, TESForm, BGSEncounterZone))
			if (ownerForm->refID == 0x14 || !ownerForm) zone->owner = PlayerCharacter::GetSingleton()->baseForm;
			else zone->owner = ownerForm; 

				
	}
	return true;
}
