题意：
让一个规定值替换为规定的数字，同时把该规定位置的上下左右也变成该数字，再不断以此方式循环“传染”下去。
方法一：DFS
T(n) = O(n), S(n) = O(n)
思路：
1.首先判断指定位置是否已经填充上了规定数字，如果已经填充，那么直接返回，没有其他步骤。
2.如果没有，那么进入DFS递归。
注意只要进入递归就要首先考虑递归的临界条件，当坐标的位置超过二维数组，或者遍历到的点已经是需要填充的数字，那么停止递归，直接return返回。
3.把指定位置更换为目标数字，分别从上下左右四个方向进行递归。
注意：
1.二维数组不一定是square类型的， 因此行和列不能使用相同的长度。
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if(image[sr][sc] == newColor) return image;
        helper(image,sr,sc,newColor,image[sr][sc]);
        return image;
    }
    
    void helper(vector<vector<int>>& image, int sr, int sc, int newColor,int color){
        if(sr < 0 || sc < 0 || sc >= image[0].size() || sr >= image.size() || image[sr][sc] != color) return;
        image[sr][sc] = newColor;
        helper(image,sr+1,sc,newColor,color);
        helper(image,sr,sc+1,newColor,color);
        helper(image,sr-1,sc,newColor,color);
        helper(image,sr,sc-1,newColor,color);
    }
};
方法二：BFS
思路：
1.从起始点开始进入队列，记录下当前queue的长度，取出队列顶部元素。把顶部元素代表的方向进行涂色。
再设置两个新的变量分别加上四个方向，如果四个方向满足在原数组范围内且初始颜色和目标坐标颜色相等，那么push到队列中。
2.如果不满足，跳过即可。
3.在开始要判断是否该结点已经是目标颜色，如果是，直接返回即可。
注意：
1.在BFS的写法中需要注意四个方向是方向数组中的元素，初始化元素都需要写成花括号。
2.队列本身要写成花括号，pair<>也是花括号，<int,int>也是花括号，因此有3个花括号嵌套。
3.队列输出第一个元素用的是front()方法
4.注意pair可以直接用auto进行循环，循环方向数组中的四个方向也用auto
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if(image[sr][sc] == newColor) return image;
        vector<vector<int>> d{{1,0},{0,1},{-1,0},{0,-1}};
        int color = image[sr][sc];
        queue<pair<int,int>>q{{{sr,sc}}};
        while(!q.empty()){
            int l = q.size();
            for(int i = 0; i < l; ++i){
                auto p = q.front();
                q.pop();
                image[p.first][p.second] = newColor;
                for(auto a : d){
                    int x = p.first + a[0];
                    int y = p.second + a[1];
                    if(x < 0 || y < 0 || x >= image.size() || y >= image[0].size() || image[x][y] != color) continue;
                    q.push({x,y});
                }
            }
        }
        return image;
    }
};