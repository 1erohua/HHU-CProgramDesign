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
		//strcmp���������Ƚ������ַ����Ƿ���ͬ
		if (!strcmp(user_node->u_data.ID_number,user_ID_number))
		{
			printf("\n�û�����%s\n�û��Ա�%s\n�û����䣺%d\n�û����֤%s\n�û��绰���룺%s\n�û���ַ��%s\n�û��������ڣ�%s\n�û����ִ�����%d\n�û�����Ʒ�ƣ�%s\n�û������ˣ�%s\n�û����ֹ��ţ�%s\n",
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
	printf("û�н����˵��û�ҵ���\n");
}

int check_Vaccines(User_Link* user_list, int i, int choice_brand)//�鿴������
{
	//�ⲿ����ͳ�Ƽ������������
	Vaccines yi_miao_amount[20];//�ṹ������
	int types_of_vaccines[4] = { 0 };//0�ǿ��ˣ�1�ǿ�ϣŵ��2�Ǳ������3����������
	int batch_of_vaccines= get_Vaccines_amount(yi_miao_amount);//�������͹�ȥ�������ļ�����������������ɹ�����
	//ȫ�����ܺ�
	int sum_of_vaccines = 0;
	for (int i = 0; i < batch_of_vaccines; i++)
	{
		if (!strcmp(yi_miao_amount[i].Brands, "��������"))
		{
			types_of_vaccines[0] += (yi_miao_amount[i].amount);
		}
		else if (!strcmp(yi_miao_amount[i].Brands, "��ϣŵ"))
		{
			types_of_vaccines[1] += yi_miao_amount[i].amount;
		}
		else if (!strcmp(yi_miao_amount[i].Brands, "��������"))
		{
			types_of_vaccines[2] += (yi_miao_amount[i].amount);
		}
		else//��������
		{
			types_of_vaccines[3] += yi_miao_amount[i].amount;
		}
		sum_of_vaccines += (yi_miao_amount[i].amount);
	}
	//������ǿ�ʼͳ�Ƹ��������������
	User_Node* user_node = user_list->U_first_node;
	while (user_node != NULL)
	{
		if (!strcmp((user_node->u_data.brand),"��������"))
		{
			types_of_vaccines[0]--;
		}
		else if (!strcmp((user_node->u_data.brand), "��ϣŵ"))
		{
			types_of_vaccines[1]--;
		}
		else if (!strcmp((user_node->u_data.brand), "��������"))
		{
			types_of_vaccines[2] --;
		}
		else
		{
			types_of_vaccines[3]--;
		}
		user_node = user_node->next;
	}

	if (i == 4)	//�̵���������������
	{
		printf("****************************************");
		printf("\n�Ѳɹ���������:%d\n", sum_of_vaccines);
		printf("�ѽ��ִ�����%d\n", user_list->U_node_amount);
		printf("��ǰʣ������������%d\n", (sum_of_vaccines - (user_list->U_node_amount)));
		printf("��ǰ������������ʣ�ࣺ%d\n", types_of_vaccines[0]);
		printf("��ǰ��ϣŵ����ʣ�ࣺ%d\n", types_of_vaccines[1]);
		printf("��ǰ������������ʣ�ࣺ%d\n", types_of_vaccines[2]);
		printf("��ǰ��������ʣ�ࣺ%d\n", types_of_vaccines[3]);
		return 1;
	}
	else if (i == 0)//���Ѳɹ�
	{
		if (sum_of_vaccines - (user_list->U_node_amount) <= 10)
		{
			printf("�������㣡�뼰ʱ�ɹ�!\n");
			//�����return 1�����ģ�ûʲô��
			return 1;
		}
	}
	else if (i == 2)//���������ֹ���֣�
	{
		if (sum_of_vaccines - (user_list->U_node_amount) <= 3)
		{
			printf("�������㣬��ֹ���֣�����\n");
			//�����return 1���Ǵ����ģ����������������һ���������ͷ���1��ִ�����ļ����break
			return 1;
		}
	}
	else if (i == 5)//������������ڣ��û��ڽ��ֱ�������ʱ��������ֱ�������û���ˣ���ֱ��ֹͣ���֣��������
	{
		//�����return 1�����������
		if ((choice_brand == 1) && (types_of_vaccines[0] < 5))
		{
			printf("�����������粻�㣡�޷����֣�\n");
			return 1;
		}
		else if ((choice_brand == 2) && (types_of_vaccines[1] < 5))
		{
			printf("��ϣŵ���粻�㣡�޷����֣�\n");
			return 1;
		}
		else if ((choice_brand == 3) && (types_of_vaccines[2] < 5))
		{
			printf("�����������粻�㣡�޷����֣�\n");
			return 1;
		}
		else if ((choice_brand == 4) && (types_of_vaccines[3] < 5))
		{
			printf("�������粻�㣡�޷����֣�\n");
			return 1;
		}
	}
	return 0;
}

void vaccine_inoculation(User_Link* users_list, Manager_Data* manager)//������ֵǼ�
{
	User_Data user_data{};
	//���ݵ�����
	//Ϊ�˷����ѯ�����������֤֮��ϵͳ��ͨ�����ֱ֤�Ӳ�ѯ�����еķ��ϵ��������µĽ��ּ�¼
	// ��ѯ�ɹ���������ڵıȶԣ�����ʱ�䲻�����Ļ���ֹ����
	//Ϊ�˷����д����������õ�goto��䣬��labelΪǰ׺���Ǹ��������Ҫgoto��

	//���֤                                 
	printf("������Ǽ���Ա�����֤(18λ)\n");
Label_ID_Card:
	char ID_USER[25];
	scanf("%s", ID_USER);
	//�������18λ���֤�ͻ᷵������������д
	if (strlen(ID_USER) != 18)
	{
		printf("���֤������Ҫ���������������֤�ţ�\n");
		goto Label_ID_Card;
	}
	else
	{	//���������Ͱ��ַ���1������ȥ
		strcpy(user_data.ID_number, ID_USER);
	}
	//����
	printf("��������������ڵ����ڣ�������20220304��(��ÿ����Ϊ30����㣬���ν�������Ҫ���180��)\n");
Label_Date:
	char data_rule[20];
	scanf("%s", data_rule);
	if (strlen(data_rule) != 8)
	{
		printf("��������ȷ��������ڸ�ʽ:\n");
		goto Label_Date;
	}
	else
	{
		strcpy(user_data.date, data_rule);
	}
	//�������֤������->������ѯ���˲����ظ������µĽ������->��������ڵ�Ƚ�->������ֱ��return�˳�����
	//��������е�����⣬�࿴����
	//���û�н��ֹ��ͷ��ؿ�ֵ�����ֹ��ͷ������µĽ������
	User_Node* check_date_for_this_one = check_date(users_list, user_data.ID_number);
	if (check_date_for_this_one == NULL)
	{
		printf("\n*���û�δ���ֹ�����\n");
	}
	else
	{
		printf("\n*���û��ϴν���ʱ��Ϊ%s,��������Ϊ%d\n", 
			check_date_for_this_one->u_data.date, 
			check_date_for_this_one->u_data.batch);
		if (comparison((check_date_for_this_one->u_data.date), data_rule))//δ����������֣��򷵻�1����������
		{
			printf("\n���û�����ʱ��δ�������꣡Ϊ�����Ľ��������������Ľ���!\n");
			return;
		}
		else { printf("\n���û����Ͻ��������������������Ϣ\n"); }

	}
	//����Ʒ��
	//������switch��Ϊ�˷����������������ͳ�ƣ���ֹ�ͻ�������һЩ��������
label_brand:
	printf("���������Ʒ��(�������ˡ���ϣŵ�����������������)\n");
	printf("ֻ��Ҫ�����Ӧ����ż���\n");
	printf("1.��������\n");
	printf("2.��ϣŵ\n");
	printf("3.��������\n");
	printf("4.��������\n");
	int choice_brand = 0;
	while (scanf("%d", &choice_brand) != 1)
	{
		while (getchar() != '\n');
		printf("�������������֣�\n");
	}
	if (check_Vaccines(users_list, 5, choice_brand))//�����ѯ��ӦƷ�Ƶ������Ƿ��л���û���˾Ͳ���������������
	{
		printf("������ѡ����֣�\n");
		goto label_brand;
	}
	switch (choice_brand)
	{
	case 1:
		strcpy(user_data.brand, "��������");
		break;
	case 2:
		strcpy(user_data.brand, "��ϣŵ");
		break;
	case 3:
		strcpy(user_data.brand, "��������");
		break;
	default:
		strcpy(user_data.brand, "��������");
		break;
	}
	//����
	printf("������Ǽ���Ա������\n");
	scanf("%s", user_data.name);
	//����
	printf("������Ǽ���Ա������\n");
	while(scanf("%d",&user_data.age)!=1)
	{
		while (getchar() != '\n');
		printf("�������������֣�\n");
	}
	//�Ա�
	printf("������Ǽ���Ա���Ա�\n");
	scanf("%s", user_data.gender);
	//�绰����
	printf("������Ǽ���Ա�ĵ绰����\n");
Label_phone:char USER_PHONE[20];
	scanf("%s", USER_PHONE);
	if (strlen(USER_PHONE) != 11)
	{
		printf("�绰���벻����Ҫ������������绰���룺\n");
		goto Label_phone;
	}
	else
	{
		strcpy(user_data.phone, USER_PHONE);
	}
	//��ַ
	printf("������Ǽǵ�ַ���������ֵ�λ��\n");
	scanf("%s", user_data.address);
	//����
	printf("������Ǽ���Ա�Ľ�������\n");
	scanf("%d", &user_data.batch);
	//������
	strcpy(user_data.jie_zhong_ren, manager->Manager_Name);
	//�����˹���
	strcpy(user_data.jie_zhong_gong_hao, manager->Manager_Number);

	open_print_to_file(user_data, users_list);
	printf("\n*******************************\n");
	printf("���ֳɹ���\n");
	printf("\n*******************************\n");
}//������ֵǼ�

User_Node* check_date(User_Link* user_list, char ID_number[])
{
	User_Node* user_node = user_list->U_first_node;//��ֵ�׽ڵ㣬������������
	User_Node* pass_node = NULL;//����ڵ���Ҫ����ȥ��
	while (user_node != NULL)
	{
		if (!strcmp(user_node->u_data.ID_number, ID_number))
		{
			//���ʾ͸�ֵ�������µ��Ǹ�
			pass_node = user_node;
		}
		user_node = user_node->next;
	}
	//����ȥ
	return pass_node;
}

int comparison(char last_time[], char this_time[])//����һ�ѿ��Բ��ÿ��ģ�ûɶ����������������������ʱ����������
{
	int last_time_year = (last_time[0] - '0') * 1000 + (last_time[1] - '0') * 100 + (last_time[2] - '0') * 10 + (last_time[3] - '0');
	int this_time_year = (this_time[0] - '0') * 1000 + (this_time[1] - '0') * 100 + (this_time[2] - '0') * 10 + (this_time[3] - '0');
	if ((this_time_year - last_time_year)>1)//����������꣬����0�����������꣬����1
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

void check_all_users(User_Link* users_list)//����������
{
	User_Node* test_node = users_list->U_first_node;//�����׽ڵ㣬�������
	printf("\n******************************************\n");
	printf("����  �Ա�  ����  ���֤�ţ�����18λ���� �绰���루����11λ���� ���ֵ�ַ �������� ���� ����Ʒ�� ������ �����˹���\n");
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
		test_node = test_node->next;//�¸��ڵ�
	}
	printf("��������ǰ����ڵ�����:%d\n", users_list->U_node_amount);
	printf("\n******************************************\n");
}

 void Manager_Detect(Manager_Data* oneManager)
{
	
	Manager_Data AllManager[5]{};

	strcpy(AllManager[0].Manager_Number, "00001");
	strcpy(AllManager[0].Manager_Code, "123456");
	strcpy(AllManager[0].Manager_Name, "����");

	strcpy(AllManager[1].Manager_Number, "00002");
	strcpy(AllManager[1].Manager_Code, "123456");
	strcpy(AllManager[1].Manager_Name, "����");

	strcpy(AllManager[2].Manager_Number, "00003");
	strcpy(AllManager[2].Manager_Code, "123456");
	strcpy(AllManager[2].Manager_Name, "����");

	strcpy(AllManager[3].Manager_Number, "00004");
	strcpy(AllManager[3].Manager_Code, "123456");
	strcpy(AllManager[3].Manager_Name, "����");

	strcpy(AllManager[4].Manager_Number, "00005");
	strcpy(AllManager[4].Manager_Code, "123456");
	strcpy(AllManager[4].Manager_Name, "����");

	while (1)
	{
		printf("******************\n");
		printf("���������Ա����\n");
		printf("******************\n");
		scanf("%s", oneManager->Manager_Number);
		printf("******************\n");
		printf("���������Ա����\n");
		scanf("%s", oneManager->Manager_Code);
		printf("******************\n");

		for (int i = 0; i < 5; i++)
		{
			if ((strcmp(oneManager->Manager_Number, AllManager[i].Manager_Number) == 0) && (strcmp(oneManager->Manager_Code, AllManager[i].Manager_Code)==0))
			{
				printf("��¼�ɹ���\n");
				strcpy(oneManager->Manager_Number,AllManager[i].Manager_Number);
				strcpy(oneManager->Manager_Code,AllManager[i].Manager_Code);
				strcpy(oneManager->Manager_Name,AllManager[i].Manager_Name);
				return;
			}
		}
		printf("��Ϣ�������������룡\n");
	}
}