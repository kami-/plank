#include "plank_macros.h"

// Magic to set default font for Arma 2 and Arma 3
__EXEC(_plank_default_font = "puristaMedium"; _stop = false; while {isNil {call compile "blufor"} && {!_stop}} do {_plank_default_font = "Zeppelin32"; _stop = true;};)

#define H_RATIO(NUM)                            (NUM * 3 / 4)
#define TO_REAL_W(NUM)                          (NUM / safeZoneW)
#define TO_REAL_H(NUM)                          (H_RATIO(NUM) / safeZoneH)

#define FONT_SIZE                               TO_REAL_W(0.1)
#define DISABLED_COLOR                          {0, 0, 0, 0}
#define DIALOG_BG_COLOR                         {0.161, 0.271, 0.275, 0.7}
#define COMBO_SELECTED_BG_COLOR                 {0.6, 0.706, 0.729, 1}
#define BUTTON_BG_COLOR                         {0.725, 0.435, 0.161, 1}
#define BUTTON_TEXT_COLOR                       {1, 1, 1, 1}

#define DIALOG_H                                (safeZoneH * 0.54)
#define DIALOG_W                                (safeZoneW * 0.213)
#define DIALOG_MARGIN_RIGHT                     TO_REAL_W(0.02)
#define DIALOG_MARGIN_BOTTOM                    TO_REAL_H(0.02)
#define DIALOG_PADDING_LEFT                     TO_REAL_H(0.03)
#define DIALOG_PADDING_TOP                      TO_REAL_H(0.03)
#define DIALOG_X                                safeZoneX + safeZoneW - DIALOG_W - DIALOG_MARGIN_RIGHT
#define DIALOG_Y                                safeZoneY + safeZoneH - 1.5 * DIALOG_H - DIALOG_MARGIN_BOTTOM

#define ROW_BASE_H                              TO_REAL_H(0.1)
#define CONTROL_MARGIN_RIGHT                    TO_REAL_W(0.02)
#define CONTROL_MARGIN_BOTTOM                   TO_REAL_H(0.03)
#define CONTROL_GROUP_H                         (2 * ROW_BASE_H) + CONTROL_MARGIN_BOTTOM + TO_REAL_H(0.08)
#define CONTROL_GROUP_HALF_H                    ROW_BASE_H + CONTROL_MARGIN_BOTTOM + TO_REAL_H(0.02)
#define CONTROL_X                               DIALOG_X + DIALOG_PADDING_LEFT
#define CONTROL_HALF_Y(ROW)                     (DIALOG_Y + DIALOG_PADDING_TOP + (CONTROL_GROUP_HALF_H) * ROW)
#define CONTROL_Y(ROW)                          (DIALOG_Y + DIALOG_PADDING_TOP + (CONTROL_GROUP_H) * ROW) - 3 * (ROW_BASE_H + CONTROL_MARGIN_BOTTOM)

#define EXPORT_BUTTON_W                         TO_REAL_W(0.209)
#define EXPORT_BACKGROUND_W                     (EXPORT_BUTTON_W + DIALOG_PADDING_LEFT * 2)
#define COMBO_W                                 DIALOG_W - DIALOG_PADDING_LEFT * 2
#define CONFIRM_BUTTON_W                        TO_REAL_W(0.24)
#define LOCK_BUTTON_W                           TO_REAL_W(0.21)
#define PICKUP_BUTTON_W                         TO_REAL_W(0.21)
#define TITLE_BASE_W                            TO_REAL_W(0.31)
#define TITLE_BASE_H                            ROW_BASE_H
#define VALUE_BASE_W                            TO_REAL_W(0.3)
#define VALUE_BASE_H                            ROW_BASE_H
#define HEIGHT_MODE_BUTTON_W                    TO_REAL_W(0.5)
#define STATE_BASE_W                            TO_REAL_W(0.05)
#define SLIDER_BASE_W                           TO_REAL_W(0.9)
#define SLIDER_BASE_H                           ROW_BASE_H
#define RESET_BUTTON_W                          TO_REAL_W(0.17)
#define RESET_BUTTON_H                          ROW_BASE_H
#define EXPORT_BACKGROUND_H                     RESET_BUTTON_H + DIALOG_PADDING_LEFT

#define EXPORT_BUTTON_X                         safeZoneX + safeZoneW - EXPORT_BUTTON_W - DIALOG_MARGIN_RIGHT - DIALOG_PADDING_LEFT
#define EXPORT_BUTTON_Y                         DIALOG_Y - RESET_BUTTON_H
#define EXPORT_BACKGROUND_X                     safeZoneX + safeZoneW - EXPORT_BACKGROUND_W - DIALOG_MARGIN_RIGHT
#define EXPORT_BACKGROUND_Y                     DIALOG_Y - EXPORT_BACKGROUND_H - DIALOG_PADDING_LEFT * 2
#define EXPORT_BUTTON_Y                         DIALOG_Y - RESET_BUTTON_H
#define LOCK_BUTTON_X                           CONTROL_X + CONFIRM_BUTTON_W + TO_REAL_W(0.05)
#define PICKUP_BUTTON_X                         LOCK_BUTTON_X + LOCK_BUTTON_W + TO_REAL_W(0.05)
#define RESET_BUTTON_X                          CONTROL_X + TITLE_BASE_W + TO_REAL_W(0.05)
#define HEIGHT_MODE_BUTTON_X                    RESET_BUTTON_X + RESET_BUTTON_W + TO_REAL_W(0.05)


class PlankSettingsDialog {
    idd = SETTINGS_DIALOG_IDD;
    controlsBackground[] = {};
    objects[] = {};
    onLoad = "uiNamespace setVariable ['plank_ui_settingsDialogIdd', _this select 0];";
    onUnload = "[] call plank_ui_fnc_dialogOnUnload;";
    controls[] = {
        DialogBackground,
        ExportBackground,
        ExportButton,
        FortCombo,
        ConfirmButton,
        LockModeButton,
        PickupButton,
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
        sizeEx = FONT_SIZE;
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
        text = "Height";
        colorBackground[] = {0, 0, 0, 0};
        colorText[] = BUTTON_TEXT_COLOR;
    };

    class ValueBase : RscTextBase {
        w = VALUE_BASE_W;
        h = VALUE_BASE_H;
        text = "-10.00001";
        colorBackground[] = {0, 0, 0, 0};
        colorText[] = BUTTON_TEXT_COLOR;
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
        style = 0x02 + 0x0c;
        colorText[] = BUTTON_TEXT_COLOR;
        colorDisabled[] = DISABLED_COLOR;
        colorBackground[] = BUTTON_BG_COLOR;
        colorBackgroundDisabled[] = DISABLED_COLOR;
        colorBackgroundActive[] = BUTTON_BG_COLOR;
        colorFocused[] = BUTTON_BG_COLOR;
        colorShadow[] = {0, 0, 0, 0};
        colorBorder[] = {0, 0, 0, 0};
        soundEnter[] = {"", 0.09, 1};
        soundPush[] = {"", 0.09, 1};
        soundClick[] = {"\ca\ui\data\sound\new1", 0.07, 1};
        soundEscape[] = {"", 0.09, 1};
        x = 0;
        y = 0;
        w = 0;
        h = 0;
        shadow = 0;
        font = __EVAL(_plank_default_font);
        sizeEx = FONT_SIZE;
        offsetX = 0.003;
        offsetY = 0.003;
        offsetPressedX = 0.001;
        offsetPressedY = 0.001;
        borderSize = 0.003;
    };

    class ResetButtonBase : RscButton {
        w = RESET_BUTTON_W;
        h = RESET_BUTTON_H;
        x = RESET_BUTTON_X;
        sizeEx = FONT_SIZE;
        text = "Reset";
    };

    class RscCombo {
        idc = -1;
        w = COMBO_W;
        h = TITLE_BASE_H;
        access = 0;
        type = 4;
        style = 0;
        color[] = {0,0,0,0.6};
        colorActive[] = {0,0,0,1};
        colorDisabled[] = {0,0,0,0.3};
        colorSelect[] = {0, 0, 0, 1};
        colorSelect2[] = {0, 0, 0, 1};
        colorSelectBackground[] = COMBO_SELECTED_BG_COLOR;
        colorSelectBackground2[] = COMBO_SELECTED_BG_COLOR;
        colorText[] = {0, 0, 0, 1};
        colorBackground[] = {1, 1, 1, 1};
        colorScrollbar[] = {0, 0, 0, 1};
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
        arrowEmpty = "\ca\ui\data\ui_arrow_combo_ca.paa";
        arrowFull = "\ca\ui\data\ui_arrow_combo_active_ca.paa";
        wholeHeight = TO_REAL_H(1);
        font = __EVAL(_plank_default_font);
        sizeEx = FONT_SIZE;
    };
//--------------------------
    class ExportBackground {
        idc = SETTINGS_EXPORT_BACKGROUND_IDC;
        type = 0;
        style = 0;
        colorText[] = {0, 0, 0, 0};
        colorBackground[] = DIALOG_BG_COLOR;
        colorDisabled[] = DISABLED_COLOR;
        colorBackgroundDisabled[] = DISABLED_COLOR;
        font = "EtelkaNarrowMediumPro";
        sizeEx = 0.03;
        text = "";
        x = EXPORT_BACKGROUND_X;
        y = EXPORT_BACKGROUND_Y;
        h = EXPORT_BACKGROUND_H;
        w = EXPORT_BACKGROUND_W;
    };

    class ExportButton : RscButton {
        idc = SETTINGS_EXPORT_BUTTON_IDC;
        x = EXPORT_BUTTON_X;
        y = EXPORT_BUTTON_Y;
        w = EXPORT_BUTTON_W;
        h = RESET_BUTTON_H;
        sizeEx = FONT_SIZE;
        text = "Export";
        action = "[] call plank_ui_fnc_exportButtonClick";
        tooltip = "Exports player placed objects as SQF script to clipboard. Only works in SP."
    };
//--------------------------
    class FortCombo : RscCombo {
        idc = SETTINGS_FORT_COMBO_IDC;
        x = CONTROL_X;
        y = CONTROL_HALF_Y(FORT_LIST_ROW_INDEX);
        onLBSelChanged = "_this call plank_ui_fnc_selectionChanged;";
    };
//--------------------------
    class ConfirmButton : RscButton {
        idc = SETTINGS_CONFIRM_BUTTON_IDC;
        x = CONTROL_X;
        y = CONTROL_HALF_Y(FORT_CONFIRM_LOCK_ROW_INDEX);
        w = CONFIRM_BUTTON_W;
        h = RESET_BUTTON_H;
        sizeEx = FONT_SIZE;
        text = "Confirm";
        action = "[] call plank_ui_fnc_confirmButtonClick";
    };

    class LockModeButton : RscButton {
        idc = SETTINGS_LOCK_MODE_BUTTON_IDC;
        x = LOCK_BUTTON_X;
        y = CONTROL_HALF_Y(FORT_CONFIRM_LOCK_ROW_INDEX);
        w = LOCK_BUTTON_W;
        h = RESET_BUTTON_H;
        sizeEx = FONT_SIZE;
        text = "Unlock";
        action = "[] call plank_ui_fnc_lockModeButtonClick";
    };

    class PickupButton : RscButton {
        idc = SETTINGS_PICKUP_BUTTON_IDC;
        x = PICKUP_BUTTON_X;
        y = CONTROL_HALF_Y(FORT_CONFIRM_LOCK_ROW_INDEX);
        w = LOCK_BUTTON_W;
        h = RESET_BUTTON_H;
        sizeEx = FONT_SIZE;
        text = "Pickup";
        action = "[] call plank_ui_fnc_pickupButtonClick";
        tooltip = "Pickup your previously placed object."
    };
//--------------------------
    class CtrlTitle : TitleBase {
        idc = SETTINGS_CTRL_TITLE_IDC;
        x = CONTROL_X;
        y = CONTROL_HALF_Y(TOGGLE_ROW_INDEX);
        text = "Ctrl";
    };

    class CtrlValue : ValueBase {
        idc = SETTINGS_CTRL_VALUE_IDC;
        x = CONTROL_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT;
        y = CONTROL_HALF_Y(TOGGLE_ROW_INDEX);
        text = "Off";
        colorText[] = {1, 0, 0, 1};
    };

    class ShiftTitle : TitleBase {
        idc = SETTINGS_SHIFT_TITLE_IDC;
        x = CONTROL_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT + STATE_BASE_W + CONTROL_MARGIN_RIGHT * 3;
        y = CONTROL_HALF_Y(TOGGLE_ROW_INDEX);
        text = "Shift";
    };

    class ShiftValue : ValueBase {
        idc = SETTINGS_SHIFT_VALUE_IDC;
        x = CONTROL_X + TITLE_BASE_W + CONTROL_MARGIN_RIGHT + STATE_BASE_W + CONTROL_MARGIN_RIGHT * 3 + TITLE_BASE_W + CONTROL_MARGIN_RIGHT;
        y = CONTROL_HALF_Y(TOGGLE_ROW_INDEX);
        w = STATE_BASE_W;
        text = "Off";
        colorText[] = {1, 0, 0, 1};
    };
//--------------------------
    class HeightTitle : TitleBase {
        idc = SETTINGS_HEIGHT_TITLE_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(HEIGHT_ROW_INDEX);
    };

    class HeightModeButton : ResetButtonBase {
        idc = SETTINGS_HEIGHT_MODE_BUTTON_IDC;
        x = HEIGHT_MODE_BUTTON_X;
        y = CONTROL_Y(HEIGHT_ROW_INDEX);
        w = HEIGHT_MODE_BUTTON_W;
        text = "Snap to Terrain";
        action = "[] call plank_ui_fnc_heightModeButtonClick";
    };

    class HeightSlider : SliderBase {
        idc = SETTINGS_HEIGHT_SLIDER_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(HEIGHT_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateHeightSliderValue";
    };
    
    class HeightValue : ValueBase {
        idc = SETTINGS_HEIGHT_VALUE_IDC;
        x = CONTROL_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = CONTROL_Y(HEIGHT_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class HeightResetButton : ResetButtonBase {
        idc = SETTINGS_HEIGHT_RESET_BUTTON_IDC;
        y = CONTROL_Y(HEIGHT_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetHeightSlider";
    };
//--------------------------
    class HorizontalOffsetTitle : TitleBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_TITLE_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(HORIZONTAL_OFFSET_ROW_INDEX);
        text="Horizontal";
    };

    class HorizontalOffsetSlider : SliderBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_SLIDER_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(HORIZONTAL_OFFSET_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateHorizontalOffsetSliderValue";
    };

    class HorizontalOffsetValue : ValueBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_VALUE_IDC;
        x = CONTROL_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = CONTROL_Y(HORIZONTAL_OFFSET_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class HorizontalOffsetResetButton : ResetButtonBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_RESET_BUTTON_IDC;
        y = CONTROL_Y(HORIZONTAL_OFFSET_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetHorizontalOffsetSlider";
    };
//--------------------------
    class DirectionTitle : TitleBase {
        idc = SETTINGS_DIRECTION_TITLE_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(DIRECTION_ROW_INDEX);
        text="Direction";
    };

    class DirectionSlider : SliderBase {
        idc = SETTINGS_DIRECTION_SLIDER_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(DIRECTION_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateDirectiontSliderValue";
    };

    class DirectionValue : ValueBase {
        idc = SETTINGS_DIRECTION_VALUE_IDC;
        x = CONTROL_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = CONTROL_Y(DIRECTION_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class DirectionResetButton : ResetButtonBase {
        idc = SETTINGS_DIRECTION_RESET_BUTTON_IDC;
        y = CONTROL_Y(DIRECTION_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetDirectionSlider";
    };
//--------------------------
    class DistanceTitle : TitleBase {
        idc = SETTINGS_DISTANCE_TITLE_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(DISTANCE_ROW_INDEX);
        text="Distance";
    };

    class DistanceSlider : SliderBase {
        idc = SETTINGS_DISTANCE_SLIDER_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(DISTANCE_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateDistanceSliderValue";
    };

    class DistanceValue : ValueBase {
        idc = SETTINGS_DISTANCE_VALUE_IDC;
        x = CONTROL_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = CONTROL_Y(DISTANCE_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class DistanceResetButton : ResetButtonBase {
        idc = SETTINGS_DISTANCE_RESET_BUTTON_IDC;
        y = CONTROL_Y(DISTANCE_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetDistanceSlider";
    };
//--------------------------
    class PitchTitle : TitleBase {
        idc = SETTINGS_PITCH_TITLE_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(PITCH_ROW_INDEX);
        text="Pitch";
    };

    class PitchSlider : SliderBase {
        idc = SETTINGS_PITCH_SLIDER_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(PITCH_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updatePitchSliderValue";
    };

    class PitchValue : ValueBase {
        idc = SETTINGS_PITCH_VALUE_IDC;
        x = CONTROL_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = CONTROL_Y(PITCH_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class PitchResetButton : ResetButtonBase {
        idc = SETTINGS_PITCH_RESET_BUTTON_IDC;
        y = CONTROL_Y(PITCH_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetPitchSlider";
    };
//--------------------------
    class BankTitle : TitleBase {
        idc = SETTINGS_BANK_TITLE_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(BANK_ROW_INDEX);
        text="Bank";
    };

    class BankSlider : SliderBase {
        idc = SETTINGS_BANK_SLIDER_IDC;
        x = CONTROL_X;
        y = CONTROL_Y(BANK_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateBankSliderValue";
    };

    class BankValue : ValueBase {
        idc = SETTINGS_BANK_VALUE_IDC;
        x = CONTROL_X + SLIDER_BASE_W + CONTROL_MARGIN_RIGHT;
        y = CONTROL_Y(BANK_ROW_INDEX) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM;
    };

    class BankResetButton : ResetButtonBase {
        idc = SETTINGS_BANK_RESET_BUTTON_IDC;
        y = CONTROL_Y(BANK_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetBankSlider";
    };
//--------------------------
    class DialogBackground {
        idc = SETTINGS_BACKGROUND_IDC;
        type = 0;
        style = 0;
        colorBackground[] = DIALOG_BG_COLOR;
        colorText[] = {0, 0, 0, 0};
        font = "EtelkaNarrowMediumPro";
        sizeEx = 0.03;
        text = "";
        x = DIALOG_X;
        y = DIALOG_Y;
        h = DIALOG_H;
        w = DIALOG_W;
    };
};