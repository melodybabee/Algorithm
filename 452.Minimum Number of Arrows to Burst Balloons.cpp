spherical 球面的
horizontal 水平的
题意：
用箭射气球，如果有共同范围内的气球可以一箭射掉，问最少需要多少箭。
思路：
1.类似253meeting rooms的题目，首先将pair排序，从头部开始遍历。
2.如果后面的头部元素小于等于尾部元素，那么可以一箭双雕，更新当前最小值为两个尾部元素的最小值。
如果后面元素的头结点还在这个最小值范围内，说明这一箭还可以射穿。
如果后面元素头结点比这个最小值大，那么表示需要新的箭，计数器+1。
注意：
1.本题相等头尾相等时也认为可以射穿。
2.官方的说法本方法叫做greedy,因为局部最优解就等于全局最优解。
class Solution {
public:
    struct cmp{
        bool operator()(pair<int, int> a, pair<int, int> b){
            return a.first < b.first;
        }
    };
    int findMinArrowShots(vector<pair<int, int>>& points) {
        if(points.empty()) return 0;
        int count = 1;
        sort(points.begin(),points.end(),cmp());
        int temp = points[0].second;
        for(int i = 1; i< points.size(); ++i){
            if(points[i].first <= temp){
                temp = min (temp,points[i].second);
            }else{
                ++count;
                temp = points[i].second;
            }
        }
        return count;
    }
};
优化：
因为默认的对于pair的排序，就是按第一个数字升序排列，如果第一个数字相同，那么按第二个数字升序排列
因此不需要自定义比较函数也可以。
class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        if(points.empty()) return 0;
        int count = 1;
        sort(points.begin(),points.end());
        int temp = points[0].second;
        for(int i = 1; i< points.size(); ++i){
            if(points[i].first <= temp){
                temp = min (temp,points[i].second);
            }else{
                ++count;
                temp = points[i].second;
            }
        }
        return count;
    }
};