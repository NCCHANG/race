#include <iostream>
#include <vector>
#include <iomanip>
#include <string> // Include this for string and getline

using namespace std;

extern const int widthhh;

class RLayout {
public:

    void HorizontalEqual() {
        cout << setw(widthhh) << setfill('=') << "=" << endl;
    }

    void WelcomeMessage() {
        cout << setw(widthhh) << setfill(' ') << " Welcome To Player Registration!  " << endl;
    }

    void RegistrationLayout() {
        HorizontalEqual();
        WelcomeMessage();
        HorizontalEqual();
    }
}; 

class QLayout {
public:
    void HorizontalEqual() {
        cout << setw(widthhh) << setfill('=') << "=" << endl;
    }

    void WelcomeMessage() {
        cout << setw(widthhh) << setfill(' ') << " Game Start!            " << endl;
    }

    void StartLayout() {
        HorizontalEqual();
        WelcomeMessage();
        HorizontalEqual();
    }
};

class Player {
public:
    string name;
    string email;
    string racer;

public:
    static std::vector<Player> userslist; // allows all instances of 'Player' to share the same userslist.
    
    // Constructor
    Player(const string& name="", const string& email="", const string& racer="")
        : name(name), email(email), racer(racer) {}

    // Function to register users
    static void registerUsers() {
        string batman = "batman";
        string flash = "flash";
        string superman = "superman";

        for (int i = 0; i < 3; i++) {
            string name, email, racer;

            cout << "\n";
            cout << "User " << i + 1 << "\n";

            cout << "Enter Name: ";
            getline(cin, name);

            cout << "Enter Email: ";
            getline(cin, email);

            do {
                cout << "Select your racer (batman, flash, superman): ";
                getline(cin, racer);

                if (racer != batman && racer != flash && racer != superman) {
                    cout << "The racer you have chosen is not available. Please choose your racer again!" << "\n";
                }
            } while (racer != batman && racer != flash && racer != superman);

            userslist.push_back(Player(name, email, racer));
        }
    }
    
    string getName() const {
        return name;
    }
    
    string getEmail() const {
        return email;
    }

    string getRacer() const {
        return racer;
    }

    static void printRegisteredUsers() {
        for (const Player& user : userslist) {
            cout << "\n" << "Great! User " << user.name << ", you have chosen " << user.racer << " as your racer!";
        }
    }
};

std::vector<Player> Player::userslist;

