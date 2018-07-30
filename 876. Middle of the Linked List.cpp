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
    ListNode* middleNode(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast != NULL && fast->next != NULL){
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        
        return slow;
        
        
    }
};
/*
serialization 序列化

设计思路：
1.在链表头部和尾部分别建立双指针
2.头部指针向后移动，尾部指针向前移动，直到值相等或者head->next的值与last相等时，返回last
思路的问题在于：
1.首先无法声明last指针的位置（解决办法，可以先让last指针遍历整个链表）
2.第二个问题是无法使指针向前移动（解决办法：换一个思路）

优化：
method 1:（也叫floyd’s cycle-finding algorithm，龟兔赛跑算法，后面完整学习下）
1.可以设置快指针和慢指针，每次快指针移动2格，慢指针移动1格
2.需要注意边界条件，即在什么情况下停止（单数和双数的情况不同）

method 2:
也可以首先用一个指针遍历链表，记下链表长度，在循环至链表长度的二分之一位置处（时间复杂度较高）

注意： while(fast != NULL && fast->next != NULL)一句的顺序不能颠倒，因为如果先写fast->next，会出现fast->next不存在的情况，runtime error

*/