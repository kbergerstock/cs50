select printf("%.4f",avg(energy)) AS average from
    (select energy from songs where artist_id = (select id from artists where name = "Drake"));