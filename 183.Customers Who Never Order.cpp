# Write your MySQL query statement below
SELECT
    Customers.Name as Customers
FROM
    Customers
WHERE 
    Customers.Id NOT IN(
    SELECT 
        CustomerId 
    FROM
        Orders
    );
    
1.用NOT IN来判断不在另一个表格中的CustomerId