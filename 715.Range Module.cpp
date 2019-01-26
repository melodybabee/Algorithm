题意：
设计一个范围模块用于数组区间的插入，查找和删除。
方法一：遍历
思路：
1.首先建立一个全局变量表示所要操作的一对数字，以pair<>形式出现
2.在插入过程中，建立一个临时的数组作为临时操作，依次遍历判断区间范围。同时用一个变量来记录需要插入的位置。
如果右边界大于左边，那么直接跳出，同时对插入位置+1。
如果左边界小于右边，那么直接跳过，输入原数组即可。
如果所要插入的位置与原来的区间有交集，那么左边取小，右边取大即可。
遍历结束之后在指定位置插入新的左右区间，用全局变量替换临时变量。
3.在查找过程中，依次遍历判断是否在当前区间内即可，有的话返回true
4.删除过程与插入过程类似，但是如果有新的区间在以前两者的区间之间的情况的话，需要一个临时的pair来记录下新的区间对。
在临时数组中插入新的值，如果没有就插入空，再把临时数组替换为全局变量。
class RangeModule {
private:
    vector<pair<int,int>>vec;
public:
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        vector<pair<int,int>>temp;
        int cur = 0;
        for(int i = 0 ; i < vec.size();++i){
            if(vec[i].second < left){
                temp.push_back(vec[i]);
                ++cur;
            }else if(vec[i].first > right){
                temp.push_back(vec[i]);
            }else{
                left = min(vec[i].first,left);
                right = max(vec[i].second,right);
            }
        }
        temp.insert(temp.begin()+cur,{left,right});
        vec = temp;
    }
    
    bool queryRange(int left, int right) {
       for(int i = 0 ; i< vec.size(); ++i){
           if(left >= vec[i].first && right <= vec[i].second) return true;
       }
       return false;
    }
    
    void removeRange(int left, int right) {
        vector<pair<int,int>>temp;
        vector<pair<int,int>>s;
        int cur = 0;
        for(int i = 0; i < vec.size(); ++i){
            if(vec[i].second <= left){
                temp.push_back(vec[i]);
                ++cur;
            }else if(vec[i].first >= right){
                temp.push_back(vec[i]);
            }else{
                if(vec[i].first < left){
                    s.push_back({vec[i].first,left});
                }
                if(vec[i].second > right){
                    s.push_back({right,vec[i].second});
                }
            }
        }
        temp.insert(temp.begin()+cur,s.begin(),s.end());
        vec = temp;
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule obj = new RangeModule();
 * obj.addRange(left,right);
 * bool param_2 = obj.queryRange(left,right);
 * obj.removeRange(left,right);
 */
方法二：map
思路：
1.利用map来直接建立映射，在插入过程中用upper_bound()分别找到左边界和右边界的更大一位的位置
如果有比左边界大的位置，那么做指针减小一位，如果右侧要比做指针指向的位置小，那么再加上一位
如果新的区间范围是独立出来的，那么直接插入到map中。如果左右不等，说明有交叉的区间，取较大的范围同时把之前的范围删除。
2.在查找方法中，找到比左边界大的位置，判断是否是第一位同时其右边界是否小于右侧，是的话返回false,否则返回true
3.删除过程与插入类似，如果左右位置相等，那么直接返回，说明本身就没有当前区间
否则分别取左右较小和较大，判断是否能够分成两个区间
class RangeModule {
private:
    map<int,int>m;
public:
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        auto l = m.upper_bound(left);
        auto r = m.upper_bound(right);
        if(l != m.begin()){
            --l;
            if(l->second < left) ++l;
        }
        if(l != r){
            left = min(l->first,left);
            right= max(right,(--r)->second);
            m.erase(l,++r);
        }
        m[left] = right;
    }
    
    bool queryRange(int left, int right) {
        auto it = m.upper_bound(left);
        if(it == m.begin() || (--it)->second < right) return false;
        return true;
    }
    
    void removeRange(int left, int right) {
        auto l = m.upper_bound(left);
        auto r = m.upper_bound(right);
        if(l != m.begin()){
            --l;
            if(l->second < left) ++l;
        }
        if(l == r) return;
        int l1 = min(l->first,left);
        int r1 = max(right,(--r)->second);
        m.erase(l,++r);
        if(l1 < left) m[l1] = left;
        if(r1 > right) m[right] = r1;
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule obj = new RangeModule();
 * obj.addRange(left,right);
 * bool param_2 = obj.queryRange(left,right);
 * obj.removeRange(left,right);
 */