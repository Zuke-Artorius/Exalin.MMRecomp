#include "gGiCull.h"

Vtx gGiCull_gGiCull_mesh_layer_Transparent_vtx_cull[8] = {
	{{ {-100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx gGiCull_gGiCull_mesh_layer_Transparent_vtx_0[3] = {
	{{ {-100, 0, 100}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {100, 0, 100}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {0, 0, -100}, 0, {-16, -16}, {0, 127, 0, 255} }},
};

Gfx gGiCull_gGiCull_mesh_layer_Transparent_tri_0[] = {
	gsSPVertex(gGiCull_gGiCull_mesh_layer_Transparent_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx mat_gGiCull_f3d_cull_001_layerTransparent[] = {
	gsSPLoadGeometryMode(G_SHADE | G_FOG | G_SHADING_SMOOTH | G_LIGHTING | G_ZBUFFER),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_TP_PERSP | G_CK_NONE | G_TT_NONE | G_TD_CLAMP | G_AD_NOISE | G_CD_MAGICSQ | G_TF_BILERP | G_TC_FILT | G_CYC_2CYCLE | G_PM_NPRIMITIVE | G_TL_TILE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_XLU_SURF2 | G_RM_FOG_SHADE_A | G_ZS_PIXEL | G_AC_NONE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 128),
	gsSPEndDisplayList(),
};

Gfx mat_revert_gGiCull_f3d_cull_001_layerTransparent[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF2 | G_RM_AA_ZB_OPA_SURF),
	gsSPEndDisplayList(),
};

Gfx gGiCull[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(gGiCull_gGiCull_mesh_layer_Transparent_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_gGiCull_f3d_cull_001_layerTransparent),
	gsSPDisplayList(gGiCull_gGiCull_mesh_layer_Transparent_tri_0),
	gsSPDisplayList(mat_revert_gGiCull_f3d_cull_001_layerTransparent),
	gsSPEndDisplayList(),
};

