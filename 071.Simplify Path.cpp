题意：
简化文件路径。
思路：
1.根据题目要求得知，如果是重复的／,只取一个;如果是/../那么删除它上面紧挨着的一个路径;如果是/./,那么跳过;如果是空的话返回／
2.那么把所有除去／的有效字符提取出来，再在输出的时候在每个字符间添加／即可
3.设置一个vector,每次找到两个/之间的元素，遇到/就跳过。如果该元素等于..，那么删除vector中的尾部元素，如果该元素等于.,那么跳过，其余直接push_back进去
4.如果vector为空，那么返回／，否则在每个元素之间添加/，最后输出即可
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> vec;
        int i = 0;
        while(i < path.size()){
            while(path[i] == '/' && i < path.size()) ++i;
            if(i == path.size()) break;
            int start = i;
            while(path[i] != '/' && i < path.size()) ++i;
            int end = i-1;
            string str = path.substr(start,end-start+1);
            if(str == ".."){
                if(!vec.empty()) vec.pop_back();
            }else{
                if(str != ".")
                    vec.push_back(str);
            }
        }
        if(vec.empty()) return "/";
        string str;
        for(int i = 0; i< vec.size();++i){
            str += '/'+ vec[i];
        }
        return str;
    }
};