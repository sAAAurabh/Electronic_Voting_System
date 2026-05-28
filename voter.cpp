#include <iostream>
#include "Voter.h"
using namespace std;



void Voter::display()
{
    cout << "\n--- VOTER INFO ---\n";
    cout << "NID: " << Voter::nid << "\n";
    cout << "Name: " << Voter::firstName << " " << Voter::lastName << "\n";
}
