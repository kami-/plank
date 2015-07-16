if (!isDedicated) then {
    // Check if Arma 2 or Arma 3
    if (isNil {call compile "blufor"}) then {
        call compile preprocessFileLineNumbers "plank\arma2_fortifications.sqf";
        if (isNil {BIS_fnc_init} || {!BIS_fnc_init}) then {
            createCenter sideLogic;
            (createGroup sideLogic) createUnit ["FunctionsManager", [0, 0, 0], [], 0, "NONE"];
        };
    } else {
        call compile preprocessFileLineNumbers "plank\arma3_fortifications.sqf";
    };

    plank_isInitialized = false;

    waitUntil {
        !isNil {BIS_fnc_init} && {BIS_fnc_init};
    };
    call compile preProcessFileLineNumbers "plank\deploy_functions.sqf";
    call compile preProcessFileLineNumbers "plank\ui_functions.sqf";
    call compile preProcessFileLineNumbers "plank\api_functions.sqf";

    plank_isInitialized = true;
};