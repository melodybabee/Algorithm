题意：
找到int数组中能形成的最大数字，转换为string型
思路：
1.首先用to_string将所有的整数转换为string类型，push到新的数组中
2.自定义排序方法，两个string相加，由大到小排列
如果ab > ba，则a排在前面，比如9和34，由于934>349，所以9排在前面，再比如说30和3，由于303<330，所以3排在30的前面。
3.最后依次相加新数组中的字符串，如果结果第一位是0，那么返回0，如果不是返回结果
class Solution {
private:
    static bool compareNum(string s1, string s2){
        return s1+s2 > s2+s1;
    }

public:
    string largestNumber(vector<int>& nums) {
        vector<string> temp;
        string ret;
        for(auto n : nums){
            temp.push_back(to_string(n));
        }
        sort(temp.begin(),temp.end(),compareNum);
        for(int i = 0; i< temp.size(); ++i){
            ret += temp[i];
        }
        return ret[0] == '0' ? "0" : ret;
    }
};
优化：
也可以直接在sort函数中调用compareNum函数从而自定义排序结果。
注意因为是在sort函数中改变原有值，所有操作要在sort()方法内，同时加；结尾。
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        string ret;
        sort(nums.begin(),nums.end(),[](int a, int b){
            return to_string(a)+to_string(b) > to_string(b)+to_string(a);
        });
        for(int i = 0; i< nums.size(); ++i){
            ret += to_string(nums[i]);
        }
        return ret[0] == '0' ? "0" : ret;
    }
};

补充：
sort排序方法：
sort(a,a+n)代表从a首地址到a的尾地址按默认的从小到大排序
bool compareNum(const int &odd1,const int &odd2)
{
	return odd1>odd2;
}
1.bool格式的返回值
2.有两个参数变量，const不会在引用中改变本身的值
3.返回的是两个参数想要得到的排列结果
比如结构体排序：
struct stu  
{  
    int num;  
    float grade;  
};
bool compareNum(const stu* st1,const stu* st2)  
{  
    return st1->grade>st2->grade;  
}  
输出的是由大到小的grade值。

多重因素排序：
struct  stu
{
	std::string name;
	int grade;
};
//const表示引用变量不会在函数中被改变
bool compare(const stu& st1,const stu& st2)
{
	if(st1.grade>st2.grade)
		return 1;
	else if(st1.grade==st2.grade&&st1.name<st2.name)
		return 1;
	else
		return 0;
}
先按照grade由大到小排序，如果相等，按名字字典序小的在前面。