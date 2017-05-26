//
// Created by amoscoso on 5/21/2017.
//

#include <unistd.h>
#include <memory.h>
#include "Atm.h"

Atm::Atm(int atm_number, AccountDataBase *ADT, IOThreadSave *IOTS) {
    this-> IOTS = IOTS;
    this->_atm_number=atm_number;
    this->_ADT=ADT; // the idea is that all the atm will have acces to the same ADT

}

void Atm::do_commands(string path) {

    FILE *fp=fopen(path,"r");
    if (fp == 0) {
        fprintf(stderr, "cannot open trace file\n");
        exit(2);
    }

    char * line=NULL;
    while (fgets(line, 256, fp) != NULL) {
        if (line  == "\n") {
            fclose(fp);
            break;
        }
        usleep(10000);
        string instruction[5];
        int i = 0;
        for (i = 0; i < 5; ++i) {
            instruction[i] = string(strtok_r(line, " ",&line)); //Todo cheack whtat happends when string gets char *
        }


        if(instruction[0] == "O") {
            this->account(atoi(instruction[1]), instruction[2], atoi(instruction[3]));
        }
        if(instruction[0] == "D") {
            this->deposit(atoi(instruction[1]), instruction[2], atoi(instruction[3]));
        }
        if(instruction[0] == "W") {
            this->withdraw(atoi(instruction[1]), instruction[2], atoi(instruction[3]));
        }
        if(instruction[0] == "B") {
            this->check_balance(atoi(instruction[1]), instruction[2]);
        }
        if(instruction[0] == "C") {
            this->close_account(atoi(instruction[1]), instruction[2]);
        }
        if(instruction[0] == "T") {
            this->transfer(atoi(instruction[1]), instruction[2], atoi(instruction[3]), atoi(instruction[4]));
        }

    }


}

void Atm::account(int id, string password, int initial_amount) {
    string to_print;
    pthread_mutex_lock(&this->_ADT->db_write_lock);
     if (this->_ADT->insert_account(id,password,initial_amount))//todo check if insert to map check duplicity
    {
         to_print= to_string(_atm_number)+" New account id is "+to_string(id)+" with password "+password+" and initial balance "+to_string(initial_amount)+"\n";
    }
    else
          to_print= to_string(_atm_number)+" Your transaction failed - account with same id exists\n";

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
    if (temp == NULL)
    {

         to_print= "Error "+ to_string(this->_atm_number)+" Your transaction failed - account "+to_string(id)+" does not exist\n" ;


    }else {

        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->write_lock);
            sleep(1);
            temp->deposit(amount);
             to_print= to_string(_atm_number)+ " account "+ to_string(id) + " new balance is " +to_string(temp->check_balance()) + " after "
                 + to_string(amount) + "was deposited" +"\n";
            pthread_mutex_unlock(&temp->write_lock);
        } else
             to_print= "Error " +to_string( this->_atm_number) + " Your transaction failed - password for account " + to_string(id)
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
    string to_print;
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count++;
    if (this->_ADT->rd_count==1) {
        pthread_mutex_lock(&this->_ADT->db_write_lock);
    }
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    Account *temp = this->_ADT->search_account(id);

    if (temp == NULL) {
        to_print="Error "+to_string(this->_atm_number) + " Your transaction failed - account "+to_string(id) + " does not exist" +"\n";
    }
    else {
        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->write_lock);
            sleep(1);
            if (temp->withdraw(amount)) {
                to_print= to_string(_atm_number)+ " account "+ to_string(id) + " new balance is " +to_string(temp->check_balance()) + " after "
                                             + to_string(amount) + "was withdrew" +"\n";
            }
            else {
                to_print= "Error " +to_string(this->_atm_number) + " Your transaction failed - account " + to_string(id)
                                 + " balance is lower than " + to_string(amount) +"\n";
            }
            pthread_mutex_unlock(&temp->write_lock);
        } else {
            to_print= "Error " +to_string( this->_atm_number) + " Your transaction failed - password for account " + to_string(id)
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
    string to_print;
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count++;
    if (this->_ADT->rd_count==1)
        pthread_mutex_lock(&this->_ADT->db_write_lock);
    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    Account *temp = this->_ADT->search_account(id);

    if (temp == NULL) {
        to_print="Error "+to_string(this->_atm_number) + " Your transaction failed - account "+to_string(id) + " does not exist" +"\n";

    }
    else {
        if (temp->check_password(password)) {
            pthread_mutex_lock(&temp->read_lock);
            sleep(1);
            temp->rd_count++;
            if (temp->rd_count == 1)
                pthread_mutex_lock(&temp->write_lock);
            pthread_mutex_unlock(&temp->read_lock);
            to_print= to_string(_atm_number)+ " account "+ to_string(id)+ " balance is " +to_string(temp->check_balance()) +"\n";
            pthread_mutex_lock(&temp->read_lock);
            temp->rd_count--;
            if (temp->rd_count == 0)
                pthread_mutex_unlock(&temp->write_lock);
            pthread_mutex_unlock(&temp->read_lock);
        } else
            to_print= "Error " +to_string( this->_atm_number) + " Your transaction failed - password for account " + to_string(id)
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
    string to_print;
    pthread_mutex_lock(&this->_ADT->db_write_lock);
    sleep(1);
    Account *temp = this->_ADT->search_account(id);
    if (temp == NULL) {
        to_print="Error "+to_string(this->_atm_number) + " Your transaction failed - account "+to_string(id) + " does not exist" +"\n";

    }
    else {
        if (temp->check_password(password))
            this->_ADT->delete_account(id);
        else
            to_print= "Error " +to_string( this->_atm_number) + " Your transaction failed - password for account " + to_string(id)
                             + " is incorrect" +"\n";

    }
    pthread_mutex_unlock(&this->_ADT->db_write_lock);
    this->IOTS->save_to_log(to_print);
    return;

}

void Atm::transfer(int source_id, string password, int target_id, int amount) {
    string to_print;
    pthread_mutex_lock(&this->_ADT->db_read_lock);
    this->_ADT->rd_count++;
    if (this->_ADT->rd_count==1)
        pthread_mutex_lock(&this->_ADT->db_write_lock);

    pthread_mutex_unlock(&this->_ADT->db_read_lock);
    Account *temp1 = this->_ADT->search_account(source_id);
    Account *temp2 = this->_ADT->search_account(target_id);



    if (temp1 == NULL ) {
        to_print="Error "+to_string(this->_atm_number) + " Your transaction failed - account "+to_string(source_id) + " does not exist"
                        +"\n";

    }
    else
    if (temp2 == NULL ) {
        to_print="Error "+to_string(this->_atm_number) + " Your transaction failed - account "+to_string(target_id) + " does not exist"
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
                to_print= to_string(_atm_number)+ " Transfer from account " +to_string(source_id)  +" to account " +to_string(target_id)
                     + " new account balance is  "
                      +to_string(temp1->check_balance()) + " new target account balance is " + to_string(temp2->check_balance()) +"\n";
            } else
                to_print= "Error " +to_string(this->_atm_number) + " Your transaction failed - account " + to_string(source_id)
                     + " balance is lower than " + to_string(amount) +"\n";
            pthread_mutex_unlock(&temp2->write_lock);
            pthread_mutex_unlock(&temp1->write_lock);
        } else
            to_print= "Error " +to_string( this->_atm_number) + " Your transaction failed - password for account " + to_string(source_id)
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
