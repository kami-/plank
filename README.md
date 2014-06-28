Plank
=====

Plank is a simple but extremely useful open-source fortification script. It can be use in a broad spectrum, base building, FOB building or on-the-fly-defenses.It was designed in the mindset of simplicity with regards to both mission implementation and player use.

A demonstration of how it works and looks ingame:

* [Arma 2 screenshot](http://i.imgur.com/idesKIO.jpg)
* [Arma 2 demo](http://gfycat.com/BasicRemarkableFoxhound)
* [Arma 3 demo](http://gfycat.com/PitifulScientificAmazonparrot)

Script works for both Arma 3 and Arma 2, (showcase mission works only for Arma 3) no alteration is needed in order for it to work in either of the games. Fully tested in MP without issues. This project is fully open-source (MIT license) so please feel free to contribute or fork as you require, but you must include the license file in your version.

Huge thanks to [ARK](http://ark-group.org/) for suggestions and testing.

Usage
=====

##Prerequisites

1. Copy `\plank` directory into the mission directory
2. Put line `#include "plank\plank.h"` in `description.ext`
3. Put line `call compile preprocessFileLineNumbers "plank\plank_init.sqf";` in `init.sqf`
4. To add fortifications to a unit use `[_unit, [<number of 1. fort>, <number of 2. fort>, ..., <number of n. fort>]] call plank_deploy_fnc_init`. For example: `[player, [2, 1, 2, 2, 0, 2, 0, 0]] call plank_deploy_fnc_init;`

##Ingame

The player will have an action for each fortification with the available numbers.
Using an action will create the selected fortification. The player can move freely while the fortification "follows" them around. While in the deployment mode, the player cannot create other fortifications, until the deployment is confirmed or cancelled. The player also gets 3 new actions:

* **Confirm Deployment** - This action will deploy the fortification at its current position and properties. It decreses the available numbers of the fortification.
* **Cancel Deployment** - This will cancel the deployment and "refunds" the fortification.
* **Open Settings** - Opens a dialog at the bottom right corner of screen. Here the player can set/reset the different properties of the fortification. Close the dialog with `ESC`, it will save the properties. The player cannot move while the dialog is open.

After confirmation or cancellation of the fortification the player is free to place any of the other fortifications left.

Fortifications
==============

To add new fortifications edit either `plank\arma2_fortifications.sqf` for Arma 2, or `plank\arma3_fortifications.sqf` for Arma 3.

* **Action text** - The text displayed by the action.
* **Classname** - The classname of the object to be placed.
* **Distance** - Minimum distance of the object from the player, in metres.
* **Direction** - Direction the object will be rotated initially, in degrees (minimum 0, maximum 360).
* **Direction range** - The range you can turn the object, in degrees (minimum 0, maximum 360). This means that the player will be able to set the direction of the object between `direction - direction_range / 2` and `direction + direction_range / 2` degrees. For example given 180 direction and 60 direction range, player will be able turn the object between 150 and 210 degrees.
* **Code** - A piece of code that will be executed when the object placement is confirmed. Set it to `{}`, if you don't want to use it. The unit who confirmed the placement and the object placed, are passed as arguments to the code. An example code that hints the players name could look like `{hint str (_this select 0);}`.
