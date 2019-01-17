Shuffle 洗牌
题意：数组洗牌
思路：
1.题目中的意思是shuffle() 方法获得随机顺序的数组，reset()恢复原数组顺序
2.那么在洗牌方法中，首先建立一个临时数组，为了不破坏数组本身，随机生成坐标来完成随机数字的生成，最后交换即可。
注意：
1.c++生成随机数调用rand()方法
2.每次想获得一定范围内的随机数，就用随机获得的数字对范围的最大值取余即可。
class Solution {
private:
    vector<int> ans;
public:
    Solution(vector<int> nums) {
        ans = nums;
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return ans;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> temp = ans;
        for(int i = 0; i < temp.size(); ++i){
            int j = rand() %temp.size();
            swap(temp[i],temp[j]);
        }
        return temp;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */

补充：洗牌的正确姿势-Knuth shuffle算法
1.因为单纯的产生随机数字再进行交换不能保证所有的情况等概率，那么在样本数量非常大的情况下，就不能满足随机的含义
2.Knuth洗牌算法在上述方法的基础上，做一处修改，就能剪去一些分支，让分支数是N!的整数倍。
唯一修改的就是随机牌j选取的方法，在拿起第i张牌时，只从它前面的牌随机选出j，而不是从整副牌里面随机选取。
优化：
class Solution {
private:
    vector<int> ans;
public:
    Solution(vector<int> nums) {
        ans = nums;
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return ans;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> temp = ans;
        for(int i = 0; i < temp.size(); ++i){
            int j = i+rand() %(temp.size()-i);
            swap(temp[i],temp[j]);
        }
        return temp;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */