题意：
输出文件中的第10行
**********************************************
方法一：awk
awk '{if(NR == 10) print $0}' file.txt

优化：
awk '(NR == 10)' file.txt
wk的默认动作就是print $0,因此NR == 10后面不需要加print %0

补充：
from : http://blog.51cto.com/tanxin/1222140
1.awk：shell脚本，文本处理工具
功能：流控制、数学运算、进程控制、内置的变量和函数、循环和判断
2.工作原理：
awk 会把每行进行一个拆分，用相应的命令对拆分出来的“段”进行处理。
(1）行工作模式，读入文件的每一行，会把一行的内容，存到$0里
(2）使用内置的变量FS(段的分隔符，默认用的是空白字符)，分割这一行，把分割出来的每个段存到相应的变量$(1-100)
(3）输出的时候按照内置变量OFS(out FS)，输出
(4）读入下一行继续操作
例如：
# echo "this is a book" > awk.txt
# awk '{print $2,$1,$3,$4}' awk.txt
is this a book
3.【NR】NR表示从awk开始执行后，按照记录分隔符读取的数据次数，默认的记录分隔符为换行符，因此默认的就是读取的数据行数，NR可以理解为Number of Record的缩写。从1开始。
【FNR】在awk处理多个输入文件的时候，在处理完第一个文件后，NR并不会从1开始，而是继续累加，因此就出现了FNR，每当处理一个新文件的时候，FNR就从1开始计数，FNR可以理解为File Number of Record。
**********************************************
方法二：sed
sed -n 10p file.txt
-n默认表示打印所有行，p限定了打印的行数。如果不够10行则什么都不打印

补充：
from: http://blog.51cto.com/tanxin/1208944
1.功能：
sed是一款流编辑工具，用来对文本进行过滤与替换工作，sed通过输入读取文件内容，但一次仅读取一行内容进行某些指令处理后输出，sed更适合于处理大数据文件。
2.工作原理：
sed在处理文本文件的时候，会在内存上创建一个模式空间，然后把这个文件的每一行调入模式空间用相应的命令处理，处理完输出；接着处理下一行，直到最后。
3.与vim区别：
vim需要通知处理文件的哪几行才会去处理，sed默认会处理文件的所有行，除非你告诉它不处理哪几行。
**********************************************
方法三：tail and head作为关键字处理
tail -n +10 file.txt | head -n 1 
tail从第10行开始打印，打印的结果传给后面，从头部开始打印第一行
head -n 10 file.txt | tail -n +10
head打印了前10行，tail在结果中从第10行开始打印，不能写成打印最后一行，最后一行是9不是10【存疑】

tail and head: http://www.it610.com/article/1196291.htm
linux pipeline: http://www.programgo.com/article/6462705832/;jsessionid=01A7179C41368EACBD963D21018878B2
补充：
1.tail -n 3 file.txt: 打印file文件的最后三行内容　　　　　　
tail -n +3 file.txt： 从file文件第三行开始打印所有内容，从前三行之后开始打印
head -n 3 file.txt： 打印file文件的前三行
head -n -3 file.txt： 打印file文件除了最后三行的所有内容，打印到最后三行以前
2.pipeline原则：
用法: command 1 | command 2 他的功能是把第一个命令command1执行的结果作为command 2的输入传给command 2。
