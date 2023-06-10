#include <stdio.h>
#include <stdlib.h>

#include "editer_functions.h"

int main()
{
    char menu_choice;//菜单选择
    char import_flag;//导入判断标签
    char edite_flag;//可修改标签
    char search_flag;//查找标签
    char rewrite_flag;//重写成功标签
    char update_flag;//更新文件标签
    char file_name[] = "characters_information.txt";
    Character characters[Character_Len];//角色数组


    import_flag = import_character(file_name, characters);
    if(import_flag=='t')
    {
        edite_flag = 't';
    }
    else
    {
        edite_flag = 'f';
        printf("\n\n");
        printf("\t\t导入角色文件失败，请检查文件或重新访问博客下载角色文件\n");
        Sleep(1200);
    }
    do{//菜单功能循环

        menu_choice = show_menu();
        switch(menu_choice)
        {
        case '1'://修改已有角色信息
            if(edite_flag=='f')
            {
                printf("\t\t你现在还不能修改成员（访问角色失败），可以尝试重写\n");
            }
            else
            {
                search_flag = search_character(characters);
                if(search_flag=='f')
                {
                    printf("\t\t未找到\n");
                }
            }
            break;

        case '2'://全部重写
            rewrite_flag = rewrite(characters);
            if(rewrite_flag=='f')
            {
                printf("\t\t重写失败！");
            }
            else
            {
                edite_flag = 't';
            }

            break;

        case '3'://更新角色文件
            update_flag = update_file(file_name, characters);
            if(update_flag=='t')
            {
                printf("\t\t文件更新成功\n");
            }
            else
            {
                printf("\t\t更新失败，请检查文件\n");
            }
            break;

        case '0':
            printf("\t\t谢谢支持！！！\n");
            exit(0);
            break;
        }
        Sleep(1200);
        system("cls");
    }while(menu_choice!='0');
    return 0;
}
