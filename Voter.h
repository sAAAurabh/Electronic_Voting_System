#pragma once

#include <string>


class Voter {

    public:
        std::string nid;
        std::string firstName;
        std::string lastName;
        std::string salt;
        std::string hash;
        bool is_locked ;

        void display();

};
