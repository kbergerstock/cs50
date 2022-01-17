-- Keep a log of any SQL queries you execute as you solve the mystery.

-- get the  initial crime scene reoirt
select description  from crime_scene_reports where year = 2020 and month = 7 and day = 28 and street like 'Chamb%';

-- read the interviews
select name, transcript from interviews where year = 2020 and month = 7 and day = 28;-- read

-- read the courthouse security logs
select activity, license_plate, minute from courthouse_security_logs where year = 2020 and month = 7 and day = 28 and hour = 10;


