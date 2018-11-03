prefix 前缀
题意：
实现trie树的插入，查找，查找前缀的结构。
思路：
1.trie树的特点是把公共前缀储存起来，主要有以下3个特点：
(1)根节点不包含字符，除根节点以外每个节点只包含一个字符。
(2)从根节点到某一个节点，路径上经过的字符连接起来，为该节点对应的字符串。
(3)每个节点的所有子节点包含的字符串不相同。
2.从结点到儿子的指向：对每个结点开一个字母集大小的数组，数组的位置就是相应字母的顺序。
3.那么Trie()方法就是创建一个根结点，根结点中有一个字母集大小的数组，数组中的内容都是TrieNode类型，还有一个标记位记录是否是一个完整的单词。
4.insert方法遍历单词，如果字母不存在，那么插入对应位置，并把该位置中再创建一个新的TrieNode根结点。指针指向这个位置。
如果字母存在，那么直接指向这个位置。
循环完一个单词之后把这一位的标记为true,为一个完整的单词。
5.search方法同样循环单词，如果没有，返回false,如果一直有，最后循环结束判断标志位是否为true;
6.查找前缀的时候直接查找，如果没有返回false,循环完毕就返回true
注意：
1，在新建一个数据结构的时候，要把该结构写在最开始，作为新建。不要忘记每新建一个class,都是要以;结尾。
同时每个class中都需要包含public: 或者private：等等
2.在另一个class中调用另一个class中的数据结构，常用private+变量名称作为自己这个class中的变量。
class TrieNode{
public:
    TrieNode *child[26];//TrieNode中的变量声明
    bool isword;
    TrieNode() : isword(false){//把标志位初始值定为false,数组中全部初始为空
        for(auto &a: child) a = NULL;
    }
};

class Trie {
private:
    TrieNode *root;//Trie中的变量声明，创建了一个TrieNode类型的根结点指针变量
public:
    /** Initialize your data structure here. */
    Trie() {//给根结点指针赋值，创建新的TrieNode对象
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *p = root;
        for(auto &a : word){
            int i = a - 'a';
            if(!p -> child[i]) p -> child[i] = new TrieNode();
            p = p -> child[i];
        }
        p -> isword = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode *p = root;
        for(auto &a :word){
            int i = a -'a';
            if(!p -> child[i]) return false;
            p = p -> child[i];
        }
        return p -> isword;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode *p = root;
        for(auto &a : prefix){
            int i = a - 'a';
            if(! p -> child[i]) return false;
            p = p -> child[i];
        }
        return true;
        
    }
};


/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */