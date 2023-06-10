#ifndef GAME_FUNCTIONS_H_INCLUDED
#define GAME_FUNCTIONS_H_INCLUDED

#include <stdio.h>//stdin����
#include <stdlib.h>//�����
#include <string.h>//�ַ�������
#include <ctype.h>//�ַ��ж�
#include <time.h>//ʱ������
#include <windows.h>//���������ߡ���ͣ
#include <mmsystem.h>//����
#include "character_player.h"

//�궨��
#define BGM_num 5//BGM����
#define Character_Len 30//��ɫ����
#define Player_Len 6//��������
#define Start_Money 20000//�����ʽ�
#define Cleaner while((c=getchar())!=EOF&&c!='\n')//��ջ�����
//״̬
#define Unenabled 0//δ����
#define Active 1//��Ծ
#define Broke 2//�Ʋ�
#define Rest 3//��Ϣ

//��������
/**�˵������*/
char music(char cammand);//��������

char show_menu(void);//��ӡ���ܲ˵�
void game_introducation(char file_name[]);//��Ϸ�淨����
char import_characters(const char file_name[], Character characters[]);//�����ɫ
void get_string(char str[], const unsigned int str_len);//��ȡ�ַ���
int get_number(const int start, const int stop);//��ȡ����
/**��Ϸ����*/
char init_characters(Character characters[]);//��ʼ����ɫ
char init_player(Player players[], unsigned int player_num);//��ʼ�����
    //��Ϸ����
void show_map(Character characters[], Player players[], const unsigned int player_num);//��ʾ��ͼ�����λ��
        //��ɫ��Ϣ�仯
int get_step(void);//������
void buy_character(Player * pre_player, Character * pre_character);//�����ɫ
void sell_character(Player * pre_player, Character * pre_character);//���۽�ɫ
void update_character(Player * pre_player, Character * pre_character);//������ɫ
char pay_protection(Player * pre_player, Player players[], Character characters[]);//���ɱ�����
    //��Ϸѭ��
char player_turn(Player * pre_player, Player players[], Character characters[]);//�޸����״̬
void show_winner(Player players[], const unsigned int player_num);//���а�
void run_game(Character characters[], Player players[], const unsigned int player_num);//������Ϸ

/**�鿴��ɫ*/
void show_character(const Character * sh_character);//��ӡ��ɫ��Ϣ
void search_character(Character characters[]);//���ҽ�ɫ


//��������

/**�˵����������*/

char music(char cammand)
{//��������
    switch(cammand)
    {
    case 'p'://��������
        if(mciSendString("play BGM", NULL, 0, NULL))
        {
            return 'f';
        }
        else
        {
            return 't';
        }
        break;
    case 'r'://�ظ�����
        if(mciSendString("play BGM repeat", NULL, 0, NULL))
        {
            return 'f';
        }
        else
        {
            return 't';
        }
        break;
    case 's'://��ͣ����
        if(mciSendString("stop BGM", NULL, 0, NULL))
        {
            return 'f';
        }
        else
        {
            return 't';
        }
        break;
    case 'c'://�ر��ļ�
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
{//��ӡ���ܲ˵�
    char c;
    char choice;

    system("cls");
    printf("\n\n");
    printf("\t\tWelcome to play!\n\n");
    Sleep(50);
    printf("\t\t1. ��ʼ����Ϸ\n");
    Sleep(50);
    printf("\t\t2. �鿴��Ϸ�淨\n");
    Sleep(50);
    printf("\t\t3. �鿴��ɫ���\n");
    Sleep(50);
    printf("\t\t0. �˳���Ϸ\n");
    Sleep(50);
    printf("\n\t\t�޸Ľ�ɫ��Ϣ���Է��ʲ��������޸���\n");
    Sleep(50);
    printf("\n\n");
    printf("\t\t��ѡ��");
    choice = getchar();
    Cleaner;
    return choice;
}

void game_introducation(char file_name[])
{//��Ϸ�淨����
    char c;
    FILE * game_intro_file = NULL;

    game_intro_file = fopen(file_name, "r");

    system("cls");
    printf("\n\n");
    if(game_intro_file==NULL)
    {
        printf("\t\t�Ҳ�����Ϸ�����ļ�\n");
    }
    else
    {
        printf("\t\t");
        do
        {
            c = fgetc(game_intro_file);
            putchar(c);//�������
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
{//�����ɫ
    FILE * chara_file = NULL;
    chara_file = fopen(file_name, "rb");
    if(chara_file == NULL)
    {
        printf("\n\n");
        printf("\t\t��ɫ�ļ�����ʧ�ܣ�\n");
        printf("\t\t����ʲ�����ҳ�������ؽ�ɫ�ļ�\n");
        printf("\t\t��ѡ����ʲ�����ҳ���ؽ�ɫ�޸������Լ�д���ɫ��Ϣ\n");
        printf("\t\t");
        system("pause");
        return 'f';
    }
    else if(fread(characters, sizeof(Character), Character_Len, chara_file)!=Character_Len)
    {
        printf("\n\n");
        printf("\t\t��ɫ�ļ�����ʧ�ܣ�\n");
        printf("\t\t����ʲ�����ҳ�������ؽ�ɫ�ļ�\n");
        printf("\t\t��ѡ����ʲ�����ҳ���ؽ�ɫ�޸������Լ�д���ɫ��Ϣ\n");
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

int get_number(const int start, const int stop)
{//��ȡ����
    int num;
    char c;
    do{
        printf("\t\t������ֵ��%d-%d����", start, stop);
        scanf("%d", &num);
        if(num<start||num>stop)
        {
            printf("\n\n");
            printf("\t\t������������ֵ��\n");
            printf("\n\n");
        }
    }while(num<start||num>stop);
    Cleaner;
    return num;
}

/**��Ϸ����*/

char init_characters(Character characters[])
{//��ʼ����ɫ
    int i;//ѭ������
    system("cls");
    printf("\n\n");
    printf("\t\t��ʼ����ɫ����\n");
    Sleep(1000);
    for(i=0;i<Character_Len;i++)
    {
        characters[i].id = i+1;
        characters[i].degree = 0;
        characters[i].owner = 0;
    }
    system("cls");
    printf("\n\n");
    printf("\t\t��ɫ��ʼ�����\n");
    Sleep(1000);
    return 't';
}

char init_player(Player players[], unsigned int player_num)
{//��ʼ�����
    int i,j;

    system("cls");
    printf("\n\n");
    printf("\t\t��ʼ����ҡ���\n");
    Sleep(1000);
    for(i=0;i<Player_Len;i++)
    {
        players[i].id = i+1;//��ʼ�����
        players[i].position = 0;//��ʼ��λ��
        for(j=0;j<=Max_Character;j++)
        {//��ʼ��ӵ�н�ɫ
            players[i].characters[j] = 0;
        }
        if(i<player_num)
        {//����
            players[i].fund = Start_Money;//��ʼ�ʽ�
            players[i].status = Active;//��ʼ״̬
            printf("\t\t����%d������ǳƣ�", i+1);
            get_string(players[i].name, Name_Len);
        }
        else
        {//δ����
            players[i].fund = 0;//��ʼ�ʽ�
            players[i].status = Unenabled;//��ʼ״̬
            strcpy(players[i].name, "δ����");
        }
    }
    system("cls");
    printf("\n\n");
    printf("\t\t��ʼ��������\n");
    Sleep(1000);
    return 't';
}

void show_map(Character characters[], Player players[], const unsigned int player_num)
{//��ʾ��ͼ�����λ��
    int i,j;
    system("cls");
    printf("\n\n");
    printf("\t\t��ɫ��� ��ɫ����\t����/����\t������/����\t��ɫ�ȼ� ӵ����\t\t���λ��\n\n");
    for(i=0;i<Character_Len;i++)
    {
        Sleep(50);
        if(characters[i].bonus==0&&characters[i].fine==0)
        {//��ͨ��ɫ
            printf("\t\t%4d\t %-10s\t����:%-4d\t������:%-8d %-8d ",
                   characters[i].id,
                   characters[i].name,
                   characters[i].expenses,
                   characters[i].protection_fee,
                   characters[i].degree
                   );
            if(characters[i].owner==0)
            {
                printf("%-10s\t", "δ�۳�");
            }
            else
            {
                printf("%-10s\t", players[characters[i].owner-1].name);
            }

        }
        else
        {//�ؿ�
            printf("\t\t%4d\t %-10s\t����:%-4d\t����:%-10d\t\t\t\t",
                   characters[i].id,
                   characters[i].name,
                   characters[i].bonus,
                   characters[i].fine
                   );
        }
        for(j=0;j<player_num;j++)
        {//��ɫλ�ô�ӡ����
            if(players[j].status==Active||players[j].status==Rest)
            {//�Ƿ���Ч
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
{//������
    int luck_number;
    int step;
    printf("\t\tѡ������������֣�\n");
    luck_number = get_number(0, 9);
    srand(time(NULL)+luck_number);
    step = (rand() % 6) + 1;
    return step;
}

void buy_character(Player * pre_player, Character * pre_character)
{//�����ɫ
    char c;
    int i;
    char buy_flag;
    int new_degree;//����ĵȼ�
    int buy_expenses;//���򻨷�

    printf("\t\t�Ƿ����ɫ��%s����y/n��\t���ã�%d*�ȼ�\n", pre_character->name, pre_character->expenses);
    printf("\t\t");
    buy_flag = getchar();
    Cleaner;
    if(buy_flag=='y')
    {//����
        printf("\t\tѡ����ȼ���1/2/3��\n");
        new_degree = get_number(1, 3);
        buy_expenses = pre_character->expenses * new_degree;
        if(pre_player->fund < buy_expenses)
        {//�ʽ���
            printf("\t\t��Ŀ����ʽ���\n");
        }
        else if(pre_player->characters[0]==Max_Character)
        {//��ɫ����
            printf("\t\t�����ֻ��ӵ��%d����ɫ\n", Max_Character);
        }
        else
        {//����
            pre_player->fund -= buy_expenses;//�ʽ��޸�
            pre_player->characters[0] += 1;//��ҽ�ɫ���
            for(i=1;i<=Max_Character;i++)
            {//���ӵ�н�ɫ�����޸�
                if(pre_player->characters[i]==0)
                {//��λ
                    pre_player->characters[i] = pre_character->id;
                    break;
                }
            }
            pre_character->degree = new_degree;//��ɫ�ȼ��޸�
            pre_character->owner = pre_player->id;//��ɫӵ�����޸�
            printf("\t\t����ɹ�\n");
        }
    }
}

void sell_character(Player * pre_player, Character * pre_character)
{//���۽�ɫ
    int i;
    char c;
    char sell_flag;//����ѡ��
    int sell_money;//�۳���

    sell_money = (pre_character->expenses * pre_character->degree)/2;
    printf("\t\t�Ƿ��ۡ�(����*�ȼ�)/2�����۽�ɫ��%s����y/n��\t������ʽ�%d\n", pre_character->name, sell_money);
    printf("\t\t");
    sell_flag = getchar();
    Cleaner;
    if(sell_flag=='y')
    {//���۽�ɫ
        pre_player->fund += sell_money;//����ʽ�
        for(i=1;i<=Max_Character;i++)
        {//�������ӵ�иý�ɫ��λ��
            if(pre_player->characters[i]==pre_character->id)
            {
                pre_player->characters[i] = 0;
                pre_player->characters[0] -= 1;//��ɫ������һ
                pre_character->owner = 0;//��ɫӵ�����޸�
                pre_character->degree = 0;//��ɫ�ȼ��޸�
                printf("\t\t���۳ɹ�\n");
                break;
            }
        }
    }
}

void update_character(Player * pre_player, Character * pre_character)
{//������ɫ
    char c;
    char update_flag;//����ѡ��
    int change_degree;//�޸ĵĵȼ�
    int update_expenses;//��������

    printf("\t\t�Ƿ�������ǰ��ɫ��%s����y/n��\t��ǰ�ȼ���%d\n", pre_character->name, pre_character->degree);
    printf("\t\t");
    update_flag = getchar();
    Cleaner;
    if(update_flag=='y')
    {
        if(pre_character->degree==3)
        {//������ɫ
            printf("\t\t��ǰ��ɫ��������������\n");
        }
        else if(pre_character->degree==2)
        {//������ɫ
            if(pre_player->fund < pre_character->expenses)
            {//�ʽ���
                printf("\t\t����ʽ𲻹������ý�ɫ\n");
            }
            else
            {
                pre_player->fund -= pre_character->expenses;
                pre_character->degree += 1;
                printf("\t\t�����ɹ�\n");
            }
        }
        else
        {//һ����ɫ
            printf("\t\tѡ��������ȼ���2/3����\n");
            change_degree = get_number(2, 3);
            update_expenses = pre_character->expenses * (change_degree-1);
            if(pre_player->fund < update_expenses)
            {//�ʽ���
                printf("\t\t����ʽ��������ý�ɫ\n");
            }
            else
            {
                pre_player->fund -= update_expenses;
                pre_character->degree = change_degree;
                printf("\t\t�����ɹ�\n");
            }
        }
    }
}
char pay_protection(Player * pre_player, Player players[], Character characters[])
{//���ɱ�����
    int i;
    int protection;//������
    Character * pre_character;//��ǰ��ɫ

    pre_character = &characters[pre_player->position];
    protection = pre_character->protection_fee * pre_character->degree;
    printf("\t\t�㽫��%s��ӵ����%s֧�������ѣ�%d\n",
           pre_character->name,
           players[pre_character->owner-1].name,
           protection
           );
    while(pre_player->fund < protection)
    {//�ʽ��㣬���۽�ɫ
        if(pre_player->characters[0]==0)
        {
            printf("\t\t������ʽ��㣬��û�п��۳��Ľ�ɫ�������Ʋ������л�֧�����ʣ���˵�\n");
            printf("\t\t��������һ��������come on\n");
            players[pre_character->owner-1].fund += protection;
            pre_player->fund = 0;
            pre_player->status = Broke;
            break;
        }
        else
        {//���۽�ɫ�����ʽ�
            printf("\t\t�������ʽ��㣬����۽�ɫ�Ի���㹻���ʽ�\n");
            for(i=1;i<=Max_Character;i++)
            {//���۽�ɫ
                if(pre_player->characters[i]!=0)
                {//ѯ�ʳ��۽�ɫ
                    sell_character(pre_player,&characters[pre_player->characters[i]-1]);
                    if(pre_player->characters[0]==0)
                    {//��ɫ����
                        printf("\t\t���۳��������еĽ�ɫ��\n");
                        break;
                    }
                }
            }
        }
    }
    if(pre_player->status!=Broke)
    {//δ�Ʋ�
        pre_player->fund -= protection;
        players[pre_character->owner-1].fund += protection;
        printf("\t\t�㵱ǰӵ���ʽ�%d\n", pre_player->fund);
        return 't';
    }
    else
    {//�Ʋ�����
        return 'f';
    }
}

char player_turn(Player * pre_player, Player players[], Character characters[])
{//�޸����״̬
    int i;
    int step;//�н�����
    int fine;//����

    if(pre_player->status==Broke)
    {//���Ʋ����
        return 't';//���ؼ�����Ϸ
    }
    else if(pre_player->status==Rest)
    {//��Ϣһ�ֵ����
        printf("\n\n");
        printf("\t\t��ң�%s���ֲ�����\n",pre_player->name);
        printf("\t\t�㵱ǰӵ���ʽ�%d\n", pre_player->fund);
        pre_player->status = Active;//��һ�ֿ��Բ���
        return 't';//���ؼ�����Ϸ
    }
    //��Ծ���
    printf("\n\n");
    printf("\t\t��ǰ��ң�%s\t�����ʽ�%d\n\n", pre_player->name, pre_player->fund);
    step = get_step();
    pre_player->position += step;//����н�
    pre_player->position %= Character_Len;//��ͼѭ��
    printf("\n\n");
    printf("\t\t���ӽ����ǰ�����ȣ���%d\n", step);
    if(characters[pre_player->position].owner==(pre_player->id))
    {//��ǰλ�����ڸ����
        //������ɫ
        update_character(pre_player, &characters[pre_player->position]);
        //������ɫ
        sell_character(pre_player, &characters[pre_player->position]);
        printf("\t\t�㵱ǰӵ���ʽ�%d\n", pre_player->fund);
    }
    else
    {//�����ڸ����
        if(characters[pre_player->position].bonus!=0)
        {//��ý���
            pre_player->fund += characters[pre_player->position].bonus;
            printf("\t\t������%d�Ľ���\n", characters[pre_player->position].bonus);
            printf("\t\t�㵱ǰӵ���ʽ�%d\n", pre_player->fund);
            if(characters[pre_player->position].bonus==300)
            {//��һ����Ϣ
                pre_player->status = Rest;
                printf("\t\t������һ����Ϣ�������н��Ͳ���\n");
            }
        }
        else if(characters[pre_player->position].fine!=0)
        {//���ɷ���
            fine = characters[pre_player->position].fine;

            printf("\t\t�㽫��%s֧������%d\n", characters[pre_player->position].name, fine);
            while(pre_player->fund < fine)
            {//�ʽ��㣬���۽�ɫ
                if(pre_player->characters[0]==0)
                {//�޽�ɫ����
                    printf("\t\t����ʽ��㣬�����Ʋ������л�֧�����ʣ���˵�\n");
                    printf("\t\t�´�һ���ᱩ����come on\n");
                    pre_player->fund = 0;
                    pre_player->status = Broke;
                    break;
                }
                else
                {//���۽�ɫ�����ʽ�
                    printf("\t\t�������ʽ��㣬����۽�ɫ�Ի���㹻���ʽ�\n");
                    for(i=1;i<=Max_Character;i++)
                    {//���۽�ɫ
                        if(pre_player->characters[i]!=0)
                        {//ѯ�ʳ��۽�ɫ
                            sell_character(pre_player,&characters[pre_player->characters[i]-1]);
                            if(pre_player->characters[0]==0)
                            {//��ɫ����
                                break;
                            }
                        }
                    }
                }
            }
            if(pre_player->status!=Broke)
            {//δ�Ʋ�
                pre_player->fund -= fine;
                printf("\t\t�㵱ǰӵ���ʽ�%d\n", pre_player->fund);
            }
            else
            {//�Ʋ�
                return 'f';
            }
        }
        else if(characters[pre_player->position].owner==0)
        {//δ�۳�
            //����
            buy_character(pre_player, &characters[pre_player->position]);
        }
        else
        {//�����������
            if(pay_protection(pre_player, players, characters)=='f')
            {//�Ʋ�
                return 'f';
            }
        }
    }
    return 't';
}

void show_winner(Player players[], const unsigned int player_num)
{//���а�
    int i, j;
    Player * p_players[player_num+1];//0�����ڽ���
    for(i=0;i<player_num;i++)
    {//�������ָ��
        p_players[i+1] = &players[i];
    }
    for(i=1;i<player_num;i++)
    {//����
        for(j=1;j<player_num;j++)
        {
            if(p_players[j]->fund < p_players[j+1]->fund)
            {//����
                p_players[0] = p_players[j];
                p_players[j] = p_players[j+1];
                p_players[j+1] = p_players[0];
            }
        }
    }
    system("cls");
    printf("\n\n");
    printf("\t\tthanks for playing!!!\n");
    printf("\t\t������Ϸ�������������а����£�\n\n");
    printf("\t\t����ǳ�\t�����ʽ�\t���н�ɫ��\t���״̬\n\n");
    for(i=1;i<=player_num;i++)
    {
        printf("\t\t%-10s\t%-10d\t%-10d\t",
               p_players[i]->name,
               p_players[i]->fund,
               p_players[i]->characters[0]
               );
        if(p_players[i]->status!=Broke)
        {//δ�Ʋ�
            printf("��Ծ\n");
        }
        else
        {
            printf("�Ʋ�\n");
        }
    }
}
void run_game(Character characters[], Player players[], const unsigned int player_num)
{//������Ϸ
    char c;
    int count_players;//�������
    int turn;//���˳��
    char exit_flag;//�˳���ǩ

    count_players = player_num;//�ִ���ҳ�ʼ��
    turn = 0;//��һ����ҿ�ʼ������
    while(count_players>1)
    {//��Ϸѭ��
        show_map(characters, players, player_num);//�������map
        if(player_turn(&players[turn], players, characters)=='f')
        {//������Ʋ�
            count_players--;
        }
        if(count_players>1)
        {
            printf("\n\n");
            printf("\t\t�س���ʼ��һλ��ң�����x������Ϸ����ʾ���а�\n");
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
        printf("\t\t����ʣһλ��ң���Ϸ�������������ʾ���а�\n");
        system("pause");
    }
    show_winner(players, player_num);//���а�
}


/**�鿴��ɫ��Ϣ����*/

void show_character(const Character * sh_character)
{//��ӡ��ɫ��Ϣ
    system("cls");
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

void search_character(Character characters[])
{//���ҽ�ɫ
    int i;//ѭ������
    char c;//����������
    char search_name[Name_Len];//��ѯ��ɫ����
    char refind_choice;//���²���ѡ��

    do{
        system("cls");
        printf("\n\n");
        printf("\t\t�����ɫ�����֣�");
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
                printf("\t\tû���ҵ������ҵĽ�ɫ\n");
                break;
            }
            else
            {
                i++;
            }
        }
        printf("\n\n");
        printf("\t\t�����鿴��y/n��:");
        refind_choice = getchar();
        Cleaner;
    }while(refind_choice=='y');
}

#endif // GAME_FUNCTIONS_H_INCLUDED
