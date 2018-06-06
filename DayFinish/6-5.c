#include "linklist.h"


LinkNode* LinkListCycleEntry (LinkNode* head){
    if(head == NULL){
        return NULL;
    }
    LinkNode* fast = head;
    LinkNode* slow = head;
   while(1){
        if(fast == slow){
            break;
        }
        fast = fast->next->next;
        slow = slow->next;
    }
    LinkNode* meet = fast;
    LinkNode* cur = head;
    while(1){
        if(meet == cur){
            break;
        }
        meet = meet->next;
        cur = cur->next;
    }
    return cur;
}
