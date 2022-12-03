//
// Created by enVine on 2022/11/19.
//
#include <cstdlib>
#include "store.h"
#include "res.h"

extern char *text;
extern char *dest;

static void anim_prep_and_start(lv_obj_t *obj,const char *format,...);
static void nxStep(lv_event_t * e);
static void nav(int a);

extern int l_step;

extern lv_anim_t anim;

extern lv_timer_t *tim;
extern lv_timer_t *text_passin;
static void textAnim(lv_timer_t * timer);
static void animSync(lv_timer_t * timer);
static void anim_cb(void * var, int32_t v);

extern lv_obj_t *cScr;

lv_obj_t *cbg;

extern lv_obj_t *dialog_text;
extern lv_obj_t *button;

void prep_ckpt_0_1(lv_obj_t *obj){
    cScr = obj;

    cbg = lv_img_create(cScr);
    lv_img_set_src(cbg,&cave_img);
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

static void nav(int a) {
    switch (a) {
        case 0:
             anim_prep_and_start(dialog_text,"%s","每年，都有不计其数的人遭受黑恶势力的迫害。");
            l_step = 1;
            break;
        case 1:
             anim_prep_and_start(dialog_text,"%s","这个世界从来都不安全");
            l_step = 2;
            break;
        case 2:
             anim_prep_and_start(dialog_text,"%s","它与你所熟悉的世界有许多不同");
            l_step = 3;
            break;
        case 3:
             anim_prep_and_start(dialog_text,"%s","这是一个拥有魔法，拥有超自然生物的世界\n无数人享受着超自然力量带来的便利\n每个人都可以拥有独属于自己的力量");
            l_step = 4;
            break;
        case 4:
             anim_prep_and_start(dialog_text,"%s","但是，人们虽然手握着力量，却迟迟没办法理解为何力量产生了");
            l_step = 5;
            break;
        case 5:
             anim_prep_and_start(dialog_text,"%s","于是，人们将其归结于[神明]的存在");
            l_step = 6;
            break;
        case 6:
             anim_prep_and_start(dialog_text,"%s","一部分人漠不关心，一部分人追寻神明，一部分人始终坚信，力量源自于自己");
            l_step = 7;
            break;
        case 7:
             anim_prep_and_start(dialog_text,"%s","本就不存在的奇迹，因为某些被误解的事情\n被某些人当作了真");
            l_step = 8;
            break;
        case 8:
             anim_prep_and_start(dialog_text,"%s","他们疯狂的去追寻，去寻找传说中的神明");
            l_step = 9;
            break;
        case 9:
             anim_prep_and_start(dialog_text,"%s","于是，有些人彻底疯狂");
            l_step = 10;
            break;
        case 10:
             anim_prep_and_start(dialog_text,"%s","他们仿佛变成了原始人一般\n疯狂的去为所谓[神明]奉献一切\n为此不惜一切去牺牲自己，牺牲他人也在所不惜");
            l_step = 11;
            break;
        case 11:
             anim_prep_and_start(dialog_text,"%s","#ff0000 你只是其中之一#");
            l_step = 12;
            break;
        case 12:
             anim_prep_and_start(dialog_text,"%s","于是，有些人彻底疯狂");
            l_step = 13;
            break;
        case 13:
             anim_prep_and_start(dialog_text,"%s","");
            lv_img_set_src(cbg,&Player_FullImage);
            l_step = 14;
            break;
        case 14:
            anim_prep_and_start(dialog_text,"你是%s\n出生在一个▩▩▩▩▩",player.name);
            lv_img_set_src(cbg,&cave_img);
            l_step = 15;
            break;
        case 15:
             anim_prep_and_start(dialog_text,"%s","虽然从来就不知道自己的父母是谁\n但是从有记忆的时候开始\n自己就在经营着一家药店");
            lv_img_set_src(cbg,&cave_img);
            l_step = 16;
            break;
        case 16:
             anim_prep_and_start(dialog_text,"%s","这非常蹊跷，但没有办法，现实或许就是这样\n毕竟与其一直死磕在失忆问题上\n还是生活最为重要");
            l_step = 17;
            break;
        case 17:
             anim_prep_and_start(dialog_text,"%s","[档案损坏]");
            l_step = 18;
            break;
        case 18:
             anim_prep_and_start(dialog_text,"%s","ERROR_CODE:43\nEACCES:Operation not permitted");
            l_step = 19;
            break;
        case 19:
            //exit(43);
            l_step = 20;
            break;
        case 20:
             anim_prep_and_start(dialog_text,"%s","#ff0000 鲜血 #早已干涸...");
            l_step = 21;
            break;
        case 21:
             anim_prep_and_start(dialog_text,"%s","少女的尸体，此刻也依旧静静的躺在石头所作的台上。");
            l_step = 22;
            break;
        case 22:
             anim_prep_and_start(dialog_text,"%s","或许这个山洞唯一的特点就是采光还算良好\n能见度还算高，可以看清洞内所有的东西");
            l_step = 23;
            break;
        case 23:
             anim_prep_and_start(dialog_text,"%s","");
            lv_img_set_src(cbg,&crystals);
            l_step = 24;
            break;
        case 24:
             anim_prep_and_start(dialog_text,"%s","天花板上，有无数的大型蓝色晶体悬挂于此");
            lv_img_set_src(cbg,&cave_img);
            l_step = 25;
            break;
        case 25:
             anim_prep_and_start(dialog_text,"%s","这是一个祭祀用的洞窟\n洞璧上画有无法识别的符号\n除此之外便是少女所在的石桌");
            l_step = 26;
            break;
        case 26:
             anim_prep_and_start(dialog_text,"%s","突然\n一块蓝晶石就这样毫无预兆的掉落下来");
            l_step = 27;
            break;
        case 27:
             anim_prep_and_start(dialog_text,"%s","晶石的强度并没有到非常可怕的程度\n它#0000FF 摔碎#了");
            l_step = 28;
            break;
        case 28:
             anim_prep_and_start(dialog_text,"%s","刹那间，所有的蓝晶石同时爆发出了强烈的蓝色光茫");
            l_step = 29;
            break;
        case 29:
             anim_prep_and_start(dialog_text,"%s","如同共鸣一般，就连少女的遗体，也绽放出了光茫");
            l_step = 30;
            break;
        case 30:
             anim_prep_and_start(dialog_text,"%s","...");
            l_step = 31;
            break;
        case 31:
             anim_prep_and_start(dialog_text,"%s","光茫消失了,除了蓝晶石以外，便似乎没有更多的变化了");
            l_step = 32;
            break;
        case 32:
             anim_prep_and_start(dialog_text,"%s","但异象远未结束");
            l_step = 33;
            break;
        case 33:
             anim_prep_and_start(dialog_text,"%s","不知何时，少女已经不再残破不堪");
            l_step = 34;
            break;
        case 34:
             anim_prep_and_start(dialog_text,"%s","紧接着....");
            l_step = 35;
            break;
        case 35:
             anim_prep_and_start(dialog_text,"%s","少女睁开了双眼，重新看到了这个世界");
            l_step = 36;
            break;
        case 36:
            anim_prep_and_start(dialog_text,"%s","......");
            l_step = 37;
            break;
        case 37:
            anim_prep_and_start(dialog_text,"%s","[从现在开始，你可以操作你的角色]");
            l_step = 38;
            break;
        case 38:
            player.checkpoint_0_1 = true;
            lanix_nextStep(LANIX_SCENE_OUTSKIRT_UCAVE_SPLT4);
            break;
    }
}

static int length;
static int w_Pos;
static int h_Pos;
static int w_Pos_ml;
static int t_Pos;
static void anim_prep_and_start(lv_obj_t *obj,const char *format,...){
    va_list _args;
    va_start(_args,format);
    uint32_t len = lv_vsnprintf(NULL, 0, format, _args);
    lv_vsnprintf(text, len+1, format, _args);
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
    text_passin = lv_timer_create(textAnim,20,NULL);
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
        memset(dest,'\0',4096);
        memcpy(dest,text,t_Pos);
        lv_label_set_text_fmt(dialog_text,"%s",dest);
    }
    //lv_obj_set_size(dialog_text, (w_Pos_ml +1) * 36,h_Pos * 28);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_width(dialog_text,1366);
    lv_obj_set_height(dialog_text,6+h_Pos*28);
    lv_obj_set_style_text_align(dialog_text, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(dialog_text , LV_ALIGN_CENTER, 0, 0);
}
