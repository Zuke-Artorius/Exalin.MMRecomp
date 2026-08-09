#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "playermodelmanager_api.h"
#include "proxymm_custom_actor.h"

#include "gExalinAdultSkel.h"


PLAYERMODELMANAGER_CALLBACK_REGISTER_MODELS void registerBase() {

    PlayerModelManagerHandle exalinHandle = PLAYERMODELMANAGER_REGISTER_MODEL("pmm_exalin_pack", PMM_MODEL_TYPE_MODEL_PACK);
    PlayerModelManager_setAuthor(exalinHandle, "Zuke");
    PlayerModelManager_setDisplayName(exalinHandle, "Exalin");
    
    PlayerModelManagerHandle exalinHuman = PLAYERMODELMANAGER_REGISTER_MODEL("pmm_exalin_human", PMM_MODEL_TYPE_ADULT);
    PlayerModelManager_setAuthor(exalinHuman, "Zuke");
    PlayerModelManager_setDisplayName(exalinHuman, "Exalin");

    PlayerModelManager_setSkeleton(exalinHuman, &gExalinAdultSkel);

    PlayerModelManager_addHandleToPack(exalinHuman, exalinHandle);

}