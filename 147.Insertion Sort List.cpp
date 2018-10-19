题意：
链表的内部排序
思路：
1.首先为了方便处理头结点，一般首先都先会构造一个dummy结点来连接头结点，便于最后dummy->next的返回
2.链表的内部排序的整体思想是每次取出一个结点，与当前有序的结点大小进行比较并插入
3.head作为每次循环到的头结点，用temp保存下头结点下一位的地址
cur作为循环结点，每次进入while循环之后cur都会在dummy位置，即链表头部。
如果cur有next且cur下一位的值小于当前head的值，说明head应该执行插入操作，那么把cur后移到cur指向的值比head结点的值大的位置。
让head结点指向cur指向的值，即head指向比自己值大的结点。cur用来连接上head和dummy,head移动到下一位。
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
    ListNode* insertionSortList(ListNode* head) {
        ListNode* dummy = new ListNode(-1);
        ListNode* cur = dummy;
        while(head){
            ListNode* temp = head -> next;
            cur = dummy;
            while(cur -> next && cur -> next -> val < head -> val){
                cur = cur -> next;
            }
            head -> next = cur ->next;
            cur -> next = head;
            head = temp;
        }
        return dummy -> next;
    }
};