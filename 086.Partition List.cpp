partition 划分
题意：
把链表中小于目标值的结点向前移动，大于等于目标值的结点向后移动进行划分，保持原顺序不变。
思路：
1.和082思路相同，设置一个探路结点负责和目标值进行大小比较。
2.如果小于目标值，那么pre指针正常向前移动；
3.新建一个结点，把所有大于等于目标值的结点单独拎出来形成一个新链表
4.最后在小于目标值的子链表后面连上新链表即为结果。
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
    ListNode* partition(ListNode* head, int x) {
        ListNode *dummy = new ListNode(-1);
        ListNode *pre = dummy;
        pre -> next = head;
        ListNode *temp = new ListNode(-1);
        ListNode *q = temp;
        while(pre -> next){
            ListNode *cur = pre -> next;
            if(cur -> val < x){
                pre = pre -> next;
                if(cur -> next)cur = cur -> next;
            }else{
                pre -> next = cur -> next;
                cur -> next = NULL;
                q -> next = cur;
                q = q -> next;
            }
        }
        pre -> next = temp -> next;
        return dummy -> next;
    }
};
思路2:
也可以把所有小于目标值的结点都向前移动。
首先找到第一个大于等于目标值的结点，后面循环的过程中把所有小于目标值的结点移动到这一位之前即可。
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
    ListNode* partition(ListNode* head, int x) {
        ListNode *dummy = new ListNode(-1);
        ListNode *p = dummy;
        p -> next = head;
        while(p -> next && p -> next -> val < x) p = p -> next;
        ListNode *cur = p;
        while(cur -> next){
            ListNode *q = cur -> next;
            if(q -> val < x){
                cur -> next = q -> next;
                q -> next = p -> next;
                p -> next = q;
                p = p -> next;
            }else{
               cur = cur -> next;
            }
        }
        
        return dummy -> next;
    }
};