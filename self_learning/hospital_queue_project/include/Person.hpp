// person.hpp

#pragma once

#ifndef PERSON_HPP  // Include guard to prevent multiple inclusion
#define PERSON_HPP

#pragma once

#include <queue>
#include <list>
#include <iostream>
#include <string>
#include <fstream>

class Person {
protected:
    std::string name;
    int age;
    bool disability;

public:
    Person(std::string _name, int _age, bool _disability);
    void print() const;
    void writeToCSV(std::ofstream& file) const;
};

class Patient : public Person {
private:
    int patientNumber;
    int priorityScore;

public:
    Patient(int _patientNumber, Person& p);
    Patient(int _patientNumber, std::string _name, int _age, bool _disability = false);
    void calculatePriorityScore();
    bool operator<(const Patient& p) const;
    void print();
    void writeToCSV(std::ofstream& file) const;
};




#endif // PERSON_HPP
