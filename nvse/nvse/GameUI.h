#pragma once

#include "GameTiles.h"
#include "GameTypes.h"
#include "internal/utility.h"

class Menu;
class SceneGraph;
class FOPipboyManager;
class NiObject;
class TESObjectREFR;
class NiNode;

typedef Menu * (* _TempMenuByType)(UInt32 menuType);
extern const _TempMenuByType TempMenuByType;

// 584
class InterfaceManager
{
public:
	InterfaceManager();
	~InterfaceManager();

	static InterfaceManager *	GetSingleton(void);
	static bool					IsMenuVisible(UInt32 menuType);
	static Menu *				GetMenuByType(UInt32 menuType);
	static Menu *				TempMenuByType(UInt32 menuType);
	static TileMenu *			GetMenuByPath(const char * componentPath, const char ** slashPos);
	static Tile::Value *		GetMenuComponentValue(const char * componentPath);
	static Tile *				GetMenuComponentTile(const char * componentPath);
	static Tile::Value *		GetMenuComponentValueAlt(const char * componentPath);



	UInt32				flags;							// 000	bit 1 would be "not menu mode"
	SceneGraph			* sceneGraph004;				// 004
	SceneGraph			* sceneGraph008;				// 008
	UInt8				byt00C;							// 00C
	UInt8				pad00D[3];						// 00D
	UInt32				unk010[(0x028 - 0x010) >> 2];	// 010
	Tile				* cursor;						// 028
	UInt32				unk02C[(0x070 - 0x02C) >> 2];	// 02C
	UInt32				unk070;							// 070
	UInt32				unk074;							// 074
	UInt32				unk078;							// 078
	UInt32				unk07C;							// 07C
	NiNode				* niNode080;					// 080
	NiNode				* niNode084;					// 084
	UInt32				unk088[(0x09C - 0x088) >> 2];	// 088
	Tile				* menuRoot;						// 09C
	Tile				* unk0A0;						// 0A0 seen "Strings"
	void				* unk0A4;						// 0A4 saw Tile? seen NiNode
	UInt32				unk0A8;							// 0A8
	NiObject			* unk0AC;						// 0AC seen NiAlphaProperty
	UInt32				unk0B0[(0x0BC - 0x0B0) >> 2];	// 0B0
	Tile				*activeTileAlt;					// 0BC
	UInt32				unk0C0[3];						// 0B0
	Tile				* activeTile;					// 0CC
	Menu				* activeMenu;					// 0D0
	UInt32				unk0D4[(0x0E4 - 0x0D4) >> 2];	// 0D4
	UInt8				msgBoxButton;					// 0E4 -1 if no button pressed
	UInt8				pad0E5[3];
	UInt32				unk0E8;							// 0E8
	UInt32				unk0EC;							// 0EC
	TESObjectREFR		*debugSelection;				// 0F0	compared to activated object during Activate
	UInt32				unk0F4;							// 0F4
	UInt32				unk0F8;							// 0F8
	TESObjectREFR		* crosshairRef;					// 0FC
	UInt32				unk100[(0x114 - 0x100) >> 2];	// 100
	UInt32				menuStack[10];					// 114
	UInt32				unk13C[14];						// 13C
	FOPipboyManager		* pipboyManager;				// 174
	UInt32				* unk178;						// 178 could be camera pointer, 0054 is bFlyCam
	NiTArray<UInt32>	array17C;						// 17C NiTPrimitiveArray@PackedMenu@BGSMenuPacker
	UInt32				unk18C[(0x394 - 0x18C) >> 2];	// 18C
	NiObject			* unk394;						// 394 seen NiSourceTexture
	UInt32				unk398[(0x454 - 0x398) >> 2];	// 398
	NiTArray<UInt32>	array454;						// 454 NiTPrimitiveArray@TextureType@BSTextureManager
	NiTArray<UInt32>	array464;						// 464 NiTPrimitiveArray@FilterMode@NiTexturingProperty
	UInt32				unk468[(0x584 - 0x474) >> 2];	// 474
};
STATIC_ASSERT(sizeof(InterfaceManager) == 0x584);
STATIC_ASSERT(offsetof(InterfaceManager, debugSelection) == 0x0F0);
STATIC_ASSERT(offsetof(InterfaceManager, crosshairRef) == 0x0FC);
STATIC_ASSERT(offsetof(InterfaceManager, pipboyManager) == 0x174);

void Debug_DumpMenus(void);

enum
{
	kMenuType_Min =				0x3E9,
	kMenuType_Message =			kMenuType_Min,
	kMenuType_Inventory,
	kMenuType_Stats,
	kMenuType_HUDMain,
	kMenuType_Loading =			0x3EF,
	kMenuType_Container,
	kMenuType_Dialog,
	kMenuType_SleepWait =		0x3F4,
	kMenuType_Start,
	kMenuType_LockPick,
	kMenuType_Quantity =		0x3F8,
	kMenuType_Map =				0x3FF,
	kMenuType_Book =			0x402,
	kMenuType_LevelUp,
	kMenuType_Repair =			0x40B,
	kMenuType_RaceSex,
	kMenuType_Credits =			0x417,
	kMenuType_CharGen,
	kMenuType_TextEdit =		0x41B,
	kMenuType_Barter =			0x41D,
	kMenuType_Surgery,
	kMenuType_Hacking,
	kMenuType_VATS,
	kMenuType_Computers,
	kMenuType_RepairServices,
	kMenuType_Tutorial,
	kMenuType_SpecialBook,
	kMenuType_ItemMod,
	kMenuType_LoveTester =		0x432,
	kMenuType_CompanionWheel,
	kMenuType_TraitSelect,
	kMenuType_Recipe,
	kMenuType_SlotMachine =		0x438,
	kMenuType_Blackjack,
	kMenuType_Roulette,
	kMenuType_Caravan,
	kMenuType_Trait =			0x43C,
	kMenuType_Max =				kMenuType_Trait,
};

class Menu
{
public:
	Menu();
	~Menu();

	virtual void	Destructor(bool arg0);		// pass false to free memory
	virtual void	SetField(UInt32 idx, Tile* value);
	virtual void	Unk_02(UInt32 arg0, UInt32 arg1);	// show menu?
	virtual void	HandleClick(UInt32 buttonID, Tile* clickedButton); // buttonID = <id> trait defined in XML
	virtual void	HandleMouseover(UInt32 arg0, Tile * activeTile);	//called on mouseover, activeTile is moused-over Tile
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_06(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_07(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_08(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_09(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0A(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0B(void);
	virtual bool	HandleKeyboardInput(char inputChar);	//for keyboard shortcuts, return true if handled
	virtual UInt32	GetID(void);
	virtual bool	Unk_0E(UInt32 arg0, UInt32 arg1);

	TileMenu		*tile;		// 04
	UInt32			unk08;		// 08
	UInt32			unk0C;		// 0C
	UInt32			unk10;		// 10
	UInt32			unk14;		// 14
	UInt32			unk18;		// 18
	UInt32			unk1C;		// 1C
	UInt32			id;			// 20
	UInt32			unk24;		// 24

	__forceinline Tile* AddTileFromTemplate(Tile* destTile, const char* templateName)
	{
		return ThisCall<Tile*>(0xA1DDB0, this, destTile, templateName, 0);
	}
};

class RaceSexMenu : public Menu
{
public:
	void UpdatePlayerHead(void);
};

struct HotKeyWheel
{
	TileRect* parent;		// 00
	TileRect* hotkeys[8];	// 04
	UInt8		byte24;			// 24
	UInt8		pad25[3];		// 25
	UInt32		unk28;			// 28
	UInt32		selectedHotkeyTrait;// 2C
	UInt32		selectedTextTrait;	// 30
};
static_assert(sizeof(HotKeyWheel) == 0x34);

// 278
class HUDMainMenu : public Menu			// 1004
{

public:

	struct QueuedMessage
	{
		char	msgText[0x204];			// 000
		char	iconPate[MAX_PATH];		// 204
		char	soundPath[MAX_PATH];	// 308
		float	displayTime;			// 40C

	};

	struct SubtitleData;

	struct Struct224
	{
		UInt8		byte00;		// 00
		UInt8		pad01[3];	// 01
		float		flt04;		// 04
		float		flt08;		// 08
		float		flt0C;		// 0C
		float		flt10;		// 10
		UInt32		unk14;		// 14
		UInt32		tickCount;	// 18
		UInt8		byte1C;		// 1C
		UInt8		byte1D;		// 1D
		UInt8		pad1E[2];	// 1E
	};

	struct QueuedQuestText
	{
		char		msg[0x104];
		bool		byte104;
		bool		byte105;
	};

	enum VisibilityFlags
	{
		kActionPoints = 0x1,//0
		kHitPoints = 0x2,//1
		kRadiationMeter = 0x4,//2
		kEnemyHealth = 0x8,//3
		kQuestReminder = 0x10,//4
		kRegionLocation = 0x20,//5
		kReticleCenter = 0x40,//6
		kSneakMeter = 0x80, //7
		kMessages = 0x100, //8
		kInfo = 0x200, //9
		kSubtibles = 0x400,//10
		kHotkeys = 0x800,//11
		kXpMeter = 0x1000,//12
		kBreathMeter = 0x2000,//13
		kExplosivePositioning = 0x4000,//14
		kCrippledLimbIndicator = 0x8000,//15
		kHardcoreMode = 0x10000,//16
	};

	enum HUDStates
	{
		kRECALCULATE = 0x1,
		kNormal,
		kPipBoy,
		kPause,
		kLoading,
		kDialog,
		kVATSMenu,
		kVATSPlayback,
		kContainer,
		kBeginSit,
		kSleepWait,
		kPlayerDisabledControls,
		kUnusedD,
		kLevelUpMenu,
		kHacking,
		kComputers,
		kMessage,
		kSpecialBook,
		kLoveTester,
		kVanityCam,
		kUnused15,
		kAiming,
		kAimingScope,
		kIntroMovie,
		kGambling,
	};

	UInt32							unk028;			// 028
	union
	{
		Tile* tiles[0x56];
		struct
		{
			TileImage* tile02C;		// 02C	HitPoints\meter
			TileText* tile030;		// 030	HitPoints\justify_right_text
			TileRect* tile034;		// 034	HitPoints\compass_window\compass_icon_group
			TileRect* tile038;		// 038	HitPoints\compass_window\compass_icon_group
			TileRect* tile03C;		// 03C	HitPoints\compass_window\compass_icon_group
			TileImage* tile040;		// 040	HitPoints\compass_window
			TileImage* tile044;		// 044	ActionPoints\meter
			TileText* tile048;		// 048	ActionPoints\justify_right_text
			TileText* tile04C;		// 04C	ActionPoints\justify_right_text
			TileImage* tile050;		// 050	ActionPoints\meter
			TileImage* tile054;		// 054	ActionPoints\MeterBackground
			TileText* tile058;		// 058	ActionPoints\justify_right_text
			TileRect* tile05C;		// 05C	QuestReminder\QuestStages
			TileRect* tile060;		// 060	QuestReminder\QuestAdded
			TileText* tile064;		// 064	Region_Location\justify_left_text
			TileText* tile068;		// 068	Region_Location\justify_left_text
			TileImage* tile06C;		// 06C	RadiationMeter\radiation_bracket
			TileImage* tile070;		// 070	RadiationMeter\radiation_pointer
			TileText* tile074;		// 074	RadiationMeter\radiation_text_value
			TileText* tile078;		// 078	RadiationMeter\radiation_text
			TileImage* tile07C;		// 07C	EnemyHealth\enemy_health_bracket
			TileImage* tile080;		// 080	EnemyHealth\meter
			TileText* tile084;		// 084	EnemyHealth\justify_center_text
			TileText* sneakLabel;	// 088	SneakMeter\sneak_nif
			TileImage* tile08C;		// 08C	Messages\message_icon
			TileText* tile090;		// 090	Messages\justify_left_text
			TileImage* tile094;		// 094	Messages\message_bracket
			TileText* tile098;		// 098	Subtitles\justify_center_text
			TileRect* tileTakePrompt;		// 09C	Info\justify_center_hotrect
			TileText* tile0A0;		// 0A0	Info\justify_center_hotrect\PCShortcutLabel
			TileImage* tile0A4;		// 0A4	Info\justify_center_hotrect\xbox_button
			TileText* tile0A8;		// 0A8	Info\justify_center_text
			TileText* tileLockLevelStr;	// 0AC	Info\justify_center_text
			TileText* tile0B0;		// 0B0	Info\justify_center_text
			TileText* tilePickupWeightStr;	// 0B4	Info\justify_right_text
			TileText* tilePickupWG;			// 0B8	Info\justify_left_text
			TileText* tilePickupValueStr;	// 0BC	Info\justify_right_text
			TileText* tilePickupVAL;		// 0C0	Info\justify_left_text
			TileImage* tile0C4;		// 0C4	Info\info_seperator
			TileRect* tile0C8;		// 0C8	Hokeys\hotkey_selector
			TileText* tile0CC;		// 0CC	Hokeys\justify_center_text
			TileImage* tile0D0;		// 0D0	HitPoints\left_bracket
			TileImage* tile0D4;		// 0D4	ActionPoints\right_bracket
			TileImage* tile0D8;		// 0D8	XPMeter\XPBracket
			TileText* tile0DC;		// 0DC	XPMeter\XPAmount
			TileText* tile0E0;		// 0E0	XPMeter\XPLabel
			TileImage* tile0E4;		// 0E4	XPMeter\XPPointer
			TileText* tile0E8;		// 0E8	XPMeter\XPLastLevel
			TileText* tile0EC;		// 0EC	XPMeter\XPNextLevel
			TileText* tile0F0;		// 0F0	XPMeter\XPLevelUp
			TileImage* tile0F4;		// 0F4	ReticleCenter\reticle_center
			TileImage* tile0F8;		// 0F8	crippled_limb_indicator\Face
			TileImage* tile0FC;		// 0FC	crippled_limb_indicator\Head
			TileImage* tile100;		// 100	crippled_limb_indicator\Torso
			TileImage* tile104;		// 104	crippled_limb_indicator\Left_Arm
			TileImage* tile108;		// 108	crippled_limb_indicator\Right_Arm
			TileImage* tile10C;		// 10C	crippled_limb_indicator\Left_Leg
			TileImage* tile110;		// 110	crippled_limb_indicator\Right_Leg
			TileRect* tile114;		// 114	ActionPoints
			TileRect* tile118;		// 118	HitPoints
			TileRect* tile11C;		// 11C	RadiationMeter
			TileRect* tile120;		// 120	EnemyHealth
			TileRect* tile124;		// 124	QuestReminder
			TileRect* tile128;		// 128	Region_Location
			TileRect* tile12C;		// 12C	ReticleCenter
			TileRect* tile130;		// 130	SneakMeter
			TileRect* tile134;		// 134	Messages
			TileRect* tile138;		// 138	Info
			TileRect* tile13C;		// 13C	Subtitles
			TileRect* tile140;		// 140	Hokeys
			TileRect* tile144;		// 144	XPMeter
			int* tile148;			// 148	BreathMeter
			TileRect* tile14C;		// 14C	Explosive_positioning_rect
			TileRect* crippledLimbIndicator;		// 150	crippled_limb_indicator
			TileImage* tile154;		// 154	DDTIcon
			TileImage* tile158;		// 158	DDTIconEnemy
			TileText* tile15C;		// 15C	AmmoTypeLabel
			TileRect* tile160;		// 160	HardcoreMode
			TileText* tile164;		// 164	HardcoreMode\Dehydration
			TileText* tile168;		// 168	HardcoreMode\Sleep
			TileText* tile16C;		// 16C	HardcoreMode\Hunger
			TileImage* tile170;		// 170	DDTIcon
			TileImage* tile174;		// 174	DDTIconEnemyAP
			TileText* tile178;		// 178	HardcoreMode\Rads
			TileText* tile17C;		// 17C	HardcoreMode\LMBs
			TileImage* tile180;		// 180	CNDArrows

		};
	};
	UInt32							unk184;				// 184
	float							flt188;				// 188
	tList<QueuedMessage>			queuedMessages;		// 18C
	UInt32							currMsgKey;			// 194
	BSSimpleArray<SubtitleData>		subtitlesArr;		// 198
	UInt32							unk1A8[4];			// 1A8
	TESObjectREFR* crosshairRef;		// 1B8
	UInt32							unk1BC;				// 1BC
	UInt32							visibilityOverrides;	// 1C0
	UInt32							stage;				// 1C4
	HotKeyWheel						hotKeyWheel;		// 1C8
	UInt8							isUsingScope;		// 1FC
	UInt8							byte1FD[3];			// 1FD
	NiControllerSequence* niContSeq;			// 200
	UInt8							isLevelUpQueued;	// 204
	UInt8							autoDisplayObjectives;	// 205
	UInt8							pad206[2];			// 206
	UInt32							unk208;				// 208
	UInt32							questTargets;		// 20C
	UInt32							unk210;				// 210
	UInt32							compassWidth;		// 214
	UInt32							maxCompassAngle;	// 218
	Actor* healthTarget;		// 21C
	UInt32							unk220;				// 220
	Struct224						unk224;				// 224
	UInt32							unk244;				// 244
	UInt32							unk248[4];			// 248
	tList<QueuedQuestText>			queuedQuestTextList;// 258
	UInt8							byte260;			// 260
	UInt8							byte261;			// 261
	UInt8							pad262[2];			// 262
	tList<UInt32>					xpMessages;			// 264
	tList<UInt32>					list26C;			// 26C
	float							hudShake;			// 274
};
STATIC_ASSERT(sizeof(HUDMainMenu) == 0x278);

// FC
class ComputersMenu : public Menu		// 1057
{
public:
	UInt32				unk28[32];		// 28
	BGSTerminal* baseTerminal;	// A8
	TESObjectREFR* targetRef;		// AC
	UInt32				unkB0[19];		// B0

	__forceinline static ComputersMenu* Get() { return *(ComputersMenu**)0x11D9334; }
};
static_assert(sizeof(ComputersMenu) == 0xFC);
