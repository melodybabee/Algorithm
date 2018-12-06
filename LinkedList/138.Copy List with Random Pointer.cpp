题意：
一个链表中的结点有next和random两个指针，复制出这个链表。
思路：
1.新建一个结点，同给定的head结点，设置两个指针分别从两个链表的头部同时移动。
但因为一个结点可以有两个指针，所有有可能后遍历到的指针在之前的遍历中已经创建，直接指向即可，不能再次创建。
所以需要一个hashtable记录下每个新创建的结点。key表示原链表中指向目标结点的指针，value表示指向新创建的结点的指针。
2.在每次进行创建之前首先判断当前位指针指向的地址是否存在于map中，如果存在，直接指向，如果不存在，创建新结点并把它存入map中。
注意：
1.不能用vector是因为vector中的count函数于map不同，vector中的count指出现了多少次，而不是存在不存在
2.map中count()函数表示在value列中是否存在某个元素，所以不管是next建立的还是random建立的，都被放在了value里，map.count()调用的是map中的值
3.复制链表的时候要新建结点进行赋值，再把指针指向目标结点
4.头指针需要提前放入map,记录下此时新链表的头结点，便于最后返回
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        RandomListNode* p = head;
        RandomListNode* q = new RandomListNode(head -> label);
        unordered_map<RandomListNode*,RandomListNode*> map;
        map[head] = q;
        while(p){
            if(p -> next){
                if(map.count(p -> next)) q->next = map[p -> next];
                else{
                    q->next = new RandomListNode(p->next->label);
                    map[p -> next] = q -> next;
                }
            }
            if(p -> random){
                if(map.count(p -> random)) q -> random = map[p -> random];
                else{
                    q -> random = new RandomListNode(p->random->label);
                    map[p -> random] = q -> random;
                }
            }
            p = p -> next;
            q = q -> next;
        }
        return map[head];
    }
};
优化：复制链表再拆分，减少空间复杂度
思路：
1.首先在每个结点后面复制原链表的next指针
2.再依照原结点的random来复制next指针中random的指向
3.最后拆分两个链表的next指针，因为random指针是分别复制的，没有交叉，因此不需要拆分
4.最后返回新链表即可
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        RandomListNode* cur = head;
        while(cur){
            RandomListNode *p = new RandomListNode(cur->label);
            p -> next = cur -> next;
            cur -> next = p;
            cur = p ->next;
        }
        cur = head;
        while(cur){
            if(cur -> random){
                cur -> next -> random= cur -> random -> next;
            }
            cur = cur -> next -> next;
        }
        cur = head;
        RandomListNode* ret = cur -> next;
        while(cur){
            RandomListNode * temp = cur -> next;
            cur -> next = temp -> next;
            if(temp->next)temp -> next = temp -> next ->next;
            cur = cur -> next;
        }
        return ret;
    }
};

12.6复习：
注意：
1.链表中有两个结点，那么需要建立一个hashtable用来存储已经建立好的结点，用原链表中的结点对应新链表中的结点
2.如果在原链表中指向的下一个结点已经能在map中找到，说明已经建立过，也有新的结点与其对应，那么直接连接即可
没有的话重新建立。
3.需要注意newlist会跟着链表的建立一起移动，和cur一样。
所以要不直接返回map中head对应的结点作为新的返回结点。要不新建一个结点记录下新建链表的头结点的位置，作为结果返回。
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        RandomListNode*cur = head;
        RandomListNode*newlist = new RandomListNode(cur ->label);
        RandomListNode*pre = newlist;
        unordered_map<RandomListNode*,RandomListNode*>map;
        map[cur] = pre;
        while(cur){
            if(cur->next){
                if(map.count(cur->next)) newlist->next = map[cur->next];
                else{
                    newlist -> next = new RandomListNode(cur ->next -> label);
                    map[cur->next] = newlist->next;
                }
            }
            if(cur->random){
                if(map.count(cur->random)) newlist->random = map[cur->random];
                else{
                    newlist -> random = new RandomListNode(cur ->random -> label);
                    map[cur->random] = newlist->random;
                }
            }
            cur = cur-> next;
            newlist = newlist -> next;
        }
        return pre;
    }
};