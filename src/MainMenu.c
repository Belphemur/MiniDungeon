#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "Adventure.h"
#include "Character.h"
#include "Battle.h"
#include "Items.h"
#include "MainMenu.h"
#include "Menu.h"
#include "Shop.h"
#include "UILayers.h"

// **************** TEST MENU ******************//

void DoNothing(void)
{
}

#if ALLOW_TEST_MENU

void ForceEvent(void)
{
	PopMenu();
	ComputeRandomEvent(true);
}

void ForceNewFloor(void)
{
	PopMenu();
	ShowNewFloorWindow();
}

void ForceItemGain(void)
{
	PopMenu();
	ShowItemGainWindow();
}

void ForceBattle(void)
{
	PopMenu();
	ShowBattleWindow();
}

void ForceShop(void)
{
	PopMenu();
	ShowShopWindow();
}

MenuDefinition testMenuDef = 
{
	.menuEntries = 
	{
		{"Quit", "", PopMenu},
		{"Random", "", ForceEvent},
		{"NewFloor", "", ForceNewFloor},
		{"Item", "", ForceItemGain},
		{"Battle", "", ForceBattle},
		{"Shop", "", ForceShop},
	},
	.mainImageId = -1
};

void ShowTestMenu(void)
{
	PushNewMenu(&testMenuDef);
}
#endif

//************* Main Menu *****************//

static bool vibration = true;
static bool fastMode = false;
#if ALLOW_GOD_MODE
static bool godMode = false;
#endif

void DrawOptionsMenu(void)
{
	ShowMainWindowRow(0, "Options", "");
	ShowMainWindowRow(1, "Vibration", vibration ? "On" : "Off");
	ShowMainWindowRow(2, "Fast Mode", fastMode ? "On" : "Off");
#if ALLOW_GOD_MODE
	ShowMainWindowRow(3, "God Mode", godMode ? "On" : "Off");
#endif
}

void ToggleVibration(void)
{
	vibration = !vibration;
	DrawOptionsMenu();
}

bool GetVibration(void)
{
	return vibration;
}

bool GetFastMode(void)
{
	return fastMode;
}

void ToggleFastMode(void)
{
	fastMode = !fastMode;
	DrawOptionsMenu();
}
#if ALLOW_GOD_MODE
void ToggleGodMode(void)
{
	godMode = !godMode;
	DrawOptionsMenu();
}

bool GetGodMode(void)
{
	return godMode;
}
#endif
void OptionsMenuAppear(Window *window);

MenuDefinition optionsMenuDef = 
{
	.menuEntries = 
	{
		{"Quit", "Return to main menu", PopMenu},
		{"Toggle", "Toggle Vibration", ToggleVibration},
		{"Toggle", "Speed up events", ToggleFastMode}
#if ALLOW_GOD_MODE
		,{"Toggle", "Invinsible and autokill", ToggleGodMode}
#endif
	},
	.appear = OptionsMenuAppear,
	.mainImageId = -1
};

void OptionsMenuAppear(Window *window)
{
	MenuAppear(window);
	DrawOptionsMenu();
}

void ShowOptionsMenu(void)
{
	PushNewMenu(&optionsMenuDef);
}

void MainMenuWindowAppear(Window *window);

MenuDefinition mainMenuDef = 
{
	.menuEntries = 
	{
		{"Quit", "Return to adventure", PopMenu},
		{"Items", "Items Owned", ShowMainItemMenu},
		{"Progress", "Character advancement", ShowProgressMenu},
		{"Stats", "Character Stats", ShowStatMenu},
		{"Options", "Open the options menu", ShowOptionsMenu},
	},
	.appear = MainMenuWindowAppear,
	.mainImageId = RESOURCE_ID_IMAGE_REST
};

void MainMenuWindowAppear(Window *window)
{
	MenuAppear(window);
	ShowMainWindowRow(0, "Paused", "");
}

void ShowMainMenu(void)
{
	PushNewMenu(&mainMenuDef);
}
