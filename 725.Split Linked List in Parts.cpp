题意：
把一个链表分成相等的几部分。如果不能均分，靠前组的长度要大于等于后面组的长度。如果组数过多，用null来填充。
061 follow up.
思路：
1.首先计算出链表的长度,用k除以长度得到每组中有gruop个结点，用k对长度取余，得到前temp组的长度需要+1
2.开始循环，如果结点存在且当前组数<k,把返回数组的第一位替换为根结点，根结点和根结点的前一位向后移动group个长度
注意如果temp>0,那么需要每次加1，写法就是(temp > 0),如果为真返回1，否则返回0。
pre指针指向空。继续下一次循环。
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
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        ListNode *cur = root;
        ListNode * pre = NULL;
        vector<ListNode*> ret(k,NULL);
        if(!root) return ret;
        int len = 1;
        int temp = 0;
        int group = 0;
        while(cur->next){
            ++len;
            cur = cur ->next;
        }
        cur = root;
        temp = len%k;
        group = len/k;
        for(int i = 0; root && i< k;++i,temp--){
            ret[i] = root;
            for(int j = 0; j < group + (temp > 0);j++){
                pre = root;
                root = root -> next;
            }
            pre -> next = NULL;
        }  
        return ret;
    }
};