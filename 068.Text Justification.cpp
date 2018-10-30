题意：
根据给定的长度使文本左右对齐。
思路；
1.首先循环words，把循环到的words的长度相加，如果所有word的长度+中间的空格数大于最长长度，开始输出。
2.首先根据最长长度和单词的长度相减得到空格的个数。开始把string依次输出到vector中。
3.如果空格的个数大于0，如果已经循环到最后一行，如果只有一个单词，那么所有的空格直接添加在string末尾即可。
如果不是一个单词，那么空格数为1。
如果没有到最后一行，判断是否只有一个单词，如果只有一个单词，那么把左右的空格放在单词后面即可。
如果大于一个单词，那么用空格数取余单词数，如果可以整除，那么每个单词之间的空格数为空格数除以单词数的商，如果不能整除，空格数等于商+1；
4.把空格数push到string中。
一次循环结束之后空格数更新为原空格数-已经push到string中的空格数。
循环的i位移动到j的位置，从下一位应该判断长度的单词开始循环。
5.最后输出vector.
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ans;
        int i = 0;
        while(i< words.size()){
            int j = i; 
            int len = 0;
            while(j < words.size() && words[j].size()+ len + j-i <= maxWidth){
                len += words[j].size();
                ++j;
            }
            string str;
            int space = maxWidth - len;
            for(int k = i; k < j; ++k){
                str += words[k];
                if(space > 0){
                    int temp;
                    if(j == words.size()){
                        if(j - k ==1) temp = space;
                        else temp = 1;
                    }else{
                        if(j-k-1>0){
                            if(space % (j-k-1) == 0) temp = space/(j-k-1);
                            else temp = space/(j-k-1) +1;
                        }else{
                            temp = space;
                        }
                    }
                    str.append(temp,' ');
                    space -= temp;
                }
            }
            ans.push_back(str);
            i = j;
        }
        return ans;
    }
};