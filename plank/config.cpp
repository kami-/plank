#include "plank_macros.h"

class CfgPatches {
    class Plank {
        units[] = {};
        weapons[] = {};
        requiredVersion = 1.0;
        requiredAddons[] = {"CBA_MAIN"};
        author = "Kami";
        authorUrl = "https://github.com/kami-";
    };
};

class Extended_PreInit_EventHandlers {
    class Plank {
        init = "[] call compile preProcessFileLineNumbers 'x\ark\addons\plank\plank_preinit.sqf';";
    };
};

class Extended_PostInit_EventHandlers {
    class Plank {
        init = "[] call compile preProcessFileLineNumbers 'x\ark\addons\plank\plank_postinit.sqf';";
    };
};

#include "plank.h"