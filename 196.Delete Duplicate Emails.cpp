# Write your MySQL query statement below
DELETE
    p1
FROM
    Person p1, Person p2
WHERE
    p1.Email = p2.Email AND p1.Id > p2.Id
;

思路：
1.删除表中邮箱相同的姓名，可以使用内连接，把邮箱相等的找到，同时保留Id号大的那个  