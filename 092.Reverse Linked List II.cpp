题意：
把链表在指定位置反转。
思路：
1.需要以下几个指针：
last:记录下反转链表的最后一个位置，也就是原序链表第一个需要反转的位置，用于指向原链表中不被循环的后半部分。
pre:用于指向被反转的链表的之前一个元素，用于固定头部元素，最后指向被反转的链表头部
cur为反转链表的第一个起点位置
2.根据指定位置的起点，把指针移动到起点位置的前一位，last指向起点位置，pre指向起点的前一位
3.开始反转链表，cur每次表示需要反转的位置，反转位置指向NULL,pre -> next指向当前位置的下一位，更新反转链表的头结点
4.最后把last -> next指向pre -> next, 把pre -> next指向反转链表的头部
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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *dummy = new ListNode(-1);
        dummy -> next = head;
        ListNode *pre = head;
        ListNode *front = NULL;
        ListNode *last = dummy;
        ListNode *cur = last;
        for(int i = 1; i <= m-1; ++i){
            cur = cur -> next;
        }
        last = cur -> next;
        pre = cur;
        for(int i = m; i <= n; ++i){
            cur = pre -> next;
            pre -> next = cur -> next;
            cur -> next = front;
            front = cur;
        }
        last -> next = pre -> next;
        pre -> next = front;
        return dummy -> next;
    }
};