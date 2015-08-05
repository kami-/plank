#include "plank_macros.h"

#include "\userconfig\plank\log\deploy.h"
#include "logbook.h"

plank_deploy_fnc_preInit = {
    FORTS_DATA = [[FORT_COMBO_NONE_NAME, "", 0, 0, 0, {}]];
    PUSH_ALL(FORTS_DATA,plank_deploy_manualFortData);
};

plank_deploy_fnc_getLabelToFortMapping = {
    FUN_ARGS_1(_unit);

    private ["_mapping", "_fortCounts"];
    _mapping = [];
    _fortCounts = _unit getVariable ["plank_deploy_fortCounts", []];
    {
        if (_x > 0) then { PUSH(_mapping,_forEachIndex); };
    } foreach _fortCounts;

    _mapping;
};

plank_deploy_fnc_setFortDirection = {
    FUN_ARGS_3(_unit,_fort,_fortIndex);

    private "_direction";
    _direction = _unit getVariable ["plank_deploy_fortDirection", GET_FORT_DIRECTION(_fortIndex)];
    _fort setDir ((getDir _unit) + _direction);
};

plank_deploy_fnc_setFortPosition = {
    FUN_ARGS_2(_unit,_fort);

    private ["_heightMode", "_newPostion"];
    _heightMode = _unit getVariable ["plank_deploy_heightMode", RELATIVE_TO_UNIT];
    _newPostion = _unit modelToWorld [player getVariable ["plank_deploy_fortHorizontalOffset", 0], [_unit] call plank_deploy_fnc_getFortDistance, 0];
    call {
        if (_heightMode == RELATIVE_TO_TERRAIN) exitWith {
            _newPostion set [2, 0];
            _fort setPos _newPostion;
        };
        if (_heightMode == RELATIVE_TO_UNIT) exitWith {
            _newPostion set [2, ((getPosASL _unit) select 2) + (_unit getVariable ["plank_deploy_fortRelativeHeight", 0])];
            _fort setPosASL _newPostion;
        };
    };
};

plank_deploy_fnc_setFortVariables = {
    FUN_ARGS_11(_unit,_fortIndex,_fort,_horizontalOffset,_relativeHeight,_direction,_distance,_pitch,_bank,_heightMode,_lockMode);

    _unit setVariable ["plank_deploy_fortIndex", _fortIndex, false];
    // TODO: Hacky, should refactor to all variables
    if (isNil {_fort}) then {
        _unit setVariable ["plank_deploy_fort", nil, false];
    } else {
        _unit setVariable ["plank_deploy_fort", _fort, false];
    };
    _unit setVariable ["plank_deploy_fortHorizontalOffset", _horizontalOffset, false];
    _unit setVariable ["plank_deploy_fortRelativeHeight", _relativeHeight, false];
    _unit setVariable ["plank_deploy_fortDirection", _direction, false];
    _unit setVariable ["plank_deploy_fortDistance", _distance, false];
    _unit setVariable ["plank_deploy_fortPitch", _pitch, false];
    _unit setVariable ["plank_deploy_fortBank", _bank, false];
    _unit setVariable ["plank_deploy_heightMode", _heightMode, false];
    _unit setVariable ["plank_deploy_lockMode", _lockMode, false];
};

plank_deploy_fnc_setFortPitchAndBank = {
    FUN_ARGS_2(_unit,_fort);

    [_fort, _unit getVariable ["plank_deploy_fortPitch", 0], _unit getVariable ["plank_deploy_fortBank", 0]] call BIS_fnc_setPitchBank;
};

plank_deploy_fnc_getFortDistance = {
    FUN_ARGS_1(_unit);

    _unit getVariable ["plank_deploy_fortDistance", GET_FORT_DISTANCE((_unit getVariable "plank_deploy_fortIndex"))];
};

plank_deploy_fnc_createFortification = {
    FUN_ARGS_2(_unit,_fortIndex);

    private "_fort";
    _fort = createVehicle [GET_FORT_CLASS_NAME(_fortIndex), [0,0,0], [], 0, "NONE"];
    [_unit, _fortIndex, _fort, 0, 0, GET_FORT_DIRECTION(_fortIndex), GET_FORT_DISTANCE(_fortIndex), 0, 0, RELATIVE_TO_UNIT, LOCK_MODE_UNLOCKED] call plank_deploy_fnc_setFortVariables;
    [_unit, _fort, _fortIndex] call plank_deploy_fnc_setFortDirection;
    [_unit, _fort] call plank_deploy_fnc_setFortPosition;

    _fort;
};

plank_deploy_fnc_addPlankActions = {
    FUN_ARGS_1(_unit);

    DECLARE(_plankActionId) = _unit addAction ['<t color="#3748E3">Plank</t>', ADDON_PATH(plank_action.sqf), [], 100, false, false, "", "driver _target == _this"];
    _unit setVariable ["plank_deploy_plankActionId", _plankActionId, false];
};

plank_deploy_fnc_removePlankAction = {
    FUN_ARGS_1(_unit);

    DECLARE(_actionId) = _unit getVariable "plank_deploy_plankActionId";
    if (!isNil {_actionId}) then {
        _unit removeAction _actionId;
    };
};

plank_deploy_fnc_updateFortPlacement = {
    FUN_ARGS_1(_unit);

    waitUntil {
        private ["_fort", "_fortIndex", "_lockMode"];
        _fort = _unit getVariable "plank_deploy_fort";
        _fortIndex = _unit getVariable "plank_deploy_fortIndex";
        _lockMode = _unit getVariable ["plank_deploy_lockMode", LOCK_MODE_UNLOCKED];
        if (!isNil {_fort} && {!isNil {_fortIndex}} && {_lockMode == LOCK_MODE_UNLOCKED}) then {
            [_unit, _fort, _fortIndex] call plank_deploy_fnc_setFortDirection;
            [_unit, _fort] call plank_deploy_fnc_setFortPosition;
            [_unit, _fort] call plank_deploy_fnc_setFortPitchAndBank;
        };

        _unit getVariable ["plank_deploy_placementState", STATE_PLACEMENT_INIT] != STATE_PLACEMENT_IN_PROGRESS;
    };
};

plank_deploy_fnc_tryStartFortPlacement = {
    FUN_ARGS_2(_unit,_fortIndex);

    DECLARE(_currentFortIndex) = _unit getVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX];
    if (_currentFortIndex != _fortIndex) then {
        [_unit] call plank_deploy_fnc_cancelFortPlacement;
        [_unit, _fortIndex] spawn plank_deploy_fnc_startFortPlacement;
    };
};

plank_deploy_fnc_startFortPlacement = {
    FUN_ARGS_2(_unit,_fortIndex);

    _unit setVariable ["plank_deploy_fortIndex", _fortIndex, false];
    _unit setVariable ["plank_deploy_placementState", STATE_PLACEMENT_IN_PROGRESS, false];
    [_unit, _fortIndex] call plank_deploy_fnc_createFortification;
    [] call plank_ui_fnc_initFortControls;
    [_unit] call plank_deploy_fnc_updateFortPlacement;
};

plank_deploy_fnc_cancelFortPlacement = {
    FUN_ARGS_1(_unit);

    _unit setVariable ["plank_deploy_placementState", STATE_PLACEMENT_CANCELLED, false];
    [_unit] call plank_deploy_fnc_deleteFort;
};

plank_deploy_fnc_confirmFortPlacement = {
    FUN_ARGS_1(_unit);

    DECLARE(_fort) = _unit getVariable "plank_deploy_fort";
    _unit setVariable ["plank_deploy_placementState", STATE_PLACEMENT_DONE, false];
    [_unit] call plank_deploy_fnc_decreaseFortCount;
    [_unit, _fort] call plank_export_fnc_addFort;
    [_unit, _fort] call GET_FORT_CODE(_unit getVariable "plank_deploy_fortIndex");
    [_unit] call plank_deploy_fnc_resetFort;
};

plank_deploy_fnc_deleteFort = {
    FUN_ARGS_1(_unit);

    DECLARE(_fort) = _unit getVariable "plank_deploy_fort";
    if (!isNil {_fort}) then {
        deleteVehicle _fort;
    };
    [_unit] call plank_deploy_fnc_resetFort;
};

plank_deploy_fnc_resetFort = {
    FUN_ARGS_1(_unit);

    [_unit, DEFAULT_FORT_INDEX, nil, DEFAULT_HORIZONTAL_OFFSET, DEFAULT_HEIGHT, DEFAULT_DIRECTION, DEFAULT_DISTANCE, DEFAULT_PITCH, DEFAULT_BANK, RELATIVE_TO_UNIT, LOCK_MODE_UNLOCKED] call plank_deploy_fnc_setFortVariables;
};

plank_delpoy_fnc_forceRemoveAllFortifications = {
    FUN_ARGS_1(_unit);

    [] call plank_ui_fnc_closeSettingsDialog;
    _unit setVariable ["plank_deploy_placementState", STATE_PLACEMENT_CANCELLED, false];
    [_unit] call plank_deploy_fnc_removePlankAction;
    [_unit] call plank_deploy_fnc_deleteFort;
    _unit setVariable ["plank_deploy_fortCounts", nil, false];
};

plank_deploy_fnc_decreaseFortCount = {
    FUN_ARGS_1(_unit);

    private ["_fortIndex", "_fortCounts"];
    _fortIndex = _unit getVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX];
    _fortCounts = _unit getVariable ["plank_deploy_fortCounts", []];
    if (_fortIndex != DEFAULT_FORT_INDEX && {count _fortCounts >= _fortIndex}) then {
        _fortCounts set [_fortIndex, (_fortCounts select _fortIndex) - 1];
        if ([_unit] call plank_deploy_fnc_isFortsCountEmpty) then {
            [_unit] call plank_delpoy_fnc_forceRemoveAllFortifications;
        };
    };
};

plank_deploy_fnc_isFortsCountEmpty = {
    FUN_ARGS_1(_unit);

    private ["_isFortsCountEmpty", "_fortCounts"];
    _isFortsCountEmpty = true;
    _fortCounts = _unit getVariable ["plank_deploy_fortCounts", []];
    for "_i" from 1 to (count _fortCounts) - 1 do {
        if (_fortCounts select _i > 0) exitWith { _isFortsCountEmpty = false; };
    };

    _isFortsCountEmpty;
};

plank_deploy_fnc_initUnitVariables = {
    FUN_ARGS_2(_unit,_fortifications);

    private "_fortActionIds";
    _fortActionIds = [];
    _fortActionIds set [(count _fortifications) - 1, nil];
    _unit setVariable ["plank_deploy_fortActionIds", _fortActionIds, false];
    _unit setVariable ["plank_deploy_fortCounts", [_fortifications] call plank_deploy_fnc_shiftFortifications, false];
    [_unit] call plank_deploy_fnc_resetFort;
};

plank_deploy_fnc_shiftFortifications = {
    FUN_ARGS_1(_fortifications);

    DECLARE(_shifted) = [1];
    {
        PUSH(_shifted,_x);
    } foreach _fortifications;

    _shifted;
};

plank_deploy_fnc_init = {
    FUN_ARGS_2(_unit,_fortifications);

    [_unit] call plank_delpoy_fnc_forceRemoveAllFortifications;
    [_unit, _fortifications] call plank_deploy_fnc_initUnitVariables;
    [_unit] call plank_deploy_fnc_addPlankActions;
};