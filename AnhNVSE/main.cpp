#include "nvse/PluginAPI.h"
#include "nvse/CommandTable.h"
#include "nvse/GameAPI.h"
#include "nvse/ParamInfos.h"
#include "nvse/GameObjects.h"
#include "nvse/GameForms.h"
#include "misc/scancodes.h"
#include "nvse/GameData.h"
#include <string>

#define RegisterScriptCommand(name) nvse->RegisterCommand(&kCommandInfo_ ##name); //Default return type (return a number)
#define REG_CMD(name) nvse->RegisterCommand(&kCommandInfo_##name);  //Short version of RegisterScriptCommand, from JIP.
#define REG_TYPED_CMD(name, type) nvse->RegisterTypedCommand(&kCommandInfo_##name,kRetnType_##type);  //from JG
#define REG_CMD_STR(name) nvse->RegisterTypedCommand(&kCommandInfo_##name, kRetnType_String); //From JIPLN
#define REG_CMD_ARR(name) nvse->RegisterTypedCommand(&kCommandInfo_##name, kRetnType_Array); //From JIPLN
#define REG_CMD_FORM(name) nvse->RegisterTypedCommand(&kCommandInfo_##name, kRetnType_Form); //From JIPLN
#define REG_CMD_AMB(name) nvse->RegisterTypedCommand(&kCommandInfo_##name, kRetnType_Ambiguous); //From JIPLN

IDebugLog		gLog("AnhNVSE.log");
PluginHandle	g_pluginHandle = kPluginHandle_Invalid;

NVSEMessagingInterface* g_messagingInterface;
NVSEStringVarInterface* g_stringvarInterface;
NVSEInterface* g_nvseInterface;
NVSECommandTableInterface* g_cmdTable;
const CommandInfo* g_TFC;

#if RUNTIME  
NVSEScriptInterface* g_script;
#endif

bool (*ExtractArgsEx)(COMMAND_ARGS_EX, ...);
bool (*ExtractFormatStringArgs)(UInt32 fmtStringPos, char *buffer, COMMAND_ARGS_EX, UInt32 maxParams, ...);

// This is a message handler for nvse events
// With this, plugins can listen to messages such as whenever the game loads
void MessageHandler(NVSEMessagingInterface::Message* msg)
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
}
bool Cmd_DegToRad_Execute(COMMAND_ARGS);

#if RUNTIME
bool Cmd_DegToRad_Execute(COMMAND_ARGS) {
	float deg;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &deg)) {
		*result = (deg * 0.0174532925);
	}
	return true;
}
#endif

bool Cmd_RadToDeg_Execute(COMMAND_ARGS);

#if RUNTIME
bool Cmd_RadToDeg_Execute(COMMAND_ARGS) {
	float rad;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &rad)) {
		*result = (rad * 57.2957795131);
	}
	return true;
}
#endif

bool Cmd_ScancodeToChar_Execute(COMMAND_ARGS);

#if RUNTIME
bool Cmd_ScancodeToChar_Execute(COMMAND_ARGS) {
	int key;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &key)) {
		g_stringvarInterface->Assign(PASS_COMMAND_ARGS, ScanCodes[key]);
		return true;
	}
	return true;
}
#endif 

bool Cmd_Sv_PadStart_Execute(COMMAND_ARGS);

static ParamInfo kParams_OneString_OneInt_OneString[3] =
{
	{	"string",	kParamType_StringVar,	0	},
	{	"max_length",	kParamType_Integer,	0	},
	{	"string",	kParamType_String,	0	},
};

bool Cmd_Sv_PadStart_Execute(COMMAND_ARGS) {
	UInt32 strID;
	int maxLength;
	char padChar;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &strID, &maxLength, &padChar)) {
		const char* srcString = g_stringvarInterface->GetString(strID);
		if (srcString) {
			/*if (strlen(srcString) == maxLength) {
				for (int i = strlen(srcString); i < maxLength; i++) {
					srcString += padChar;
				}
				g_stringvarInterface->Assign(PASS_COMMAND_ARGS, srcString);
			} */
			Console_Print("hi");
			//else { g_stringvarInterface->Assign(PASS_COMMAND_ARGS, srcString); }

		}
	}

	return true;
}

DEFINE_COMMAND_PLUGIN(DegToRad, "Converts degrees to radians", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(RadToDeg, "Converts radians to degrees", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(ScancodeToChar, "Converts a scancode int to string", 0, 1, kParams_OneInt)
DEFINE_COMMAND_PLUGIN(Sv_PadStart, "Pad a character to the start of a string", 0, 1, kParams_OneString_OneInt_OneString)

bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info)
{
	_MESSAGE("query");

	// fill out the info structure
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "AnhNVSE";
	info->version = 2;

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

	g_messagingInterface = (NVSEMessagingInterface*)nvse->QueryInterface(kInterface_Messaging);
	g_messagingInterface->RegisterListener(g_pluginHandle, "NVSE", MessageHandler);

	g_stringvarInterface = (NVSEStringVarInterface*)nvse->QueryInterface(kInterface_StringVar);
	ExtractFormatStringArgs = g_script->ExtractFormatStringArgs;

#if RUNTIME
	g_script = (NVSEScriptInterface*)nvse->QueryInterface(kInterface_Script);
	ExtractArgsEx = g_script->ExtractArgsEx;
#endif
	nvse->SetOpcodeBase(0x2000);
	REG_CMD(DegToRad);
	REG_CMD(RadToDeg);
	REG_CMD_STR(ScancodeToChar);
	REG_CMD_STR(Sv_PadStart);
	return true;
}
