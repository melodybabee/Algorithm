题意：247follow up，找到指定长度范围内正反相同的数字
思路：
1.同样利用递归解决问题，首先把得到的字符串的长度规定在low和high之间，在这两个值之间循环
2.初始化的时候同样初始化为"","0","1","8"四个值，调用递归函数
3.判断得到的字符串的长度是否大于等于目标值，如果大于或者长度大于1但是第一位为0，直接返回
4.如果递归的长度等于low边界的值，但是得到的字符串的大小小于范围；或者递归的长度等hign边界的值，得到的字符串的长度大于范围，那么也直接返回
利用C++内置的STL函数compare()进行字符串大小的判断
5.如果满足条件，在结果值中+1
6.如果字符串的长度小于规定值，继续在头尾加入数字重新进入递归
class Solution {
public:
    int strobogrammaticInRange(string low, string high) {
        int ret = 0;
        for(int i = low.size(); i <= high.size();++i){
            find(low,high,"",i,ret);
            find(low,high,"0",i,ret);
            find(low,high,"1",i,ret);
            find(low,high,"8",i,ret);
        }
        return ret;
    }
    
    void find(string low,string high, string temp, int i,int &ret){
        if(temp.size() >= i){
            if(temp.size() > i || (i != 1 && temp[0] == '0')) return;
            if(i == low.size() && temp.compare(low) < 0 || i == high.size() && temp.compare(high) > 0) return;
            ++ret;
        }
        find(low,high,"0"+temp+"0",i,ret);
        find(low,high,"1"+temp+"1",i,ret);
        find(low,high,"8"+temp+"8",i,ret);
        find(low,high,"6"+temp+"9",i,ret);
        find(low,high,"9"+temp+"6",i,ret);
    }
};
补充：
C++ compare函数：用来进行字符串以及其子串的比较
1.字符串比较
string str1="hi,test,hello";
string str2="hi,test";
//字符串比较，比较两个字符串的大小
	if(str1.compare(str2)>0)
		printf("str1>str2\n");
	else if(str1.compare(str2)<0)
		printf("str1<str2\n");
	else
		printf("str1==str2\n");
2.子串的比较,判断是否相等
//str1的子串（从索引3开始，包含4个字符）与str2进行比较
	if(str1.compare(3,4,str2)==0)
		printf("str1的指定子串等于str2\n");
	else
		printf("str1的指定子串不等于str2\n");
//str1指定子串与str2的指定子串进行比较
	if(str1.compare(3,4,str2,3,4)==0)
		printf("str1的指定子串等于str2的指定子串\n");
	else
		printf("str1的指定子串不等于str2的指定子串\n")
//str1指定子串与字符串的前n个字符进行比较
	if(str1.compare(0,2,"hi,hello",2)==0)
		printf("str1的指定子串等于指定字符串的前2个字符组成的子串\n");
	else
		printf("str1的指定子串不等于指定字符串的前2个字符组成的子串\n");
	