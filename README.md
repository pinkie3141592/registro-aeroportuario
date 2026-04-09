# Airline Management System

## Description

This program is a simple airport management system developed in C/C++. It allows users to register destinations, purchase flights, and consult stored travel information through a menu-driven interface.

## Features

* Register new destinations with price information
* Purchase flights (one-way or round-trip)
* View all available destinations
* View all registered flights or filter by date
* Input validation for dates, prices, and formats

## How to Use

When the program runs, a menu will appear with the following options:

a. Register destinations
Add new destinations including a unique code, name, and price.

b. Register flights
Select a destination and book a flight. You can choose between one-way or round-trip travel, including departure and return dates.

c. List destinations
Displays all registered destinations and their prices.

d. List flights
Allows you to view all flights or search for flights by a specific date.

e. Exit
Closes the program.

## Data Storage

The program stores information in two files:

destinos.txt: stores destination data
viajes.txt: stores flight records

In the auxiliares directory these files already exist with few entries to make a trial quicker.

## How to Compile and Run

```bash
g++ registro_aeroportuario.cpp -o program
./program
```


## Notes

You must register at least one destination before purchasing flights. The program validates inputs such as destination format, prices, and dates to prevent errors.

## Technologies Used

C / C++
File handling with text files
Input validation using regular expressions

