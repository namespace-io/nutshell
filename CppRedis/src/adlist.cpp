#include "adlist.h"


ListNode::ListNode():prev(nullptr),next(nullptr),value(nullptr){}
ListNode::~ListNode(){
}



ADList::ADList():head(nullptr), tail(nullptr), len(0), dup(nullptr), free(nullptr), match(nullptr){

}

void ADList::InsertNode(ListNode *node, void *value, int8_t after){
    ListNode *newNode = new ListNode();
    newNode->value = value;
    if(len == 0 && node == nullptr){
        head = tail = newNode;
        newNode->prev = newNode->next = nullptr;
        len += 1;
        return ;
    }
    if(after > 0){
        newNode->next = node->next;
        newNode->prev = node;
        if(node == tail){
            tail = newNode;
        }

    } else {
      
        newNode->prev = node->prev;
        newNode->next = node;
        if(node == head){
            head = newNode;
        }

    }

    if(newNode->prev != nullptr){
        newNode->prev->next = newNode;
    }

    if(newNode->next != nullptr){
        newNode->next->prev = newNode;
    }


    len += 1;
    return ;   
}


void ADList::AddNodeHead(void *value){
    InsertNode(head, value, 0);
}

void ADList::AddNodeTail(void *value){
    InsertNode(tail, value, 1); 
}

ListNode* ADList::SearchKey(void *key){
    for(ListNode* p = head; p != nullptr; p = p->next){
        if(match){
            if(match(p->value, key)){
                return p;
            }
        } else {
            if(p->value == key){
                return p;
            }
        }
    }

    return nullptr;
}


ListNode* ADList::Index(int32_t index){
    ListNode *n = nullptr;
    if(index < 0){
        index = (-index)-1;
        n = tail;
        while(index-- > 0 && n) n = n->prev; 
    } else {
        n = head;
        while(index-- > 0 && n) n = n->next;
    }

    return n;

}

void ADList::DeleteNode(ListNode *node){
    if(node->prev){
        node->prev->next = node->next;
    } else {
        head = node->next;
    }

    if(node->next){
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }

    if(free) free(node);
    delete node;
    len -= 1;
}

ADList::ADList(const ADList &ad){
    len = 0;
    dup = ad.dup;
    free = ad.free;
    match = ad.match;
    
    for(ListNode *p = head; p != nullptr; p = p->next){
        void *value;
        if(dup){
            value = dup(p->value);
        } else {
            value = p->value;
        }

        AddNodeTail(value);
    }
}