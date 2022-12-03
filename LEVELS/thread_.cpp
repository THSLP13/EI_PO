//
// Created by enVine on 2022/11/18.
//
#define _DEFAULT_SOURCE
#include "levelTree.h"

void GUI_Draw();

std::thread *thr;
using namespace std::chrono;
void thr_init(){
    title_load();
    //在这里放初始化

    //std::this_thread::sleep_for(milliseconds(2500));
    player.init_test();

    //然后加载标题界面
    title_main();
    //testBattle_init();

    //lanix_baseUI_Crate();
    //if(player.checkpoint_0_0 == false){
    //    lanix_nextStep(LANIX_SCENE_OUTSKIRT_UCAVE_SPLT4);
    //}

    //thr = new std::thread(GUI_Draw);
}

void GUI_Draw(){
    while(1){
        lv_timer_handler();
        for(int i=0;i<84000;i++);
        //usleep(5*1000);
    }
}
