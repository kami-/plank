#include "fortifications.sqf";

plank_isInitialized = false;
call compile preProcessFileLineNumbers "plank\deploy_functions.sqf";
call compile preProcessFileLineNumbers "plank\ui_functions.sqf";
plank_isInitialized = true;