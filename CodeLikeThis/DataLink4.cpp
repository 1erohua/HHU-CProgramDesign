#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataLink3.h"
#include "MenuFuction3.h"
#include "FileOperation3.h"
#include <io.h>


//下面创建用户链表

User_Link* create_users_list()//链表创建函数//需要初始化，并且从文件中读取
{
	//给list分配地址
	User_Link* user_link = (User_Link*)malloc(sizeof(User_link));
	//初始化
	if (user_link == NULL)
	{
		printf("链表创建失败！请联系管理人员！\n");
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

void push_back(User_Link* users_list, User_Data user_data)//pushback函数
{
	//接收传过来的数据，并创造节点，将数据存入节点中
	User_Node* new_user_node = create_user_node(user_data);
	if (new_user_node == NULL)
	{
		printf("插入函数出错，请联系工作人员修正\n");
		system("pause");
		exit(0);
	}

	if (users_list->U_node_amount == 0)
	{
		//如果接入的是第一个节点，那么就让list的首尾都指向它
		//（“指向”这个说法不是那么准确，应该是赋值，但我觉得指向能更好地帮助你理解这个list）
		users_list->U_first_node = new_user_node;
		users_list->U_last_node = new_user_node;
	}
	else
	{
		//这里可能比较难理解，我建议画图理解一下
		//1.通过尾节点，将 最后一个节点的指针域 指向 新来的节点
		users_list->U_last_node->next = new_user_node;
		//2.再把尾节点 指向 新来的节点， 即 新来的节点 变成了 最后一个节点
		users_list->U_last_node = new_user_node;
	}
	//每增加一个节点，节点数+1
	users_list->U_node_amount++;
}

User_Node* create_user_node(User_Data user_data)//节点创建函数
{
	User_Node* user_node = (User_Node*)malloc(sizeof(User_Node));//可能这里会出现问题
	if (user_node == NULL)
	{
		printf("节点创建失败！怀疑是内存不足！请找管理人员！\n");
		return user_node;
	}
	else
	{
		user_node->u_data = user_data;
		user_node->next = NULL;
	}
	return user_node;
}

