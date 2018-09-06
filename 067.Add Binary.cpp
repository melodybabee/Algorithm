class Solution {
public:
    string addBinary(string a, string b) {
        int mid = 0;
        int ret = 0;
        string ans;
        for (int i = a.size()-1, j = b.size()-1; i >= 0 || j >= 0; --i,--j){
            if(i < 0){
                i = 0;
                a[i] = '0';
            }
            if(j < 0){
                j = 0;
                b[j] = '0';
            }
            ret = (a[i]-'0' + b[j]-'0'+ mid)%2;
            mid = (a[i]-'0' + b[j]-'0'+ mid)/2;
            ans.insert(ans.begin(),ret+'0');
        }
        
        if(mid == 1){
            ans = '1' + ans;
        }
        
        return ans;
        
    }
};

/*
设计思路：
1.分别循环两个string,从两个string的最后一位开始相加，用mid来记录进位的情况，用ret记录每一位的保存结果
2.其中mid用两个数相加取余得到，ret用两个数字相加除以2得到
3.如果最后循环到第一位后仍然有进位，则在ans结果之前加1
4.还需要考虑一长一短的情况（此步需要提示）

需要注意的问题：
1.mid 和 ret两个结果每次都需要加上mid的上一位进位值，易忽视。因此mid需要设定初始值为0。
2.注意mid 和ret相加的都是string中每一位的结果，string中的每一位本身是char字符格式，因此如果相加则需要转换为整数的形式
string --> int, char-'0';
int --> string, int +'0';
3.在一个字符串ans中插入字符，ans.insert(),ans.begin()从ans的头部插入，后面是插入的值
4.再次强调ans是string的格式，因此在头部插入1的时候，1的形式应该为char,为'1'
5.卡住的点1，本想在原字符串的基础上直接进行相加，省去了新建变量的过程，但是原string的位置不好确定，思路显得不清晰
返回值需要的是string形式的，因此创建string变量即可
6.卡住的点2，如果a,b本身长度不等如何处理
因为for循环中的i >= 0 || j >= 0;是或的条件，只有i,j都小于0的时候才会跳出for循环，因此可以分别讨论i或者j一方为0的情况
当一方为0时，设定该数为0，string中的这一位为'0',使下方取到该位时的整数值为0.

*/