题意：
由高到低输出一个文件中所有单词和其频率。
*************************************
方法一：grep
grep -oE '[a-z]+' words.txt | sort | uniq -c | sort -nr | awk '{print $2" "$1}'
1.-oE '[a-z]+'参数表示原文本内容变成一个单词一行的存储方式
以示例举例：
the
day
is
sunny
the
the
the
sunny
is
2.sort表示对现有的单词进行升序排列
day
is
is
is
sunny
sunny
the
the
the
the
3.uniq -c表示去重，在前面加上编号
	1 day
	3 is
	2 sunny
	4 the
4.sort -nr表示对数字进行降序排序
    4 the
    3 is
    2 sunny
    1 day 
5.最后用awk输出元素，先输出单词再输出频数
注意：
-oE后面要有空格！

补充：
1.grep:是一种强大的文本搜索工具，它能使用正则表达式搜索文本，并把匹配的行打印出来。
http://www.cnblogs.com/peida/archive/2012/12/17/2821195.html
2.Linux shell sort
https://blog.csdn.net/monkeyduck/article/details/10097829
sort 从首字符向后，依次按ASCII码值进行比较，最后将他们按升序输出。
sort -u 输出行中去除重复行
sort -r 将输出的模式由升序变成降序
sort -n 按数值来排序
3.linux去除重复行命令uniq
http://blog.51yip.com/shell/1022.html
对文本操作时，它一般会和sort命令进行组合使用，因为uniq不会检查重复的行，除非它们是相邻的行。如果您想先对输入排序，使用sort -u。
-c, --count    //在每行前加上表示相应行目出现次数的前缀编号  

*************************************
方法二：tr写法
tr -s ' ' '\n' <words.txt | sort | uniq -c | sort -nr | awk '{print $2" "$1}'
或者
tr -s ' ' '\n' <words.txt | sort | uniq -c | sort -nr | awk '{print $2,$1}'
思路：
1.-s表示如果发现连续的字符，就把它们缩减为1个，用换行来替换空格，能达到一行一个单词的效果
2.<+文件名称
注意：
1.\n表示换行
补充：
1.tr:字符替换，大小写替换
http://www.cnblogs.com/leaven/archive/2011/01/05/1926194.html
tr命令不接受指定的文件参数，而只是对标准输入进行翻译。

*************************************
方法三：awk实现【存疑】
思路：
1.首先把单词和数字分成不同的两列，第一列是单词，第二列是频数
2.打印出单词和频数
3.sort -nr -k 2 对第二列的数字降序排列
# Read from the file words.txt and output the word frequency list to stdout.
awk '{
    for (i = 1; i <= NF; ++i) ++s[$i];
} END {
    for (i in s) print i, s[i];
}' words.txt | sort -nr -k 2

