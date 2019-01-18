题意：知道工人的性价比和工资，求目标个工人最少花多少钱
思路：
1.因为每个工人的工资需要和他其他人成比例，所以满足关系wage[i] : wage[j] = quality[i] : quality[j]
那么对于每个人来说，都会有一个比值wage[i] : quality[i] = wage[j] : quality[j]，如果想总花费最小，那么应该使比值最小
2.那么首先建立一个数组，求出所有的比值，并进行排序。注意此处要转换为double类型。
因为后面需要根据比较的排序来逐渐相加q,因此是一个二维数组的形式，
3.因为要取前K个，那么遇到此类问题用heap解决最方便，c++默认是最大栈。
4.开始遍历二维数组，每次对数组中的q进行相加，并放入最小栈。如果栈中的数量等于K，那么用当前的q的和与当前的比值进行相乘。
继续遍历，如果大于K，那么去掉最小栈的顶部元素，即目前为止最大的q值，再次进行比较，最后的结果取较小。
注意：
因为最后求的是工资，所以比值用工资除以q会更好。最后会以w/q * q的形式得到结果。
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        vector<vector<double>>vec;
        priority_queue<int>q;
        double ret = DBL_MAX;
        for(int i = 0; i < quality.size();++i){
            vec.push_back({(double)wage[i]/quality[i],(double)quality[i]});
        }
        sort(vec.begin(),vec.end());
        int sum = 0;
        for(auto v: vec){
            sum += v[1];
            q.push(v[1]);
            if(q.size() > K ){
                sum -= q.top();
                q.pop();
            }
            if(q.size() == K) ret = min(ret,sum * v[0]);
        }
        return ret;
    }
};