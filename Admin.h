#pragma once

#include <string>
#include "Voter.h"


class Admin {
    private:

        std::string file = "voter.txt";

        std::string genSalt();

        std::string hashPass(std::string pass, std::string salt);

        std::string getPassword();

        bool validPassword(std::string username, std::string password);

        int passwordStrength(std::string password);
        
        bool findVoter(std::string nid, Voter &v);

        
    public:

        void registerVoter();
        
        void loginVoter();
        
        void updateVoter(std::string targetNID, bool lockStatus);

};