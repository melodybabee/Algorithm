题意：
整数转换成罗马数字。
思路：
1.因为罗马数字的特殊性，可以分别创建两个数组，存取相应值下对应的罗马数字，共有13种情况
2.遍历数字，如果大于等于val[]中的值，那么就对应的加上相应的roman值
3.直到加到最后1，num减为0，跳出循环，返回ret
class Solution {
public:
    string intToRoman(int num) {
        string ret;
        string roman[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        int val[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        
        for(int i = 0; num != 0; ++i){
            while(num >= val[i]){
                ret += roman[i];
                num -= val[i];
            }
        }
        return ret;
    }
};