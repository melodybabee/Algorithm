题意：
给链表的值+1,类似066给数组的值+1。
方法一：两次反转
思路：
1.因为涉及到进位问题，链表无法从右向左倒退处理，因此先把链表反转过来处理进位问题，后再反转回去即可。
2.链表反转除了可以提前设置一个NULL指针指向它以外，也可以设置一个dummy头结点，cur为链表第一个结点，每当cur -> next存在的时候，用pre更新cur -> next
cur -> next指向pre -> next;
pre -> next指向dummy -> next即头部位置；
最后把dummy一直更新到头部。
即一个一个向前移动到头部。
3.从头部开始+1，当前位上的值取余，除以10更新进位，如果进位为0，直接退出。
如果链表到尾部进位仍然为1，那么在尾部新加入一个值为1的结点。
4.最后从dummy结点开始再次反转链表。最后返回dummy -> next;
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
    ListNode* plusOne(ListNode* head) {
        ListNode *dummy = new ListNode(-1);
        dummy -> next = head;
        ListNode * cur = head;
        while(cur -> next){
            ListNode *pre  = cur->next;
            cur -> next = pre -> next;
            pre -> next = dummy -> next;
            dummy -> next = pre;
        }
        int count = 1;
        cur = dummy -> next;
        ListNode *pre = cur;
        while(cur){
            pre = cur;
            int total = cur -> val + count;
            cur -> val = total%10;
            count = total/10;
            if(count == 0 ) break;
            cur =  cur -> next;
        }
        if(count == 1) pre -> next = new ListNode(1);
        cur = dummy -> next;
        while(cur -> next){
            pre = cur -> next;
            cur -> next = pre -> next;
            pre -> next = dummy -> next;
            dummy -> next = pre ;
        }
        return dummy -> next;
    }
};
方法二：递归
思路：
1.用一个helper函数对链表进行递归，递归到链表的最后一位，如果不存在某结点的时候就返回1.
2.在当前的值的基础上+1，做取余和除以10的操作，返回到其前一位递归的位置。
3.最后在主函数中如果进位为1，那么在头部增加一个新的结点。如果不为1，直接返回头结点即可。
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
    ListNode* plusOne(ListNode* head) {
        if(!head) return head;
        int count = helper(head);
        if(count == 1){
            ListNode *pre = new ListNode(1);
            pre -> next = head;
            return pre;
        }
        return head;
    }
    int helper(ListNode*head){
        if(!head) return 1;
        int count = helper(head -> next);
        int temp = head -> val + count;
        head -> val = temp%10;
        temp /=10;
        return temp;
    }
};
方法三：用栈实现方法二的递归
思路：
1.设置一个栈，用于把链表中的结点逐个push到栈中，直到到最后一个结点
2.出栈，依次+1，进位，取余，除以10
3.最后如果有进位，加入一个新结点，返回
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
    ListNode* plusOne(ListNode* head) {
        stack<ListNode*>s;
        ListNode*p = head;
        while(p){
            s.push(p);
            p = p -> next;
        }
        int count = 1;
        while(!s.empty() && count){
            ListNode *cur = s.top();
            s.pop();
            int temp = cur -> val + count;
            cur -> val = temp%10;
            count = temp /10;
        }
        if(count){
        ListNode *fir = new ListNode(1);
        fir -> next = head;
        return fir;
        }
        return head;
    }
};
方法四：
思路：
1.找到链表中最靠右第一位不为9的结点，把这个结点+1，如果其后面还有元素，那么一定是9，直接把其后面的所有元素变为0即可。
2.如果没有这个元素，那么说明都是9，因此在头部新建一个结点，指向head。把新建的值+1，其后面所有的值变为0。
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
    ListNode* plusOne(ListNode* head) {
        ListNode *p = head;
        ListNode *right = NULL;
        while(p){
            if(p -> val != 9) right = p;
            p = p -> next;
        }
        if(!right){
            right = new ListNode(0);
            right->next = head;
            head = right;
        }
        ++right -> val;
        p = right -> next;
        while(p){
            p -> val = 0;
            p = p -> next;
        }
        return head;
    }
};