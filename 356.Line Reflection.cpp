题意：判断数组中给出的所有点中，能否找到一条平行于Y轴的直线使得所有点对这条线对称
思路：
1.因为需要找到的是对所有点都以这条线为对称的点，那么遍历所有点，找到横坐标最大和最小的两个点，取中，如果能够对称，那么一定在这条线上。
2.下面是查找的工作，检查所有点是否能找到以这条线为对称的点。
那么需要建立一个哈希表，key表示每个点的横坐标，因为有可能横坐标相同的点有不同的纵坐标，而需要区分这些点，所以value的类型是set
3.第一次遍历的时候把这些点放入map中，取中值。
注意因为有可能会有0.5的情况，所以中值的类型是浮点型，对原数字进行计算的时候也需要转换成double
4.再次遍历，每遍历到一个数字求出其应该与之对应的横坐标，在map中查找key中有没有这个横坐标，在value中查找有没有该点对应的纵坐标
如果没有找到，返回false
最后遍历结束返回true
注意：
1.判断有没有的情况要注意思路是，只要不存在就返回false,如果遍历结束没有返回false，那么返回true
2.int更改为double类型要注意（double）转换
class Solution {
public:
    bool isReflected(vector<pair<int, int>>& points) {
        unordered_map<int,set<int>>map;
        int mx = INT_MIN;
        int mn = INT_MAX;
        for(auto p : points){
            mx = max(mx,p.first);
            mn = min(mn,p.first);
            map[p.first].insert(p.second);
        }
        double temp = (double)(mx+mn)/2;
        for(auto p : points){
            int y =  2*temp - p.first;
            if(!map.count(y) || !map[y].count(p.second)) return false;
        }
        return true;
    }
};