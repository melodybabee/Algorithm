class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        int pro = 0;
         for ( int i = a.length()-1, j = b.length() - 1; i >= 0 || j >= 0; --i, --j ){
            if (i < 0) {
                i = 0;
                a[i] = '0';
            }
            if (j < 0) {
                j = 0;
                b[j] = '0';
            }
            int ans = (a[i]-'0'+b[j]-'0'+pro) % 2;
            pro = (a[i]-'0'+b[j]-'0'+pro)/2;
            res.insert(res.begin(), ans+'0'); 
              
         }
         if(pro == 1) res = '1' + res;
        
       return res;
            
    }
};

/*
设计思路：

*/