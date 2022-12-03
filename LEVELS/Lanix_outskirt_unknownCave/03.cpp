//
// Created by enVine on 2022/11/20.
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
extern int l_room;

extern lv_anim_t anim;

extern lv_timer_t *tim;
extern lv_timer_t *text_passin;
static void textAnim(lv_timer_t * timer);
static void animSync(lv_timer_t * timer);
static void anim_cb(void * var, int32_t v);

extern lv_obj_t *cScr;

extern lv_obj_t *cbg;

extern lv_obj_t *dialog_text;
extern lv_obj_t *button;

lv_obj_t *blend_HParc;
extern lv_obj_t *HParc;
extern lv_obj_t *HParc_label;

lv_obj_t *action_list;
lv_obj_t *action_Bars;
static void actList_cb(lv_event_t * e);

void prep_ckpt_0_2(lv_obj_t *obj){
    cScr = obj;
    float ab = 0.00;

    cbg = lv_img_create(cScr);
    lv_img_set_src(cbg,&cave_img);
    lv_obj_add_event_cb(cScr, nxStep,LV_EVENT_CLICKED,NULL);
    dialog_text = lv_label_create(cScr);
    lv_label_set_text_fmt(dialog_text, "%s\n%s","请稍后","正在加载资源");
    lv_label_set_recolor(dialog_text, true);
    lv_obj_set_size(dialog_text, 1300,120);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(dialog_text, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(dialog_text , LV_ALIGN_CENTER, 0, 0);

    button = lv_btn_create(obj);
    lv_obj_add_event_cb(button, nxStep, LV_EVENT_ALL, NULL);
    lv_obj_set_size(button,50,50);
    lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, -40);


    static lv_style_t style_HParc;
    lv_style_init(&style_HParc);
    //lv_style_set_arc_color(&style_HParc, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_arc_color(&style_HParc, lv_palette_main(LV_PALETTE_CYAN));

    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(200, 200)];
    blend_HParc = lv_canvas_create(cScr);
    lv_canvas_set_buffer(blend_HParc, cbuf, 200, 200, LV_IMG_CF_TRUE_COLOR);
    lv_canvas_fill_bg(blend_HParc, lv_color_hex(0xFFFFFF),LV_OPA_COVER);
    lv_obj_set_size(blend_HParc,170,170);
    lv_obj_align(blend_HParc, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_style_opa(blend_HParc,LV_OPA_60,0);

    HParc = lv_arc_create(blend_HParc);
    lv_arc_set_rotation(HParc, 270);
    lv_arc_set_bg_angles(HParc, 0, 360);
    lv_obj_remove_style(HParc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(HParc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_align(HParc, LV_ALIGN_TOP_LEFT, 20, 20);
    lv_obj_add_style(HParc, &style_HParc, LV_PART_INDICATOR );
    ab = 100.000 * ((float)player.c_energyPoint/player.energyPoint);
    lv_arc_set_value(HParc, (int)ab);

    HParc_label = lv_label_create(HParc);
    lv_label_set_text_fmt(HParc_label, "MP\n%d",player.c_energyPoint);
    lv_obj_set_width(HParc_label, 300);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(HParc_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(HParc_label, LV_ALIGN_CENTER, 0, 0);


    lv_obj_set_scrollbar_mode(cScr,LV_SCROLLBAR_MODE_OFF);

    text = (char *)lv_malloc(4096);
    dest = (char *)lv_malloc(4096);

    nav(0);
}

static void nxStep(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        if(action_list != nullptr){
            lv_obj_del(action_list);
        }
        action_list = lv_list_create(cScr);
        switch(l_step){
            case 0:
                lv_list_add_text(action_list, "菜单操作");
                action_Bars = lv_list_add_btn(action_list, 0, "关闭");
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);

                lv_list_add_text(action_list, "移动");
                lv_list_add_text(action_list, "当前位置:洞穴空地");

                action_Bars = lv_list_add_btn(action_list, 0, "祭坛");
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);

                action_Bars = lv_list_add_btn(action_list, 0, "洞穴四周");
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);

                action_Bars = lv_list_add_btn(action_list, 0, "洞穴出口");
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);

                lv_obj_set_width(action_list,400);
                lv_obj_align(action_list, LV_ALIGN_CENTER, 0, 0);
                break;
            case 1:
                lv_list_add_text(action_list, "菜单操作");
                action_Bars = lv_list_add_btn(action_list, 0, "关闭");
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);

                lv_list_add_text(action_list, "移动");
                lv_list_add_text(action_list, "当前位置:洞穴内的祭坛");
                action_Bars = lv_list_add_btn(action_list, 0, "洞内的空地");
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);

                lv_obj_set_width(action_list,400);
                lv_obj_align(action_list, LV_ALIGN_CENTER, 0, 0);
                break;
            case 2:
                lv_list_add_text(action_list, "菜单操作");
                action_Bars = lv_list_add_btn(action_list, 0, "关闭");
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);

                lv_list_add_text(action_list, "移动");
                lv_list_add_text(action_list, "当前位置:洞穴的四周");
                action_Bars = lv_list_add_btn(action_list, 0, "洞内的空地");
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);

                lv_obj_set_width(action_list,400);
                lv_obj_align(action_list, LV_ALIGN_CENTER, 0, 0);
                break;
            case 3:
                lv_list_add_text(action_list, "菜单操作");
                action_Bars = lv_list_add_btn(action_list, 0, "关闭");
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);

                lv_list_add_text(action_list, "移动");
                lv_list_add_text(action_list, "当前位置:大型洞穴空地");

                action_Bars = lv_list_add_btn(action_list, 0, "前往中央的祭坛");
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);
                action_Bars = lv_list_add_btn(action_list, 0, "回到背后的洞穴");
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);
                action_Bars = lv_list_add_btn(action_list, 0, (player.c_0_2_discover_flag_Tunnel1 ? "前往左边的洞穴" : "前往左边的通道"));
                lv_obj_add_event_cb(action_Bars, actList_cb, LV_EVENT_CLICKED, NULL);

                lv_obj_set_width(action_list,400);
                lv_obj_align(action_list, LV_ALIGN_CENTER, 0, 0);
                break;
            case 4:
                lv_obj_del(action_list);
                l_step = 5;
                nav(5);
                break;
        }
    }
}

static void actList_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        char *res = (char *)lv_list_get_btn_text(action_Bars, obj);
        switch(l_step){
            case 0:
                if(strcmp(res,"关闭") == 0){
                    lv_obj_align(action_list , LV_ALIGN_BOTTOM_RIGHT, 400, 100);
                }
                if(strcmp(res,"祭坛") == 0){
                    lv_obj_align(action_list , LV_ALIGN_BOTTOM_RIGHT, 400, 100);
                    l_step = 1;
                    nav(1);
                }
                if(strcmp(res,"洞穴四周") == 0){
                    lv_obj_align(action_list , LV_ALIGN_BOTTOM_RIGHT, 400, 100);
                    l_step = 2;
                    nav(2);
                }
                if(strcmp(res,"洞穴出口") == 0){
                    lv_obj_align(action_list , LV_ALIGN_BOTTOM_RIGHT, 400, 100);
                    l_step = 3;
                    nav(3);
                }
                break;
            case 1:
                if(strcmp(res,"关闭") == 0){
                    lv_obj_align(action_list , LV_ALIGN_BOTTOM_RIGHT, 400, 100);
                }
                if(strcmp(res,"洞内的空地") == 0){
                    lv_obj_align(action_list , LV_ALIGN_BOTTOM_RIGHT, 400, 100);
                    l_step = 0;
                    nav(0);
                }
                break;
            case 2:
                if(strcmp(res,"关闭") == 0){
                    lv_obj_align(action_list , LV_ALIGN_BOTTOM_RIGHT, 400, 100);
                }
                if(strcmp(res,"洞内的空地") == 0){
                    lv_obj_align(action_list , LV_ALIGN_BOTTOM_RIGHT, 400, 100);
                    l_step = 0;
                    nav(0);
                }
                break;
            case 3:
                if(strcmp(res,"关闭") == 0){
                    lv_obj_align(action_list , LV_ALIGN_BOTTOM_RIGHT, 400, 100);
                }
                if(strcmp(res,"回到背后的洞穴") == 0){
                    lv_obj_align(action_list , LV_ALIGN_BOTTOM_RIGHT, 400, 100);
                    l_step = 0;
                    nav(0);
                }
                if(strcmp(res,"前往左边的洞穴") == 0 or strcmp(res,"前往左边的通道") == 0){
                    lv_obj_align(action_list , LV_ALIGN_BOTTOM_RIGHT, 400, 100);
                    if(strcmp(res,"前往左边的通道") == 0) {
                        l_step = 4;
                        nav(4);
                    }
                    if(strcmp(res,"前往左边的洞穴") == 0) {
                        l_step = 5;
                        nav(5);
                    }
                }
                break;
        }
    }
}

static void nav(int a) {
    switch (a) {
        case 0:
            anim_prep_and_start(dialog_text, "%s\n%s","你现在处于自由活动状态","单击按钮来决定你的行动");
            break;
        case 1:
            anim_prep_and_start(dialog_text, "%s","你回到了祭坛旁边\n这个祭坛的台面上，除了一些早已干涸的血迹便没有其他东西了。");
            break;
        case 2:
            anim_prep_and_start(dialog_text, "%s","洞穴的四周似乎没有什么值得一提的东西\n墙壁上的那些孔洞里头或许曾经有东西镶嵌其中\n但现在也空空如也了");
            break;
        case 3:
            anim_prep_and_start(dialog_text, "%s","你来到了一处更为高大的洞穴\n这里有五处通道\n其中一处通道通向的正是你先前苏醒的地方");
            break;
        case 4:
            anim_prep_and_start(dialog_text, "%s","你向未知的通道行进着...");
            break;
        case 5:
            anim_prep_and_start(dialog_text, "%s","这是另一个较小的洞穴\n同样也拥有一个祭坛\n只是上面的尸体已经只剩下了骨架\n空气弥漫着一股难闻的味道");
            player.c_0_2_discover_flag_Tunnel1 = true;
            break;
    }
}

extern int length;
extern int w_Pos;
extern int h_Pos;
extern int w_Pos_ml;
extern int t_Pos;
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
    lv_obj_set_height(dialog_text,6+h_Pos*32);
    lv_obj_set_style_text_align(dialog_text, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(dialog_text , LV_ALIGN_CENTER, 0, 0);
}
