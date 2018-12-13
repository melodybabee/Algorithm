题意：
在一个数组中找到其右侧比它小的数字的个数，在新数组的对应位置返回该值。
方法一：暴力拆解
思路：
两层for循环查找右侧比当前数字小的数字并返回到新的数组中。
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> ret(nums.size(),0);
        for(int i = 0; i < nums.size(); ++i){
            int count = 0;
            for(int j = i+1; j < nums.size(); ++j){
                if(nums[j] < nums[i]) ++ count;
                ret[i] = count;
            }
        }
        return ret;
    }
};
方法二：二叉搜索+插入排序
思路：
1.因为题目中要求的是找到右侧比该数字小的数，那么从数组的尾部开始循环，二叉搜索形成新的数组，这样插入的位置的坐标就是右侧数字中比自己小的个数。
2.用一个temp数组来记录临时新形成的数组，ret数组用来记录右侧小数的个数并返回。
注意：
1.vector<int> ret(nums.size())在声明数组的时候只确认了数组的大小表示创建了一个大小为指定值，值为0的数组。
2.vector.insert(a,b)方法表示在数组的a位置插入b元素。
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> temp;
        vector<int> ret(nums.size());
        for(int i = nums.size()-1; i >= 0; --i){
            int left = 0;
            int right = temp.size();
            while(left < right){
                int mid = left + (right - left)/2;
                if(temp[mid] >= nums[i]) right = mid;
                else left = mid+1;
            }
            ret[i] = right;
            temp.insert(temp.begin()+right,nums[i]);
        }
        return ret;
    }
};
方法三：运用内置的lower_bound函数优化插入排序
思路：
1.和方法3相同，运用lower_bound()找到在新的构造数组中第一个不小于当前数字的位置，用distance()返回其到起始位置的距离。
2.把距离更新到要返回的数组中去，并在临时数组中的对应位置该值，
注意：
1.C++的STL中的distance()函数用来求两个迭代器之间的元素个数。
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> temp;
        vector<int> ret(nums.size());
        for(int i = nums.size()-1; i >= 0; --i){
            int d = distance(temp.begin(),lower_bound(temp.begin(),temp.end(),nums[i]));
            ret[i] = d;
            temp.insert(temp.begin()+d,nums[i]);
        }
        return ret;
    }
};
方法4:构造二叉搜索树
思路：
1.注意构造二叉搜索树的性质是从结点开始大于他的放在右侧，小于他的放在左侧，中序遍历后是单增的。
2.首先依旧先从数组的尾部开始往前依次循环，每遍历到一个新的值，在搜索树中插入。
3.二叉搜索树的构造包括根结点的值，左右指针，和在结点处记录一个值表示比当前节点值小的所有节点的个数。
插入方法中如果根结点不存在，创建根结点，返回0；
如果小于他，smaller值加1，插入到结点的左侧；
如果大于他，在右侧插入该结点，返回递归得到的值+根结点已经记录的值（因为比根结点小一定比根结点的右结点小）+根结点本身是否比该右子树结点小（小为1，等于为0）
注意：
1.注意构造新的数据结构要有struct+结构名+由；结尾的{}
在构造方法中建立初始化的方法，后面用于overriding,因此要有{};
2.如果想在一个递归语句里面既完成递归又有返回值，在return两个语句中间写为逗号即可。
例如：return ++root->smaller,insert(root->left, v);
class Solution {
public:
    struct Node{
        int val, smaller;
        Node *left;
        Node *right;
        Node(int v,int s):val(v), smaller(s), left(NULL),right(NULL){};
    };
    vector<int> countSmaller(vector<int>& nums) {
        vector<int>ret(nums.size());
        Node *root = NULL;
        for(int i = nums.size()-1; i >= 0; --i){
            ret[i] = insert(root, nums[i]);
        }
        return ret;
    }
    int insert(Node*&root, int v){
        if(!root){
            root = new Node(v,0);
            return 0;
        }
        if(v < root -> val){
            return ++root->smaller,insert(root->left, v);
        }
        else{
            return insert(root -> right, v) + root -> smaller + (root -> val < v ?1 :0);
        }
    }
};

12.13复习：
建造二叉树注意：
1.要从数组的右侧依次向前开始循环
2.根结点要用引用的方式构造
class Solution {
public:
    struct Node{
        int val;
        int min;
        Node *left;
        Node *right;
        Node(int v,int m):val(v),min(m),left(NULL),right(NULL){};
    };
    
    vector<int> countSmaller(vector<int>& nums) {
        vector<int>ret(nums.size());
        Node *root = NULL;
        for(int i= nums.size()-1; i >= 0; --i){
            ret[i]= insert(root,nums[i]);
        }
        return ret;
    }
    
    int insert(Node *&root,int i){
        if(!root){
            root = new Node(i,0);
            return 0;
        }
        if(root -> val < i){
            return insert(root -> right,i) + root -> min + (root -> val < i? 1: 0);
        }else{
            return ++root -> min, insert(root -> left,i);
        }
    }
};