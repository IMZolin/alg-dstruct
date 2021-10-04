#pragma warning(disable : 4996)
#include "gtest/gtest.h"
extern "C" {
#include "unrolled_list.h"
}

list_t* CreateHeadForTest(){
	list_t* head = (list_t*)malloc(sizeof(list_t));
	if (head != NULL)
	{
		head->N = 1;
		head->data[0] = 0;
		//head->data[1] = 1;
		//head->data[2] = 2;
		head->next = NULL;
		return head;
	}
	else
	{
		return NULL;
	}
}

list_t* PushListForTest(list_t* last)
{
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	if (tmp != NULL)
	{
		tmp->N = 0;
		tmp->next = NULL;
		last->next = tmp;
		return tmp;
	}
	else
	{
		return NULL;
	}
}

TEST(CreateHeadTest, TestAllocation)
{
	list_t* head = CreateHeadForTest();
	EXPECT_TRUE(head->next == NULL);
	EXPECT_TRUE(head != NULL);
	free(head);
}

TEST(PushlistTest, TestAllocation)
{
	list_t* head = CreateHeadForTest();
	list_t* tmp = PushList(head);
	EXPECT_TRUE(tmp->next == NULL);
	EXPECT_TRUE(tmp != NULL);
	free(head);
	free(tmp);
}

TEST(GetNthTest, Test)
{
	list_t* head = CreateHeadForTest();
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
	list_t* head = CreateHeadForTest();
	EXPECT_TRUE(PopList(head, 0) == NULL);
}

TEST(PopListTest, TestList)
{
	list_t* head = CreateHeadForTest();
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
	list_t* head = CreateHeadForTest();
	ASSERT_EQ(head, GetLastNode(head));
	free(head);
}

TEST(GetLastNodeTest, TestList)
{
	list_t* head = CreateHeadForTest();
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	//tmp = PushListForTest(head);
	tmp->N = 0;
	tmp->next = NULL;
	head->next = tmp;
	
	ASSERT_EQ(tmp, GetLastNode(head));
	free(tmp);
	free(head);
}

TEST(AddItemTest, TestHead)
{
	list_t* head = CreateHeadForTest();
	list_t* tmp = AddItem(head, 1);
	ASSERT_EQ(1, tmp->data[1]);
	free(head);
}

TEST(AddItemTest, TestList)
{
	list_t* head = CreateHeadForTest();
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	for (int i = 1; i < head->N + 2; i++)
	{
		tmp = AddItem(head, i);
	}
	ASSERT_EQ(5, tmp->data[0]);
	free(head);
}
TEST(FindNumberByKeyTest, TestHead)
{
	list_t* head = CreateHeadForTest();
	ASSERT_EQ(0, FindNumberByKey(head, 0));
}

TEST(FindNumberByKeyTest, TestError)
{
	list_t* head = CreateHeadForTest();
	ASSERT_EQ(ERROR, FindNumberByKey(head, 3));
}

TEST(QuantityItemsTest, TestHead)
{
	list_t* head = CreateHeadForTest();
	ASSERT_EQ(1, QuantityItems(head));
}

TEST(QuantityItemsTest, TestList)
{
	list_t* head = CreateHeadForTest();
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
	ASSERT_EQ(i+1, QuantityItems(head));
}

TEST(FindItemTest, TestHead)
{
	list_t* head = CreateHeadForTest();
	ASSERT_EQ(0, FindItem(head, 0));
}

TEST(FindItemTest, TestErrorNonNegative)
{
	list_t* head = CreateHeadForTest();
	ASSERT_EQ(ERROR, FindItem(head, -1));
}

TEST(FindItemTest, TestErrorLessNumber)
{
	list_t* head = CreateHeadForTest();
	ASSERT_EQ(ERROR, FindItem(head, 3));
}

TEST(DeleteItemTest, TestHead)
{
	list_t* head = CreateHeadForTest();
	head->data[1] = 1;
	head->N++;
	DeleteItem(head, 1);
	ASSERT_EQ(1, head->N);
}

TEST(DeleteItemTest, TestErrorNonNegative)
{
	list_t* head = CreateHeadForTest();
	ASSERT_EQ(ERROR, FindItem(head, -1));
}

TEST(DeleteItemTest, TestErrorLessNumber)
{
	list_t* head = CreateHeadForTest();
	ASSERT_EQ(ERROR, FindItem(head, 3));
}

TEST(IterationTest, TestHead)
{
	list_t* head = CreateHeadForTest();
	head->data[1] = 2;
	head->data[2] = 7;
	head->data[3] = 5;
	head->N = 4;
	ASSERT_EQ(5, Iteration(head, 7));
}

TEST(IterationTest, TestList)
{
	list_t* head = CreateHeadForTest();
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
}

TEST(IterationTest, TestErrorNoItem)
{
	list_t* head = CreateHeadForTest();
	head->data[1] = 2;
	head->data[2] = 7;
	head->data[3] = 5;
	head->N = 4;
	ASSERT_EQ(ERROR, Iteration(head, -3));
}

TEST(IterationTest, TestErrorNoNext)
{
	list_t* head = CreateHeadForTest();
	head->data[1] = 2;
	head->data[2] = 7;
	head->data[3] = 5;
	head->N = 4;
	ASSERT_EQ(ERROR, Iteration(head, 5));
}
int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}