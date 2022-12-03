//
// Created by enVine on 2022/11/19.
//
#include <cstdlib>
#include "store.h"

char *text;
char *dest;

static void anim_prep_and_start(lv_obj_t *obj,const char *format,...);
static void nxStep(lv_event_t * e);
static void winH1(lv_event_t * e);
void nav(int a);

int l_step;

lv_anim_t anim;

lv_timer_t *tim;
lv_timer_t *text_passin;
static void textAnim(lv_timer_t * timer);
static void animSync(lv_timer_t * timer);
static void anim_cb(void * var, int32_t v);

lv_obj_t *cScr;

lv_obj_t *dialog_text;
lv_obj_t *button;

lv_obj_t *nameDialog;lv_obj_t *ct;
lv_obj_t *nDl_label,*nDl_nameArea;

void prep_ckpt_0_0(lv_obj_t *obj){
    cScr = obj;
    lv_obj_add_event_cb(cScr, nxStep,LV_EVENT_CLICKED,NULL);
    dialog_text = lv_label_create(cScr);
    lv_label_set_text_fmt(dialog_text, "%s\n%s","系统消息","正在加载中");
    lv_label_set_recolor(dialog_text, true);
    lv_obj_set_size(dialog_text, 1300,120);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(dialog_text, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(dialog_text , LV_ALIGN_CENTER, 0, 0);

    button = lv_btn_create(obj);
    lv_obj_add_event_cb(button, nxStep, LV_EVENT_ALL, NULL);
    lv_obj_set_size(button,50,50);
    lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, -40);

    tim = lv_timer_create(animSync, 0,  NULL);
    lv_timer_reset(tim);

    text = (char *)lv_malloc(4096);
    dest = (char *)lv_malloc(4096);

    nav(0);
}

static void nxStep(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        nav(l_step);
    }
}

static void winH1(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);

    title_main();
}

void nav(int a) {
    switch (a) {
        case 0:
            // anim_prep_and_start(dialog_text,"%s","你遭受非人的折磨");
            anim_prep_and_start(dialog_text,"%s","你遭受非人的折磨");
            l_step = 1;
            break;
        case 1:
            anim_prep_and_start(dialog_text,"%s","你流尽无限的鲜血 ");
            l_step = 2;
            break;
        case 2:
             anim_prep_and_start(dialog_text,"%s","你曾哀嚎着请求敌人的仁慈 ");
            l_step = 3;
            break;
        case 3:
             anim_prep_and_start(dialog_text,"%s","徒留刺耳的狂笑 ");
            l_step = 4;
            break;
        case 4:
             anim_prep_and_start(dialog_text,"%s","...... ");
            l_step = 5;
            break;
        case 5:
             anim_prep_and_start(dialog_text,"%s","猎物哦 你不要挣扎呀");
            l_step = 6;
            break;
        case 6:
            lv_label_set_text_fmt(dialog_text, "%s", "#ff0000 敌人 会笑#");

            lv_anim_init(&anim);
            lv_anim_set_var(&anim, dialog_text);
            lv_anim_set_values(&anim, 0, 255);
            lv_anim_set_time(&anim, 500);
            lv_anim_set_exec_cb(&anim, anim_cb);
            lv_anim_set_path_cb(&anim, lv_anim_path_ease_in);
            lv_anim_start(&anim);

            lv_timer_set_period(tim,500);
            break;
        case 9:
            lv_timer_set_period(tim,3000);
            break;
        case 10:
            lv_obj_set_style_opa(dialog_text, 255, 0);
             anim_prep_and_start(dialog_text,"%s","序章 - All is Unknown");
            l_step = 11;
            break;
        case 11:
             anim_prep_and_start(dialog_text,"%s","请点击下方按钮\n在弹出的窗口填写角色名\n若不想创建存档可以取消");
            l_step = 12;
            break;
        case 12:
            nameDialog = lv_win_create(cScr,40);
            lv_obj_set_size(nameDialog,500,500);
            lv_obj_center(nameDialog);
            lv_obj_t * btn;
            btn = lv_win_add_btn(nameDialog, "Exit", 40);
            lv_obj_add_event_cb(btn, winH1, LV_EVENT_CLICKED, NULL);

            lv_win_add_title(nameDialog, "创建角色");
            ct= lv_win_get_content(nameDialog);

            nDl_label = lv_label_create(ct);
            lv_label_set_text_fmt(nDl_label, "%s","游戏内的唯一自定义角色\n拥有固定初始面板和属性\n角色名:");
            lv_obj_set_size(nDl_label, 400,120);  /*Set smaller width to make the lines wrap*/
            lv_obj_set_style_text_align(nDl_label, LV_TEXT_ALIGN_LEFT, 0);
            lv_obj_align(nDl_label , LV_ALIGN_TOP_LEFT, 0, 0);

            nDl_nameArea = lv_textarea_create(ct);
            lv_textarea_set_one_line(nDl_nameArea, true);
            lv_obj_align(nDl_nameArea, LV_ALIGN_TOP_LEFT, 0, 120);
            lv_obj_add_state(nDl_nameArea, LV_STATE_FOCUSED); /*To be sure the cursor is visible*/
            l_step = 13;
            break;
        case 13:
            lv_obj_del(nDl_nameArea);
            lv_label_set_text_fmt(nDl_label,  "在开始之前，我有必要提醒一句(即使一旦开始我便什么也记不得了)\n\n"
                                                      "我事实上已经不属于传统的生物了，所以任何对我的攻击都将直接作用在我的魔力池之中。"
                                                      "当我的魔力枯竭的时候，我就会暂时休眠。\n"
                                                      "我擅长大型镰刀和双刀的使用，但其它武器我也有所涉猎\n"
                                                      "<!>该角色没有等级划分\n\n"
                                                      "角色名:%s\n"
                                                      "HP:  %d MP:  %d\n"
                                                      "ATK: %.0f MTK: %.0f\n"
                                                      "MATK:%.0f MDEF:%.0f\n"
                                                      ""
                                                      ,player.name
                                                      ,player.healPoint,player.energyPoint
                                                      ,player.attack,player.mAttack
                                                      ,player.defense,player.mDefense
                                                      );
            lv_obj_set_size(nDl_label, 400,1000);  /*Set smaller width to make the lines wrap*/
            lv_obj_set_style_text_align(nDl_label, LV_TEXT_ALIGN_LEFT, 0);
            lv_obj_align(nDl_label , LV_ALIGN_TOP_LEFT, 0, 0);
            l_step = 14;
            break;
        case 14:
            player.checkpoint_0_0 = true;
            lanix_nextStep(LANIX_SCENE_OUTSKIRT_UCAVE_SPLT4);
            break;
    }


}

void animSync(lv_timer_t * timer)
{
    /*Use the user_data*/
    uint32_t * user_data = (uint32_t *)timer->user_data;

    switch(l_step){
        case 6:
            //l_step = 7;
            break;
        case 7:
            lv_anim_set_values(&anim, 255, 0);
            l_step = 8;
            lv_anim_start(&anim);
            break;
        case 9:
            l_step = 10;
            nav(10);
            break;
    }
}

static void anim_cb(void * var, int32_t v)
{
    switch(l_step){
        case 6:
            lv_obj_set_style_opa((lv_obj_t *)var, v, 0);
            if(v == 255){
                lv_timer_set_period(tim,1000);
                l_step = 7;
            }
            break;
        case 8:
            lv_obj_set_style_opa((lv_obj_t *)var, v, 0);
            if(v == 0){
                l_step = 9;
                nav(9);
            }
            break;
    }
}

int length;
int w_Pos;
int h_Pos;
int w_Pos_ml;
int t_Pos;
static void anim_prep_and_start(lv_obj_t *obj,const char *format,...){
    va_list _args;
    va_start(_args,format);
    uint32_t len = lv_vsnprintf(NULL, 0, format, _args);
    lv_vsnprintf(text, len+1, format, _args);
    //text[len] = 0;
    memset(text+len,'\0',1);
    //lv_label_set_text_fmt(obj,"%s",text);
    va_end(_args);
    length = len+1;
    w_Pos = 0;
    h_Pos = 1;
    w_Pos_ml = 0;
    t_Pos = 0;

    if(text_passin != nullptr) {
        lv_timer_del(text_passin);
    }
    text_passin = lv_timer_create(textAnim,50,NULL);
    lv_timer_reset(text_passin);

    lv_obj_clear_flag(cScr,LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(dialog_text, 0,0);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(dialog_text, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(dialog_text , LV_ALIGN_CENTER, 0, 0);
}

static void textAnim(lv_timer_t * timer){
    t_Pos+=1;
    if(t_Pos > length){
        lv_obj_add_flag(cScr,LV_OBJ_FLAG_CLICKABLE);
        lv_timer_reset(timer);
        t_Pos--;
        return;
    }
    if(text[t_Pos] == '\n'){
    //if(1==0){
        h_Pos++;
    }else{
        w_Pos ++;
        //strncat(dest,text,t_Pos);
        //strcpy_s(dest,t_Pos,text);
        memset(dest,'\0',4096);
        memcpy(dest,text,t_Pos);
        LV_ASSERT(dest != nullptr);
        lv_label_set_text_fmt(dialog_text,"%s",dest);
    }
    //lv_obj_set_size(dialog_text, (w_Pos_ml +1) * 36,h_Pos * 28);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_width(dialog_text,1366);
    lv_obj_set_height(dialog_text,6+h_Pos*28);
    lv_obj_set_style_text_align(dialog_text, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(dialog_text , LV_ALIGN_CENTER, 0, 0);
}
