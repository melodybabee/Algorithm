/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //递归实现
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return true;
        if(!root) return true;
        return TwoNodes(root-> left, root ->right);
    }
        
    bool TwoNodes(TreeNode* p, TreeNode* q){
        if(!p && !q) return true;//p, q都不存在的意思，符号！的逻辑顺序在&&之上
        if(!p || !q) return false;
        if(p-> val != q -> val) return false;
            
        return TwoNodes (p -> left, q->right) && TwoNodes(p->right, q -> left);
    }
}；
/*
思路：
1.先判断root部分，是否存在，是否为空，从而判断是否对称
2.接着定义一个新方法，用left和right两个变量，递归实现，当p,q都不存在的时候返回true,一方空或者值不等的时候返回false
都不满足条件时进行不断递归

注意：
1.！的逻辑顺序要在&&之前
2.递归的过程需要判断跳出条件

*/
//非递归实现
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
    bool isSymmetric(TreeNode* root) {
        //if(root == NULL) return true;作用与下一行相同
        if(!root) return true;
        queue<TreeNode*> que;
        que.push(root -> left);
        que.push(root -> right);
        while(!que.empty()){
            TreeNode* p = que.front();
            que.pop();
            TreeNode* q = que.front();
            que.pop();
            if(!p && q) return false;
            if(p && !q) return false;
            if(p && q){
                if(p -> val != q -> val) return false;
                que.push(p -> left);
                que.push(q -> right);
                que.push(p -> right);
                que.push(q -> left);
                }
            }
        return true;
    }
};
/*
思路：
1.首先同样先判断根结点的情况，是否存在，不存在直接返回true
2.把跟结点的左右子结点放入queue中
3.用两个不同的指针分别取queue前两个位置的地址，取出一个后pop掉当前的
4.比较两个指针的地址，如果一个存在一个不存在或者都存在的情况下值不等，返回false
5.继续把子结点的子结点push到queue里，依次比较
6.当queue为空且没有遇到不满足条件的情况时，返回true

注意：
1.思路的卡顿点在于如何把新的子结点push到queue后面，应该按照左1左，右1右，左1右，右1左的顺序（可参考binary tree的数组）
2.只要用到p,q的值的情况，应该考虑p,q是否存在
3.当while循环结束之后，要最后返回true（考虑程序break的情况）
4.queue的思想时先进先出，因此可以从头部取到每一个结点的值，后面注意灵活应用这一特性，同时注意queue中存放的是tree的地址，指针指向的也是地址

优化：
1.需要将两个数据合并为一个，或者当一个函数需要返回两个数据的时候，可以选择pair
2.pair是一个结构体，包括first和second,
3.创建 pair<变量1的类型，变量2的类型>pair名称(变量1，变量2)；可在初始的时候赋值，也可以用make_pair()初始化，如果是数字的话，make_pair会把second值自动转为int
*/


//补充二叉树创建，DFS前中后序遍历递归和非递归，BFS遍历的知识。
#include <iostream>
#include <stack>
using std::cin;

//树的结构体
struct Node{
	int val;
	Node* left;
	Node* right;
	Node(int val): val(val); left(NULL); right(NULL){}
};

//构建二叉树
void CreateTree(Node* node, int value){//设立一个指向跟结点的指针node
	if(value <= node -> value){
		if（!node -> left){
		node -> left = new Node(value);
		}
		else{
			CreateTree(node -> left, value);//改变根node,从初始状态的node更改为原node的左结点
		}
	}

	else{
		if(!node -> right){
			node -> right = new Node(value);
		}
		else{
			CreateTree(node -> right, value);
		}
	}

}
//DFS,深度优先，即先找到左子树的最下面一个左结点，在开始
//先序遍历
//递归实现
void preOrder(Node *node){
	if(node){
		cout<< node->value << endl;
	}
	preorder(node -> left);
	preorder(node -> right);
}
//非递归实现
void preOrder1(Node *node){
	stack<Node *> st;//建立一个类型为Node *的stack, 用来存树中每个位置的地址
	Node *p = node;//p作为先序遍历过程中的移动指针，每次都输出
	while(p != NULL || !st.empty()){
		while(p!= NULL){
			cout << p -> value << endl;
			st.push(p);
			p = p -> left;
		}
	    if(!st.empty()){
	    	p = st.top();//返回栈顶元素
	    	st.pop();//移除栈顶元素
	    	p = p -> right;
	    }
	}
}

//中序遍历
//递归实现
void inOrder(Node *node){
	if(node != NULL){//首先要找到递归终止的条件
		inOrder (node -> left);
		cout << node -> value;
		inOrder (node -> right);
	}
}
//非递归实现
void inOrder1(Node *node){
	stack<Node*> st;
	Node *p = node;
	while(p != NUll || !st.empty()){
		while(p != null){
			st.push(p);
			p = p->left;
		}
		if(!st.empty()){
			st.top();
			cout << p -> val << endl;
			st.pop();
			p = p -> right;
		}
	}
}
//后序遍历
//递归实现
void postOrder(Node *node){
	if(node != NULL){
		postOrder(node ->left);
		postOrder(node -> right);
		cout << node -> val << endl;
	}
}
//非递归实现
void postOrder1(Node *node){
	stack<Node*> st;
	Node *p = node;
	Node *q = NULL;//存放上次访问的结点，因为后序遍历回到跟结点之后还需要判断有无右结点，直到没有右结点或者右结点已经被访问过的情况，才会输出跟结点
	while (p != NULL){//为了找到左子树的最下面一个左结点
		st.push(p);
		p = p ->left;
	}

	while (!st.empty()){
		p = st.top();
		st.pop();

		if(p-> right == NULL || p -> right == q){
			cout<< p -> val << endl;
			q = p;
		}
		else{
			st.push(p);
			p = p -> right;
			while(p){
				st.push(p);
				p = p -> left;//再次寻找到最下面的左结点，为NULL后从顶部开始输出栈
			}
		}
	}

}

//BFS 广度优先，进行层层遍历
void boardFirst(Node *node){
	if(!node) return;
	queue<Node*> que;
	que.push(node);
	while(!que.empty()){
		Node *p = que.front();//p永远指向queue的首元素,含义是首元素的地址，因此在不断更新
		cout << p -> val << end;
		que.pop();//pop指弹出队列的第一个元素，不会读取该元素的值，因此如果que不为空，会有新的元素到首位来
		if(p -> left){
			que.push(p -> left);
		}
		if(p -> right){
			que.push(p -> right);
		}
	}
}
//队列中，比如root, 1, 2，p首先会指向root,输出root的值之后会pop掉root, 此时p指向1的地址，输出1，判断树中1有无左右子树，有的话会接在queue里面的2后，接着p指向2，依次类推

//上述方法被调用的主函数
int main(){
	int n;
	while (cin >> n){
		n--;
		int value;
		cin >> value;//root结点上的值
		Node root(value);
		while(n--){
			int newValue;
			cin >> newValue;//需要插入的值
			CreateTree(&root, newValue);
		}
		cout << "preOrder is" << endl;
		preOrder(&root);
		cout << "inOrder is" << endl;
		inOrder(&root);
		cout << "postOrder is" << endl;
		postOrder(&root);
		cout << "preOrder with recursion is" << endl;
		preOrder1(&root);
		cout << "inOrder with recursion is" << endl;
		inOrder1(&root);
		cout << "postOrder with recursion is" << endl;
		postOrder1(&root);
		cout << "boardOrder is" << endl;
		boardFirst(&root);

	}
}


3.25复习：
递归方法：
注意：
1.因为需要同时比较两个变量的值，所以需要建立helper函数来保持两个变量
2.两个变量命名为left和right不好，与左结点或者右结点重合，可以命名为p,q
递归函数中的最后要返回递归的结果
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
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        return helper(root->left, root->right);
    }
    
    bool helper(TreeNode*left, TreeNode*right){
        if(!left && !right) return true;
        if(!left || !right) return false;
        if(left->val != right -> val) return false;
        return helper(left->left,right->right) && helper(left->right, right->left);
    }
};

遍历：
注意：
1.栈中需要每次弹出两个变量，注意判断两个变量什么时候返回false,什么时候返回true
2.区分
	if(!temp1 && temp2) return false;
    if(temp1 && !temp2) return false;
与
if(!temp1 || !temp2) return false;只要有一方不存在返回false,但是无法处理都为空的情况
3.当满足左右条件之后返回true
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
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        queue<TreeNode*>q;
        q.push(root->left);
        q.push(root->right);
        while(!q.empty()){
            TreeNode *temp1 = q.front();
            q.pop();
            TreeNode *temp2 = q.front();
            q.pop();
            if(!temp1 && temp2) return false;
            if(temp1 && !temp2) return false;
            if(temp1 && temp2){
                if(temp1->val != temp2->val) return false;
                q.push(temp1->left);
                q.push(temp2->right);
                q.push(temp1->right);
                q.push(temp2->left);
            }
        }
        return true;
    }
};

