# Write your MySQL query statement below
SELECT 
    a.Name AS Employee
FROM
    Employee AS a,
    Employee AS b
    WHERE a.ManagerId = b.Id
        AND a.Salary > b.Salary
;

注意：
1.要从两个Employee表格中进行SELECT,设为a,b 
2.SQL自连接：
SQL自连接被用来联接表本身以作为两个表，暂时重命名，在SQL语句中至少有一个表。
基本语法：
SELECT a.column_name, b.column_name...
FROM table1 a, table1 b
WHERE a.common_field = b.common_field;
