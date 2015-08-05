#include "plank_macros.h"

// Magic to set default font for Arma 2 and Arma 3
__EXEC(_plank_default_font = "puristaMedium"; _stop = false; while {isNil {call compile "blufor"} && {!_stop}} do {_plank_default_font = "Zeppelin32"; _stop = true;};)

#define SETTINGS_BASE_H                         1.62
#define SETTINGS_BASE_W                         0.8

#define SETTINGS_DIALOG_H                       SETTINGS_BASE_H
#define SETTINGS_DIALOG_W                       SETTINGS_BASE_W * 3 / 4

#define SETTINGS_BASE_X                         safeZoneX + safeZoneW - (SETTINGS_BASE_W + 0.1) * 3 / 4
#define SETTINGS_BASE_Y                         safeZoneY + safeZoneH - (SETTINGS_BASE_H + 0.1)

#define CONTROL_MARGIN_RIGHT                    0.02
#define CONTROL_MARGIN_BOTTOM                   0.03

#define ROW_BASE_H                              0.035
#define TITLE_BASE_W                            0.11
#define TITLE_BASE_H                            ROW_BASE_H
#define VALUE_BASE_W                            0.11
#define VALUE_BASE_H                            ROW_BASE_H
#define STATE_BASE_W                            0.05
#define SLIDER_BASE_W                           0.4
#define SLIDER_BASE_H                           ROW_BASE_H
#define RESET_BUTTON_BASE_W                     0.085
#define RESET_BUTTON_BASE_H                     ROW_BASE_H

#define CONTROL_GROUP_H                         (2 * ROW_BASE_H) + CONTROL_MARGIN_BOTTOM + 0.07

#define SETTINGS_PADDING_LEFT                   0.03
#define SETTINGS_CONTROL_BASE_X                 SETTINGS_BASE_X + SETTINGS_PADDING_LEFT

#define SETTINGS_PADDING_TOP                    0.03
#define SETTINGS_CONTROL_BASE_Y(ROW)            (SETTINGS_BASE_Y + SETTINGS_PADDING_TOP + (CONTROL_GROUP_H) * ROW)

class PlankSettingsDialog {
    idd = SETTINGS_DIALOG_IDD;
    controlsBackground[] = {};
    objects[] = {};
    onLoad = "uiNamespace setVariable ['plank_ui_settingsDialogIdd', _this select 0];";
    onUnload = "[] call plank_ui_fnc_dialogOnUnload;";
    controls[] = {
        DialogBackground,
        FortCombo,
        ConfirmButton,
        LockModeButton,
        CtrlTitle,
        CtrlValue,
        ShiftTitle,
        ShiftValue,
        HeightTitle,
        HeightModeButton,
        HeightSlider,
        HeightResetButton,
        HeightValue,
        HorizontalOffsetTitle,
        HorizontalOffsetSlider,
        HorizontalOffsetResetButton,
        HorizontalOffsetValue,
        DirectionTitle,
        DirectionSlider,
        DirectionResetButton,
        DirectionValue,
        DistanceTitle,
        DistanceSlider,
        DistanceValue,
        DistanceResetButton,
        PitchTitle,
        PitchSlider,
        PitchValue,
        PitchResetButton,
        BankTitle,
        BankSlider,
        BankValue,
        BankResetButton
    };

    class RscTextBase {
        idc = -1;
        access = 0;
        type = 0;
        colorBackground[] = {0, 0, 0, 1};
        colorText[] = {1, 1, 1, 1};
        text = "";
        fixedWidth = 0;
        x = 0;
        y = 0;
        h = 0.1;
        w = 0.1;
        style = 0;
        shadow = 2;
        font = __EVAL(_plank_default_font);
        SizeEx = 0.03921;
    };

    class TitleBase : RscTextBase {
        idc = -1;
        access = 0;
        type = 0;
        style = 0;
        shadow = 2;
        fixedWidth = 0;
        font = __EVAL(_plank_default_font);
        w = TITLE_BASE_W;
        h = TITLE_BASE_H;
        text="Height";
        colorBackground[] = {0, 0, 0, 0};
        colorText[] = {0.85, 0.85, 0.85, 1};
    };

    class ValueBase : RscTextBase {
        w = VALUE_BASE_W;
        h = VALUE_BASE_H;
        text="";
        colorBackground[] = {0, 0, 0, 0};
        colorText[] = {0.85, 0.85, 0.85, 1};
    };

    class RscSliderBase {
        access = 0;
        type = 3;
        style = 1024;
        w = 0.1;
        h = 0.035;
        color[] = {1, 1, 1, 0.8};
        colorActive[] = {1, 1, 1, 1};
        shadow = 0;
    };

    class SliderBase : RscSliderBase {
        w = SLIDER_BASE_W;
        h = SLIDER_BASE_H;
    };

    class RscButton {
        access = 0;
        type = 1;
        text = "";
        colorText[] = {0.305, 0.286, 0.301, 1};
        colorDisabled[] = {0.4, 0.4, 0.4, 0};
        colorBackground[] = {0.596, 0.576, 0.592, 1};
        colorBackgroundDisabled[] = {0, 0, 0, 0};
        colorBackgroundActive[] = {0.596, 0.576, 0.592, 1};
        colorFocused[] = {0.596, 0.576, 0.592, 1};
        colorShadow[] = {0, 0, 0, 1};
        colorBorder[] = {0, 0, 0, 1};
        soundEnter[] = {"",0.09,1};
        soundPush[] = {"",0.09,1};
        soundClick[] = {"\ca\ui\data\sound\new1",0.07,1};
        soundEscape[] = {"",0.09,1};
        style = 2;
        x = 0;
        y = 0;
        w = 0;
        h = 0;
        shadow = 0;
        font = __EVAL(_plank_default_font);
        sizeEx = 0.03921;
        offsetX = 0.003;
        offsetY = 0.003;
        offsetPressedX = 0.001;
        offsetPressedY = 0.001;
        borderSize = 0.003;
    };

    class ResetButtonBase : RscButton {
        w = RESET_BUTTON_BASE_W;
        h = RESET_BUTTON_BASE_H;
        SizeEx = 0.03921;
        text="Reset";
    };

    class RscCombo {
        idc = -1;
        w = TITLE_BASE_W * 3;
        h = TITLE_BASE_H;
        access = 0;
        type = 4;
        style = 0;
        colorSelect[] = {0.023529,0,0.0313725,1};
        colorText[] = {0.023529,0,0.0313725,1};
        colorBackground[] = {0.95,0.95,0.95,1};
        colorScrollbar[] = {0.023529,0,0.0313725,1};
        soundSelect[] = {"",0.1,1};
        soundExpand[] = {"",0.1,1};
        soundCollapse[] = {"",0.1,1};
        maxHistoryDelay = 1;
        class ScrollBar {
            color[] = {1,1,1,0.6};
            colorActive[] = {1,1,1,1};
            colorDisabled[] = {1,1,1,0.3};
            shadow = 0;
            thumb = "\ca\ui\data\ui_scrollbar_thumb_ca.paa";
            arrowFull = "\ca\ui\data\ui_arrow_top_active_ca.paa";
            arrowEmpty = "\ca\ui\data\ui_arrow_top_ca.paa";
            border = "\ca\ui\data\ui_border_scroll_ca.paa";
        };
        shadow = 0;
        colorSelectBackground[] = {0.8784,0.8471,0.651,1};
        arrowEmpty = "\ca\ui\data\ui_arrow_combo_ca.paa";
        arrowFull = "\ca\ui\data\ui_arrow_combo_active_ca.paa";
        wholeHeight = 0.45;
        color[] = {0,0,0,0.6};
        colorActive[] = {0,0,0,1};
        colorDisabled[] = {0,0,0,0.3};
        font = __EVAL(_plank_default_font);
        sizeEx = 0.03921;
    };
//--------------------------
    class FortCombo : RscCombo {
        idc = SETTINGS_FORT_COMBO_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(FORT_LIST_ROW_INDEX);
        onLBSelChanged = "_this call plank_ui_fnc_selectionChanged;";
    };
//--------------------------
    class ConfirmButton : RscButton {
        idc = SETTINGS_CONFIRM_BUTTON_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(FORT_CONFIRM_LOCK_ROW_INDEX);
        w = RESET_BUTTON_BASE_W;
        h = RESET_BUTTON_BASE_H;
        SizeEx = 0.03921;
        text = "Confirm";
        action = "[] call plank_ui_fnc_confirmButtonClick";
    };

    class LockModeButton : RscButton {
        idc = SETTINGS_LOCK_MODE_BUTTON_IDC;
        x = SETTINGS_CONTROL_BASE_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(FORT_CONFIRM_LOCK_ROW_INDEX);
        w = RESET_BUTTON_BASE_W;
        h = RESET_BUTTON_BASE_H;
        SizeEx = 0.03921;
        text = "Lock";
        action = "[] call plank_ui_fnc_lockModeButtonClick";
    };
//--------------------------
    class CtrlTitle : TitleBase {
        idc = SETTINGS_CTRL_TITLE_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(TOGGLE_ROW_INDEX);
        text = "Ctrl";
    };

    class CtrlValue : ValueBase {
        idc = SETTINGS_CTRL_VALUE_IDC;
        x = SETTINGS_CONTROL_BASE_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(TOGGLE_ROW_INDEX);
        text = "Off";
        colorText[] = {1, 0, 0, 1};
    };

    class ShiftTitle : TitleBase {
        idc = SETTINGS_SHIFT_TITLE_IDC;
        x = SETTINGS_CONTROL_BASE_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT + STATE_BASE_W + CONTROL_MARGIN_RIGHT * 3;
        y = SETTINGS_CONTROL_BASE_Y(TOGGLE_ROW_INDEX);
        text = "Shift";
    };

    class ShiftValue : ValueBase {
        idc = SETTINGS_SHIFT_VALUE_IDC;
        x = SETTINGS_CONTROL_BASE_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT + STATE_BASE_W + CONTROL_MARGIN_RIGHT * 3 + TITLE_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(TOGGLE_ROW_INDEX);
        w = STATE_BASE_W;
        text = "Off";
        colorText[] = {1, 0, 0, 1};
    };
//--------------------------
    class HeightTitle : TitleBase {
        idc = SETTINGS_HEIGHT_TITLE_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(HEIGHT_ROW_INDEX);
    };

    class HeightModeButton : ResetButtonBase {
        idc = SETTINGS_HEIGHT_MODE_BUTTON_IDC;
        x = SETTINGS_CONTROL_BASE_X + TITLE_BASE_W + RESET_BUTTON_BASE_W + CONTROL_MARGIN_RIGHT * 2;
        y = SETTINGS_CONTROL_BASE_Y(HEIGHT_ROW_INDEX);
        w = 0.2;
        text = "Snap to Terrain";
        action = "[] call plank_ui_fnc_heightModeButtonClick";
        colorBackground[] = {1, 1, 1, 1};
        colorBackgroundActive[] = {1, 1, 1, 1};
        colorFocused[] = {1, 1, 1, 1};
    };

    class HeightSlider : SliderBase {
        idc = SETTINGS_HEIGHT_SLIDER_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(HEIGHT_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateHeightSliderValue";
    };
    
    class HeightValue : ValueBase {
        idc = SETTINGS_HEIGHT_VALUE_IDC;
        x = SETTINGS_CONTROL_BASE_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(HEIGHT_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class HeightResetButton : ResetButtonBase {
        idc = SETTINGS_HEIGHT_RESET_BUTTON_IDC;
        x = SETTINGS_CONTROL_BASE_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(HEIGHT_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetHeightSlider";
    };
//--------------------------
    class HorizontalOffsetTitle : TitleBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_TITLE_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(HORIZONTAL_OFFSET_ROW_INDEX);
        text="Horizontal";
    };

    class HorizontalOffsetSlider : SliderBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_SLIDER_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(HORIZONTAL_OFFSET_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateHorizontalOffsetSliderValue";
    };

    class HorizontalOffsetValue : ValueBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_VALUE_IDC;
        x = SETTINGS_CONTROL_BASE_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(HORIZONTAL_OFFSET_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class HorizontalOffsetResetButton : ResetButtonBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_RESET_BUTTON_IDC;
        x = SETTINGS_CONTROL_BASE_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(HORIZONTAL_OFFSET_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetHorizontalOffsetSlider";
    };
//--------------------------
    class DirectionTitle : TitleBase {
        idc = SETTINGS_DIRECTION_TITLE_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(DIRECTION_ROW_INDEX);
        text="Direction";
    };

    class DirectionSlider : SliderBase {
        idc = SETTINGS_DIRECTION_SLIDER_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(DIRECTION_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateDirectiontSliderValue";
    };

    class DirectionValue : ValueBase {
        idc = SETTINGS_DIRECTION_VALUE_IDC;
        x = SETTINGS_CONTROL_BASE_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(DIRECTION_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class DirectionResetButton : ResetButtonBase {
        idc = SETTINGS_DIRECTION_RESET_BUTTON_IDC;
        x = SETTINGS_CONTROL_BASE_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(DIRECTION_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetDirectionSlider";
    };
//--------------------------
    class DistanceTitle : TitleBase {
        idc = SETTINGS_DISTANCE_TITLE_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(DISTANCE_ROW_INDEX);
        text="Distance";
    };

    class DistanceSlider : SliderBase {
        idc = SETTINGS_DISTANCE_SLIDER_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(DISTANCE_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateDistanceSliderValue";
    };

    class DistanceValue : ValueBase {
        idc = SETTINGS_DISTANCE_VALUE_IDC;
        x = SETTINGS_CONTROL_BASE_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(DISTANCE_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class DistanceResetButton : ResetButtonBase {
        idc = SETTINGS_DISTANCE_RESET_BUTTON_IDC;
        x = SETTINGS_CONTROL_BASE_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(DISTANCE_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetDistanceSlider";
    };
//--------------------------
    class PitchTitle : TitleBase {
        idc = SETTINGS_PITCH_TITLE_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(PITCH_ROW_INDEX);
        text="Pitch";
    };

    class PitchSlider : SliderBase {
        idc = SETTINGS_PITCH_SLIDER_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(PITCH_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updatePitchSliderValue";
    };

    class PitchValue : ValueBase {
        idc = SETTINGS_PITCH_VALUE_IDC;
        x = SETTINGS_CONTROL_BASE_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(PITCH_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class PitchResetButton : ResetButtonBase {
        idc = SETTINGS_PITCH_RESET_BUTTON_IDC;
        x = SETTINGS_CONTROL_BASE_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(PITCH_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetPitchSlider";
    };
//--------------------------
    class BankTitle : TitleBase {
        idc = SETTINGS_BANK_TITLE_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(BANK_ROW_INDEX);
        text="Bank";
    };

    class BankSlider : SliderBase {
        idc = SETTINGS_BANK_SLIDER_IDC;
        x = SETTINGS_CONTROL_BASE_X;
        y = SETTINGS_CONTROL_BASE_Y(BANK_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateBankSliderValue";
    };

    class BankValue : ValueBase {
        idc = SETTINGS_BANK_VALUE_IDC;
        x = SETTINGS_CONTROL_BASE_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(BANK_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class BankResetButton : ResetButtonBase {
        idc = SETTINGS_BANK_RESET_BUTTON_IDC;
        x = SETTINGS_CONTROL_BASE_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT;
        y = SETTINGS_CONTROL_BASE_Y(BANK_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetBankSlider";
    };
//--------------------------
    class DialogBackground {
        idc = SETTINGS_BACKGROUND_IDC;
        type = 0;
        style = 0;
        colorBackground[] = {0, 0, 0, 0.3};
        colorText[] = {0, 0, 0, 0};
        font = "EtelkaNarrowMediumPro";
        sizeEx = 0.03;
        text = "";
        x = SETTINGS_BASE_X;
        y = SETTINGS_BASE_Y;
        h = SETTINGS_DIALOG_H;
        w = SETTINGS_DIALOG_W;
    };
};