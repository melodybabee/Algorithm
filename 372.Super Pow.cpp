题意：
求一个数字的超级平方。050 follow up.
思路：
1.题目中给出的幂是在数组中的形式，根据这个特征需要进行转化
Suppose f(a, b) calculates a^b % k; Then translate above formula to using f :
f(a,1234567) = f(a, 1234560) * f(a, 7) % k = f(f(a, 123456),10) * f(a,7)%k;
即从数组中取出最后一个数，把前面的数组做10次幂的运算再递归回数组。注意最后取余。
2.余数的公式是：ab % k = (a%k)(b%k)%k
3.每次求幂运算的时候和50相同，从最高位开始循环每次取一半，如果是奇数那么乘一次，如果是偶数那么得到二次幂。
注意在每一步都需要取余避免超出int范围。
class Solution {
public:
    const int base = 1337;
    int superPow(int a, vector<int>& b) {
        if(b.empty()) return 1;
        int last = b.back();
        b.pop_back();
        return Pow(superPow(a,b),10) * Pow(a,last) % base;
    }
    
    int Pow(int a, int last){
        int ret = 1;
        a %= base;
        for(int i = last; i > 0; i /= 2){
            if(i % 2 == 1) ret *= a;
            a *= a;
            a %= base;
        }
        return ret % base;
    }
};