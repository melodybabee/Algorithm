题意：从给定的员工开始计算出他领导的职员的重要性，BFS
思路：
1.首先建立一个queue来表示所有需要入栈的元素，当找到指定元素之后相加上他的重要性，再把他的下属入栈。直到栈空。
2.c++中引用结构体的属性需要用->,调用方法需要用.,原理待补充
/*
// Employee info
class Employee {
public:
    // It's the unique ID of each node.
    // unique id of this employee
    int id;
    // the importance value of this employee
    int importance;
    // the id of direct subordinates
    vector<int> subordinates;
};
*/
class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        queue<int>q;
        q.push(id);
        int ret = 0;
        while(!q.empty()){
            int temp = q.front();
            q.pop();
            for(int i = 0; i < employees.size();++i){
                if(employees[i]->id == temp){
                    ret += employees[i]->importance;
                    for(auto s : employees[i]->subordinates){
                        q.push(s);
                    }
                }
            }
        }
        return ret;
    }
};
优化：
如果为了减少for循环依次查找的过程，可以把对应的id和employee放在unordered_map中。每次把对应的employee的下属依次队列即可。
/*
// Employee info
class Employee {
public:
    // It's the unique ID of each node.
    // unique id of this employee
    int id;
    // the importance value of this employee
    int importance;
    // the id of direct subordinates
    vector<int> subordinates;
};
*/
class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int,Employee*>map;
        for(auto e : employees){
            map[e->id] = e;
        }
        queue<Employee*>q;
        q.push(map[id]);
        int ret = 0;
        while(!q.empty()){
            auto temp = q.front();
            q.pop();
            ret += temp->importance;
            for(auto s : temp->subordinates){
                q.push(map[s]);
            }
        }
        return ret;
    }
};

方法2:DFS
思路：
1.DFS通常会用到helper函数，本质上是递归的思路。
2.从其中一个结点开始直到找到它的结尾为止，那么就需要在处理完当前的结点之后进行for遍历操作
3.把所有的结点存在map中同样为了方便查找，因为需要通过id查找，所以key是id,value部分放employee的结构
/*
// Employee info
class Employee {
public:
    // It's the unique ID of each node.
    // unique id of this employee
    int id;
    // the importance value of this employee
    int importance;
    // the id of direct subordinates
    vector<int> subordinates;
};
*/
class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int,Employee*>map;
        for(auto e : employees){
            map[e->id] = e;
        }
        int ret = 0;
        helper(map, ret, id);
        return ret;
    }
    
    void helper(unordered_map<int,Employee*> &map, int &ret, int id){
        ret += map[id]->importance;
        for(auto s : map[id]-> subordinates){
            helper(map, ret, s);
        }
    }
};