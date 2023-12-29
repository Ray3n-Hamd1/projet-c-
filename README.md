# Car Rental Agency

This is a C program for a car rental agency. It allows users to rent cars, view car details, update car states and details, view rental history, cancel rentals, and add new cars.

## Table of Contents

- Features
- How it Works
- Running the Program

## Features

- **Rent a Car**: Users can rent a car by providing their ID, the car's plate number, and the rental start and end dates.
- **View Car Details**: Users can view the details of a car by providing the car's plate number.
- **Update Car State or Details**: Users can update the state or details of a car by providing the car's plate number.
- **View Rental History**: Users can view the rental history of all cars.
- **Cancel Rental**: Users can cancel a rental by providing the car's plate number and the reason for cancellation.
- **Add New Car**: Users can add a new car by providing the car's plate number and details.

## How it Works

The program stores car data in a linked list of `CarNode` structures. Each `CarNode` contains a `Car` structure, which contains the car's plate number, state, loan status, and a linked list of `LocationNode` structures representing the car's rental history.

The program presents the user with a menu of options to interact with the car data. The options include renting a car, viewing car details, updating car state or details, viewing rental history, cancelling a rental, and adding a new car.

The program reads and writes car data from and to a file named "carlocation.txt". It uses the `loadcars` function to load car data from the file into the linked list at the start of the program, and the `savecars` function to save the car data from the linked list back to the file at the end of the program.

## Running the Program

To run the program, compile the C code with a C compiler, then run the resulting executable. The program will present you with a menu of options. Enter the number of the option you want to choose, then follow the prompts.
