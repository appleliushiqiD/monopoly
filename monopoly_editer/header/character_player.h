#ifndef CHARACTER_PLAYER_H_INCLUDED
#define CHARACTER_PLAYER_H_INCLUDED

//宏定义
#define Name_Len 11//名称长度
#define Intro_Len 11//简介长度
#define Description_Len 101//描述长度

//角色结构体
typedef struct character
{
    unsigned int id;//编号
    unsigned int owner;//拥有者
    unsigned int degree;//等级
    unsigned int expenses;//费用
    unsigned int protection_fee;//保护费
    unsigned int bonus;//福利
    unsigned int fine;//罚金
    char name[Name_Len];//名称
    char introduction[Intro_Len];//简介
    char description[Description_Len];//描述
}Character;

#endif // CHARACTER_PLAYER_H_INCLUDED
