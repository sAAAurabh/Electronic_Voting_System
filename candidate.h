#pragma once
#include <string>

struct Candidate
{
    std::string nid;
    std::string first;
    std::string last;
    std::string party;
    std::string salt;
    std::string hash;
    std::string votes;

    bool is_locked = false;
    int attempts_left = 5;

    // NID | firstname | lastname | party | salt | hash | lockstatus | attempsts_left | votes

};