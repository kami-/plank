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

    [_unit, _fortifications] call plank_deploy_fnc_init;
};

/**
 * Returns the available fortification names and their indexes.
 * @return Array of fortification name, index pairs
 */
plank_api_fnc_getFortifications = {
    [] call plank_deploy_fnc_getFortifications;
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