class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char,char> map1;
         unordered_map<char,char> map2;
        for(int i = 0; i< s.size();++i){
            if((map1[s[i]]&&map1[s[i]] != t[i]) || (map2[t[i]]&&map2[t[i]] != s[i]))
                return false;
            map1[s[i]] = t[i];
            map2[t[i]] = s[i];
        }
        return true;
    }
};
*Isomorphic 同构的

思路：
1.创建hash表来找对应关系，如果当前字母不存在，将另一个string中的字母添加进去
2.如果存在但是不等，直接返回false

注意：
1.需要两个表来相互进行判断，如果建一个表，ba,aa的情况无法处理
因为b->a,a->a会返回true,是错的
应该b->a,a->b,此时表二就已经存在a,a只能对应b,因此不能在对应a