class Solution {
public:
    string convertToTitle(int n) {
        string ans;
        while (n > 0){
            int firnum = n%26;
            if(firnum == 0){
                ans += 'Z';
                --n;
            }else{
            ans += ('A' + firnum -1);
            }
            n = n/26;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
/*
思路：
1.系统中会自带26进制,本题的核心是进制转换
1-A
2-B
3-C
...
26-Z
27-AA
28-AB
2.在n的范围是1-26的时候，A-Z；如果是27-52，AA-AZ
因此个位是原数对26取余的结果，而十位是除以26对应的结果
3.因此新建一个string,先对26取余，如果不为0，string中输入A加上该位置的距离
如果为0，添加'Z'
4.再对原数除以26，取余，添加到string后面
5.最后对string进行反转，即得到转制后的数字
*/