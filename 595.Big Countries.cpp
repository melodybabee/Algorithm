题意：筛选出占地面积大于三百万或者人口大于25百万的所有城市
注意：
1.25百万是两千五百万
2.为了便于美观需要把所有MYSQL的关键字进行大写
# Write your MySQL query statement below
SELECT name, population, area 
FROM World 
WHERE area > 3000000 OR population > 25000000;

优化：UNION写法
比OR更快，尤其是在扫描两个不同的表的时候比OR快的更明显。
因为在用OR的时候，在做第一个判断条件的时候仍然需要扫描第二个判断条件，做第二个判断的时候同理还需要再次判断第一个条件。
但是用UNION的时候就不需要，分别根据第一个和第二个判断条件进行扫描，再把他们结合在一起即可。
# Write your MySQL query statement below
SELECT name, population, area 
FROM World 
WHERE area > 3000000 

UNION

SELECT name, population, area 
FROM World 
WHERE population > 25000000;