题意：
024加强版，给定一个数字k,反转链表内以k为周期的所有子链表
思路：
1.思路和025两两反转链表相似，不同之处是需要在一个周期内多次反转
2.首先得到链表长度，如果周期k大于链表长度，直接返回head
3.进入循环用三个指针执行反转操作，一次反转两个元素，如果k>2,那么会一直执行反转操作
pre 需要反转的结点的前一个准备元素，从它下一位开始为周期的起点
test 周期的起点，每次反转需要向后连接的结点
temp 开始在后面，每次反转需要向前走的点
4.一个周期结束后需要把pre更新到下一个周期的前一个结点的位置，即test处，因为此时test是上一个周期的最后一个结点
5.链表的长度值减去一个周期
6.在内部循环中，因为如果k为2,循环1次，因此i从1开始循环
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *dummy = new ListNode(-1);
        ListNode *pre = dummy;
        dummy -> next = head;
        ListNode *test = dummy;
        int count = 0;
        while(test -> next != NULL){
            ++count;
            test = test -> next;
        }
        if(count < k) return head;
        while(count >= k){
            test = pre -> next;
            for(int i = 1; i < k; ++i){
                ListNode *temp = test -> next;
                test -> next = temp -> next;
                temp -> next = pre -> next;
                pre -> next = temp;
            }
            pre = test;
            count -=k;
        }
        
        return dummy -> next;
        
    }
};