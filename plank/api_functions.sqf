#include "plank_macros.h"

/**
 * Removes all fortifications, including the one currently being placed, from a unit.
 * Closes the currently open dialog aswell.
 * @param _unit The unit to remove the fortifications from
 */
plank_api_fnc_forceRemoveAllFortifications = {
    FUN_ARGS_1(_unit);

    [_unit] call plank_delpoy_fnc_forceRemoveAllFortifications;
};

/**
 * Adds fortifications to a unit. Removes all previous fortifications, including the one currently being placed.
 * @param _unit The unit to give fortifications to
 * @param _fortifications An array of number of fortifications, [<number of 1. fort>, <number of 2. fort>, ..., <number of n. fort>]
 *              Fortifications are found in plank\armaX_fortifications.sqf
 */
plank_api_fnc_forceAddFortifications = {
    FUN_ARGS_2(_unit,_fortifications);

    [_unit, _fortifications] call plank_deploy_fnc_forceAddFortifications;
};

/**
 * Returns the available fortification names and their indexes.
 * @return Array of fortification name, index pairs
 */
plank_api_fnc_getFortifications = {
    [] call plank_deploy_fnc_getFortifications;
};

/**
 * Adds a new deployable fortification.
 * Cancels any ongoing deployment.
 * @param _unit The unit to add the fortifications to
 * @param _fortData Array of fortification data consisting [_displayName, _className, _minDistance, _direction, _directionRange, _code]
 * @return The index of the newly added fortification
 */
plank_api_fnc_addNewFortification = {
    FUN_ARGS_2(_unit,_forData);

    [_unit, _forData] call plank_deploy_fnc_addNewFortification;
};

/**
 * Adds a new deployable fortification with default fort data.
 * Cancels any ongoing deployment.
 * @param _unit The unit to add the fortifications to
 * @param _className Class name of the object to be deployes
 * @param _displayName (optional) Display name of the fortification in the dialog
 * @return The index of the newly added fortification
 */
plank_api_fnc_addNewDefaultFortification = {
    FUN_ARGS_3(_unit,_className,_displayName);

    [_unit, _className, _displayName] call plank_deploy_fnc_addNewDefaultFortification;
};

/**
 * Adds a new deployable fortification with default fort data using the bounding box of the object.
 * Cancels any ongoing deployment.
 * @param _unit The unit to add the fortifications to
 * @param _className Class name of the object to be deployes
 * @param _displayName (optional) Display name of the fortification in the dialog
 * @return The index of the newly added fortification
 */
plank_api_fnc_addNewBoundingFortification = {
    FUN_ARGS_3(_unit,_className,_displayName);

    [_unit, _className, _displayName] call plank_deploy_fnc_addNewBoundingFortification;
};

/**
 * Adds given number of fortifications by index.
 * Cancels any ongoing deployment.
 * @param _unit The unit to add the fortifications to
 * @param _fortIndex The index of the fortification (use plank_api_fnc_getFortifications to get indexes)
 * @param _count Number of fortifications to add
 */
plank_api_fnc_addFortification = {
    FUN_ARGS_3(_unit,_fortIndex,_count);

    [_unit, _fortIndex, _count] call plank_deploy_fnc_addFortification;
};

/**
 * Removes given number of fortifications by index.
 * Cancels any ongoing deployment.
 * @param _unit The unit to remove the fortifications from
 * @param _fortIndex The index of the fortification (use plank_api_fnc_getFortifications to get indexes)
 * @param _count Number of fortifications to remove
 */
plank_api_fnc_removeFortification = {
    FUN_ARGS_3(_unit,_fortIndex,_count);

    [_unit, _fortIndex, _count] call plank_deploy_fnc_removeFortification;
};

/**
 * Exports fortification placed by the player as a script to the clipboard.
 * Only works in single player!
 */
plank_api_fnc_export = {
    [] call plank_export_fnc_export;
};