#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int LTDataType;  // 定义链表节点存储的数据类型为整型

// 定义链表节点的结构体
typedef struct ListNode {
    LTDataType data;           // 数据域，存储节点的数据
    struct ListNode* front;    // 前驱指针，指向前一个节点
    struct ListNode* next;     // 后继指针，指向后一个节点
} ListNode;

// 创建一个新节点
ListNode* CreateNode(LTDataType value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));  // 分配内存给新节点
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");  // 如果内存分配失败，打印错误消息
        return NULL;
    }
    newNode->data = value;  // 设置新节点的数据
    newNode->front = newNode;  // 新节点的前驱指向自己
    newNode->next = newNode;  // 新节点的后继也指向自己，形成自环
    return newNode;  // 返回新创建的节点
}

// 初始化带头节点的双向循环链表
ListNode* InitList() {
    ListNode* phead = CreateNode(-1);  // 创建头节点，数据通常设置为-1或其他非法值以区分
    if (phead != NULL) {
        phead->front = phead;  // 头节点的前驱指向自己
        phead->next = phead;  // 头节点的后继也指向自己，确保循环链表的闭环
    }
    return phead;  // 返回头节点
}

// 在链表前端插入新节点
void ListPushFront(ListNode* phead, LTDataType value) {
    assert(phead);  // 断言头节点不为空

    ListNode* newNode = CreateNode(value);  // 创建新节点
    ListNode* front = phead->next;  // 获取头节点后的第一个节点

    phead->next = newNode;  // 头节点的下一个节点设置为新节点
    newNode->front = phead;  // 新节点的前驱设置为头节点

    newNode->next = front;  // 新节点的下一个节点设置为原来的第一个节点
    front->front = newNode;  // 原来的第一个节点的前驱设置为新节点
}

// 从链表前端删除节点
void ListPopFront(ListNode* phead) {
    assert(phead);  // 断言头节点不为空
    assert(phead->next != phead);  // 断言链表不是空的

    ListNode* front = phead->next;  // 获取要删除的节点（头节点后的第一个节点）
    ListNode* newFront = front->next;  // 获取要删除节点的下一个节点

    phead->next = newFront;  // 头节点的下一个节点更新为新的第一个节点
    newFront->front = phead;  // 新的第一个节点的前驱更新为头节点

    free(front);  // 释放原来第一个节点的内存
}

// 在链表尾部插入新节点
void ListPushBack(ListNode* phead, LTDataType value) {
    assert(phead);  // 断言头节点不为空

    ListNode* newNode = CreateNode(value);  // 创建新节点
    ListNode* tail = phead->front;  // 获取尾节点（头节点的前一个节点）

    newNode->next = phead;  // 新节点的下一个节点设置为头节点
    phead->front = newNode;  // 头节点的前驱设置为新节点

    tail->next = newNode;  // 尾节点的下一个节点设置为新节点
    newNode->front = tail;  // 新节点的前驱设置为尾节点
}

// 从链表尾部删除节点
void ListPopBack(ListNode* phead) {
    assert(phead);  // 断言头节点不为空
    assert(phead->next != phead);  // 断言链表不是空的

    ListNode* tail = phead->front;  // 获取尾节点
    ListNode* newTail = tail->front;  // 获取新的尾节点（尾节点的前一个节点）

    newTail->next = phead;  // 新尾节点的下一个节点设置为头节点
    phead->front = newTail;  // 头节点的前驱设置为新尾节点

    free(tail);  // 释放原尾节点的内存
}

// 在指定位置插入节点
void ListInsert(ListNode* pos, LTDataType value) {
    assert(pos);  // 断言指定位置的节点不为空

    ListNode* before = pos->front;  // 获取指定位置节点的前一个节点
    ListNode* newNode = CreateNode(value);  // 创建新节点

    before->next = newNode;  // 前一个节点的下一个节点设置为新节点
    newNode->front = before;  // 新节点的前驱设置为前一个节点

    newNode->next = pos;  // 新节点的下一个节点设置为指定位置的节点
    pos->front = newNode;  // 指定位置的节点的前驱设置为新节点
}

// 删除指定位置的节点
void ListErase(ListNode* pos) {
    assert(pos);  // 断言指定位置的节点不为空

    ListNode* before = pos->front;  // 获取指定位置节点的前一个节点
    ListNode* after = pos->next;  // 获取指定位置节点的后一个节点

    before->next = after;  // 前一个节点的下一个节点设置为后一个节点
    after->front = before;  // 后一个节点的前驱设置为前一个节点

    free(pos);  // 释放指定位置的节点内存
}

// 检查链表是否为空
bool isEmpty(ListNode* phead) {
    return (phead->next == phead && phead->front == phead);
}

// 获取链表中的元素个数
int ListSize(ListNode* phead) {
    assert(phead);  // 断言头节点不为空

    int count = 0;  // 初始化计数器
    ListNode* cur = phead->next;  // 从头节点的后一个节点开始遍历
    while (cur != phead) {  // 当当前节点不是头节点时，继续遍历
        count++;  // 计数器增加
        cur = cur->next;  // 移至下一个节点
    }
    return count;  // 返回元素个数
}


int main() {
    ListNode* list = InitList();  // 初始化链表

    // 向链表添加元素
    ListPushBack(list, 10);
    ListPushBack(list, 20);
    ListPushBack(list, 30);
    ListPushFront(list, 5);
    ListInsert(list->next->next, 15); // 插入元素到第二个位置

    // 打印链表
    printf("Current List Size: %d\n", ListSize(list));
    ListNode* temp = list->next;
    while (temp != list) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    // 删除操作
    ListPopFront(list);
    ListPopBack(list);
    ListErase(list->next);  // 删除第一个元素

    // 再次打印链表
    printf("Current List Size after deletions: %d\n", ListSize(list));
    temp = list->next;
    while (temp != list) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    // 检查链表是否为空
    printf("Is the list empty? %s\n", isEmpty(list) ? "Yes" : "No");

    return 0;
}