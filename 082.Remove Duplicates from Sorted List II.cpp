题意：
删除链表中所有重复的元素
思路：
1.从头部开始设置一个pre结点，一个当前结点。用当前结点去遍历链表，遇到重复的向后移动。
2.直到不重复的时候如果不是紧邻着的，说明有cur遍历过重复的结点，那么pre->next = cur ->next;
3.如果是紧邻着的说明不重复，那么直接把pre向后移动即可。
4.返回dummy -> next;
5.思路的重点在于用一个cur指针为pre探路，重复的话不断向前移动，不重复就把pre移动过去。
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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *dummy = new ListNode(-1);
        dummy -> next = head;
        ListNode *pre = dummy;
        while(pre -> next){
            ListNode *p = pre -> next;
            while(p-> next && p -> next -> val == p -> val){
                p = p -> next;
            }
            if(p != pre -> next) pre -> next = p->next;
            else pre = pre -> next;
        }
        return dummy -> next;
    }
};