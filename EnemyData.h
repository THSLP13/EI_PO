//
// Created by enVine on 2022/11/18.
//

#ifndef EIPO_ENEMYDATA_H
#define EIPO_ENEMYDATA_H


class EnemyData {
public:
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

    void init();
    void init_test();

private:
};


#endif //EIPO_ENEMYDATA_H
