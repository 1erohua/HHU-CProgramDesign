#pragma once
void open_print_to_file(User_Data user_data, User_Link* users_list);//将数据输入到文件
void open_scan_to_file(User_Link* users_list);//从文件中读取数据给链表
int get_Vaccines_amount(Vaccines yi_miao_amount[]);//返回值为疫苗的批次
void procurement_of_vaccines();//采购疫苗，负责直接写入文件
void create_xls(int i);//创建文件