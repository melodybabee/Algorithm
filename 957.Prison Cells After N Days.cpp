题意：
更新数组，一个位置两侧是一样的数字那么更新为1，如果不同更新为0，求出更新N次后的数组。
思路：
1.本题可以设置一个数组记录下每次更新后的值，用一个for循环对每一位上的数字进行更新。
2.但是如果N非常大的话本题会TLE，通过观察返现N在一定次数之后会进行重复，重复过后就是不断找规律的题目了。
3.那么可以新建两个数组，一个用来记录第一个数组的值，一个用来记录更新后的值。
如果更新后的数组等于第一个数组的值，说明已经找到循环的次数，对N进行取余即可。
4.每次进入循环之后对N进行减1操作，在N为0的时候结束循环输出数组。
class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        vector<int>f,n(8,0);
        for(int cycle = 0; N-- > 0 ; cells = n,++cycle){
            for(auto j = 1; j < 7; ++j) n[j] = cells[j - 1] == cells[j + 1];
            if (cycle == 0) f = n;
            else if(n == f) N %= cycle;
        }
        return cells;
    }
};


Weekly Contest 115总结：
1.只做了一道判断是否是完全二叉树的题目，近几次一直没有什么进步，思考题目上不够专注不太踏实。
要从现在开始改进，还是一直强调的必须要有思考的过程。