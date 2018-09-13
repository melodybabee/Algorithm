class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> vec;
        for(int i = 1; i <= numRows; ++i)
            vec.push_back(vector<int> (i,1));
        
        for(int i = 0; i < numRows; ++i){
            for(int j = 1; j < vec[i].size()-1; ++j){
                vec[i][j] = vec[i-1][j-1]+vec[i-1][j];
            }
        }
        return vec;
    }
};
//非递归算法
/*
思路：
1.杨辉三角不需要把第一行位置的元素放在中间，因此可以看作是
{[1]
[1,1]
[1,2,1]
[1,3,3,1]}
的vector中嵌套的vector
2.首先可以创建整个矩阵，将所有位置填充上1
3.更改数值，用i来循环行，用j循环列，在第三行之后，除首尾元素外，第j个元素的值等于上一行此位置与此位置的前一位

注意：
1.思路的巧妙点在于首先用1填充上所有的元素值
注意此时i从第一位开始，如果i=0， 会出现vector<int>(0,1)的情况,出现“member access within misaligned address 0x000100000006 for type 'struct mynode', which requires 8 byte alignment”的错误
2.注意i ,j从哪里开始循环，for循环的中间判断语句是什么
j循环的长度需要用i的size来制约，同时剔除掉最后一位
*/
//递归算法
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if(numRows == 0) return vector<vector<int>>(0);
        if(numRows == 1) return vector<vector<int>>(1,vector<int>(1,1));
        vector<vector<int>> res = generate(numRows-1);
        vector<int> p(numRows, 1);
        for(int i = 1; i < numRows-1; ++i){
            p[i] = res[numRows-2][i]+res[numRows-2][i-1];
        }
        res.push_back(p);
        return res;
    }
};
/*
思路：
1.递归自上而下解决问题，第3行的值等于上一行此位置与其前一位的求和
2.因此首先列出第一行和当numRows为0的情况，作为前提条件
3.进行到当位之后，创建子vector,首先将本行的所有元素填为1之后，用i循环进行修改（杨辉三角中行数和列数都为i-1）
4.最后push到大的vector中
*/