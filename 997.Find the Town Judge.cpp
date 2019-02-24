题意：类似277找名人，只有一个人不相信任何人，而所有人相信他，判断是否存在这个人
思路：
1.按照题目中的意思暴力求解，设置一个数组默认值为1，相信别人的人不可能是这个人，所以在原始数组中第一位出现的都更改为-1
2.判断此时数组中1的个数，必须有且只有一个，否则直接返回-1
3.接下来判断所有人都必须相信这个人，因此原始数组中第二位等于这个人，数组更改为1
4.最后判断temp数组中是否还有-1，有的话就返回-1
注意：
因为数组的长度要大一位，因此0每次都需要单独处理
class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        vector<int>vec(N+1,1);
        vec[0] = -1;
        for(int i = 0; i < trust.size(); ++i){
            int temp = trust[i][0];
            vec[temp] = -1;
        }
        int count = 0;
        int cur = 0;
        for(int i = 0; i < vec.size(); ++i){
            if(vec[i] == 1){
                ++count;
                cur = i;
            } 
            if(count > 1) return -1;
        }
        if(cur == 0) return -1;
        vec[0] = 1;
        for(int i = 0; i < trust.size(); ++i){
            if(trust[i][1] == cur) vec[trust[i][0]] = 1;
        }
        for(int i = 0; i < vec.size(); ++i){
            if(vec[i] == -1){
                return -1;
            } 
        }
        return cur;
    }
};
优化
思路：
1.把这道题的题意看作是一个有向图，从第一个元素指向第二个元素
2.相信别人-1，被别人信任+1，那么如果存在这个人，应该最后的值是N-1
class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        vector<int>vec(N+1,0);
        for(int i = 0; i < trust.size(); ++i){
            ++vec[trust[i][1]];
            --vec[trust[i][0]];
        }
        for(int i = 1; i <= N; ++i){
            if(vec[i] == N-1) return i;
        }
        return -1;
    }
};