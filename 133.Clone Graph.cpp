题意：复制一个无向图
方法一：DFS递归
思路：
1.图结构是一个结点下面连着一个图结点类型的数组
2.本题是无向图，类似138链表的拷贝，那么需要建立一个map来记录某个图结点是否已经被建立过。
map的key放入图的值，保证了唯一性，不会重复创建，value放入图的结点
3.难点在于对于一个图结点下面的数组，要写一个循环进行遍历，每遍历一个进入一次递归，dfs方法
4.如果在map中找到了这个结点，直接返回，如果没有找到，创建一个新的结点，同时在map中对应上相应的关系
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        unordered_map<int,UndirectedGraphNode*>map;
        return dfs(node,map);
    }
    
    UndirectedGraphNode* dfs(UndirectedGraphNode *node,unordered_map<int,UndirectedGraphNode*> &map){
        if(!node) return NULL;
        if(map.count(node->label)) return map[node->label];
        UndirectedGraphNode *newnode = new UndirectedGraphNode(node -> label);
        map[node->label] = newnode;
        for(int i = 0; i < node->neighbors.size();++i){
            newnode -> neighbors.push_back(dfs(node->neighbors[i],map));
        }
        return newnode;
    }
};

优化：
1.map直接放入图结点就可以，但是注意此处的map需要是一个全局变量
2.如果在map中查找不到对应的元素，那么直接新建一个与其对应。后开始循环邻接点。调用递归查找是否在map中有某个元素。
如果能找到该元素直接返回即可。
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
private:
    unordered_map<UndirectedGraphNode*,UndirectedGraphNode*>map;
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return NULL;
        if(map.find(node) == map.end()){
            map[node]= new UndirectedGraphNode(node->label);
            for(auto neigh : node->neighbors){
                map[node] ->neighbors.push_back(cloneGraph(neigh));
            }
        }
        return map[node];
    }
};

方法2:DFS非递归
TLE,但是思路正确
思路：
1.首先建立第一个图结点，建立旧图和新图之间的映射，把旧图的结点入栈
2.进入while循环，获取头部结点，开始遍历头部结点的邻接点，如果在map中没有，该点入栈，建立一个与他对应的新的结点，建立图映射关系。
最后要把跳出的头结点在map中映射的结点与其新建的邻接点在map中对应的结点连接起来，push进入其数组中。
如果在map中存在，直接执行最后一步。
3.最后返回头结点。
4.注意非递归方法都需要注意结点为0的情况。
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return NULL;
        unordered_map<UndirectedGraphNode*,UndirectedGraphNode*>map;
        UndirectedGraphNode *newnode = new UndirectedGraphNode(node -> label);
        map[node] = newnode;
        stack<UndirectedGraphNode*>st;
        st.push(node);
        while(!st.empty()){
            UndirectedGraphNode *temp = st.top();
            for(int i = 0; i < temp->neighbors.size();++i){
                if(!map.count(temp->neighbors[i])){
                    st.push(temp->neighbors[i]);
                    UndirectedGraphNode *cur = new UndirectedGraphNode(temp->neighbors[i] -> label);
                    map[temp->neighbors[i]] = cur;
                } 
                map[temp] -> neighbors.push_back(map[temp->neighbors[i]]);
            }
        }
        return newnode;
    }
};

方法3:BFS
思路：
1.设置一个queue先输入图的第一个结点，接着遍历其邻接数组，如果不存在，那么创建新的同时放入栈。
如果存在那么直接在map中对应结点后push_back
2.注意所有新建的结点都需要从map中的对应位置开始，便于建立映射关系。
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return NULL;
        unordered_map<UndirectedGraphNode*,UndirectedGraphNode*>map;
        map[node] = new UndirectedGraphNode(node -> label);
        queue<UndirectedGraphNode*>q;
        q.push(node);
        while(!q.empty()){
            UndirectedGraphNode *temp = q.front();
            q.pop();
            for(int i = 0; i< temp->neighbors.size();++i){
                if(map.find(temp->neighbors[i]) == map.end()){
                    map[temp -> neighbors[i]] = new UndirectedGraphNode(temp ->neighbors[i]->label);
                    q.push(temp->neighbors[i]);
                }
                map[temp]->neighbors.push_back(map[temp -> neighbors[i]]);
            }
        }
        return map[node];
    }
};