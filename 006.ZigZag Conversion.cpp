思路：
1.举例说明 numRows = 4
0    6       12
1  5 7    11 13
2 4  8  10   14
3    9       15
通过观察发现，每一个被填满的列的列数都和2*numRows-2有关，2*numRows-2为一个周期
6=2*numRows-2
12 = 2*（2*numRows-2）
9 = 3*（2*numRows-2）
15 = 4*（2*numRows-2）
因此在列循环的时候每次相加2*numRows-2
2.当斜的位置有数字的时候，数字与其左边一列的关系是比如157在一行里，5的位置是2-7一个周期的长度减去5-7的长度
因为行数从0起，所以5-7的长度是2*i，因此1-5的长度是（一个周期-2*i）
也可以这样理解，4-8的距离是6（+1），5，7（+2），8（+1）， 因此共有i*2个距离，位置也就是j+一个周期-2*i
3.所以用i来循环行数，每列相加一个周期，当i不是第一行或者最后一行的时候，输出前一列的位置+一个周期-2*所在行数
直到所输出的位置大于s本身的长度退出循环
class Solution {
public:
    string convert(string s, int numRows) {
        string ret;
        if(numRows <= 0 || s.size() == 0) return "";
        if(numRows == 1) return s;
        int key = 2*numRows-2;
        for(int i = 0; i< numRows; ++i){
            for(int j = i; j < s.size(); j += key){
                ret = ret+s[j];
                if(i!= 0 && i != numRows-1){
                    int temp = j+2*numRows-2-2*i;
                    if(temp < s.size()){
                        ret += s[temp];
                    }
                }
            }
        }
        return ret;
    }
};