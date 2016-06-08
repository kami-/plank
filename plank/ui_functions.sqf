#include "plank_macros.h"

#include "\userconfig\plank\log\ui.h"
#include "logbook.h"

#define LOCK_SHORTCUT_KEY_CODE                  33 // F
#define PICKUP_SHORTCUT_KEY_CODE                32 // D
#define CONFIRM_SHORTCUT_KEY_CODE               19 // R
#define CANCEL_SHORTCUT_KEY_CODE                16 // Q
#define VERTICAL_MODE_SHORTCUT_KEY_CODE         47 // V

plank_ui_fnc_createSettingsDialog = {
    if (!dialog) then {
        private "_isDialogCreated";
        _isDialogCreated = createDialog "PlankSettingsDialog";
        if (_isDialogCreated) then {
            [] call plank_ui_fnc_initDialog;
        };
    };
};

plank_ui_fnc_isDialogOpen = {
    !isNull findDisplay SETTINGS_DIALOG_IDD;
};

plank_ui_fnc_closeSettingsDialog = {
    if ([] call plank_ui_fnc_isDialogOpen) then {
        closeDialog 0;
    };
};

plank_ui_fnc_resetHeightSlider = {
    sliderSetPosition [SETTINGS_HEIGHT_SLIDER_IDC, 0];
    [0] call plank_ui_fnc_updateHeightSliderValue;
};

plank_ui_fnc_resetHorizontalOffsetSlider = {
    sliderSetPosition [SETTINGS_HORIZONTAL_OFFSET_SLIDER_IDC, 0];
    [0] call plank_ui_fnc_updateHorizontalOffsetSliderValue;
};

plank_ui_fnc_resetDirectionSlider = {
    private "_fortDirection";
    _fortDirection = GET_FORT_DIRECTION(player getVariable "plank_deploy_fortIndex");
    sliderSetPosition [SETTINGS_DIRECTION_SLIDER_IDC, _fortDirection];
    [_fortDirection] call plank_ui_fnc_updateDirectiontSliderValue;
};

plank_ui_fnc_resetDistanceSlider = {
    private "_fortDistance";
    _fortDistance = GET_FORT_DISTANCE((player getVariable "plank_deploy_fortIndex"));
    sliderSetPosition [SETTINGS_DISTANCE_SLIDER_IDC, _fortDistance];
    [_fortDistance] call plank_ui_fnc_updateDistanceSliderValue;
};

plank_ui_fnc_resetPitchSlider = {
    sliderSetPosition [SETTINGS_PITCH_SLIDER_IDC, 0];
    [0] call plank_ui_fnc_updatePitchSliderValue;
};

plank_ui_fnc_resetBankSlider = {
    sliderSetPosition [SETTINGS_BANK_SLIDER_IDC, 0];
    [0] call plank_ui_fnc_updateBankSliderValue;
};

plank_ui_fnc_exportButtonClick = {
    [] call plank_api_fnc_export;
};

plank_ui_fnc_pickupButtonClick = {
    [player, cursorTarget] call plank_deploy_fnc_pickupObject;
};

plank_ui_fnc_heightModeButtonClick = {
    DECLARE(_heightMode) = player getVariable ["plank_deploy_heightMode", RELATIVE_TO_UNIT];
    call {
        if (_heightMode == RELATIVE_TO_TERRAIN) exitWith {
            _heightMode = RELATIVE_TO_UNIT;
        };
        if (_heightMode == RELATIVE_TO_UNIT) exitWith {
            _heightMode = RELATIVE_TO_TERRAIN;
        };
    };
    [_heightMode] call plank_ui_fnc_setHeightModeButton;
};

plank_ui_fnc_setHeightModeButton = {
    FUN_ARGS_1(_heightMode);

    player setVariable ["plank_deploy_heightMode", _heightMode, false];
};

plank_ui_fnc_lockModeButtonClick = {
    DECLARE(_lockMode) = player getVariable ["plank_deploy_lockMode", LOCK_MODE_UNLOCKED];
    call {
        if (_lockMode == LOCK_MODE_UNLOCKED) exitWith {
            _lockMode = LOCK_MODE_LOCKED;
            [] call plank_ui_fnc_initFortControls;
        };
        if (_lockMode == LOCK_MODE_LOCKED) exitWith {
            _lockMode = LOCK_MODE_UNLOCKED;
            [] call plank_ui_fnc_initFortControls;
        };
    };
    [_lockMode] call plank_ui_fnc_setLockModeButton;
};

plank_ui_fnc_setLockModeButton = {
    FUN_ARGS_1(_lockMode);

    player setVariable ["plank_deploy_lockMode", _lockMode, false];
    ctrlSetText [SETTINGS_LOCK_MODE_BUTTON_IDC, STR_LOCK_MODES select _lockMode];
};

plank_ui_fnc_confirmButtonClick = {
    DECLARE(_fortIndex) = player getVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX];
    if (_fortIndex != DEFAULT_FORT_INDEX) then {
        [player] call plank_deploy_fnc_confirmFortPlacement;
        [] call plank_ui_fnc_initFortControls;
        [] call plank_ui_fnc_resetFortCombo;
    };
};

plank_ui_fnc_cancelButtonClick = {
    [player] call plank_deploy_fnc_cancelFortPlacement;
    [] call plank_ui_fnc_initFortControls;
    [] call plank_ui_fnc_resetFortCombo;
};

plank_ui_fnc_updateHeightSliderValue = {
    FUN_ARGS_1(_value);

    [SETTINGS_HEIGHT_VALUE_IDC, "plank_deploy_fortRelativeHeight", _value] call plank_ui_fnc_updateValue;
};

plank_ui_fnc_updateHorizontalOffsetSliderValue = {
    FUN_ARGS_1(_value);

    [SETTINGS_HORIZONTAL_OFFSET_VALUE_IDC, "plank_deploy_fortHorizontalOffset", _value] call plank_ui_fnc_updateValue;
};

plank_ui_fnc_updateDirectiontSliderValue = {
    FUN_ARGS_1(_value);

    [SETTINGS_DIRECTION_VALUE_IDC, "plank_deploy_fortDirection", _value] call plank_ui_fnc_updateValue;
};

plank_ui_fnc_updateDistanceSliderValue = {
    FUN_ARGS_1(_value);

    [SETTINGS_DISTANCE_VALUE_IDC, "plank_deploy_fortDistance", _value] call plank_ui_fnc_updateValue;
};

plank_ui_fnc_updatePitchSliderValue = {
    FUN_ARGS_1(_value);

    [SETTINGS_PITCH_VALUE_IDC, "plank_deploy_fortPitch", _value] call plank_ui_fnc_updateValue;
};

plank_ui_fnc_updateBankSliderValue = {
    FUN_ARGS_1(_value);

    [SETTINGS_BANK_VALUE_IDC, "plank_deploy_fortBank", _value] call plank_ui_fnc_updateValue;
};

plank_ui_fnc_updateValue = {
    FUN_ARGS_3(_idc,_varName,_value);

    if (player getVariable ["plank_deploy_lockMode", LOCK_MODE_UNLOCKED] == LOCK_MODE_UNLOCKED) then {
        ctrlSetText [_idc, str _value];
        player setVariable [_varName, _value, false]
    };
};

plank_ui_fnc_initToggleValues = {
    plank_ui_isLeftClickHeld = false;
    plank_ui_isRotationButtonHeld = false;
};

plank_ui_fnc_initSliders = {
    DECLARE(_fortIndex) = player getVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX];
    sliderSetRange [SETTINGS_HEIGHT_SLIDER_IDC, MIN_HEIGHT, MAX_HEIGHT];
    sliderSetRange [SETTINGS_HORIZONTAL_OFFSET_SLIDER_IDC, MIN_HORIZONTAL_OFFSET, MAX_HORIZONTAL_OFFSET];
    sliderSetRange [
        SETTINGS_DIRECTION_SLIDER_IDC,
        GET_FORT_DIRECTION(_fortIndex) - GET_FORT_DIRECTION_RANGE(_fortIndex) / 2,
        GET_FORT_DIRECTION(_fortIndex) + GET_FORT_DIRECTION_RANGE(_fortIndex) / 2
    ];
    sliderSetRange [SETTINGS_DISTANCE_SLIDER_IDC, GET_FORT_DISTANCE(_fortIndex), GET_FORT_DISTANCE(_fortIndex) + MAX_DISTANCE_ADD];
    sliderSetRange [SETTINGS_PITCH_SLIDER_IDC, MIN_PITCH, MAX_PITCH];
    sliderSetRange [SETTINGS_BANK_SLIDER_IDC, MIN_BANK, MAX_BANK];
};

plank_ui_fnc_initSliderValues = {
    DECLARE(_fortIndex) = player getVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX];
    sliderSetPosition [SETTINGS_HEIGHT_SLIDER_IDC, player getVariable ["plank_deploy_fortRelativeHeight", DEFAULT_HEIGHT]];
    sliderSetPosition [SETTINGS_HORIZONTAL_OFFSET_SLIDER_IDC, player getVariable ["plank_deploy_fortHorizontalOffset", DEFAULT_HORIZONTAL_OFFSET]];
    sliderSetPosition [SETTINGS_PITCH_SLIDER_IDC, player getVariable ["plank_deploy_fortPitch", DEFAULT_PITCH]];
    sliderSetPosition [SETTINGS_BANK_SLIDER_IDC, player getVariable ["plank_deploy_fortBank", DEFAULT_BANK]];
    sliderSetPosition [SETTINGS_DIRECTION_SLIDER_IDC, player getVariable ["plank_deploy_fortDirection", GET_FORT_DIRECTION(_fortIndex)]];
    sliderSetPosition [SETTINGS_DISTANCE_SLIDER_IDC, player getVariable ["plank_deploy_fortDistance", GET_FORT_DISTANCE(_fortIndex)]];
};

plank_ui_fnc_initSliderTextValues = {
    DECLARE(_fortIndex) = player getVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX];
    ctrlSetText [SETTINGS_HEIGHT_VALUE_IDC, str (player getVariable ["plank_deploy_fortRelativeHeight", DEFAULT_HEIGHT])];
    ctrlSetText [SETTINGS_HORIZONTAL_OFFSET_VALUE_IDC, str (player getVariable ["plank_deploy_fortHorizontalOffset", DEFAULT_HORIZONTAL_OFFSET])];
    ctrlSetText [SETTINGS_PITCH_VALUE_IDC, str (player getVariable ["plank_deploy_fortPitch", DEFAULT_PITCH])];
    ctrlSetText [SETTINGS_BANK_VALUE_IDC, str (player getVariable ["plank_deploy_fortBank", DEFAULT_BANK])];
    ctrlSetText [SETTINGS_DIRECTION_VALUE_IDC, str (player getVariable ["plank_deploy_fortDirection", GET_FORT_DIRECTION(_fortIndex)])];
    ctrlSetText [SETTINGS_DISTANCE_VALUE_IDC, str (player getVariable ["plank_deploy_fortDistance", GET_FORT_DIRECTION(_fortIndex)])];
};

plank_ui_fnc_initFortCombo = {
    if ([] call plank_ui_fnc_isDialogOpen) then {
        lbClear SETTINGS_FORT_COMBO_IDC;
        [] call plank_ui_fnc_addFortificationLabels;
    };
};

plank_ui_fnc_selectNone = {
    DECLARE(_index) = [DEFAULT_FORT_INDEX] call plank_ui_fnc_getComboIndexByFortIndex;
    lbSetCurSel [SETTINGS_FORT_COMBO_IDC, _index];
};

plank_ui_fnc_getComboIndexByFortIndex = {
    FUN_ARGS_1(_fortIndex);

    DECLARE(_index) = 0;
    for "_i" from 0 to (lbSize SETTINGS_FORT_COMBO_IDC) - 1 do {
        if (lbValue [SETTINGS_FORT_COMBO_IDC, _i] == _fortIndex) exitWith { _index = _i; };
    };

    _index;
};

plank_ui_fnc_resetFortCombo = {
    [] call plank_ui_fnc_initFortCombo;
    DECLARE(_index) = [player getVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX]] call plank_ui_fnc_getComboIndexByFortIndex;
    lbSetCurSel [SETTINGS_FORT_COMBO_IDC, _index];
};

plank_ui_fnc_addFortificationLabel = {
    FUN_ARGS_2(_fortIndex,_fortCount);

    private ["_label", "_index"];
    _label = FORT_COMBO_NONE_NAME;
    if (_fortIndex != DEFAULT_FORT_INDEX) then {
        _label = format ["%1x %2", _fortCount, GET_FORT_DISPLAY_NAME(_fortIndex)];
    };
    _index = lbAdd [SETTINGS_FORT_COMBO_IDC, _label];
    lbSetValue [SETTINGS_FORT_COMBO_IDC, _index, _fortIndex];
};

plank_ui_fnc_addFortificationLabels = {
    private ["_fortIndexes", "_fortCounts"];
    _fortIndexes = [player] call plank_deploy_fnc_getNonZeroFortIndexes;
    _fortCounts = player getVariable ["plank_deploy_fortCounts", []];
    {
        [_x, _fortCounts select _x] call plank_ui_fnc_addFortificationLabel;
    } foreach _fortIndexes;
};

plank_ui_fnc_selectionChanged = {
    FUN_ARGS_2(_control,_index);

    if (_index > 0) then {
        [player, lbValue [SETTINGS_FORT_COMBO_IDC, _index]] call plank_deploy_fnc_tryStartFortPlacement;
    } else {
        [player] call plank_deploy_fnc_cancelFortPlacement;
    };
};

plank_ui_fnc_updateValueAndSlider = {
    FUN_ARGS_6(_value,_minValue,_maxValue,_varName,_sliderIdc,_valueIdc);

    if (player getVariable ["plank_deploy_lockMode", LOCK_MODE_UNLOCKED] == LOCK_MODE_UNLOCKED) then {
        DECLARE(_newValue) = (player getVariable _varName) + _value;
        _newValue = (_newValue max _minValue) min _maxValue;
        [_valueIdc, _varName, _newValue] call plank_ui_fnc_updateValue;
        sliderSetPosition [_sliderIdc, _newValue];
    };
};

plank_ui_fnc_onKeyDown = {
    FUN_ARGS_5(_control,_keyCode,_shift,_ctrl,_alt);

    plank_ui_isRotationButtonHeld = _shift || {_ctrl} || {_alt};

    false;
};

plank_ui_fnc_onKeyUp = {
    FUN_ARGS_5(_control,_keyCode,_shift,_ctrl,_alt);

    call {
        if (_keyCode == LOCK_SHORTCUT_KEY_CODE) exitWith { [] call plank_ui_fnc_lockModeButtonClick; };
        if (_keyCode == PICKUP_SHORTCUT_KEY_CODE) exitWith { [] call plank_ui_fnc_pickupButtonClick; };
        if (_keyCode == CONFIRM_SHORTCUT_KEY_CODE) exitWith { [] call plank_ui_fnc_confirmButtonClick; };
        if (_keyCode == CANCEL_SHORTCUT_KEY_CODE) exitWith { [] call plank_ui_fnc_cancelButtonClick; };
        if (_keyCode == VERTICAL_MODE_SHORTCUT_KEY_CODE) exitWith { [] call plank_ui_fnc_heightModeButtonClick; };
        if ((_keyCode == 42 && {_shift} && {!_ctrl} && {!_alt})
            || {_keyCode == 29 && {!_shift} && {_ctrl} && {!_alt}}
            || {_keyCode == 56 && {!_shift} && {!_ctrl} && {_alt}}) exitWith {
            plank_ui_isRotationButtonHeld = false;
        };
    };

    false;
};

plank_ui_fnc_onMouseButtonDown = {
    FUN_ARGS_7(_control,_button,_x,_y,_shift,_ctrl,_alt);

    plank_ui_isLeftClickHeld = _button == 0;

    false;
};

plank_ui_fnc_onMouseButtonUp = {
    FUN_ARGS_7(_control,_button,_x,_y,_shift,_ctrl,_alt);

    if (_button == 0) then {
        plank_ui_isLeftClickHeld = false;
    };

    false;
};

plank_ui_fnc_onMouseMoving = {
    FUN_ARGS_3(_display,_deltaX,_deltaY);

    if (!plank_ui_isLeftClickHeld) exitWith {};
    if (plank_ui_isRotationButtonHeld) then {
        [_deltaY / PLANK_PITCH_SENSITIVITY, MIN_PITCH, MAX_PITCH, "plank_deploy_fortPitch", SETTINGS_PITCH_SLIDER_IDC, SETTINGS_PITCH_VALUE_IDC] call plank_ui_fnc_updateValueAndSlider;
        [_deltaX / PLANK_BANK_SENSITIVITY, MIN_BANK, MAX_BANK, "plank_deploy_fortBank", SETTINGS_BANK_SLIDER_IDC, SETTINGS_BANK_VALUE_IDC] call plank_ui_fnc_updateValueAndSlider;
    } else {
        [-_deltaY / PLANK_HEIGHT_SENSITIVITY, MIN_HEIGHT, MAX_HEIGHT, "plank_deploy_fortRelativeHeight", SETTINGS_HEIGHT_SLIDER_IDC, SETTINGS_HEIGHT_VALUE_IDC] call plank_ui_fnc_updateValueAndSlider;
        [_deltaX / PLANK_HORIZONTAL_SENSITIVITY, MIN_HORIZONTAL_OFFSET, MAX_HORIZONTAL_OFFSET, "plank_deploy_fortHorizontalOffset", SETTINGS_HORIZONTAL_OFFSET_SLIDER_IDC, SETTINGS_HORIZONTAL_OFFSET_VALUE_IDC] call plank_ui_fnc_updateValueAndSlider;
    };
};

plank_ui_fnc_onMouseZChanged = {
    FUN_ARGS_2(_display,_deltaY);

    if (plank_ui_isRotationButtonHeld) then {
        private ["_fortIndex", "_baseDirection"];
        _fortIndex = player getVariable "plank_deploy_fortIndex";
        _baseDirection = GET_FORT_DIRECTION(_fortIndex);
        [
            _deltaY * 2,
            _baseDirection - GET_FORT_DIRECTION_RANGE(_fortIndex) / 2,
            _baseDirection + GET_FORT_DIRECTION_RANGE(_fortIndex) / 2,
            "plank_deploy_fortDirection",
            SETTINGS_DIRECTION_SLIDER_IDC,
            SETTINGS_DIRECTION_VALUE_IDC
        ] call plank_ui_fnc_updateValueAndSlider;
    } else {
        DECLARE(_minDistance) = GET_FORT_DISTANCE(player getVariable "plank_deploy_fortIndex");
        [_deltaY, _minDistance, _minDistance + MAX_DISTANCE_ADD, "plank_deploy_fortDistance", SETTINGS_DISTANCE_SLIDER_IDC, SETTINGS_DISTANCE_VALUE_IDC] call plank_ui_fnc_updateValueAndSlider;
    };
};

plank_ui_fnc_initDialog = {
    plank_ui_onKeyDownEhId = findDisplay 46 displayAddEventHandler ["KeyDown", "_this call plank_ui_fnc_onKeyDown;"];
    plank_ui_onKeyUpEhId = findDisplay 46 displayAddEventHandler ["KeyUp", "_this call plank_ui_fnc_onKeyUp;"];
    plank_ui_onMouseButtonDownEhId = findDisplay 46 displayAddEventHandler ["MouseButtonDown", "_this call plank_ui_fnc_onMouseButtonDown;"];
    plank_ui_onMouseButtonUpEhId = findDisplay 46 displayAddEventHandler ["MouseButtonUp", "_this call plank_ui_fnc_onMouseButtonUp;"];
    plank_ui_onMouseMovingEhId = findDisplay 46 displayAddEventHandler ["MouseMoving", "_this call plank_ui_fnc_onMouseMoving;"];
    plank_ui_onMouseZChangedEhId = findDisplay 46 displayAddEventHandler ["MouseZChanged", "_this call plank_ui_fnc_onMouseZChanged;"];
    [] call plank_ui_fnc_initExportPickupButtons;
    [] call plank_ui_fnc_initFortControls;
    [] call plank_ui_fnc_resetFortCombo;
    [player getVariable ["plank_deploy_heightMode", RELATIVE_TO_UNIT]] call plank_ui_fnc_setHeightModeButton;
};

plank_ui_fnc_initExportPickupButtons = {
    if (isMultiplayer) then {
        (findDisplay SETTINGS_DIALOG_IDD displayCtrl SETTINGS_EXPORT_BACKGROUND_IDC) ctrlSetBackgroundColor [0, 0, 0, 0];
        ctrlEnable [SETTINGS_EXPORT_BUTTON_IDC, false];
    };
    if !([player, cursorObject] call plank_deploy_fnc_canPickupObject) then {
        ctrlEnable [SETTINGS_PICKUP_BUTTON_IDC, false];
    };
};

plank_ui_fnc_initFortControls = {
    [] call plank_ui_fnc_initToggleValues;
    [] call plank_ui_fnc_initSliders;
    [] call plank_ui_fnc_initSliderValues;
    [] call plank_ui_fnc_initSliderTextValues;
    [player getVariable ["plank_deploy_lockMode", LOCK_MODE_UNLOCKED]] call plank_ui_fnc_setLockModeButton;
};

plank_ui_fnc_dialogOnUnload = {
    findDisplay 46 displayRemoveEventHandler ["KeyDown", plank_ui_onKeyDownEhId];
    findDisplay 46 displayRemoveEventHandler ["KeyUp", plank_ui_onKeyUpEhId];
    findDisplay 46 displayRemoveEventHandler ["MouseButtonDown", plank_ui_onMouseButtonDownEhId];
    findDisplay 46 displayRemoveEventHandler ["MouseButtonUp", plank_ui_onMouseButtonUpEhId];
    findDisplay 46 displayRemoveEventHandler ["MouseMoving", plank_ui_onMouseMovingEhId];
    findDisplay 46 displayRemoveEventHandler ["MouseZChanged", plank_ui_onMouseZChangedEhId];
};