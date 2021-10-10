#pragma warning(disable : 4996)
#include "gtest/gtest.h"
extern "C" {
#include "unrolled_list.h"
}

TEST(CreateHeadTest, TestAllocation)
{
	
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	head->next = NULL;
	EXPECT_TRUE(head->next == NULL);
	EXPECT_TRUE(head != NULL);
	DestroyList(head);
}

TEST(PushlistTest, TestAllocation)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	PushList(head,1);
	EXPECT_TRUE(head->next != NULL);
	EXPECT_TRUE(head != NULL);
	DestroyList(head);
}

TEST(GetNthTest, Test)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	tmp->data[0] = 1;
	tmp->N = 1;
	head->next = tmp;
	list_t* buf = (list_t*)malloc(sizeof(list_t));
	buf->data[0] = 2;
	buf->N = 1;
	buf->next = NULL;
	tmp->next = buf;
	ASSERT_EQ(GetNth(head, 2), buf);
}

TEST(PopListTest, TestHead)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	head->next = NULL;
	EXPECT_TRUE(PopList(head, 0) == NULL);
}

TEST(PopListTest, TestList)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	list_t* prev = (list_t*)malloc(sizeof(list_t));
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	list_t* buf;

	head->next = prev;
	prev->N = 1;
	prev->data[0] = 3;
	prev->next = NULL;
	prev->next = tmp;
	tmp->N = 1;
	tmp->data[0] = 1;
	tmp->next = NULL;
	buf = PopList(head, 1);

	EXPECT_TRUE(buf != NULL);
	EXPECT_TRUE(buf->next != NULL);
	ASSERT_EQ(head, buf);
	ASSERT_EQ(tmp, buf->next);
}

TEST(GetLastNodeTest, TestHead)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	head->next = NULL;
	ASSERT_EQ(head, GetLastNode(head));
	DestroyList(head);
}

TEST(GetLastNodeTest, TestList)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	tmp->N = 0;
	tmp->next = NULL;
	head->next = tmp;

	ASSERT_EQ(tmp, GetLastNode(head));
	DestroyList(tmp);
}

TEST(AddItemTest, TestHead)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	head->next = NULL;
	AddItem(head, 1);
	EXPECT_TRUE(head->data[1] = 1);
}

TEST(AddItemTest, TestList1)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	head->next = NULL;
	for (int i = 1; i < ARRAY_SIZE+1; i++)
	{
		AddItem(head, i);
	}
	EXPECT_TRUE(head->next != NULL);
}

TEST(AddItemTest, TestList2)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;	
	tmp->N = 2;
	head->next = tmp;
	tmp->next = NULL;
	tmp->data[0] = 4;
	tmp->data[1] = 3;
	AddItem(head, 2);
	ASSERT_EQ(2, head->data[1]);
}

TEST(FindNumberByKeyTest, TestHead)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	head->next = NULL;
	ASSERT_EQ(0, FindNumberByKey(head, 0));
	DestroyList(head);
}

TEST(FindNumberByKeyTest, TestError)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	head->next = NULL;
	ASSERT_EQ(ERROR, FindNumberByKey(head, 3));
	DestroyList(head);
}

TEST(QuantityItemsTest, TestHead)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	head->next = NULL;
	ASSERT_EQ(1, QuantityItems(head));
	DestroyList(head);
}

TEST(QuantityItemsTest, TestList)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	int i;
	tmp->next = NULL;
	head->next = tmp;
	tmp->N = 0;
	for (i = 0; i < 4; i++)
	{
		tmp->data[i] = i;
		tmp->N++;
	}
	ASSERT_EQ(i + 1, QuantityItems(head));
	DestroyList(head);
}

TEST(FindItemTest, TestHead)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	head->next = NULL;
	ASSERT_EQ(0, FindItem(head, 0));
	DestroyList(head);
}

TEST(FindItemTest, TestErrorNonNegative)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	head->next = NULL;
	ASSERT_EQ(ERROR, FindItem(head, -1));
	DestroyList(head);
}

TEST(FindItemTest, TestErrorLessNumber)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->N = 1;
	head->data[0] = 0;
	head->next = NULL;
	ASSERT_EQ(ERROR, FindItem(head, 3));
	DestroyList(head);
}

TEST(DeleteItemTest, TestHead1)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->data[0] = 0;
	head->data[1] = 1;
	head->N = 2;
	head->next = NULL;
	DeleteItem(head, 1);
	ASSERT_EQ(1, head->N);
	DestroyList(head);
}

TEST(DeleteItemTest, TestHead2)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->data[0] = 0;
	head->next = NULL;
	head->N = 1;
	for (int i = 1; i < ARRAY_SIZE; i++)
	{
		head->data[i] = i;
		head->N++;
	}
	DeleteItem(head, 5);
	EXPECT_TRUE(head->N == 4);
	DestroyList(head);
}

TEST(DeleteItemTest, TestListLastNode)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->data[0] = 0;
	head->N = 1;
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	for (int i = 1; i < ARRAY_SIZE; i++)
	{
		head->data[i] = i;
		(head->N)++;
	}
	head->next = tmp;
	tmp->next = NULL;
	tmp->data[0] = 5;
	tmp->N = 1;
	ASSERT_EQ(head->N, 5);
	DeleteItem(head, 6);
	DestroyList(head);
}

TEST(DeleteItemTest, TestErrorNonNegative)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->data[0] = 0;
	head->N = 1;
	head->next = NULL;
	ASSERT_EQ(ERROR, FindItem(head, -1));
	DestroyList(head);
}

TEST(DeleteItemTest, TestErrorLessNumber)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->data[0] = 0;
	head->N = 1;
	head->next = NULL;
	ASSERT_EQ(ERROR, FindItem(head, 3));
	DestroyList(head);
}

TEST(IterationTest, TestHead)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->data[0] = 0;
	head->data[1] = 2;
	head->data[2] = 7;
	head->data[3] = 5;
	head->N = 4;
	head->next = NULL;
	ASSERT_EQ(5, Iteration(head, 7));
	DestroyList(head);
}

TEST(IterationTest, TestList)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->data[0] = 0;
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	head->data[1] = 2;
	head->data[2] = 7;
	head->data[3] = 5;
	head->data[4] = 1;
	head->N = 5;

	head->next = tmp;
	tmp->next = NULL;
	tmp->data[0] = 8;
	tmp->N = 1;
	ASSERT_EQ(8, Iteration(head, 1));
	DestroyList(head);
}

TEST(IterationTest, TestErrorNoItem)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->data[0] = 0;;
	head->data[1] = 2;
	head->data[2] = 7;
	head->data[3] = 5;
	head->N = 4;
	head->next = NULL;
	ASSERT_EQ(ERROR, Iteration(head, -3));
	DestroyList(head);
}

TEST(IterationTest, TestErrorNoNext)
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	head->data[0] = 0;
	head->next = NULL;
	head->data[1] = 2;
	head->data[2] = 7;
	head->data[3] = 5;
	head->N = 4;
	ASSERT_EQ(ERROR, Iteration(head, 5));
	DestroyList(head);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

