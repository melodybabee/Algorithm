# Write your MySQL query statement below
SELECT wt1.Id 
FROM Weather wt1, Weather wt2
WHERE wt1.Temperature > wt2.Temperature AND 
      TO_DAYS(wt1.RecordDate)-TO_DAYS(wt2.RecordDate)=1;

注意：
1.TO_DAYS(wt1.DATE) return the number of days between from year 0 to date DATE
  TO_DAYS(wt1.DATE)-TO_DAYS(wt2.DATE)=1 check if wt2.DATE is yesterday respect to wt1.DATE