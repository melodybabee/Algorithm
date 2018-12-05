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
4.接下来进入merge方法，思路和021完全一样，两链表汇合，注意判断长度，把长的链表接上。
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

12.4复习：
方法一：插入排序
1.如果没有题目中的时间复杂度要求，第一反应肯定是插入排序，时间复杂度O(n) = O(n^2);
2.依次循环链表进行比较，如果后面的结点比前面的结点小，需要再从dummy后面进行比较，插入到合适的位置。
注意：
1.只要涉及p -> next的问题，就需要考虑p->next是否都存在。
2.分清各个指针是什么用途，画图验证即可。
本题：
temp用来确定后面的结点插入的位置的值
pre表示当前遍历到的结点
cur记录原有的链表顺序不被破坏，便于pre插入到新的位置之后还能返回
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
        if(!head) return NULL;
        ListNode *dummy = new ListNode(-1);
        ListNode *temp = dummy;
        dummy -> next = head;
        ListNode *pre = head;
        ListNode *cur = head;
        while(pre -> next){
            cur = pre;
            pre = pre -> next;
            if(pre-> val < cur ->val){
                cur ->next = pre -> next;
                while(pre -> val > temp ->next -> val){
                    temp = temp -> next;
                }
                pre -> next = temp -> next;
                temp -> next = pre;
                temp = dummy;
                pre = cur;
            }
        }
        return dummy -> next;
    }
};
方法2:归并排序
1.首先用快慢指针找链表中点，注意判断条件是fast 和fast -> next都存在的时候，快走两步，慢走一步。
需要用一个指针来记录下slow当前的位置，作为前半部分链表的结尾，找到中点之后指向NULL。
slow作为后半部分链表的头结点。
2.开始递归把每一个链表分成两部分，直到只有一个结点为止。再用021的方法依次汇合链表。
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
        if(!head || !head->next) return head;
        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *pre = head;
        while(fast && fast -> next){
            pre = slow;
            fast = fast -> next -> next;
            slow = slow -> next;
        }
        pre -> next = NULL;
        return merge(sortList(head),sortList(slow));
    }
    
    ListNode* merge(ListNode*l1, ListNode*l2){
        ListNode *dummy = new ListNode(-1);
        ListNode *temp = dummy;
        while(l1 && l2){
            if(l1 -> val <= l2 -> val){
                temp -> next = l1;
                l1 = l1 -> next;
            }else{
                temp -> next = l2;
                l2 = l2 -> next;
            }
            temp = temp -> next;
        }
        if(l1) temp -> next = l1;
        if(l2) temp -> next = l2;
        return dummy -> next;
    }
};

