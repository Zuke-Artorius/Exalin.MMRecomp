#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "playermodelmanager_api.h"
#include "proxymm_custom_actor.h"

#include "gExalinAdultSkel.h"
#include "gExalinAdultFistsSkel.h"
#include "gExalinAdultBottleHandSkel.h"

static void* gExalinMouth[] = {
    gExalinAdultSkel_exalin_mouth_big_closed_ci8,
    gExalinAdultSkel_exalin_mouth_big_teeth_ci8,
    gExalinAdultSkel_exalin_mouth_big_open_ci8,
    gExalinAdultSkel_exalin_mouth_big_smile_ci8,
};

TexturePtr gExalinEyeR[] = {
    gExalinAdultSkel_exalin_eyes_r_ci8,
    gExalinAdultSkel_exalin_eyes_r_half_ci8,
    gExalinAdultSkel_exalin_eyes_r_close_ci8,
    gExalinAdultSkel_exalin_eyes_r_right_ci8,
    gExalinAdultSkel_exalin_eyes_r_left_ci8,
    gExalinAdultSkel_exalin_eyes_r_shock_ci8,
    gExalinAdultSkel_exalin_eyes_r_down_ci8,
    gExalinAdultSkel_exalin_eyes_r_clench_ci8,
};

PLAYERMODELMANAGER_CALLBACK_REGISTER_MODELS void registerBase() {

    PlayerModelManagerHandle exalinHandle = PLAYERMODELMANAGER_REGISTER_MODEL("pmm_exalin_pack", PMM_MODEL_TYPE_MODEL_PACK);
    PlayerModelManager_setAuthor(exalinHandle, "Zuke");
    PlayerModelManager_setDisplayName(exalinHandle, "Exalin");
    
    PlayerModelManagerHandle exalinHuman = PLAYERMODELMANAGER_REGISTER_MODEL("pmm_exalin_human", PMM_MODEL_TYPE_ADULT);
    PlayerModelManager_setAuthor(exalinHuman, "Zuke");
    PlayerModelManager_setDisplayName(exalinHuman, "Exalin");

    PlayerModelManager_setEyesTextures(exalinHuman, gExalinEyeR);
    PlayerModelManager_setMouthTextures(exalinHuman, gExalinMouth);

    PlayerModelManager_setSkeleton(exalinHuman, &gExalinAdultSkel);

    PlayerModelManager_setDisplayList(exalinHuman, PMM_DL_LHAND_BOTTLE, gExalinAdultBottleHandSkel_bone015_gLinkZoraLeftHandLimb_mesh_layer_Opaque);
    PlayerModelManager_setDisplayList(exalinHuman, PMM_DL_LFIST, gExalinAdultFistsSkel_bone015_gLinkZoraLeftHandLimb_mesh_layer_Opaque);
    PlayerModelManager_setDisplayList(exalinHuman, PMM_DL_RFIST, gExalinAdultFistsSkel_bone018_gLinkZoraRightHandLimb_mesh_layer_Opaque);

    PlayerModelManager_addHandleToPack(exalinHuman, exalinHandle);

}

TexturePtr gExalinEyeL[] = {
    gExalinAdultSkel_exalin_eyes_l_ci8,
    gExalinAdultSkel_exalin_eyes_l_half_ci8,
    gExalinAdultSkel_exalin_eyes_l_close_ci8,
    gExalinAdultSkel_exalin_eyes_l_right_ci8,
    gExalinAdultSkel_exalin_eyes_l_left_ci8,
    gExalinAdultSkel_exalin_eyes_l_shock_ci8,
    gExalinAdultSkel_exalin_eyes_l_down_ci8,
    gExalinAdultSkel_exalin_eyes_l_clench_ci8,
};

extern struct PlayerFaceIndices {
    /* 0x0 */ u8 eyeIndex;
    /* 0x1 */ u8 mouthIndex;
} PlayerFaceIndices; // size = 0x2

extern struct PlayerFaceIndices sPlayerFaces[];

RECOMP_HOOK("Player_DrawImpl") void on_Player_DrawImpl(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount, s32 lod,
                     PlayerTransformation playerForm, s32 boots, s32 face, OverrideLimbDrawFlex overrideLimbDraw,
                     PostLimbDrawFlex postLimbDraw, Actor* actor) {
    s32 eyeIndex = GET_EYE_INDEX_FROM_JOINT_TABLE(jointTable);
    s32 mouthIndex = GET_MOUTH_INDEX_FROM_JOINT_TABLE(jointTable);

    OPEN_DISPS(play->state.gfxCtx);

    if (eyeIndex < 0) {
        eyeIndex = sPlayerFaces[face].eyeIndex;
    }

    if (playerForm == PLAYER_FORM_GORON) {
        if ((eyeIndex >= PLAYER_EYES_ROLL_RIGHT) && (eyeIndex <= PLAYER_EYES_ROLL_DOWN)) {
            eyeIndex = PLAYER_EYES_OPEN;
        } else if (eyeIndex == PLAYER_EYES_7) {
            eyeIndex = PLAYER_EYES_ROLL_RIGHT;
        }
    }

    if (mouthIndex < 0) {
        mouthIndex = sPlayerFaces[face].mouthIndex;
    }

    if (playerForm == PLAYER_FORM_HUMAN) {
        gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(gExalinEyeL[eyeIndex]));
    }

    CLOSE_DISPS(play->state.gfxCtx);
}