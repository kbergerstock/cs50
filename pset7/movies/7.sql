select title, ratings.rating from movies inner join ratings 
    on id = movie_id where year = 2010 order by ratings.rating DESC,title ;



