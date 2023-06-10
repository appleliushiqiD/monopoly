#ifndef EDITER_FUNCTIONS_H_INCLUDED
#define EDITER_FUNCTIONS_H_INCLUDED

#include <stdio.h>//stdin参数
#include <stdlib.h>
#include <string.h>//字符串操作
#include <ctype.h>//字符判断
#include <windows.h>//清屏及休眠
#include "character_player.h"

#define Character_Len 30//角色数量
#define Cleaner while((c=getchar())!=EOF&&c!='\n')//清空缓冲区

//函数声明
char show_menu(void);//显示菜单
char import_character(char file_name[], Character characters[]);//导入角色信息
void show_character(const Character * sh_character);//打印单个角色信息
void get_string(char str[], const unsigned int str_len);//获取字符串
char search_character(Character characters[]);//查找角色
void change_character(Character * ch_character);//修改角色信息
char rewrite(Character characters[]);//全部重写
char update_file(char file_name[], Character characters[]);//更新文件

//函数定义
char show_menu(void)
{//显示菜单
    char c;
    char choice;

    system("cls");
    printf("\n\n");
    printf("\t\t1. 查询已有角色信息\n");
    Sleep(50);
    printf("\t\t2. 全部重写\n");
    Sleep(50);
    printf("\t\t3. 更新角色文件\n");
    Sleep(50);
    printf("\t\t0. 退出\n");
    Sleep(50);
    printf("\n\t\t修改内容后或全部重写后，请选择“更新角色文件”，否则不会修改原有角色文件\n");
    Sleep(50);
    printf("\n\n");
    printf("\t\t请选择：");
    choice = getchar();
    Cleaner;//清空输入缓存
    return choice;
}

char import_character(char file_name[], Character characters[])
{//导入角色信息
    FILE * chara_file = NULL;
    chara_file = fopen(file_name, "rb");

    if(chara_file==NULL)
    {
        return 'f';
    }
    else if(fread(characters, sizeof(Character), Character_Len, chara_file)!=Character_Len)
    {
        fclose(chara_file);
        return 'f';
    }
    else
    {
        fclose(chara_file);
        return 't';
    }
}

void show_character(const Character * sh_character)
{//打印角色信息
    printf("\n\n");
    printf("\t\t角色信息：\n\n\n");
    Sleep(50);
    printf("\t\t编号：%d\n\n", sh_character->id);
    Sleep(50);
    printf("\t\t价格：%4d * 等级\t保护费：%4d * 等级\n\n", sh_character->expenses, sh_character->protection_fee);
    Sleep(50);
    printf("\t\t福利：%4d\t\t罚金：%4d\n\n", sh_character->bonus, sh_character->fine);
    Sleep(50);
    printf("\t\t名字：%s\t\t简介：%s\n\n", sh_character->name, sh_character->introduction);
    Sleep(50);
    printf("\t\t描述：%s\n", sh_character->description);
    Sleep(50);
    printf("\n\n");
}

void get_string(char str[], const unsigned int str_len)
{//获取字符串
    char c;//清理缓存变量
    do{
        fgets(str, str_len, stdin);
        if(str[0] == '\n')//输入回车
        {
            printf("\t\t输入错误（不要输入换行符）\n");
            printf("\n\t\t请重新输入：");
        }
        else if(str[strlen(str)-1]=='\n')//末尾多换行符
        {
            str[strlen(str)-1] = '\0';
        }
        else
        {
            Cleaner;//清空缓存
        }
    }while(str[0] == '\n');
}

char search_character(Character characters[])
{//查找角色
    int i;//循环变量
    char c;//清除缓存变量
    char change_name[Name_Len];//查询角色名称
    char change_flag;//修改选择

    system("cls");
    printf("\n\n");
    printf("\t\t输入需要修改角色的名字：");
    get_string(change_name, Name_Len);
    i = 0;
    while(i<Character_Len)
    {
        if(strcmp(change_name, characters[i].name)==0)
        {
            show_character(&characters[i]);
            printf("\t\t是否修改？（y/n）：");
            change_flag = getchar();
            Cleaner;
            if(change_flag=='y')
            {
                change_character(&characters[i]);
                return 't';
            }
            else
            {
                printf("\t\t没有进行修改\n");
                return 't';
            }
        }
        else if(i==Character_Len-1)
        {
            return 'f';
        }
        else
        {
            i++;
        }
    }
    return 'f';
}

void change_character(Character * ch_character)
{//修改角色信息
    char c;//清理缓存变量

    ch_character->degree = 0;
    ch_character->owner = 0;
    printf("\t\t价格、过路费、福利、罚金均为自然数\n");
    printf("\t\t其他为字符类型\n\n\n");
    printf("\t\t1. 输入价格：");
    scanf("%d",&ch_character->expenses);
    Cleaner;
    printf("\t\t2. 输入过路费：");
    scanf("%d",&ch_character->protection_fee);
    Cleaner;
    printf("\t\t3. 输入福利：");
    scanf("%d",&ch_character->bonus);
    Cleaner;
    printf("\t\t4. 输入罚金：");
    scanf("%d",&ch_character->fine);
    Cleaner;
    printf("\t\t5. 输入名字（不多于%d个汉字）：", (Name_Len-1)/2);
    get_string(ch_character->name, Name_Len);
    printf("\t\t6. 输入简介（不多于%d个汉字）：", (Intro_Len-1)/2);
    get_string(ch_character->introduction, Intro_Len);
    printf("\t\t7. 输入描述（不多于%d个汉字）：", (Description_Len-1)/2);
    get_string(ch_character->description, Description_Len);
    printf("\n\n");
    printf("\t\t已修改！");
}

char rewrite(Character characters[])
{//全部重写
    int i;//循环变量
    for(i=0;i<Character_Len;i++)
    {
        system("cls");
        printf("\n\n");
        printf("\t\t第%d位\n\n", i+1);
        characters[i].id = i+1;//自动化编号
        change_character(&characters[i]);
    }
    system("cls");
    printf("\n\n");
    printf("\t\t写入完成，请及时更新文件！！！\n");
    return 't';
}

char update_file(char file_name[], Character characters[])
{//更新文件
    FILE * chara_file = NULL;

    chara_file = fopen(file_name, "wb");
    if(fwrite(characters, sizeof(Character), Character_Len, chara_file)!=Character_Len)
    {
        return 'f';
    }
    else
    {
        system("cls");
        printf("\n\n");
        printf("\t\t更新完成\n");
        fclose(chara_file);
        return 't';
    }
}

#endif // EDITER_FUNCTIONS_H_INCLUDED
