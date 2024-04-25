#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int LTDataType;  // ��������ڵ�洢����������Ϊ����

// ��������ڵ�Ľṹ��
typedef struct ListNode {
    LTDataType data;           // �����򣬴洢�ڵ������
    struct ListNode* front;    // ǰ��ָ�룬ָ��ǰһ���ڵ�
    struct ListNode* next;     // ���ָ�룬ָ���һ���ڵ�
} ListNode;

// ����һ���½ڵ�
ListNode* CreateNode(LTDataType value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));  // �����ڴ���½ڵ�
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");  // ����ڴ����ʧ�ܣ���ӡ������Ϣ
        return NULL;
    }
    newNode->data = value;  // �����½ڵ������
    newNode->front = newNode;  // �½ڵ��ǰ��ָ���Լ�
    newNode->next = newNode;  // �½ڵ�ĺ��Ҳָ���Լ����γ��Ի�
    return newNode;  // �����´����Ľڵ�
}

// ��ʼ����ͷ�ڵ��˫��ѭ������
ListNode* InitList() {
    ListNode* phead = CreateNode(-1);  // ����ͷ�ڵ㣬����ͨ������Ϊ-1�������Ƿ�ֵ������
    if (phead != NULL) {
        phead->front = phead;  // ͷ�ڵ��ǰ��ָ���Լ�
        phead->next = phead;  // ͷ�ڵ�ĺ��Ҳָ���Լ���ȷ��ѭ������ıջ�
    }
    return phead;  // ����ͷ�ڵ�
}

// ������ǰ�˲����½ڵ�
void ListPushFront(ListNode* phead, LTDataType value) {
    assert(phead);  // ����ͷ�ڵ㲻Ϊ��

    ListNode* newNode = CreateNode(value);  // �����½ڵ�
    ListNode* front = phead->next;  // ��ȡͷ�ڵ��ĵ�һ���ڵ�

    phead->next = newNode;  // ͷ�ڵ����һ���ڵ�����Ϊ�½ڵ�
    newNode->front = phead;  // �½ڵ��ǰ������Ϊͷ�ڵ�

    newNode->next = front;  // �½ڵ����һ���ڵ�����Ϊԭ���ĵ�һ���ڵ�
    front->front = newNode;  // ԭ���ĵ�һ���ڵ��ǰ������Ϊ�½ڵ�
}

// ������ǰ��ɾ���ڵ�
void ListPopFront(ListNode* phead) {
    assert(phead);  // ����ͷ�ڵ㲻Ϊ��
    assert(phead->next != phead);  // ���������ǿյ�

    ListNode* front = phead->next;  // ��ȡҪɾ���Ľڵ㣨ͷ�ڵ��ĵ�һ���ڵ㣩
    ListNode* newFront = front->next;  // ��ȡҪɾ���ڵ����һ���ڵ�

    phead->next = newFront;  // ͷ�ڵ����һ���ڵ����Ϊ�µĵ�һ���ڵ�
    newFront->front = phead;  // �µĵ�һ���ڵ��ǰ������Ϊͷ�ڵ�

    free(front);  // �ͷ�ԭ����һ���ڵ���ڴ�
}

// ������β�������½ڵ�
void ListPushBack(ListNode* phead, LTDataType value) {
    assert(phead);  // ����ͷ�ڵ㲻Ϊ��

    ListNode* newNode = CreateNode(value);  // �����½ڵ�
    ListNode* tail = phead->front;  // ��ȡβ�ڵ㣨ͷ�ڵ��ǰһ���ڵ㣩

    newNode->next = phead;  // �½ڵ����һ���ڵ�����Ϊͷ�ڵ�
    phead->front = newNode;  // ͷ�ڵ��ǰ������Ϊ�½ڵ�

    tail->next = newNode;  // β�ڵ����һ���ڵ�����Ϊ�½ڵ�
    newNode->front = tail;  // �½ڵ��ǰ������Ϊβ�ڵ�
}

// ������β��ɾ���ڵ�
void ListPopBack(ListNode* phead) {
    assert(phead);  // ����ͷ�ڵ㲻Ϊ��
    assert(phead->next != phead);  // ���������ǿյ�

    ListNode* tail = phead->front;  // ��ȡβ�ڵ�
    ListNode* newTail = tail->front;  // ��ȡ�µ�β�ڵ㣨β�ڵ��ǰһ���ڵ㣩

    newTail->next = phead;  // ��β�ڵ����һ���ڵ�����Ϊͷ�ڵ�
    phead->front = newTail;  // ͷ�ڵ��ǰ������Ϊ��β�ڵ�

    free(tail);  // �ͷ�ԭβ�ڵ���ڴ�
}

// ��ָ��λ�ò���ڵ�
void ListInsert(ListNode* pos, LTDataType value) {
    assert(pos);  // ����ָ��λ�õĽڵ㲻Ϊ��

    ListNode* before = pos->front;  // ��ȡָ��λ�ýڵ��ǰһ���ڵ�
    ListNode* newNode = CreateNode(value);  // �����½ڵ�

    before->next = newNode;  // ǰһ���ڵ����һ���ڵ�����Ϊ�½ڵ�
    newNode->front = before;  // �½ڵ��ǰ������Ϊǰһ���ڵ�

    newNode->next = pos;  // �½ڵ����һ���ڵ�����Ϊָ��λ�õĽڵ�
    pos->front = newNode;  // ָ��λ�õĽڵ��ǰ������Ϊ�½ڵ�
}

// ɾ��ָ��λ�õĽڵ�
void ListErase(ListNode* pos) {
    assert(pos);  // ����ָ��λ�õĽڵ㲻Ϊ��

    ListNode* before = pos->front;  // ��ȡָ��λ�ýڵ��ǰһ���ڵ�
    ListNode* after = pos->next;  // ��ȡָ��λ�ýڵ�ĺ�һ���ڵ�

    before->next = after;  // ǰһ���ڵ����һ���ڵ�����Ϊ��һ���ڵ�
    after->front = before;  // ��һ���ڵ��ǰ������Ϊǰһ���ڵ�

    free(pos);  // �ͷ�ָ��λ�õĽڵ��ڴ�
}

// ��������Ƿ�Ϊ��
bool isEmpty(ListNode* phead) {
    return (phead->next == phead && phead->front == phead);
}

// ��ȡ�����е�Ԫ�ظ���
int ListSize(ListNode* phead) {
    assert(phead);  // ����ͷ�ڵ㲻Ϊ��

    int count = 0;  // ��ʼ��������
    ListNode* cur = phead->next;  // ��ͷ�ڵ�ĺ�һ���ڵ㿪ʼ����
    while (cur != phead) {  // ����ǰ�ڵ㲻��ͷ�ڵ�ʱ����������
        count++;  // ����������
        cur = cur->next;  // ������һ���ڵ�
    }
    return count;  // ����Ԫ�ظ���
}


int main() {
    ListNode* list = InitList();  // ��ʼ������

    // ���������Ԫ��
    ListPushBack(list, 10);
    ListPushBack(list, 20);
    ListPushBack(list, 30);
    ListPushFront(list, 5);
    ListInsert(list->next->next, 15); // ����Ԫ�ص��ڶ���λ��

    // ��ӡ����
    printf("Current List Size: %d\n", ListSize(list));
    ListNode* temp = list->next;
    while (temp != list) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    // ɾ������
    ListPopFront(list);
    ListPopBack(list);
    ListErase(list->next);  // ɾ����һ��Ԫ��

    // �ٴδ�ӡ����
    printf("Current List Size after deletions: %d\n", ListSize(list));
    temp = list->next;
    while (temp != list) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    // ��������Ƿ�Ϊ��
    printf("Is the list empty? %s\n", isEmpty(list) ? "Yes" : "No");

    return 0;
}