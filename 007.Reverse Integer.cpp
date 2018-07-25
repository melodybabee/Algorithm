class Solution {
public:
    int reverse(int x) {
        vector<int> q;
        int mid;
        long long ans = 0;
        int minus = 0;
        
        if(x < 0){
            x = -x;
            minus = 1;
        }  
        
        while(x!=0){
            mid = x%10;
            q.push_back(mid);
            x = x/10;
        }
            
        for (int i = 0; i < q.size(); ++i){
            ans *= 10;
            ans += q[i];
            } 
        
        if(ans > 2147483647 || ans < -2147483648) return 0;
        
        if(minus == 1){
            return -ans;
            }
        else{
            return ans;
            }
    }
};

/*
设计思路：
1.数字不在范围内，return 0;
2.如果输入值小于0 ，需要先加上负号变为正
3.用%10取个位数，再将数/10，存入一个vector中
4.用一个int型ans读取vector的每一位，相乘再相加，得到结果

需要注意：
1.原始数可能不超过范围，但是反转过后会超出范围。所以ans要设置成long long（注意读题，输入的数字不可能超过int范围）
2.看清循环vector的时候加和乘的先后顺序
3.如果原数最后一位是0，反转过来第一位是0，但是先乘后加，因此不需要单独考虑这种情况
4，设立标识位，如果为负，在return的时候单独考虑一下这种情况
*/