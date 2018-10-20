题意：
用nlogn的时间复杂度来合并链表。
方法：归并排序
思路：
1.因为要求nlogn的时间复杂度，所以满足这种规模复杂度的只有快速排序，归并排序和堆排序。那么这道题用链表来解答用到了归并排序。
2.首先用快慢指针拆分原链表，注意技巧：
进入while循环的时候需要判断fast和fast->next是否都存在。
因为如果链表长度为奇数，那么会停在最后位置，没有fast->next;而如果链表长度为偶数，那么fast会直接到尾部null的位置，没有fast;
用一个pre指针记录slow前一个位置。这样循环结束时pre指向空，那么两个子链表的头部分别是head和slow,进入递归。
3.只要有递归就需要有递归的边界条件，当头结点不存在或者只有一个头结点的时候返回头结点。
4.接下来进入merge方法，思路和024完全一样，两链表汇合，注意判断长度，把长的链表接上。
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
    ListNode* sortList(ListNode* head) {
        if(!head || !head -> next) return head;
        ListNode *fast = head;
        ListNode *slow = head;
        ListNode *pre = head;
        while(fast && fast->next){
            pre = slow;
            fast = fast -> next -> next;
            slow = slow -> next;
        }
        pre -> next = NULL;
        return merge(sortList(head),sortList(slow));
    }
    ListNode* merge(ListNode*l1, ListNode*l2){
        ListNode *dummy = new ListNode(-1);
        ListNode *cur = dummy;
        while(l1 && l2){
            if(l1 -> val < l2 -> val){
                cur -> next = l1;
                l1 = l1 -> next;
            }else{
                cur -> next = l2;
                l2 = l2 -> next;
            }
            cur = cur -> next;
        }
        if(l1) cur -> next = l1;
        if(l2) cur -> next = l2;
        return dummy -> next;
    }
};