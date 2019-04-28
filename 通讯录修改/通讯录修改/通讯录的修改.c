//ͨѶ¼
//��ͨѶ¼�е������ﵽ����ʱ����õĴ�������
//�����Զ���ʵ�����ݣ����ö�̬�ڴ�ķ�ʽ
//��Ҫ�޸ĵĵط�AddressBook��Init����,AddPersonInfo��������ݺ���
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

//ÿ�������Ա�����ˣ��������绰����˾����ַ
//����������ɾ�Ĳ飨CRUD��
typedef struct PersonInfo
{
	char name[1024];
	char phone[1024];
	char company[1024];
	char address[1024];
}PersonInfo;

#define PERSON_INFOS_MAX_SIZE 200

typedef struct AddressBook
{
	PersonInfo* person_infos;
	int capacity;//person_infosָ��ָ����ڴ������������Ԫ��
	int size;//[0,size]��ʾ��Ч����ϵ��������Ϣ
}AddressBook;

AddressBook g_addr_book;

int Menu()
{
	printf("============================\n");
	printf("1.����\n");
	printf("2.ɾ��\n");
	printf("3.�޸�\n");
	printf("4.����\n");
	printf("5.����\n");
	printf("6.��ӡȫ��\n");
	printf("7.���ȫ��\n");
	printf("0.�˳�\n");
	printf("============================\n");
	printf("����������ѡ��");
	int choice;
	scanf("%d", &choice);
	return choice;
}

//��ʼ����������������Ĳ���Ϊָ�붼��Ҫ�ж�
void Init(AddressBook* addr_book)
{
	//�ж���������Ƿ�Ϊ��
	assert(addr_book != NULL);
	addr_book->size = 0;
	addr_book->capacity = 10;
	addr_book->person_infos = (PersonInfo*)malloc(
		sizeof(PersonInfo)*addr_book->capacity);
}

//C++ std::vectorһ��ҪӦ����
void Realloc(AddressBook* addr_book)
{
	assert(addr_book != NULL);
	addr_book->capacity *= 2;
	PersonInfo* old_infos = addr_book->person_infos;//��¼ԭ��ַ
	addr_book->person_infos = (PersonInfo*)malloc(
		addr_book->capacity * sizeof(PersonInfo));
	//��ʼ��������
	for (int i = 0; i < addr_book->size; ++i)
	{
		addr_book->person_infos[i] = old_infos[i];
	}
	free(old_infos);
}

void AddPersonInfo(AddressBook* addr_book)
{
	printf("������ϵ��\n");
	//����ϵ�������ʱ���������������������Ƚ�
	if (addr_book->size >= addr_book->capacity)
	{
		printf("��ϵ���Ѿ��������ˣ��������ݣ�\n");
		Realloc(addr_book);
	}
	PersonInfo* p = &addr_book->person_infos[addr_book->size];

	printf("��������ϵ��������");
	//��ʱ��������ݽ��������±�Ϊsize��Ԫ���Ϸ���
	scanf("%s", p->name);

	printf("��������ϵ�˵绰��");
	scanf("%s", p->phone);

	printf("��������ϵ�˹�˾��");
	scanf("%s", p->company);

	printf("��������ϵ�˵�ַ��");
	scanf("%s", p->address);

	++addr_book->size;
	printf("��ӳɹ���\n");
}//���еĴ��涼�����ڴ��е�ʵ�ֵģ����Ե������ڴ������Ǿͻ���ʧ

void DelPersonInfo(AddressBook* addr_book)
{
	assert(addr_book != NULL);
	printf("ɾ����ϵ�ˣ�\n");
	//���±���ɾ��
	printf("��������Ҫɾ������ţ�");
	int id = 0;
	scanf("%d", &id);
	if (id < 0 || id >= addr_book->size)
	{
		printf("��������������ɾ��ʧ�ܣ�\n");
		return;
	}
	//��ȡ�����е�Ԫ��ʱ���Ƽ�ʹ��ָ��ķ�ʽ��ȡ
	//���ֱ�ӻ�ȡ�ṹ��������ܻ��������ν�Ŀ���
	PersonInfo* p = &addr_book->person_infos[id];
	printf("��Ҫɾ����Ԫ����[%d]%s,����Y��ʾȷ��\n", id, p->name);
	char cmd[1024] = { 0 };
	scanf("%s", cmd);
	if (strcmp(cmd, "Y") != 0)
	{
		printf("ɾ������ȡ��!\n");
		return;
	}

	//��ʼɾ����
	//1.�����һ��Ԫ�ظ���Ҫɾ����Ԫ��
	PersonInfo* from = &addr_book->person_infos[addr_book->size - 1];
	PersonInfo* to = &addr_book->person_infos[id];
	*to = *from;//�������ֻ��Ҫ����һ��Ԫ�ؾͿ���

	//2.Ȼ��size--��������Ч����
	--addr_book->size;
	printf("ɾ���ɹ���\n");
}
void ModifyPersonInfo(AddressBook* addr_book)
{
	assert(addr_book != NULL);
	printf("����ϵ�˽����޸ģ�\n");
	printf("������Ҫ�޸ĵļ�¼��ţ�\n");
	int id = 0;
	scanf("%d", &id);
	if (id < 0 || id >= addr_book->size)
	{
		printf("���������������޸�ʧ�ܣ�\n");
		return;
	}
	PersonInfo* p = &addr_book->person_infos[id];
	printf("��Ҫ�޸ĵļ�¼Ϊ[%d]%s,ȷ��������Y\n", id, p->name);
	char cmd[1024] = { 0 };
	scanf("%s", &cmd);
	if (strcmp(cmd, "Y") != 0)
	{
		printf("�޸�ȡ����\n");
		return;
	}
	char input[1024] = { 0 };
	printf("�������޸�֮������֣���������ַ�����ʾ������");
	scanf("%s", &input);
	if (strcmp(input, "") != 0)
	{
		strcpy(p->name, input);
	}

	printf("�������޸�֮��ĵ绰����������ַ�����ʾ������");
	scanf("%s", &input);
	if (strcmp(input, "") != 0)
	{
		strcpy(p->phone, input);
	}

	printf("�������޸�֮��Ĺ�˾����������ַ�����ʾ������");
	scanf("%s", &input);
	if (strcmp(input, "") != 0)
	{
		strcpy(p->company, input);
	}

	printf("�������޸�֮��ĵ�ַ����������ַ�����ʾ������");
	scanf("%s", &input);
	if (strcmp(input, "") != 0)
	{
		strcpy(p->address, input);
	}

	printf("�޸ĳɹ���");
}

void FindPersonInfo(AddressBook* addr_book)
{
	assert(addr_book != NULL);
	printf("���в��ң�\n");
	//��ǰֻ���ǰ����������ҵ���ʽ
	printf("������Ҫ���ҵ�������");
	char name[1024] = { 0 };
	scanf("%s", name);
	for (int i = 0; i < addr_book->size; ++i)
	{
		PersonInfo* p = &addr_book->person_infos[i];
		if (strcmp(name, p->name) == 0)
		{
			printf("[%d]%s\t%s\t%s\t%s\n", i,
				p->name, p->phone, p->company, p->address);
		}//�˴������е���ϵ�˶�����һ��
	}
	printf("���ҳɹ���\n");
}
void SortPersonInfo(AddressBook* addr_book)
{

}

void PrintAllPersonInfo(AddressBook* addr_book)
{
	assert(addr_book != NULL);

	printf("��ʾ���е���ϵ����Ϣ��\n");

	PersonInfo* p = addr_book->person_infos;
	for (int i = 0; i < addr_book->size; ++i)
	{
		printf("[%d] %s\t%s\t%s\t%s\n", i, p[i].name, p[i].phone, p[i].address, p[i].company);
	}
	printf("��ʾ��ϣ�����ʾ%d����¼\n", addr_book->size);
}

void ClearAllPersonInfo(AddressBook* addr_book)
{
	assert(addr_book != NULL);
	printf("���������ϵ�ˣ�\n");
	printf("��ȷ��Ҫ�������ô��Y��ʾȷ��\n");
	char name[1024] = { 0 };
	scanf("%s", &name);
	if (strcmp(name, "Y") != 0)
	{
		printf("��ղ���ȡ����\n");
		return;
	}
	addr_book->size = 0;
	printf("��ճɹ���\n");
}


int main()
{
	typedef void(*pfunc_t)(AddressBook*);
	pfunc_t func_table[] = {
		AddPersonInfo,
		DelPersonInfo,
		ModifyPersonInfo,
		FindPersonInfo,
		SortPersonInfo,
		PrintAllPersonInfo,
		ClearAllPersonInfo,
	};

	//��Ԫ�ؽ��г�ʼ��
	Init(&g_addr_book);
	while (1)
	{
		int choice = Menu();
		if (choice == 0)
		{
			printf("Goodbye!\n");
			break;
		}
		if (choice < 0 || choice > sizeof(func_table) / sizeof(func_table[0]))
		{
			//��ʱ˵���û�����Ƿ�
			printf("�����������!���������룡\n");
			continue;
		}
		func_table[choice - 1](&g_addr_book);
	}

	return 0;
}