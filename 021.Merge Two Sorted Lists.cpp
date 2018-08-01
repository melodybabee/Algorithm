/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL && l2 == NULL) return NULL;
        ListNode newlist(0);
        ListNode *move = &newlist;
        ListNode *p = l1;
        ListNode *q = l2;
        
        while(p != NULL && q != NULL){
            if(p -> val >= q -> val){
                move -> next = q;
                move = move -> next;
                q = q-> next;
            }
            else{
                move -> next = p;
                move = move -> next;
                p = p->next;
            }
        }
        
        if(p == NULL && q != NULL){
            move -> next = q;
        }
        
        if(q == NULL && p != NULL){
            move -> next = p;
        }
        
        return newlist.next;
        
    }
};
/*
splice 拼接
设计思路：
1.建立一个新的链表
2.比较l1与l2的大小，谁小连谁
3.若长度不同，直接把长的链表结尾接过来

注意：
1.新建链表！！！
ListNode newlist(0)；ListNode *move = &newlist; 其中0也可以写成NULL。
2.返回链表的时候要是 结点.next
3.判断结尾的两个if,可以改成move ->next = l1 ? l1 :l2;【这一步思路比较简洁】
*/