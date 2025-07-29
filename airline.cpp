#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "headers/airline.h"

using namespace std;

Airline::~Airline()
{
    FlightNode *curr = head;
    FlightNode *next = nullptr;

    while (curr != nullptr)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }
}

Airline::Airline(const Airline &airline)
{
    cout << "Copy constructor called" << endl;
    airline_name = airline.airline_name;
    num_flights = airline.num_flights;

    FlightNode *curr = airline.head;

    while (curr != nullptr)
    {
        addFlight(curr->flight);
        curr = curr->next;
    }
}

Airline &Airline::operator=(const Airline &airline)
{
    if (this == &airline)
    {
        return *this;
    }

    airline_name = airline.airline_name;
    num_flights = airline.num_flights;

    FlightNode *curr = head;
    FlightNode *next = nullptr;

    while (curr != nullptr)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }

    head = nullptr;

    curr = airline.head;

    while (curr != nullptr)
    {
        addFlight(curr->flight);
        curr = curr->next;
    }

    return *this;
}

void Airline::addFlight(Flight &flight)
{
    FlightNode *newNode = new FlightNode(flight);
    newNode->next = head;
    head = newNode;
    num_flights++;
}

void Airline::removeFlight(Flight &flight)
{
    FlightNode *curr = head;
    FlightNode *prev = nullptr;

    while (curr != nullptr && curr->flight != flight)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr)
    {
        return;
    }

    if (prev == nullptr)
    {
        head = head->next;
    }
    else
    {
        prev->next = curr->next;
    }

    delete curr;
    num_flights--;
}

vector<string> Airline::showAirlineFlightList()
{
    vector<string> flight_list;

    FlightNode *curr = head;
    cout << "--------" << endl;
    while (curr != nullptr)
    {
        string flight_id = curr->flight.get_flight_id();
        flight_list.push_back(flight_id);
        cout << flight_id << endl;
        cout << "--------" << endl;
        curr = curr->next;
    }

    return flight_list;
}

Flight &Airline::getFlight(string flight_id)
{
    FlightNode *curr = head;

    while (curr != nullptr && curr->flight.get_flight_id() != flight_id)
    {
        curr = curr->next;
    }

    if (curr == nullptr)
    {
        cout << "Flight not found" << endl;
        static Flight dummy_flight("", 0, 0);
        return dummy_flight;
    }

    return curr->flight;
}

void Airline::showInfo(ostream &stream)
{
    stream << airline_name << endl;
    stream << "Number of flights: " << num_flights << endl;
    stream << endl;

    FlightNode *curr = head;

    while (curr != nullptr)
    {
        curr->flight.showInfo(stream);
        curr = curr->next;
    }
    stream << endl;
}

int Airline::addFlightFromFile(string file_name)
{
    ifstream flight_file(file_name);

    // Check if file opened successfully
    if (flight_file.fail())
    {
        cout << "File failed to open" << endl;
        return 0;
    }

    string airline_info;
    string passenger_info;

    string flight_id, first_name, last_name, phone_number, seat;
    int rows, columns;
    int seatrow;
    char seatcol;
    int passenger_id;

    // Get the first line of the file (flight info)
    getline(flight_file, airline_info);
    istringstream iss(airline_info);

    iss >> flight_id >> rows >> columns;

    // Add flight to airline
    Flight flight(flight_id, rows, columns);
    addFlight(flight);

    // Get the passenger info
    while (getline(flight_file, passenger_info))
    {
        // Extract passenger information
        istringstream iss(passenger_info);
        string field;

        iss >> first_name;
        iss.seekg(1, ios::cur); // Skip space

        if (iss.peek() != ' ')
        {
            string temp;
            iss >> temp;
            first_name += " " + temp;
        }

        iss >> last_name;
        iss.seekg(1, ios::cur); // Skip space

        if (iss.peek() != ' ')
        {
            string temp;
            iss >> temp;
            last_name += " " + temp;
        }

        iss >> phone_number >> seat >> passenger_id;

        // Split seat into row and column
        istringstream seat_stream(seat);
        seat_stream >> seatrow >> seatcol;
        Seat *flight_seat = getFlight(flight_id).getSeat(seatcol, seatrow);

        // Create a passenger object
        Passenger passenger(passenger_id, first_name, last_name, phone_number, flight_seat);

        // Add passenger to flight
        getFlight(flight_id).add_passenger(passenger);
    }

    flight_file.close();
    return 1;
}
