题意：
找出给定的4个数字能组成的最大时间。
方法一：从2359开始依次遍历
思路：
1.首先把数组中的数字存在map里，为了后面判断某数字是否与给出的数组匹配。
2.从2359开始倒着循环，因为时间最大是2359,找到最大的满足条件的即可。
3.用一个新的方法判断是否满足条件，有以下几个条件：
(1)如果后两位是大于60，false;
(2)如果数字中的某一位不在map中，false
(3)如果数字为0，需要判断map中0的位置是否是4个0
(4)如果在map中还有key不为0，且value大于0的值，返回false。比如[5,5,5,5]中找到数字555.
以上都不满足，返回true
4.找到满足条件的数字之后，需要先转换为字符串，如果位数小于4位，在前面补0.在中间第二个位置insert冒号，返回字符串
class Solution {
public:
    string largestTimeFromDigits(vector<int>& A) {
        unordered_map<int,int>map;
        string ret;
        for(int i = 0; i < A.size() ;++i)++map[A[i]];
        for(int i = 2359; i>=0; --i){
            if(valid(map,i)){
                ret = to_string(i);
                while(ret.size() < 4) ret = '0'+ret;
                ret.insert(ret.begin()+2,':');
                return ret;
            }
        }
        return ret;
    }
    
    bool valid(unordered_map<int,int>map,int i){
        if(i == 0) return map[0] == 4;
        if(i%100 >= 60) return false;
        while(i>0){
            int temp = i%10;
            --map[temp];
            if(map[temp] < 0) return false;
            i /= 10;
        }
        for(auto it : map){
            if(it.first != 0 && it.second > 0) return false;
        }
        return true;
    }
};
方法二：next_permutation
思路：
1.用C++ next_permutation()方法，会对所有数字进行全排列,注意全排列的顺序是从小到大，因此需要先sort好找到最小的数字。
2.排除前两位大于23和后两位大于等于60的情况，用总的分钟数来计算最大值，如果有更大的，更新为最大的，再依次更新到字符串中。
class Solution {
public:
    string largestTimeFromDigits(vector<int>& A) {
        sort(A.begin(),A.end());
        int ans = INT_MIN;
        string str;
        do{
            int hour = A[0]*10 + A[1];
            int min = A[2]*10 + A[3];
            if(hour > 23 || min >= 60) continue;
            if(hour*60+min > ans){
                ans = hour*60 + min;
                str.clear();
                str.push_back(A[0]+'0');
                str.push_back(A[1]+'0');
                str.push_back(':');
                str.push_back(A[2]+'0');
                str.push_back(A[3]+'0');
            }
            
        }while(next_permutation(A.begin(),A.end()));
        
        return str;
    }
};

Weekly contest 113总结：
本次一道题都没有AC，难受。不过也更有动力刷题，不断刷题，刷透题，及时复习总结，同时调整心态保持平常心。
第二道还是自认为问题不大的树的题目，也没有做出来，任何题目都不能掉以轻心。