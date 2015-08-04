#include "plank_macros.h"

#include "\userconfig\plank\log\ui.h"
#include "logbook.h"


plank_ui_fnc_createSettingsDialog = {
    if (!dialog) then {
        private "_isDialogCreated";
        _isDialogCreated = createDialog "PlankSettingsDialog";
        if (_isDialogCreated) then {
            [] call plank_ui_fnc_initDialog;
        };
    };
};

plank_ui_fnc_closeSettingsDialog = {
    if (dialog) then {
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

plank_ui_fnc_heightModeButtonClick = {
    private "_heightMode";
    _heightMode = player getVariable ["plank_deploy_heightMode", RELATIVE_TO_UNIT];
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

    ctrlSetText [_idc, str _value];
    player setVariable [_varName, _value, false]
};

plank_ui_fnc_updateToggleValue = {
    FUN_ARGS_2(_idc,_toggleState);

    if (_toggleState) then {
        (findDisplay SETTINGS_DIALOG_IDD displayCtrl _idc) ctrlSetTextColor [0, 1, 0, 1];
        (findDisplay SETTINGS_DIALOG_IDD displayCtrl _idc) ctrlSetText "On";
    } else {
        (findDisplay SETTINGS_DIALOG_IDD displayCtrl _idc) ctrlSetTextColor [1, 0, 0, 1];
        (findDisplay SETTINGS_DIALOG_IDD displayCtrl _idc) ctrlSetText "Off";
    };
};

plank_ui_fnc_initToggleValues = {
    plank_ui_isControlToggled = false;
    plank_ui_isShiftToggled = false;
    [SETTINGS_CTRL_VALUE_IDC, plank_ui_isControlToggled] call plank_ui_fnc_updateToggleValue;
    [SETTINGS_SHIFT_VALUE_IDC, plank_ui_isShiftToggled] call plank_ui_fnc_updateToggleValue;
};

plank_ui_fnc_initSliders = {
    _fortIndex = player getVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX];
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
    _fortIndex = player getVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX];
    sliderSetPosition [SETTINGS_HEIGHT_SLIDER_IDC, player getVariable ["plank_deploy_fortRelativeHeight", DEFAULT_HEIGHT]];
    sliderSetPosition [SETTINGS_HORIZONTAL_OFFSET_SLIDER_IDC, player getVariable ["plank_deploy_fortHorizontalOffset", DEFAULT_HORIZONTAL_OFFSET]];
    sliderSetPosition [SETTINGS_PITCH_SLIDER_IDC, player getVariable ["plank_deploy_fortPitch", DEFAULT_PITCH]];
    sliderSetPosition [SETTINGS_BANK_SLIDER_IDC, player getVariable ["plank_deploy_fortBank", DEFAULT_BANK]];
    sliderSetPosition [SETTINGS_DIRECTION_SLIDER_IDC, player getVariable ["plank_deploy_fortDirection", GET_FORT_DIRECTION(_fortIndex)]];
    sliderSetPosition [SETTINGS_DISTANCE_SLIDER_IDC, player getVariable ["plank_deploy_fortDistance", GET_FORT_DISTANCE(_fortIndex)]];
};

plank_ui_fnc_initSliderTextValues = {
    _fortIndex = player getVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX];
    ctrlSetText [SETTINGS_HEIGHT_VALUE_IDC, str (player getVariable ["plank_deploy_fortRelativeHeight", DEFAULT_HEIGHT])];
    ctrlSetText [SETTINGS_HORIZONTAL_OFFSET_VALUE_IDC, str (player getVariable ["plank_deploy_fortHorizontalOffset", DEFAULT_HORIZONTAL_OFFSET])];
    ctrlSetText [SETTINGS_PITCH_VALUE_IDC, str (player getVariable ["plank_deploy_fortPitch", DEFAULT_PITCH])];
    ctrlSetText [SETTINGS_BANK_VALUE_IDC, str (player getVariable ["plank_deploy_fortBank", DEFAULT_BANK])];
    ctrlSetText [SETTINGS_DIRECTION_VALUE_IDC, str (player getVariable ["plank_deploy_fortDirection", GET_FORT_DIRECTION(_fortIndex)])];
    ctrlSetText [SETTINGS_DISTANCE_VALUE_IDC, str (player getVariable ["plank_deploy_fortDistance", GET_FORT_DIRECTION(_fortIndex)])];
};

plank_ui_fnc_initFortCombo = {
    lbClear SETTINGS_FORT_COMBO_IDC;
    [] call plank_ui_fnc_addFortificationLabels;
    lbSetCurSel [SETTINGS_FORT_COMBO_IDC, player getVariable ["plank_deploy_fortIndex", DEFAULT_FORT_INDEX]];
};

plank_ui_fnc_addFortificationLabel = {
    FUN_ARGS_2(_fortCount,_fortIndex);

    DECLARE(_label) = FORT_COMBO_NONE_NAME;
    if (_fortIndex != DEFAULT_FORT_INDEX) then {
        _label = format ["%1x %2", _fortCount, GET_FORT_DISPLAY_NAME(_fortIndex)];
    };
    lbAdd [SETTINGS_FORT_COMBO_IDC, _label];
};

plank_ui_fnc_addFortificationLabels = {
    {
        [_x, _forEachIndex] call plank_ui_fnc_addFortificationLabel;
    } foreach (player getVariable ["plank_deploy_fortCounts", []]);
};

plank_ui_fnc_selectionChanged = {
    FUN_ARGS_2(_control,_index);

    if (_index > 0) then {
        [player, _index] call plank_deploy_fnc_tryStartFortPlacement;
    } else {
        [player] call plank_deploy_fnc_cancelFortPlacement;
    };
};

plank_ui_fnc_setHeightModeButton = {
    FUN_ARGS_1(_heightMode);

    player setVariable ["plank_deploy_heightMode", _heightMode, false];
    ctrlSetText [SETTINGS_HEIGHT_MODE_BUTTON_IDC, STR_HEIGHT_MODES select _heightMode];
};

plank_ui_fnc_updateValueAndSlider = {
    FUN_ARGS_6(_value,_minValue,_maxValue,_varName,_sliderIdc,_valueIdc);

    DECLARE(_newValue) = (player getVariable _varName) + _value;
    _newValue = (_newValue max _minValue) min _maxValue;
    [_valueIdc, _varName, _newValue] call plank_ui_fnc_updateValue;
    sliderSetPosition [_sliderIdc, _newValue];
};

plank_ui_fnc_onKeyDown = {
    FUN_ARGS_5(_control,_keyCode,_shift,_ctrl,_alt);

    plank_ui_isControlToggled = _ctrl && {!plank_ui_isControlToggled};
    plank_ui_isShiftToggled = _shift && {!plank_ui_isShiftToggled};
    [SETTINGS_CTRL_VALUE_IDC, plank_ui_isControlToggled] call plank_ui_fnc_updateToggleValue;
    [SETTINGS_SHIFT_VALUE_IDC, plank_ui_isShiftToggled] call plank_ui_fnc_updateToggleValue;

    false;
};

plank_ui_fnc_onMouseMoving = {
    FUN_ARGS_3(_display,_deltaX,_deltaY);

    call {
        if (plank_ui_isControlToggled) exitWith {
            [-_deltaY / 15, MIN_HEIGHT, MAX_HEIGHT, "plank_deploy_fortRelativeHeight", SETTINGS_HEIGHT_SLIDER_IDC, SETTINGS_HEIGHT_VALUE_IDC] call plank_ui_fnc_updateValueAndSlider;
            [_deltaX / 25, MIN_HORIZONTAL_OFFSET, MAX_HORIZONTAL_OFFSET, "plank_deploy_fortHorizontalOffset", SETTINGS_HORIZONTAL_OFFSET_SLIDER_IDC, SETTINGS_HORIZONTAL_OFFSET_VALUE_IDC] call plank_ui_fnc_updateValueAndSlider;
        };
        if (plank_ui_isShiftToggled) exitWith {
            [-_deltaY, MIN_PITCH, MAX_PITCH, "plank_deploy_fortPitch", SETTINGS_PITCH_SLIDER_IDC, SETTINGS_PITCH_VALUE_IDC] call plank_ui_fnc_updateValueAndSlider;
            [-_deltaX, MIN_BANK, MAX_BANK, "plank_deploy_fortBank", SETTINGS_BANK_SLIDER_IDC, SETTINGS_BANK_VALUE_IDC] call plank_ui_fnc_updateValueAndSlider;
        };
    };
};

plank_ui_fnc_onMouseZChanged = {
    FUN_ARGS_2(_display,_deltaY);

    call {
        if (plank_ui_isControlToggled) exitWith {
            DECLARE(_minDistance) = GET_FORT_DISTANCE(player getVariable "plank_deploy_fortIndex");
            [_deltaY, _minDistance, _minDistance + MAX_DISTANCE_ADD, "plank_deploy_fortDistance", SETTINGS_DISTANCE_SLIDER_IDC, SETTINGS_DISTANCE_VALUE_IDC] call plank_ui_fnc_updateValueAndSlider;
        };
        if (plank_ui_isShiftToggled) exitWith {
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
        };
    };
};

plank_ui_fnc_initDialog = {
    plank_ui_onKeyDownEhId = findDisplay 46 displayAddEventHandler ["KeyDown", "_this call plank_ui_fnc_onKeyDown;"];
    plank_ui_onMouseMovingEhId = findDisplay 46 displayAddEventHandler ["MouseMoving", "_this call plank_ui_fnc_onMouseMoving;"];
    plank_ui_onMouseZChangedEhId = findDisplay 46 displayAddEventHandler ["MouseZChanged", "_this call plank_ui_fnc_onMouseZChanged;"];
    [] call plank_ui_fnc_initFortControls;
    [] call plank_ui_fnc_initFortCombo;
    [player getVariable ["plank_deploy_heightMode", RELATIVE_TO_UNIT]] call plank_ui_fnc_setHeightModeButton;
};

plank_ui_fnc_initFortControls = {
    [] call plank_ui_fnc_initToggleButtons;
    [] call plank_ui_fnc_initSliders;
    [] call plank_ui_fnc_initSliderValues;
    [] call plank_ui_fnc_initSliderTextValues;
};

plank_ui_fnc_dialogOnUnload = {
    findDisplay 46 displayRemoveEventHandler ["KeyDown", plank_ui_onKeyDownEhId];
    findDisplay 46 displayRemoveEventHandler ["MouseMoving", plank_ui_onMouseMovingEhId];
    findDisplay 46 displayRemoveEventHandler ["MouseZChanged", plank_ui_onMouseZChangedEhId];
};