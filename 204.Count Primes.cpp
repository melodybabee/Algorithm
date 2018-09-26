class Solution {
public:
    int countPrimes(int n) {
        vector<bool> ret(n,true);
        ret[0] = false;
        ret[1] = false;
        for(int i = 0; i< sqrt(n);++i){
            if(ret[i]){
                for(int j = i*i;j < n; j += i){
                    ret[j] = false;
                }
            }
        }
        return count(ret.begin(),ret.end(),true);
    }
};

思路：
1.Sieve of Eratosthenes方法筛选质数
如果要检查n，事实上只要检查至n的开根号就可以了。因为假设n不是质数，A*B = n，如果A大于n的开根号，则事实上在小于A之前的检查就可以先检查到B这个数可以整除n。
2.第二步从2开始对所有的数字进行筛选，首先保留2，划掉所有后面小于n且是2的倍数的数字；
接着从3开始对所有的数字进行筛选，首先保留2，划掉所有后面小于n且是3的倍数的数字；
因为4已经被筛选过，所以再走5，以此类推，直到n的开根号位置停止。
3.因此可以建立一个hashtable,原数字的编号作为key,value作为false/true.
4.首先把所有的数字置为true,1,2手动置为false,后面如果为true的状态进入，开始找倍数，置为false
5.最后返回vector中true的数量

注意：
1.在循环一个数字的倍数的时候，直接可以从它的平方数开始寻找。
因为如果有因子小于这个数字本身，在之前的循环当中已经被循环过。
e.g. 对于数字5来说，5 is true,接着就可以从25开始依次置为false
     因为5*4 = 20， 5*3 = 15...在对2进行循环的时候就已经置为false