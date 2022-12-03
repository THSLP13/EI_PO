//
// Created by enVine on 2022/11/17.
//

#ifndef EIPO_LEVELTREE_H
#define EIPO_LEVELTREE_H

#include "../lvgl/lvgl.h"
#include "../BATTLE/battleTree.h"
#include "../PlayerData.h"

extern PlayerData player;

#include <thread>
#include <chrono>
#include "time.h"

void thr_init();

extern lv_obj_t * title_Base;
extern lv_obj_t * title_main_Base;
void title_load();
void title_main();

#include "Lanix_outskirt_unknownCave/store.h"
extern void lanix_baseUI_Crate();

#endif //EIPO_LEVELTREE_H
