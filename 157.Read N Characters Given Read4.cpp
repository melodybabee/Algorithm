题意：
把一次读取4个字符的方法更改为一次读取n个的。
方法一：递归
思路：
1.题目中的意思是如果长度大于4个，那么直接返回4，如果小于4那么返回剩余的字符数
2.那么读取n的时候先用一个变量记录下当前读了几个，如果大于等于n，那么直接返回n
3.r如果小于4,那么直接返回该数字。
4.剩下的情况是n个数量要大于4，那么返回的结果是4+从第4个位置开始读取的，读了n-4个数字的结果和。
注意：
1.buf是一个引入流，*buf表示指向buf的指针，因此如果从第4位开始取的话，需要对buf[4]进行取地址操作保证其是一个指针类型
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int temp = read4(buf);
        if(temp >= n) return n;
        if(temp < 4) return temp;
        return 4+read(&buf[4],n-4);
    }
};
方法2:遍历
思路：
1.n中包含几个4就虚幻几次，那么用一个值记录从read4()中得到的结果，如果为0那么直接跳出，说明buf为空。
2.否则结果值加上之前求出的商。
3.最后返回结果值和n中较小的一个。
注意：
read4(buf+res)表示的是buf指针向后移动4个位置，注意buf一直是指针类型。
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int res = 0;
        for(int i = 0 ; i <= n/4;++i){
            int cur = read4(buf+res);
            if(cur == 0)break;
            res+=cur;
        }
        return min(res,n);
    }
};
