#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataLink3.h"
#include "MenuFuction3.h"
#include "FileOperation3.h"
#include <io.h>



void check_one_user(User_Link* users_list, char user_ID_number[])
{
	User_Node* user_node = users_list->U_first_node;
	for (int i = 0; i < users_list->U_node_amount; i++)
	{
		//strcmp函数用来比较两个字符串是否相同
		if (!strcmp(user_node->u_data.ID_number,user_ID_number))
		{
			printf("\n用户名：%s\n用户性别：%s\n用户年龄：%d\n用户身份证%s\n用户电话号码：%s\n用户地址：%s\n用户接种日期：%s\n用户接种次数：%d\n用户接种品牌：%s\n用户接种人：%s\n用户接种工号：%s\n",
				user_node->u_data.name,
				user_node->u_data.gender,
				user_node->u_data.age,
				user_node->u_data.ID_number,
				user_node->u_data.phone,
				user_node->u_data.address,
				user_node->u_data.date,
				user_node->u_data.batch,
				user_node->u_data.brand,
				user_node->u_data.jie_zhong_ren,
				user_node->u_data.jie_zhong_gong_hao);
		}
		user_node = user_node ->next;
	}
	printf("没有结果则说明没找到。\n");
}

int check_Vaccines(User_Link* user_list, int i, int choice_brand)//查看疫苗库存
{
	//这部分是统计计算疫苗的数据
	Vaccines yi_miao_amount[20];//结构体数组
	int types_of_vaccines[4] = { 0 };//0是科兴，1是康希诺，2是北京生物，3是其他疫苗
	int batch_of_vaccines= get_Vaccines_amount(yi_miao_amount);//将数组送过去让疫苗文件填满，并返回疫苗采购次数
	//全疫苗总和
	int sum_of_vaccines = 0;
	for (int i = 0; i < batch_of_vaccines; i++)
	{
		if (!strcmp(yi_miao_amount[i].Brands, "北京科兴"))
		{
			types_of_vaccines[0] += (yi_miao_amount[i].amount);
		}
		else if (!strcmp(yi_miao_amount[i].Brands, "康希诺"))
		{
			types_of_vaccines[1] += yi_miao_amount[i].amount;
		}
		else if (!strcmp(yi_miao_amount[i].Brands, "北京生物"))
		{
			types_of_vaccines[2] += (yi_miao_amount[i].amount);
		}
		else//其他疫苗
		{
			types_of_vaccines[3] += yi_miao_amount[i].amount;
		}
		sum_of_vaccines += (yi_miao_amount[i].amount);
	}
	//这里就是开始统计各种疫苗的数量了
	User_Node* user_node = user_list->U_first_node;
	while (user_node != NULL)
	{
		if (!strcmp((user_node->u_data.brand),"北京科兴"))
		{
			types_of_vaccines[0]--;
		}
		else if (!strcmp((user_node->u_data.brand), "康希诺"))
		{
			types_of_vaccines[1]--;
		}
		else if (!strcmp((user_node->u_data.brand), "北京生物"))
		{
			types_of_vaccines[2] --;
		}
		else
		{
			types_of_vaccines[3]--;
		}
		user_node = user_node->next;
	}

	if (i == 4)	//盘点疫苗数量与种类
	{
		printf("****************************************");
		printf("\n已采购疫苗总数:%d\n", sum_of_vaccines);
		printf("已接种次数：%d\n", user_list->U_node_amount);
		printf("当前剩余疫苗总数：%d\n", (sum_of_vaccines - (user_list->U_node_amount)));
		printf("当前北京科兴疫苗剩余：%d\n", types_of_vaccines[0]);
		printf("当前康希诺疫苗剩余：%d\n", types_of_vaccines[1]);
		printf("当前北京生物疫苗剩余：%d\n", types_of_vaccines[2]);
		printf("当前其他疫苗剩余：%d\n", types_of_vaccines[3]);
		return 1;
	}
	else if (i == 0)//提醒采购
	{
		if (sum_of_vaccines - (user_list->U_node_amount) <= 10)
		{
			printf("数量不足！请及时采购!\n");
			//这里的return 1凑数的，没什么用
			return 1;
		}
	}
	else if (i == 2)//数量不足禁止接种！
	{
		if (sum_of_vaccines - (user_list->U_node_amount) <= 3)
		{
			printf("数量不足，禁止接种！！！\n");
			//这里的return 1不是凑数的，如果疫苗总量不足一定数量，就返回1，执行主文件里的break
			return 1;
		}
	}
	else if (i == 5)//这个的作用在于，用户在接种北京科兴时，如果发现北京科兴没货了，会直接停止接种，类似如此
	{
		//下面的return 1都是有意义的
		if ((choice_brand == 1) && (types_of_vaccines[0] < 5))
		{
			printf("北京科兴疫苗不足！无法接种！\n");
			return 1;
		}
		else if ((choice_brand == 2) && (types_of_vaccines[1] < 5))
		{
			printf("康希诺疫苗不足！无法接种！\n");
			return 1;
		}
		else if ((choice_brand == 3) && (types_of_vaccines[2] < 5))
		{
			printf("北京生物疫苗不足！无法接种！\n");
			return 1;
		}
		else if ((choice_brand == 4) && (types_of_vaccines[3] < 5))
		{
			printf("其他疫苗不足！无法接种！\n");
			return 1;
		}
	}
	return 0;
}

void vaccine_inoculation(User_Link* users_list, Manager_Data* manager)//疫苗接种登记
{
	User_Data user_data{};
	//数据的输入
	//为了方便查询，在输入身份证之后，系统会通过身份证直接查询链表中的符合的且是最新的接种记录
	// 查询成功会进行日期的比对，接种时间不足半年的会终止接种
	//为了方便编写，下面会多次用到goto语句，以label为前缀的那个玩意就是要goto的

	//身份证                                 
	printf("请输入登记人员的身份证(18位)\n");
Label_ID_Card:
	char ID_USER[25];
	scanf("%s", ID_USER);
	//如果不足18位身份证就会返回让你重新填写
	if (strlen(ID_USER) != 18)
	{
		printf("身份证不符合要求，请重新输入身份证号：\n");
		goto Label_ID_Card;
	}
	else
	{	//符合条件就把字符串1拷贝进去
		strcpy(user_data.ID_number, ID_USER);
	}
	//日期
	printf("请输入接种人现在的日期：（形如20220304）(以每个月为30天计算，两次接种至少要相隔180天)\n");
Label_Date:
	char data_rule[20];
	scanf("%s", data_rule);
	if (strlen(data_rule) != 8)
	{
		printf("请输入正确的年份日期格式:\n");
		goto Label_Date;
	}
	else
	{
		strcpy(user_data.date, data_rule);
	}
	//传递身份证给函数->函数查询该人并传回该人最新的接种情况->拿日期与节点比较->不符合直接return退出接种
	//这里可能有点难理解，多看几遍
	//如果没有接种过就返回空值，接种过就返回最新的接种情况
	User_Node* check_date_for_this_one = check_date(users_list, user_data.ID_number);
	if (check_date_for_this_one == NULL)
	{
		printf("\n*该用户未接种过疫苗\n");
	}
	else
	{
		printf("\n*该用户上次接种时间为%s,接种批次为%d\n", 
			check_date_for_this_one->u_data.date, 
			check_date_for_this_one->u_data.batch);
		if (comparison((check_date_for_this_one->u_data.date), data_rule))//未超过半年接种，则返回1，不给接种
		{
			printf("\n该用户接种时间未超过半年！为了您的健康，不允许您的接种!\n");
			return;
		}
		else { printf("\n该用户符合接种条件，请继续输入信息\n"); }

	}
	//接种品牌
	//这里用switch是为了方便后面疫苗数量的统计，防止客户乱输入一些其他东西
label_brand:
	printf("请输入接种品牌(北京科兴、康希诺、北京生物、其他疫苗)\n");
	printf("只需要输入对应的序号即可\n");
	printf("1.北京科兴\n");
	printf("2.康希诺\n");
	printf("3.北京生物\n");
	printf("4.其他疫苗\n");
	int choice_brand = 0;
	while (scanf("%d", &choice_brand) != 1)
	{
		while (getchar() != '\n');
		printf("请重新输入数字！\n");
	}
	if (check_Vaccines(users_list, 5, choice_brand))//这里查询对应品牌的疫苗是否有货，没货了就不给接种这种疫苗
	{
		printf("请重新选择接种！\n");
		goto label_brand;
	}
	switch (choice_brand)
	{
	case 1:
		strcpy(user_data.brand, "北京科兴");
		break;
	case 2:
		strcpy(user_data.brand, "康希诺");
		break;
	case 3:
		strcpy(user_data.brand, "北京生物");
		break;
	default:
		strcpy(user_data.brand, "其他疫苗");
		break;
	}
	//名字
	printf("请输入登记人员的名字\n");
	scanf("%s", user_data.name);
	//年龄
	printf("请输入登记人员的年龄\n");
	while(scanf("%d",&user_data.age)!=1)
	{
		while (getchar() != '\n');
		printf("请重新输入数字！\n");
	}
	//性别
	printf("请输入登记人员的性别\n");
	scanf("%s", user_data.gender);
	//电话号码
	printf("请输入登记人员的电话号码\n");
Label_phone:char USER_PHONE[20];
	scanf("%s", USER_PHONE);
	if (strlen(USER_PHONE) != 11)
	{
		printf("电话号码不符合要求，请重新输入电话号码：\n");
		goto Label_phone;
	}
	else
	{
		strcpy(user_data.phone, USER_PHONE);
	}
	//地址
	printf("请输入登记地址（包含接种单位）\n");
	scanf("%s", user_data.address);
	//批次
	printf("请输入登记人员的接种批次\n");
	scanf("%d", &user_data.batch);
	//接种人
	strcpy(user_data.jie_zhong_ren, manager->Manager_Name);
	//接种人工号
	strcpy(user_data.jie_zhong_gong_hao, manager->Manager_Number);

	open_print_to_file(user_data, users_list);
	printf("\n*******************************\n");
	printf("接种成功！\n");
	printf("\n*******************************\n");
}//疫苗接种登记

User_Node* check_date(User_Link* user_list, char ID_number[])
{
	User_Node* user_node = user_list->U_first_node;//赋值首节点，用来遍历链表
	User_Node* pass_node = NULL;//这个节点是要传回去的
	while (user_node != NULL)
	{
		if (!strcmp(user_node->u_data.ID_number, ID_number))
		{
			//合适就赋值，找最新的那个
			pass_node = user_node;
		}
		user_node = user_node->next;
	}
	//传回去
	return pass_node;
}

int comparison(char last_time[], char this_time[])//这里一堆可以不用看的，没啥技术含量，单纯计算两个时间相差的天数
{
	int last_time_year = (last_time[0] - '0') * 1000 + (last_time[1] - '0') * 100 + (last_time[2] - '0') * 10 + (last_time[3] - '0');
	int this_time_year = (this_time[0] - '0') * 1000 + (this_time[1] - '0') * 100 + (this_time[2] - '0') * 10 + (this_time[3] - '0');
	if ((this_time_year - last_time_year)>1)//如果超过半年，返回0；不超过半年，返回1
	{
		return 0;
	}
	else if ((this_time_year - last_time_year) == 1)
	{
		int this_time_month = (this_time[4] - '0') * 10 + (this_time[5] - '0') + 12;
		int last_time_month = (last_time[4] - '0') * 10 + (last_time[5] - '0');
		if (((this_time_month - last_time_month) * 30) > 180)
		{
			return 0;
		}
		else
		{
			int this_time_day = (this_time[6] - '0') * 10 + (this_time[7] - '0');
			int last_time_day= (last_time[6] - '0') * 10 + (last_time[7] - '0');
			if (((this_time_day + this_time_month * 30) - (last_time_day + last_time_month * 30)) > 180)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
	else if ((this_time_year - last_time_year) == 0)
	{
		int this_time_month = (this_time[4] - '0') * 10 + (this_time[5] - '0') ;
		int last_time_month = (last_time[4] - '0') * 10 + (last_time[5] - '0');
		int this_time_day = (this_time[6] - '0') * 10 + (this_time[7] - '0');
		int last_time_day = (last_time[6] - '0') * 10 + (last_time[7] - '0');
		if (((this_time_day + this_time_month * 30) - (last_time_day + last_time_month * 30)) > 180)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

void check_all_users(User_Link* users_list)//查找所有人
{
	User_Node* test_node = users_list->U_first_node;//给个首节点，方便遍历
	printf("\n******************************************\n");
	printf("名字  性别  年龄  身份证号（共计18位数） 电话号码（共计11位数） 接种地址 接种日期 批次 接种品牌 接种人 接种人工号\n");
	while (test_node != NULL)
	{
		printf("%s  %s  %d  %s  %s  %s  %s  %d  %s  %s  %s\n",
			test_node->u_data.name,
			test_node->u_data.gender,
			test_node->u_data.age,
			test_node->u_data.ID_number,
			test_node->u_data.phone,
			test_node->u_data.address,
			test_node->u_data.date,
			test_node->u_data.batch,
			test_node->u_data.brand,
			test_node->u_data.jie_zhong_ren,
			test_node->u_data.jie_zhong_gong_hao);
		test_node = test_node->next;//下个节点
	}
	printf("反馈！当前链表节点数！:%d\n", users_list->U_node_amount);
	printf("\n******************************************\n");
}

 void Manager_Detect(Manager_Data* oneManager)
{
	
	Manager_Data AllManager[5]{};

	strcpy(AllManager[0].Manager_Number, "00001");
	strcpy(AllManager[0].Manager_Code, "123456");
	strcpy(AllManager[0].Manager_Name, "张三");

	strcpy(AllManager[1].Manager_Number, "00002");
	strcpy(AllManager[1].Manager_Code, "123456");
	strcpy(AllManager[1].Manager_Name, "李四");

	strcpy(AllManager[2].Manager_Number, "00003");
	strcpy(AllManager[2].Manager_Code, "123456");
	strcpy(AllManager[2].Manager_Name, "王五");

	strcpy(AllManager[3].Manager_Number, "00004");
	strcpy(AllManager[3].Manager_Code, "123456");
	strcpy(AllManager[3].Manager_Name, "赵六");

	strcpy(AllManager[4].Manager_Number, "00005");
	strcpy(AllManager[4].Manager_Code, "123456");
	strcpy(AllManager[4].Manager_Name, "林七");

	while (1)
	{
		printf("******************\n");
		printf("输入管理人员工号\n");
		printf("******************\n");
		scanf("%s", oneManager->Manager_Number);
		printf("******************\n");
		printf("输入管理人员密码\n");
		scanf("%s", oneManager->Manager_Code);
		printf("******************\n");

		for (int i = 0; i < 5; i++)
		{
			if ((strcmp(oneManager->Manager_Number, AllManager[i].Manager_Number) == 0) && (strcmp(oneManager->Manager_Code, AllManager[i].Manager_Code)==0))
			{
				printf("登录成功！\n");
				strcpy(oneManager->Manager_Number,AllManager[i].Manager_Number);
				strcpy(oneManager->Manager_Code,AllManager[i].Manager_Code);
				strcpy(oneManager->Manager_Name,AllManager[i].Manager_Name);
				return;
			}
		}
		printf("信息错误！请重新输入！\n");
	}
}