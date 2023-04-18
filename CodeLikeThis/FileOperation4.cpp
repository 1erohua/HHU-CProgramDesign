#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataLink3.h"
#include "MenuFuction3.h"
#include "FileOperation3.h"
#include <io.h>

void create_xls(int i)//�����ļ�����
{
	//����ļ������ڣ���ֹ���д���������ͨ������������
	if (i == 6)//6��������/�����û����ݴ�ȫ
	{
		//rename(�ɺ��������º�����)��������д�ļ��ĺ�����
		//ΪʲôҪ��д�������޷���xlsֱ�Ӳ�����������תΪ��txtͬ��ʽ��csv���в���
		//д���ļ��ļ�ʱ��Ԫ����\t����������fprintf(fp,"%s\t%s"),��һ����Ԫ��Ϊ��һ��%s���ڶ�����Ԫ��Ϊ�ڶ���%s
		rename("�û����ݴ�ȫ.xls", "�û����ݴ�ȫ.csv");
		FILE* fp = NULL;
		if ((fp = fopen("�û����ݴ�ȫ.csv", "w")) == NULL)
		{
			printf("�ļ���ʧ��\n");
		}
		fclose(fp);
		//������ٰ����ָĻ���
		rename("�û����ݴ�ȫ.csv", "�û����ݴ�ȫ.xls");
	}
	//����������ͬ���Ͳ�������������
	else if (i == 7)//��������/�����������ݴ�ȫ
	{
		rename("�������ݴ�ȫ.xls", "�������ݴ�ȫ.csv");
		FILE* fp = NULL;
		if ((fp = fopen("�������ݴ�ȫ.csv", "w")) == NULL)
		{
			printf("�ļ���ʧ��\n");
		}
		fclose(fp);
		rename("�������ݴ�ȫ.csv", "�������ݴ�ȫ.xls");
	}
}

//���ļ����ȡ����
//1.��list����ȥ
//2.�����û����ݣ��ٱ��ļ���ֵ
//3.�����������ݴ���pushback����pushback���ýڵ㴴����������ڵ㣬�����ڵ����list
void open_scan_to_file(User_Link* users_list)
{
	//��xlsתΪcsv�����д
	rename("�û����ݴ�ȫ.xls", "�û����ݴ�ȫ.csv");
	FILE* fp;
	if ((fp = fopen("�û����ݴ�ȫ.csv", "r")) == NULL)
	{
		printf("scanf�ļ���ʧ�ܣ�����ϵ������Ա�����޸���\n");
		system("pause");
		exit(0);
	}
	//���ļ��ж�ȡ��Ϣ
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
		//feof�������ж��Ƿ����ļ�β�����ǣ��򷵻ط�0ֵ
		//���޷��������ΪʲôҪ��feof����fscanf֮����Ϊ���Ƕ�β���֮��Ψһʹ�ô������Ҫ��ķ���
		if (feof(fp))
		{
			break;
		}
		// �����ݴ���pushback����pushback����ڵ㣬�ٲ���list�������������룬���Խ�pushback
		push_back(users_list, user_data);
	}
	fclose(fp);
	rename("�û����ݴ�ȫ.csv", "�û����ݴ�ȫ.xls");
}

int get_Vaccines_amount(Vaccines yi_miao_amount[])//���ļ��ж�ȡ��������
{
	//����������������ܣ�һ�Ǵ��ļ���ȡ���ݸ��ṹ������
	//���Ƿ���һ��ֵ�����ֵ��¼���ǲɹ�����
	rename("�������ݴ�ȫ.xls", "�������ݴ�ȫ.csv");
	FILE* fp;
	if ((fp = fopen("�������ݴ�ȫ.csv", "r")) == NULL)
	{
		printf("�������ݴ�ȫ�ļ������ʧ�ܣ�����ϵ������Ա�����޸���\n");
		printf("�����ǻ�û�д����ļ����������ȴ����ļ�\n");
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
	rename("�������ݴ�ȫ.csv", "�������ݴ�ȫ.xls");
	//����Ҳû�취���ͷ���i-1����ô���£�ֻ��˵�Ƕ�γ��ԵĽ��
	return i - 1;
}


void open_print_to_file(User_Data user_data,User_Link* users_list)//��������д�뵽�ļ���ͷ���ٷŽ�����
{
	FILE* fp;
	rename("�û����ݴ�ȫ.xls", "�û����ݴ�ȫ.csv");
	if ((fp = fopen("�û����ݴ�ȫ.csv", "a")) == NULL)
	{
		printf("print�ļ���ʧ�ܣ�����ϵ������Ա�����޸���\n");
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
	rename("�û����ݴ�ȫ.csv", "�û����ݴ�ȫ.xls");
}

void procurement_of_vaccines()
{
	Vaccines needed_vaccine{};//����һ���ṹ��
	printf("\n��������Ҫ�ɹ������Ʒ�ƣ����������ˡ����������ϣŵ�ȣ�\n");
	scanf("%s", needed_vaccine.Brands);

	printf("��������Ҫ�ɹ�������������ң���������ά����ҩ����,��ϣŵ�ȣ�\n");
	scanf("%s", needed_vaccine.factory);

	printf("��������Ҫ�ɹ�����Ĳɹ����ڣ����������գ�\n");
	scanf("%s", needed_vaccine.date);

	printf("��������Ҫ�ɹ�����Ĳɹ�������\n");
	scanf("%d",&needed_vaccine.amount);

	printf("��������Ҫ�ɹ�����ı�ţ�����������ɹ������йأ�\n");
	scanf("%s", needed_vaccine.Number);
	//���������뵽�ļ���
	rename("�������ݴ�ȫ.xls", "�������ݴ�ȫ.csv");
	FILE* fp;
	if ((fp = fopen("�������ݴ�ȫ.csv", "a")) == NULL)
	{
		printf("�������ݴ�ȫ�ļ������ʧ�ܣ�����ϵ������Ա�����޸���\n");
		printf("�����ǻ�û�д����ļ����������ȴ����ļ�\n");
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
	rename("�������ݴ�ȫ.csv", "�������ݴ�ȫ.xls");
}

