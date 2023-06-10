#ifndef CHARACTER_PLAYER_H_INCLUDED
#define CHARACTER_PLAYER_H_INCLUDED

//�궨��
#define Name_Len 11//���Ƴ���
#define Intro_Len 11//��鳤��
#define Description_Len 101//��������

//��ɫ�ṹ��
typedef struct character
{
    unsigned int id;//���
    unsigned int owner;//ӵ����
    unsigned int degree;//�ȼ�
    unsigned int expenses;//����
    unsigned int protection_fee;//������
    unsigned int bonus;//����
    unsigned int fine;//����
    char name[Name_Len];//����
    char introduction[Intro_Len];//���
    char description[Description_Len];//����
}Character;

#endif // CHARACTER_PLAYER_H_INCLUDED
