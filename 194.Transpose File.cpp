题意：把文件转制输出
方法一：awk
思路：
1.NF表示当前记录中的字段个数，就是有多少列  
NR表示已经读出的记录数，就是行号，从1开始 
2.如果是第一行，那么添加一个新的s[i],为了把原先的每一列改为新的行
如果不是第一行，直接在s[i]的后面加入遍历到的行中的对应位置的元素即可
3.END表示汇总的操作
4.开始依次输出每个s[i]
# Read from the file file.txt and print its transposed content to stdout.
awk '{
    for(i = 1; i <= NF; ++i){
        if(NR == 1) s[i] = $i;
        else s[i] = s[i] " " $i;
    }
}END{
        for(i = 1; s[i] != ""; ++i){
            print s[i];
        }
}' file.txt
