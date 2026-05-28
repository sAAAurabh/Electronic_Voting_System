#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Voter.h"
#include "Admin.h"
using namespace std;

int main()
{
    srand(time(0));

    Admin admin;
    int choice;

    cout << "\n1. Register\n2. Login\n3. Exit\nChoice: ";
    cin >> choice;

    if (choice == 1)
        admin.registerVoter();
    else if (choice == 2)
        admin.loginVoter();

    return 0;
}