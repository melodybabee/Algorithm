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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return NULL;
        int lena = getlen(headA);
        int lenb = getlen(headB);
        if(lena > lenb){
            for(int i = 0; i < lena - lenb; ++i){
                headA = headA -> next;
            }
        }else{
            for(int i = 0; i < lenb - lena; ++i){
                headB = headB -> next;
            }
        }
        while(headA && headB && headA != headB){
            headA = headA -> next;
            headB = headB -> next;
        }
        return headA == headB ? headA : NULL;
    }
    int getlen(ListNode* n){
        int count = 0;
        while(n -> next){
            count++;
            n = n->next;
        }
        return count;
    }
};
/*
思路：
1.因为想要找到两个linklist的汇合点，如果有汇合，那么从汇合点到结尾都是重合的
2.因此首先可以找到两个链表的长度，将长的链表的头结点指针后移，使两者相等，再分别开始循环，如果有相等的点，return，如果直到结尾还没有相等的点，返回NULL
3.可以单独建一个找链表长度的方法，只要n -> next存在，计数器+1

注意：
1.因为有可能两个链表为空，因此需要首先判断是否存在，不存在直接返回NULL
*/
*******************************
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return NULL;
        ListNode *p = headA;
        ListNode *q = headB;
        
        while(p != q){
            p = p ? p->next : headB;//p存在吗？存在p -> next;不存在，到另一个链表的头部
            q = q ? q->next : headA;
        }
        return p;
    }
};
/*
优化：
1.分别在两个linklist的头部设定两个指针，如果走到末尾的话就接在另一个的linklist头部
2.这样的话两个指针走的总距离是两个linklist的长度之和，因此如果又汇合，会在汇合点相遇；如果没有汇合点，会在两个linklist的末尾NULL值处相遇
*/