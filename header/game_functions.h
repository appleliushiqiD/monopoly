#ifndef GAME_FUNCTIONS_H_INCLUDED
#define GAME_FUNCTIONS_H_INCLUDED

#include <stdio.h>//stdin参数
#include <stdlib.h>//随机数
#include <string.h>//字符串操作
#include <ctype.h>//字符判断
#include <time.h>//时间种子
#include <windows.h>//清屏、休眠、暂停
#include <mmsystem.h>//音乐
#include "character_player.h"

//宏定义
#define BGM_num 5//BGM数量
#define Character_Len 30//角色数量
#define Player_Len 6//最大玩家数
#define Start_Money 20000//出发资金
#define Cleaner while((c=getchar())!=EOF&&c!='\n')//清空缓冲区
//状态
#define Unenabled 0//未启用
#define Active 1//活跃
#define Broke 2//破产
#define Rest 3//休息

//函数声明
/**菜单与基础*/
char music(char cammand);//播放音乐

char show_menu(void);//打印功能菜单
void game_introducation(char file_name[]);//游戏玩法介绍
char import_characters(const char file_name[], Character characters[]);//导入角色
void get_string(char str[], const unsigned int str_len);//获取字符串
int get_number(const int start, const int stop);//获取数字
/**游戏主体*/
char init_characters(Character characters[]);//初始化角色
char init_player(Player players[], unsigned int player_num);//初始化玩家
    //游戏运行
void show_map(Character characters[], Player players[], const unsigned int player_num);//显示地图和玩家位置
        //角色信息变化
int get_step(void);//掷骰子
void buy_character(Player * pre_player, Character * pre_character);//购买角色
void sell_character(Player * pre_player, Character * pre_character);//出售角色
void update_character(Player * pre_player, Character * pre_character);//升级角色
char pay_protection(Player * pre_player, Player players[], Character characters[]);//缴纳保护费
    //游戏循环
char player_turn(Player * pre_player, Player players[], Character characters[]);//修改玩家状态
void show_winner(Player players[], const unsigned int player_num);//排行榜
void run_game(Character characters[], Player players[], const unsigned int player_num);//运行游戏

/**查看角色*/
void show_character(const Character * sh_character);//打印角色信息
void search_character(Character characters[]);//查找角色


//函数定义

/**菜单与基础函数*/

char music(char cammand)
{//播放音乐
    switch(cammand)
    {
    case 'p'://播放音乐
        if(mciSendString("play BGM", NULL, 0, NULL))
        {
            return 'f';
        }
        else
        {
            return 't';
        }
        break;
    case 'r'://重复播放
        if(mciSendString("play BGM repeat", NULL, 0, NULL))
        {
            return 'f';
        }
        else
        {
            return 't';
        }
        break;
    case 's'://暂停播放
        if(mciSendString("stop BGM", NULL, 0, NULL))
        {
            return 'f';
        }
        else
        {
            return 't';
        }
        break;
    case 'c'://关闭文件
        if(mciSendString("close BGM", NULL, 0, NULL))
        {
            return 'f';
        }
        else
        {
            return 't';
        }
        break;
    }
    return 'f';
}

char show_menu(void)
{//打印功能菜单
    char c;
    char choice;

    system("cls");
    printf("\n\n");
    printf("\t\tWelcome to play!\n\n");
    Sleep(50);
    printf("\t\t1. 开始新游戏\n");
    Sleep(50);
    printf("\t\t2. 查看游戏玩法\n");
    Sleep(50);
    printf("\t\t3. 查看角色简介\n");
    Sleep(50);
    printf("\t\t0. 退出游戏\n");
    Sleep(50);
    printf("\n\t\t修改角色信息可以访问博客下载修改器\n");
    Sleep(50);
    printf("\n\n");
    printf("\t\t请选择：");
    choice = getchar();
    Cleaner;
    return choice;
}

void game_introducation(char file_name[])
{//游戏玩法介绍
    char c;
    FILE * game_intro_file = NULL;

    game_intro_file = fopen(file_name, "r");

    system("cls");
    printf("\n\n");
    if(game_intro_file==NULL)
    {
        printf("\t\t找不到游戏介绍文件\n");
    }
    else
    {
        printf("\t\t");
        do
        {
            c = fgetc(game_intro_file);
            putchar(c);//输出内容
            Sleep(30);
            if(c=='\n')
            {
                printf("\t\t");
            }
        }while(c!=EOF);
        fclose(game_intro_file);
    }
}

char import_characters(const char file_name[], Character characters[])
{//导入角色
    FILE * chara_file = NULL;
    chara_file = fopen(file_name, "rb");
    if(chara_file == NULL)
    {
        printf("\n\n");
        printf("\t\t角色文件访问失败！\n");
        printf("\t\t请访问博客主页重新下载角色文件\n");
        printf("\t\t或选择访问博客主页下载角色修改器，自己写入角色信息\n");
        printf("\t\t");
        system("pause");
        return 'f';
    }
    else if(fread(characters, sizeof(Character), Character_Len, chara_file)!=Character_Len)
    {
        printf("\n\n");
        printf("\t\t角色文件访问失败！\n");
        printf("\t\t请访问博客主页重新下载角色文件\n");
        printf("\t\t或选择访问博客主页下载角色修改器，自己写入角色信息\n");
        fclose(chara_file);
        printf("\t\t");
        system("pause");
        return 'f';
    }
    else
    {
        fclose(chara_file);
        return 't';
    }
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

int get_number(const int start, const int stop)
{//获取数字
    int num;
    char c;
    do{
        printf("\t\t输入数值（%d-%d）：", start, stop);
        scanf("%d", &num);
        if(num<start||num>stop)
        {
            printf("\n\n");
            printf("\t\t请输入合理的数值！\n");
            printf("\n\n");
        }
    }while(num<start||num>stop);
    Cleaner;
    return num;
}

/**游戏主体*/

char init_characters(Character characters[])
{//初始化角色
    int i;//循环变量
    system("cls");
    printf("\n\n");
    printf("\t\t初始化角色……\n");
    Sleep(1000);
    for(i=0;i<Character_Len;i++)
    {
        characters[i].id = i+1;
        characters[i].degree = 0;
        characters[i].owner = 0;
    }
    system("cls");
    printf("\n\n");
    printf("\t\t角色初始化完成\n");
    Sleep(1000);
    return 't';
}

char init_player(Player players[], unsigned int player_num)
{//初始化玩家
    int i,j;

    system("cls");
    printf("\n\n");
    printf("\t\t初始化玩家……\n");
    Sleep(1000);
    for(i=0;i<Player_Len;i++)
    {
        players[i].id = i+1;//初始化编号
        players[i].position = 0;//初始化位置
        for(j=0;j<=Max_Character;j++)
        {//初始化拥有角色
            players[i].characters[j] = 0;
        }
        if(i<player_num)
        {//启用
            players[i].fund = Start_Money;//初始资金
            players[i].status = Active;//初始状态
            printf("\t\t输入%d号玩家昵称：", i+1);
            get_string(players[i].name, Name_Len);
        }
        else
        {//未启用
            players[i].fund = 0;//初始资金
            players[i].status = Unenabled;//初始状态
            strcpy(players[i].name, "未启用");
        }
    }
    system("cls");
    printf("\n\n");
    printf("\t\t初始化玩家完成\n");
    Sleep(1000);
    return 't';
}

void show_map(Character characters[], Player players[], const unsigned int player_num)
{//显示地图和玩家位置
    int i,j;
    system("cls");
    printf("\n\n");
    printf("\t\t角色编号 角色名字\t费用/奖励\t保护费/罚金\t角色等级 拥有者\t\t玩家位置\n\n");
    for(i=0;i<Character_Len;i++)
    {
        Sleep(50);
        if(characters[i].bonus==0&&characters[i].fine==0)
        {//普通角色
            printf("\t\t%4d\t %-10s\t费用:%-4d\t保护费:%-8d %-8d ",
                   characters[i].id,
                   characters[i].name,
                   characters[i].expenses,
                   characters[i].protection_fee,
                   characters[i].degree
                   );
            if(characters[i].owner==0)
            {
                printf("%-10s\t", "未售出");
            }
            else
            {
                printf("%-10s\t", players[characters[i].owner-1].name);
            }

        }
        else
        {//关卡
            printf("\t\t%4d\t %-10s\t奖励:%-4d\t罚金:%-10d\t\t\t\t",
                   characters[i].id,
                   characters[i].name,
                   characters[i].bonus,
                   characters[i].fine
                   );
        }
        for(j=0;j<player_num;j++)
        {//角色位置打印名称
            if(players[j].status==Active||players[j].status==Rest)
            {//是否有效
                if(players[j].position==i)
                {
                    printf("%s/", players[j].name);
                }
            }
        }
        printf("\n");
    }

}

int get_step(void)
{//掷骰子
    int luck_number;
    int step;
    printf("\t\t选择你的幸运数字！\n");
    luck_number = get_number(0, 9);
    srand(time(NULL)+luck_number);
    step = (rand() % 6) + 1;
    return step;
}

void buy_character(Player * pre_player, Character * pre_character)
{//购买角色
    char c;
    int i;
    char buy_flag;
    int new_degree;//购买的等级
    int buy_expenses;//购买花费

    printf("\t\t是否购买角色（%s）（y/n）\t费用：%d*等级\n", pre_character->name, pre_character->expenses);
    printf("\t\t");
    buy_flag = getchar();
    Cleaner;
    if(buy_flag=='y')
    {//购买
        printf("\t\t选择购买等级（1/2/3）\n");
        new_degree = get_number(1, 3);
        buy_expenses = pre_character->expenses * new_degree;
        if(pre_player->fund < buy_expenses)
        {//资金不足
            printf("\t\t你的可用资金不足\n");
        }
        else if(pre_player->characters[0]==Max_Character)
        {//角色已满
            printf("\t\t你最多只能拥有%d个角色\n", Max_Character);
        }
        else
        {//购买
            pre_player->fund -= buy_expenses;//资金修改
            pre_player->characters[0] += 1;//玩家角色添加
            for(i=1;i<=Max_Character;i++)
            {//玩家拥有角色数组修改
                if(pre_player->characters[i]==0)
                {//空位
                    pre_player->characters[i] = pre_character->id;
                    break;
                }
            }
            pre_character->degree = new_degree;//角色等级修改
            pre_character->owner = pre_player->id;//角色拥有者修改
            printf("\t\t购买成功\n");
        }
    }
}

void sell_character(Player * pre_player, Character * pre_character)
{//出售角色
    int i;
    char c;
    char sell_flag;//出售选择
    int sell_money;//售出价

    sell_money = (pre_character->expenses * pre_character->degree)/2;
    printf("\t\t是否半价”(费用*等级)/2“出售角色（%s）（y/n）\t将获得资金：%d\n", pre_character->name, sell_money);
    printf("\t\t");
    sell_flag = getchar();
    Cleaner;
    if(sell_flag=='y')
    {//出售角色
        pre_player->fund += sell_money;//获得资金
        for(i=1;i<=Max_Character;i++)
        {//查找玩家拥有该角色的位置
            if(pre_player->characters[i]==pre_character->id)
            {
                pre_player->characters[i] = 0;
                pre_player->characters[0] -= 1;//角色总数减一
                pre_character->owner = 0;//角色拥有者修改
                pre_character->degree = 0;//角色等级修改
                printf("\t\t出售成功\n");
                break;
            }
        }
    }
}

void update_character(Player * pre_player, Character * pre_character)
{//升级角色
    char c;
    char update_flag;//升级选择
    int change_degree;//修改的等级
    int update_expenses;//升级费用

    printf("\t\t是否升级当前角色（%s）（y/n）\t当前等级：%d\n", pre_character->name, pre_character->degree);
    printf("\t\t");
    update_flag = getchar();
    Cleaner;
    if(update_flag=='y')
    {
        if(pre_character->degree==3)
        {//三级角色
            printf("\t\t当前角色已满级（三级）\n");
        }
        else if(pre_character->degree==2)
        {//二级角色
            if(pre_player->fund < pre_character->expenses)
            {//资金不足
                printf("\t\t你的资金不够升级该角色\n");
            }
            else
            {
                pre_player->fund -= pre_character->expenses;
                pre_character->degree += 1;
                printf("\t\t升级成功\n");
            }
        }
        else
        {//一级角色
            printf("\t\t选择升级后等级（2/3）：\n");
            change_degree = get_number(2, 3);
            update_expenses = pre_character->expenses * (change_degree-1);
            if(pre_player->fund < update_expenses)
            {//资金不足
                printf("\t\t你的资金不足升级该角色\n");
            }
            else
            {
                pre_player->fund -= update_expenses;
                pre_character->degree = change_degree;
                printf("\t\t升级成功\n");
            }
        }
    }
}
char pay_protection(Player * pre_player, Player players[], Character characters[])
{//缴纳保护费
    int i;
    int protection;//保护费
    Character * pre_character;//当前角色

    pre_character = &characters[pre_player->position];
    protection = pre_character->protection_fee * pre_character->degree;
    printf("\t\t你将向%s的拥有者%s支付保护费：%d\n",
           pre_character->name,
           players[pre_character->owner-1].name,
           protection
           );
    while(pre_player->fund < protection)
    {//资金不足，出售角色
        if(pre_player->characters[0]==0)
        {
            printf("\t\t你的总资金不足，且没有可售出的角色，你已破产，银行会支付你的剩余账单\n");
            printf("\t\t往后余生一定暴富！come on\n");
            players[pre_character->owner-1].fund += protection;
            pre_player->fund = 0;
            pre_player->status = Broke;
            break;
        }
        else
        {//出售角色补充资金
            printf("\t\t你现有资金不足，需出售角色以获得足够的资金\n");
            for(i=1;i<=Max_Character;i++)
            {//出售角色
                if(pre_player->characters[i]!=0)
                {//询问出售角色
                    sell_character(pre_player,&characters[pre_player->characters[i]-1]);
                    if(pre_player->characters[0]==0)
                    {//角色售完
                        printf("\t\t你售出了你所有的角色！\n");
                        break;
                    }
                }
            }
        }
    }
    if(pre_player->status!=Broke)
    {//未破产
        pre_player->fund -= protection;
        players[pre_character->owner-1].fund += protection;
        printf("\t\t你当前拥有资金：%d\n", pre_player->fund);
        return 't';
    }
    else
    {//破产返回
        return 'f';
    }
}

char player_turn(Player * pre_player, Player players[], Character characters[])
{//修改玩家状态
    int i;
    int step;//行进长度
    int fine;//罚金

    if(pre_player->status==Broke)
    {//已破产玩家
        return 't';//返回继续游戏
    }
    else if(pre_player->status==Rest)
    {//休息一轮的玩家
        printf("\n\n");
        printf("\t\t玩家：%s本轮不参与\n",pre_player->name);
        printf("\t\t你当前拥有资金：%d\n", pre_player->fund);
        pre_player->status = Active;//下一轮可以参与
        return 't';//返回继续游戏
    }
    //活跃玩家
    printf("\n\n");
    printf("\t\t当前玩家：%s\t可用资金：%d\n\n", pre_player->name, pre_player->fund);
    step = get_step();
    pre_player->position += step;//玩家行进
    pre_player->position %= Character_Len;//地图循环
    printf("\n\n");
    printf("\t\t骰子结果（前进长度）：%d\n", step);
    if(characters[pre_player->position].owner==(pre_player->id))
    {//当前位置属于该玩家
        //升级角色
        update_character(pre_player, &characters[pre_player->position]);
        //售卖角色
        sell_character(pre_player, &characters[pre_player->position]);
        printf("\t\t你当前拥有资金：%d\n", pre_player->fund);
    }
    else
    {//不属于该玩家
        if(characters[pre_player->position].bonus!=0)
        {//获得奖励
            pre_player->fund += characters[pre_player->position].bonus;
            printf("\t\t你获得了%d的奖励\n", characters[pre_player->position].bonus);
            printf("\t\t你当前拥有资金：%d\n", pre_player->fund);
            if(characters[pre_player->position].bonus==300)
            {//下一轮休息
                pre_player->status = Rest;
                printf("\t\t你在下一轮休息，不能行进和操作\n");
            }
        }
        else if(characters[pre_player->position].fine!=0)
        {//缴纳罚金
            fine = characters[pre_player->position].fine;

            printf("\t\t你将向%s支付罚金：%d\n", characters[pre_player->position].name, fine);
            while(pre_player->fund < fine)
            {//资金不足，出售角色
                if(pre_player->characters[0]==0)
                {//无角色出售
                    printf("\t\t你的资金不足，你已破产，银行会支付你的剩余账单\n");
                    printf("\t\t下次一定会暴富！come on\n");
                    pre_player->fund = 0;
                    pre_player->status = Broke;
                    break;
                }
                else
                {//出售角色补充资金
                    printf("\t\t你现有资金不足，需出售角色以获得足够的资金\n");
                    for(i=1;i<=Max_Character;i++)
                    {//出售角色
                        if(pre_player->characters[i]!=0)
                        {//询问出售角色
                            sell_character(pre_player,&characters[pre_player->characters[i]-1]);
                            if(pre_player->characters[0]==0)
                            {//角色售完
                                break;
                            }
                        }
                    }
                }
            }
            if(pre_player->status!=Broke)
            {//未破产
                pre_player->fund -= fine;
                printf("\t\t你当前拥有资金：%d\n", pre_player->fund);
            }
            else
            {//破产
                return 'f';
            }
        }
        else if(characters[pre_player->position].owner==0)
        {//未售出
            //购买
            buy_character(pre_player, &characters[pre_player->position]);
        }
        else
        {//属于其他玩家
            if(pay_protection(pre_player, players, characters)=='f')
            {//破产
                return 'f';
            }
        }
    }
    return 't';
}

void show_winner(Player players[], const unsigned int player_num)
{//排行榜
    int i, j;
    Player * p_players[player_num+1];//0号用于交换
    for(i=0;i<player_num;i++)
    {//玩家数组指针
        p_players[i+1] = &players[i];
    }
    for(i=1;i<player_num;i++)
    {//排序
        for(j=1;j<player_num;j++)
        {
            if(p_players[j]->fund < p_players[j+1]->fund)
            {//交换
                p_players[0] = p_players[j];
                p_players[j] = p_players[j+1];
                p_players[j+1] = p_players[0];
            }
        }
    }
    system("cls");
    printf("\n\n");
    printf("\t\tthanks for playing!!!\n");
    printf("\t\t本次游戏结束，富豪排行榜如下：\n\n");
    printf("\t\t玩家昵称\t现有资金\t现有角色数\t玩家状态\n\n");
    for(i=1;i<=player_num;i++)
    {
        printf("\t\t%-10s\t%-10d\t%-10d\t",
               p_players[i]->name,
               p_players[i]->fund,
               p_players[i]->characters[0]
               );
        if(p_players[i]->status!=Broke)
        {//未破产
            printf("活跃\n");
        }
        else
        {
            printf("破产\n");
        }
    }
}
void run_game(Character characters[], Player players[], const unsigned int player_num)
{//运行游戏
    char c;
    int count_players;//现有玩家
    int turn;//玩家顺序
    char exit_flag;//退出标签

    count_players = player_num;//现存玩家初始化
    turn = 0;//由一号玩家开始掷骰子
    while(count_players>1)
    {//游戏循环
        show_map(characters, players, player_num);//清屏输出map
        if(player_turn(&players[turn], players, characters)=='f')
        {//新玩家破产
            count_players--;
        }
        if(count_players>1)
        {
            printf("\n\n");
            printf("\t\t回车开始下一位玩家，输入x结束游戏并显示排行榜\n");
            printf("\t\t");
            exit_flag = getchar();
            if(exit_flag!='\n')
            {
                Cleaner;
            }
            if(exit_flag=='x')
            {
                break;
            }
        }
        turn++;
        turn %= player_num;
    }
    if(count_players == 1)
    {
        printf("\t\t现在剩一位玩家，游戏结束。任意键显示排行榜\n");
        system("pause");
    }
    show_winner(players, player_num);//排行榜
}


/**查看角色信息部分*/

void show_character(const Character * sh_character)
{//打印角色信息
    system("cls");
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

void search_character(Character characters[])
{//查找角色
    int i;//循环变量
    char c;//清除缓存变量
    char search_name[Name_Len];//查询角色名称
    char refind_choice;//重新查找选择

    do{
        system("cls");
        printf("\n\n");
        printf("\t\t输入角色的名字：");
        get_string(search_name, Name_Len);
        i = 0;
        while(i<Character_Len)
        {
            if(strcmp(search_name, characters[i].name)==0)
            {
                system("cls");
                show_character(&characters[i]);
                break;
            }
            else if(i==Character_Len-1)
            {
                printf("\t\t没有找到你想找的角色\n");
                break;
            }
            else
            {
                i++;
            }
        }
        printf("\n\n");
        printf("\t\t继续查看（y/n）:");
        refind_choice = getchar();
        Cleaner;
    }while(refind_choice=='y');
}

#endif // GAME_FUNCTIONS_H_INCLUDED
