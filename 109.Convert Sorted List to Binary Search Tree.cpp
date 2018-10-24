题意：
通过给的链表形成一课二叉平衡搜索树，二叉平衡树是左右子树的高度差不大于1，且其子树也是二叉平衡树。
思路：
1.因为给定的链表是经过搜索的，因此找到链表的中点就是树的根结点
2.把链表一分为二，再进行递归即可
注意：
1.快慢指针找中点while循环的判断条件是while(fast->next && fast -> next->next)
2.每次跳出while循环都需要把快指针指向慢指针的下一位，作为第二段链表的起始位置，不能写作slow->next因为如果只有两个结点，pre和slow会都在头部，那么pre指向null之后slow也指向null
3.需要判断根结点的左结点是否存在，如果head本身就是slow的话，那么不存在左子树，直接递归右子树即可
4.递归的边界条件是不存在头结点返回null，只有一个头结点返回头结点，注意此时简历一个树结点即可
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return NULL;
        if(!head->next) return new TreeNode(head->val);
        ListNode*fast = head;
        ListNode*slow = head;
        ListNode *pre = slow;
        while(fast->next && fast -> next->next){
            pre = slow;
            fast = fast -> next->next;
            slow = slow -> next;
        }
        fast = slow -> next;
        pre->next = NULL;
        TreeNode *p = new TreeNode(slow->val);
        if(head != slow) p -> left = sortedListToBST(head);
        p -> right = sortedListToBST(fast);
        return p;
    }
};