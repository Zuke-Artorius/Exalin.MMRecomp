#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "playermodelmanager_api.h"
#include "proxymm_custom_actor.h"
#include "modelreplacer_api.h"
#include "z64save.h"
#include "z64item.h"
#include "gfx.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

#include "skel/gExalinAdultSkel.h"
#include "skel/gExalinAdultFistsSkel.h"
#include "skel/gExalinAdultBottleHandSkel.h"
#include "skel/gExalinAdultSkelVanillaSheath.h"
#include "skel/gExalinAdultDoubleSheathSkel.h"
#include "skel/gExalinAdultHoodSkel.h"
#include "skel/gExalinAdultLeftSheathSkel.h"

#include "dl/gExTwinSword1Blade.h"
#include "dl/gExTwinSword1Handle.h"
#include "dl/gExTwinSword2Blade.h"
#include "dl/gExTwinSword2Handle.h"
#include "dl/gExTwinSword3Blade.h"
#include "dl/gExTwinSword3Handle.h"
#include "dl/gExGreatSwordBlade.h"
#include "dl/gExGreatSwordHilt.h"

#include "dl/gExalinSheath1.h"
#include "dl/gExalinSheath2.h"
#include "dl/gExalinSheath3.h"
#include "dl/gExalinSheath1_001.h"
#include "dl/gExalinSheath2_001.h"
#include "dl/gExalinSheath3_001.h"

#include "dl/gExalinLeftSheathHandle_001.h"
#include "dl/gExalinRightSheathHandle_001.h"
#include "dl/gExalinLeftSheathHandle_002.h"
#include "dl/gExalinRightSheathHandle_002.h"
#include "dl/gExalinLeftSheathHandle_003.h"
#include "dl/gExalinRightSheathHandle_003.h"
#include "dl/gExalinLeftSheath_001.h"
#include "dl/gExalinLeftSheath_002.h"
#include "dl/gExalinLeftSheath_003.h"
#include "dl/gExalinRightSheath_001.h"
#include "dl/gExalinRightSheath_002.h"
#include "dl/gExalinRightSheath_003.h"

#include "dl/gExShieldDeku.h"
#include "dl/gExShieldHero.h"
#include "dl/gExShieldMirror.h"

#include "dl/gOcarinaDL.h"
#include "dl/gExalinFisher.h"
#include "dl/gExalinHood.h"
#include "dl/gExalinElegyShellHumanDL.h"

#include "gi/gGiCull.h"
#include "gi/gGiExalinSword1DL.h"
#include "gi/gGiExalinSword2DL.h"
#include "gi/gGiExalinSword3DL.h"
#include "gi/gGiExalinSword4DL.h"
#include "gi/gGiOcarinaDL.h"
#include "gi/gGiExalinHood.h"
#include "gi/gGiExalinFisher.h"

#include "dl/gExalinIconKokiriSword.h"
#include "dl/gExalinIconRazorSword.h"
#include "dl/gExalinIconGildedSword.h"
#include "dl/gExalinIconFairySword.h"
#include "dl/gExalinIconMaskHood.h"
#include "dl/gExalinIconMaskFisher.h"
#include "dl/gExalinIconOcarina.h"
#include "dl/gExalinIconEmpty.h"

#define MASK_ROTATE_X 0.f
#define MASK_ROTATE_Y 0.f
#define MASK_ROTATE_Z 0.f
#define MASK_SCALE 1.f
#define MASK_TRANSLATE_X -350.f
#define MASK_TRANSLATE_Y -120.f
#define MASK_TRANSLATE_Z 0.f

#define SHIELD_BACK_ROTATE_X 0.f
#define SHIELD_BACK_ROTATE_Y 0.f
#define SHIELD_BACK_ROTATE_Z 180.f
#define SHIELD_BACK_SCALE 0.f
#define SHIELD_BACK_TRANSLATE_X 0.f
#define SHIELD_BACK_TRANSLATE_Y -200.f
#define SHIELD_BACK_TRANSLATE_Z 0.f

#define SWORD_BACK_ROTATE_X 0.f
#define SWORD_BACK_ROTATE_Y 0.f
#define SWORD_BACK_ROTATE_Z -30.f
#define SWORD_BACK_SCALE 1.f
#define SWORD_BACK_TRANSLATE_X -800.f
#define SWORD_BACK_TRANSLATE_Y 75.f
#define SWORD_BACK_TRANSLATE_Z 50.f

#define ARROW_ROTATE_X 0.f
#define ARROW_ROTATE_Y 0.f
#define ARROW_ROTATE_Z 0.f
#define ARROW_SCALE 1.f
#define ARROW_TRANSLATE_X 0.f
#define ARROW_TRANSLATE_Y -200.f
#define ARROW_TRANSLATE_Z 0.f
#define BOWSTRING_OFFSET -100.f

Mtx gExalinMaskMtx;
Mtx gExalinShieldMtx;
Mtx gExalinSwordMtx;
Mtx gExalinArrowMtx;

TexturePtr gExalinMouth[] = {
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

PlayerModelManagerHandle gExalinModelHandle;
PlayerModelManagerHandle gExalinHoodHandle;
PlayerModelManagerHandle gExalinModelVanillaSheathHandle;
PlayerModelManagerHandle gExalinKokiriSwordHandle;
PlayerModelManagerHandle gExalinRazorSwordHandle;
PlayerModelManagerHandle gExalinGildedSwordHandle;
PlayerModelManagerHandle gExalinKokiriSwordShieldHandle;
PlayerModelManagerHandle gExalinRazorSwordShieldHandle;
PlayerModelManagerHandle gExalinGildedSwordShieldHandle;
PlayerModelManagerHandle gExalinFairySwordHandle;
PlayerModelManagerHandle gExalinHeroShieldHandle;
PlayerModelManagerHandle gExalinMirrorShieldHandle;
PlayerModelManagerHandle gExalinMaskFisherHandle;
PlayerModelManagerHandle gExalinOcarinaHandle;

PLAYERMODELMANAGER_CALLBACK_REGISTER_MODELS void registerBase() {

    PlayerModelManagerHandle exalinDualHandle = PLAYERMODELMANAGER_REGISTER_MODEL("pmm_exalin_dual_pack", PMM_MODEL_TYPE_MODEL_PACK);
        PlayerModelManager_setAuthor(exalinDualHandle, "Zuke");
        PlayerModelManager_setDisplayName(exalinDualHandle, "Exalin - Dual Wield");

    PlayerModelManagerHandle exalinShieldHandle = PLAYERMODELMANAGER_REGISTER_MODEL("pmm_exalin_shield_pack", PMM_MODEL_TYPE_MODEL_PACK);
        PlayerModelManager_setAuthor(exalinShieldHandle, "Zuke");
        PlayerModelManager_setDisplayName(exalinShieldHandle, "Exalin - Sword & Shield");

    PlayerModelManagerHandle exalinHumanNoMtx = PLAYERMODELMANAGER_REGISTER_MODEL("pmm_exalin_human_no_mtx", PMM_MODEL_TYPE_ADULT);
        PlayerModelManager_setAuthor(exalinHumanNoMtx, "Zuke");
        PlayerModelManager_setDisplayName(exalinHumanNoMtx, "Exalin - Sword & Shield");
        PlayerModelManager_setEyesTextures(exalinHumanNoMtx, gExalinEyeR);
        PlayerModelManager_setMouthTextures(exalinHumanNoMtx, gExalinMouth);
        PlayerModelManager_setSkeleton(exalinHumanNoMtx, &gExalinAdultSkelVanillaSheath);
        PlayerModelManager_setDisplayList(exalinHumanNoMtx, PMM_DL_LHAND_BOTTLE, gExalinAdultBottleHandSkel_bone015_gLinkZoraLeftHandLimb_mesh_layer_Opaque);
        PlayerModelManager_setDisplayList(exalinHumanNoMtx, PMM_DL_LFIST, gExalinAdultFistsSkel_bone015_gLinkZoraLeftHandLimb_mesh_layer_Opaque);
        PlayerModelManager_setDisplayList(exalinHumanNoMtx, PMM_DL_RFIST, gExalinAdultFistsSkel_bone018_gLinkZoraRightHandLimb_mesh_layer_Opaque);
        guPosition(&gExalinMaskMtx, MASK_ROTATE_X, MASK_ROTATE_Y, MASK_ROTATE_Z, MASK_SCALE, MASK_TRANSLATE_X, MASK_TRANSLATE_Y, MASK_TRANSLATE_Z);
        guPosition(&gExalinArrowMtx, ARROW_ROTATE_X, ARROW_ROTATE_Y, ARROW_ROTATE_Z, ARROW_SCALE, ARROW_TRANSLATE_X, ARROW_TRANSLATE_Y, ARROW_TRANSLATE_Z);
        PlayerModelManager_setMatrix(exalinHumanNoMtx, PMM_MTX_MASKS, &gExalinMaskMtx);
        PlayerModelManager_setMatrix(exalinHumanNoMtx, PMM_MTX_ARROW_DRAWN, &gExalinArrowMtx);
        PlayerModelManager_addHandleToPack(exalinShieldHandle, exalinHumanNoMtx);
        gExalinModelVanillaSheathHandle = exalinHumanNoMtx;

    PlayerModelManagerHandle exalinHuman = PLAYERMODELMANAGER_REGISTER_MODEL("pmm_exalin_human", PMM_MODEL_TYPE_ADULT);
        PlayerModelManager_setAuthor(exalinHuman, "Zuke");
        PlayerModelManager_setDisplayName(exalinHuman, "Exalin - Dual Wield");
        PlayerModelManager_setEyesTextures(exalinHuman, gExalinEyeR);
        PlayerModelManager_setMouthTextures(exalinHuman, gExalinMouth);
        PlayerModelManager_setSkeleton(exalinHuman, &gExalinAdultSkel);
        PlayerModelManager_setDisplayList(exalinHuman, PMM_DL_LHAND_BOTTLE, gExalinAdultBottleHandSkel_bone015_gLinkZoraLeftHandLimb_mesh_layer_Opaque);
        PlayerModelManager_setDisplayList(exalinHuman, PMM_DL_LFIST, gExalinAdultFistsSkel_bone015_gLinkZoraLeftHandLimb_mesh_layer_Opaque);
        PlayerModelManager_setDisplayList(exalinHuman, PMM_DL_RFIST, gExalinAdultFistsSkel_bone018_gLinkZoraRightHandLimb_mesh_layer_Opaque);
        PlayerModelManager_setDisplayList(exalinHuman, PMM_DL_ELEGY_OF_EMPTINESS_SHELL, gExalinElegyShellHumanDL);
        guPosition(&gExalinMaskMtx, MASK_ROTATE_X, MASK_ROTATE_Y, MASK_ROTATE_Z, MASK_SCALE, MASK_TRANSLATE_X, MASK_TRANSLATE_Y, MASK_TRANSLATE_Z);
        guPosition(&gExalinShieldMtx, SHIELD_BACK_ROTATE_X, SHIELD_BACK_ROTATE_Y, SHIELD_BACK_ROTATE_Z, SHIELD_BACK_SCALE, SHIELD_BACK_TRANSLATE_X, SHIELD_BACK_TRANSLATE_Y, SHIELD_BACK_TRANSLATE_Z);
        guPosition(&gExalinSwordMtx, SWORD_BACK_ROTATE_X, SWORD_BACK_ROTATE_Y, SWORD_BACK_ROTATE_Z, SWORD_BACK_SCALE, SWORD_BACK_TRANSLATE_X, SWORD_BACK_TRANSLATE_Y, SWORD_BACK_TRANSLATE_Z);
        guPosition(&gExalinArrowMtx, ARROW_ROTATE_X, ARROW_ROTATE_Y, ARROW_ROTATE_Z, ARROW_SCALE, ARROW_TRANSLATE_X, ARROW_TRANSLATE_Y, ARROW_TRANSLATE_Z);
        PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SWORD1_BACK, &gExalinSwordMtx);
        PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SWORD2_BACK, &gExalinSwordMtx);
        PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SWORD3_BACK, &gExalinSwordMtx);
        PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SHIELD1_BACK, &gExalinShieldMtx);
        PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SHIELD2_BACK, &gExalinShieldMtx);
        PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_SHIELD3_BACK, &gExalinShieldMtx);
        PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_MASKS, &gExalinMaskMtx);
        PlayerModelManager_setMatrix(exalinHuman, PMM_MTX_ARROW_DRAWN, &gExalinArrowMtx);
        PlayerModelManager_addHandleToPack(exalinDualHandle, exalinHuman);
        gExalinModelHandle = exalinHuman;

    PlayerModelManagerHandle exalinSwordKokiri = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_sword_kokiri_pmm", PMM_MODEL_TYPE_SWORD_KOKIRI);
        PlayerModelManager_setAuthor(exalinSwordKokiri, "Zuke");
        PlayerModelManager_setDisplayName(exalinSwordKokiri, "Exalin - Dual Wield");
        PlayerModelManager_setDisplayList(exalinSwordKokiri, PMM_DL_SWORD_KOKIRI_BLADE, gExTwinSword1Blade);
        PlayerModelManager_setDisplayList(exalinSwordKokiri, PMM_DL_SWORD_KOKIRI_HILT, gGiCull);
        PlayerModelManager_setDisplayList(exalinSwordKokiri, PMM_DL_SWORD_KOKIRI_SHEATH, gGiCull);
        PlayerModelManager_addHandleToPack(exalinDualHandle, exalinSwordKokiri);
        gExalinKokiriSwordHandle = exalinSwordKokiri;

    PlayerModelManagerHandle exalinSwordKokiriShield = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_sword_kokiri_shield_pmm", PMM_MODEL_TYPE_SWORD_KOKIRI);
        PlayerModelManager_setAuthor(exalinSwordKokiriShield, "Zuke");
        PlayerModelManager_setDisplayName(exalinSwordKokiriShield, "Exalin - Sword & Shield");
        PlayerModelManager_setDisplayList(exalinSwordKokiriShield, PMM_DL_SWORD_KOKIRI_BLADE, gExTwinSword1Blade);
        PlayerModelManager_setDisplayList(exalinSwordKokiriShield, PMM_DL_SWORD_KOKIRI_HILT, gExTwinSword1Handle);
        PlayerModelManager_setDisplayList(exalinSwordKokiriShield, PMM_DL_SWORD_KOKIRI_SHEATH, gExalinSheath1_001);
        PlayerModelManager_addHandleToPack(exalinShieldHandle, exalinSwordKokiriShield);
        gExalinKokiriSwordShieldHandle = exalinSwordKokiriShield;

    PlayerModelManagerHandle exalinSwordRazor = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_sword_razor_pmm", PMM_MODEL_TYPE_SWORD_RAZOR);
        PlayerModelManager_setAuthor(exalinSwordRazor, "Zuke");
        PlayerModelManager_setDisplayName(exalinSwordRazor, "Exalin - Dual Wield");
        PlayerModelManager_setDisplayList(exalinSwordRazor, PMM_DL_SWORD_RAZOR_BLADE, gExTwinSword2Blade);
        PlayerModelManager_setDisplayList(exalinSwordRazor, PMM_DL_SWORD_RAZOR_HILT, gGiCull);
        PlayerModelManager_setDisplayList(exalinSwordRazor, PMM_DL_SWORD_RAZOR_SHEATH, gGiCull);
        PlayerModelManager_addHandleToPack(exalinDualHandle, exalinSwordRazor);
        gExalinRazorSwordHandle = exalinSwordRazor;

    PlayerModelManagerHandle exalinSwordRazorShield = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_sword_razor_shield_pmm", PMM_MODEL_TYPE_SWORD_RAZOR);
        PlayerModelManager_setAuthor(exalinSwordRazorShield, "Zuke");
        PlayerModelManager_setDisplayName(exalinSwordRazorShield, "Exalin - Sword & Shield");
        PlayerModelManager_setDisplayList(exalinSwordRazorShield, PMM_DL_SWORD_RAZOR_BLADE, gExTwinSword2Blade);
        PlayerModelManager_setDisplayList(exalinSwordRazorShield, PMM_DL_SWORD_RAZOR_HILT, gExTwinSword2Handle);
        PlayerModelManager_setDisplayList(exalinSwordRazorShield, PMM_DL_SWORD_RAZOR_SHEATH, gExalinSheath2_001);
        PlayerModelManager_addHandleToPack(exalinShieldHandle, exalinSwordRazorShield);
        gExalinRazorSwordShieldHandle = exalinSwordRazorShield;

    PlayerModelManagerHandle exalinSwordGilded = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_sword_gilded_pmm", PMM_MODEL_TYPE_SWORD_GILDED);
        PlayerModelManager_setAuthor(exalinSwordGilded, "Zuke");
        PlayerModelManager_setDisplayName(exalinSwordGilded, "Exalin - Dual Wield");
        PlayerModelManager_setDisplayList(exalinSwordGilded, PMM_DL_SWORD_GILDED_BLADE, gExTwinSword3Blade);
        PlayerModelManager_setDisplayList(exalinSwordGilded, PMM_DL_SWORD_GILDED_HILT, gGiCull);
        PlayerModelManager_setDisplayList(exalinSwordGilded, PMM_DL_SWORD_GILDED_SHEATH, gGiCull);
        PlayerModelManager_addHandleToPack(exalinDualHandle, exalinSwordGilded);
        gExalinGildedSwordHandle = exalinSwordGilded;

    PlayerModelManagerHandle exalinSwordGildedShield = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_sword_gilded_shield_pmm", PMM_MODEL_TYPE_SWORD_GILDED);
        PlayerModelManager_setAuthor(exalinSwordGildedShield, "Zuke");
        PlayerModelManager_setDisplayName(exalinSwordGildedShield, "Exalin - Sword & Shield");
        PlayerModelManager_setDisplayList(exalinSwordGildedShield, PMM_DL_SWORD_GILDED_BLADE, gExTwinSword3Blade);
        PlayerModelManager_setDisplayList(exalinSwordGildedShield, PMM_DL_SWORD_GILDED_HILT, gExTwinSword3Handle);
        PlayerModelManager_setDisplayList(exalinSwordGildedShield, PMM_DL_SWORD_GILDED_SHEATH, gExalinSheath3_001);
        PlayerModelManager_addHandleToPack(exalinShieldHandle, exalinSwordGildedShield);
        gExalinGildedSwordShieldHandle = exalinSwordGildedShield;

    PlayerModelManagerHandle exalinSwordFairy = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_sword_fairy_pmm", PMM_MODEL_TYPE_SWORD_GREAT_FAIRY);
        PlayerModelManager_setAuthor(exalinSwordFairy, "Zuke");
        PlayerModelManager_setDisplayName(exalinSwordFairy, "Exalin");
        PlayerModelManager_setDisplayList(exalinSwordFairy, PMM_DL_SWORD_GREAT_FAIRY_BLADE, gExGreatSwordBlade);
        PlayerModelManager_setDisplayList(exalinSwordFairy, PMM_DL_SWORD_GREAT_FAIRY_HILT, gExGreatSwordHilt);
        PlayerModelManager_addHandleToPack(exalinDualHandle, exalinSwordFairy);
        PlayerModelManager_addHandleToPack(exalinShieldHandle, exalinSwordFairy);
        gExalinFairySwordHandle = exalinSwordFairy;

    PlayerModelManagerHandle exalinShieldHero = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_shield_hero_pmm", PMM_MODEL_TYPE_SHIELD_HERO);
        PlayerModelManager_setAuthor(exalinShieldHero, "Zuke");
        PlayerModelManager_setDisplayName(exalinShieldHero, "Exalin - Dual Wield");
        PlayerModelManager_setDisplayList(exalinShieldHero, PMM_DL_SHIELD_HERO, gGiCull);
        PlayerModelManager_addHandleToPack(exalinDualHandle, exalinShieldHero);
        gExalinHeroShieldHandle = exalinShieldHero;

    PlayerModelManagerHandle exalinShieldMirror = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_shield_mirror_pmm", PMM_MODEL_TYPE_SHIELD_MIRROR);
        PlayerModelManager_setAuthor(exalinShieldMirror, "Zuke");
        PlayerModelManager_setDisplayName(exalinShieldMirror, "Exalin - Dual Wield");
        PlayerModelManager_setDisplayList(exalinShieldMirror, PMM_DL_SHIELD_MIRROR, gGiCull);
        PlayerModelManager_addHandleToPack(exalinDualHandle, exalinShieldMirror);
        gExalinMirrorShieldHandle = exalinShieldMirror;

    PlayerModelManagerHandle exalinOcarina = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_ocarina_pmm", PMM_MODEL_TYPE_OCARINA_TIME);
        PlayerModelManager_setAuthor(exalinOcarina, "Zuke");
        PlayerModelManager_setDisplayName(exalinOcarina, "Exalin");
        PlayerModelManager_setDisplayList(exalinOcarina, PMM_DL_OCARINA_TIME, gOcarinaDL);
        PlayerModelManager_addHandleToPack(exalinDualHandle, exalinOcarina);
        PlayerModelManager_addHandleToPack(exalinShieldHandle, exalinOcarina);
        gExalinOcarinaHandle = exalinOcarina;

    PlayerModelManagerHandle exalinHood = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_hood_pmm", PMM_MODEL_TYPE_MASK_BUNNY);
        PlayerModelManager_setAuthor(exalinHood, "Zuke");
        PlayerModelManager_setDisplayName(exalinHood, "Exalin");
        PlayerModelManager_setDisplayList(exalinHood, PMM_DL_MASK_BUNNY, gGiCull);
        PlayerModelManager_addHandleToPack(exalinDualHandle, exalinHood);
        PlayerModelManager_addHandleToPack(exalinShieldHandle, exalinHood);
        gExalinHoodHandle = exalinHood;

    PlayerModelManagerHandle exalinFisher = PLAYERMODELMANAGER_REGISTER_MODEL("mm_exalin_fisher_pmm", PMM_MODEL_TYPE_MASK_POSTMAN);
        PlayerModelManager_setAuthor(exalinFisher, "Zuke");
        PlayerModelManager_setDisplayName(exalinFisher, "Exalin");
        PlayerModelManager_setDisplayList(exalinFisher, PMM_DL_MASK_POSTMAN, gExalinFisher);
        PlayerModelManager_addHandleToPack(exalinDualHandle, exalinFisher);
        PlayerModelManager_addHandleToPack(exalinShieldHandle, exalinFisher);
        gExalinMaskFisherHandle = exalinFisher;
}

// Draw additional eye bank for left eye
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

// Adjusted ocarina grip animaton replacement

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

bool exalinKokiriSwordOn;
bool exalinRazorSwordOn;
bool exalinGildedSwordOn;
bool exalinKokiriSwordShieldOn;
bool exalinRazorSwordShieldOn;
bool exalinGildedSwordShieldOn;
bool exalinFairySwordOn;
bool exalinHeroShieldOn;
bool exalinMirrorShieldOn;
bool exalinMaskFisherOn;
bool exalinOcarinaOn;
bool isExalin;
bool isExalinVanillaSheath;

RECOMP_HOOK("PlayerAnimation_Update") void on_PlayerAnimation_Update(struct PlayState* play, SkelAnime* skelAnime) {
    Player* player = GET_PLAYER(play);
    
    exalinKokiriSwordOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinKokiriSwordHandle);
    exalinRazorSwordOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinRazorSwordHandle);
    exalinGildedSwordOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinGildedSwordHandle);
    exalinKokiriSwordShieldOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinKokiriSwordShieldHandle);
    exalinRazorSwordShieldOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinRazorSwordShieldHandle);
    exalinGildedSwordShieldOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinGildedSwordShieldHandle);
    exalinFairySwordOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinFairySwordHandle);
    exalinHeroShieldOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinHeroShieldHandle);
    exalinMirrorShieldOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinMirrorShieldHandle);
    exalinMaskFisherOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinMaskFisherHandle);
    exalinOcarinaOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinOcarinaHandle);
    isExalin = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinModelHandle);
    isExalinVanillaSheath = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinModelVanillaSheathHandle);
    
    if (!(isExalin || isExalinVanillaSheath)) {
    } else {
        if (player->transformation == PLAYER_FORM_HUMAN) {
            *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_link_normal_okarina_end) = gExalinAdultSkel_okarina_endAnim;
            *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_link_normal_okarina_start) = gExalinAdultSkel_okarina_startAnim;
            *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_link_normal_okarina_swing) = gExalinAdultSkel_okarina_swingAnim;
            *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_clink_normal_okarina_walk) = gExalinAdultSkel_okarina_walkAnim;
            *(LinkAnimationHeader*)Lib_SegmentedToVirtual(&gPlayerAnim_clink_normal_okarina_walkB) = gExalinAdultSkel_okarina_walkbAnim;
        }
    }
}

// GI model replacement

extern Gfx gGiKokiriSwordGuardDL[];
extern Gfx gGiKokiriSwordBladeHiltDL[];
extern Gfx gGiRazorSwordDL[];
extern Gfx gGiGildedSwordDL[];
extern Gfx gGiGreatFairysSwordHiltEmblemDL[];
extern Gfx gGiGreatFairysSwordBladeDL[];
extern Gfx gGiHerosShieldDL[];
extern Gfx gGiHerosShieldEmblemDL[];
extern Gfx gGiMirrorShieldDL[];
extern Gfx gGiOcarinaOfTimeDL[];
extern Gfx gGiOcarinaOfTimeHolesDL[];
extern Gfx gGiPostmanHatBunnyLogoDL[];
extern Gfx gGiPostmanHatCapDL[];
extern Gfx gGiBunnyHoodDL[];
extern Gfx gGiBunnyHoodEyesDL[];

MODEL_REPLACER_CALLBACK_ON_REGISTER_REPLACERS void registerExalinGiModels() {

    //swords
    ModelReplacerHandle exalinGiSwordKokiri = ModelReplacer_registerReplacer(OBJECT_GI_SWORD_1, gGiKokiriSwordBladeHiltDL, gGiExalinSword1DL);
    ModelReplacerHandle exalinGiSwordKokiri2 = ModelReplacer_registerReplacer(OBJECT_GI_SWORD_1, gGiKokiriSwordGuardDL, gGiCull);
    ModelReplacerHandle exalinGiSwordRazor = ModelReplacer_registerReplacer(OBJECT_GI_SWORD_2, gGiRazorSwordDL, gGiExalinSword2DL);
    ModelReplacerHandle exalinGiSwordGilded = ModelReplacer_registerReplacer(OBJECT_GI_SWORD_3, gGiGildedSwordDL, gGiExalinSword3DL);
    ModelReplacerHandle exalinGiSwordFairy = ModelReplacer_registerReplacer(OBJECT_GI_SWORD_4, gGiGreatFairysSwordBladeDL, gGiExalinSword4DL);
    ModelReplacerHandle exalinGiSwordFairy2 = ModelReplacer_registerReplacer(OBJECT_GI_SWORD_4, gGiGreatFairysSwordHiltEmblemDL, gGiCull);
    ModelReplacer_setReplacerModel(exalinGiSwordKokiri, gGiExalinSword1DL);
    ModelReplacer_setReplacerModel(exalinGiSwordKokiri2, gGiCull);
    ModelReplacer_setReplacerModel(exalinGiSwordRazor, gGiExalinSword2DL);
    ModelReplacer_setReplacerModel(exalinGiSwordGilded, gGiExalinSword3DL);
    ModelReplacer_setReplacerModel(exalinGiSwordFairy, gGiExalinSword4DL);
    ModelReplacer_setReplacerModel(exalinGiSwordFairy2, gGiCull);

    //shields
    ModelReplacerHandle exalinGiShieldHero = ModelReplacer_registerReplacer(OBJECT_GI_SHIELD_2, gGiHerosShieldDL, gGiExalinSword3DL);
    ModelReplacerHandle exalinGiShieldHero2 = ModelReplacer_registerReplacer(OBJECT_GI_SHIELD_2, gGiHerosShieldEmblemDL, gGiCull);
    ModelReplacerHandle exalinGiShieldMirror = ModelReplacer_registerReplacer(OBJECT_GI_SHIELD_3, gGiMirrorShieldDL, gGiExalinSword3DL);
    ModelReplacer_setReplacerModel(exalinGiShieldHero, gGiExalinSword3DL);
    ModelReplacer_setReplacerModel(exalinGiShieldHero2, gGiCull);
    ModelReplacer_setReplacerModel(exalinGiShieldMirror, gGiExalinSword3DL);

    //ocarina
    ModelReplacerHandle exalinGiOcarina = ModelReplacer_registerReplacer(OBJECT_GI_OCARINA, gGiOcarinaOfTimeDL, gGiOcarinaDL);
    ModelReplacerHandle exalinGiOcarina2 = ModelReplacer_registerReplacer(OBJECT_GI_OCARINA, gGiOcarinaOfTimeHolesDL, gGiCull);
    ModelReplacer_setReplacerModel(exalinGiOcarina, gGiOcarinaDL);
    ModelReplacer_setReplacerModel(exalinGiOcarina2, gGiCull);

    //masks
    ModelReplacerHandle exalinGiMaskPost = ModelReplacer_registerReplacer(OBJECT_GI_MASK12, gGiPostmanHatCapDL, gGiExalinFisher);
    ModelReplacerHandle exalinGiMaskPost2 = ModelReplacer_registerReplacer(OBJECT_GI_MASK12, gGiPostmanHatBunnyLogoDL, gGiCull);
    ModelReplacerHandle exalinGiMaskHood = ModelReplacer_registerReplacer(OBJECT_GI_RABIT_MASK, gGiBunnyHoodDL, gGiExalinHood);
    ModelReplacerHandle exalinGiMaskHood2 = ModelReplacer_registerReplacer(OBJECT_GI_RABIT_MASK, gGiBunnyHoodEyesDL, gGiCull);
    ModelReplacer_setReplacerModel(exalinGiMaskPost, gGiExalinFisher);
    ModelReplacer_setReplacerModel(exalinGiMaskPost2, gGiCull);
    ModelReplacer_setReplacerModel(exalinGiMaskHood, gGiExalinHood);
    ModelReplacer_setReplacerModel(exalinGiMaskHood2, gGiCull);
}

// Dependency check for BunnyHoodTweaks

bool bunnyHoodTweaksEnabled = false;

RECOMP_IMPORT("yazmt_mm_bunnyhoodtweaks", bool BunnyHoodTweaks_isPlayerRunSpeedModified(PlayState *play, Player *player));

RECOMP_CALLBACK("*", recomp_on_init) void on_init() {
    DependencyStatus bunnyHoodTweaksStatus = recomp_is_dependency_met("yazmt_mm_bunnyhoodtweaks");

    switch (bunnyHoodTweaksStatus) {
        case DEPENDENCY_STATUS_FOUND:
            bunnyHoodTweaksEnabled = true;
            recomp_printf("[INFO] Exalin - Dragon Quest X: Found optional dependency BunnyHoodTweaks!\n");
            break;
        case DEPENDENCY_STATUS_INVALID_DEPENDENCY:
            recomp_printf("[INFO] Exalin - Dragon Quest X: Optional dependency BunnyHoodTweaks ID mismatch!\n");
            break;
        case DEPENDENCY_STATUS_NOT_FOUND:
            recomp_printf("[INFO] Exalin - Dragon Quest X: Optional dependency BunnyHoodTweaks not found\n");
            break;
        case DEPENDENCY_STATUS_WRONG_VERSION:
            recomp_printf("[INFO] Exalin - Dragon Quest X: Optional dependency BunnyHoodTweaks version mismatch!\n");
            break;
    }
}

// Draw upper section of Exalin's hood

u8 gPushedHeadMatrix;
bool exalinHoodOn;

RECOMP_HOOK("Player_DrawBunnyHood") void on_Player_DrawBunnyHood(PlayState* play) {
    Player* player = GET_PLAYER(play);
    exalinHoodOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinHoodHandle);

    if (exalinHoodOn){
        OPEN_DISPS(play->state.gfxCtx);
        Matrix_Push();
        gPushedHeadMatrix++;
        // Reverse matrix translation of hood if BunnyHoodTweaks is disabled
        if (!bunnyHoodTweaksEnabled) {
            Matrix_Translate(-MASK_TRANSLATE_X, -MASK_TRANSLATE_Y, -MASK_TRANSLATE_Z, MTXMODE_APPLY);
        }
        MATRIX_FINALIZE_AND_LOAD(POLY_OPA_DISP++, play->state.gfxCtx);
        gSPDisplayList(POLY_OPA_DISP++, gExalinAdultHoodSkel_bone010_gLinkZoraHeadLimb_mesh_layer_Opaque);
        CLOSE_DISPS(play->state.gfxCtx);
    }
}

RECOMP_HOOK_RETURN("Player_DrawBunnyHood") void return_Player_DrawBunnyHood(void) {
    while (gPushedHeadMatrix) {
        Matrix_Pop();
        gPushedHeadMatrix--;
    }
    gPushedHeadMatrix = 0;
}

u8 gPushedSwordHandleMatrix;
u8 gPushedRHShieldMatrix;
u8 gPushedBowstringMatrix;
u8 gPushedTorsoMatrix;
u8 gPushedLeftSheathMatrix;
u8 gPushedRightSheathMatrix;
Gfx* exalinDrawHoodBot = gGiCull;
Gfx* exalinDrawSwordHandle = gGiCull;
Gfx* exalinDrawShieldHandle = gGiCull;
Gfx* exalinDrawShieldBlade = gGiCull;
Gfx* exalinDrawLeftSheath = gGiCull;
Gfx* exalinDrawRightSheath = gGiCull;
Gfx* exalinDrawLeftSheathHandle = gGiCull;
Gfx* exalinDrawRightSheathHandle = gGiCull;
bool exalinDrawLeftSheathToggle = false;
bool exalinDrawRightSheathToggle = false;
bool exalinDrawLeftSheathHandleToggle = false;
bool exalinDrawRightSheathHandleToggle = false;
bool hoodSpeedIsActive = false;

// Draw lower section of Exalin's hood
/*
    If BunnyHoodTweaks is detected, check against modified run speed using exported function.
    Otherwise, check against bunny hood's mask index.
    BHT changes the bunny hood, so player->currentMask is 0 while wearing it. 
*/

RECOMP_HOOK("Player_PostLimbDrawGameplay") void on_Player_PostLimbDrawGameplay(PlayState* play, s32 limbIndex, Gfx** dList1, Gfx** dList2, Vec3s* rot, Actor* actor) {
    Player* player = (Player*)actor;
    exalinHoodOn = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinHoodHandle);
    // Logic for drawing bottom of the hood
    if (bunnyHoodTweaksEnabled) {
        hoodSpeedIsActive = BunnyHoodTweaks_isPlayerRunSpeedModified(play, player);
        if (hoodSpeedIsActive && !player->currentMask) {
            exalinDrawHoodBot = gExalinAdultHoodSkel_bone020_gLinkZoraTorsoLimb_mesh_layer_Opaque;
        } else {
            exalinDrawHoodBot = gGiCull;
        }
    } else {
        if (player->currentMask == PLAYER_MASK_BUNNY) {
            exalinDrawHoodBot = gExalinAdultHoodSkel_bone020_gLinkZoraTorsoLimb_mesh_layer_Opaque;
        } else {
            exalinDrawHoodBot = gGiCull;
        }
    }
    if (player->stateFlags1 & PLAYER_STATE1_100000) {
        Vec3f temp;
        SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &player->actor.focus.pos, &temp);
        if (temp.z < 5.0f) {
            exalinDrawHoodBot = gGiCull;
            }
    }

    if (exalinHoodOn) {
        if (limbIndex == PLAYER_LIMB_TORSO) {
            s32 pad;
            OPEN_DISPS(play->state.gfxCtx);
            Matrix_Push();
            gPushedTorsoMatrix++;
            Matrix_Translate(0.f, 0.F, 0.f, MTXMODE_APPLY);
            MATRIX_FINALIZE_AND_LOAD(POLY_XLU_DISP++, play->state.gfxCtx);
            gSPDisplayList(POLY_OPA_DISP++, exalinDrawHoodBot);
            CLOSE_DISPS(play->state.gfxCtx);
        } else { 
            gPushedTorsoMatrix = 0;
        }
    } else {
        gPushedTorsoMatrix = 0;
    }
    
    isExalin = PlayerModelManager_Actor_isModelApplied(&player->actor, gExalinModelHandle);
    EquipValueSword swordEquipValue;
    EquipValueShield shieldEquipValue;

    // Logic for drawing handles in the left hand
    if (limbIndex == PLAYER_LIMB_LEFT_HAND) {
        if ((player->leftHandType == PLAYER_MODELTYPE_LH_ONE_HAND_SWORD) &&
            (player->transformation == PLAYER_FORM_HUMAN) &&
            ((swordEquipValue = GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD),
              swordEquipValue != EQUIP_VALUE_SWORD_NONE))) {
                if ((exalinKokiriSwordOn && swordEquipValue == EQUIP_VALUE_SWORD_KOKIRI) || 
                    (exalinRazorSwordOn && swordEquipValue == EQUIP_VALUE_SWORD_RAZOR) || 
                    (exalinGildedSwordOn && swordEquipValue == EQUIP_VALUE_SWORD_GILDED)) {
                    switch (swordEquipValue) {
                        case EQUIP_VALUE_SWORD_KOKIRI:
                            exalinDrawSwordHandle = gExTwinSword1Handle;
                            break;
                        case EQUIP_VALUE_SWORD_RAZOR:
                            exalinDrawSwordHandle = gExTwinSword2Handle;
                            break;
                        case EQUIP_VALUE_SWORD_GILDED:
                            exalinDrawSwordHandle = gExTwinSword3Handle;
                            break;
                        default:
                            break;
                    }
                    OPEN_DISPS(play->state.gfxCtx);
                    Matrix_Push();
                    gPushedSwordHandleMatrix++;
                    MATRIX_FINALIZE_AND_LOAD(POLY_XLU_DISP++, play->state.gfxCtx);
                    gSPDisplayList(POLY_OPA_DISP++, exalinDrawSwordHandle);
                    CLOSE_DISPS(play->state.gfxCtx);
                }
        } else {
            gPushedSwordHandleMatrix = 0;
        }
    // Adjust bowstring position
    } else if (limbIndex == PLAYER_LIMB_RIGHT_HAND) {
        Actor* heldActor = player->heldActor;
        s32 pad;
        
        if (*dList1 != NULL) {
            if (!isExalin) {
            } else {
                if (player->rightHandType == PLAYER_MODELTYPE_RH_BOW) {
                    OPEN_DISPS(play->state.gfxCtx);
                    Matrix_Push();
                    gPushedBowstringMatrix++;
                    Matrix_Translate(0.f, BOWSTRING_OFFSET, 0.f, MTXMODE_APPLY);
                    MATRIX_FINALIZE_AND_LOAD(POLY_XLU_DISP++, play->state.gfxCtx);
                    CLOSE_DISPS(play->state.gfxCtx);
                }
            }
            // Logic for drawing sword in the offhand
            if (((player->rightHandType == PLAYER_MODELTYPE_RH_SHIELD) || 
                (player->leftHandType == PLAYER_MODELTYPE_LH_ONE_HAND_SWORD)) &&
                (player->transformation == PLAYER_FORM_HUMAN) &&
                ((swordEquipValue = GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD),
                swordEquipValue != EQUIP_VALUE_SWORD_NONE)) &&
                ((shieldEquipValue = GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SHIELD),
                shieldEquipValue != EQUIP_VALUE_SHIELD_NONE))) {
                    if ((exalinHeroShieldOn && shieldEquipValue == EQUIP_VALUE_SHIELD_HERO) || 
                        (exalinMirrorShieldOn && shieldEquipValue == EQUIP_VALUE_SHIELD_MIRROR)) {
                        switch (swordEquipValue) {
                            case EQUIP_VALUE_SWORD_KOKIRI:
                                exalinDrawShieldHandle = gExTwinSword1Handle;
                                exalinDrawShieldBlade = gExTwinSword1Blade;
                                break;
                            case EQUIP_VALUE_SWORD_RAZOR:
                                exalinDrawShieldHandle = gExTwinSword2Handle;
                                exalinDrawShieldBlade = gExTwinSword2Blade;
                                break;
                            case EQUIP_VALUE_SWORD_GILDED:
                                exalinDrawShieldHandle = gExTwinSword3Handle;
                                exalinDrawShieldBlade = gExTwinSword3Blade;
                                break;
                            default:
                                break;
                        }
                        OPEN_DISPS(play->state.gfxCtx);
                        Matrix_Push();
                        gPushedRHShieldMatrix++;
                        MATRIX_FINALIZE_AND_LOAD(POLY_XLU_DISP++, play->state.gfxCtx);
                        gSPDisplayList(POLY_OPA_DISP++, exalinDrawShieldHandle);
                        gSPDisplayList(POLY_OPA_DISP++, exalinDrawShieldBlade);
                        CLOSE_DISPS(play->state.gfxCtx);
                    }
            }
        } else {
            gPushedBowstringMatrix = 0;
            gPushedRHShieldMatrix = 0;
        }
    // Logic for drawing sheaths, and stowed handles
    } else if (limbIndex == PLAYER_LIMB_SHEATH) {
            if (player->currentShield != PLAYER_SHIELD_NONE) {
                exalinDrawLeftSheathToggle = true;
            } else {
                exalinDrawLeftSheathToggle = false;
            }


            if ((player->sheathType == PLAYER_MODELTYPE_SHEATH_14) ||
                (player->sheathType == PLAYER_MODELTYPE_SHEATH_15)) {
                exalinDrawRightSheathHandleToggle = true;
                if (player->currentShield != PLAYER_SHIELD_NONE) {
                    exalinDrawLeftSheathHandleToggle = true;
                } else {
                    exalinDrawLeftSheathHandleToggle = false;
                }
            } else if (player->sheathType == PLAYER_MODELTYPE_SHEATH_12) {
                exalinDrawLeftSheathHandleToggle = true;
                exalinDrawRightSheathHandleToggle = false;
            } else {
                exalinDrawLeftSheathHandleToggle = false;
                exalinDrawRightSheathHandleToggle = false;
            }

            if ((swordEquipValue = GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD),
                swordEquipValue != EQUIP_VALUE_SWORD_NONE)) {
                exalinDrawRightSheathToggle = true;
                if ((*dList1 != NULL) && (player->transformation == PLAYER_FORM_HUMAN)) {
                    if ((exalinKokiriSwordOn && swordEquipValue == EQUIP_VALUE_SWORD_KOKIRI) || 
                    (exalinRazorSwordOn && swordEquipValue == EQUIP_VALUE_SWORD_RAZOR) || 
                    (exalinGildedSwordOn && swordEquipValue == EQUIP_VALUE_SWORD_GILDED) ||
                    (exalinHeroShieldOn && shieldEquipValue == EQUIP_VALUE_SHIELD_HERO) ||
                    (exalinMirrorShieldOn && shieldEquipValue == EQUIP_VALUE_SHIELD_MIRROR)) {
                        switch (swordEquipValue) {
                            case EQUIP_VALUE_SWORD_KOKIRI:
                                exalinDrawLeftSheath = gExalinLeftSheath_001;
                                exalinDrawLeftSheathHandle = gExalinLeftSheathHandle_001;
                                exalinDrawRightSheath = gExalinRightSheath_001;
                                exalinDrawRightSheathHandle = gExalinRightSheathHandle_001;
                                break;
                            case EQUIP_VALUE_SWORD_RAZOR:
                                exalinDrawLeftSheath = gExalinLeftSheath_002;
                                exalinDrawLeftSheathHandle = gExalinLeftSheathHandle_002;
                                exalinDrawRightSheath = gExalinRightSheath_002;
                                exalinDrawRightSheathHandle = gExalinRightSheathHandle_002;
                                break;
                            case EQUIP_VALUE_SWORD_GILDED:
                                exalinDrawLeftSheath = gExalinLeftSheath_003;
                                exalinDrawLeftSheathHandle = gExalinLeftSheathHandle_003;
                                exalinDrawRightSheath = gExalinRightSheath_003;
                                exalinDrawRightSheathHandle = gExalinRightSheathHandle_003;
                                break;
                            default:
                                exalinDrawLeftSheathToggle = false;
                                exalinDrawLeftSheathHandleToggle = false;
                                exalinDrawRightSheathToggle = false;
                                exalinDrawRightSheathHandleToggle = false;
                        }
                    }
                }
            } else {
                exalinDrawRightSheathToggle = false;
                exalinDrawRightSheathHandleToggle = false;
                exalinDrawLeftSheathToggle = false;
                exalinDrawLeftSheathHandleToggle = false;
            }

            // Cull in FPS
            if (player->stateFlags1 & PLAYER_STATE1_100000) {
                Vec3f temp;
                SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &player->actor.focus.pos, &temp);
                if (temp.z < 5.0f) {
                    exalinDrawLeftSheathToggle = false;
                    exalinDrawLeftSheathHandleToggle = false;
                    exalinDrawRightSheathToggle = false;
                    exalinDrawRightSheathHandleToggle = false;
                    }
            }

            if (!exalinDrawLeftSheathToggle || !isExalin) {
                exalinDrawLeftSheath = gGiCull;
            }
            if (!exalinDrawLeftSheathHandleToggle || !isExalin) {
                exalinDrawLeftSheathHandle = gGiCull;
            }
            if (!exalinDrawRightSheathToggle || !isExalin) {
                exalinDrawRightSheath = gGiCull;
            }
            if (!exalinDrawRightSheathHandleToggle || !isExalin) {
                exalinDrawRightSheathHandle = gGiCull;
            }

            OPEN_DISPS(play->state.gfxCtx);
            gSPDisplayList(POLY_OPA_DISP++, exalinDrawLeftSheath);
            gSPDisplayList(POLY_OPA_DISP++, exalinDrawLeftSheathHandle);
            gSPDisplayList(POLY_OPA_DISP++, exalinDrawRightSheath);
            gSPDisplayList(POLY_OPA_DISP++, exalinDrawRightSheathHandle);
            CLOSE_DISPS(play->state.gfxCtx);

        if (player->actor.scale.y >= 0.0f) {
            if ((player->rightHandType != PLAYER_MODELTYPE_RH_SHIELD) &&
                (player->rightHandType != PLAYER_MODELTYPE_RH_FF)) {
                static Vec3f sSheathLimbModelShieldOnBackPos = { 630.0f, 100.0f, -30.0f };
                static Vec3s sSheathLimbModelShieldOnBackZyxRot = { 0, 0, 0x7FFF };

                Matrix_TranslateRotateZYX(&sSheathLimbModelShieldOnBackPos, &sSheathLimbModelShieldOnBackZyxRot);
                Matrix_Get(&player->shieldMf);
            }
        }
    } else {
        gPushedBowstringMatrix = 0;
        gPushedRHShieldMatrix = 0;
        gPushedSwordHandleMatrix = 0;
    }
}

RECOMP_HOOK_RETURN("Player_PostLimbDrawGameplay") void return_Player_PostLimbDrawGameplay(void) {
    while (gPushedTorsoMatrix) {
        Matrix_Pop();
        gPushedTorsoMatrix--;
    }
    while (gPushedSwordHandleMatrix) {
        Matrix_Pop();
        gPushedSwordHandleMatrix--;
    }
    while (gPushedRHShieldMatrix) {
        Matrix_Pop();
        gPushedRHShieldMatrix--;
    }
    while (gPushedBowstringMatrix) {
        Matrix_Pop();
        gPushedBowstringMatrix--;
    }

    gPushedSwordHandleMatrix = 0;
    gPushedRHShieldMatrix = 0;
    gPushedTorsoMatrix = 0;
    gPushedBowstringMatrix = 0;
}

// Replace item icons

u8 gCurIconIsKokiriSword = 0;
u8 gCurIconIsRazorSword = 0;
u8 gCurIconIsGildedSword = 0;
u8 gCurIconIsFairySword = 0;
u8 gCurIconIsHeroShield = 0;
u8 gCurIconIsMirrorShield = 0;
u8 gCurIconIsMaskHood = 0;
u8 gCurIconIsMaskFisher = 0;
u8 gCurIconIsOcarina = 0;

PlayState* gPlayState;
u8 gId;
void* gDst;
u8 gAlreadyTranslated = 0;
uintptr_t gTranslatedAddress;

RECOMP_HOOK("CmpDma_LoadFileImpl") void on_CmpDma_LoadFileImpl(uintptr_t segmentRom, s32 id, void* dst, size_t size) {

    if (!gAlreadyTranslated ) {
        gTranslatedAddress = DmaMgr_TranslateVromToRom(SEGMENT_ROM_START(icon_item_static_yar));
        gAlreadyTranslated = 1;
    }
    if (segmentRom == gTranslatedAddress) {
        switch (id) {
            case ITEM_SWORD_KOKIRI:
                if (exalinKokiriSwordOn || exalinKokiriSwordShieldOn) {
                    gCurIconIsKokiriSword = 1;
                }
                break;
            case ITEM_SWORD_RAZOR:
                if (exalinRazorSwordOn || exalinRazorSwordShieldOn) {
                    gCurIconIsRazorSword = 1;
                }
                break;
            case ITEM_SWORD_GILDED:
                if (exalinGildedSwordOn || exalinGildedSwordShieldOn) {
                    gCurIconIsGildedSword = 1;
                }
                break;
            case ITEM_SWORD_GREAT_FAIRY:
                if (exalinFairySwordOn) {
                    gCurIconIsFairySword = 1;
                }
                break;
            case ITEM_SHIELD_HERO:
                if (exalinHeroShieldOn) {
                    gCurIconIsHeroShield = 1;
                }
                break;
            case ITEM_SHIELD_MIRROR:
                if (exalinMirrorShieldOn) {
                    gCurIconIsMirrorShield = 1;
                }
                break;
            case ITEM_MASK_BUNNY:
                if (exalinHoodOn) {
                    gCurIconIsMaskHood = 1;
                }
                break;
            case ITEM_MASK_POSTMAN:
                if (exalinMaskFisherOn) {
                    gCurIconIsMaskFisher = 1;
                }
                break;
            case ITEM_OCARINA_OF_TIME:
                if (exalinOcarinaOn) {
                    gCurIconIsOcarina = 1;
                }
                break;
            default:
                break;
        }
    } else {
        gCurIconIsKokiriSword = 0;
        gCurIconIsRazorSword = 0;
        gCurIconIsGildedSword = 0;
        gCurIconIsFairySword = 0;
        gCurIconIsHeroShield = 0;
        gCurIconIsMirrorShield = 0;
        gCurIconIsMaskHood = 0;
        gCurIconIsMaskFisher = 0;
        gCurIconIsOcarina = 0;
    } 
    gId = id;
    gDst = dst;
}

RECOMP_HOOK_RETURN("CmpDma_LoadFileImpl") void return_CmpDma_LoadFileImpl(void) {
    if (gCurIconIsKokiriSword && (exalinKokiriSwordOn || exalinKokiriSwordShieldOn)) {
        Lib_MemCpy(gDst, gExalinIconKokiriSword_exalin_icon_kokiri_sword_rgba32, ICON_ITEM_TEX_SIZE);
    }
    if (gCurIconIsRazorSword && (exalinRazorSwordOn || exalinRazorSwordShieldOn)) {
        Lib_MemCpy(gDst, gExalinIconRazorSword_exalin_icon_razor_sword_rgba32, ICON_ITEM_TEX_SIZE);
    }
    if (gCurIconIsGildedSword && (exalinGildedSwordOn || exalinGildedSwordShieldOn)) {
        Lib_MemCpy(gDst, gExalinIconGildedSword_exalin_icon_gilded_sword_rgba32, ICON_ITEM_TEX_SIZE);
    }
    if (gCurIconIsFairySword && exalinFairySwordOn) {
        Lib_MemCpy(gDst, gExalinIconFairySword_exalin_icon_fairy_great_sword_rgba32, ICON_ITEM_TEX_SIZE);
    }
    if (gCurIconIsHeroShield && exalinHeroShieldOn) {
        Lib_MemCpy(gDst, gExalinIconEmpty_exalin_icon_empty_rgba32, ICON_ITEM_TEX_SIZE);
    }
    if (gCurIconIsMirrorShield && exalinMirrorShieldOn) {
        Lib_MemCpy(gDst, gExalinIconEmpty_exalin_icon_empty_rgba32, ICON_ITEM_TEX_SIZE);
    }
    if (gCurIconIsMaskHood && exalinHoodOn) {
        Lib_MemCpy(gDst, gExalinIconMaskHood_exalin_icon_mask_hood_rgba32, ICON_ITEM_TEX_SIZE);
    }
    if (gCurIconIsMaskFisher && exalinMaskFisherOn) {
        Lib_MemCpy(gDst, gExalinIconMaskFisher_exalin_icon_mask_fisher_rgba32, ICON_ITEM_TEX_SIZE);
    }
    if (gCurIconIsOcarina && exalinOcarinaOn) {
        Lib_MemCpy(gDst, gExalinIconOcarina_exalin_icon_ocarina_rgba32, ICON_ITEM_TEX_SIZE);
    }

    gCurIconIsKokiriSword = 0;
    gCurIconIsRazorSword = 0;
    gCurIconIsGildedSword = 0;
    gCurIconIsFairySword = 0;
    gCurIconIsHeroShield = 0;
    gCurIconIsMirrorShield = 0;
    gCurIconIsMaskHood = 0;
    gCurIconIsMaskFisher = 0;
    gCurIconIsOcarina = 0;

}

// Draw the offhand sword icon

RECOMP_HOOK("KaleidoScope_DrawQuestStatus") void on_KaleidoScope_DrawQuestStatus(PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    PauseContext* pauseCtx = &play->pauseCtx;
    
    if ((isExalin) && (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SHIELD) != EQUIP_VALUE_SHIELD_NONE) && (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) != EQUIP_VALUE_SWORD_NONE)) {
        OPEN_DISPS(play->state.gfxCtx);

        KaleidoScope_SetCursorVtxPos(pauseCtx, pauseCtx->cursorSlot[PAUSE_QUEST] * 4, pauseCtx->questVtx);

        // Draw shield
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        // shield icon is index 16
        gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[16], 4, 0);
        KaleidoScope_DrawTexQuadRGBA32(play->state.gfxCtx, gItemIcons[(ITEM_SWORD_KOKIRI - 1) + GET_CUR_EQUIP_VALUE(0)], 32, 32, 0);
        CLOSE_DISPS(play->state.gfxCtx);
    }

}