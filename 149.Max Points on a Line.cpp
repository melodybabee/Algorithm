题意：找到所有点中能形成的最长直线
方法一：利用斜率判断两点是否共线
因为求斜率的时候会有误差，因此如果两个点的数字很大，同时差距很小，那么会四舍五入为共线，实际不共线
不能AC。
Failed on case: [[0,0],[94911151,94911150],[94911152,94911151]]
思路：
1.依次遍历每个结点，两两利用y1-y2/x1-x2来求斜率，特别区分两种情况
一是当x1==x2的时候，不能计算，那么把这种情况的斜率记为INT_MAX
第二种情况是当两个点重合的时候，不共线但是也需要计算进去，那么在每次进入遍历之后，用一个变量记录下这种情况，到结尾直接更新
2.需要一个unordered_map,key用来放斜率，value是等于该斜率的个数
每进入一次遍历，找到当前map中最大的值。
注意：
1.因为需要求最大的共线个数，所以每当遍历到一个新的点的时候，都需要初始化map和重复的点的个数
由于一旦重复的话那么重复的个数就是2个，因此重复的点的个数的初始值为1
2.当没有斜率的时候，即与X轴平行的时候，记这种情况的斜率为INT_MAX
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int ret = 0;
        for(int i = 0; i < points.size(); ++i){
            unordered_map<double,int>map;
            int d = 1;
            for(int j = i+1; j < points.size(); ++j){
                if(points[j].x == points[i].x && points[j].y == points[i].y){
                    ++d;
                }
                else if (points[j].x == points[i].x){
                    ++map[INT_MAX];
                }
                else {
                    double k = (double)(points[i].y - points[j].y) / (double)(points[i].x - points[j].x);
                     ++map[k];
                }
            }
            ret = max(ret,d);
            for(auto it = map.begin(); it != map.end(); ++it){
                ret = max(ret,it->second+d);
            }
        }
        return ret;
    }
};

方法2:避免因为除法的精度不同的问题导致无法AC的问题
思路：
1.第一种方法当横纵坐标相差很小且数字本身很大的时候，求斜率因为精度问题不能test case
2.因此避免直接作除法，而是找到两个点的横纵坐标之差，再分别除以他们的最大公约数，这样可以保证精度
3.设置一个map，key中放入两个点之间的横纵坐标的差除以其最大公约数的结果，用一个pair<,>类型来进行记录,每次放入pair
在查找的时候如果pair相等表示他们有共同的斜率，计数器+1
4.求最大公约数的方法利用递归，如果其中一个为0，那么输出另一个
否则交换位置，用另一个对一个数字取余来进入递归
注意：
1.pair<,>的用法如果想要插入值或者声明初始值的话，需要用{}的形式
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int ret = 0;
        for(int i = 0; i < points.size(); ++i){
            map<pair<int,int>,int>map;
            int d = 1;
            for(int j = i+1; j < points.size(); ++j){
                if(points[j].x == points[i].x && points[j].y == points[i].y){
                    ++d;
                    continue;
                }
                int dx = points[j].x-points[i].x;
                int dy = points[j].y-points[i].y;
                int m = gcd(dx,dy);
                ++map[{dx/m,dy/m}];
            }
            ret = max(ret,d);
            for(auto it = map.begin(); it != map.end(); ++it){
                ret = max(ret,it->second+d);
            }
        }
        return ret;
    }
    
    int gcd(int dx,int dy){
        return dy == 0 ? dx : gcd(dy,dx%dy);
    }
};

方法3:三点共线的判断方法
思路：
1.利用矢量积来计算面积，注意题目中是两点共线即可，所以在循环第三个点的时候，要从头部开始遍历
2.因为会涉及两个坐标相乘的问题，比如65536*65536，这个数字是2的16次幂
那么相乘就会超出int范围，所以在声明的时候要换成long long的形式
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int ret = 0;
        for(int i = 0; i < points.size(); ++i){
            int d = 1;
            for(int j = i+1; j < points.size(); ++j){
                int count = 0;
                long long x1 = points[i].x, y1 = points[i].y;
                long long x2 = points[j].x, y2 = points[j].y;
                if(x1 == x2 && y1 == y2){
                    ++d;
                    continue;
                }
                for(int k = 0; k < points.size();++k){
                    int x3 = points[k].x, y3 = points[k].y;
                    if(x1*y2 + x2*y3+ x3 * y1 - x1*y3-x2 * y1- x3*y2 == 0) ++count;
                }
                ret = max(ret,count);
            }
            ret = max(ret,d);
        }
        return ret;
    }
};
补充：
判断三点是否共线的三种方法及其优劣
判断二维坐标系中是否三个点在一条直线上：A (ax,ay) ,B(bx,by),C(cx,cy)
(1)斜率解法【方法一】
判断  (ay-by)/(ax-bx) == (cy-by)/(cx-bx)
当 ax == bx 或 cx==bx 时需要特殊判断，注意使用 gcd 化简分子分母比较【方法二】，不要使用浮点结果比较，可能会有差别
(2)周长判断解法
排序周长 AC > AB >BC，判断 AC == AB+BC
缺点：由于 sqrt  开方运算，导致结果不准确，不稳定，在三角形接近扁平时，结果误差。
(3)面积判断
判断 area(ABC) ==0
area(ABC) = 1/2 * (AC X BC) = 1/2 *((ax-cx)*(by-cy)-(bx-cx)*(ay-cy))，判断 (ax-cx)*(by-cy) == (bx-cx)*(ay-cy) 即可。
AC X BC 为两矢量的叉积（矢量积），即等于a*b*sin角度，此处的a,b表示边
也就是说三个点(x1,y1)(x2,y2)(x3,y3)用来表示三个点
那么判断的叉积是否等于0
x1 y1 1
x2 y2 1
x3 y3 1
叉积求法：x1 * y2 + x2 * y3 + x3 * y1 - x3 * y2 - x2 * y1 - x1 * y3