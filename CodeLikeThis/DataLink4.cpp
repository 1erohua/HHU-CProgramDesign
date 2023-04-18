#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataLink3.h"
#include "MenuFuction3.h"
#include "FileOperation3.h"
#include <io.h>


//���洴���û�����

User_Link* create_users_list()//����������//��Ҫ��ʼ�������Ҵ��ļ��ж�ȡ
{
	//��list�����ַ
	User_Link* user_link = (User_Link*)malloc(sizeof(User_link));
	//��ʼ��
	if (user_link == NULL)
	{
		printf("������ʧ�ܣ�����ϵ������Ա��\n");
		return user_link;
	}
	else
	{
		user_link->U_first_node = NULL;
		user_link->U_last_node = NULL;
		user_link->U_node_amount =0;
		return user_link;
	}
}

void push_back(User_Link* users_list, User_Data user_data)//pushback����
{
	//���մ����������ݣ�������ڵ㣬�����ݴ���ڵ���
	User_Node* new_user_node = create_user_node(user_data);
	if (new_user_node == NULL)
	{
		printf("���뺯����������ϵ������Ա����\n");
		system("pause");
		exit(0);
	}

	if (users_list->U_node_amount == 0)
	{
		//���������ǵ�һ���ڵ㣬��ô����list����β��ָ����
		//����ָ�����˵��������ô׼ȷ��Ӧ���Ǹ�ֵ�����Ҿ���ָ���ܸ��õذ�����������list��
		users_list->U_first_node = new_user_node;
		users_list->U_last_node = new_user_node;
	}
	else
	{
		//������ܱȽ�����⣬�ҽ��黭ͼ���һ��
		//1.ͨ��β�ڵ㣬�� ���һ���ڵ��ָ���� ָ�� �����Ľڵ�
		users_list->U_last_node->next = new_user_node;
		//2.�ٰ�β�ڵ� ָ�� �����Ľڵ㣬 �� �����Ľڵ� ����� ���һ���ڵ�
		users_list->U_last_node = new_user_node;
	}
	//ÿ����һ���ڵ㣬�ڵ���+1
	users_list->U_node_amount++;
}

User_Node* create_user_node(User_Data user_data)//�ڵ㴴������
{
	User_Node* user_node = (User_Node*)malloc(sizeof(User_Node));//����������������
	if (user_node == NULL)
	{
		printf("�ڵ㴴��ʧ�ܣ��������ڴ治�㣡���ҹ�����Ա��\n");
		return user_node;
	}
	else
	{
		user_node->u_data = user_data;
		user_node->next = NULL;
	}
	return user_node;
}

