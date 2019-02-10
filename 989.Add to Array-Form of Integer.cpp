题意：用一个数组与一个数字进行相加，返回一个新的数组
思路：
1.涉及字符串和数字相加的问题一个要注意进位问题，一个要小心% /的操作即可
2.数组从最后一位开始while循环，每次对数字取%，用一个temp变量来记录进位，进位是数组中的数字的值+最后一位数字+之前的进位值再除以10得到的
3.一旦数字或者数组其中有一个到头部了，那么对另一方进行单独的while循环，如果数组在，继续更新，如果只有数字在那么从头部插入即可
4.最后判断进位的数组是否为1，如果是1那么头部插入，最后返回
class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        vector<int> ans(A.size());
        int temp = 0;
        int i = A.size()-1;
        while(i >= 0 && K > 0){
            int j = K%10;
            int sum = A[i] + j+ temp;
            ans[i] = sum % 10;
            temp = sum/10;
            --i;
            K /= 10;
        }
        while(i >= 0){
            ans[i] = (A[i] + temp) %10;
            temp = (A[i] + temp) /10;
            --i;
        }
        while(K > 0){
            int j = (K % 10 + temp) % 10;
            ans.insert(ans.begin(),j);
            temp = (K % 10 + temp)/10;
            K /= 10;
        }
        if(temp == 1) ans.insert(ans.begin(),1);
        return ans;
    }
};
优化：
1.因为是在A的基础上进行操作，所以对A进行改变就可以
2.每次都让A位置上的数字全部加上K，K更新为新的需要相加的值，A当前位置上取余
3.最后只要判断K是否存在即可
class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        for(int i = A.size()-1; i >= 0 && K > 0; --i){
            A[i] += K;
            K = A[i]/10;
            A[i] %= 10;
        }
        
        while(K > 0){
            A.insert(A.begin(), K%10);
            K /= 10;
        }
        return A;
    }
};