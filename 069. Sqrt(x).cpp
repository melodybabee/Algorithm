class Solution {
public:
    int mySqrt(int x) {
        long long a = 1;
        while(true){
            if(a*a > x)
                return int(a)-1;
            else{
                ++a;
            }
        }
      
        
    }
}；//二分查找法

class Solution {
public:
    int mySqrt(int x) {
        double ans = x;
        while(fabs(pow(ans,2)-x) > 0.00001)
            ans = (ans + x/ans)/2;
        
        return ans;
        
    }
};//Newton's method


/*
思路：
1.求一个数字x的平方根，首先想到如果想解决这个问题，需要让a*a=x,求出对应的a值即可
2.a从1开始，如果a*a小于等于x,++a;一旦大于a,返回a-1;

需要注意：
1.当x比较大的时候，a是int, 但是a*a有可能超出int的取值范围,因此需要用long long来进行声明
2.return的类型是int,还需要把long转换为int,即int(a)

优化：
1.利用牛顿迭代的方法进行解题，牛顿迭代的根本思想是利用迭代的方法来求解一个方程的根，不断求切线以此来逼近根
2.本题中的问题可以转换成y = ans的平方-x,求ans的值的问题
3.初始值设置为x,不断做切线逼近，直到y的值非常接近0为止，此时的值为所求的ans
4.注意pow(需要平方的值，平方的次数)方法求幂，fabs()求绝对值
5.因为ans的值不断进行迭代，因此会产生y<0的情况，因此需要加入绝对值运算
6.ans的值不一定为int,需要初始化为double,但是return的时候要求为int,会自动转换只取整数部分
*/