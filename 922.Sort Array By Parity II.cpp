题意：
给一个非负的vector,一半奇数一半偶数，把奇数放在奇数的位置，偶数放在偶数的位置上
思路：
1.循环vector,取余，能整除2的从第0为开始放，每次+2
2.不能整除2的从第一位开始放，每次+2
3.最后返回新的vector
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        vector<int> ret(A.size());
        int j = 0;
        int p = 1;
        for(int i = 0; i < A.size() ; ++i){
            if(A[i]%2 == 0) {
                ret[j] = A[i];
                j = j+2;
            }else{
                ret[p] = A[i];
                p = p+2;
            }
        }
        return ret;
    }
};