#ifndef MAIN_FUNCTIONS_HPP
#define MAIN_FUNCTIONS_HPP

#include "HospitalRegistration.hpp"
#include "Person.hpp"
#include <iostream>
#include <string>

class main_functions
{
private:
    HospitalRegistration hospital;

public:
    main_functions();
    void set_patient();
    void register_patient(Person& p);
    void print_registration_queue();
    void print_examination_queue();
    void print_examination_queue_message();
    void call_patient();
    ~main_functions();
    void run();
};

#endif // MAIN_FUNCTIONS_HPP
