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
	//��ӡһ���˵�
	printf("��ӭʹ���¹�������ֵǼ�ϵͳ��\n");
	printf("��Ϊ���������Ա��������ֵǼ�ϵͳ\n");
	printf("Ϊ���������չʾ����ֻѡ����5��������Ա���н���\n");
	Manager_Data* manager = (Manager_Data*)malloc(sizeof(Manager_Data));
	Manager_Detect(manager);//�����Ͳ�������д���ֹ��źͽ���������
	printf("1.��ʼ\n");
	printf("2.�˳�����\n");
	printf("��������Ҫ���е�ѡ�\n");

	int choice;
	scanf("%d", &choice);
	
	//�û������ʼ-����ѯ�ļ��Ƿ����-�������ھͽ����������򲻽���-�����ļ���ȡ��Ϣ�γ���������ں�̨
	if (choice)
	{
		//��������if�ǲ�ѯ�ļ��Ƿ���ڣ��õ���ͷ�ļ�Ϊ<io.h>��_access�����������İ汾����ô�£����԰�_access��Ϊaccess���ԣ�
		//�ٴ����ѣ���Ҫ���д����������ļ��������Ǳ���������fopen("xxxx.xls",w)���������д����ᵼ�¶�ȡд��Ĳ�����
		//_access(�ļ���,0),����ļ����ڣ�����0�������ڷ���-1
		if (_access("�û����ݴ�ȫ.xls", 0) == (-1))//����û����ݴ�ȫ�����ڣ����Ƚ���
		{
			create_xls(6);
		}
		if (_access("�������ݴ�ȫ.xls", 0) == (-1))//����������ݴ�ȫ�����ڣ����Ƚ���
		{
			create_xls(7);
		}

		//ע�⣬�������������ƽʱѧ����΢��Щ��ͬ������������Ϊ list �� node
		//list�ƿ���������׺�β����¼�ڵ�ĸ���
		//node���Ǵ��ƽʱ���˽�ģ���Ϊ�������ָ����
		//�����һử��ͼ��������һ�µ�
		User_Link* user_list = create_users_list();//���ﴴ������ʼ��һ��list
		//�˴���list����ȥ��Ȼ����ļ�����ȡ�ļ���Ϣ���洢���ڵ㣬�ѽڵ㴫��pushback�����ٽ���list
		open_scan_to_file(user_list);
		while (1)
		{
			//��ӡ�����˵�
			printf("\n******************************************\n");
			printf("1.�鿴ָ���û��Ľ������\n");
			printf("2.��������\n");
			printf("3.�鿴�������\n");
			printf("4.��ѯ��ǰ������\n");
			printf("5.�ɹ�����\n");
			printf("6.����ԭ�����û����ݴ�ȫ\n");
			printf("7.����ԭ�����������ݴ�ȫ\n");
			printf("8.�˳�����\n");
			printf("���������ѡ�\n");
			printf("\n******************************************\n");
			//����check_Vaccines��ָ������
			//0----���Ѳɹ�����
			//2----���粻��ʱ��ֹ����
			//4----�鿴������---���̵���������
			//check_Vaccines�ĵ������������������NULL���Ͳ��ùܣ��ò����ģ����������õ�
			check_Vaccines(user_list, 0,NULL);//���粻��ʱ�����Ѳɹ�

			int another_choice;
			scanf("%d", &another_choice);
			switch (another_choice)
			{
			case 1://�鿴�����û�������ͨ�����֤�Ų�ѯ
				char user_ID_number[25];
				printf("\n���������ѯ�û������֤��\n");
				scanf("%s", user_ID_number);
				check_one_user(user_list, user_ID_number);//listΪ������ƿ��ߣ������˱�����
				break;
			case 2://��������
				if(check_Vaccines(user_list, 2,NULL))//����ֻ�Ǽ�������������ѣ���������ͻ�ֹͣ����
				{
					break;
				}
				//��������ȥ�������ȴ���һ���û����ݽ������ݣ��ٰѸ�����д���ļ��������pushback��������
				vaccine_inoculation(user_list,manager);//������õ�check_Vaccines����
				break;
			case 3://�鿴ȫԱ
				check_all_users(user_list);
				break;
			case 4://�����������ýṹ�������
				check_Vaccines(user_list,4,NULL);
				break;
			case 5://�ɹ�����
				procurement_of_vaccines();//�������ļ���������ȥFileOperation
				break;
			case 6:
				//����/�����û����ݴ�ȫ
				create_xls(6);
				break;
			case 7:
				//����/�����������ݴ�ȫ
				create_xls(7);
				break;
			default:
				printf("���������\n");
				return 0;
				break;
			}
		}
	}
	else//�û�ѡ�����˳�����
	{
		return 0;
	}
}
