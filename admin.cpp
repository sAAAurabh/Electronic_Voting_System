#include "admin.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "picosh.h"
#include <QDebug>


using namespace std;

// generates salt
string Admin::gen_salt()
{
    string chars = "abcdefghijklmnopqrstuvwxyz0123456789";
    string salt;

    for(int i = 0; i < 6; i++)
        salt += chars[rand() % chars.size()];

    return salt;
}


// hashes salt + password
string Admin::hash_pass(const string& pass, const string& salt)
{
    return picosha2::hash256_hex_string(salt + pass);
}


// finds voter
bool Admin::find_voter(const string& nid, Voter& v)
{
    ifstream fin(voter_file);
    string line;

    while(getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, v.nid, '|');
        getline(ss, v.first, '|');
        getline(ss, v.last, '|');
        getline(ss, v.salt, '|');
        getline(ss, v.hash, '|');

        string lock, attempts;
        getline(ss, lock, '|');
        getline(ss, attempts);

        v.is_locked = (lock == "1");
        v.attempts_left = stoi(attempts);

        if(v.nid == nid)
            return true;
    }

    return false;
}


//finds candidate
bool Admin::find_candidate(const string& nid, Candidate& c)
{
    ifstream fin(candidate_file);
    string line;

    while(getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, c.nid, '|');
        getline(ss, c.first, '|');
        getline(ss, c.last, '|');
        getline(ss, c.party, '|');
        getline(ss, c.salt, '|');
        getline(ss, c.hash, '|');

        string lock, attempts;
        getline(ss, lock, '|');
        getline(ss, attempts);

        c.is_locked = (lock == "1");
        c.attempts_left = stoi(attempts);

        if(c.nid == nid)
            return true;
    }

    return false;
}


// add voter
void Admin::add_voter(const Voter& v)
{
    ofstream fout(voter_file, ios::app);

    fout << v.nid << "|"
         << v.first << "|"
         << v.last << "|"
         << v.salt << "|"
         << v.hash << "|"
         << v.is_locked << "|"
         << v.attempts_left << "\n";
}


//add candidate
void Admin::add_candidate(const Candidate& c)
{
    ofstream fout(candidate_file, ios::app);

    fout << c.nid << "|"
         << c.first << "|"
         << c.last << "|"
         << c.party << "|"
         << c.salt << "|"
         << c.hash << "|"
         << c.is_locked << "|"
         << c.attempts_left << "\n";
}


// updates voter
void Admin::update_voter(const Voter& v)
{
    ifstream fin(voter_file);
    ofstream fout("Other files/temp.txt");

    string line;
    Voter temp;

    while(getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, temp.nid, '|');
        getline(ss, temp.first, '|');
        getline(ss, temp.last, '|');
        getline(ss, temp.salt, '|');
        getline(ss, temp.hash, '|');

        string lock, attempts;
        getline(ss, lock, '|');
        getline(ss, attempts);

        temp.is_locked = (lock == "1");
        temp.attempts_left = stoi(attempts);

        if(temp.nid == v.nid)
            temp = v;

        fout << temp.nid << "|"
             << temp.first << "|"
             << temp.last << "|"
             << temp.salt << "|"
             << temp.hash << "|"
             << temp.is_locked << "|"
             << temp.attempts_left << "\n";
    }

    fin.close();
    fout.close();

    remove(voter_file.c_str());
    rename("Other files/temp.txt", voter_file.c_str());
}


//updates candidate
void Admin::update_candidate(const Candidate& c)
{
    ifstream fin(candidate_file);
    ofstream fout("Other files/temp.txt");

    string line;
    Candidate temp;

    while(getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, temp.nid, '|');
        getline(ss, temp.first, '|');
        getline(ss, temp.last, '|');
        getline(ss, temp.party, '|');
        getline(ss, temp.salt, '|');
        getline(ss, temp.hash, '|');

        string lock, attempts;
        getline(ss, lock, '|');
        getline(ss, attempts);

        temp.is_locked = (lock == "1");
        temp.attempts_left = stoi(attempts);

        if(temp.nid == c.nid)
            temp = c;

        fout << temp.nid << "|"
             << temp.first << "|"
             << temp.last << "|"
             << temp.party << "|"
             << temp.salt << "|"
             << temp.hash << "|"
             << temp.is_locked << "|"
             << temp.attempts_left << "\n";
    }

    fin.close();
    fout.close();

    remove(candidate_file.c_str());
    rename("Other files/temp.txt", candidate_file.c_str());

}


// login voter
login_result Admin::login_voter(const std::string& nid, const std::string& pass)
{
    Voter v;

    if (!find_voter(nid, v))
        return not_found;

    if (v.is_locked)
        return acc_locked;

    if (hash_pass(pass, v.salt) == v.hash)
    {
        v.attempts_left = 5;   // reset on success
        update_voter(v);
        return login_success;
    }

    v.attempts_left--;

    if (v.attempts_left <= 0)
    {
        v.is_locked = true;
        update_voter(v);
        return acc_locked;
    }

    update_voter(v);
    return wrong_pass;
}


//login candidate
login_result Admin::login_candidate(const std::string& nid, const std::string& pass)
{
    Candidate c;

    if (!find_candidate(nid, c))
        return not_found;

    if (c.is_locked)
        return acc_locked;

    if (hash_pass(pass, c.salt) == c.hash)
    {
        c.attempts_left = 5;   // reset on success
        update_candidate(c);
        return login_success;
    }

    c.attempts_left--;

    if (c.attempts_left <= 0)
    {
        c.is_locked = true;
        update_candidate(c);
        return acc_locked;
    }

    update_candidate(c);
    return wrong_pass;
}


//validates password
pass_val Admin::is_valid_pass(const string pass, string nm){
    {
        if (pass.length() < 7)
            return letter;

        int digits = 0;
        bool has_special = false;
        bool has_capital = false;

        for (unsigned char c : pass)
        {
            if (isdigit(c))
                digits++;
            else if (isupper(c))
                has_capital = true;
            else if (!isalnum(c))
                has_special = true;
        }

        if (pass == nm)
            return name;

        if (digits < 3)
            return number;

        if (!has_special)
            return special;

        if (!has_capital)
            return capital;

        return is_valid;
    }
}


// read the manifesto
std::string Admin::get_manifesto(const std::string &nid)
{
    std::ifstream file("Other files/manifesto.txt");

    if (!file.is_open())
        return "";

    std::string line;

    while (std::getline(file, line))
    {
        if (line.find(nid + "|") == 0)
        {
            return line.substr(nid.size() + 1);
        }
    }

    return "";
}

