//
// Created by enVine on 2022/11/18.
//

#include "EnemyData.h"

void EnemyData::init() {
    healPoint = 0;
    energyPoint = 0;
    attack = 0;
    mAttack = 0;
    defense = 0;
    mDefense = 0;
    agile = 0;
    critical = 0;

    RES_sleep = 0;
    RES_confusion = 0;
    RES_floppy = 0;
}

void EnemyData::init_test() {
    healPoint = c_healPoint = 1240;
    energyPoint = c_energyPoint = 0;
    attack = 55;
    mAttack = 0;
    defense = 40;
    mDefense = 0;
    agile = 21;
    critical = 0.2;

    RES_sleep = 0;
    RES_confusion = 0;
    RES_floppy = 0;
}
