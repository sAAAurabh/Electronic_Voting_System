#pragma once
#include "voter.h"
#include "candidate.h"
#include <string>
#include <cctype>

enum login_result{
    login_success,
    not_found,
    wrong_pass,
    acc_locked
};

enum pass_val{
    number, letter, capital, is_valid, name, special
};


class Admin
{
private:
    std::string voter_file = "Other files/voter.txt";
    std::string candidate_file = "Other files/candidate.txt";

public:
    std::string gen_salt();
    std::string hash_pass(const std::string& pass, const std::string& salt);

    bool find_voter(const std::string& nid, Voter& v);
    bool find_candidate(const std::string& nid, Candidate& c);

    bool all_empty(Voter obj);

    void add_voter(const Voter& v);
    void add_candidate(const Candidate& c);

    void update_voter(const Voter& v);
    void update_candidate(const Candidate& c);

    std::string get_manifesto(const std::string &nid);


    login_result login_voter(const std::string& nid, const std::string& pass);
    login_result login_candidate(const std::string& nid, const std::string& pass);

    pass_val is_valid_pass(std::string pass, std::string nm);

};