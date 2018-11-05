题意：
把链表重新排序。
思路：
1.本题分为3步，首先快慢指针找到链表的中点，分离链表。fast的范围需要二次检查。
2.把后半部分链表反转。注意反转过程中设置一个空指针和记录下一个结点的指针，为了把头结点指向空，同时对下一个结点继续进行该操作。
3.再在前半部分链表中逐一插入后半部分链表。本题直接返回head指针，直接在head上操作就可以。要记录head -> next的位置。
4.注意链表指针的移动出了指向还可以直接用到相等，比如反转过程中pre = cur;最后移动过程中head = next;
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
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return;
        ListNode *fast = head;
        ListNode *slow = head;
        while(fast->next && fast -> next -> next){
            fast = fast -> next -> next;
            slow = slow -> next;
        }
        ListNode *cur = slow -> next;
        slow -> next = NULL;
        ListNode *pre = NULL;
        while(cur){
            ListNode* temp = cur -> next;
            cur -> next = pre;
            pre = cur;
            cur = temp;
        }
        while(head && pre){
            ListNode *next = head->next;
            head->next = pre;
            pre = pre->next;
            head->next->next = next;
            head = next;
            
        }
        
    }
};