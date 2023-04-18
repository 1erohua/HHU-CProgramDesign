#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataLink3.h"
#include "MenuFuction3.h"
#include "FileOperation3.h"
#include <io.h>
int main()
{
	//打印一级菜单
	printf("欢迎使用新冠疫苗接种登记系统！\n");
	printf("此为面向管理人员的疫苗接种登记系统\n");
	printf("为方便管理与展示我们只选择了5名工作人员进行接种\n");
	Manager_Data* manager = (Manager_Data*)malloc(sizeof(Manager_Data));
	Manager_Detect(manager);//这样就不用再填写接种工号和接种人了了
	printf("1.开始\n");
	printf("2.退出程序\n");
	printf("请输入你要进行的选项：\n");

	int choice;
	scanf("%d", &choice);
	
	//用户点击开始-》查询文件是否存在-》不存在就建立，存在则不建立-》从文件读取信息形成链表放置于后台
	if (choice)
	{
		//下面两个if是查询文件是否存在，用的是头文件为<io.h>的_access函数（如果你的版本不那么新，可以把_access改为access试试）
		//再次提醒，不要自行创建这两个文件，必须是本程序内用fopen("xxxx.xls",w)创建，自行创建会导致读取写入的不兼容
		//_access(文件名,0),如果文件存在，返回0；不存在返回-1
		if (_access("用户数据大全.xls", 0) == (-1))//如果用户数据大全不存在，就先建立
		{
			create_xls(6);
		}
		if (_access("疫苗数据大全.xls", 0) == (-1))//如果疫苗数据大全不存在，就先建立
		{
			create_xls(7);
		}

		//注意，这里的链表与大家平时学的稍微有些不同，这里的链表分为 list 和 node
		//list掌控着链表的首和尾，记录节点的个数
		//node就是大家平时所了解的，分为数据域和指针域
		//后续我会画张图给大家理解一下的
		User_Link* user_list = create_users_list();//这里创建并初始化一个list
		//此处将list传过去，然后打开文件，读取文件信息并存储到节点，把节点传给pushback函数再接入list
		open_scan_to_file(user_list);
		while (1)
		{
			//打印二级菜单
			printf("\n******************************************\n");
			printf("1.查看指定用户的接种情况\n");
			printf("2.接种疫苗\n");
			printf("3.查看接种情况\n");
			printf("4.查询当前疫苗库存\n");
			printf("5.采购疫苗\n");
			printf("6.覆盖原来的用户数据大全\n");
			printf("7.覆盖原来的疫苗数据大全\n");
			printf("8.退出程序\n");
			printf("请输入操作选项：\n");
			printf("\n******************************************\n");
			//函数check_Vaccines的指令如下
			//0----提醒采购疫苗
			//2----疫苗不足时禁止接种
			//4----查看疫苗库存---并盘点疫苗种类
			//check_Vaccines的第三个参数，如果填了NULL，就不用管，用不到的，不是在这用的
			check_Vaccines(user_list, 0,NULL);//疫苗不够时，提醒采购

			int another_choice;
			scanf("%d", &another_choice);
			switch (another_choice)
			{
			case 1://查看单个用户———通过身份证号查询
				char user_ID_number[25];
				printf("\n请输入需查询用户的身份证号\n");
				scanf("%s", user_ID_number);
				check_one_user(user_list, user_ID_number);//list为链表的掌控者，别忘了别忘了
				break;
			case 2://接种疫苗
				if(check_Vaccines(user_list, 2,NULL))//这里只是检查疫苗总量而已，如果不够就会停止接种
				{
					break;
				}
				//把链表传过去，它会先创建一个用户数据接收数据，再把该数据写入文件，最后用pushback插入链表
				vaccine_inoculation(user_list,manager);//这里会用到check_Vaccines函数
				break;
			case 3://查看全员
				check_all_users(user_list);
				break;
			case 4://疫苗库存暂且用结构体数组吧
				check_Vaccines(user_list,4,NULL);
				break;
			case 5://采购疫苗
				procurement_of_vaccines();//这里是文件操作，请去FileOperation
				break;
			case 6:
				//创造/覆盖用户数据大全
				create_xls(6);
				break;
			case 7:
				//创造/覆盖疫苗数据大全
				create_xls(7);
				break;
			default:
				printf("程序结束！\n");
				return 0;
				break;
			}
		}
	}
	else//用户选择了退出程序
	{
		return 0;
	}
}
