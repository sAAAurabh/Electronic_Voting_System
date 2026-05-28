#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include "picosha2.h"
#include <conio.h>
#include "Voter.h" 
#include "Admin.h"
using namespace std;



string Admin::genSalt() // generates a random string to add do the password before hashing it
{
    int salt_size = 6;
    string chars = "abcdefghijklmnopqrstuvwxyz0123456789"; // total 36 characters
    string salt = "";

    for (int i = 0; i < salt_size; i++)
        salt += chars[rand() % chars.size()]; // rand()% chars.size() insures that the index is less than 36

    return salt;
}


string Admin::hashPass(string pass, string salt) // returns a hash for the (password + salt)
{
    return picosha2::hash256_hex_string(salt + pass); 
}


string Admin::getPassword() // reads the password from the user in *** format
{
    string pass = "";
    char ch;

    cout << "Password: ";

    while (true)
    {
        ch = getch(); // getch doesnt echo(show on terminal) the entered character

        if (ch == 13) // Ascii value of enter is 13 so if use presses 13(enter) the loop breaks out
            break;
        else if (ch == 8) // Ascii vaue of backspace is 8 so if user enter backspace it pops the character
        {
            if (!pass.empty())
            {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            pass += ch;
            cout << "*";
        }
    }

    cout << endl;
    return pass;
}


bool Admin::validPassword(string username, string password) //checks whether the password is acceptable or not
{
    if (password.length() < 7)
    {
        cout << "\nPassword must be at least 7 characters.\n";
        return false;
    }

    int digits = 0;
    bool special = false;
    bool capital = false;

    for (char c : password)
    {
        if (isdigit(c))
            digits++;
        else if (isupper(c))
            capital = true;
        else if (!isalnum(c))
            special = true;
    }

    if (digits < 3)
    {
        cout << "\nAt least 3 digits required.\n";
        return false;
    }

    if (!special)
    {
        cout << "\nAt least 1 special character required.\n";
        return false;
    }

    if (!capital)
    {
        cout << "\nAt least 1 capital letter required.\n";
        return false;
    }

    if (password == username)
    {
        cout << "\nPassword cannot match username.\n";
        return false;
    }

    return true;
}


int Admin::passwordStrength(string password) //returns a integer that represents the strength of the password
{
    int len_score = 0;
    int digit_score = 0;
    int special_score = 0;

    int digit_cnt=0;
    int special_cnt=0;

    if (password.length() >= 14) len_score = 3;         //counts the number of characters
    else if (password.length() >= 11) len_score = 2;
    else if (password.length() >= 7) len_score = 1;

    for(int i = 0; i < password.length(); i++){        //counts the number of digits
        if (isdigit(password[i])) digit_cnt ++;
    }

    for(int i = 0; i < password.length(); i++){     //counts the number of speical characters
        if (!isalnum(password[i])) special_cnt ++;
    }

    if(digit_cnt==3 || digit_cnt==4) digit_score = 1;
    else if(digit_cnt==5 || digit_cnt==6) digit_score = 2;
    else digit_score = 3;

    if(special_cnt==1) special_score = 1;
    else if(special_cnt == 2) special_score = 2;
    else special_score = 3;

    return len_score + digit_score + special_score;    



}


bool Admin::findVoter(string nid, Voter &v) //checks if the voter is registered or not
{
    ifstream fin(file);
    string line;

    while (getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, v.nid, '|');
        getline(ss, v.firstName, '|');
        getline(ss, v.lastName, '|');
        getline(ss, v.salt, '|');
        getline(ss, v.hash, '|');
        string temp;
        getline(ss, temp, '|');
        v.is_locked = (temp == "1");

        if (v.nid == nid)
            return true;
    }

    return false;
}


void Admin::registerVoter()
{
    Voter v;
    string password;
    int pass_strength;

    cout << "\nNID: ";
    cin >> v.nid;

    cout << "First Name: ";
    cin >> v.firstName;

    cout << "Last Name: ";
    cin >> v.lastName;

    while (true)  //ensures the voter registers with a valid password and warns them with the strength of their password
    {
        password = getPassword();
        if (validPassword(v.firstName, password)){
            pass_strength = passwordStrength(password);
            if (pass_strength <= 4)
            {
                cout << "\nPassword Strength : Weak \n";
                cout << "Continue[1] or Set another stronger password[2]\n";
                int choice;
                cin >> choice;
                if (choice == 1)
                    break;
            }
            else if (pass_strength >= 5 && pass_strength <=7)
            {
                cout << "\nPassword Strength : Medium \n";
                cout << "Continue[1] or Set another stronger password[2]\n";
                int choice;
                cin >> choice;
                if (choice == 1)
                    break;
            }
            else
            {
                cout << "\nPassword Strength : Strong \n";
                cout << "Continue[1] or Set a different password[2]\n";
                int choice;
                cin >> choice;
                if (choice == 1)
                    break;
            }

        }else continue;

    }

    v.salt = genSalt();
    v.hash = hashPass(password, v.salt);    //generates a hash for the password to store in the data file
    v.is_locked = false;                    // sets the new voters account as not_locked

    ofstream fout(file, ios::app);
    fout << v.nid << "|"             // writes the users information to the data file
         << v.firstName << "|"
         << v.lastName << "|"
         << v.salt << "|"
         << v.hash << "|"
         << v.is_locked << "\n";

    cout << "Registered successfully\n";
}


void Admin::loginVoter()
{
    int pass_attempts = 5;
    int nid_attempts = 7;
    string nid;
    Voter v;

    while (nid_attempts > 0)    //searches for the voter account in data file and echoes "Register" if account not found
    {
        cout << "\nNID: ";
        cin >> nid;

        if (!findVoter(nid, v))
        {
            cout << "\nVoter Not Found\n";
            nid_attempts--;
            if (nid_attempts == 0)
            {
                cout << "\nVoter Not found. Register first.\n";
                return;
            }
            continue;
        }

        if (v.is_locked)
        {
            cout << "Account is locked. Contact Admin.\n";
            return;
        }
        else
        {
            while (pass_attempts > 0)     //if password fails to match a certain number of times, the account gets locked
            {
                string password = getPassword();

                if (hashPass(password, v.salt) == v.hash)
                {
                    cout << "\nLogin successful\n";
                    v.display();
                    return;
                }
                else
                {
                    cout << "\nWrong Password\n";
                    if (pass_attempts!=0) cout << pass_attempts - 1 << " attempts left\n\n";
                    pass_attempts--;

                    if (pass_attempts == 0)
                    {
                        cout << "\nToo many attempts. Your ID has been locked. Please Contact Your Nearest Election Commission\n";
                        updateVoter(nid, true);   //sets the is_locked value in voter data to true(i.e 1)
                        return;
                    }
                }
            }
        }
    }
}


void Admin::updateVoter(string targetNID, bool lockStatus)   //updates the lockedStatus of voter account
{
    ifstream fin(file);
    ofstream fout("temp.txt");

    string line;

    while (getline(fin, line))
    {
        stringstream ss(line);

        string nid, first, last, salt, hash, lock;

        getline(ss, nid, '|');
        getline(ss, first, '|');
        getline(ss, last, '|');
        getline(ss, salt, '|');
        getline(ss, hash, '|');
        getline(ss, lock, '|');

        if (nid == targetNID)
            lock = lockStatus ? "1" : "0";

        fout << nid << "|"
             << first << "|"
             << last << "|"
             << salt << "|"
             << hash << "|"
             << lock << "\n";
    }

    fin.close();
    fout.close();

    remove(file.c_str());
    rename("temp.txt", file.c_str());
}
