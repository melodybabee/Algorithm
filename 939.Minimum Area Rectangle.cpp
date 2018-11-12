题意：
在一个二位数组中找到能形成的最小矩形的面积。
方法一：找对角线
T(n) = O(n^2);
思路：
1.矩形能形成的条件是如果两个点能形成对角线，那么判断矩形的另外两点是否满足条件，如果满足，则能形成矩形，计算出面积，求最小。如果两个点不能形成对角线那么不可能形成矩形。
两层for循环，属于暴力拆解。
2.首先把原有的一对一对的结点insert到一个set中，便于后面查找是否存在某结点。
3.再从二位数组开始循环，每次取出两个结点，判断能否形成对角线，即这两个点的横纵坐标分别都不能相等。
如果能存在，那么在set中查找以这两个点为对角线，形成的另外两个点是否存在。如果存在，说明能形成矩形，计算面积。
不存在则不能形成矩形。
4.最后返回面积的最小值。
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        set<vector<int>> s;
        int area = INT_MAX;
        for(auto &p : points){
            s.insert(p);
        }
        for(int i = 0; i < points.size(); ++i){
            vector<int> p =  points[i];
            for(int j = i+1 ; j < points.size(); ++j){
                vector<int> q = points[j];
                if(p[0] != q[0] && p [1] != q[1] && s.find({q[0],p[1]}) != s.end() && s.find({p[0], q[1]}) != s.end()){
                    area = min(abs(p[0]-q[0])*abs(p[1]-q[1]),area);
                }
            }
        }
        return area == INT_MAX ? 0 : area;
    }
};
方法二：存入set<pair<int,int>>进行查找，本质仍然是找对角线
T(n) = O(n^2logn);
思路：
1.两层循环结点，把循环到的结点依次按照pair insert到set中
2.判断这两个点交换横纵坐标后的两个新结点是否存在于vector中
3.不存在则不能形成矩形，还需要判断面积是否为0。在面积大于0的情况下，输出面积的最小值。
4.不要忘记如果没有矩形输出的是0，如果有输出了area
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int area = INT_MAX;
        set<pair<int,int>> s;
        
        for(int i = 0; i < points.size(); ++i){
            int a = points[i][0];
            int b = points[i][1];
            s.insert({a,b});
            for(int j = i+1; j < points.size(); ++j){
                int m = points[j][0];
                int n = points[j][1];
                s.insert({m,n});
                if(s.find({a,n}) != s.end() && s.find({m,b}) != s.end()){
                    if(abs(a-m)*abs(b-n) > 0){
                        area = min(area,abs(a-m)*abs(b-n));
                    }
                }
            }
        }
        return area == INT_MAX ? 0: area;
    }
};
