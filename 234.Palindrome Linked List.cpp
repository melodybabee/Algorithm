利用stack和快慢指针进行判断
T（O) = O(N), S(O) = O(N)
思路：
1.回文链表的特点是从中间开始循环，找到对应位置的值是否相等，首先想到会用到快慢指针，用快指针找到链表中点
2.快指针一次走一步，慢指针一次走两步，慢指针遍历过的结点入栈
3.每次入栈前需要判断快指针的next,next->next结点是否存在，不存在的时候慢指针指向的即为中点
4.需要注意链表的结点有可能是奇数个，或者偶数个，因此如果是fast->next不存在的情况，就需要先出栈一个元素
5.再用慢结点与栈内元素进行比较，移动一步出栈一个元素比较其值是否相等，一旦不等，false,如果slow已经循环到最后一位仍没有false,则为true
注意：
1.注意stack申请的类型，如果为链表结点类型，最后就需要比较slow和stack.top()的值是否相等，如果是int类型，入栈的要是结点的值
2.要判断head结点是否存在！！
3.如果为空或者是一个数字的话都是回文数字
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(!head) return true;
        ListNode* slow = head;
        ListNode* fast = head;
        stack<ListNode*> st;
        st.push(head);
        while(fast->next && fast -> next ->next){
            slow = slow -> next;
            fast = fast -> next -> next;
            st.push(slow);
        }
        if(!fast -> next) st.pop();
        while(slow -> next){
            ListNode* temp = st.top();
            slow = slow -> next;
            st.pop();
            if(temp->val != slow-> val) return false;
        }
        return true;
    }
};

优化：
T（O) = O(N), S(O) = O(1)
思路：
1.不用栈，slow循环到中点以后反转后半部分链表，再从head开始与slow进行比较
注意：
1.如果是12321的情况，中间的3不需要考虑，因为slow会停在3,反转后半部分21为12，再从head的12开始比较，slow如果结束就为结束，不需要管3
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(!head) return true;
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast->next && fast -> next ->next){
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        slow-> next = reverseList(slow -> next);
        slow = slow -> next;
        while(slow!= NULL){
            if(head->val != slow ->val) return false;
            head = head -> next;
            slow = slow -> next;
        }
        return true;
    }
    ListNode* reverseList(ListNode* head){
        ListNode* pre = NULL;
        while(head){
            ListNode* now = head -> next;
            head -> next = pre;
            pre = head;
            head = now;
        }
        return pre;
    }
};