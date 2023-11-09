-- Keep a log of any SQL queries you execute as you solve the mystery.
-- 1
SELECT
  *
FROM
  "crime_scene_reports"
WHERE
  "street" = 'Humphrey Street';

-- 2
SELECT
  "description"
FROM
  "crime_scene_reports"
WHERE
  "year" = '2021'
  AND "month" = '7'
  AND "day" = '28';

-- 3
SELECT
  "description"
FROM
  "crime_scene_reports"
WHERE
  "year" = '2021'
  AND "month" = '7'
  AND "day" = '28'
  AND "street" = 'Humphrey Street';

-- 4
SELECT
  *
FROM
  "interviews"
WHERE
  "transcript" LIKE '%bakery%';

-- 5
SELECT
  "transcript"
FROM
  "interviews"
WHERE
  "year" = '2021'
  AND "month" = '7'
  AND "day" = '28'
  AND "transcript" LIKE "%bakery%";

-- 6
SELECT
  *
FROM
  "bakery_security_logs"
WHERE
  "YEAR" = '2021'
  AND "MONTH" = '7'
  AND "DAY" = '28'
  AND "HOUR" = '10'
  AND "MINUTE" BETWEEN '15' AND '25';

-- 7
SELECT
  "name"
FROM
  "people"
  JOIN "bakery_security_logs" ON bakery_security_logs.license_plate = people.license_plate
WHERE
  bakery_security_logs.year = '2021'
  AND bakery_security_logs.month = '7'
  AND bakery_security_logs.day = '28'
  AND bakery_security_logs.hour = '10'
  AND bakery_security_logs.minute >= '15'
  AND bakery_security_logs.minute <= '25';

-- 8
SELECT
  bakery_security_logs.activity,
  bakery_security_logs.license_plate,
  people.name
FROM
  "people"
  JOIN "bakery_security_logs" ON bakery_security_logs.license_plate = people.license_plate
WHERE
  bakery_security_logs.year = '2021'
  AND bakery_security_logs.month = '7'
  AND bakery_security_logs.day = '28'
  AND bakery_security_logs.hour = '10'
  AND bakery_security_logs.minute >= '15'
  AND bakery_security_logs.minute <= '25';

-- 9
SELECT
  people.name,
  bakery_security_logs.activity,
  bakery_security_logs.license_plate,
  bakery_security_logs.year,
  bakery_security_logs.month,
  bakery_security_logs.day,
  bakery_security_logs.hour,
  bakery_security_logs.minute
FROM
  bakery_security_logs
  JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE
  bakery_security_logs.year = 2021
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute BETWEEN 15 AND 25;

-- 10
SELECT
  *
FROM
  "atm_transactions"
WHERE
  "atm_location" = 'Leggett Street'
  AND "YEAR" = 2021
  AND "MONTH" = 7
  AND "DAY" = 28;

-- 11
SELECT
  people.name,
  atm_transactions.transaction_type
FROM
  "people"
  JOIN "bank_accounts" ON bank_accounts.person_id = people.id
  JOIN "atm_transactions" ON atm_transactions.account_number = bank_accounts.account_number
WHERE
  atm_transactions.year = '2021'
  AND atm_transactions.month = '7'
  AND atm_transactions.day = '28'
  AND atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw';

-- 12
SELECT
  *,
  people.name
FROM
  "atm_transactions"
  JOIN "bank_accounts" ON atm_transactions.account_number = bank_accounts.account_number
  JOIN "people" ON bank_accounts.person_id = people.id
WHERE
  "year" = '2021'
  AND "month" = '7'
  AND "day" = '28'
  AND "atm_location" = 'Leggett Street'
  AND "transaction_type" = 'withdraw';

-- 13
SELECT
  *
FROM
  "phone_calls"
WHERE
  "year" = '2021'
  AND "month" = '7'
  AND "day" = '28'
  AND "duration" < 60;

-- 14
SELECT
  "caller",
  "caller_name",
  "receiver",
  "receiver_name"
FROM
  "phone_calls"
WHERE
  "year" = '2021'
  AND "month" = '7'
  AND "day" = '28'
  AND "duration" < 60;

-- 15
SELECT
  "id",
  "hour",
  "minute",
  "origin_airport_id",
  "destination_airport_id"
FROM
  "flights"
WHERE
  "year" = '2021'
  AND "month" = '7'
  AND "day" = '29'
ORDER BY
  "hour" ASC
LIMIT
  1;

-- 16
SELECT
  flights.destination_airport_id,
  name,
  phone_number,
  license_plate
FROM
  people
  JOIN passengers ON people.passport_number = passengers.passport_number
  JOIN flights ON flights.id = passengers.flight_id
WHERE
  flights.id = 36
ORDER BY
  flights.hour ASC;

-- 17
SELECT
  people.name,
  phone_calls.caller,
  phone_calls.receiver,
  phone_calls.year,
  phone_calls.month,
  phone_calls.day,
  phone_calls.duration
FROM
  "phone_calls"
  JOIN "people" ON phone_calls.caller = people.phone_number
WHERE
  phone_calls.year = 2021
  AND phone_calls.month = 7
  AND phone_calls.day = 28
  AND phone_calls.duration < 60;

-- 18
SELECT
  *
FROM
  airports;

-- 19
SELECT
  "name"
FROM
  "people"
  JOIN "passengers" ON passengers.passport_number = people.passport_number
WHERE
  passengers.flight_id = (
    SELECT
      "id"
    FROM
      "flights"
    WHERE
      "YEAR" = '2021'
      AND "MONTH" = '7'
      AND "DAY" = '29'
      AND "origin_airport_id" = (
        SELECT
          "id"
        FROM
          "airports"
        WHERE
          "city" = 'Fiftyville'
      )
    ORDER BY
      "HOUR",
      "MINUTE"
    LIMIT
      1
  );

-- 20 new york
SELECT
  "city"
FROM
  "airports"
WHERE
  "id" = (
    SELECT
      "destination_airport_id"
    FROM
      "flights"
    WHERE
      "YEAR" = '2021'
      AND "MONTH" = '7'
      AND "DAY" = '29'
      AND "origin_airport_id" = (
        SELECT
          "id"
        FROM
          "airports"
        WHERE
          "city" = 'Fiftyville'
      )
    ORDER BY
      "HOUR",
      "MINUTE"
    LIMIT
      1
  );

-- 21
SELECT
  "name"
FROM
  "bakery_security_logs"
  JOIN "people" ON people.license_plate = bakery_security_logs.license_plate
  JOIN "bank_accounts" ON bank_accounts.person_id = people.id
  JOIN "atm_transactions" ON atm_transactions.account_number = bank_accounts.account_number
  JOIN "phone_calls" ON phone_calls.caller = people.phone_number
WHERE
  bakery_security_logs.year = 2021
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute BETWEEN 15 AND 25
  AND atm_transactions.year = 2021
  AND atm_transactions.month = 7
  AND atm_transactions.day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw'
  AND phone_calls.year = 2021
  AND phone_calls.month = 7
  AND phone_calls.day = 28
  AND phone_calls.duration < 60;

-- 22 Bruce
SELECT
  "name"
FROM
  "people"
  JOIN "passengers" ON people.passport_number = passengers.passport_number
WHERE
  passengers.flight_id = '36'
  AND people.name IN ('Bruce', 'Diana');

-- 23 Robin
SELECT
  p.name AS receiver
FROM
  "phone_calls"
  JOIN "people" ON people.phone_number = phone_calls.caller
  JOIN people p ON p.phone_number = phone_calls.receiver
WHERE
  people.name = 'Bruce'
  AND phone_calls.year = '2021'
  AND phone_calls.month = '7'
  AND phone_calls.day = '28'
  AND phone_calls.duration < '60';

-- 24
SELECT
  people.name,
  phone_calls.caller,
  phone_calls.receiver,
  phone_calls.year,
  phone_calls.month,
  phone_calls.day,
  phone_calls.duration,
  p.name AS receiver_name
FROM
  "phone_calls"
  JOIN people ON phone_calls.caller = people.phone_number
  JOIN people p ON phone_calls.receiver = p.phone_number
WHERE
  phone_calls.year = '2021'
  AND phone_calls.month = '7'
  AND phone_calls.day = '28'
  AND phone_calls.duration < '60'
  AND people.name = 'Bruce';