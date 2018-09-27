思路：
1.本题要求删除已给的结点，但是没有给完整的链表和头部结点，因此直接在结点上操作即可
注意：
1.将下一个结点先前移动一位，不仅要移动地址，还有移动地址
2.ret -> val = ret -> next ->val;
  ret ->next = ret ->next ->next;
  可以写成：
  *ret = *(ret ->next);
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
    void deleteNode(ListNode* node) {
        ListNode *ret = node;
        ret -> val = ret -> next ->val;
        ret ->next = ret ->next ->next;
    }
};