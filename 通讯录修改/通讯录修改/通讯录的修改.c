//通讯录
//当通讯录中的人数达到上限时，最好的处理方法是
//可以自动的实现扩容，利用动态内存的方式
//需要修改的地方AddressBook，Init函数,AddPersonInfo中添加扩容函数
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

//每个管理成员包含了：姓名，电话，公司，地址
//管理方法：增删改查（CRUD）
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
	int capacity;//person_infos指针指向的内存最多所包含的元素
	int size;//[0,size]表示有效的联系人区间信息
}AddressBook;

AddressBook g_addr_book;

int Menu()
{
	printf("============================\n");
	printf("1.新增\n");
	printf("2.删除\n");
	printf("3.修改\n");
	printf("4.查找\n");
	printf("5.排序\n");
	printf("6.打印全部\n");
	printf("7.清空全部\n");
	printf("0.退出\n");
	printf("============================\n");
	printf("请输入您的选择：");
	int choice;
	scanf("%d", &choice);
	return choice;
}

//初始化操作：但凡传入的参数为指针都需要判定
void Init(AddressBook* addr_book)
{
	//判定传入参数是否为空
	assert(addr_book != NULL);
	addr_book->size = 0;
	addr_book->capacity = 10;
	addr_book->person_infos = (PersonInfo*)malloc(
		sizeof(PersonInfo)*addr_book->capacity);
}

//C++ std::vector一样要应用它
void Realloc(AddressBook* addr_book)
{
	assert(addr_book != NULL);
	addr_book->capacity *= 2;
	PersonInfo* old_infos = addr_book->person_infos;//记录原地址
	addr_book->person_infos = (PersonInfo*)malloc(
		addr_book->capacity * sizeof(PersonInfo));
	//开始搬运数据
	for (int i = 0; i < addr_book->size; ++i)
	{
		addr_book->person_infos[i] = old_infos[i];
	}
	free(old_infos);
}

void AddPersonInfo(AddressBook* addr_book)
{
	printf("新增联系人\n");
	//当联系人添加满时的做法：这种做法不够先进
	if (addr_book->size >= addr_book->capacity)
	{
		printf("联系人已经储存满了！进行扩容！\n");
		Realloc(addr_book);
	}
	PersonInfo* p = &addr_book->person_infos[addr_book->size];

	printf("请输入联系人姓名：");
	//此时输入的内容将放置在下标为size的元素上放置
	scanf("%s", p->name);

	printf("请输入联系人电话：");
	scanf("%s", p->phone);

	printf("请输入联系人公司：");
	scanf("%s", p->company);

	printf("请输入联系人地址：");
	scanf("%s", p->address);

	++addr_book->size;
	printf("添加成功！\n");
}//所有的储存都是在内存中的实现的，所以当程序在次启动是就会消失

void DelPersonInfo(AddressBook* addr_book)
{
	assert(addr_book != NULL);
	printf("删除联系人！\n");
	//按下标来删除
	printf("请输入您要删除的序号：");
	int id = 0;
	scanf("%d", &id);
	if (id < 0 || id >= addr_book->size)
	{
		printf("您输入的序号有误！删除失败！\n");
		return;
	}
	//在取数组中的元素时，推荐使用指针的方式获取
	//如果直接获取结构体变量可能会造成无所谓的拷贝
	PersonInfo* p = &addr_book->person_infos[id];
	printf("您要删除的元素是[%d]%s,输入Y表示确定\n", id, p->name);
	char cmd[1024] = { 0 };
	scanf("%s", cmd);
	if (strcmp(cmd, "Y") != 0)
	{
		printf("删除操作取消!\n");
		return;
	}

	//开始删除：
	//1.用最后一个元素覆盖要删除的元素
	PersonInfo* from = &addr_book->person_infos[addr_book->size - 1];
	PersonInfo* to = &addr_book->person_infos[id];
	*to = *from;//这种情况只需要搬用一个元素就可以

	//2.然后size--，减少有效区间
	--addr_book->size;
	printf("删除成功！\n");
}
void ModifyPersonInfo(AddressBook* addr_book)
{
	assert(addr_book != NULL);
	printf("对联系人进行修改！\n");
	printf("请输入要修改的记录序号：\n");
	int id = 0;
	scanf("%d", &id);
	if (id < 0 || id >= addr_book->size)
	{
		printf("您输入的序号有误！修改失败！\n");
		return;
	}
	PersonInfo* p = &addr_book->person_infos[id];
	printf("您要修改的记录为[%d]%s,确认请输入Y\n", id, p->name);
	char cmd[1024] = { 0 };
	scanf("%s", &cmd);
	if (strcmp(cmd, "Y") != 0)
	{
		printf("修改取消！\n");
		return;
	}
	char input[1024] = { 0 };
	printf("请输入修改之后的名字：（输入空字符串表示跳过）");
	scanf("%s", &input);
	if (strcmp(input, "") != 0)
	{
		strcpy(p->name, input);
	}

	printf("请输入修改之后的电话：（输入空字符串表示跳过）");
	scanf("%s", &input);
	if (strcmp(input, "") != 0)
	{
		strcpy(p->phone, input);
	}

	printf("请输入修改之后的公司：（输入空字符串表示跳过）");
	scanf("%s", &input);
	if (strcmp(input, "") != 0)
	{
		strcpy(p->company, input);
	}

	printf("请输入修改之后的地址：（输入空字符串表示跳过）");
	scanf("%s", &input);
	if (strcmp(input, "") != 0)
	{
		strcpy(p->address, input);
	}

	printf("修改成功！");
}

void FindPersonInfo(AddressBook* addr_book)
{
	assert(addr_book != NULL);
	printf("进行查找！\n");
	//当前只考虑按照姓名查找到方式
	printf("请输入要查找的姓名：");
	char name[1024] = { 0 };
	scanf("%s", name);
	for (int i = 0; i < addr_book->size; ++i)
	{
		PersonInfo* p = &addr_book->person_infos[i];
		if (strcmp(name, p->name) == 0)
		{
			printf("[%d]%s\t%s\t%s\t%s\n", i,
				p->name, p->phone, p->company, p->address);
		}//此处将所有的联系人都查找一遍
	}
	printf("查找成功！\n");
}
void SortPersonInfo(AddressBook* addr_book)
{
	assert(person_book != NULL);

	//按姓名排序，应用冒泡排序的方式写
	PersonInfo temp = { 0 };
	int num = 0;//[0,num]表示未排序区间，[num,size]表示已经排序的区间
	int i = (person_book->size) - 1;
	for (; num < person_book->size; ++num)
	{
		for (; i > num; --i)
		{
			//升序排序
			if (strcmp((person_book->book[i].name), (person_book->book[i - 1].name)) < 0)
			{
				//person_book->book[i + 1].name = person_book->book[i].name;
				temp = person_book->book[i - 1];
				person_book->book[i - 1] = person_book->book[i];
				person_book->book[i] = temp;
			}
		}
	}

	//打印出联系人
	for (; i < person_book->size; ++i)
	{
		PersonInfo* p = &person_book->book[i];
		printf("[%d]	%s\t%s\t%s\t%s\t%s\t%s\n",
			i, p->name, p->sex, p->age, p->phone, p->addrss, p->company);
	}
}

void PrintAllPersonInfo(AddressBook* addr_book)
{
	assert(addr_book != NULL);

	printf("显示所有的联系人信息！\n");

	PersonInfo* p = addr_book->person_infos;
	for (int i = 0; i < addr_book->size; ++i)
	{
		printf("[%d] %s\t%s\t%s\t%s\n", i, p[i].name, p[i].phone, p[i].address, p[i].company);
	}
	printf("显示完毕！共显示%d条记录\n", addr_book->size);
}

void ClearAllPersonInfo(AddressBook* addr_book)
{
	assert(addr_book != NULL);
	printf("清空所有联系人！\n");
	printf("您确定要清空所有么？Y表示确定\n");
	char name[1024] = { 0 };
	scanf("%s", &name);
	if (strcmp(name, "Y") != 0)
	{
		printf("清空操作取消！\n");
		return;
	}
	addr_book->size = 0;
	printf("清空成功！\n");
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

	//对元素进行初始化
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
			//此时说明用户输入非法
			printf("您的输入错误!请重新输入！\n");
			continue;
		}
		func_table[choice - 1](&g_addr_book);
	}

	return 0;
}
