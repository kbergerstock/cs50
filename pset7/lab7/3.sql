select * from
    (SELECT name from songs order by duration_ms desc)
    limit 5;

