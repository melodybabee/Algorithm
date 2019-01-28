题意：拆分数组中的字符串进行统计并输出
思路：
1.因为需要进行统计输出，那么建立一个哈希表来放入string和int
2.循环原数组，用vector.find()方法找到空格的位置，前半部分转换为整数，后面从全长开始遇到.就对字符串进行截取
截取后在map中插入整数
3.遍历map进行输出操作
注意：
1.在vector中查找某一点的位置用find()方法
2.substr()方法如果有两个变量，前一位是开始的位置，后一位是长度；如果只有一个变量表示到结尾
3.to_string表示整数转字符串
class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        vector<string>ans;
        unordered_map<string,int>map;
        for(auto c : cpdomains){
            int i = c.find(" ");
            int n = stoi(c.substr(0,i));
            string s = c.substr(i+1,c.size()-i-1);
            for(int j = 0; j < s.size(); ++j){
                if(s[j] == '.'){
                    map[s.substr(j+1)] += n;
                }
            }
            map[s] += n;
        }
        for(auto it:map){
            ans.push_back(to_string(it.second) + " " + it.first);
        }
        return ans;
    }
};