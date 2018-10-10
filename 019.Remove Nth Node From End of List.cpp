题意：
删除从链表尾部开始指定的第n个元素
思路：
1.首先创建两个指针分别指向头部，用循环使第一个指针与第二个指针相隔n个距离
2.当第一个指针不为空的时候，就同时移动两个指针，这样当第一个指针指向NULL的时候，第二个指针正好指向目标结点
3.为了便于删除，可以当第一个指针的next为空的时候就停止，这样第二个指针的next结点就是需要删除的结点
4.定义一个temp指针，使第一个指针的next指向temp指针的next，删除temp,返回head
注意：
1.链表的题目需要格外注意边界条件
*指针以及指针的next是否已经达到链表尾部，从而越界
2.本题中的边界条件：
如果n本身小于0， 直接返回原链表
如果n为头结点，在第一次循环的时候判断p的next为空的时候n应该正为0
如果n的大小大于链表长度,那么第一次循环p的next为空的时候n还大于0，那么直接返回头部结点
3.常用技巧
使用dummy head来简化改变删除头指针的处理
运用双指针
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *p = head;
        ListNode *follow = head;
        if(n < 0) return head;
        while(n > 0){
            --n;
            if(n == 0 && p -> next == NULL) return head -> next;
            if(n > 0 && p -> next == NULL) return head;
            p = p -> next;
        }
        while(p->next != NULL){
            p = p -> next;
            follow = follow -> next;
        }
        ListNode *temp = follow -> next;
        follow -> next = temp -> next;
        delete(temp);
        
        return head;
    }
};