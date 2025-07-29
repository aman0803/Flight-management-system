#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

#include "headers/airline.h"
#include "headers/flight.h"
#include "headers/passenger.h"
#include "headers/seat.h"

using namespace std;

void display_header()
{
    cout << "============================" << endl;
    cout << "Flight Management Program   " << endl;
    cout << "============================" << endl;
    cout << "Version: 1.0                " << endl;
    cout << "============================" << endl;
    cout << "Produced by: Olamikun Aluko " << endl;
    cout << "             Ron Ivan Ibe   " << endl;
    cout << "Year: 2023                  " << endl;
    cout << "============================" << endl;
    cout << "\n<<Press Enter to continue>> ";

    cin.get();
}

void populateFlightFromFile(Airline &airline)
{
    while (true)
    {
        string file_name;
        cout << "Enter the file name (with .txt): ";
        cin >> file_name;

        if (airline.addFlightFromFile(file_name))
        {
            cout << "Flight added successfully" << endl;
            break;
        }

        else
            break;
    }

    cout << "\n<<Press any key to continue>> ";
    cin.ignore();
    cin.get();
}

void changeFlight(string &flight_id, Airline &airline)
{
    while (true)
    {
        cout << "Which flight would you like to manage?" << endl;
        vector<string> flight_list = airline.showAirlineFlightList();
        bool flight_found = false;
        cout << "Enter flight ID: ";
        cin >> flight_id;

        for (const string &saved_id : flight_list)
        {
            if (flight_id == saved_id)
            {
                flight_found = true;
                break;
            }
        }

        if (flight_found)
        {
            cout << "\nFlight changed successfully\n"
                 << endl;
            break;
        }

        else
        {
            cout << "\nFlight not found!\n"
                 << endl;
            continue;
        }
    }

    cout << "\n<<Press any key to continue>> ";

    cin.ignore();
    cin.get();
}

void displayFlightSeatMap(string &flight_id, Airline &airline)
{
    airline.getFlight(flight_id).showFlightSeatMap();
    cout << "\n<<Press any key to continue>> ";
    cin.ignore();
    cin.get();
}

void displayPassengerInfo(string &flight_id, Airline &airline)
{
    airline.getFlight(flight_id).showInfo();
    cout << "\n<<Press any key to continue>> ";

    cin.ignore();
    cin.get();
}

void addNewPassenger(string &flight_id, Airline &airline)
{
    Flight &flight = airline.getFlight(flight_id);
    int id, row;
    string firstName, lastName, phoneNumber;
    char seat;

    cout << "Please enter the passenger ID: ";
    cin >> id;

    if (cin.fail())
    {
        cout << "\nError! Invalid ID" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Please enter the passenger first name: ";
    getline(cin >> ws, firstName);

    cout << "Please enter the passenger last name: ";
    getline(cin >> ws, lastName);

    cout << "Please enter the passenger phone number: ";
    cin >> phoneNumber;

    while (true)
    {

        cout << "Enter the passenger's desired row.\n(Please enter a number between 1 and " << flight.get_rows() << "): ";
        cin >> row;

        if (cin.fail())
        {
            cout << "\nError! Invalid row number" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Enter the passenger's desired seat.\n(Please enter a letter between A and " << (char)((int)'A' + flight.get_columns() - 1) << "): ";
        cin >> seat;

        if (cin.fail())
        {
            cout << "\nError! Invalid seat letter" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (flight.isSeatAvailable(seat, row))
        {
            break;
        }

        else
        {
            cout << "\nSeat is not available\n"
                 << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }

    Passenger passenger(id, firstName, lastName, phoneNumber, flight.getSeat(seat, row));
    while (true)
    {

        if (airline.getFlight(flight_id).add_passenger(passenger))
        {
            cout << "Here is the passenger's information:\n"
                 << endl;
            airline.getFlight(flight_id).getPassenger(id).showInfo();
            break;
        }
        else
        {
            cout << "Error adding passenger\n"
                 << endl;
            break;
        }
    }

    cout << "\n<<Press any key to continue>> ";
    cin.clear();
    cin.ignore();
    cin.get();
}

void removePassenger(string &flight_id, Airline &airline)
{
    int passengerID;
    cout << "\nEnter the id of the passenger that needs to be removed: ";
    cin >> passengerID;

    if (airline.getFlight(flight_id).getPassenger(passengerID).getPassengerID() == -1)
    {
        cout << "Passenger not found" << endl;
        return;
    }

    airline.getFlight(flight_id).remove_passenger(airline.getFlight(flight_id).getPassenger(passengerID));

    cout << "Passenger removed successfully" << endl;
    cout << "\n<<Press any key to continue>> ";
    cin.clear();
    cin.ignore();
    cin.get();
}

void saveData(string &flight_id, Airline &airline)
{
    string file_name;
    cout << "Where would you like to save the data? (Enter the file name):";
    cin >> file_name;

    ofstream flight_file(file_name);

    if (flight_file.fail())
    {
        cout << "File failed to open" << endl;
        exit(1);
    }

    airline.showInfo(flight_file);

    flight_file.close();
    cout << "Data saved successfully" << endl;
    cout << "\n<<Press any key to continue>> ";
    cin.clear();
    cin.ignore();
    cin.get();
}

void menu(Airline &airline)
{
    int input;
    string flight_id;
    cout << "\n\nWelcome to the Flight Management Program!" << endl;

    changeFlight(flight_id, airline);

    while (true)
    {
        cout << "\nPlease select one of the following options:" << endl;
        cout << "\n1. Change Flight." << endl;
        cout << "\n2. Display Flight Seat Map." << endl;
        cout << "\n3. Display Passengers Information." << endl;
        cout << "\n4. Add a new Passenger." << endl;
        cout << "\n5. Remove an Existing Passenger." << endl;
        cout << "\n6. Save data to file" << endl;
        cout << "\n7. Add a new Flight from file." << endl;
        cout << "\n8. Quit." << endl;
        cout << "\nEnter your choice: (1, 2, 3, 4, 5, 6, 7, or 8) ";
        cin >> input;

        if (cin.fail() || input < 1 || input > 8)
        {
            cin.clear();

            while (cin.get() != '\n')
            {
                continue;
            }

            cout << "Invalid Input\n"
                 << endl;
        }

        else if (input >= 1 && input <= 7)
        {
            switch (input)
            {
            case 1:
                changeFlight(flight_id, airline);
                break;
            case 2:
                displayFlightSeatMap(flight_id, airline);
                break;
            case 3:
                displayPassengerInfo(flight_id, airline);
                break;
            case 4:
                addNewPassenger(flight_id, airline);
                break;
            case 5:
                removePassenger(flight_id, airline);
                break;
            case 6:
                saveData(flight_id, airline);
                break;

            case 7:
                populateFlightFromFile(airline);
                break;
            }
        }

        else
        {
            break;
        }
    }

    return;
}

int main(void)
{

    display_header();

    Airline airline("WesJet");
    airline.addFlightFromFile();

    // Display menu for WesJet
    menu(airline);

    return 0;
}