//
// Created by enVine on 2022/11/18.
//
#include "stdio.h"

#include "../battleTree.h"
#include "../../LEVELS/levelTree.h"
#include "../../PlayerData.h"
#include "../../EnemyData.h"

extern PlayerData player;
EnemyData enemy;

lv_obj_t *bscr;

lv_obj_t *playerName;
lv_obj_t * HParc;
         lv_obj_t *HParc_label;
lv_obj_t * MParc;
         lv_obj_t *MParc_label;


lv_obj_t *enemyName;
lv_obj_t * eHParc;
         lv_obj_t *eHParc_label;
lv_obj_t * eMParc;
         lv_obj_t *eMParc_label;
lv_anim_t eHParc_a;

lv_obj_t * BattleDialog_0;
lv_obj_t * BDialog_Item;

static int judge_();

static void set_angle(void * obj, int32_t v)
{
    lv_arc_set_value((lv_obj_t *)obj,v);
    if(obj == eHParc){
        lv_label_set_text_fmt(eHParc_label,"%d",enemy.c_healPoint);
    }
}

static void BDLOG_0(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_current_target(e);
    LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
    uint16_t selected;
    selected = lv_msgbox_get_active_btn(obj);
    if(e->code==LV_EVENT_RELEASED) {
        if (selected == 0) {

        }
        if (selected == 3) {
            lv_obj_align(BattleDialog_0, LV_ALIGN_BOTTOM_RIGHT, 1000, 1000);
            lv_obj_align(BDialog_Item, LV_ALIGN_CENTER, 0, 0);
        }
    }
}

static void BDLST_ITEM(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    const char *ab;
    ab = lv_list_get_btn_text(BDialog_Item, obj);
    if(code == LV_EVENT_CLICKED) {
        if(strcmp(ab,"Return")==0){
            lv_obj_align(BDialog_Item, LV_ALIGN_BOTTOM_RIGHT , 1000, 1000);
            lv_obj_align(BattleDialog_0, LV_ALIGN_BOTTOM_MID, 0, -50);
        }
    }
}


void testBattle_init(){
    float ab = 0.00;
    player.init_test();
    enemy.init_test();

    bscr = lv_obj_create(NULL);
    lv_scr_load(bscr);

    static lv_style_t style_HParc;
    lv_style_init(&style_HParc);
    //lv_style_set_arc_color(&style_HParc, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_arc_color(&style_HParc, lv_palette_main(LV_PALETTE_RED));
    static lv_style_t style_MParc;
    lv_style_init(&style_MParc);
    //lv_style_set_arc_color(&style_HParc, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_arc_color(&style_MParc, lv_palette_main(LV_PALETTE_CYAN));

    playerName = lv_label_create(bscr);
    lv_label_set_text(playerName, "PlayerSample");
    lv_obj_set_width(playerName, 300);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(playerName, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align(playerName, LV_ALIGN_TOP_LEFT, 0, 0);

    HParc = lv_arc_create(bscr);
    lv_arc_set_rotation(HParc, 270);
    lv_arc_set_bg_angles(HParc, 0, 360);
    lv_obj_remove_style(HParc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(HParc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_align(HParc, LV_ALIGN_TOP_LEFT, 20, 50);
    lv_obj_add_style(HParc, &style_HParc, LV_PART_INDICATOR );
    ab = 1.000 * (player.c_healPoint/player.healPoint)*100;
    lv_arc_set_value(HParc, (int)ab);

    HParc_label = lv_label_create(HParc);
    lv_label_set_text_fmt(HParc_label, "%d",player.c_healPoint);
    lv_obj_set_width(HParc_label, 300);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(HParc_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(HParc_label, LV_ALIGN_CENTER, 0, 0);

    MParc = lv_arc_create(bscr);
    lv_arc_set_rotation( MParc , 270);
    lv_arc_set_bg_angles( MParc , 0, 360);
    lv_obj_remove_style( MParc , NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag( MParc , LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_align( MParc , LV_ALIGN_TOP_LEFT, 20, 200);
    lv_obj_add_style( MParc , &style_MParc, LV_PART_INDICATOR );
    ab = 1.0000 * player.c_energyPoint/player.energyPoint*100;
    lv_arc_set_value( MParc , (int16_t)ab);

    MParc_label = lv_label_create( MParc );
    lv_label_set_text_fmt(MParc_label, "%d",player.c_energyPoint);
    lv_obj_set_width(MParc_label, 300);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(MParc_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(MParc_label, LV_ALIGN_CENTER, 0, 0);

    enemyName = lv_label_create(bscr);
    lv_label_set_text(enemyName, "EnemySample");
    lv_obj_set_width(enemyName, 300);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(enemyName, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_align(enemyName, LV_ALIGN_TOP_RIGHT, 0, 0);

    eHParc = lv_arc_create(bscr);
    lv_arc_set_rotation(eHParc, 270);
    lv_arc_set_bg_angles(eHParc, 0, 360);
    lv_obj_remove_style(eHParc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(eHParc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_align(eHParc, LV_ALIGN_TOP_RIGHT, -20, 50);
    lv_obj_add_style(eHParc, &style_HParc, LV_PART_INDICATOR );
    ab = 1.000 * (enemy.c_healPoint/enemy.healPoint)*100;
    lv_arc_set_value(eHParc, (int)ab);

    eHParc_label = lv_label_create(eHParc);
    lv_label_set_text_fmt(eHParc_label, "%d",enemy.c_healPoint);
    lv_obj_set_width(eHParc_label, 300);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(eHParc_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(eHParc_label, LV_ALIGN_CENTER, 0, 0);

    eMParc = lv_arc_create(bscr);
    lv_arc_set_rotation( eMParc , 270);
    lv_arc_set_bg_angles( eMParc , 0, 360);
    lv_obj_remove_style( eMParc , NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag( eMParc , LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_align( eMParc , LV_ALIGN_TOP_RIGHT, -20, 200);
    lv_obj_add_style( eMParc , &style_MParc, LV_PART_INDICATOR );
    ab = 1.0000 * enemy.c_energyPoint/enemy.energyPoint*100;
    lv_arc_set_value( eMParc , (int16_t)ab);

    eMParc_label = lv_label_create( eMParc );
    lv_label_set_text_fmt(eMParc_label, "%d",enemy.c_energyPoint);
    lv_obj_set_width(eMParc_label, 300);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(eMParc_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(eMParc_label, LV_ALIGN_CENTER, 0, 0);

    lv_anim_init(&eHParc_a);
    lv_anim_set_var(&eHParc_a, eHParc);
    lv_anim_set_exec_cb(&eHParc_a, set_angle);
    lv_anim_set_time(&eHParc_a, 500);
    lv_anim_set_repeat_count(&eHParc_a, 1);    /*Just for the demo*/
    //lv_anim_set_values(&HParc_a, 0, 100);

    static const char * btns[] = {"Attack", "SKILL", "DEFENSE","ITEMS","ESCAPE"};

    BattleDialog_0 = lv_msgbox_create(bscr, "Dialog", "It's your turn!Please select an option.", btns, false);
    lv_obj_set_width(BattleDialog_0, 900);
    lv_obj_set_height(BattleDialog_0, 200);
    lv_obj_add_event_cb(BattleDialog_0, BDLOG_0, LV_EVENT_RELEASED, NULL);
    lv_obj_set_size(lv_msgbox_get_btns(BattleDialog_0),900,70);
    lv_obj_align(BattleDialog_0, LV_ALIGN_BOTTOM_MID, 0, -50);

    BDialog_Item = lv_list_create(bscr);
    lv_obj_set_size(BDialog_Item, 500, 500);
    lv_obj_align(BDialog_Item, LV_ALIGN_BOTTOM_RIGHT , 1000, 1000);

    lv_obj_t * btn;

    lv_list_add_text(BDialog_Item, "CONTROL");
    btn = lv_list_add_btn(BDialog_Item, LV_SYMBOL_CLOSE, "Return");
    lv_obj_add_event_cb(btn, BDLST_ITEM, LV_EVENT_CLICKED, NULL);
}

static int judge_(){

}