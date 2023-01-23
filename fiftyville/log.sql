-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Verifiy content of crime scnee reports to find the crime we are interested in:
SELECT * FROM crime_scene_reports;


-- Verify the interviews on that day
SELECT * FROM interviews WHERE (year = 2021 AND month = 7 AND day = 28);



-- Crosscheck the information gathered during the interview FROM the thief withdrawal + the bakery parking lot + the call duration + correlation of time and date.
SELECT name, phone_number, passport_number, license_plate
  FROM atm_transactions
  JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
  JOIN people ON bank_accounts.person_id = people.id
 WHERE (atm_location = "Leggett Street"
   AND transaction_type = "withdraw" AND atm_transactions.day = 28
   AND phone_number IN (SELECT caller FROM phone_calls WHERE (duration < 60))
   AND license_plate
    IN (SELECT license_plate FROM bakery_security_logs WHERE (month = 7 AND day = 28 AND hour = 10 AND minute > 14 AND minute < 26 AND activity = "exit")));


-- Below list of onsite suspects.
+-------+----------------+-----------------+---------------+
| name  |  phone_number  | passport_number | license_plate |
+-------+----------------+-----------------+---------------+
| Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
| Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
+-------+----------------+-----------------+---------------+


-- Get global picture of airports ID


SELECT * FROM airports ;
+----+--------------+-----------------------------------------+---------------+
| id | abbreviation |                full_name                |     city      |
+----+--------------+-----------------------------------------+---------------+
| 1  | ORD          | OHare International Airport            | Chicago       |
| 2  | PEK          | Beijing Capital International Airport   | Beijing       |
| 3  | LAX          | Los Angeles International Airport       | Los Angeles   |
| 4  | LGA          | LaGuardia Airport                       | New York City |
| 5  | DFS          | Dallas/Fort Worth International Airport | Dallas        |
| 6  | BOS          | Logan International Airport             | Boston        |
| 7  | DXB          | Dubai International Airport             | Dubai         |
| 8  | CSF          | Fiftyville Regional Airport             | Fiftyville    |
| 9  | HND          | Tokyo International Airport             | Tokyo         |
| 10 | CDG          | Charles de Gaulle Airport               | Paris         |
| 11 | SFO          | San Francisco International Airport     | San Francisco |
| 12 | DEL          | Indira Gandhi International Airport     | Delhi         |
+----+--------------+-----------------------------------------+---------------+


--Get the earliest flight the say after FROM Fiftyville. Fligh ID 36 toward New York City.
SELECT * FROM flights WHERE(origin_airport_id=8 AND day = 29) ORDER BY hour;
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | mINute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
| 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
| 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
| 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
+----+-------------------+------------------------+------+-------+-----+------+--------+


-- Bruce is a passenger for flight 36, his passport number matches. He has to be the suspect.
SELECT * FROM passengers WHERE passport_number IN (SELECT passport_number FROM atm_transactions
  JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
  JOIN people ON bank_accounts.person_id = people.id
 WHERE (atm_location = "Leggett Street"
   AND transaction_type = "withdraw" AND atm_transactions.day = 28
   AND phone_number IN (SELECT caller FROM phone_calls WHERE (duration < 60))
   AND license_plate
    IN (SELECT license_plate FROM bakery_security_logs
 WHERE (month = 7 AND day = 28 AND hour = 10 AND minute > 14 AND minute < 26 AND activity = "exit"))));
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 18        | 3592750733      | 4C   |
| 24        | 3592750733      | 2C   |
| 36        | 5773159633      | 4A   |
| 54        | 3592750733      | 6C   |
+-----------+-----------------+------+


-- To find the accomplice, we need to see who Bruce called after the theft by filering the call records FROM his number and identying the receiver.
SELECT * FROM phone_calls WHERE(caller =  "(367) 555-5533" AND day = 28 AND duration < 60);
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
+-----+----------------+----------------+------+-------+-----+----------+
SELECT name, phone_number FROM people WHERE(phone_number="(375) 555-8161");
+-------+----------------+
| name  |  phone_number  |
+-------+----------------+
| Robin | (375) 555-8161 |
+-------+----------------+

-- Robin is the accomplice.