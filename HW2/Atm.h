//
// Created by amoscoso on 5/21/2017.
//

#ifndef HW2_ATM_H
#define HW2_ATM_H


class Atm {
public:
    Atm(int atm_number);
    void do_commands(string path);

private:
    void account(int id,string password, int initial_amount);
    void deposit(int id,string password, int amount);
    void withdraw(int id,string password, int amount);
    void check_balance(int id);

    void transfer(int source_id, string password, int target_id, int amount);
    int _atm_number;
};






#endif //HW2_ATM_H
