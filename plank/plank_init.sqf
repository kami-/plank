#include "fortifications.sqf";

plank_isInitialized = false;

waitUntil {
    !isNil {BIS_fnc_init} && {BIS_fnc_init};
};
call compile preProcessFileLineNumbers "plank\deploy_functions.sqf";
call compile preProcessFileLineNumbers "plank\ui_functions.sqf";

plank_isInitialized = true;