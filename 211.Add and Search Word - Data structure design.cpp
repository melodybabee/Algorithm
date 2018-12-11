题意：设计trie树来查找单词。
思路：
1.类似208设计trie的结构。
2.不同之处是如果是'.'那么需要调用DFS遍历，注意递归过程中如果i的个数等于单词长度，那么返回true
遇到'.'返回它以及它的下一位是否存在
否则如果目前的根结点中不存在root -> child，那么返回false,如果存在调用递归
class TrieNode{
public:
    TrieNode *child[26];
    bool isword;
    TrieNode(): isword(false){
        for(auto &a : child) a = NULL;
    }
};

class WordDictionary {
private:
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode *p  = root;
        for(auto a: word){
            int i = a -'a';
            if(!p->child[i]) p ->child[i] = new TrieNode();
            p = p -> child[i];
        }
        p -> isword = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return helper(word, 0, root);
    }
    
    bool helper(string word, int i , TrieNode *root){
        if(i == word.size()) return root -> isword;
        if(word[i] == '.'){
            for(auto a : root -> child){
                if(a && helper(word,i+1,a)) return true;
            }
            return false;
        }else{
            if(!root -> child[word[i] - 'a']) return false;
            else return helper(word,i+1,root -> child[word[i] - 'a']);
        }

    }
    
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */