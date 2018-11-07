题意：
把两个链表相加为一个新链表，类似369链表+1
方法一：stack
思路：
1.先把两个链表各自push入栈，栈不为空的时候依次输出顶部元素。
2.注意新建一个结点作为求和后的结果，再新建一个结点作为进位。
3.最后判断进位的值是否为0，为0输出其下一位，不为0的话直接输出。
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
        stack<int> st1;
        stack<int> st2;
        while(l1){
            st1.push(l1->val);
            l1 = l1 -> next;
        }
        while(l2){
            st2.push(l2->val);
            l2 = l2 -> next;
        }
        int count = 0;
        ListNode *cur = new ListNode(count);
        while(!st1.empty() || !st2.empty()){
            if(!st1.empty()){
                count += st1.top();
                st1.pop();
            }
            if(!st2.empty()){
                count += st2.top();
                st2.pop();
            }
            cur -> val = count%10;
            ListNode *t = new ListNode(count/10);
            t -> next = cur;
            cur = t;
            count /=10;
        }
        return cur -> val == 0 ? cur -> next :cur;
        
    }
};
方法二：类似369,判断值为9的结点单独处理即可
思路：
1.循环判断两个链表的长度，把链表1放在长的位置上
2.用一个新的结点去依次链接l1,如果不是9，那么把right指针放在当前结点上，right指针的含义表示该结点的位置上小于9，可以有+1的余地，其前面的所有结点不会涉及到进位问题。
3.当两个链表长度相等的时候开始从头部相加，如果和大于9，那么把right结点从它当前的位置到现在存在的位置依次+1,表示进位，再停留在cur的位置上
4.新建一个cur结点值为两个链表和的值。同样注意处理如果是9，right指针不移动，表示没有位置允许+1.
5.最后判断dummy结点的位置是否为0，为0返回其下一位，不为0返回dummy。
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
        int len1 = getLen(l1);
        int len2 = getLen(l2);
        int diff = abs(len1 - len2);
        if(len1 < len2) swap(l1,l2);
        ListNode * dummy = new ListNode(0);
        ListNode *cur = dummy;
        ListNode *right = cur;
        while(diff > 0){
            cur -> next = new ListNode(l1 -> val);
            if(l1 -> val != 9) right = cur -> next;
            cur = cur -> next;
            l1 = l1 -> next;
            --diff;
        }
        while(l1){
            int total = l1 -> val + l2 -> val;
            if(total > 9){
                total %= 10;
                ++right -> val;
                while(right -> next){
                    right -> next -> val = 0;
                    right = right -> next;
                }
                right = cur;
            }
            cur  -> next = new ListNode(total);
            if(total != 9) right = cur -> next;
            cur = cur -> next;
            l1 = l1->next;
            l2 = l2 -> next;
        }
        return (dummy -> val == 1) ? dummy : dummy -> next;
        
    }
    int getLen(ListNode *l){
        int n = 0;
        while(l){
            ++n;
            l = l -> next;
        }
        return n;
    }
};
方法三：递归
思路：
1.首先判断链表长度，把长的放在helper函数的第一位，用来处理长度不一样的情况。
2.调用helper函数，res结点用来计算循环到不同结点的和，post结点用来判断两个链表长度及是否已经到达尾部。因此res会保持在pos的前面。
3.当pos大于9的时候，post取余，res++，res指向post.
4.最后回到主函数的时候还需要再判断一次是否大于9，注意head结点的初始值为1，为了便于返回。
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
        int len1 = getLen(l1);
        int len2 = getLen(l2);
        ListNode * head = new ListNode(1);
        head -> next = len1 > len2 ? helper(l1,l2,len1-len2) : helper(l2, l1,len2-len1);
        if(head -> next -> val > 9){
            head -> next -> val %= 10;
            return head;
        }
        return head -> next;
    }
    ListNode *helper(ListNode *l1, ListNode *l2, int diff){
        if(!l1) return NULL;
        ListNode *res = (diff == 0)? new ListNode(l1 -> val + l2 -> val) : new ListNode(l1 -> val);
        ListNode *post = (diff == 0)? helper(l1 -> next, l2 -> next, 0) : helper(l1 -> next, l2, diff-1);
        if(post && post -> val > 9){
            post -> val %= 10;
            ++res -> val;
        }
        res -> next = post;
        return res;
    }
    int getLen(ListNode *l){
        int n = 0;
        while(l){
            ++n;
            l = l -> next;
        }
        return n;
    }
};