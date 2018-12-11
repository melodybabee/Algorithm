题意：
125题的拓展，删除一位可以构成回文子串的也返回true
思路：
T(n) = O(n);
1.从头尾开始循环，如果相等，分别相加
2.一旦不等，分别有一次机会左移动或右移动，移动后进入其各自的循环判断，若一直相等，返回true
3.若左或者右移动一次之后仍不满足回文，返回false
class Solution {
public:
    bool validPalindrome(string s) {
        int p = 0;
        int q = s.size()-1;
        while(p<=q){
            if(s[p] == s[q]){
                ++p;
                --q;
            }
            else{
                
                int left1 = p+1, right1 = q;
                while(left1 <= right1 && s[left1] == s[right1]){
                    ++left1;
                    --right1;
                }
                if(left1 >=right1) return true;
                
                int left2 = p, right2 = q-1;
                while(left2 <= right2 && s[left2] == s[right2]){
                    ++left2;
                    --right2;
                }
                if(left2 >=right2) return true;
                
                return false;
            }
        }
        return true;
    }
};

12.10复习：
注意：
用两指针来判断，不满足相等条件建立子指针。
class Solution {
public:
    bool validPalindrome(string s) {
        for(int i = 0, j = s.size()-1; i <= j; ++i, --j){
            if(s[i] != s[j]){
                int l1 = i;
                int l2 = i+1;
                int r1 = j-1;
                int r2 = j;
                while(s[l1] == s[r1]) ++l1, --r1;
                while(s[l2] == s[r2]) ++l2, --r2;
                return (l1 >= r1 || l2 >= r2);
            }
        }
        return true;
    }
};
