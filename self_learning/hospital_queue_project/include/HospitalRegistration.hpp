// HospitalRegistration.hpp
#pragma once

#ifndef HOSPITALREGISTRATION_HPP
#define HOSPITALREGISTRATION_HPP

#include "Person.hpp"
#include <iostream>
#include <list>


class HospitalRegistration {
private:
    std::list<Patient> registrationQueue;
    std::priority_queue<Patient> examinationQueue;

public:
    void registerPatient(Person& p);
    void printRegistrationQueue() const;
    void printExaminationQueue() const;
    void printExaminationQueueMessage() const;
    void callPatient();
    void writeToCSV(const std::string& filename) const;
};



#endif // HOSPITALREGISTRATION_HPP