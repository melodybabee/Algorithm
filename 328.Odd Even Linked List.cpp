题意：
把链表中的所有奇数结点提前，偶数结点置后，返回新链表。
思路
1.用cur指针指向偶结点，pre指针指向奇结点
2.把奇结点的next指向偶结点的next,即奇结点提前到偶结点的前面。
cur和pre各自前进一步，即pre指向奇结点的末尾，cur指向新的偶结点。
注意中间需要一个tmp指针指向偶结点的第一个位置，为了便于之后的奇结点末尾的next指向。
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
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* cur = head->next;
        ListNode* pre = head;
        while(cur && cur -> next){
            ListNode *tmp = pre->next;
            pre -> next = cur -> next;
            cur -> next = pre -> next -> next;
            pre -> next ->next = tmp;
            cur = cur -> next;
            pre = pre -> next;
        }   
        return head;
    }
};