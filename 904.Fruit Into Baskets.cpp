题意：在篮子里只能装两种水果，问能最多装多少个
思路：
1.典型的双指针sliding window问题，右指针负责循环，左指针负责判断是否超过了2种种类
2.用一个map来记录下每个元素的位置，一旦超过了，用while循环删除左指针位置上的数字，一直保持map的大小最多为2
3.每次循环结束记录过程中的较大值，最后的最大值作为返回的结果
注意：
unordered_map也可以用size()来表示map的大小，用erase来删除其中的某一个key
class Solution {
public:
    int totalFruit(vector<int>& tree) {
        unordered_map<int,int>map;
        int left = 0; 
        int right = 0;
        int ans = 0;
        for(int right = 0; right < tree.size();++right){
            map[tree[right]]++;
            while(map.size() > 2){
                map[tree[left]]--;
                if(map[tree[left]] == 0) map.erase(tree[left]);
                ++left;
            }
            ans = max(ans,right-left+1);
        }
        return ans;
    }
};