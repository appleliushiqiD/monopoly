#ifndef EDITER_FUNCTIONS_H_INCLUDED
#define EDITER_FUNCTIONS_H_INCLUDED

#include <stdio.h>//stdin����
#include <stdlib.h>
#include <string.h>//�ַ�������
#include <ctype.h>//�ַ��ж�
#include <windows.h>//����������
#include "character_player.h"

#define Character_Len 30//��ɫ����
#define Cleaner while((c=getchar())!=EOF&&c!='\n')//��ջ�����

//��������
char show_menu(void);//��ʾ�˵�
char import_character(char file_name[], Character characters[]);//�����ɫ��Ϣ
void show_character(const Character * sh_character);//��ӡ������ɫ��Ϣ
void get_string(char str[], const unsigned int str_len);//��ȡ�ַ���
char search_character(Character characters[]);//���ҽ�ɫ
void change_character(Character * ch_character);//�޸Ľ�ɫ��Ϣ
char rewrite(Character characters[]);//ȫ����д
char update_file(char file_name[], Character characters[]);//�����ļ�

//��������
char show_menu(void)
{//��ʾ�˵�
    char c;
    char choice;

    system("cls");
    printf("\n\n");
    printf("\t\t1. ��ѯ���н�ɫ��Ϣ\n");
    Sleep(50);
    printf("\t\t2. ȫ����д\n");
    Sleep(50);
    printf("\t\t3. ���½�ɫ�ļ�\n");
    Sleep(50);
    printf("\t\t0. �˳�\n");
    Sleep(50);
    printf("\n\t\t�޸����ݺ��ȫ����д����ѡ�񡰸��½�ɫ�ļ��������򲻻��޸�ԭ�н�ɫ�ļ�\n");
    Sleep(50);
    printf("\n\n");
    printf("\t\t��ѡ��");
    choice = getchar();
    Cleaner;//������뻺��
    return choice;
}

char import_character(char file_name[], Character characters[])
{//�����ɫ��Ϣ
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
{//��ӡ��ɫ��Ϣ
    printf("\n\n");
    printf("\t\t��ɫ��Ϣ��\n\n\n");
    Sleep(50);
    printf("\t\t��ţ�%d\n\n", sh_character->id);
    Sleep(50);
    printf("\t\t�۸�%4d * �ȼ�\t�����ѣ�%4d * �ȼ�\n\n", sh_character->expenses, sh_character->protection_fee);
    Sleep(50);
    printf("\t\t������%4d\t\t����%4d\n\n", sh_character->bonus, sh_character->fine);
    Sleep(50);
    printf("\t\t���֣�%s\t\t��飺%s\n\n", sh_character->name, sh_character->introduction);
    Sleep(50);
    printf("\t\t������%s\n", sh_character->description);
    Sleep(50);
    printf("\n\n");
}

void get_string(char str[], const unsigned int str_len)
{//��ȡ�ַ���
    char c;//���������
    do{
        fgets(str, str_len, stdin);
        if(str[0] == '\n')//����س�
        {
            printf("\t\t������󣨲�Ҫ���뻻�з���\n");
            printf("\n\t\t���������룺");
        }
        else if(str[strlen(str)-1]=='\n')//ĩβ�໻�з�
        {
            str[strlen(str)-1] = '\0';
        }
        else
        {
            Cleaner;//��ջ���
        }
    }while(str[0] == '\n');
}

char search_character(Character characters[])
{//���ҽ�ɫ
    int i;//ѭ������
    char c;//����������
    char change_name[Name_Len];//��ѯ��ɫ����
    char change_flag;//�޸�ѡ��

    system("cls");
    printf("\n\n");
    printf("\t\t������Ҫ�޸Ľ�ɫ�����֣�");
    get_string(change_name, Name_Len);
    i = 0;
    while(i<Character_Len)
    {
        if(strcmp(change_name, characters[i].name)==0)
        {
            show_character(&characters[i]);
            printf("\t\t�Ƿ��޸ģ���y/n����");
            change_flag = getchar();
            Cleaner;
            if(change_flag=='y')
            {
                change_character(&characters[i]);
                return 't';
            }
            else
            {
                printf("\t\tû�н����޸�\n");
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
{//�޸Ľ�ɫ��Ϣ
    char c;//���������

    ch_character->degree = 0;
    ch_character->owner = 0;
    printf("\t\t�۸񡢹�·�ѡ������������Ϊ��Ȼ��\n");
    printf("\t\t����Ϊ�ַ�����\n\n\n");
    printf("\t\t1. ����۸�");
    scanf("%d",&ch_character->expenses);
    Cleaner;
    printf("\t\t2. �����·�ѣ�");
    scanf("%d",&ch_character->protection_fee);
    Cleaner;
    printf("\t\t3. ���븣����");
    scanf("%d",&ch_character->bonus);
    Cleaner;
    printf("\t\t4. ���뷣��");
    scanf("%d",&ch_character->fine);
    Cleaner;
    printf("\t\t5. �������֣�������%d�����֣���", (Name_Len-1)/2);
    get_string(ch_character->name, Name_Len);
    printf("\t\t6. �����飨������%d�����֣���", (Intro_Len-1)/2);
    get_string(ch_character->introduction, Intro_Len);
    printf("\t\t7. ����������������%d�����֣���", (Description_Len-1)/2);
    get_string(ch_character->description, Description_Len);
    printf("\n\n");
    printf("\t\t���޸ģ�");
}

char rewrite(Character characters[])
{//ȫ����д
    int i;//ѭ������
    for(i=0;i<Character_Len;i++)
    {
        system("cls");
        printf("\n\n");
        printf("\t\t��%dλ\n\n", i+1);
        characters[i].id = i+1;//�Զ������
        change_character(&characters[i]);
    }
    system("cls");
    printf("\n\n");
    printf("\t\tд����ɣ��뼰ʱ�����ļ�������\n");
    return 't';
}

char update_file(char file_name[], Character characters[])
{//�����ļ�
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
        printf("\t\t�������\n");
        fclose(chara_file);
        return 't';
    }
}

#endif // EDITER_FUNCTIONS_H_INCLUDED
