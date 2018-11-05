题意：
找到成环链表环的起点。
思路：
1.涉及到链表环的问题运用快慢指针来判断相遇位置。因为快慢指针的步数差为1，如果快指针想要超过慢指针，那么在超过之前必相遇。
注意对于快结点判断fast && fast -> next是否存在即可。
2.首先while循环找到相遇位置，相遇时跳出。如果fast到链表尾部仍然没有相遇，那么返回NULL
3.相遇后把其中一个结点放到head位置，两个指针分别一步一步走，再相遇的位置就是环的起始位置。
解释：
设从头部到相遇位置s的长度是L，环的周长为C，第一次相遇的位置是m,从环起始位置到相遇的距离是X。
快指针走的路程是慢指针的2倍。
L+n*C+X = 2(L+X),其中n为快指针转的圈数，可为任意值。
那么L = n*C - X;即从相遇点走到起始位置的长度等于从head走到起始位置的长度，因此可以有上述操作。
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
    ListNode *detectCycle(ListNode *head) {
        if(!head) return NULL;
        ListNode *fast = head;
        ListNode *slow = head;
        int count = 0;
        while(fast && fast -> next){
            slow = slow -> next;
            fast = fast -> next -> next;
            if(fast == slow) break;
        }
        if(!fast || !fast -> next) return NULL;
        slow = head;
        while(slow != fast){
            slow = slow -> next;
            fast = fast -> next;
        }
        return fast;
    }
};
优化：
可以把slow的移动放在while循环中，如果都不满足返回NULL
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
    ListNode *detectCycle(ListNode *head) {
        if(!head) return NULL;
        ListNode *fast = head;
        ListNode *slow = head;
        while(fast -> next && fast -> next -> next){
            slow = slow -> next;
            fast = fast -> next -> next;
            if(fast == slow){
                slow = head;
                while(slow != fast){
                    slow = slow -> next;
                    fast = fast -> next;
                    }
                return slow;
            }
       
        }
        return NULL;
    }
};