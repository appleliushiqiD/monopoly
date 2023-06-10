#include <stdio.h>
#include <stdlib.h>

#include "game_functions.h"

int main()
{
    int pre_bgm;//随机播放音乐标签
    int player_num;//玩家数量
    char menu_choice;//菜单选择
    char import_flag;//导入标签

    char open_music[100] = "open sounds/bgm0.mp3 ";//音乐文件名
    char chara_file[] = "characters_information.txt";//角色文件名
    char game_intro_file[] = "game_introduction.txt";//游戏介绍文件名
    Character characters[Character_Len];//角色数组
    Player players[Player_Len];//玩家数组

    //修改背景色与字体色
    system("color 90");
    //播放BGM
    srand(time(NULL));
    pre_bgm = rand() % BGM_num;
    open_music[strlen(open_music)-6] = pre_bgm + 48;//随机音乐
    strcat(open_music, "alias BGM");
    if(mciSendString(open_music, NULL, 0, NULL)!=0)
    {//打开文件失败
        printf("\n\n");
        printf("\t\twrong!!!(no music file)\n");
        Sleep(1200);
    }
    else
    {//打开文件
        music('r');
    }

    import_flag = import_characters(chara_file, characters);
    if(import_flag=='f')
    {
        exit(0);
    }

    do{//游戏循环
        menu_choice = show_menu();
        switch(menu_choice)
        {
        case '1'://开始新游戏
            system("cls");
            printf("\n\n");
            //获取玩家数
            printf("\t\thow many players?\n");
            player_num = get_number(2, Player_Len);
            //初始化并开始游戏
            init_characters(characters);
            init_player(players, player_num);
            run_game(characters, players, player_num);
            printf("\n\n");
            printf("\t\t");
            system("pause");
            break;
        case '2':
            game_introducation(game_intro_file);
            printf("\n\n");
            printf("\t\t");
            system("pause");
            break;
        case '3'://查看角色信息
            search_character(characters);
            break;
        case '0'://退出游戏
            printf("\t\tthanks for playing!\n");
            music('c');
            break;
        default:
            printf("\t\twrong!!!");
            Sleep(1200);
        }
    }while(menu_choice!='0');

    return 0;
}
