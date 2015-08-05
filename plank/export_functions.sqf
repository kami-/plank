#include "plank_macros.h"

#include "\userconfig\plank\log\export.h"
#include "logbook.h"

#define NEW_LINE                toString [13, 10]


plank_export_fnc_preInit = {
    plank_export_deployedForts = [];
};

plank_export_fnc_addFort = {
    FUN_ARGS_2(_unit,_fort);

    DECLARE(_exportData) = [
        typeOf _fort,
        getPosASL _fort,
        getDir _fort,
        _unit getVariable ["plank_deploy_fortPitch", 0],
        _unit getVariable ["plank_deploy_fortBank", 0]
    ];
    PUSH(plank_export_deployedForts,_exportData);
};

plank_export_fnc_export = {
    DECLARE(_exportCode) = format ['comment "Exported from Plank.";%1', NEW_LINE];
    if (isNil {blufor}) then {
        _exportCode = _exportCode + format ['comment "Requires BIS functions modules.";%1%1', NEW_LINE];
    };
    {
        _exportCode = _exportCode + ([_x] call plank_export_fnc_getFortCode);
    } foreach plank_export_deployedForts;

    copyToClipboard _exportCode;
};


plank_export_fnc_getFortCode = {
    FUN_ARGS_1(_exportData);

    DECLARE(_exportCode) = format ['private "_fortification";%1', NEW_LINE];
    _exportCode = _exportCode + format ['_fortification = createVehicle ["%1", [0,0,0], [], 0, "NONE"];%2', _exportData select 0, NEW_LINE];
    _exportCode = _exportCode + format ['_fortification setPosASL %1;%2', _exportData select 1, NEW_LINE];
    _exportCode = _exportCode + format ['_fortification setDir %1;%2', _exportData select 2, NEW_LINE];
    _exportCode = _exportCode + format ['[_fortification, %1, %2] call BIS_fnc_setPitchBank;%3%3', _exportData select 3, _exportData select 4, NEW_LINE];

    _exportCode;
};