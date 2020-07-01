#ifndef _ADLIST_H
#define _ADLIST_H

#include <cstddef>
#include <cstdlib>

class ListNode{
public:
    ListNode *prev;
    ListNode *next;
    void *value;
   
    ListNode();
};

class ADList {
public:
    ADList();
    ADList(const ADList &ad);
    ~ADList();
    void InsertNode(ListNode* node, void *value, int8_t after);
    void AddNodeHead(void *value);
    void AddNodeTail(void *value);
    ListNode* SearchKey(void *key);
    ListNode* Index(int32_t index);
    void DeleteNode(ListNode *node);
    void Rewind();
    void RewindTail();
    void RotateTailToHead();
    void RotateHeadToTail();

    ListNode *tail;
    ListNode *head;
    size_t len;
    void* (*dup)(void *value);
    void (*free)(void *value);
    int (*match)(void *value, void *key);
};

#endif
