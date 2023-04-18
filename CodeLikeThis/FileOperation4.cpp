#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataLink3.h"
#include "MenuFuction3.h"
#include "FileOperation3.h"
#include <io.h>

void create_xls(int i)//创建文件函数
{
	//如果文件不存在，禁止自行创建，必须通过本函数创建
	if (i == 6)//6——创建/覆盖用户数据大全
	{
		//rename(旧函数名，新函数名)，负责重写文件的函数名
		//为什么要重写？我们无法对xls直接操作，但可以转为和txt同格式的csv进行操作
		//写入文件文件时单元格用\t隔开，例如fprintf(fp,"%s\t%s"),第一个单元格为第一个%s，第二个单元格为第二个%s
		rename("用户数据大全.xls", "用户数据大全.csv");
		FILE* fp = NULL;
		if ((fp = fopen("用户数据大全.csv", "w")) == NULL)
		{
			printf("文件打开失败\n");
		}
		fclose(fp);
		//到最后再把名字改回来
		rename("用户数据大全.csv", "用户数据大全.xls");
	}
	//这里与上面同理，就不做过多论述了
	else if (i == 7)//——创建/覆盖疫苗数据大全
	{
		rename("疫苗数据大全.xls", "疫苗数据大全.csv");
		FILE* fp = NULL;
		if ((fp = fopen("疫苗数据大全.csv", "w")) == NULL)
		{
			printf("文件打开失败\n");
		}
		fclose(fp);
		rename("疫苗数据大全.csv", "疫苗数据大全.xls");
	}
}

//从文件里读取数据
//1.将list传过去
//2.创建用户数据，再被文件赋值
//3.将创建的数据传入pushback，在pushback调用节点创建函数创造节点，并将节点插入list
void open_scan_to_file(User_Link* users_list)
{
	//将xls转为csv方便读写
	rename("用户数据大全.xls", "用户数据大全.csv");
	FILE* fp;
	if ((fp = fopen("用户数据大全.csv", "r")) == NULL)
	{
		printf("scanf文件打开失败！请联系管理人员进行修复！\n");
		system("pause");
		exit(0);
	}
	//从文件中读取信息
	while (1)
	{
		User_Data user_data{};
		fscanf(fp, "%s %d %s %s %s %s %s %d %s %s %s",
			user_data.name,
			&user_data.age,
			user_data.ID_number,
			user_data.phone,
			user_data.gender,
			user_data.date,
			user_data.address,
			&user_data.batch,
			user_data.brand,
			user_data.jie_zhong_ren,
			user_data.jie_zhong_gong_hao
		);
		//feof函数是判断是否处于文件尾部，是，则返回非0值
		//我无法向你解释为什么要把feof放在fscanf之后，因为这是多次测试之后唯一使得代码符合要求的方法
		if (feof(fp))
		{
			break;
		}
		// 将数据传入pushback，让pushback创造节点，再插入list，由于是向后插入，所以叫pushback
		push_back(users_list, user_data);
	}
	fclose(fp);
	rename("用户数据大全.csv", "用户数据大全.xls");
}

int get_Vaccines_amount(Vaccines yi_miao_amount[])//从文件中读取疫苗数据
{
	//这个函数有两个功能，一是从文件读取数据给结构体数组
	//二是返回一个值，这个值记录的是采购次数
	rename("疫苗数据大全.xls", "疫苗数据大全.csv");
	FILE* fp;
	if ((fp = fopen("疫苗数据大全.csv", "r")) == NULL)
	{
		printf("疫苗数据大全文件读入打开失败！请联系管理人员进行修复！\n");
		printf("可能是还没有创建文件！！！请先创建文件\n");
		system("pause");
		exit(0);
	}

	int i = 0;
	while (!feof(fp))
	{

		fscanf(fp, "%s %s %s %d %s",
			yi_miao_amount[i].Brands,
			yi_miao_amount[i].factory,
			yi_miao_amount[i].date,
			&yi_miao_amount[i].amount,
			yi_miao_amount[i].Number
		);
		i++;
	}
	fclose(fp);
	rename("疫苗数据大全.csv", "疫苗数据大全.xls");
	//这里也没办法解释返回i-1是怎么回事，只能说是多次尝试的结果
	return i - 1;
}


void open_print_to_file(User_Data user_data,User_Link* users_list)//把数据先写入到文件里头，再放进链表
{
	FILE* fp;
	rename("用户数据大全.xls", "用户数据大全.csv");
	if ((fp = fopen("用户数据大全.csv", "a")) == NULL)
	{
		printf("print文件打开失败！请联系管理人员进行修复！\n");
		system("pause");
		exit(0);
	}
	fprintf(fp,
		"%s\t%d\t%s\t%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s\n",
		user_data.name,
		user_data.age,
		user_data.ID_number,
		user_data.phone,
		user_data.gender,
		user_data.date,
		user_data.address,
		user_data.batch,
		user_data.brand,
		user_data.jie_zhong_ren,
		user_data.jie_zhong_gong_hao
	);
	push_back(users_list, user_data);
	fclose(fp);
	rename("用户数据大全.csv", "用户数据大全.xls");
}

void procurement_of_vaccines()
{
	Vaccines needed_vaccine{};//创建一个结构体
	printf("\n请输入你要采购疫苗的品牌：（北京科兴、北京生物、康希诺等）\n");
	scanf("%s", needed_vaccine.Brands);

	printf("请输入你要采购疫苗的生产厂家：（科兴中维、国药集团,康希诺等）\n");
	scanf("%s", needed_vaccine.factory);

	printf("请输入你要采购疫苗的采购日期：（含年月日）\n");
	scanf("%s", needed_vaccine.date);

	printf("请输入你要采购疫苗的采购数量：\n");
	scanf("%d",&needed_vaccine.amount);

	printf("请输入你要采购疫苗的编号：（编号最好与采购次数有关）\n");
	scanf("%s", needed_vaccine.Number);
	//把数据输入到文件里
	rename("疫苗数据大全.xls", "疫苗数据大全.csv");
	FILE* fp;
	if ((fp = fopen("疫苗数据大全.csv", "a")) == NULL)
	{
		printf("疫苗数据大全文件读入打开失败！请联系管理人员进行修复！\n");
		printf("可能是还没有创建文件！！！请先创建文件\n");
		system("pause");
		exit(0);
	}
	fprintf(fp, "%s\t%s\t%s\t%d\t%s\n",
		needed_vaccine.Brands,
		needed_vaccine.factory,
		needed_vaccine.date,
		needed_vaccine.amount,
		needed_vaccine.Number
	);
	fclose(fp);
	rename("疫苗数据大全.csv", "疫苗数据大全.xls");
}

