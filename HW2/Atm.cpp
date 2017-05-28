//
// Created by amoscoso on 5/21/2017.
//

#include <unistd.h>
#include <memory.h>
#include "Atm.h"
#include <fstream>
#include <sstream>
#include <cstdlib>


using namespace std;
Atm::Atm(int atm_number, AccountDataBase *ADT, IOThreadSave *IOTS) {
    this-> IOTS = IOTS;
    this->_atm_number=atm_number;
    this->_ADT=ADT; // the idea is that all the atm will have acces to the same ADT

}

void Atm::do_commands(string path) {

    ifstream file(path.c_str());
    if (!file.is_open()) {
        fprintf(stderr, "cannot open trace file\n");
        exit(2);
    }
    string line;

    while (getline(file,line)) {
        if (line  == "\n") {
            file.close();
            break;
        }
        usleep(10000);
        istringstream iss(line);
        string instruction[5];
        int i = 0;
       do{
            iss >> instruction[i] ;
           i++;
        }while (iss);


        if(instruction[0] == "O") {
            this->account(atoi(instruction[1].c_str()), instruction[2], atoi(instruction[3].c_str()));
        }
        if(instruction[0] == "D") {
            this->deposit(atoi(instruction[1].c_str()), instruction[2], atoi(instruction[3].c_str()));
        }
        if(instruction[0] == "W") {
            this->withdraw(atoi(instruction[1].c_str()), instruction[2], atoi(instruction[3].c_str()));
        }
        if(instruction[0] == "B") {
            this->check_balance(atoi(instruction[1].c_str()), instruction[2]);
        }
        if(instruction[0] == "C") {
            this->close_account(atoi(instruction[1].c_str()), instruction[2]);
        }
        if(instruction[0] == "T") {
            this->transfer(atoi(instruction[1].c_str()), instruction[2], atoi(instruction[3].c_str()), atoi(instruction[4].c_str()));
        }

    }


}

void Atm::account(int id, string password, int initial_amount) {
    string to_print;

    pthread_mutex_lock(&this->_ADT->db_write_lock);

    char * number;
    char * id_char;
    char* initial_amount_char;
    if (this->_ADT->insert_account(id,password,initial_amount))//todo check if insert to map check duplicity
    {
        itoa(id,id_char,10);
        itoa(_atm_number,number,10);
        itoa(initial_amount,initial_amount_char,10);
        
         to_print= string(number)+": New account id is "+string(id_char)+" with password "+password+" and initial balance "+string(initial_amount_char)+"\n";
    }
    else
        itoa(_atm_number,number,10);
          to_print= string(number)+": Your transaction failed - account with same id exists\n";

    pthread_mutex_unlock(&this->_ADT->db_write_lock);
    this->IOTS->save_to_log(to_print);
    return;
}

void Atm::deposit(int id, string password, int amount) {
    string to_print;
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count++;
    if (this->_ADT->rd_count==1)
        pthread_mutex_lock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    Account * temp = this->_ADT->search_account(id);

    char * number_char;
    char * id_char;
    char* initial_amount_char;
    char* new_balance_string;
    char* amount_string;
    itoa(id,id_char,10);
    itoa(_atm_number,number_char,10);
    itoa(amount,initial_amount_char,10);

    if (temp == NULL)
    {

         to_print= "Error "+ string(number_char)+": Your transaction failed - account "+string(id_char)+" does not exist\n" ;


    }else {

        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->write_lock);
            sleep(1);
            temp->deposit(amount);


            itoa(id,id_char,10);
            itoa(_atm_number,number_char,10);
            int new_balance=temp->check_balance();
            itoa(new_balance,new_balance_string,10);
            itoa(amount,amount_string,10);
             to_print= string(number_char)+ ": Account "+ string(id_char) + " new balance is " +string(new_balance_string) + " after "
                 + string(amount_string) + " $ was deposited" +"\n";
            pthread_mutex_unlock(&temp->write_lock);
        } else
            itoa(id,id_char,10);
        itoa(_atm_number,number_char,10);
             to_print= "Error " +string(number_char) + ": Your transaction failed - password for account " + string(id_char)
                 + " is incorrect" +"\n";
    }
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count--;
    if (this->_ADT->rd_count==0)
        pthread_mutex_unlock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    this->IOTS->save_to_log(to_print);
    return;


}

void Atm::withdraw(int id, string password, int amount) {
    char * number_char;
    char *id_char;
    char *amount_string;
    char* new_balance_string;
    itoa(amount,amount_string,10);
    string to_print;
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count++;
    if (this->_ADT->rd_count==1) {
        pthread_mutex_lock(&this->_ADT->db_write_lock);
    }
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    Account *temp = this->_ADT->search_account(id);
    itoa(id,id_char,10);
    itoa(_atm_number,number_char,10);
    if (temp == NULL) {

        to_print="Error "+string(number_char) + ": Your transaction failed - account "+string(id_char) + " does not exist" +"\n";
    }
    else {
        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->write_lock);
            sleep(1);
            if (temp->withdraw(amount)) {
                int new_balance=temp->check_balance();
                itoa(new_balance,new_balance_string,10);
                to_print= string(number_char)+ ": Account "+ string(id_char) + " new balance is " +string(new_balance_string) + " after "
                                             + string(amount_string) + " $ was withdrew" +"\n";
            }
            else {
                to_print= "Error " +string(number_char) + ": Your transaction failed - account " + string(id_char)
                                 + " balance is lower than " + string(amount_string) +"\n";
            }
            pthread_mutex_unlock(&temp->write_lock);
        } else {
            to_print= "Error " +string(number_char) + ": Your transaction failed - password for account " + string(id_char)
                                     + " is incorrect" +"\n";
        }
    }
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count--;
    if (this->_ADT->rd_count==0) {
        pthread_mutex_unlock(&this->_ADT->db_write_lock);
    }
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    this->IOTS->save_to_log(to_print);
    return;
}

void Atm::check_balance(int id, string password){
    char * number_char;
    char *id_char;
    itoa(id,id_char,10);
    itoa(_atm_number,number_char,10);
    char * new_balance_string;
    string to_print;
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count++;
    if (this->_ADT->rd_count==1)
        pthread_mutex_lock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    Account *temp = this->_ADT->search_account(id);

    if (temp == NULL) {
        to_print="Error "+string(number_char) + ": Your transaction failed - account "+string(id_char) + " does not exist" +"\n";

    }
    else {
        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->read_lock);
            sleep(1);
            temp->rd_count++;
            if (temp->rd_count == 1)
                pthread_mutex_lock(&temp->write_lock);
            pthread_mutex_unlock(&temp->read_lock);
            int new_balance=temp->check_balance();
            itoa(new_balance,new_balance_string,10);
            to_print= string(number_char)+ ": Account "+ string(id_char)+ " balance is " +string(new_balance_string) +"\n";
            pthread_mutex_lock(&temp->read_lock);
            temp->rd_count--;
            if (temp->rd_count == 0)
                pthread_mutex_unlock(&temp->write_lock);
            pthread_mutex_unlock(&temp->read_lock);
        } else
            to_print= "Error " +string( number_char) + ": Your transaction failed - password for account " + string(id_char)
                             + " is incorrect" +"\n";
    }
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count--;
    if (this->_ADT->rd_count==0)
        pthread_mutex_unlock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    this->IOTS->save_to_log(to_print);
    return;

}

void Atm::close_account(int id, string password){
    char * number_char;
    char *id_char;
    itoa(id,id_char,10);
    itoa(_atm_number,number_char,10);
    string to_print;
    pthread_mutex_lock(&this->_ADT->db_write_lock);
    sleep(1);
    Account *temp = this->_ADT->search_account(id);
    if (temp == NULL) {
        to_print="Error "+string(number_char) + ": Your transaction failed - account "+string(id_char) + " does not exist" +"\n";

    }
    else {
        if (temp->check_password(password))
            this->_ADT->delete_account(id);
        else
            to_print= "Error " +string( number_char) + ": Your transaction failed - password for account " + string(id_char)
                             + " is incorrect" +"\n";

    }
    pthread_mutex_unlock(&this->_ADT->db_write_lock);
    this->IOTS->save_to_log(to_print);
    return;

}

void Atm::transfer(int source_id, string password, int target_id, int amount) {
    char * number_char;
    char *source_id_char;
    char *target_id_char;
    char * amount_string;
    itoa(amount,amount_string,10);
    itoa(source_id,source_id_char,10);
    itoa(target_id,target_id_char,10);
    itoa(_atm_number,number_char,10);
    string to_print;
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count++;
    if (this->_ADT->rd_count==1)
        pthread_mutex_lock(&this->_ADT->db_write_lock);

    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    Account *temp1 = this->_ADT->search_account(source_id);
    Account *temp2 = this->_ADT->search_account(target_id);



    if (temp1 == NULL ) {
        to_print="Error "+string(number_char) + ": Your transaction failed - account "+string(source_id_char) + " does not exist"
                        +"\n";

    }
    else
    if (temp2 == NULL ) {
        to_print="Error "+string(number_char) + " Your transaction failed - account "+string(target_id_char) + " does not exist"
             +"\n";
    }
    else {
        if (temp1->check_password(password)) {
            if (source_id < target_id) {
                pthread_mutex_lock(&temp1->write_lock);
                pthread_mutex_lock(&temp2->write_lock);
            } else {
                pthread_mutex_lock(&temp2->write_lock);
                pthread_mutex_lock(&temp1->write_lock);
            }
            sleep(1);
            if (temp1->withdraw(amount)) {
                temp2->deposit(amount);
                int new_balance=temp1->check_balance();
                int new_balance2 = temp2->check_balance();
                char * new_balance_string_2;
                char * new_balance_string;
                itoa(new_balance,new_balance_string,10);
                itoa(new_balance2,new_balance_string_2,10);
                to_print= string(number_char)+ ": Transfer from account " +string(source_id_char)  +" to account " +string(target_id_char)
                     + " new account balance is  "
                      +string(new_balance_string) + " $ new target account balance is " + string(new_balance_string_2) +" $ \n";
            } else
                to_print= "Error " +string(number_char) + ": Your transaction failed - account " + string(source_id_char)
                     + " balance is lower than " + string(amount_string) +"\n";
            pthread_mutex_unlock(&temp2->write_lock);
            pthread_mutex_unlock(&temp1->write_lock);
        } else
            to_print= "Error " +string( number_char) + ": Your transaction failed - password for account " + string(source_id_char)
                             + " is incorrect" +"\n";
    }
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count--;
    if (this->_ADT->rd_count==0)
        pthread_mutex_unlock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    this->IOTS->save_to_log(to_print);
    return;
}
