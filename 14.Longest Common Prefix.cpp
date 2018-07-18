class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ret = "";
        if(strs.size()==0) return "";
        if(!strs[0][0]) return "";
        for (int i =0; i < strs[0].size();++i){
            for (int j = 1; j < strs.size(); ++j){
                if(strs[j][0] != strs[0][0]) return "";
                if(!strs[j][i]) return ret;
                if(strs[j][i] != strs[0][i]) return ret;
                else{
                    continue;
                } 
            }
            ret += strs[0][i];
        }
        return ret;
    }
};

/*
prefix 前缀

思路：
1.循环vector中的第一个string,如果后面的每一个string都与第一位的字符相同，继续循环。一旦有不等的，直接返回已有的返回值。

盲点：
1.边界条件
*如果vector本身不存在，即strs.size()==0，返回空；
*如果vector中的第一个string不存在，即!strs[0][0]，返回空
*如果vector中后面的stirng比第一个短，e.g. flower,fl,flink,这种情况，!strs[j][i]，直接返回已有的返回值
2.除了特殊情况的return,正常情况的return不要忘记，第18行

其余思路：
1.设计标识位，先设置flag默认为true,bool flag = true;
2.一旦有不满足情况的条件，将flag更改为false;
3.最后判断，如果flag为true, 返回已有的返回值。如果flag是！true, break;
优点就在于直接写好不满足条件的情况即可。
代码可以看原题部分。

代码报错排查：
1.Runtime Error Message:reference binding to null pointer of type 'value_type'
  Last executed input:[]
  可能原因： 
  对于数组长度为0的情况没有进行判断，加入判断条件就可以解决。
2.execution reached the end of a value-returning function without returning a val
  没有返回值。

*/
