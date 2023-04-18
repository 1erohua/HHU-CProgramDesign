//�û�����
typedef struct data 
{
    char name[50];//����
    int age;//����
    char gender[5];//�Ա�
    char phone[20];//�绰����//��Ҫ����11λ
    char ID_number[25];//���֤��//��Ҫ����Ƿ���������Ϊ��ȷ
    char address[100];//��ַ
    char date[20];//��Ҫ���嵽��
    int batch;//����
    char brand[20];//����Ʒ��
    char jie_zhong_ren[10];//������
    char jie_zhong_gong_hao[20];//���ֹ���
}User_Data;

//����
typedef struct vaccines
{
    char Brands[20];//�����Ʒ��
    char factory[20];//�������������
    char date[20];//����Ĳɹ�����
    int amount;//�ɹ�����
    char Number[10];//���
}Vaccines;

typedef struct User_node //�ڵ�
{
    User_Data u_data;
    User_node* next;
}User_Node;

typedef struct User_link //����
{
    User_Node* U_first_node;//ָ���׽ڵ�
    User_Node* U_last_node;//ָ��β�ڵ�
    int U_node_amount;//����ͳ�ƽڵ�����
} User_Link;

User_Link* create_users_list();//��������

User_Node* create_user_node(User_Data user);//�����ڵ�

void push_back(User_Link* users_list, User_Data user_data);//������ڵ�

typedef struct Manager_Code //������Ա������
{
    char Manager_Number[20];
    char Manager_Code[20];
    char Manager_Name[20];
}Manager_Data;