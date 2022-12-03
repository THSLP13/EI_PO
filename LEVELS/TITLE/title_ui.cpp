//
// Created by enVine on 2022/11/17.
//
#include "../levelTree.h"
#include "../../lvgl/lvgl.h"
#include "res.h"

lv_fs_file_t res_file;
lv_res_t  res_Fopen;
lv_obj_t * title_Base;
lv_obj_t * title_main_Base;
lv_obj_t * title_bg;

void title_load(){
    title_Base = lv_obj_create(NULL);
    lv_scr_load(title_Base);

    /*Create a spinner*/
    lv_obj_t * spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
    lv_obj_set_size(spinner, 100, 100);
    lv_obj_center(spinner);
}

lv_obj_t *menuList;
lv_obj_t *about;

static void MMLST_CB(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    const char *ab;
    ab = lv_list_get_btn_text(menuList, obj);
    if(code == LV_EVENT_CLICKED) {
        if(strcmp(ab,"新的旅程")==0){
            exit(0);
        }
        if(strcmp(ab,"回到过去")==0){
            lanix_baseUI_Crate();
            lanix_nextStep(LANIX_SCENE_OUTSKIRT_UCAVE_SPLT4);
        }
        if(strcmp(ab,"关于")==0){
            about = lv_msgbox_create(title_main_Base,"关于","如你所见，这是一个非常简陋的图形版文字游戏\n该作品为练手作品，屎山代码了解一下？", {0},true);
            lv_obj_set_size(about,500,250);
            lv_obj_align(about,LV_ALIGN_BOTTOM_MID,0,0);
        }
    }
}


void title_main(){
    title_main_Base = lv_obj_create(NULL);

    title_bg = lv_img_create(title_main_Base);
    lv_img_set_src(title_bg,&title_img);
    lv_obj_set_size(title_bg, 1366, 768);
    lv_obj_align(title_bg,LV_ALIGN_TOP_LEFT,0,0);

    //lv_scr_load(title_main_Base);
    lv_scr_load_anim(title_main_Base,LV_SCR_LOAD_ANIM_FADE_IN,1000,500,false);

    menuList = lv_list_create(title_main_Base);
    lv_obj_set_size(menuList, 300, 220);
    lv_obj_align(menuList,LV_ALIGN_BOTTOM_MID,0,0);

    lv_obj_t * btn;
    btn = lv_list_add_btn(menuList, 0, "新的旅程");
    lv_obj_add_event_cb(btn, MMLST_CB, LV_EVENT_CLICKED, NULL);
    btn = lv_list_add_btn(menuList, 0, "回到过去");
    lv_obj_add_event_cb(btn, MMLST_CB, LV_EVENT_CLICKED, NULL);
    btn = lv_list_add_btn(menuList, 0, "关于");
    lv_obj_add_event_cb(btn, MMLST_CB, LV_EVENT_CLICKED, NULL);

    lv_obj_set_style_opa(menuList,LV_OPA_50,0);
}
