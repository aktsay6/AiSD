#include "gtest/gtest.h"
#include "linked_list.h"

using xi::LinkedList;
using xi::Node;



TEST(linked_list_tests, TestGetOperator) {
    LinkedList<int> list;
    int a;
    list.addElementToEnd(a = 2);
    list.addElementToEnd(a = 3);
    list.addElementToEnd(a = 4);

    ASSERT_THROW(list[-25], std::out_of_range);
    ASSERT_THROW(list[-1], std::out_of_range);
    ASSERT_EQ(list[0], 2);
    ASSERT_EQ(list[1], 3);
    ASSERT_EQ(list[2], 4);
    ASSERT_THROW(list[3], std::out_of_range);
    ASSERT_THROW(list[25], std::out_of_range);


    list.addElementToEnd(a = 5);
    ASSERT_EQ(list[3], 5);
    ASSERT_THROW(list[4], std::out_of_range);
}

TEST(linked_list_tests, MoveElemAfter)
{
    LinkedList<int> list;
    int a;
    list.addElementToEnd(a = 2);
    list.addElementToEnd(a = 3);
    list.addElementToEnd(a = 4);
    list.addElementToEnd(a = 5);

    LinkedList<int> copy(list); // 24 - 3 - 4 - 5 - 77 >>>>>>>> 24 - 5 - 3 - 4 - 5 - 77
    //  0   1   2   3   4            0   1   2   3   4    5   6
    copy[0] = 24;
    copy.addElementToEnd(a = 77);
    list[2] = 47; // 2 - 3 - 47 - 5 >>>>>>>> 2 - 3 - 47

    ASSERT_EQ(list.size(), 4);
    ASSERT_EQ(copy.size(), 5);

    ASSERT_EQ(2, list[0]);
    ASSERT_EQ(3, list[1]);
    ASSERT_EQ(47, list[2]);

    ASSERT_EQ(24, copy[0]);
    ASSERT_EQ(3, copy[1]);
    ASSERT_EQ(4, copy[2]);
    ASSERT_EQ(5, copy[3]);
    ASSERT_EQ(77, copy[4]);

    copy.moveNodeAfter(copy.getPreHead()->next, list.getPreHead()->next->next->next);
    // после copy[0] = 24 вставить list[3] = 5 и удалить list[3] = 5

    ASSERT_EQ(3, list.size());
    ASSERT_EQ(6, copy.size());
    ASSERT_EQ(5, copy[1]);
    ASSERT_EQ(3, copy[2]);
    ASSERT_EQ(2, list[0]);
    ASSERT_EQ(3, list[1]);
    ASSERT_EQ(47, list[2]);
}

TEST(linked_list_tests, MoveElementsAfter)
{
    LinkedList<int> list;
    int a;
    list.addElementToEnd(a = 2);
    list.addElementToEnd(a = 3);
    list.addElementToEnd(a = 4);
    list.addElementToEnd(a = 5);

    LinkedList<int> copy(list); // 24 - 3 - 4 - 5 - 77 >>>>>>>> 24 - 47 - 5 - 3 - 4 - 5 - 77
    //  0   1   2   3   4            0   1   2   3   4    5   6
    copy[0] = 24;
    copy.addElementToEnd(a = 77);
    list[2] = 47; // 2 - 3 - 47 - 5 >>>>>>>> 2 - 3

    ASSERT_EQ(list.size(), 4);
    ASSERT_EQ(copy.size(), 5);

    ASSERT_EQ(2, list[0]);
    ASSERT_EQ(3, list[1]);
    ASSERT_EQ(47, list[2]);

    ASSERT_EQ(24, copy[0]);
    ASSERT_EQ(3, copy[1]);
    ASSERT_EQ(4, copy[2]);
    ASSERT_EQ(5, copy[3]);
    ASSERT_EQ(77, copy[4]);

    copy.moveNodesAfter(copy.getPreHead()->next, list.getPreHead()->next->next, list.getPreHead()->next->next->next->next);
    //после copy[0] = 24 вставить list[2] = 47 - list[3] = 5 и удалить list[2] = 47 - list[3] = 5
    ASSERT_EQ(2, list.size());
    ASSERT_EQ(7, copy.size());
    ASSERT_EQ(47, copy[1]);
    ASSERT_EQ(5, copy[2]);
    ASSERT_EQ(2, list[0]);
    ASSERT_EQ(3, list[1]);
    EXPECT_THROW(list[2], std::out_of_range);
}

// will be enabled only if you decided to explicitly implement copy constructor and assign operator
// !!!do not define TEST_COPY_CONSTR_ASSIGN_OP in this file!!! it will be overwritten on the server
#ifdef TEST_COPY_CONSTR_ASSIGN_OP
TEST(linked_list_cc_ao, CopyConstructor) {
    LinkedList<int> list;
    int a;
    list.addElementToEnd(a = 2);
    list.addElementToEnd(a = 3);
    list.addElementToEnd(a = 4);
    
    LinkedList<int> copy(list);
    
    copy[0] = 24;
    copy.addElementToEnd(a = 77);
    list[2] = 47;
    
    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(copy.size(), 4);
    
    ASSERT_EQ(2, list[0]);
    ASSERT_EQ(3, list[1]);
    ASSERT_EQ(47, list[2]);
    
    ASSERT_EQ(24, copy[0]);
    ASSERT_EQ(3, copy[1]);
    ASSERT_EQ(4, copy[2]);
    ASSERT_EQ(77, copy[3]);
}


TEST(linked_list_cc_ao, AssignOperator) {
    LinkedList<int> list;
    int a;
    list.addElementToEnd(a = 2);
    list.addElementToEnd(a = 3);
    list.addElementToEnd(a = 4);
    
    LinkedList<int> copy;
    ASSERT_EQ(copy.size(), 0);
    
    copy = list = copy = list;
    
    copy[0] = 24;
    copy.addElementToEnd(a = 77);
    list[2] = 47;
    
    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(copy.size(), 4);
    
    ASSERT_EQ(2, list[0]);
    ASSERT_EQ(3, list[1]);
    ASSERT_EQ(47, list[2]);
    
    ASSERT_EQ(24, copy[0]);
    ASSERT_EQ(3, copy[1]);
    ASSERT_EQ(4, copy[2]);
    ASSERT_EQ(77, copy[3]);
}

#endif // TEST_COPY_CONSTR_ASSIGN_OP

TEST(linked_list_tests, CreatedEmptyList_HasSizeZero) {
    LinkedList<int> list;
    ASSERT_EQ(0, list.size());
}



TEST(linked_list_tests, AddingOneElementToEmptyList_HasSizeOne) {
    LinkedList<int> list;
    int inserted_element = 2;
    list.addElementToEnd(inserted_element);

    ASSERT_EQ(1, list.size());
}

TEST(linked_list_tests, AddingTwoElementsToEmptyList_HasSizeTwo) {
    LinkedList<int> list;
    int inserted_element = 2;
    list.addElementToEnd(inserted_element);

    int inserted_element_2 = 56;
    list.addElementToEnd(inserted_element_2);

    ASSERT_EQ(2, list.size());
}

TEST(linked_list_tests, AddingOneElementToEmptyList_ReturnFirstElement_ReturnsInsertedElement) {
    LinkedList<int> list;
    int inserted_element = 234;
    list.addElementToEnd(inserted_element);

    ASSERT_EQ(inserted_element, list.getPreHead()->next->value);
}

