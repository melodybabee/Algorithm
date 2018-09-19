# Write your MySQL query statement below
SELECT 
    Email
FROM
    Person
GROUP BY Email
having count(Email) > 1

1.GROUP BY 语句根据一个或多个列对结果集进行分组。在分组的列上我们可以使用 COUNT, SUM, AVG,等函数。
GROUP BY之后可以添加count，count(Email) as num也是一种方式
2.having 
having字句可以让我们筛选成组后的各种数据，where字句在聚合前先筛选记录，也就是说作用在group by和having字句前。
而 having子句在聚合后对组记录进行筛选。