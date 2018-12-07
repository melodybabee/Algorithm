题意：
找出给定圆内的随机坐标值。
方法一：产生随机数+拒绝采样
思路：
1.求在一个圆里面的坐标，可以先求其正方形中均匀分布的点，然后再判断坐标中的点在不在内切圆内，如果在就是x^2+y^2<=r^2;
不在的话就重新循环。
2.注意求正方形的方法：
(double)rand()/RAND_MAX表示获取浮点型的0-1之间的数字。2倍表示扩大范围以能够取到正负轴上的值。-1表示以原点为界限取到两侧的值。
最后要乘上半径的长度。
3.在返回的时候注意是vector类型，同时需要加上半径的偏移量。
class Solution {
private:
    double r;
    double x;
    double y;
public:
    Solution(double radius, double x_center, double y_center) {
        r = radius;
        x = x_center;
        y = y_center;
    }
    
    vector<double> randPoint() {
        while(true){
            double realx = (2*(double)rand()/RAND_MAX-1)*r;
            double realy = (2*(double)rand()/RAND_MAX-1)*r;
            if(realx*realx + realy*realy <= r*r) return {{x+realx},{y+realy}};
        }
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj.randPoint();
 */
方法2:极坐标
思路：
1.极坐标的表示方法是x^2 + y^2 = r^2;(r*cos@)^2 + （r*sin@)^2 = r^2;
2.那么求出一个随机角度，再在范围内求出一个随机半径长度，就能得到圆中坐标的位置。
3.注意PI的表示是M_PI，表示180度，360度就是2* M_PI
取半径的时候注意开平方，因为r^2(cos@^2+sin@^2) = r^2;单独求出坐标位置之后会对r取平方，如果在求半径的时候不取平方那么就会在乘积的时候用两个小于1的数字再相乘，会缩小数字的范围。
class Solution {
private:
    double r;
    double x;
    double y;
public:
    Solution(double radius, double x_center, double y_center) {
        r = radius;
        x = x_center;
        y = y_center;
    }
    
    vector<double> randPoint() {
        double theta = 2* M_PI *((double)rand()/RAND_MAX);
        double length = sqrt((double)rand()/RAND_MAX) *r;
        return{{x+length *cos(theta)},{y + length*sin(theta)}};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj.randPoint();
 */