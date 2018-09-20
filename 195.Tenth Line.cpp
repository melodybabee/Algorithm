awk 'NR == 10' file.txt
相当于awk '{ if (FNR==10) print $0 }' file.txt
awk的默认动作就是print $0,因此NR == 10后面不需要加print %0
【NR】NR表示从awk开始执行后，按照记录分隔符读取的数据次数，默认的记录分隔符为换行符，因此默认的就是读取的数据行数，NR可以理解为Number of Record的缩写。
【FNR】在awk处理多个输入文件的时候，在处理完第一个文件后，NR并不会从1开始，而是继续累加，因此就出现了FNR，每当处理一个新文件的时候，FNR就从1开始计数，FNR可以理解为File Number of Record。

sed -n '10p' file.txt
如果不够10行则什么都不打印