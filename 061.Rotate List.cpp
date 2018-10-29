题意：
根据指定值n旋转链表n次。
思路：
1.设置一个dummy头结点便于最后返回操作，p指针指向当前结点，pre指向p之前的结点
2.依次循环，当p不存在的时候把pre指向NULL,p->next = 头结点，注意是头结点不是head,因为head没有根据旋转同步更新
3.直到k=0的时候输出dummy->next
4.因为k值有可能非常大，因此需要首先计算出链表的长度,用k对链表的长度取余，即最小旋转次数。
计算链表长度的时候需要从1开始计数。
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
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head) return head;
        ListNode* dummy = new ListNode(-1);
        ListNode* cur = dummy;
        cur -> next = head;
        ListNode* p = head;
        ListNode* pre = cur;
        pre -> next  = p;
        int len = 1;
        while(p->next){
            ++len;
            p = p -> next;
        }
        p = head;
        k = k%len;
        while(k>0){
            while(p->next != NULL){
                pre = pre -> next;
                p = p->next;
            }
            pre->next = NULL;
            p -> next = cur -> next;
            cur ->next = p;
            pre = cur;
            --k;
        }
        return dummy -> next;
    }
};
优化：
还有一种思路是首先把链表连接成一个环，从头结点开始向后移动（链表长度-k%链表长度）个单位到达一个新结点，再断开链表即可。
class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        if (!head) return NULL;
        int n = 1;
        ListNode *cur = head;
        while (cur->next) {
            ++n;
            cur = cur->next;
        }
        cur->next = head;
        int m = n - k % n;
        for (int i = 0; i < m; ++i) {
            cur = cur->next;
        }
        ListNode *newhead = cur->next;
        cur->next = NULL;
        return newhead;
    }
};