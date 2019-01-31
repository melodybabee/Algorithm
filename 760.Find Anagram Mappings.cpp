题意：找到一个数组在另一个数组中的坐标对应位置
思路：
1.利用hashmap首先进行初始化，再遍历另一个数组进行匹配即可。
2.题目中说如果有重复的元素返回任意一个即可的意思是返回哪一个坐标位置都可以，不需要分别返回不同的坐标
class Solution {
public:
    vector<int> anagramMappings(vector<int>& A, vector<int>& B) {
        unordered_map<int,int>map;
        for(int i = 0; i < B.size(); ++i){
            map[B[i]] = i;
        }
        for(int i = 0; i < A.size();++i){
            A[i] = map[A[i]];
        }
        return A;
    }
};