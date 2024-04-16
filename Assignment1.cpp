#include <iostream>
using namespace std;

void horizontal() {
    int i = 0;
    char addSign = '+';
    char minusSign = '-';
    string space = "   ";

    while (i <= 16){
        if (i==8) {
        cout << addSign;
        cout << space;
        }else {
            cout << addSign << minusSign << minusSign << minusSign;
        }
        i = i + 1;
    }
    cout << addSign << '\n';
}

void vertical() {
    char straightLine = '|';
    string space = "   ";
    int j = 0;

    while (j <= 17){
        cout << straightLine << space;    
        j = j + 1;
    }
    cout << '\n';
}

void middleVertical() {
    char straightLine = '|';
    char space = ' ';
    int j = 0;

    while (j < 18){
        if (j < 2 || (7<=j && j<=10) || j > 15){
            cout << straightLine << space << space << space;
            j = j + 1;
        }
        else {
            cout << space << space << space << space;
            j = j + 1;
        }
    }
    cout << '\n';
}

void middleHorizontal() {
    int i = 0;
    string sign = "+---";
    string addSign = "+";
    string space = "  ";

    while (i < 29){
        if (i < 1 || i == 13 || i == 15 || i > 27) {
            cout << '\b' << sign << addSign;
            i = i + 1;
        }
        else if (i==14) {
            cout << space << space;
            i = i + 1;
        }
        else {
            cout << space;
            i = i + 1;
        }
    }
    cout << '\n';
}

int main()
{
    int i = 0;

    horizontal();
    vertical();
    horizontal();
    while (i < 6){
        if (i < 5){
            middleVertical();
            middleHorizontal();
            i = i + 1;
        }
        else {
            middleVertical();
            i = i + 1;
        }
    }
    horizontal();
    vertical();
    horizontal();

    return 0;
}