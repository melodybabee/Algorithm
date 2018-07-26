class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> ret;
        if(digits[digits.size()-1] != 9){
            digits[digits.size()-1] += 1;
            ret = digits;
            }
        
        else if(digits[digits.size()-1] == 9 && digits[0]!= 9){
            for (int i = digits.size()-1;i >= 0; --i){
                if(digits[i] == 9){
                   digits[i] = 0;}
                else{
                   digits[i] += 1;
                   break;
                    }
                }
                ret = digits;
            }
        
        else if(digits[digits.size()-1] == 9 && digits[0]== 9){
            ret.push_back(1);      
            for(int i = 0; i < digits.size();++i){
                if(digits[i] == 9)
                    digits[i] = 0;
                else{
                    digits[i] += 1;
                    }
                ret.push_back(digits[i]);
                }
            }
        
        return ret;
        }
};
/*
设计思路：
1.判断最后一位，如果不是9，直接+1
2.如果最后一位是9而第一位不是9，从后往前循环，遇到9归0，直到不是9的时候加1，break
3.如果最后一位和第一位都是9，现在第一位push_back（1），从前往后循环，遇到9归0，不是9加1，逐一push_back

注意：
1.认真检查写的每一个语法，runtime error的错误大部分因为溢出，或者引用了没有声明的内存
2.如果想每个if循环执行后直接return, 从第二个if语句要写成else if,否则会依次执行if

优化：
void plusone(vector<int> &digits)
{
  int n = digits.size();
  for (int i = n - 1; i >= 0; --i)
  {
    if (digits[i] == 9)//从后向前循环，只要为9，置0
    {
      digits[i] = 0;
    }
    else
    {
      digits[i]++;//如果不为9，加1
      return;
    }
  }
    digits[0] =1;//99，999，9999情况
    digits.push_back(0);//最后补一位9
    
}
*/