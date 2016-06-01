#include "plank_macros.h"

#include "\userconfig\plank\log\preinit.h"
#include "logbook.h"


plank_isInitialized = false;

[] call compile preProcessFileLineNumbers ADDON_PATH(config_functions.sqf);
plank_isEnabled = ["isEnabled"] call plank_config_fnc_getBool;

if (plank_isEnabled && {!isDedicated}) then {
    [] call compile preProcessFileLineNumbers ADDON_PATH(event_functions.sqf);
    [] call plank_event_fnc_init;
    [] call compile preProcessFileLineNumbers ADDON_PATH(deploy_functions.sqf);
    [] call compile preProcessFileLineNumbers ADDON_PATH(ui_functions.sqf);
    [] call compile preProcessFileLineNumbers ADDON_PATH(export_functions.sqf);
    [] call compile preProcessFileLineNumbers ADDON_PATH(api_functions.sqf);
    [] call compile preprocessFileLineNumbers ADDON_PATH(arma3_fortifications.sqf);

    [] call plank_deploy_fnc_preInit;
    [] call plank_export_fnc_preInit;

    plank_isInitialized = true;
    ["plank.initialized", []] call plank_event_fnc_emitEvent;
    INFO("plank",FMT_1("Plank version '%1' has been successfully initialized.",STR_PLANK_VERSION));
} else {
    INFO("plank",FMT_1("Plank version '%1' was disabled.",STR_PLANK_VERSION));
};
