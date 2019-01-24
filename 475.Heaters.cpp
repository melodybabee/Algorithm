题意：
散热器问题
方法一：遍历
思路：
1.首先将房子数组和散热器都进行排序。从头开始遍历房子数组。
2.每遍历到一个房子，就开始在散热器的位置中找到包含这个房子的范围，两侧取小，表示这个房子可以被散热器照射上。
3.如果左散热器到房子的距离要大于右散热器了，那么表示可以向后移动右散热器了，移动后记录此时的距离
4.因为要使所有房子都被照射上，因此要在较小的结果中取较大值，最后返回结果。
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(),houses.end());
        sort(heaters.begin(),heaters.end());
        int ret = 0;
        int j = 0;
        for(int i = 0; i < houses.size(); ++i){
            while(j +1 < heaters.size() && abs(heaters[j+1]-houses[i]) <= abs(heaters[j]-houses[i])){
                ++j;
            }
            ret = max(ret,abs(heaters[j]-houses[i]));
        }
        return ret;
    }
};
方法二：binary search
思路：
1.对散热器进行排序，遍历所有的房子，每遍历一个房子用二叉搜索找到第一个比房子大的散热器的位置。
2.计算两个距离，一个是比房子大的散热器到房子的距离，一个是比房子小的散热器到房子的距离，结果取两个距离之间的较小值。
3.最后结果取所有较小值中的较大值。
注意：
1.如果找到的比当前位置房子大的值等于0，那么没有再前一位，因此取INT_MAX，结果肯定取右边界。
如果右边界等于原始值，表示没有再大的值，那么同样取INT_MAX。
2.在循环过程中while的条件判断左小于右的时候进入循环判断，一旦相等就进入左右取值比较。
3.右边界每次需要取到heaters.size()，为左闭右开区间，所以left同样要取到mid+1
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int ret = 0;
        sort(heaters.begin(),heaters.end());
        for(auto h : houses){
            int left = 0;
            int right = heaters.size();
            while(left < right){
                int mid = left + (right -left)/2;
                if(heaters[mid] < h) left = mid+1;
                else right = mid;
            }
            
            int r = (right == heaters.size()) ? INT_MAX:heaters[right]-h;
            int l = (right == 0) ? INT_MAX: h-heaters[right-1];
            ret = max(ret,min(r,l));
        }
        return ret;
    }
};