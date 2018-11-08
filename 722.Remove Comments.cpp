题意：
去掉vector中的注释
思路：
1.有两种注释，"//"的情况去掉该行后面的所有元素，"/*"'*/'之间的元素要去掉，最后输出剩余部分
2.从头部开始循环vector,循环到每一行的时候，如果是"//"说明可以省略后面的部分，直接开始下一行的循环
3.如果是"/*"那么标记flag为true,直到遇见下一个"*/"再标记为false,中间部分省略
4.注意用一个string来记录每行的输出，在内循环结束的时候判断，如果flag为false且s不为空，输出。输出后清空字符串。
意思是吧"//"之前或者没有注释或者"/*"之前的字符或者"*/"之后的字符push到返回的vector中。
class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        vector<string>ret;
         string s = "";
        int m = source.size();
        bool flag = false;
        for(int i = 0;i < m;++i){
            for(int j = 0; j < source[i].size(); ++j){
                if(!flag && j +1 < source[i].size() && source[i][j] == '/' && source[i][j+1] == '/') break;
                else if(!flag && j +1 < source[i].size() && source[i][j] == '/' && source[i][j+1] == '*') flag = true,++j;
                else if(flag && j +1 < source[i].size() && source[i][j] == '*' && source[i][j+1] == '/') flag = false,++j;
                else if(!flag) s.push_back(source[i][j]);
            }
            if(!flag && !s.empty()) ret.push_back(s),s.clear();
        }
        return ret;
    }
};