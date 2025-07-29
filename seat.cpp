
#include "headers/seat.h"
#include <iostream>

using namespace std;

Seat::Seat(int rowNum, char colLetter) : rowNumber(rowNum), columnLetter(colLetter), is_occupied(false) {}

Seat::Seat(const Seat &other)
{
    rowNumber = other.rowNumber;
    columnLetter = other.columnLetter;
    is_occupied = other.is_occupied;
}

void Seat::setStatus(bool stat)
{
    is_occupied = stat;
}

Seat &Seat::operator=(const Seat &other)
{
    if (this == &other)
    {
        return *this;
    }

    rowNumber = other.rowNumber;
    columnLetter = other.columnLetter;
    is_occupied = other.is_occupied;

    return *this;
}