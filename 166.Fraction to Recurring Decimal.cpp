Fraction 分数 Recurring循环的
题意：分数转换为循环小数
思路：
1.整数转换为字符串类型首先要注意范围，因为string的范围远远大于int,那么避免越界，需要先转换为long long
2.其次要注意正负，需要先判断下是同号还是异号，做好标记之后对所有的数字去绝对值。
3.因为两个数字只要能表示成分数，那么肯定是可循环的小数，先计算小数点前半部分，就是直接相除的值
对正负号进行判断。
如果取余的结果等于0，那么就直接返回。
4.添加小数点，再设置变量计算后半部分。
5.只要遇到了相同的被除数，那么表示不可能被整除，已经找到了循环节，所以用一个map来记录当前所有的被除数，value放入这个数字的位置，作用是为了(的插入，因此从0开始
6.只要被除数不为0，那么就进入while循环，如果没有在map中找到，插入map,*10除以除数得到结果，被除数*10取余
如果在map中找到了，那么在对应的key之前插入（，补上）返回后半部分结果即可。
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        int s1 = numerator >= 0 ? 1 : -1;
        int s2 = denominator >= 0 ? 1 : -1;
        long long num = abs((long long)numerator);
        long long den = abs((long long)denominator);
        long long ret = num/den;
        long long rem = num%den;
        string ans = to_string(ret);
        if(s1 * s2 == -1 && (ret > 0 || rem > 0)) ans = "-" + ans;
        if(rem == 0) return ans;
        ans += '.';
        string p = "";
        int count = 0;
        unordered_map<long long,int>map;
        while(rem != 0){
            if(map.find(rem)!= map.end()){
                p.insert(map[rem],"(");
                p += ')';
                return ans + p;
            }
            map[rem] = count;
            p += to_string(rem*10/den);
            rem = rem*10%den;
            ++count;
        }
        return ans + p;
    }
};