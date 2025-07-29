#include <string>
#include <iostream>
#include <iomanip>

#include "headers/flight.h"

using namespace std;

Flight::Flight() : flight_id(""), rows(0), columns(0), head(nullptr)
{
    seat_map.resize(rows, vector<Seat>(columns));
}

Flight::Flight(string flight_id, int rows, int columns) : flight_id(flight_id), rows(rows), columns(columns), head(nullptr)
{

    seat_map.resize(rows, vector<Seat>(columns));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; ++j)
        {
            seat_map[i][j] = Seat(i + (size_t)1, (char)('A' + (size_t)j));
        }
    }
}

Flight::~Flight()
{
    PassengerNode *curr = head;
    PassengerNode *next = nullptr;

    while (curr != nullptr)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }
}

Flight::Flight(const Flight &flight)
{
    flight_id = flight.flight_id;
    rows = flight.rows;
    columns = flight.columns;
    head = nullptr;
    seat_map = flight.seat_map;

    PassengerNode *curr = flight.head;

    while (curr != nullptr)
    {
        add_passenger(curr->passenger);
        curr = curr->next;
    }
}

Flight &Flight::operator=(const Flight &flight)
{
    if (this == &flight)
    {
        return *this;
    }

    flight_id = flight.flight_id;
    rows = flight.rows;
    columns = flight.columns;
    seat_map = flight.seat_map;

    PassengerNode *curr = head;
    PassengerNode *next = nullptr;

    while (curr != nullptr)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }

    head = nullptr;

    curr = flight.head;

    while (curr != nullptr)
    {
        add_passenger(curr->passenger);
        curr = curr->next;
    }

    return *this;
}

Passenger &Flight::getPassenger(int passenger_id)
{
    PassengerNode *curr = head;

    while (curr != nullptr)
    {
        if (curr->passenger.getPassengerID() == passenger_id)
        {
            return curr->passenger;
        }

        curr = curr->next;
    }

    cout << "Passenger not found" << endl;
    return curr->passenger;
}

Seat *Flight::getSeat(char col, int row)
{
    int col_index = (int)col - (int)'A';
    int row_index = row - 1;

    if (col_index < 0 || col_index >= columns || row_index < 0 || row_index >= rows)
    {
        cout << "Invalid seat" << endl;
        static Seat *dummy_seat = new Seat(-1, ' ');
        return dummy_seat;
    }

    return &seat_map[row_index][col_index];
}

int Flight::add_passenger(Passenger &passenger)
{
    PassengerNode *curr = head;
    PassengerNode *prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->passenger == passenger)
        {
            cout << "\nPassenger ID already exists\n" << endl;
            return 0;
        }

        prev = curr;
        curr = curr->next;
    }

    PassengerNode *new_node = new PassengerNode(passenger, nullptr);

    if (prev == nullptr)
    {
        head = new_node;
    }
    else
    {
        prev->next = new_node;
    }

    return 1;
}

void Flight::remove_passenger(Passenger &passenger)
{
    PassengerNode *curr = head;
    PassengerNode *prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->passenger == passenger)
        {
            if (prev == nullptr)
            {
                head = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            curr->passenger.getPassengerSeat()->setStatus(false);

            delete curr;
            break;
        }

        prev = curr;
        curr = curr->next;
    }
}

int Flight::count_passengers()
{
    int count = 0;
    PassengerNode *curr = head;

    while (curr != nullptr)
    {
        count++;
        curr = curr->next;
    }

    return count;
}

void Flight::showInfo(ostream &stream)
{
    PassengerNode *curr = head;

    stream << "Flight ID: " << flight_id << endl;
    stream << "Rows: " << rows << endl;
    stream << "Columns: " << columns << endl;

    stream << setw(20) << left << "First Name" << setw(20) << left << "Last Name" << setw(20) << left << "Phone Number" << setw(5) << left << "Row" << setw(5) << left << "Seat" << setw(10) << left << "ID" << endl;

    for (int i = 0; i < 80; ++i)
    {
        stream << "-";
    }
    stream << endl;

    while (curr != nullptr)
    {
        curr->passenger.showInfo(stream);
        for (int i = 0; i < 80; ++i)
        {
            stream << "-";
        }
        stream << endl;

        // cout << curr->passenger.getFirstName() << " " << curr->passenger.getLastName() << endl;
        curr = curr->next;
    }
    stream << endl;
}

void Flight::showFlightSeatMap()
{

    cout << "\tAircraft Seat Map\n";
    cout << "     ";

    for (int i = 0; i < columns; ++i)
    {
        cout << (char)('A' + i) << "   ";
    }

    cout << "\n   ";

    for (int k = 0; k < columns; ++k)
    {
        cout << "+---";
    }
    cout << "+\n";

    for (int i = 0; i < rows; ++i)
    {
        cout << setw(2) << i + 1 << " ";
        for (int j = 0; j < columns; ++j)
        {
            cout << "| " << (seat_map[i][j].getStatus() == false ? ' ' : 'X') << " ";
        }
        cout << "|\n   ";

        for (int k = 0; k < columns; ++k)
        {
            cout << "+---";
        }
        cout << "+\n";
    }
}

bool Flight::isSeatAvailable(char col, int row)
{
    int col_index = (int)col - (int)'A';
    int row_index = row - 1;

    if (col_index < 0 || col_index >= columns || row_index < 0 || row_index >= rows)
    {
        cout << "Invalid seat" << endl;
        return false;
    }

    return !seat_map[row_index][col_index].getStatus();
}