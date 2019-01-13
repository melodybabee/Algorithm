题意：
奇偶跳，奇数可以跳到大于等于自己的最小值的位置上，偶数可以跳到小于等于自己的最大值的位置上，问有几个数字可以跳到尾部。
思路：
1.分别设置一个DP的奇偶数组，用来记录dp[i]第i位置上的数字能否跳到最后的位置
2.建立一个treemap用来表示记录数组中的数字与其坐标位置的映射
3.从倒数第二个数字开始遍历，每遍历到一个数字在map中查找大于等于它的数字和小于等于它的数字
大于自己的数字判断不等于尾部，小于自己的数字判断不等于头部。如果能找到，那么根据其在另一个数组中的真假性质进行改位置的更新
注意更新要对应dp数组中的坐标位置，是map中的value值
4.最后把该位置写入map中
5.最后在奇数dp数组中包含true的个数就是能够跳到结尾的数字个数
注意：
1.这道题与G OA不同的地方在于可以跳到等于自己的位置上，那么使用treemap中的upper_bound和lower_bound能有效加快效率
lower_bound()表示的是序列中的第一个出现的值大于等于val的位置，注意是位置
upper_bound()返回的是最后一个大于等于val的位置
因为upper_bound()返回的是最后一个大于等于val的位置，那么迭代器向小的方向跳一次就是小于等于当前位置的值的坐标了，因此要--l
class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
        vector<bool>odd(A.size(),false);
        odd[A.size()-1] = true;
        vector<bool>even(A.size(),false);
        even[A.size()-1] = true;
        int total = 0;
        map<int,int>map;
        map[A[A.size()-1]] = A.size()-1;
        for(int i = A.size()-2; i >= 0; --i){
            auto l = map.upper_bound(A[i]);
            auto h = map.lower_bound(A[i]);
            if(l != map.begin()) even[i] = odd[(--l)->second];
            if(h != map.end()) odd[i] = even[h->second];
            map[A[i]] = i;
        }
        for(auto a: odd){
            if(a == true) ++total;
        }
        return total;
    }
};