思路：
1.一般做法，严格意义上会TLE
2.从后往前循环n,不停的调用bool函数，遇到false的时候返回该位数+1
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);
class Solution {
public:
    int firstBadVersion(int n) {
        bool flag = true;
        int i = n;
        for(i; i >= 0 ; --i){
            flag = isBadVersion(i);
            if(!flag) break;
        }
        return i+1;
    }
};

二叉搜索
思路：
1.定义头尾两个指针，只要头结点小于尾部结点的时候，取中值
*此处注意取中值的方法middle =(end-begin)/2 + begin;不能（begin+end）／2，因为有可能会溢出
2.分析可得，结果一定是FFTTT（F前T后的顺序），如果中值为T，右结点移动到中间；如果中值为F，begin移动到middle+1
3.返回begin／end值，寻找的是第一个true值
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        bool flag = true;
        int begin = 0;
        int end = n;
        int middle = 0;
        while(begin < end){
            middle =(end-begin)/2 + begin;
            if(isBadVersion(middle)) end = middle;
            else{
                begin = middle+1;
            }
        }
        return begin;
        
    }
};

12.11复习：
二叉搜索：
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 0;
        int right = n;
        while(left < right){
            int mid = left + (right-left)/2;
            if(isBadVersion(mid)) right = mid;
            else left = mid+1;
        }
        return left;
    }
};