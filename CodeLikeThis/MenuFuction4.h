#pragma once
//������ֺ���
void vaccine_inoculation(User_Link* users_list, Manager_Data*manager);
//�鿴ȫԱ����
void check_all_users(User_Link* users_list);
//�鿴һ�˺���
void check_one_user(User_Link* users_list, char user_ID_number[]);
//����鿴����
int check_Vaccines(User_Link* user_list,int i,int if_no_this_Vaccines);
//���ڲ�ѯҪ�����û������ڣ�����ֵ��һ���ڵ�
User_Node* check_date(User_Link* user_list, char ID_number[]);
//���ڱȽ��û�����ʱ��
int comparison(char last_time[], char this_time[]);
//���ڼ�������Ա����
void Manager_Detect(Manager_Data* oneManager);