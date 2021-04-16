select name from people inner join stars on id = person_id where movie_id in
    (select movie_id from stars where person_id in  
        (select id from people where name = 'Kevin Bacon' and birth  = 1958)) and
            name != 'Kevin Bacon'