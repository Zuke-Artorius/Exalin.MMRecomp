#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "playermodelmanager_api.h"
#include "proxymm_custom_actor.h"

#include "gExalinAdultSkel.h"
#include "gExalinAdultFistsSkel.h"
#include "gExalinAdultBottleHandSkel.h"

#include "gExTwinSword1Blade.h"
#include "gExTwinSword1Handle.h"
#include "gExTwinSword2Blade.h"
#include "gExTwinSword2Handle.h"
#include "gExTwinSword3Blade.h"
#include "gExTwinSword3Handle.h"

#include "gExalinSheath1.h"
#include "gExalinSheath2.h"
#include "gExalinSheath3.h"

#include "gExShieldHero.h"

#include "gOcarinaDL.h"

#define MASK_ROTATE_X 0.f
#define MASK_ROTATE_Y 0.f
#define MASK_ROTATE_Z 0.f
#define MASK_SCALE 1.f
#define MASK_TRANSLATE_X -320.f
#define MASK_TRANSLATE_Y -320.f
#define MASK_TRANSLATE_Z 0.f

#define SHIELD_BACK_ROTATE_X 0.f
#define SHIELD_BACK_ROTATE_Y 0.f
#define SHIELD_BACK_ROTATE_Z 0.f
#define SHIELD_BACK_SCALE 0.f
#define SHIELD_BACK_TRANSLATE_X 0.f
#define SHIELD_BACK_TRANSLATE_Y 0.f
#define SHIELD_BACK_TRANSLATE_Z 180.f

#define SWORD_BACK_ROTATE_X 0.f
#define SWORD_BACK_ROTATE_Y 0.f
#define SWORD_BACK_ROTATE_Z 0.f
#define SWORD_BACK_SCALE 1.f
#define SWORD_BACK_TRANSLATE_X 0.f
#define SWORD_BACK_TRANSLATE_Y 0.f
#define SWORD_BACK_TRANSLATE_Z 180.f

Mtx gExalinMaskMtx;
Mtx gExalinShieldMtx;
Mtx gExalinSwordMtx;

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

    guPosition(&gExalinMaskMtx, MASK_ROTATE_X, MASK_ROTATE_Y, MASK_ROTATE_Z, MASK_SCALE, MASK_TRANSLATE_X, MASK_TRANSLATE_Y, MASK_TRANSLATE_Z);
    guPosition(&gExalinShieldMtx, SHIELD_BACK_ROTATE_X, SHIELD_BACK_ROTATE_Y, SHIELD_BACK_ROTATE_Z, SHIELD_BACK_SCALE, SHIELD_BACK_TRANSLATE_X, SHIELD_BACK_TRANSLATE_Y, SHIELD_BACK_TRANSLATE_Z);
    guPosition(&gExalinSwordMtx, SWORD_BACK_ROTATE_X, SWORD_BACK_ROTATE_Y, SWORD_BACK_ROTATE_Z, SWORD_BACK_SCALE, SWORD_BACK_TRANSLATE_X, SWORD_BACK_TRANSLATE_Y, SWORD_BACK_TRANSLATE_Z);

    PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_MASKS, &gExalinMaskMtx);
    PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SHIELD1_BACK, &gExalinShieldMtx);
    PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SHIELD2_BACK, &gExalinShieldMtx);
    PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SHIELD3_BACK, &gExalinShieldMtx);
    
    /*
    PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SWORD1_BACK, &gExalinSwordMtx);
    PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SWORD2_BACK, &gExalinSwordMtx);
    PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SWORD3_BACK, &gExalinSwordMtx);
    PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SWORD4_BACK, &gExalinSwordMtx);
    PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SWORD5_BACK, &gExalinSwordMtx);
    */
    PlayerModelManager_addHandleToPack(exalinHandle, exalinHuman);

    PlayerModelManagerHandle exalinSwordKokiri = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_sword_kokiri_pmm", PMM_MODEL_TYPE_SWORD_KOKIRI);
    PlayerModelManager_setAuthor(exalinSwordKokiri, "Zuke");
    PlayerModelManager_setDisplayName(exalinSwordKokiri, "Exalin");
    PlayerModelManager_setDisplayList(exalinSwordKokiri, PMM_DL_SWORD_KOKIRI_BLADE, gExTwinSword1Blade);
    PlayerModelManager_setDisplayList(exalinSwordKokiri, PMM_DL_SWORD_KOKIRI_HILT, gExTwinSword1Handle);
    PlayerModelManager_setDisplayList(exalinSwordKokiri, PMM_DL_SWORD_KOKIRI_SHEATH, gExalinSheath1);
    PlayerModelManager_addHandleToPack(exalinHandle, exalinSwordKokiri);

    PlayerModelManagerHandle exalinSwordRazor = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_sword_razor_pmm", PMM_MODEL_TYPE_SWORD_RAZOR);
    PlayerModelManager_setAuthor(exalinSwordRazor, "Zuke");
    PlayerModelManager_setDisplayName(exalinSwordRazor, "Exalin");
    PlayerModelManager_setDisplayList(exalinSwordRazor, PMM_DL_SWORD_RAZOR_BLADE, gExTwinSword2Blade);
    PlayerModelManager_setDisplayList(exalinSwordRazor, PMM_DL_SWORD_RAZOR_HILT, gExTwinSword2Handle);
    PlayerModelManager_setDisplayList(exalinSwordRazor, PMM_DL_SWORD_RAZOR_SHEATH, gExalinSheath2);
    PlayerModelManager_addHandleToPack(exalinHandle, exalinSwordRazor);

    PlayerModelManagerHandle exalinSwordGilded = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_sword_gilded_pmm", PMM_MODEL_TYPE_SWORD_GILDED);
    PlayerModelManager_setAuthor(exalinSwordGilded, "Zuke");
    PlayerModelManager_setDisplayName(exalinSwordGilded, "Exalin");
    PlayerModelManager_setDisplayList(exalinSwordGilded, PMM_DL_SWORD_GILDED_BLADE, gExTwinSword3Blade);
    PlayerModelManager_setDisplayList(exalinSwordGilded, PMM_DL_SWORD_GILDED_HILT, gExTwinSword3Handle);
    PlayerModelManager_setDisplayList(exalinSwordGilded, PMM_DL_SWORD_GILDED_SHEATH, gExalinSheath3);
    PlayerModelManager_addHandleToPack(exalinHandle, exalinSwordGilded);

    PlayerModelManagerHandle exalinShieldHero = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_shield_hero_pmm", PMM_MODEL_TYPE_SHIELD_HERO);
    PlayerModelManager_setAuthor(exalinShieldHero, "Zuke");
    PlayerModelManager_setDisplayName(exalinShieldHero, "Exalin");
    PlayerModelManager_setDisplayList(exalinShieldHero, PMM_DL_SHIELD_HERO, gExShieldHero);
    //PlayerModelManager_setDisplayList(exalinShieldHero, PMM_DL_SWORD_GILDED_SHEATH, gExalinSheath3DL);
    PlayerModelManager_addHandleToPack(exalinHandle, exalinShieldHero);

    PlayerModelManagerHandle exalinShieldMirror = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_shield_mirror_pmm", PMM_MODEL_TYPE_SHIELD_MIRROR);
    PlayerModelManager_setAuthor(exalinShieldMirror, "Zuke");
    PlayerModelManager_setDisplayName(exalinShieldMirror, "Exalin");
    PlayerModelManager_setDisplayList(exalinShieldMirror, PMM_DL_SHIELD_MIRROR, gExShieldHero);
    //PlayerModelManager_setDisplayList(exalinShieldMirror, PMM_DL_SWORD_GILDED_SHEATH, gExalinSheath3DL);
    PlayerModelManager_addHandleToPack(exalinHandle, exalinShieldMirror);

    PlayerModelManagerHandle exalinOcarina = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_ocarina_pmm", PMM_MODEL_TYPE_OCARINA_TIME);
    PlayerModelManager_setAuthor(exalinOcarina, "Zuke");
    PlayerModelManager_setDisplayName(exalinOcarina, "Exalin");
    PlayerModelManager_setDisplayList(exalinOcarina, PMM_DL_OCARINA_TIME, gOcarinaDL);
    PlayerModelManager_addHandleToPack(exalinHandle, exalinOcarina);
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

#include "anim/gExalinAdultSkel_okarina_endAnim.h"
#include "anim/gExalinAdultSkel_okarina_startAnim.h"
#include "anim/gExalinAdultSkel_okarina_swingAnim.h"
#include "anim/gExalinAdultSkel_okarina_walkAnim.h"
#include "anim/gExalinAdultSkel_okarina_walkbAnim.h"

extern LinkAnimationHeader gPlayerAnim_link_normal_okarina_end[];
extern LinkAnimationHeader gPlayerAnim_link_normal_okarina_start[];
extern LinkAnimationHeader gPlayerAnim_link_normal_okarina_swing[];
extern LinkAnimationHeader gPlayerAnim_clink_normal_okarina_walk[];
extern LinkAnimationHeader gPlayerAnim_clink_normal_okarina_walkB[];

void updateLink(PlayState* play) {
    Player* player = GET_PLAYER(play);
    if (player->transformation == PLAYER_FORM_HUMAN) {
        *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_link_normal_okarina_end) = gExalinAdultSkel_okarina_endAnim;
        *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_link_normal_okarina_start) = gExalinAdultSkel_okarina_startAnim;
        *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_link_normal_okarina_swing) = gExalinAdultSkel_okarina_swingAnim;
        *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_clink_normal_okarina_walk) = gExalinAdultSkel_okarina_walkAnim;
        *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_clink_normal_okarina_walkB) = gExalinAdultSkel_okarina_walkbAnim;
    }
}


RECOMP_CALLBACK("*", recomp_on_play_main)
void mainUpdate(PlayState* play) {
    updateLink(play);
}