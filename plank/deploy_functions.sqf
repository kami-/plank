#include "plank_macros.h"

#include "\userconfig\plank\log\deploy.h"
#include "logbook.h"

plank_deploy_fnc_preInit = {
    FORTS_DATA = [[FORT_COMBO_NONE_NAME, "", 0, 0, 0, ""]];
    private _configForts = ["fortifications"] call plank_config_fnc_getBothArray;
    PUSH_ALL(FORTS_DATA,_configForts);
};

plank_deploy_fnc_expandFortCounts = {
    FUN_ARGS_1(_unit);

    _fortCounts = _unit getVariable ["plank_deploy_fortCounts", [1]];
    DECLARE(_shifted) = [1];
    {
        PUSH(_shifted,_x);
    } foreach FORTS_DATA;
};

plank_deploy_fnc_getNonZeroFortIndexes = {
    FUN_ARGS_1(_unit);

    private ["_fortIndexes", "_fortCounts"];
    _fortIndexes = [];
    _fortCounts = _unit getVariable ["plank_deploy_fortCounts", [1]];
    {
        if (_x > 0) then { PUSH(_fortIndexes,_forEachIndex); };
    } foreach _fortCounts;

    _fortIndexes;
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

plank_deploy_fnc_addPlankAction = {
    FUN_ARGS_1(_unit);

    if (isNil {_unit getVariable "plank_deploy_plankActionId"}) then {
        DECLARE(_plankActionId) = _unit addAction ['<t color="#3748E3">Plank</t>', ADDON_PATH(plank_action.sqf), [], 100, false, false, "", "driver _target == _this"];
        _unit setVariable ["plank_deploy_plankActionId", _plankActionId, false];
    };
};

plank_deploy_fnc_removePlankAction = {
    FUN_ARGS_1(_unit);

    DECLARE(_actionId) = _unit getVariable "plank_deploy_plankActionId";
    if (!isNil {_actionId}) then {
        _unit removeAction _actionId;
        _unit setVariable ["plank_deploy_plankActionId", nil, false];
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

    private ["_fort", "_fortIndex"];
    _fort = _unit getVariable ["plank_deploy_fort", DEFAULT_FORT_INDEX];
    _fortIndex = _unit getVariable "plank_deploy_fortIndex";
    _unit setVariable ["plank_deploy_placementState", STATE_PLACEMENT_DONE, false];
    [_unit, _fort] call plank_export_fnc_addFort;
    [_unit, _fort] call compile GET_FORT_CODE(_fortIndex);
    _fort setVariable ["plank_deploy_placedByData", [_unit, _fortIndex], false];
    [_unit, _fortIndex, 1] call plank_deploy_fnc_decreaseFortCount;
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

plank_deploy_fnc_pickupObject = {
    FUN_ARGS_2(_unit,_object);

    DECLARE(_placedByData) = _object getVariable ["plank_deploy_placedByData", [objNull, 0]];
    if (_placedByData select 0 == _unit) then {
        [_unit, _placedByData select 1, 1] call plank_deploy_fnc_addFortification;
        deleteVehicle _object;
    };
};

plank_deploy_fnc_canPickupObject = {
    FUN_ARGS_2(_unit,_object);

    DECLARE(_canPickup) = false;
    if (!isNull _object) then {
        DECLARE(_placedByData) = _object getVariable ["plank_deploy_placedByData", [objNull, 0]];
        _canPickup = _placedByData select 0 == _unit;
    };

    _canPickup
};

plank_delpoy_fnc_forceRemoveAllFortifications = {
    FUN_ARGS_1(_unit);

    [_unit] call plank_deploy_fnc_forceResetPlacement;
    [_unit] call plank_deploy_fnc_removePlankAction;
    _unit setVariable ["plank_deploy_fortCounts", [1], false];
};

plank_deploy_fnc_forceResetPlacement = {
    FUN_ARGS_1(_unit);

    [] call plank_ui_fnc_closeSettingsDialog;
    _unit setVariable ["plank_deploy_placementState", STATE_PLACEMENT_CANCELLED, false];
    _unit setVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX, false];
    [_unit] call plank_deploy_fnc_deleteFort;
};

plank_deploy_fnc_decreaseFortCount = {
    FUN_ARGS_3(_unit,_fortIndex,_count);

    DECLARE(_fortCounts) = _unit getVariable ["plank_deploy_fortCounts", [1]];
    if (_fortIndex > DEFAULT_FORT_INDEX && {count _fortCounts > _fortIndex} && {_fortCounts select _fortIndex > 0}) then {
        _fortCounts set [_fortIndex, ((_fortCounts select _fortIndex) - _count) max 0];
        if ([_unit] call plank_deploy_fnc_isFortsCountEmpty) then {
            [_unit] spawn plank_delpoy_fnc_forceRemoveAllFortifications;
        };
    };
};

plank_deploy_fnc_isFortsCountEmpty = {
    FUN_ARGS_1(_unit);

    private ["_isFortsCountEmpty", "_fortCounts"];
    _isFortsCountEmpty = true;
    _fortCounts = _unit getVariable ["plank_deploy_fortCounts", [1]];
    for "_i" from 1 to (count _fortCounts) - 1 do {
        if (_fortCounts select _i > 0) exitWith { _isFortsCountEmpty = false; };
    };

    _isFortsCountEmpty;
};

plank_deploy_fnc_initUnitVariables = {
    FUN_ARGS_2(_unit,_fortifications);

    _unit setVariable ["plank_deploy_plankActionId", nil, false];
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

plank_deploy_fnc_initFortCounts = {
    FUN_ARGS_1(_unit);

    DECLARE(_fortCounts) = _unit getVariable ["plank_deploy_fortCounts", [1]];
    for "_i" from 1 to (count FORTS_DATA - count _fortCounts) do {
        PUSH(_fortCounts,0);
    };
    _unit setVariable ["plank_deploy_fortCounts", _fortCounts, false];
};

plank_deploy_fnc_getDistanceFromBoundingBox = {
    FUN_ARGS_1(_className);

    private ["_object", "_boundingBox", "_maxWidth", "_maxLength"];
    _object = _className createVehicleLocal [-100, -100, 100];
    _boundingBox = boundingBox _object;
    _maxWidth = abs ((_boundingBox select 1 select 0) - (_boundingBox select 0 select 0));
    _maxLength = abs ((_boundingBox select 1 select 1) - (_boundingBox select 0 select 1));
    deleteVehicle _object;

    _maxWidth max _maxLength;
};

plank_deploy_fnc_getFortifications = {
    DECLARE(_forts) = [];
    for "_i" from 1 to (count FORTS_DATA) - 1 do {
        DECLARE(_fortNameAndIndex) = [FORTS_DATA select _i select 0, _i];
        PUSH(_forts,_fortNameAndIndex);
    };

    _forts;
};

plank_deploy_fnc_addNewFortification = {
    FUN_ARGS_2(_unit,_forData);

    private ["_index", "_fortCounts"];
    _index = count FORTS_DATA;
    _fortCounts = _unit getVariable ["plank_deploy_fortCounts", [1]];
    [_unit] call plank_deploy_fnc_initFortCounts;
    PUSH(FORTS_DATA,_forData);
    PUSH(_fortCounts,0);

    _index;
};

plank_deploy_fnc_addNewDefaultFortificationWithDistance = {
    FUN_ARGS_4(_unit,_className,_distance,_displayName);

    DECLARE(_actualDisplayName) = _displayName;
    if (isNil {_displayName}) then {
        _actualDisplayName = _className;
    };

    [_unit, [_actualDisplayName, _className, _distance, 0, 360, ""]] call plank_deploy_fnc_addNewFortification;
};

plank_deploy_fnc_addNewDefaultFortification = {
    FUN_ARGS_3(_unit,_className,_displayName);

    [_unit, _className, 12, _displayName] call plank_deploy_fnc_addNewDefaultFortificationWithDistance;
};

plank_deploy_fnc_addNewBoundingFortification = {
    FUN_ARGS_3(_unit,_className,_displayName);

    [_unit, _className, [_className] call plank_deploy_fnc_getDistanceFromBoundingBox, _displayName] call plank_deploy_fnc_addNewDefaultFortificationWithDistance;
};

plank_deploy_fnc_addFortification = {
    FUN_ARGS_3(_unit,_fortIndex,_count);

    if (_fortIndex > 0 && {_fortIndex < count FORTS_DATA}) then {
        [_unit] call plank_deploy_fnc_initFortCounts;
        DECLARE(_fortCounts) = _unit getVariable ["plank_deploy_fortCounts", [1]];
        _fortCounts set [_fortIndex, (_fortCounts select _fortIndex) + _count];
        [] call plank_ui_fnc_initFortCombo;
        [_unit] call plank_deploy_fnc_addPlankAction;
    };
};

plank_deploy_fnc_removeFortification = {
    FUN_ARGS_3(_unit,_fortIndex,_count);

    DECLARE(_fortCounts) = _unit getVariable ["plank_deploy_fortCounts", [1]];
    if (_fortIndex > 0 && {_fortIndex < count FORTS_DATA} && {_fortIndex < count _fortCounts} && {_fortCounts select _fortIndex > 0}) then {
        DECLARE(_newCount) = ((_fortCounts select _fortIndex) - _count) max 0;
        _fortCounts set [_fortIndex, _newCount];
        if ([_unit] call plank_deploy_fnc_isFortsCountEmpty) then {
            [_unit] call plank_delpoy_fnc_forceRemoveAllFortifications;
        } else {
            if (_newCount == 0) then {
                [] call plank_ui_fnc_selectNone;
            };
            [] call plank_ui_fnc_initFortCombo;
        };
    };
};

plank_deploy_fnc_forceAddFortifications = {
    FUN_ARGS_2(_unit,_fortifications);

    [_unit] call plank_delpoy_fnc_forceRemoveAllFortifications;
    [_unit, _fortifications] call plank_deploy_fnc_initUnitVariables;
    [_unit] call plank_deploy_fnc_addPlankAction;
};