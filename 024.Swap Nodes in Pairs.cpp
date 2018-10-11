题意；
反转链表中两个为一对，一对一对的结点
遍历法
思路：
1.设置一个dummy的头结点便于操作head中的头结点【技巧】
2.设置连个指针做交换，需要一个temp结点过渡，注意先需要把交换前的前指针next指向第三个结点，再把第二个结点移动到头部
3.一旦pre的next或者pre的next的next不存在的时候，返回dummy的下一个结点
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
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummy = new ListNode(-1);
        ListNode *pre = dummy;
        pre -> next = head;
        while(pre -> next && pre -> next -> next){
            ListNode*t = pre -> next -> next;
            pre -> next -> next = t -> next;
            t -> next = pre -> next;
            pre -> next = t;
            pre = t -> next;
        }
        return dummy -> next;
    }
};
递归法【待深入理解】用到了回溯的思想
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode *t = head->next;
        head->next = swapPairs(head->next->next);
        t->next = head;
        return t;
    }
};