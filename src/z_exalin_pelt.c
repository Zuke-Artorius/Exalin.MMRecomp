
/*
 * File: z_exalin_pelt.c
 * Overlay: ovl_Exalin_Pelt
 * Description: Gravestone
 */

#include "z_exalin_pelt.h"
#include "verlet_physics.h"
#include "customMath.h"
#include "math.h"
#include "proxymm_custom_actor.h"
#include "recomp_api.h"
#include "z64extern.h"

#define FLAGS 0
#define GRAVITY     -5.f
#define LIMB_MASS   1.f
#define PINNED      1
#define NOT_PINNED  0

void ExalinPelt_Init(Actor* thisx, PlayState* play);
void ExalinPelt_Destroy(Actor* thisx, PlayState* play);
void ExalinPelt_Update(Actor* thisx, PlayState* play);
void ExalinPelt_Draw(Actor* thisx, PlayState* play);

ActorProfile Exalin_Pelt_Profile = {
    /**/ ACTOR_ID_MAX,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(ExalinPelt),
    /**/ ExalinPelt_Init,
    /**/ ExalinPelt_Destroy,
    /**/ ExalinPelt_Update,
    /**/ ExalinPelt_Draw,
};

s16 CUSTOM_ACTOR_EXALIN_PELT = ACTOR_ID_MAX;

typedef enum PeltLimbs {
    EXALINPELT_ROOT_POS,     // ExalinPelt's Root bone (position)
    EXALINPELT_ROOT_ROT,     // ExalinPelt's Root bone (rotation)
    EXALINPELT_LIMB1
} PeltLimbs;

RECOMP_CALLBACK("*", recomp_on_init) 
void ExalinPelt_OnRecompInit() {
    CUSTOM_ACTOR_EXALIN_PELT = CustomActor_Register(&Exalin_Pelt_Profile);
}

/*
=================
Player Init
=================
*/
ExalinPelt* gPlayerExalinPelt = NULL;
PlayState* gPlayStateExalinPelt = NULL;

RECOMP_HOOK("Player_Init") void on_player_init(Actor* thisx, PlayState* play) {
    if (gPlayerExalinPelt == NULL) {
        Actor_SpawnAsChildAndCutscene(&play->actorCtx, play, CUSTOM_ACTOR_EXALIN_PELT, -367.0f, 0.0f, -245.0f, 0, 0x8000, 0, 0, 0, 0, 0);
    }
}

void ExalinPelt_SetDefaultBodyPartsPos(ExalinPelt* this, Player* player, StandardLimb* gLimbs[], PhysLimb* gPhysLimbs[], PhysBone* gPhysBones[], int chainStart, int chainEnd, int bodyPartRoot, int bodyPartID) {
    // Set ExalinPelt velocity
    Vec3f playerVelocity = player->actor.velocity;

    // Root limb's BodyPartsPos and gPhysLimb positions and velocity
    // Velocity only gets assigned to root limb
    // BodyPartsPos keeps track of global XYZ position of each limb
    Math_Vec3f_Copy(&this->bodyPartsPos[bodyPartRoot], &player->bodyPartsPos[bodyPartID]);
    Verlet_InitLimb(gPhysLimbs[bodyPartRoot], this->actor.world.pos, playerVelocity, LIMB_MASS, PINNED);

    // Root limb's jointTable for position
    Vec3s rootPos_Vec3s = {0, 0, 0};
    Math_Vec3f_ToVec3s(&rootPos_Vec3s, &this->actor.world.pos);
    Math_Vec3s_Copy(&this->skelAnime.jointTable[bodyPartRoot], &rootPos_Vec3s);
    Math_Vec3s_Copy(&gPhysLimbs[bodyPartRoot]->default_jointPos, &rootPos_Vec3s);

    // Root limb's jointTable for rotation
    Vec3s newRootJointRot = { 0, 0, 0};
    Math_Vec3s_Copy(&this->skelAnime.jointTable[bodyPartRoot+1], &newRootJointRot);

    // BodyPartsPos and gPhysLimbs' pos and vel for Rest of the limbs
    for (int i = (int)chainStart; i < (int)chainEnd; i++) {
        // Find global position of current limb based on offset from parent limb's position
        Vec3f transformVec3f = {0.f, 0.f, 0.f};

        // Apply exalinpelt root limb's rotation here
        Vec3s rotatedOffset = {180, 0, 0};
        CustomMath_Vec3s_Rotate(&gPhysLimbs[i]->default_jointPos, &player->actor.shape.rot, &rotatedOffset);
        CustomMath_Vec3s_Scale_ToVec3f(&rotatedOffset, this->actor.scale.x, &transformVec3f);
        Math_Vec3f_Sum(&this->bodyPartsPos[i-1], &transformVec3f, &this->bodyPartsPos[i]);

        // If limb shouldn't have any verlet physics, pin it
        if (i == (int)chainStart) {
            Verlet_InitLimb(gPhysLimbs[i], this->bodyPartsPos[i], playerVelocity, (LIMB_MASS), PINNED);
        }
        else {
            Vec3f no_velocity = {(f32)0, (f32)0, (f32)0};
            Verlet_InitLimb(gPhysLimbs[i], this->bodyPartsPos[i], no_velocity, (LIMB_MASS), NOT_PINNED);
        }
    }

    // Set matching gPhysLimbs to appropriate gPhysBones
    for (int i = 0; i < (int)chainEnd; i++) {
        Verlet_InitBone(gPhysBones[i], gPhysLimbs[i], gPhysLimbs[i+1]);
    }
}

void ExalinPelt_Init(Actor* thisx, PlayState* play) {
    Player* player = GET_PLAYER(play);
    ExalinPelt* this = (ExalinPelt*)thisx;
    this->actor.room = -1;

    gPlayerExalinPelt = this;
    gPlayStateExalinPelt = play;

    // Capture default jointPos
    // I can't think of any way aside from hardcoding, because the standardlimbs' jointPos values
    // keep getting updated based on its last jointPos values before map reloads.
    // Values are directly copied from the generated Fast64 model file (in my case, gExalinPeltSkel.c)
    Vec3s limb1_jointPos = { 0, 0, 236 };    
    Vec3s limb2_jointPos = { 0, 0, 0 };
    Vec3s limb3_jointPos = { 0, 50, 0 };
    Vec3s limb4_jointPos = { -350, -303, 22 };
    Vec3s limb5_jointPos = { 0, 35, 0 };
    Vec3s limb6_jointPos = { 1299, 0, 0 };
    Vec3s limb7_jointPos = { 350, -303, 22 };
    Vec3s limb8_jointPos = { 0, 35, 0 };
    Vec3s limb9_jointPos = { 1299, 0, 0 };
    
    // default_jointPos values for every limb should NEVER change once assigned here
    Math_Vec3s_Copy(&exalinpeltPhysLimbs[1]->default_jointPos, &limb1_jointPos);
    Math_Vec3s_Copy(&exalinpeltPhysLimbs[2]->default_jointPos, &limb2_jointPos);
    Math_Vec3s_Copy(&exalinpeltPhysLimbs[3]->default_jointPos, &limb3_jointPos);
    Math_Vec3s_Copy(&exalinpeltPhysLimbs[4]->default_jointPos, &limb4_jointPos);
    Math_Vec3s_Copy(&exalinpeltPhysLimbs[5]->default_jointPos, &limb5_jointPos);
    Math_Vec3s_Copy(&exalinpeltPhysLimbs[6]->default_jointPos, &limb6_jointPos);
    Math_Vec3s_Copy(&exalinpeltPhysLimbs[7]->default_jointPos, &limb7_jointPos);
    Math_Vec3s_Copy(&exalinpeltPhysLimbs[8]->default_jointPos, &limb8_jointPos);
    Math_Vec3s_Copy(&exalinpeltPhysLimbs[9]->default_jointPos, &limb9_jointPos);

    Actor_SetScale(&this->actor, 0.01f);
    SkelAnime_InitFlex(
        play,
        &this->skelAnime,
        &gExalinPeltSkel,
        NULL,
        this->jointTable,
        this->morphTable,
        GEXALINPELTSKEL_NUM_LIMBS
    );

    // Set position and rotation of ExalinPelt
    Math_Vec3f_Copy(&this->actor.world.pos, &player->actor.world.pos);
    Math_Vec3s_Copy(&this->actor.shape.rot, &player->actor.shape.rot);
    Math_Vec3s_Copy(&this->actor.world.rot, &player->actor.world.rot);

    // Verlet integration starts here
    Verlet_InitPhysPlayer(&gExalinPhysPlayer, player);

    ExalinPelt_SetDefaultBodyPartsPos(this, player, gExalinPeltLimbs, exalinpeltPhysLimbs, exalinpeltPhysBones, EXALINPELT_BODYPART_LIMB2, EXALINPELT_BODYPART_LIMB5, EXALINPELT_BODYPART_LIMB1, PLAYER_BODYPART_WAIST);
    ExalinPelt_SetDefaultBodyPartsPos(this, player, gExalinPeltLimbs, exalinpeltPhysLimbs, exalinpeltPhysBones, EXALINPELT_BODYPART_LIMB7, EXALINPELT_BODYPART_LIMB7, EXALINPELT_BODYPART_LIMB6, PLAYER_BODYPART_RIGHT_THIGH);
}

// @ProxyMM Example spawning this actor in south clock town.
/*
RECOMP_HOOK("Actor_SpawnTransitionActors")
void ExalinPelt_OnRoomLoad(PlayState* play, ActorContext* actorCtx) {
    if (play->sceneId == SCENE_CLOCKTOWER) {
        Actor* peltActorPtr = Actor_SpawnAsChildAndCutscene(&play->actorCtx, play, CUSTOM_ACTOR_EXALIN_PELT, -367.0f, 0.0f, -245.0f, 0, 0x8000, 0, 0, 0, 0, 0);
        recomp_printf("pelt actor: %x\n", peltActorPtr);
    }
}
*/

void ExalinPelt_Destroy(Actor* thisx, PlayState* play) {
    ExalinPelt* this = (ExalinPelt*)thisx;

    gPlayerExalinPelt = NULL;
}


/*
=================
ExalinPelt Update
=================
*/

// OLD - Vec3f waist_globalPos = { (f32)0, (f32)0, (f32)0 };  // Global position of player's waist limb
// OLD - Vec3s waist_rotate = {0, 0, 0};                      // Rotation value for player's waist (with parent limbs' rotations included)

PosRot peltRoot = {0};
PosRot peltWaist = {0};
PosRot peltThighR = {0};
PosRot peltThighL = {0};

// Get player waist limb's position and rotation values from matrix
RECOMP_HOOK("Player_PostLimbDrawGameplay") void ExalinPelt_on_Player_PostLimbDrawGameplay(PlayState* play, s32 limbIndex, Gfx** dList1, Gfx** dList2, Vec3s* rot, Actor* actor) {
    if (limbIndex == PLAYER_LIMB_ROOT) {
        // Get matrix of root limb
        OPEN_DISPS(play->state.gfxCtx);
        Matrix_Push(); 
        MtxF* mtx = Matrix_GetCurrent();

        // Get global position
        peltRoot.pos.x = mtx->xw;
        peltRoot.pos.y = mtx->yw;
        peltRoot.pos.z = mtx->zw;

        // Get rotation values
        Matrix_MtxFToYXZRot(mtx, &peltRoot.rot, 1);

        // Close matrix
        Matrix_Pop();
        CLOSE_DISPS(play->state.gfxCtx);
    }
    
    if (limbIndex == PLAYER_LIMB_WAIST) {
        // Get matrix of waist limb
        OPEN_DISPS(play->state.gfxCtx);
        Matrix_Push(); 
        MtxF* mtx = Matrix_GetCurrent();

        // Get global position
        peltWaist.pos.x = mtx->xw;
        peltWaist.pos.y = mtx->yw;
        peltWaist.pos.z = mtx->zw;

        // Get rotation values
        Matrix_MtxFToYXZRot(mtx, &peltWaist.rot, 1);

        // Close matrix
        Matrix_Pop();
        CLOSE_DISPS(play->state.gfxCtx);
    }

    if (limbIndex == PLAYER_LIMB_RIGHT_THIGH) {
        // Get matrix of right thigh limb
        OPEN_DISPS(play->state.gfxCtx);
        Matrix_Push(); 
        MtxF* mtx = Matrix_GetCurrent();

        // Get global position
        peltThighR.pos.x = mtx->xw;
        peltThighR.pos.y = mtx->yw;
        peltThighR.pos.z = mtx->zw;

        // Get rotation values
        Matrix_MtxFToYXZRot(mtx, &peltThighR.rot, 1);

        // Close matrix
        Matrix_Pop();
        CLOSE_DISPS(play->state.gfxCtx);
    }
}


void ExalinPelt_UpdateBodyPartsPos(ExalinPelt* this, Player* player, Vec3f apply_force, StandardLimb* gLimbs[], PhysLimb* gPhysLimbs[], PhysBone* gPhysBones[], int chainStart, int chainEnd, int bodyPartRoot, PosRot bodyPartPosRot) {
    // Set Root limb's bodyPartsPos
    Math_Vec3f_Copy(&this->bodyPartsPos[bodyPartRoot], &bodyPartPosRot.pos);
    Math_Vec3f_Copy(&gPhysLimbs[bodyPartRoot]->curr_pos, &this->actor.world.pos); // Rotation needs to be applied

    // jointTable Root Position
    Vec3s newRootJointPos = { 0, 0, 0};
    Math_Vec3s_Copy(&this->skelAnime.jointTable[bodyPartRoot], &newRootJointPos);
    
    // jointTable Root rotation
    Vec3s newRootJointRot = { 0, 0, 0};
    newRootJointRot.x = bodyPartPosRot.rot.z;
    newRootJointRot.y = -16384 + bodyPartPosRot.rot.y - this->actor.shape.rot.y;
    newRootJointRot.z = bodyPartPosRot.rot.x;
    Math_Vec3s_Copy(&this->skelAnime.jointTable[bodyPartRoot+1], &newRootJointRot);

    /*
    Vec3s newRootJointRot = { 0, 0, 0};
    newRootJointRot.x = 32768 + bodyPartPosRot.rot.z;
    newRootJointRot.y = -16384 + bodyPartPosRot.rot.y - this->actor.shape.rot.y;
    newRootJointRot.z = 32768 + bodyPartPosRot.rot.x;
    Math_Vec3s_Copy(&this->skelAnime.jointTable[EXALINPELT_BODYPART_LIMB7], &newRootJointRot);
    */

    // BodyPartsPos Rest of the limbs
    for (int i = chainStart; i < chainEnd; i++) {
        if (gPhysLimbs[i]->pinned == 1) {
            // Set previous values for current gPhysLimb
            Math_Vec3f_Copy(&gPhysLimbs[i]->prev_pos, &gPhysLimbs[i]->curr_pos);    // Previous Position
            Math_Vec3f_Copy(&gPhysLimbs[i]->prev_vel, &gPhysLimbs[i]->curr_vel);    // Previous Velocity

            // Find current global position of current limb based on offset from parent limb's position
            Vec3f transformVec3f = {0.f, 0.f, 0.f};
            Vec3s rotatedOffset = { 0, 0, 0};
            CustomMath_Vec3s_Rotate(&gPhysLimbs[i]->default_jointPos, &this->actor.shape.rot, &rotatedOffset);
            CustomMath_Vec3s_Scale_ToVec3f(&rotatedOffset, this->actor.scale.x, &transformVec3f);

            // Set Current values for current gPhysLimb
            Math_Vec3f_Sum(&this->bodyPartsPos[i-1], &transformVec3f, &this->bodyPartsPos[i]);
            Math_Vec3f_Copy(&gPhysLimbs[i]->curr_pos, &this->bodyPartsPos[i]);      // Current position
            Math_Vec3f_Copy(&gPhysLimbs[i]->curr_vel, &player->actor.velocity);     // Current Velocity
        }
        else {
            // Apply Verlet Integration
            Vec3f player_vel = { (f32)0, (f32)0, (f32)0 };
            Math_Vec3f_Copy(&player_vel, &player->actor.velocity);

            u8 linkOnGround = (player->actor.bgCheckFlags & BGCHECKFLAG_GROUND);
            if (linkOnGround) {
                player_vel.y = 0.f;
            }

            Verlet_LimbUpdatePos(gPhysLimbs[i], &apply_force, &player_vel);
        }
    }

    // Bone update
    for (int i = 0; i < 1; i++) {
        for (int i = 0; i < chainEnd; i++) {
            Verlet_BoneConstraint(gPhysBones[i]);
        }
    }

}


void ExalinPelt_RotateJoints(ExalinPelt* this, PhysBone* gPhysBones[], int chainStart, int chainEnd) {
    // Keep track of all limbs' rotation for subsequent limbs' rotations
    Vec3s offset_rotation = { (s16)0, (s16)0, (s16)0 };

    // Go through every bone
    for (int i = chainStart; i < chainEnd; i++) {
        // Skip to next bone if both limbs in current bone are pinned
        if (gPhysBones[i]->limb_a->pinned == 1 && gPhysBones[i]->limb_b->pinned == 1) {
            continue;
        }
        else {
            if (i == chainStart){
                // Get global direction vector from current bone's limb_a to limb_b
                Vec3f bone_direction = {(f32)0.f, (f32)0.f, (f32)0.f};
                Math_Vec3f_Diff(&gPhysBones[i]->limb_b->curr_pos, &gPhysBones[i]->limb_a->curr_pos, &bone_direction);

                // Transform direction into local space by removing actor rot & model offset
                Vec3s actorRotWithOffset = {0, 0, 0};
                Math_Vec3s_Copy(&actorRotWithOffset, &this->actor.shape.rot);
                CustomMath_Vec3f_InverseRotate(&bone_direction, &actorRotWithOffset, &bone_direction);

                // Now compute pitch/roll from the local-space direction
                Vec3f origin = {0, 0, 0};
                s16 local_pitch = CustomMath_Vec3f_Pitch(&bone_direction, &origin);
                s16 local_roll = CustomMath_Vec3f_Roll(&origin, &bone_direction);
                Vec3s curr_rotate = { local_pitch, (s16)0, local_roll };

                // Apply pitch and roll to current limb's jointTable
                this->skelAnime.jointTable[i + 1] = curr_rotate;

                // Keep note of offset for next limb
                CustomMath_Vec3s_Sum(&offset_rotation, &curr_rotate, &offset_rotation);
            }
            else {
                // Get global direction vector from current bone's limb_a to limb_b
                Vec3f bone_direction = {(f32)0.f, (f32)0.f, (f32)0.f};
                Math_Vec3f_Diff(&gPhysBones[i]->limb_b->curr_pos, &gPhysBones[i]->limb_a->curr_pos, &bone_direction);

                // Transform direction into local space by removing actor rot & model offset
                Vec3s actorRotWithOffset = {0, 0, 0};
                Math_Vec3s_Copy(&actorRotWithOffset, &this->actor.shape.rot);
                CustomMath_Vec3f_InverseRotate(&bone_direction, &actorRotWithOffset, &bone_direction);

                // Now compute pitch/roll from the local-space direction
                Vec3f origin = {0, 0, 0};
                s16 local_pitch = CustomMath_Vec3f_Pitch(&bone_direction, &origin);
                s16 local_roll = CustomMath_Vec3f_Roll(&origin, &bone_direction);
                Vec3s curr_rotate = { local_pitch, (s16)0, local_roll };

                // Subtract parent's accumulated rotation to get relative rotation
                Vec3s apply_rot = { (s16)0, (s16)0, (s16)0 };
                CustomMath_Vec3s_Diff(&curr_rotate, &offset_rotation, &apply_rot);

                // Apply pitch and roll to current limb's jointTable
                this->skelAnime.jointTable[i + 1] = apply_rot;

                // Keep note of offset for next limb
                CustomMath_Vec3s_Sum(&offset_rotation, &apply_rot, &offset_rotation);
            }
        }
    }
}


void ExalinPelt_Update(Actor* thisx, PlayState* play) {
    Player* player = GET_PLAYER(play);
    ExalinPelt* this = (ExalinPelt*)thisx;

    // Remove ExalinPelt when player transforms from human to non-human
    if (player->transformation != PLAYER_FORM_HUMAN && gPlayerExalinPelt != NULL && player->actor.draw == NULL && (player->stateFlags2 & PLAYER_STATE2_20000000)) {
        Actor_Kill(&this->actor);
        gPlayerExalinPelt = NULL;
        return;
    }
}


/*
=================
Player Draw
=================
*/
RECOMP_HOOK_RETURN ("Player_Draw") void return_Skirt_Player_Draw(void) {
    if (!recomp_get_config_u32("change_hairstyle") || gPlayerExalinPelt == NULL || gPlayStateExalinPelt == NULL) {
        return;
    }
    
    Player* player = GET_PLAYER(gPlayStateExalinPelt);
    if (recomp_get_config_u32("change_hairstyle") && gPlayerExalinPelt != NULL && player->transformation == PLAYER_FORM_HUMAN && player->actor.draw != NULL && !(player->stateFlags2 & PLAYER_STATE2_20000000)) {
        ExalinPelt* this = gPlayerExalinPelt;

        // Calculate Force
        Vec3f net_force = { (f32)0, (f32)0, (f32)0 };    // Gravity + movement
        Verlet_UpdatePhysPlayerVelocity(&gExalinPhysPlayer, player);
        Verlet_CalcNetForce(&gExalinPhysPlayer, (f32)GRAVITY, &net_force);

        // Set ExalinPelt's previous position
        Math_Vec3f_Copy(&this->actor.prevPos, &player->actor.prevPos);

        // Set ExalinPelt's position and rotations
        Math_Vec3f_Copy(&this->actor.world.pos, &peltRoot.pos);
        Math_Vec3s_Copy(&this->actor.shape.rot, &player->actor.shape.rot);
        this->actor.shape.rot.y += -32768;
        Math_Vec3s_Copy(&this->actor.world.rot, &player->actor.shape.rot);

        // Update ExalinPelt Limbs' positions based on Verlet Integration
        ExalinPelt_UpdateBodyPartsPos(this, player, net_force, gExalinPeltLimbs, exalinpeltPhysLimbs, exalinpeltPhysBones, EXALINPELT_BODYPART_LIMB2, EXALINPELT_BODYPART_LIMB5, EXALINPELT_BODYPART_LIMB1, peltWaist);
        ExalinPelt_UpdateBodyPartsPos(this, player, net_force, gExalinPeltLimbs, exalinpeltPhysLimbs, exalinpeltPhysBones, EXALINPELT_BODYPART_LIMB7, EXALINPELT_BODYPART_LIMB7, EXALINPELT_BODYPART_LIMB6, peltThighR);

        // Calculate rotations based on exalinpelt limbs' calculated positions
        ExalinPelt_RotateJoints(this, exalinpeltPhysBones, EXALINPELT_BODYPART_LIMB2, EXALINPELT_BODYPART_LIMB5);
        ExalinPelt_RotateJoints(this, exalinpeltPhysBones, EXALINPELT_BODYPART_LIMB6, EXALINPELT_BODYPART_LIMB7);
    }
}


void ExalinPelt_Draw(Actor* thisx, PlayState* play) {
    Player* player = GET_PLAYER(play);
    if (recomp_get_config_u32("change_hairstyle") && player->transformation == PLAYER_FORM_HUMAN && player->actor.draw != NULL && !(player->stateFlags2 & PLAYER_STATE2_20000000)) {
        ExalinPelt* this = (ExalinPelt*)thisx;

        OPEN_DISPS(play->state.gfxCtx);
        Gfx_SetupDL25_Opa(play->state.gfxCtx);
        func_80122868(play, player);    // Draw blinking effect of exalinpelt when player gets hit or jinxed
        SkelAnime_DrawFlexOpa(
            play,
            this->skelAnime.skeleton,
            this->skelAnime.jointTable,
            this->skelAnime.dListCount,
            NULL,
            NULL,
            &this->actor
        );

        // Reset fog to scene's default values after drawing so that other actors don't get affected
        if (player->invincibilityTimer > 0 || gSaveContext.jinxTimer != 0) {
            POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}