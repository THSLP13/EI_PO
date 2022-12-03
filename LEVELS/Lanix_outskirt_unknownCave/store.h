//
// Created by enVine on 2022/11/19.
//

#ifndef EIPO_STORE_H
#define EIPO_STORE_H

#include "../levelTree.h"

#define LANIX_SCENE_OUTSKIRT_UCAVE_SPLT1 1
#define LANIX_SCENE_OUTSKIRT_UCAVE_SPLT2 2
#define LANIX_SCENE_OUTSKIRT_UCAVE_SPLT3 3
#define LANIX_SCENE_OUTSKIRT_UCAVE_SPLT4 4

void lanix_nextStep(int scene);

void lanix_baseUI_Crate();

extern void prep_ckpt_0_0(lv_obj_t *obj);
extern void prep_ckpt_0_1(lv_obj_t *obj);
extern void prep_ckpt_0_2(lv_obj_t *obj);

#endif //EIPO_STORE_H
