# Write your MySQL query statement below
select
    (select DISTINCT
        Salary 
    from
        Employee 
    order by 
        Salary DESC
        LIMIT 1 OFFSET 1) as SecondHighestSalary
注意：   
1.DISTINCT 唯一的、独特的，用于返回唯一不同的值。当多个值相同的时候只返回一个
2.LIMIT 1 OFFSET 1 返回1行，从第二行开始
##第一个被检索的行是第0行，而不是第1行。因此，LIMIT 1 OFFSET 1会检索第2行，而不是第1行
e.g.select * from student limit 4 offset 9,表示返回4行，9表示从表的第十行开始
3.升序：ASC
  降序：DESC
4.需要注意，题意是如果没有第二高，应该返回空
SELECT DISTINCT
    Salary AS SecondHighestSalary
FROM
    Employee
ORDER BY Salary DESC
LIMIT 1 OFFSET 1
如果写成上述代码，不会产生空，只有SecondHighestSalary的标题，WA