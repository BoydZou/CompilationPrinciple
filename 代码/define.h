#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<fstream>
#include<string>

using namespace std;

#define TABLENUM 200 
#define CODENUM 300
int errors = 0;     //��������
int whilenum = 0, donum = 0, thennum = 0, ifnum = 0;
//**************************************************************************
enum symbol //�ַ�����
{							 
	ident, programS, varS, procedureS, beginS, endS, ifS, thenS, elseS,
	whileS, doS, callS, readS, writeS, oddS, constS, number, equalS, plusS, minusS,
	multiplyS, involution, divide, more, notless, lessS, notmore, notequal,
	assignment, comma, semicolon, leftbrackets, rightbrackets, undefine
};
//*************************************************
enum OpCode    //������ö������
{
	LIT, OPR, LOD, STO, CAL, RET, INT, JMP, JPC, READ, WRITE
};
struct Wordtable            //���ʱ�
{							 
	enum symbol SYM;   //�������� 
	char ID[15];	   //��ʶ������ 
	int NUM;		   //�������� 
	int lineN;		   //�к� 
}tab;
//*************************************************
typedef struct tablelink 
{				    //��������ṹ�� 
	enum symbol SYM;//��������
	char ID[15];	//��ʶ������
	int NUM;		//��������
	int lineN;		//�к�
	struct tablelink* next;//��һ��Ԫ��ַ 
}tabnode, * linklist;
//*************************************************
struct  table          //���ű�
{							
	enum symbol type;  //�������� 
	char name[15];	   //�������� 
	int num;		   //����ֵ��ռ�
	int level;         //���ڲ��
	char levelname[15];  //����
	int adr;           //���ƫ����
}ta[TABLENUM];
//*************************************************
struct Code
{
	enum OpCode Op;     //����������
	int lev;            //���
	int adr;            //���λ����
}code[CODENUM];
//*************************************************
void freelink(linklist& tb)
{						//�������� 
	linklist q;
	while (tb != NULL)
	{
		q = tb;
		tb = tb->next;
		free(q);
	}
}
//**************************************************************************

#define Stack_Init_Size 1000	//Ĭ����󳤶�Ϊ100
#define STACKINCREMENT 100	//�ռ�����Ϊ100
typedef int SElemType;
typedef struct SqStack								//����ջ�ṹ
{
	SElemType* base;//ջ��ָ��
	SElemType* top;	//ջ��ָ��
	int Stacksize;	//��ǰ����Ĵ洢����
}Stack;
Stack S;
//*************************************************
void InitStack(SqStack& S)					//����յ�ջ
{
	S.base = (SElemType*)malloc(Stack_Init_Size * sizeof(SElemType));//����ռ�
	S.top = S.base;
	S.Stacksize = Stack_Init_Size;
}
//*************************************************
void DestroyStack(SqStack& S)				//����ջ
{
	S.top = S.base;
	S.Stacksize = 0;
	free(S.base);
	S.base = NULL;
	S.top = NULL;
}
//*************************************************
void StackPush(SqStack& S, SElemType e)		//�����µ�ջ��Ԫ��
{
	SElemType* newbase;
	if ((S.top - S.base) == Stack_Init_Size)	//���ռ���������������ռ�
	{
		newbase = (SElemType*)realloc(S.base, (S.Stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!newbase)
			exit(0);
		S.base = newbase;
		S.top = S.base + Stack_Init_Size;
		S.Stacksize += STACKINCREMENT;
	}
	*(S.top) = e;
	S.top++;
}
//*************************************************
void GetESem(SqStack S, SElemType& e)		//����ջ��Ԫ��
{
	if (S.top != S.base)
		e = *(S.top - 1);
	else
	{
		printf("ջΪ�գ�\n");
		exit(0);
	}
}

#pragma once