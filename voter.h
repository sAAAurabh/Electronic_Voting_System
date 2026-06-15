#pragma once
#include <string>

struct Voter
{
    std::string nid;
    std::string first;
    std::string last;
    std::string dob;
    std::string gender;
    std::string salt;
    std::string hash;
    std::string photo_path;

    bool is_locked = false;
    int attempts_left = 5;

    //NID | firstname | lastname | salt | hash | lockstatus | attempts left
};