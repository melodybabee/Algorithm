题意：
字典序排列数字。
方法一：遍历
思路：
1.lexicographical order是字典序，所有数字要根据字典的顺序进行排列，1开头在2开头之前，11开头在12开头之前，以此类推。
2.因为返回类型是vector，那么需要循环vector中的位置来一个一个填充。
3.从1开始，每次进入一个新数字需要乘10判断是否在n的范围内，如果在范围内*10重新进入循环。
如果不在范围内那么判断如果当前数字大于n，那么如果数字已经大于等于n,那么除以10。比如13到了13的位置之后需要除以10，而不能直接+1得到14.
4.如果仍在范围内，那么在高位不变的前提下对数字进行+1操作。
5.每当遍历到一个新的数字的时候，比如从19-20，那么对20进行除以10的操作，即从2重新开始进行循环。
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> ret(n);
        int cur = 1;
        for(int i = 0; i < n;++i){
            ret[i] = cur;
            if(cur * 10 <= n){
                cur *= 10;
            }else{
               if(cur >= n) cur /= 10;
               cur += 1;
               while(cur % 10 == 0) cur /= 10;
            }
        }
        return ret;
    }
};
方法2:递归
思路：
1.和遍历相同，先对最高位进行1-9的循环，每次新在数组中循环加入一位新数字进行判断是否在n的范围内。
如果在那么调用递归在此基础之上继续进行遍历，如果不在break,进入下一位高位。
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int>ret;
        for(int i = 1; i <= 9; ++i){
            helper(ret,i,n);
        }
        return ret;
    }
    
    void helper(vector<int>&ret, int i , int n){
        if(i > n)return;
        ret.push_back(i);
        for(int j = 0 ; j <= 9; ++j){
            if(i *10 + j <= n){
                helper(ret,i*10+j,n);
            }else break;
        }
    }
};