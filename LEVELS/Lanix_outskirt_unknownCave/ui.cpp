//
// Created by enVine on 2022/11/19.
//
#include "store.h"
lv_obj_t *lanix_uiBase;

void lanix_nextStep(int scene){
    prep_ckpt_0_2(lanix_uiBase);
    return;
    switch(scene){
        case LANIX_SCENE_OUTSKIRT_UCAVE_SPLT4:
            if(player.checkpoint_0_0 == false){
                prep_ckpt_0_0(lanix_uiBase);
            }else
            if(player.checkpoint_0_1 == false){
                prep_ckpt_0_1(lanix_uiBase);
            }else
            if(player.checkpoint_0_2 == false){
                prep_ckpt_0_2(lanix_uiBase);
            }
            break;
    }
}

void lanix_baseUI_Crate(){
    lanix_uiBase = lv_obj_create(NULL);
    lv_scr_load_anim(lanix_uiBase,LV_SCR_LOAD_ANIM_FADE_OUT,1000,500,false);
}