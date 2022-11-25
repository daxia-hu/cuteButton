#ifndef LIST_H
#define LIST_H
#include "stdint.h"
/**
 * 节点类 
 */
typedef struct Node_t
{
	struct Node_t *next;
}Node;
/**
 * 链表类 
 */
typedef struct List_t
{
	Node head;
	Node tail;
}List;
//判断链表是否为空
#define LIST_EMPTY(list) ((list)->head.next == &((list)->tail))
typedef struct TestNode_t
{
    Node node;
    uint8_t num;
}Test_Node;
/**
 * @brief 链表初始化
 * @param list 链表对象的地址
 */
void List_Init(List *list);
/**
 * @brief 向指定链表中插入节点
 * @param node 待插入的节点
 * @param list 链表
 */
void List_Insert(Node *node,List *list);
#endif