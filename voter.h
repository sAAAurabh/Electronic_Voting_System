#pragma once
#include <string>

struct Voter
{
    std::string nid;
    std::string first;
    std::string last;
    std::string salt;
    std::string hash;

    bool is_locked = false;
    int attempts_left = 5;

    //NID | firstname | lastname | salt | hash | lockstatus | attempts left
};