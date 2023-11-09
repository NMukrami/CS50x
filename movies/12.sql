SELECT
  "title"
FROM
  "movies"
  JOIN "people" ON people.id = stars.person_id
  JOIN "stars" ON movies.id = stars.movie_id
WHERE
  people.name IN ('Johnny Depp', 'Helena Bonham Carter')
GROUP BY
  movies.title HAVING COUNT(DISTINCT people.name) = 2;