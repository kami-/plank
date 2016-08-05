#include "plank_macros.h"

// Static styles
#define ST_POS            0x0F
#define ST_HPOS           0x03
#define ST_VPOS           0x0C
#define ST_LEFT           0x00
#define ST_RIGHT          0x01
#define ST_CENTER         0x02
#define ST_DOWN           0x04
#define ST_UP             0x08
#define ST_VCENTER        0x0C
#define ST_PICTURE        48

#define H_RATIO(NUM)                            (NUM * 4 / 3)
#define TO_REAL_W(NUM)                          ((NUM) * safeZoneW)
#define TO_REAL_H(NUM)                          (H_RATIO(NUM) * safeZoneW)

#define DISABLED_COLOR                          {0, 0, 0, 0}
#define DIALOG_BG_COLOR                         {0.2, 0.2, 0.2, 1}
#define COMBO_SELECTED_BG_COLOR                 {0.6, 0.706, 0.729, 1}
#define BUTTON_BG_COLOR                         {0, 0, 0, 1}
#define BUTTON_ACTIVE_COLOR                     {0.77, 0.51, 0.08, 1}
#define BUTTON_TEXT_COLOR                       {1, 1, 1, 1}

#define DIALOG_H                                (safeZoneH * 0.49)
#define DIALOG_W                                (safeZoneW * 0.213)
#define DIALOG_MARGIN_RIGHT                     TO_REAL_W(0.003)
#define DIALOG_MARGIN_BOTTOM                    TO_REAL_H(0.003)
#define DIALOG_PADDING_LEFT                     TO_REAL_H(0.0045)
#define DIALOG_PADDING_TOP                      TO_REAL_H(0.0045)
#define DIALOG_X                                safeZoneX + safeZoneW - DIALOG_W - DIALOG_MARGIN_RIGHT
#define DIALOG_Y                                safeZoneY + safeZoneH - 1.5 * DIALOG_H - DIALOG_MARGIN_BOTTOM

#define FONT_TYPE                               "puristaMedium"
#define ROW_BASE_H                              TO_REAL_H(0.012)
#define FONT_SIZE                               TO_REAL_W(0.016)
#define CONTROL_MARGIN_RIGHT                    TO_REAL_W(0.003)
#define CONTROL_MARGIN_BOTTOM                   TO_REAL_H(0.0035)
#define CONTROL_GROUP_H                         (2 * ROW_BASE_H) + CONTROL_MARGIN_BOTTOM + TO_REAL_H(0.01)
#define CONTROL_GROUP_HALF_H                    ROW_BASE_H + CONTROL_MARGIN_BOTTOM + TO_REAL_H(0.003)
#define CONTROL_X                               DIALOG_X + DIALOG_PADDING_LEFT
#define CONTROL_RIGHT_X                         safeZoneX + safeZoneW - DIALOG_MARGIN_RIGHT - DIALOG_PADDING_LEFT

#define CONTROL_HALF_Y(ROW)                     (DIALOG_Y + DIALOG_PADDING_TOP + (CONTROL_GROUP_HALF_H) * ROW)
#define CONTROL_Y(ROW)                          (DIALOG_Y + DIALOG_PADDING_TOP + (CONTROL_GROUP_H) * ROW) - 2 * (ROW_BASE_H + CONTROL_MARGIN_BOTTOM)
#define SLIDER_Y(ROW)                           CONTROL_Y(ROW) + ROW_BASE_H + CONTROL_MARGIN_BOTTOM

#define TOOLTIP_MAX_WIDTH                       DIALOG_W
#define EXPORT_BUTTON_W                         TO_REAL_W(0.036)
#define EXPORT_BACKGROUND_W                     (EXPORT_BUTTON_W + DIALOG_PADDING_LEFT * 2)
#define COMBO_W                                 DIALOG_W - DIALOG_PADDING_LEFT * 2
#define CONFIRM_BUTTON_W                        TO_REAL_W(0.042)
#define LOCK_BUTTON_W                           TO_REAL_W(0.037)
#define PICKUP_BUTTON_W                         TO_REAL_W(0.037)
#define MOVE_TITLE_W                            TO_REAL_W(0.024)
#define TOGGLE_VALUE_W                          TO_REAL_W(0.018)
#define ROTATE_TITLE_W                          TO_REAL_W(0.03)
#define TITLE_BASE_W                            TO_REAL_W(0.05)
#define TITLE_BASE_H                            ROW_BASE_H
#define SHORTCUT_TEXT_W                         TO_REAL_W(0.055)
#define SHORTCUT_PICTURE_W                      TO_REAL_W(0.03)
#define SHORTCUT_PICTURE_H                      TO_REAL_H(0.025)
#define VALUE_BASE_W                            TO_REAL_W(0.045)
#define VALUE_BASE_H                            ROW_BASE_H
#define VERTICAL_MODE_CHECKBOX_W                TO_REAL_W(0.02)
#define VERTICAL_MODE_CHECKBOX_H                TO_REAL_H(0.02)
#define SLIDER_BASE_W                           TO_REAL_W(0.142)
#define SLIDER_BASE_H                           ROW_BASE_H
#define RESET_BUTTON_W                          ROW_BASE_H//TO_REAL_W(0.032)
#define RESET_BUTTON_H                          ROW_BASE_H
#define EXPORT_BACKGROUND_H                     RESET_BUTTON_H + DIALOG_PADDING_LEFT

#define CANCEL_BUTTON_X                         CONTROL_RIGHT_X - CONFIRM_BUTTON_W
#define CONFIRM_BUTTON_X                        CANCEL_BUTTON_X - TO_REAL_W(0.002) - CONFIRM_BUTTON_W
#define TITLE_X                                 CONTROL_X - TO_REAL_W(0.0035)
#define SHORTCUT_TEXT_X                         TITLE_X + TITLE_BASE_W + TO_REAL_W(0.002)
#define SHORTCUT_PICTURE_X                      SHORTCUT_TEXT_X + SHORTCUT_TEXT_W - TO_REAL_W(0.003)
#define SHORTCUT_PICTURE_Y(ROW)                 CONTROL_Y(ROW) - TO_REAL_W(0.01)
#define SLIDER_VALUE_X                          CONTROL_RIGHT_X - VALUE_BASE_W + TO_REAL_W(0.0035)
#define RESET_BUTTON_X                          CONTROL_X + SLIDER_BASE_W + TO_REAL_W(0.002)
#define VERTICAL_MODE_CHECKBOX_X                CONTROL_RIGHT_X - VERTICAL_MODE_CHECKBOX_W
#define VERTICAL_MODE_CHECKBOX_Y                CONTROL_Y(HEIGHT_ROW_INDEX) - VERTICAL_MODE_CHECKBOX_H + ROW_BASE_H
#define EXPORT_BUTTON_X                         CONTROL_RIGHT_X - EXPORT_BUTTON_W
#define EXPORT_BUTTON_Y                         DIALOG_Y - RESET_BUTTON_H
#define EXPORT_BACKGROUND_X                     safeZoneX + safeZoneW - EXPORT_BACKGROUND_W - DIALOG_MARGIN_RIGHT
#define EXPORT_BACKGROUND_Y                     DIALOG_Y - EXPORT_BACKGROUND_H - DIALOG_PADDING_LEFT * 2
#define EXPORT_BUTTON_Y                         DIALOG_Y - RESET_BUTTON_H
#define LOCK_BUTTON_X                           CONTROL_X
#define PICKUP_BUTTON_X                         CONTROL_X + LOCK_BUTTON_W + TO_REAL_W(0.002)
#define MOVE_VALUE_X                            CONTROL_X + MOVE_TITLE_W + TO_REAL_W(0.0075)
#define ROTATE_TITLE_X                          VERTICAL_MODE_CHECKBOX_X
#define ROTATE_VALUE_X                          ROTATE_TITLE_X + ROTATE_TITLE_W + TO_REAL_W(0.0075)

#define VERTICAL_MODE_ON_TEXTURE                "\a3\3DEN\Data\Displays\Display3DEN\ToolBar\vert_ASL_ca.paa"
#define VERTICAL_MODE_OFF_TEXTURE               "\a3\3DEN\Data\Displays\Display3DEN\ToolBar\vert_ATL_ca.paa"

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
        CancelButton,
        LockModeButton,
        PickupButton,
        HeightTitle,
        HeightShortcutPicture,
        VerticalModeCheckbox,
        HeightSlider,
        HeightResetButton,
        HeightValue,
        HorizontalOffsetTitle,
        HorizontalOffsetShortcutPicture,
        HorizontalOffsetSlider,
        HorizontalOffsetResetButton,
        HorizontalOffsetValue,
        DistanceTitle,
        DistanceShortcutPicture,
        DistanceSlider,
        DistanceValue,
        DistanceResetButton,
        PitchTitle,
        PitchShortcutText,
        PitchShortcutPicture,
        PitchSlider,
        PitchValue,
        PitchResetButton,
        BankTitle,
        BankShortcutText,
        BankShortcutPicture,
        BankSlider,
        BankValue,
        BankResetButton,
        DirectionTitle,
        DirectionShortcutText,
        DirectionShortcutPicture,
        DirectionSlider,
        DirectionResetButton,
        DirectionValue
    };

    class RscBase {
        idc = -1;
        access = 0;
        type = 0;
        style = ST_LEFT;

        tooltip = "";
        tooltipMaxWidth = TOOLTIP_MAX_WIDTH;
        tooltipColorShade[] = BUTTON_BG_COLOR;
        tooltipColorText[] = BUTTON_TEXT_COLOR;
        tooltipColorBox[] = {0, 0, 0, 0};

        colorBackground[] = BUTTON_BG_COLOR;
        colorText[] = BUTTON_TEXT_COLOR;

        x = 0;
        y = 0;
        h = 0;
        w = 0;

        text = "";
        font = FONT_TYPE;
        sizeEx = FONT_SIZE;
        fixedWidth = 0;
        shadow = 0;
        lineSpacing = 0;
    };

    class RscSliderBase : RscBase {
        type = 43;
        style = 1024;
        w = SLIDER_BASE_W;
        h = SLIDER_BASE_H;
        color[] = {1, 1, 1, 0.8};
        colorActive[] = {1, 1, 1, 1};
        arrowEmpty = "\a3\3DEN\Data\Controls\CtrlXSlider\arrowEmpty_ca.paa";
        arrowFull = "\a3\3DEN\Data\Controls\CtrlXSlider\arrowFull_ca.paa";
        border = "\a3\3DEN\Data\Controls\CtrlXSlider\border_ca.paa";
        thumb = "\a3\3DEN\Data\Controls\CtrlXSlider\thumb_ca.paa";
    };

    class RscButton : RscBase {
        type = 1;
        style = ST_CENTER;

        colorText[] = BUTTON_TEXT_COLOR;
        colorDisabled[] = DISABLED_COLOR;
        colorBackground[] = BUTTON_BG_COLOR;
        colorBackgroundDisabled[] = DISABLED_COLOR;
        colorBackgroundActive[] = BUTTON_ACTIVE_COLOR;
        colorFocused[] = BUTTON_BG_COLOR;
        colorShadow[] = {0, 0, 0, 0};
        colorBorder[] = {0, 0, 0, 0};

        soundEnter[] = {"",0.1,1};
        soundPush[] = {"",0.1,1};
        soundClick[] = {"",0.1,1};
        soundEscape[] = {"",0.1,1};

        offsetX = 0;
        offsetY = 0;
        offsetPressedX = 0.001;
        offsetPressedY = 0.001;
        borderSize = 0;
    };

    class TitleBase : RscBase {
        colorBackground[] = {0, 0, 0, 0};

        x = TITLE_X;
        w = TITLE_BASE_W;
        h = TITLE_BASE_H;
    };

    class ShortcutText : RscBase {
        colorText[] = {0.9, 0.9, 0.9, 1};
        colorBackground[] = {0, 0, 0, 0};

        x = SHORTCUT_TEXT_X;
        w = SHORTCUT_TEXT_W;
        h = ROW_BASE_H;

        text = "Ctrl/Shift/Alt +";
        sizeEx = FONT_SIZE * 0.9;
    };

    class ShortcutPicture : RscBase {
        style = ST_PICTURE;
        colorBackground[] = {0, 0, 0, 0};

        x = SHORTCUT_PICTURE_X;
        w = SHORTCUT_PICTURE_W;
        h = SHORTCUT_PICTURE_H;

        text = ADDON_PATH(resources\horizontal.paa);
    };

    class ValueBase : RscBase {
        style = ST_RIGHT;

        colorBackground[] = {0, 0, 0, 0};

        x = SLIDER_VALUE_X;
        w = VALUE_BASE_W;
        h = VALUE_BASE_H;
        text = "-10.00001";
    };

    class ResetButtonBase : RscButton {
        w = SLIDER_BASE_H;
        h = SLIDER_BASE_H;
        x = RESET_BUTTON_X;

        tooltip = "Reset slider to default value.";

        text = "X";

        offsetPressedX = 0;
        offsetPressedY = 0;
    };

    class RscCombo : RscBase {
        type = 4;
        style = 0;

        w = COMBO_W;
        h = TITLE_BASE_H;

        wholeHeight = DIALOG_H * 0.75;
        maxHistoryDelay = 1;

        colorBackground[] = {0.05, 0.05, 0.05, 1};
        colorSelectBackground[] = {BUTTON_ACTIVE_COLOR};

        colorText[] = {BUTTON_TEXT_COLOR};
        colorDisabled[] = {BUTTON_TEXT_COLOR};
        colorSelect[] = {0, 0, 0, 1};

        colorTextRight[] = {1, 1, 1, 1};
        colorSelectRight[] = {1, 1, 1, 0.25};
        colorSelect2Right[] = {1, 1, 1, 1};

        colorPicture[] = {1, 1, 1, 1};
        colorPictureSelected[] = {1, 1, 1, 1};
        colorPictureDisabled[] = {1, 1, 1, 0.25};

        colorPictureRight[] = {1, 1, 1, 1};
        colorPictureRightSelected[] = {1, 1, 1, 1};
        colorPictureRightDisabled[] = {1, 1, 1, 0.25};

        arrowEmpty = "\a3\3DEN\Data\Controls\ctrlCombo\arrowEmpty_ca.paa";
        arrowFull = "\a3\3DEN\Data\Controls\ctrlCombo\arrowFull_ca.paa";

        soundEnter[] = {"",0.1,1};
        soundPush[] = {"",0.1,1};
        soundClick[] = {"",0.1,1};
        soundEscape[] = {"",0.1,1};
        soundSelect[] = {"",0.1,1};
        soundExpand[] = {"",0.1,1};
        soundCollapse[] = {"",0.1,1};

        class ComboScrollBar {
            width = 0;
            height = 0;
            scrollSpeed = 0.01;

            arrowEmpty = "\a3\3DEN\Data\Controls\ctrlDefault\arrowEmpty_ca.paa";
            arrowFull = "\a3\3DEN\Data\Controls\ctrlDefault\arrowFull_ca.paa";
            border = "\a3\3DEN\Data\Controls\ctrlDefault\border_ca.paa";
            thumb = "\a3\3DEN\Data\Controls\ctrlDefault\thumb_ca.paa";

            color[] = {1, 1, 1, 1};
        };
    };

    class VerticalModeCheckboxBase : RscBase {
        type = 77;

        tooltip = "Toggle vertical mode (V)"; 

        checked = 1;

        color[] = BUTTON_TEXT_COLOR;
        colorFocused[] = BUTTON_TEXT_COLOR;
        colorHover[] = BUTTON_TEXT_COLOR;
        colorPressed[] = BUTTON_TEXT_COLOR;
        colorDisabled[] = DISABLED_COLOR;

        colorBackground[] = BUTTON_BG_COLOR;
        colorBackgroundFocused[] = BUTTON_BG_COLOR;
        colorBackgroundHover[] = BUTTON_ACTIVE_COLOR;
        colorBackgroundPressed[] = BUTTON_ACTIVE_COLOR;
        colorBackgroundDisabled[] = DISABLED_COLOR;

        textureChecked = VERTICAL_MODE_ON_TEXTURE;
        textureUnchecked = VERTICAL_MODE_OFF_TEXTURE;
        textureFocusedChecked = VERTICAL_MODE_ON_TEXTURE;
        textureFocusedUnchecked = VERTICAL_MODE_OFF_TEXTURE;
        textureHoverChecked = VERTICAL_MODE_ON_TEXTURE;
        textureHoverUnchecked = VERTICAL_MODE_OFF_TEXTURE;
        texturePressedChecked = VERTICAL_MODE_ON_TEXTURE;
        texturePressedUnchecked = VERTICAL_MODE_OFF_TEXTURE;
        textureDisabledChecked = VERTICAL_MODE_ON_TEXTURE;
        textureDisabledUnchecked = VERTICAL_MODE_OFF_TEXTURE;

        soundClick[] = {"", 0.09, 1};
        soundEnter[] = {"", 0.09, 1};
        soundPush[] = {"", 0.09, 1};
        soundEscape[] = {"", 0.09, 1};
    };
//--------------------------
    class ExportBackground : RscBase {
        idc = SETTINGS_EXPORT_BACKGROUND_IDC;

        colorText[] = {0, 0, 0, 0};
        colorBackground[] = DIALOG_BG_COLOR;
        colorDisabled[] = DISABLED_COLOR;
        colorBackgroundDisabled[] = DISABLED_COLOR;

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

        text = "Export";
        action = "[] call plank_ui_fnc_exportButtonClick";
        tooltip = "Exports player placed objects as SQF script to clipboard. Only works in SP.";
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

        x = CONFIRM_BUTTON_X;
        y = CONTROL_HALF_Y(FORT_CONFIRM_LOCK_ROW_INDEX);
        w = CONFIRM_BUTTON_W;
        h = RESET_BUTTON_H;

        tooltip = "Confirm object placement (R).";
        text = "Confirm";
        action = "[] call plank_ui_fnc_confirmButtonClick";
    };

    class CancelButton : RscButton {
        idc = SETTINGS_CANCEL_BUTTON_IDC;

        x = CANCEL_BUTTON_X;
        y = CONTROL_HALF_Y(FORT_CONFIRM_LOCK_ROW_INDEX);
        w = CONFIRM_BUTTON_W;
        h = RESET_BUTTON_H;

        tooltip = "Cancel object placement (Q).";
        text = "Cancel";
        action = "[] call plank_ui_fnc_cancelButtonClick";
    };

    class LockModeButton : RscButton {
        idc = SETTINGS_LOCK_MODE_BUTTON_IDC;

        x = LOCK_BUTTON_X;
        y = CONTROL_HALF_Y(FORT_CONFIRM_LOCK_ROW_INDEX);
        w = LOCK_BUTTON_W;
        h = RESET_BUTTON_H;

        tooltip = "Locks placed object in place (F).";
        text = "Unlock";
        action = "[] call plank_ui_fnc_lockModeButtonClick";
    };

    class PickupButton : RscButton {
        idc = SETTINGS_PICKUP_BUTTON_IDC;

        x = PICKUP_BUTTON_X;
        y = CONTROL_HALF_Y(FORT_CONFIRM_LOCK_ROW_INDEX);
        w = PICKUP_BUTTON_W;
        h = RESET_BUTTON_H;

        tooltip = "Pick up your previously placed object (D).";
        text = "Pick up";
        action = "[] call plank_ui_fnc_pickupButtonClick";
    };
//--------------------------
    class HeightTitle : TitleBase {
        idc = SETTINGS_HEIGHT_TITLE_IDC;
        y = CONTROL_Y(HEIGHT_ROW_INDEX);
        text = "Height";
    };

    class HeightShortcutPicture : ShortcutPicture {
        idc = SETTINGS_HEIGHT_SHORTCUT_PICTURE_IDC;
        y = SHORTCUT_PICTURE_Y(HEIGHT_ROW_INDEX);

        tooltip = "Hold Left mouse button and move mouse up/down.";
        text = ADDON_PATH(resources\vertical.paa);
    };

    class VerticalModeCheckbox : VerticalModeCheckboxBase {
        idc = SETTINGS_VERTICAL_MODE_CHECKBOX_IDC;

        x = VERTICAL_MODE_CHECKBOX_X;
        y = VERTICAL_MODE_CHECKBOX_Y;
        w = VERTICAL_MODE_CHECKBOX_W;
        h = VERTICAL_MODE_CHECKBOX_H;

        action = "[] call plank_ui_fnc_heightModeButtonClick";
    };

    class HeightSlider : RscSliderBase {
        idc = SETTINGS_HEIGHT_SLIDER_IDC;
        x = CONTROL_X;
        y = SLIDER_Y(HEIGHT_ROW_INDEX);
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateHeightSliderValue";
    };
    
    class HeightValue : ValueBase {
        idc = SETTINGS_HEIGHT_VALUE_IDC;
        y = SLIDER_Y(HEIGHT_ROW_INDEX);
    };

    class HeightResetButton : ResetButtonBase {
        idc = SETTINGS_HEIGHT_RESET_BUTTON_IDC;
        y = SLIDER_Y(HEIGHT_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetHeightSlider";
    };
//--------------------------
    class HorizontalOffsetTitle : TitleBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_TITLE_IDC;
        y = CONTROL_Y(HORIZONTAL_OFFSET_ROW_INDEX);
        text = "Horizontal";
    };

    class HorizontalOffsetShortcutPicture : ShortcutPicture {
        idc = SETTINGS_HORIZONTAL_OFFSET_SHORTCUT_PICTURE_IDC;
        y = SHORTCUT_PICTURE_Y(HORIZONTAL_OFFSET_ROW_INDEX);

        tooltip = "Hold Left mouse button and move mouse left/right.";
    };

    class HorizontalOffsetSlider : RscSliderBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_SLIDER_IDC;
        x = CONTROL_X;
        y = SLIDER_Y(HORIZONTAL_OFFSET_ROW_INDEX);
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateHorizontalOffsetSliderValue";
    };

    class HorizontalOffsetValue : ValueBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_VALUE_IDC;
        y = SLIDER_Y(HORIZONTAL_OFFSET_ROW_INDEX);
    };

    class HorizontalOffsetResetButton : ResetButtonBase {
        idc = SETTINGS_HORIZONTAL_OFFSET_RESET_BUTTON_IDC;
        y = SLIDER_Y(HORIZONTAL_OFFSET_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetHorizontalOffsetSlider";
    };
//--------------------------
    class DistanceTitle : TitleBase {
        idc = SETTINGS_DISTANCE_TITLE_IDC;
        y = CONTROL_Y(DISTANCE_ROW_INDEX);
        text = "Distance";
    };

    class DistanceShortcutPicture : ShortcutPicture {
        idc = SETTINGS_DISTANCE_SHORTCUT_PICTURE_IDC;
        y = SHORTCUT_PICTURE_Y(DISTANCE_ROW_INDEX);

        tooltip = "Use mouse scroll wheel.";
        text = ADDON_PATH(resources\scroll.paa);
    };

    class DistanceSlider : RscSliderBase {
        idc = SETTINGS_DISTANCE_SLIDER_IDC;
        x = CONTROL_X;
        y = SLIDER_Y(DISTANCE_ROW_INDEX);
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateDistanceSliderValue";
    };

    class DistanceValue : ValueBase {
        idc = SETTINGS_DISTANCE_VALUE_IDC;
        y = SLIDER_Y(DISTANCE_ROW_INDEX);
    };

    class DistanceResetButton : ResetButtonBase {
        idc = SETTINGS_DISTANCE_RESET_BUTTON_IDC;
        y = SLIDER_Y(DISTANCE_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetDistanceSlider";
    };
//--------------------------
    class PitchTitle : TitleBase {
        idc = SETTINGS_PITCH_TITLE_IDC;
        y = CONTROL_Y(PITCH_ROW_INDEX);
        text = "Pitch";
    };

    class PitchShortcutText : ShortcutText {
        idc = SETTINGS_PITCH_SHORTCUT_TEXT_IDC;
        y = CONTROL_Y(PITCH_ROW_INDEX);
    };

    class PitchShortcutPicture : ShortcutPicture {
        idc = SETTINGS_PITCH_SHORTCUT_PICTURE_IDC;
        y = SHORTCUT_PICTURE_Y(PITCH_ROW_INDEX);

        tooltip = "Hold Shift/Ctrl/Alt and Left mouse button and move mouse up/down.";
        text = ADDON_PATH(resources\vertical.paa);
    };

    class PitchSlider : RscSliderBase {
        idc = SETTINGS_PITCH_SLIDER_IDC;
        x = CONTROL_X;
        y = SLIDER_Y(PITCH_ROW_INDEX);
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updatePitchSliderValue";
    };

    class PitchValue : ValueBase {
        idc = SETTINGS_PITCH_VALUE_IDC;
        y = SLIDER_Y(PITCH_ROW_INDEX);
    };

    class PitchResetButton : ResetButtonBase {
        idc = SETTINGS_PITCH_RESET_BUTTON_IDC;
        y = SLIDER_Y(PITCH_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetPitchSlider";
    };
//--------------------------
    class BankTitle : TitleBase {
        idc = SETTINGS_BANK_TITLE_IDC;
        y = CONTROL_Y(BANK_ROW_INDEX);
        text = "Bank";
    };

    class BankShortcutText : ShortcutText {
        idc = SETTINGS_BANK_SHORTCUT_TEXT_IDC;
        y = CONTROL_Y(BANK_ROW_INDEX);
    };

    class BankShortcutPicture : ShortcutPicture {
        idc = SETTINGS_BANK_SHORTCUT_PICTURE_IDC;
        y = SHORTCUT_PICTURE_Y(BANK_ROW_INDEX);

        tooltip = "Hold Shift/Ctrl/Alt and Left mouse button and move mouse left/right.";
    };

    class BankSlider : RscSliderBase {
        idc = SETTINGS_BANK_SLIDER_IDC;
        x = CONTROL_X;
        y = SLIDER_Y(BANK_ROW_INDEX);
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateBankSliderValue";
    };

    class BankValue : ValueBase {
        idc = SETTINGS_BANK_VALUE_IDC;
        y = SLIDER_Y(BANK_ROW_INDEX);
    };

    class BankResetButton : ResetButtonBase {
        idc = SETTINGS_BANK_RESET_BUTTON_IDC;
        y = SLIDER_Y(BANK_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetBankSlider";
    };
//--------------------------
    class DirectionTitle : TitleBase {
        idc = SETTINGS_DIRECTION_TITLE_IDC;
        y = CONTROL_Y(DIRECTION_ROW_INDEX);
        text = "Direction";
    };

    class DirectionShortcutText : ShortcutText {
        idc = SETTINGS_DIRECTION_SHORTCUT_TEXT_IDC;
        y = CONTROL_Y(DIRECTION_ROW_INDEX);
    };

    class DirectionShortcutPicture : ShortcutPicture {
        idc = SETTINGS_DIRECTION_SHORTCUT_PICTURE_IDC;
        y = SHORTCUT_PICTURE_Y(DIRECTION_ROW_INDEX);

        tooltip = "Hold Shift/Ctrl/Alt and use mouse scroll wheel.";
        text = ADDON_PATH(resources\scroll.paa);
    };

    class DirectionSlider : RscSliderBase {
        idc = SETTINGS_DIRECTION_SLIDER_IDC;
        x = CONTROL_X;
        y = SLIDER_Y(DIRECTION_ROW_INDEX);
        onSliderPosChanged = "[_this select 1] call plank_ui_fnc_updateDirectiontSliderValue";
    };

    class DirectionValue : ValueBase {
        idc = SETTINGS_DIRECTION_VALUE_IDC;
        y = SLIDER_Y(DIRECTION_ROW_INDEX);
    };

    class DirectionResetButton : ResetButtonBase {
        idc = SETTINGS_DIRECTION_RESET_BUTTON_IDC;
        y = SLIDER_Y(DIRECTION_ROW_INDEX);
        action = "[] call plank_ui_fnc_resetDirectionSlider";
    };
//--------------------------
    class DialogBackground : RscBase {
        idc = SETTINGS_BACKGROUND_IDC;

        colorBackground[] = DIALOG_BG_COLOR;
        colorText[] = {0, 0, 0, 0};

        x = DIALOG_X;
        y = DIALOG_Y;
        h = DIALOG_H;
        w = DIALOG_W;
    };
};