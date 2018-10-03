本题的题意是两次反转操作。
第二遍复习的时候首先想到的是这种方法，因此思路更为符合题意思路的设定。但是会出现MLE的情况。
两次反转等于直接相加。注意想清楚如何处理链表长度不同的情况。

思路：
【1.0版】
1.取出两个链表中的数字，存成整数形式，存成a,b
2.将a,b相加为c
3.对c进行反转运算（取余除以10），存入新的linkedlist中
问题在于一般情况可以通过，但是当其中一个链表为0的时候不能满足，因为不需要反转（或者完成两次反转），而不是一次反转。

【2.0版】
1.新建一个链表，让原链表的每一位开始相加，取余存入新的链表中，除10，存到下一位
2.考虑非一般情况
（1）两个链表长度不同，判断下长度长的链表尾部元素
（2）如果最后有进位的情况需要单独考虑

注意：
1.在考虑好整体思路之后，需要考虑边界情况（按情况列出）
2.链表的操作：
（1）题目中给的ListNode* l1, ListNode* l2，是一个指针，指向所给的链表的第一个元素
（2）所给的原有的两个链表，最后一个元素后面的指针域会指向NULL
（3）ListNode(int x) : val(x), next(NULL) 的意思是如果ListNode(数值)，表示此位置数值域是一个数字，指针域指向NULL（可以用来添加新结点）
（4）新建链表： ListNode ret (0);为数值，还需要建立 ListNode *p = &ret;指向ret的指针，注意要对ret取地址
（5）在链表后面添加新的元素：p -> next = new ListNode(c%10);用指针添加new ListNode(数值)
3.a -> b = (*a).b。ret是结点，因此可以用ret.next表示ret的下一个节点
而a,b,p是指针，*p表示的是结点，因此需要用p->next; 类似，a->val,b ->val;
补充：
4.在链表中新建一个结点：ListNode ret (0);对ret下一位的操作是ret.next;
在链表中新建一个结点同时建立一个指向该结点的指针：ListNode * ret = new ListNode(0);ret下一位的操作是ret -> next;
注意区分声明的不同数据类型！！
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *a = l1;
        ListNode *b = l2;
        ListNode ret (0);
        ListNode *p = &ret;
        int c = 0;
        int ans = 0;
       
        while(a != NULL && b != NULL){
            c = a -> val + b -> val + ans;
            p -> next = new ListNode(c%10);
            ans = c/10;
            a = a->next;
            b = b->next;
            p = p->next;
            
        }
       
        while(a == NULL && b!= NULL ){
            int mid = b -> val +ans;
            p -> next = new ListNode(mid%10);
            ans = mid/10;
            b = b->next;
            p = p->next;
        }
        
        while(b == NULL && a!= NULL){
            int mid = a -> val +ans;
            p -> next = new ListNode(mid%10);
            ans = mid/10;
            a = a->next;
            p = p->next;
           
        }
        if (ans ==1){
            p -> next = new ListNode(ans);
        }
       
                       
        return ret.next;
        
    }
};


