//
// Created by enVine on 2022/11/18.
//

#include <cstring>
#include "PlayerData.h"

PlayerData player;

void PlayerData::init() {
    //name = "埃科西娅";
    strcpy(name,"埃科西娅");
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

void PlayerData::init_test() {
    healPoint = 1;
    c_healPoint = 1;
    energyPoint = 790;
    c_energyPoint = 75;
    attack = 45;
    mAttack = 53;
    defense = 28;
    mDefense = 40;
    agile = 32;
    critical = 0.11;

    RES_sleep = 0.2;
    RES_confusion = 0.2;
    RES_floppy = 0.2;

    energyAsHP = true;
}
