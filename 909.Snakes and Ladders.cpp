题意：在一个N*N的矩阵中找到从左下到右上的最短步数
思路：
1.题目中的要求是从左下开始，那么利用BFS来记录下每一次遍历到的位置，因为可以走1-6步，所以在queue中遍历的就是1-6个位置，每个新的位置就是当前位置加上106
2.因为题目中要求有坐标转换的问题【需要复习】
比如数组
[[-1,-1,-1,-1,-1,-1],
[-1,-1,-1,-1,-1,-1],
[-1,-1,-1,-1,-1,-1],
[-1,35,-1,-1,13,-1],
[-1,-1,-1,-1,-1,-1],
[-1,15,-1,-1,-1,-1]]
在每一次遍历的时候应该转换为
[[36,35,34,33,32,31],
[25,26,27,28,29,30],
[24,23,22,21,20,19],
[13,14,15,16,17,18],
[12,11,10,9,8,7],
[1,2,3,4,5,6]]
所以涉及了坐标转换，变量是我所能的数字和当前数组的长度
比如7，对应的坐标应该是（4，5），x需要-1，对长度取商，再取长度-1的镜像
y需要-1，对长度取余，如果x是奇数，那么y也需要取长度-1的镜像
3.因为需要得到最短距离，因此记录的是第一次到达某个位置上的值，所以建立一个hashmap来表示坐标和对应的距离
如果没有这个值，那么更新到map中再push到queue里
class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        queue<int>q;
        unordered_map<int,int>map;
        map[1] = 0;
        q.push(1);
        while(!q.empty()){
            int temp = q.front();
            q.pop();
            if(temp == board.size() * board.size()) return map[temp];
            for(int i = 1; i <= 6; ++i){
                int next = temp + i;
                if(next > board.size() * board.size()){
                    break;
                }
                auto index = cal(next,board.size());
                int x = index[0];
                int y = index[1];
                if(board[x][y] != -1){
                    next = board[x][y];
                }
                
                if(!map.count(next)){
                    map[next] = map[temp] +1;
                    q.push(next);
                }
            }
        }
        return -1;
    }
    
    vector<int> cal(int num, int size){
        int x = (num-1)/size;
        int y = (num-1)%size;
        if(x % 2 == 1){
            y = size -1 -y;
        }
        x = size - 1 - x;
        return {x,y};
    }
};