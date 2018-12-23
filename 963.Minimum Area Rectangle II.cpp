题意：939 follow up,找到能形成的矩形的最小面积，可以有不平行于X轴和Y轴的边。
T(n) = O(n^3);
优化方法待思考。
思路： 
1.整体的思路是首先确定是否能形成矩形，再去求矩阵的面积，返回面积最小的那个
2.那么首先把所有的结点都存在一个set中，方便后面查找条件中是否存在该结点
3.用三层循环分别循环到3个结点，不论是否有与坐标轴平行的边，如果想形成矩形，必然需要满足(x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1) != 0
也许矩形中任意三个坐标位置不满足，但是往后循环可能会满足，需要判断第四个结点是否存在。
4.第4个结点的位置由x4 = x2 + x3 - x1;y4 = y2 + y3 - y1;构成
5.找到第4个结点之后，用勾股定理计算两条边的边长，因为矩形都是直角边，因此直接长乘宽即可
5.最后返回找到的最小面积的矩形
注意：
1.为了便于在set中保存和查找，可以把一个坐标对转换为string类型连接起来，查找的时候也是查找string
class Solution {
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        unordered_set<string> s;
        double ret = 0;
        for(auto a: points){
            s.insert(to_string(a[0]) + "_" + to_string(a[1]));
        }
        
        for(int i = 0 ; i < points.size();++i){
            for(int j = i+1; j < points.size(); ++j){
                for(int k = j+1; k < points.size(); ++k){
                    int x1 = points[i][0], y1 = points[i][1];
                    int x2 = points[j][0], y2 = points[j][1];
                    int x3 = points[k][0], y3 = points[k][1];
                    if ((x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1) != 0) continue;
                    int x4 = x2 + x3 - x1; 
                    int y4 = y2 + y3 - y1;
                    if(s.count(to_string(x4) + "_" + to_string(y4))){
                        double w = pow(pow(x2-x1,2) + pow(y2-y1,2),0.5);
                        double l = pow(pow(x3-x1,2) + pow(y3-y1,2),0.5);
                        double area = w*l;
                        if(ret == 0 || ret != 0 && area < ret){
                            ret = area;
                        }
                    }
                }
            }
        }
        return ret;
    }
};