#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

#include "headers/passenger.h"

using namespace std;

Passenger::Passenger(int id, string fName, string lName, string phone, Seat *seat)
{

    passengerID = id;
    firstName = fName;
    lastName = lName;
    phoneNumber = phone;
    passengerSeat = seat;
    passengerSeat->setStatus(true);
}

Passenger::Passenger()
{

    passengerID = 0;
    firstName = "";
    lastName = "";
    phoneNumber = "";
    passengerSeat = nullptr;
}

Passenger::Passenger(const Passenger &other)
{

    passengerID = other.passengerID;
    firstName = other.firstName;
    lastName = other.lastName;
    phoneNumber = other.phoneNumber;
    passengerSeat = other.passengerSeat;
}

Passenger::~Passenger()
{
    passengerID = 0;
    firstName = "";
    lastName = "";
    phoneNumber = "";
    passengerSeat = nullptr;
}

void Passenger::setPassengerSeat(Seat *seat)
{
    passengerSeat = seat;
    passengerSeat->setStatus(true);
}

void Passenger::showInfo(ostream &stream)
{
    stream << setw(20) << left << firstName << setw(20) << left << lastName << setw(20) << left << phoneNumber << setw(5) << left << passengerSeat->getRowNumber() << setw(5) << left << passengerSeat->getColumnLetter() << setw(10) << left << passengerID << endl;
}