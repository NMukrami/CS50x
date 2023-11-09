SELECT
  "name"
FROM
  "people"
  JOIN "movies" ON movies.id = stars.movie_id
  JOIN "stars" ON people.id = stars.person_id
WHERE
  movies.id IN (
    SELECT
      movies.id
    FROM
      "movies"
      JOIN "people" ON people.id = stars.person_id
      JOIN "stars" ON movies.id = stars.movie_id
    WHERE
      people.birth = '1958'
      AND people.name = 'Kevin Bacon'
  )
  AND people.name != 'Kevin Bacon';