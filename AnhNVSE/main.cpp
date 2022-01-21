#include "internal/utility.h"
#include "nvse/PluginAPI.h"
#include "nvse/CommandTable.h"
#include "nvse/GameAPI.h"
#include "nvse/ParamInfos.h"
#include "nvse/GameObjects.h"
#include "nvse/GameForms.h"
#include "nvse/GameData.h"
#include "nvse/NiNodes.h"
#include "nvse/NiObjects.h"
#include "nvse/NiTypes.h"
#include "internal/netimmerse.h"
#include "misc/scancodes.h"
#include <string>

IDebugLog		gLog("AnhNVSE.log");
PluginHandle	g_pluginHandle = kPluginHandle_Invalid;

NVSEMessagingInterface* g_messagingInterface;
NVSEStringVarInterface* g_stringvarInterface;
NVSEArrayVarInterface* g_arrInterface;
NVSEInterface* g_nvseInterface;
NVSECommandTableInterface* g_cmdTable;
DataHandler* g_dataHandler;
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


#include "functions/fn_arrays.h"
#include "functions/fn_math.h"
#include "functions/fn_strings.h"
#include "functions/fn_quest.h"
#include "functions/fn_inventory.h"
#include "functions/fn_miscref.h"
#include "functions/fn_misc.h"

// This is a message handler for nvse events
// With this, plugins can listen to messages such as whenever the game loads
void MessageHandler(NVSEMessagingInterface::Message* msg)
{
	switch (msg->type)
	{
	case NVSEMessagingInterface::kMessage_DeferredInit:
		Console_Print("AnhNVSE v1.2.0");
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
} 

bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info)
{
	_MESSAGE("query");

	// fill out the info structure
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "AnhNVSE";
	info->version = 120;

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


	if (!nvse->isEditor)
	{
		g_pluginHandle = nvse->GetPluginHandle();

		g_nvseInterface = (NVSEInterface*)nvse;

		g_stringvarInterface = (NVSEStringVarInterface*)nvse->QueryInterface(kInterface_StringVar);
		g_arrInterface = (NVSEArrayVarInterface*)nvse->QueryInterface(kInterface_ArrayVar);
		ExtractFormatStringArgs = g_script->ExtractFormatStringArgs;
		g_messagingInterface = (NVSEMessagingInterface*)nvse->QueryInterface(kInterface_Messaging);
		g_messagingInterface->RegisterListener(g_pluginHandle, "NVSE", MessageHandler);

		g_script = (NVSEScriptInterface*)nvse->QueryInterface(kInterface_Script);
		ExtractArgsEx = g_script->ExtractArgsEx;

		g_dataHandler = (DataHandler*)nvse->QueryInterface(kInterface_Data);
	}
	
	nvse->SetOpcodeBase(0x3600);
	// ===== v.1.0.0 =====

	/*3600*/ REG_CMD(DegToRad);
	/*3601*/ REG_CMD(RadToDeg);
	/*3602*/ REG_CMD_STR(ScancodeToChar);
	/*3603*/ REG_CMD(GetAngleQuadrant);
	/*3604*/ REG_CMD(GetQuestCompletedAlt);
	/*3605*/ REG_CMD(Sinh);
	/*3606*/ REG_CMD(Cosh);
	/*3607*/ REG_CMD(Tanh);
	/*3608*/ REG_CMD(SetWeaponAnimJamTime);
	/*3609*/ REG_CMD(SetWeaponAnimReloadTime);
	/*360A*/ REG_CMD(SetWeaponAnimShotsPerSec);
	/*360B*/ REG_CMD(SetWeaponFireDelayMin);
	/*360C*/ REG_CMD(SetWeaponFireDelayMax);
	/*360D*/ REG_CMD(SetWeaponRumbleDuration);
	/*360E*/ REG_CMD(SetWeaponRumbleRightMotor);
	/*360F*/ REG_CMD(SetWeaponRumbleLeftMotor);
	/*3610*/ REG_CMD(SetWeaponRumbleWavelength);

	// ===== v1.1.0 =====

	/*3611*/ REG_CMD_ARR(V3NormalizeAlt);
	/*3612*/ REG_CMD_ARR(V3CrossproductAlt);
	/*3613*/ REG_CMD_ARR(QMultQuatQuatAlt);
	/*3614*/ REG_CMD_ARR(QMultQuatVector3Alt);
	/*3615*/ REG_CMD_ARR(QNormalizeAlt);
	/*3616*/ REG_CMD_ARR(QFromAxisAngleAlt);
	/*3617*/ REG_CMD_ARR(QInterpolateAlt);
	/*3618*/ REG_CMD(V3Dotproduct);
	/*3619*/ REG_CMD(GetArmorARAlt);
	/*361A*/ REG_CMD(SetArmorARAlt);
	/*361B*/ REG_CMD_STR(Sv_PadStart);
	/*361C*/ REG_CMD_STR(Sv_PadEnd);

	// ===== v1.2.0 =====
	/*361D*/ REG_CMD_ARR(V3Lerp);
	/*361E*/ REG_CMD_ARR(GenerateBezierPoint);
	/*361F*/ REG_CMD(UpdateTubeMesh);
	/*3620*/ REG_CMD_ARR(V3Mult);
	/*3621*/ REG_CMD_ARR(V3MultByScalar);
	/*3622*/ REG_CMD_STR(Sv_Capitalize);
	/*3623*/ REG_CMD(Ar_Min);
	/*3624*/ REG_CMD(Ar_Max);
	/*3625*/ REG_CMD(Ar_RangeMath);
	/*3626*/ REG_CMD(GetZoneMinLevel);
	/*3627*/ REG_CMD(GetZoneMatchLevel);
	/*3628*/ REG_CMD_FORM(GetZoneOwner);
	/*3629*/ REG_CMD(GetZoneLevel);
	/*362A*/ REG_CMD(SetZoneMinLevel);
	/*362B*/ REG_CMD(SetZoneOwner);
	
	return true;
}
