SELECT DISTINCT
  "name"
FROM
  "people"
  JOIN "ratings" ON movies.id = ratings.movie_id
  JOIN "directors" ON people.id = directors.person_id
  JOIN "movies" ON movies.id = directors.movie_id
WHERE
  "rating" >= '9.0';