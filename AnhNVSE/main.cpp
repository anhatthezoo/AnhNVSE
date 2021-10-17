#include "nvse/PluginAPI.h"
#include "nvse/CommandTable.h"
#include "nvse/GameAPI.h"
#include "nvse/ParamInfos.h"
#include "nvse/GameObjects.h"
#include "nvse/GameForms.h"
#include "nvse/GameData.h"
#include "misc/scancodes.h"
#include <string>

IDebugLog		gLog("AnhNVSE.log");
PluginHandle	g_pluginHandle = kPluginHandle_Invalid;

NVSEMessagingInterface* g_messagingInterface;
NVSEStringVarInterface* g_stringvarInterface;
NVSEArrayVarInterface* g_arrInterface;
NVSEInterface* g_nvseInterface;
NVSECommandTableInterface* g_cmdTable;
const CommandInfo* g_TFC;

#if RUNTIME  
NVSEScriptInterface* g_script;
#endif

#ifndef RegisterScriptCommand
#define RegisterScriptCommand(name) nvse->RegisterCommand(&kCommandInfo_ ##name); //Default return type (return a number)
#define REG_CMD(name) nvse->RegisterCommand(&kCommandInfo_##name);  //Short version of RegisterScriptCommand, from JIP.
#define REG_TYPED_CMD(name, type) nvse->RegisterTypedCommand(&kCommandInfo_##name,kRetnType_##type);  //from JG
#define REG_CMD_STR(name) nvse->RegisterTypedCommand(&kCommandInfo_##name, kRetnType_String); //From JIPLN
#define REG_CMD_ARR(name) nvse->RegisterTypedCommand(&kCommandInfo_##name, kRetnType_Array); //From JIPLN
#define REG_CMD_FORM(name) nvse->RegisterTypedCommand(&kCommandInfo_##name, kRetnType_Form); //From JIPLN
#define REG_CMD_AMB(name) nvse->RegisterTypedCommand(&kCommandInfo_##name, kRetnType_Ambiguous); //From JIPLN
#endif

bool (*ExtractArgsEx)(COMMAND_ARGS_EX, ...);
bool (*ExtractFormatStringArgs)(UInt32 fmtStringPos, char *buffer, COMMAND_ARGS_EX, UInt32 maxParams, ...);

#include "functions/fn_math.h"
#include "functions/fn_strings.h"
#include "functions/fn_quest.h"
#include "functions/fn_inventory.h"
#include "functions/fn_arrays.h"

// This is a message handler for nvse events
// With this, plugins can listen to messages such as whenever the game loads
/*void MessageHandler(NVSEMessagingInterface::Message* msg)
{
	switch (msg->type)
	{
	case NVSEMessagingInterface::kMessage_LoadGame:
		//_MESSAGE("Received load game message with file path %s", msg->data);
		break;
	case NVSEMessagingInterface::kMessage_SaveGame:
		//_MESSAGE("Received save game message with file path %s", msg->data);
		break;
	case NVSEMessagingInterface::kMessage_PreLoadGame:
		//_MESSAGE("Received pre load game message with file path %s", msg->data);
		break;
	case NVSEMessagingInterface::kMessage_PostLoadGame:
		//_MESSAGE("Received post load game message", msg->data ? "Error/Unkwown" : "OK");
		break;
	case NVSEMessagingInterface::kMessage_PostLoad:
		//_MESSAGE("Received post load plugins message");
		break;
	case NVSEMessagingInterface::kMessage_PostPostLoad:
		//_MESSAGE("Received post post load plugins message");
		break;
	case NVSEMessagingInterface::kMessage_ExitGame:
		//_MESSAGE("Received exit game message");
		break;
	case NVSEMessagingInterface::kMessage_ExitGame_Console:
		//_MESSAGE("Received exit game via console qqq command message");
		break;
	case NVSEMessagingInterface::kMessage_ExitToMainMenu:
		//_MESSAGE("Received exit game to main menu message");
		break;
	case NVSEMessagingInterface::kMessage_Precompile:
		//_MESSAGE("Received precompile message with script at %08x", msg->data);
		break;
	case NVSEMessagingInterface::kMessage_RuntimeScriptError:
		//_MESSAGE("Received runtime script error message %s", msg->data);
		break;
	default:
		break;
	}
} */

bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info)
{
	_MESSAGE("query");

	// fill out the info structure
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "AnhNVSE";
	info->version = 1;

	// version checks
	if (nvse->nvseVersion < PACKED_NVSE_VERSION)
	{
		_ERROR("NVSE version too old (got %08X expected at least %08X)", nvse->nvseVersion, PACKED_NVSE_VERSION);
		return false;
	}

	if (!nvse->isEditor)
	{
		if (nvse->runtimeVersion < RUNTIME_VERSION_1_4_0_525)
		{
			_ERROR("incorrect runtime version (got %08X need at least %08X)", nvse->runtimeVersion, RUNTIME_VERSION_1_4_0_525);
			return false;
		}

		if (nvse->isNogore)
		{
			_ERROR("NoGore is not supported");
			return false;
		}
	}

	else
	{
		if (nvse->editorVersion < CS_VERSION_1_4_0_518)
		{
			_ERROR("incorrect editor version (got %08X need at least %08X)", nvse->editorVersion, CS_VERSION_1_4_0_518);
			return false;
		}
	}

	return true;
}

bool NVSEPlugin_Load(const NVSEInterface* nvse)
{
	_MESSAGE("load");

	g_pluginHandle = nvse->GetPluginHandle();

	g_nvseInterface = (NVSEInterface*)nvse;

	//g_messagingInterface = (NVSEMessagingInterface*)nvse->QueryInterface(kInterface_Messaging);
	//g_messagingInterface->RegisterListener(g_pluginHandle, "NVSE", MessageHandler);

	g_stringvarInterface = (NVSEStringVarInterface*)nvse->QueryInterface(kInterface_StringVar);
	g_arrInterface = (NVSEArrayVarInterface*)nvse->QueryInterface(kInterface_ArrayVar);
	ExtractFormatStringArgs = g_script->ExtractFormatStringArgs;

#if RUNTIME
	g_script = (NVSEScriptInterface*)nvse->QueryInterface(kInterface_Script);
	ExtractArgsEx = g_script->ExtractArgsEx;
#endif
	nvse->SetOpcodeBase(0x3600);
	REG_CMD(DegToRad);
	REG_CMD(RadToDeg);
	REG_CMD_STR(ScancodeToChar);
	//REG_CMD_STR(Sv_PadStart);
	REG_CMD(GetAngleQuadrant);
	REG_CMD(GetQuestCompletedAlt);
	REG_CMD(Sinh);
	REG_CMD(Cosh);
	REG_CMD(Tanh);
	REG_CMD(SetWeaponAnimJamTime);
	REG_CMD(SetWeaponAnimReloadTime);
	REG_CMD(SetWeaponAnimShotsPerSec);
	REG_CMD(SetWeaponFireDelayMin);
	REG_CMD(SetWeaponFireDelayMax);
	REG_CMD(SetWeaponRumbleDuration);
	REG_CMD(SetWeaponRumbleRightMotor);
	REG_CMD(SetWeaponRumbleLeftMotor);
	REG_CMD(SetWeaponRumbleWavelength);

	REG_CMD(V3_Normalized_Alt);
	return true;
}
