#include <stdio.h>
#include <stdlib.h>

#include "editer_functions.h"

int main()
{
    char menu_choice;//�˵�ѡ��
    char import_flag;//�����жϱ�ǩ
    char edite_flag;//���޸ı�ǩ
    char search_flag;//���ұ�ǩ
    char rewrite_flag;//��д�ɹ���ǩ
    char update_flag;//�����ļ���ǩ
    char file_name[] = "characters_information.txt";
    Character characters[Character_Len];//��ɫ����


    import_flag = import_character(file_name, characters);
    if(import_flag=='t')
    {
        edite_flag = 't';
    }
    else
    {
        edite_flag = 'f';
        printf("\n\n");
        printf("\t\t�����ɫ�ļ�ʧ�ܣ������ļ������·��ʲ������ؽ�ɫ�ļ�\n");
        Sleep(1200);
    }
    do{//�˵�����ѭ��

        menu_choice = show_menu();
        switch(menu_choice)
        {
        case '1'://�޸����н�ɫ��Ϣ
            if(edite_flag=='f')
            {
                printf("\t\t�����ڻ������޸ĳ�Ա�����ʽ�ɫʧ�ܣ������Գ�����д\n");
            }
            else
            {
                search_flag = search_character(characters);
                if(search_flag=='f')
                {
                    printf("\t\tδ�ҵ�\n");
                }
            }
            break;

        case '2'://ȫ����д
            rewrite_flag = rewrite(characters);
            if(rewrite_flag=='f')
            {
                printf("\t\t��дʧ�ܣ�");
            }
            else
            {
                edite_flag = 't';
            }

            break;

        case '3'://���½�ɫ�ļ�
            update_flag = update_file(file_name, characters);
            if(update_flag=='t')
            {
                printf("\t\t�ļ����³ɹ�\n");
            }
            else
            {
                printf("\t\t����ʧ�ܣ������ļ�\n");
            }
            break;

        case '0':
            printf("\t\tлл֧�֣�����\n");
            exit(0);
            break;
        }
        Sleep(1200);
        system("cls");
    }while(menu_choice!='0');
    return 0;
}
