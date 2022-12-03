//
// Created by enVine on 2022/11/18.
//

#ifndef EIPO_PLAYERDATA_H
#define EIPO_PLAYERDATA_H

typedef struct item_{
    int id;
    char *name;
    char *desc;
};

class PlayerData {

public:
    char name[16];
    int healPoint;         //HP
    int c_healPoint;
    int energyPoint;       //MP
    int c_energyPoint;
    float attack;          //ATK
    float defense;         //DEF
    float mAttack;         //MATK
    float mDefense;        //MDEF
    float agile;           //AGI敏捷
    float critical;        //CHC暴击
    float RES_sleep;       //睡眠抗性(百分比)
    float RES_confusion;   //混乱抗性
    float RES_floppy;      //无力化抗性

    bool energyAsHP;

    float natk_CD = 0;

    item_ inventory[8];

    void init();
    void init_test();

    //checkpiont var~
    bool firstTimePlay;

    bool checkpoint_0_0;

    bool checkpoint_0_1;

    bool checkpoint_0_2;
    bool c_0_2_discover_flag_Tunnel1;

private:

};

extern PlayerData player;
#endif //EIPO_PLAYERDATA_H
