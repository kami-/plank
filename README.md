Plank
=====

Plank is a fortification deployment script for ArmA

Usage
=====

1. Copy `\plank` directory into the mission directory
2. Put line `#include "plank\settings_dialog.h"` in `description.ext`
3. Put line `call compile preprocessFileLineNumbers "plank\plank_init.sqf";` in `init.sqf`
4. Call function to add fortifications to a unit with `[player, [2, 2, 2, 2, 2, 2, 2, 2]] call plank_deploy_fnc_init;`

Fortifications
==============

To add new fortifications edit `\plank\fortifications.sqf`.

* **Action text** - The text displayed by the action
* **Classname** - The classname of the object
* **Distance** - Minimum distance of the object from the player, in metres
* **Direction** - Direction the object will face, in degrees
* **Direction range** - The range you can turn the object in degrees
* **Code** - A piece of code that will be executed when the object placement is confirmed. Use {}, if you don't want to use it. The unit and object placed are passed as arguments to the code.
