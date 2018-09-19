# Write your MySQL query statement below
select FirstName, LastName, City, State from 
    Person left join Address
        on Person.PersonId = Address.PersonId
本题中用on不用where的原因：
on和where的选择条件的区别：
#on后面的是连接条件，代表两个表建立关系所遵循的规则
#where后面的可以看作是筛选条件，是对最终结果集进行过滤所遵循的规则

本题涉及SQL的操作，以题目中的数据为例
创建表格：
Create table Person (PersonId int, FirstName varchar(255), LastName varchar(255))
Create table Address (AddressId int, PersonId int, City varchar(255), State varchar(255))
Truncate table Person
insert into Person (PersonId, LastName, FirstName) values ('1', 'Wang', 'Allen')
Truncate table Address
insert into Address (AddressId, PersonId, City, State) values ('1', '2', 'New York City', 'New York')
输出的表格是：

Table: Person

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| PersonId    | int     |
| FirstName   | varchar |
| LastName    | varchar |
+-------------+---------+
PersonId is the primary key column for this table.
Table: Address

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| AddressId   | int     |
| PersonId    | int     |
| City        | varchar |
| State       | varchar |
+-------------+---------+
AddressId is the primary key column for this table.

1.where 和 on 的区别
2.left join, right join and innner join
***************************************
左连接：关键字会从左表 (table_name1) 那里返回所有的行，即使在右表 (table_name2) 中没有匹配的行。
例如：
"Persons" 表：
-------------------------------------------------------------
Id_P	    LastName	FirstName	Address	        City
-------------------------------------------------------------
1	        Adams	    John	    Oxford Street	London
2	        Bush	    George	    Fifth Avenue	New York
3	        Carter	    Thomas	    Changan Street	Beijing
-------------------------------------------------------------

"Orders" 表：
---------------------
Id_O	OrderNo	Id_P
---------------------
1	    77895	3
2	    44678	3
3	    22456	1
4	    24562	1
5	    34764	65
---------------------
操作：
SELECT Persons.LastName, Persons.FirstName, Orders.OrderNo FROM 
	Persons LEFT JOIN Orders
		ON Persons.Id_P=Orders.Id_P
		ORDER BY Persons.LastName
结果：
--------------------------------
LastName	FirstName	OrderNo
--------------------------------
Adams	    John	    22456
Adams	    John	    24562
Carter	    Thomas	    77895
Carter	    Thomas	    44678
Bush	    George
--------------------------------
***************************************
右连接：与左连接类似，关键字会从右表 (table_name2) 那里返回所有的行，即使在左表 (table_name1) 中没有匹配的行。
***************************************
在表中存在至少一个匹配时，INNER JOIN 关键字返回行。INNER JOIN 和 JOIN 是相同的。
INNER JOIN 关键字在表中存在至少一个匹配时返回行。如果 "左表" 中的行在 "右表" 中没有匹配，就不会列出这些行。
