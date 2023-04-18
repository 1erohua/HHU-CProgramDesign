#pragma once
//疫苗接种函数
void vaccine_inoculation(User_Link* users_list, Manager_Data*manager);
//查看全员函数
void check_all_users(User_Link* users_list);
//查看一人函数
void check_one_user(User_Link* users_list, char user_ID_number[]);
//疫苗查看函数
int check_Vaccines(User_Link* user_list,int i,int if_no_this_Vaccines);
//用于查询要接种用户的日期，返回值是一个节点
User_Node* check_date(User_Link* user_list, char ID_number[]);
//用于比较用户接种时间
int comparison(char last_time[], char this_time[]);
//用于检测管理人员输入
void Manager_Detect(Manager_Data* oneManager);