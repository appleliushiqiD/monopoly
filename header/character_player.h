#ifndef CHARACTER_PLAYER_H_INCLUDED
#define CHARACTER_PLAYER_H_INCLUDED

//宏定义
#define Name_Len 11//名称长度
#define Intro_Len 11//简介长度
#define Description_Len 101//描述长度
#define Max_Character 6//拥有角色最大数

//角色结构体
typedef struct character
{
    int id;//编号
    int owner;//拥有者
    int degree;//等级
    int expenses;//费用
    int protection_fee;//保护费
    int bonus;//福利
    int fine;//罚金
    char name[Name_Len];//名称
    char introduction[Intro_Len];//简介
    char description[Description_Len];//描述
}Character;

//玩家结构体
typedef struct player
{
    int id;//编号
    int fund;//资金
    int status;//状态
    int position;//位置
    int characters[Max_Character+1];//拥有角色，第一位是总角色数
    char name[Name_Len];//名称
}Player;


#endif // CHARACTER_PLAYER_H_INCLUDED
