#ifndef CHARACTER_PLAYER_H_INCLUDED
#define CHARACTER_PLAYER_H_INCLUDED

//�궨��
#define Name_Len 11//���Ƴ���
#define Intro_Len 11//��鳤��
#define Description_Len 101//��������
#define Max_Character 6//ӵ�н�ɫ�����

//��ɫ�ṹ��
typedef struct character
{
    int id;//���
    int owner;//ӵ����
    int degree;//�ȼ�
    int expenses;//����
    int protection_fee;//������
    int bonus;//����
    int fine;//����
    char name[Name_Len];//����
    char introduction[Intro_Len];//���
    char description[Description_Len];//����
}Character;

//��ҽṹ��
typedef struct player
{
    int id;//���
    int fund;//�ʽ�
    int status;//״̬
    int position;//λ��
    int characters[Max_Character+1];//ӵ�н�ɫ����һλ���ܽ�ɫ��
    char name[Name_Len];//����
}Player;


#endif // CHARACTER_PLAYER_H_INCLUDED
