#ifndef Z_EXALIN_PELT_H
#define Z_EXALIN_PELT_H

#include "ultra64.h"
#include "z64actor.h"
#include "verlet_physics.h"
#include "gExalinPeltSkel.h"

/***********************************************************************

	ExalinPelt Physics

***********************************************************************/
PhysPlayer gExalinPhysPlayer;

extern StandardLimb gExalinPeltSkelLimb_000;
extern StandardLimb gExalinPeltSkelLimb_001;
extern StandardLimb gExalinPeltSkelLimb_002;
extern StandardLimb gExalinPeltSkelLimb_003;
extern StandardLimb gExalinPeltSkelLimb_004;
extern StandardLimb gExalinPeltSkelLimb_005;
extern StandardLimb gExalinPeltSkelLimb_006;
extern StandardLimb gExalinPeltSkelLimb_007;
extern StandardLimb gExalinPeltSkelLimb_008;

StandardLimb* gExalinPeltLimbs[9] = {
    &gExalinPeltSkelLimb_000,
    &gExalinPeltSkelLimb_001,
    &gExalinPeltSkelLimb_002,
    &gExalinPeltSkelLimb_003,
    &gExalinPeltSkelLimb_004,
    &gExalinPeltSkelLimb_005,
    &gExalinPeltSkelLimb_006,
    &gExalinPeltSkelLimb_007,
    &gExalinPeltSkelLimb_008
};

typedef enum ExalinPeltBodyPart {
    /* 0x00 */ EXALINPELT_BODYPART_ROOT,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB1,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB2,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB3,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB4,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB5,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB6,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB7,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB8,
    /* 0x06 */ EXALINPELT_BODYPART_MAX
} ExalinPeltBodyPart;

PhysLimb exalinpeltRootLimb;
PhysLimb exalinpeltLimb1;
PhysLimb exalinpeltLimb2;
PhysLimb exalinpeltLimb3;
PhysLimb exalinpeltLimb4;
PhysLimb exalinpeltLimb5;
PhysLimb exalinpeltLimb6;
PhysLimb exalinpeltLimb7;
PhysLimb exalinpeltLimb8;

PhysLimb* exalinpeltPhysLimbs[9] = {
    &exalinpeltRootLimb,
    &exalinpeltLimb1,
    &exalinpeltLimb2,
    &exalinpeltLimb3,
    &exalinpeltLimb4,
    &exalinpeltLimb5,
    &exalinpeltLimb6,
    &exalinpeltLimb7,
    &exalinpeltLimb8
};

PhysBone exalinpeltRootLimbLimb1;
PhysBone exalinpeltLimb1Limb2;
PhysBone exalinpeltLimb2Limb3;
PhysBone exalinpeltLimb3Limb4;
PhysBone exalinpeltLimb4Limb5;
PhysBone exalinpeltLimb6Limb7;
PhysBone exalinpeltLimb7Limb8;

typedef enum ExalinPeltBoneIndex {
    /* 0x00 */ EXALINPELT_BONE_ROOT_LIMB1,
    /* 0x00 */ EXALINPELT_BONE_LIMB1_LIMB2,
    /* 0x00 */ EXALINPELT_BONE_LIMB2_LIMB3,
    /* 0x00 */ EXALINPELT_BONE_LIMB3_LIMB4,
    /* 0x00 */ EXALINPELT_BONE_LIMB4_LIMB5,
    /* 0x00 */ EXALINPELT_BONE_LIMB6_LIMB7,
    /* 0x00 */ EXALINPELT_BONE_LIMB7_LIMB8,
    /* 0x05 */ EXALINPELT_BONE_MAX            
} ExalinPeltBoneIndex;

PhysBone* exalinpeltPhysBones[7] = {
    &exalinpeltRootLimbLimb1,
    &exalinpeltLimb1Limb2,
    &exalinpeltLimb2Limb3,
    &exalinpeltLimb3Limb4,
    &exalinpeltLimb4Limb5,
    &exalinpeltLimb6Limb7,
    &exalinpeltLimb7Limb8
};


struct ExalinPelt;

typedef void (*ExalinPeltActionFunc)(struct ExalinPelt*, struct PlayState*);

typedef struct ExalinPelt {
    Actor actor;
    SkelAnime skelAnime;
    Vec3s jointTable[GEXALINPELTSKEL_NUM_LIMBS];
    Vec3s morphTable[GEXALINPELTSKEL_NUM_LIMBS];
    Vec3f bodyPartsPos[EXALINPELT_BODYPART_MAX];
    ColliderJntSph collider;
} ExalinPelt;

// ExalinPelt manipulation based on Verlet Integration
void ExalinPelt_RotateJoints(ExalinPelt* this, PhysBone* gPhysBones[], int chainStart, int chainEnd);
void ExalinPelt_SetDefaultBodyPartsPos(ExalinPelt* this, Player* player, StandardLimb* gLimbs[], PhysLimb* gPhysLimbs[], PhysBone* gPhysBones[], int chainStart, int chainEnd, int bodyPartRoot, int bodyPartID);
void ExalinPelt_UpdateBodyPartsPos(ExalinPelt* this, Player* player, Vec3f apply_force, StandardLimb* gLimbs[], PhysLimb* gPhysLimbs[], PhysBone* gPhysBones[], int chainStart, int chainEnd, int bodyPartRoot, PosRot bodyPartPosRot);
#endif