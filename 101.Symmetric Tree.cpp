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
		cin >> value;
		Node root(value);
		while(n--){
			int newValue;
			cin >> newValue;
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





