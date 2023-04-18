//用户数据
typedef struct data 
{
    char name[50];//名字
    int age;//年龄
    char gender[5];//性别
    char phone[20];//电话号码//需要满足11位
    char ID_number[25];//身份证号//需要检查是否输入数量为正确
    char address[100];//地址
    char date[20];//需要具体到日
    int batch;//批次
    char brand[20];//接种品牌
    char jie_zhong_ren[10];//接种人
    char jie_zhong_gong_hao[20];//接种工号
}User_Data;

//疫苗
typedef struct vaccines
{
    char Brands[20];//疫苗的品牌
    char factory[20];//疫苗的生产厂家
    char date[20];//疫苗的采购日期
    int amount;//采购数量
    char Number[10];//编号
}Vaccines;

typedef struct User_node //节点
{
    User_Data u_data;
    User_node* next;
}User_Node;

typedef struct User_link //链表
{
    User_Node* U_first_node;//指向首节点
    User_Node* U_last_node;//指向尾节点
    int U_node_amount;//计算统计节点总数
} User_Link;

User_Link* create_users_list();//创建链表

User_Node* create_user_node(User_Data user);//创建节点

void push_back(User_Link* users_list, User_Data user_data);//向后插入节点

typedef struct Manager_Code //管理人员数据组
{
    char Manager_Number[20];
    char Manager_Code[20];
    char Manager_Name[20];
}Manager_Data;