题意：
design类型的题目，设计一个方法输出到当前等待时间在3000毫秒之内的拨打次数。
方法一：直接vector循环
思路：
1.每次ping一个数字，都把它放到vector中，从0开始计数，遍历vector。
2.如果不为0且vector中某位置上的值大于等于输入值-3000，计数器+1
3.最后返回计数器的个数
class RecentCounter {
private:
    vector<int> ans;
public:
    RecentCounter() {
    }
    
    int ping(int t) {
        ans.push_back(t);
        int count = 0;
        for(int i = 0; i< ans.size();++i){
            if(ans[i] != NULL && ans[i]>= t-3000)
                ++count;
        }
        return count;
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
 优化：
 方法二：利用queue，效率大大提高
 思路：
 1.利用题目中说到的后ping的大小一定会大于之前的，那么正好符合queue后进先出的性质，直接push到queue中即可
 2.如果queue不为空，且queue的头部元素超出了输入值的范围，那么pop出来
 3.最后返回queue的大小即可
class RecentCounter {
public:
    queue<int> q;
    RecentCounter() {
        q = queue<int>();
    }
    
    int ping(int t) {
        while(!q.empty() && q.front() < t-3000) q.pop();
        q.push(t);
        return q.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
 Contest 109总结：
 1.第一题是design类型的题，题目本身很简单，但是理清题意花了多长时间。
 现在出现的问题是对于一些场景类的题目，需要有大量文字信息来理解题意的题目开始读不明白，也有抵触情绪，需要重点练习。
 design的思路和各个方法的如何调用、设计类属性理解的仍然不是很透彻，加强工程能力。尽量从main函数开始自己写test case,至少会写，不能每次只会写所要求写的方法。
 2.第二题理清题意后知道思路，但是写不明白，见题少，dp类的题目还需要练习。