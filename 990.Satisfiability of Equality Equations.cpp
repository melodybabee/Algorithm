题意：给出若干个等式与不等式，判断所有的式子是否可以成立
思路：
1.因为设计一环连着一环的问题，需要判断后面的式子在前面的条件下是否成立，典型的union find的思路
2.先把新建的union find初始化，初始值是其本身，所以在查找的时候根的位置都是其值等于本身的位置。
3.注意分析题意，遇到所有相等的条件都可以是成立的，不成立是在不等的时候才会发生。因此进行第一次遍历，如果遇到相等，那么把这两个数值连在一起即可。
4.再次进行遍历，遇到不等判断这两个值的根结点是否相等，如果相等，返回false,如果最后没有返回false,返回true
注意：
因为数组中给出的是string形式的，循环到的位置是char,建立的union find数组是int类型，要注意类型的统一。也可以都转换为char,只要统一即可。
class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        vector<int>vec(26,0);
        for(int i = 0 ; i < vec.size(); ++i){
            vec[i] = i;
        }
        for(int i = 0; i < equations.size(); ++i){
            if(equations[i][1] == '='){
                int p = findroot(equations[i][0]-'a',vec);
                int q = findroot(equations[i][3]-'a',vec);
                vec[p] = q;
            }
        }
        for(int i = 0; i < equations.size(); ++i){
            if(equations[i][1] == '!'){
                int p = findroot(equations[i][0]-'a',vec);
                int q = findroot(equations[i][3]-'a',vec);
                if(p == q) return false;
            }
        }
        return true;
    }
    
    int findroot(int c,vector<int>&vec){
        return c == vec[c] ? c : findroot(vec[c], vec);
    }
};