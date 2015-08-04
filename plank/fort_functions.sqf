#include "plank_macros.h"

#include "\userconfig\plank\log\fort.h"
#include "logbook.h"


plank_fort_fnc_getDirectionOrDefault = {
    FUN_ARGS_2(_fortIndex,_dataIndex);

    (FORTS_DATA) select _fortIndex select (IDX)
};