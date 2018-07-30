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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *p = head;
        if(p == NULL) return NULL;
        while(p -> next){
            if(p -> val == p -> next ->val){
                 p -> next = p-> next -> next;
            }
            else{
                p = p -> next;
            }
        }
        
        return head;
        
    }
};

/*
设计思路：
1.创建一个p指针指向head，如果p->next的值与p的值相等，将P指向p->next->next;
2.再将p移动到p->next的位置;

注意：
1.需要判断p->next是否存在的情况，如果是2，3，3的情况，p ->next为结尾元素，p->next->next为NULL（在开头结构体中已经给出），因此循环结束，不需要单独判断
2.还可以改进成  *p = *(p -> next);
上面的语法表示为：
p = p -> next;//p先移动到下一个位置a
p -> val = p -> next ->val;//将a位置的下一位的值赋给p,因为最后一位指向NULL,因此最后会以NULL结尾

3.指针的移动不可以用p++;
4.判断指针是否为空，直接用p==NULL;
*/