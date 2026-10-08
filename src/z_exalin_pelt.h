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
extern StandardLimb gExalinPeltSkelLimb_009;
extern StandardLimb gExalinPeltSkelLimb_010;
extern StandardLimb gExalinPeltSkelLimb_011;
extern StandardLimb gExalinPeltSkelLimb_012;
extern StandardLimb gExalinPeltSkelLimb_013;
extern StandardLimb gExalinPeltSkelLimb_014;
extern StandardLimb gExalinPeltSkelLimb_015;

StandardLimb* gExalinPeltLimbs[16] = {
    &gExalinPeltSkelLimb_000,
    &gExalinPeltSkelLimb_001,
    &gExalinPeltSkelLimb_002,
    &gExalinPeltSkelLimb_003,
    &gExalinPeltSkelLimb_004,
    &gExalinPeltSkelLimb_005,
    &gExalinPeltSkelLimb_006,
    &gExalinPeltSkelLimb_007,
    &gExalinPeltSkelLimb_008,
    &gExalinPeltSkelLimb_009,
    &gExalinPeltSkelLimb_010,
    &gExalinPeltSkelLimb_011,
    &gExalinPeltSkelLimb_012,
    &gExalinPeltSkelLimb_013,
    &gExalinPeltSkelLimb_014,
    &gExalinPeltSkelLimb_015
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
    /* 0x01 */ EXALINPELT_BODYPART_LIMB9,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB10,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB11,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB12,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB13,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB14,
    /* 0x01 */ EXALINPELT_BODYPART_LIMB15,
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
PhysLimb exalinpeltLimb9;
PhysLimb exalinpeltLimb10;
PhysLimb exalinpeltLimb11;
PhysLimb exalinpeltLimb12;
PhysLimb exalinpeltLimb13;
PhysLimb exalinpeltLimb14;
PhysLimb exalinpeltLimb15;

PhysLimb* exalinpeltPhysLimbs[16] = {
    &exalinpeltRootLimb,
    &exalinpeltLimb1,
    &exalinpeltLimb2,
    &exalinpeltLimb3,
    &exalinpeltLimb4,
    &exalinpeltLimb5,
    &exalinpeltLimb6,
    &exalinpeltLimb7,
    &exalinpeltLimb8,
    &exalinpeltLimb9,
    &exalinpeltLimb10,
    &exalinpeltLimb11,
    &exalinpeltLimb12,
    &exalinpeltLimb13,
    &exalinpeltLimb14,
    &exalinpeltLimb15
};

PhysBone exalinpeltRootLimbLimb1;
PhysBone exalinpeltLimb1Limb2;
PhysBone exalinpeltLimb2Limb3;
PhysBone exalinpeltLimb3Limb4;
PhysBone exalinpeltLimb4Limb5;
PhysBone exalinpeltLimb5Limb6;
PhysBone exalinpeltLimb6Limb7;
PhysBone exalinpeltLimb7Limb8;
PhysBone exalinpeltLimb8Limb9;
PhysBone exalinpeltLimb9Limb10;
PhysBone exalinpeltLimb10Limb11;
PhysBone exalinpeltLimb11Limb12;
PhysBone exalinpeltLimb12Limb13;
PhysBone exalinpeltLimb13Limb14;
PhysBone exalinpeltLimb14Limb15;

typedef enum ExalinPeltBoneIndex {
    /* 0x00 */ EXALINPELT_BONE_ROOT_LIMB1,
    /* 0x00 */ EXALINPELT_BONE_LIMB1_LIMB2,
    /* 0x00 */ EXALINPELT_BONE_LIMB2_LIMB3,
    /* 0x00 */ EXALINPELT_BONE_LIMB3_LIMB4,
    /* 0x00 */ EXALINPELT_BONE_LIMB4_LIMB5,
    /* 0x00 */ EXALINPELT_BONE_LIMB5_LIMB6,
    /* 0x00 */ EXALINPELT_BONE_LIMB6_LIMB7,
    /* 0x00 */ EXALINPELT_BONE_LIMB7_LIMB8,
    /* 0x00 */ EXALINPELT_BONE_LIMB8_LIMB9,
    /* 0x00 */ EXALINPELT_BONE_LIMB9_LIMB10,
    /* 0x00 */ EXALINPELT_BONE_LIMB10_LIMB11,
    /* 0x00 */ EXALINPELT_BONE_LIMB11_LIMB12,
    /* 0x00 */ EXALINPELT_BONE_LIMB12_LIMB13,
    /* 0x00 */ EXALINPELT_BONE_LIMB13_LIMB14,
    /* 0x00 */ EXALINPELT_BONE_LIMB14_LIMB15,
    /* 0x05 */ EXALINPELT_BONE_MAX            
} ExalinPeltBoneIndex;

PhysBone* exalinpeltPhysBones[15] = {
    &exalinpeltRootLimbLimb1,
    &exalinpeltLimb1Limb2,
    &exalinpeltLimb2Limb3,
    &exalinpeltLimb3Limb4,
    &exalinpeltLimb4Limb5,
    &exalinpeltLimb5Limb6,
    &exalinpeltLimb6Limb7,
    &exalinpeltLimb7Limb8,
    &exalinpeltLimb8Limb9,
    &exalinpeltLimb9Limb10,
    &exalinpeltLimb10Limb11,
    &exalinpeltLimb11Limb12,
    &exalinpeltLimb12Limb13,
    &exalinpeltLimb13Limb14,
    &exalinpeltLimb14Limb15
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
    u8 needsReset;
    u8 needsResetShape;
} ExalinPelt;

// ExalinPelt manipulation based on Verlet Integration
void ExalinPelt_RotateJoints(ExalinPelt* this, PhysBone* gPhysBones[], int chainStart, int chainEnd);
void ExalinPelt_SetDefaultBodyPartsPos(ExalinPelt* this, Player* player, StandardLimb* gLimbs[], PhysLimb* gPhysLimbs[], PhysBone* gPhysBones[], int chainStart, int chainEnd, int bodyPartRoot, int bodyPartID);
void ExalinPelt_UpdateBodyPartsPos(ExalinPelt* this, Player* player, Vec3f apply_force, StandardLimb* gLimbs[], PhysLimb* gPhysLimbs[], PhysBone* gPhysBones[], int chainStart, int chainEnd, int bodyPartRoot, PosRot bodyPartPosRot, Vec3s bodyPartRotOffset);
#endif