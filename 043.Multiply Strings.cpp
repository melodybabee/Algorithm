题意：
给两个字符串，输出两个字符串的乘积，不可转换为int形式。大数乘法。
思路：
1.本题的目的在于计算大数乘法，可以不局限于int或者long的类型大小。
2.整体思路就是各位依次相乘再相加的思路，首先设置一个数组，记录每一位各自相乘的结果，为了便于后面的进位运算和去0，把0*0的结果存到倒数第二位，把m*n的结果存入第一位。
注意m*n两个数字相乘，最长长度是m+n,这是在最高位有进位的情况。
通常如果不算进位，为m+n-1长度。
因为数组从0开始，所以我们设定k为m +n -2
3.每一位分别加和之后开始处理进位，除以10取余即可。
4.注意此时得到的结果是正确结果的逆序，因此不可能在最低位有0，而且初始化为m+n个0，所以需要从数组的尾部检查，如果有0，i向前移动一位，直到第一位不是0的数字。
如果都是0，说明返回值为0，那么直接返回0即可。
5.最后创建一个string进行遍历，从尾部第一个不为0的数字开始，依次push_back进去，就是最终结果。
注意：
1.注意逆序和相加到数组的位置。
2.注意去头部的0.
3.string也可以直接在尾部进行push_back()
class Solution {
public:
    string multiply(string num1, string num2) {
        int n = num1.size();
        int m = num2.size();
        vector<int>vec(m+n,0);
        int k = m +n -2;
        for(int i= 0; i < n; ++i){
            for(int j = 0; j < m ;++j){
                vec[k-i-j] += (num1[i]-'0')*(num2[j]-'0');
            }
        }
        int count = 0;
        for(int i = 0; i < vec.size();++i){
            vec[i] += count;
            count = vec[i]/10;
            vec[i] = vec[i]%10;
        }
        int i = k+1;
        while(vec[i] == 0) i--;
        if(i<0) return "0";
        string ret;
        for(i; i>= 0; --i){
            ret.push_back(vec[i]+'0');
        }
        return ret;
    }
};
优化：
如果想简化字符相加为之前逆序的问题，可以先用reverse()函数进行反转，会使思路和代码简化一些，但是思路不变。