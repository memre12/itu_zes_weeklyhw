#include "Person.hpp"

Person::Person(std::string _name, int _age, bool _disability) : name(_name), age(_age), disability(_disability) {}

void Person::print() const {
    std::cout << "Name: " << name << std::endl << "Age: " << age << std::endl << "Disability: ";
    if (disability) {
        std::cout << "Yes";
    } else {
        std::cout << "No";
    }
    std::cout << std::endl;
}

void Person::writeToCSV(std::ofstream& file) const {
    file << name << "," << age << "," << (disability ? "Yes" : "No") << std::endl;
}

Patient::Patient(int _patientNumber, Person& p) : patientNumber(_patientNumber), Person(p), priorityScore(0) {
    calculatePriorityScore();
}

Patient::Patient(int _patientNumber, std::string _name, int _age, bool _disability) : Person(_name, _age, _disability), patientNumber(_patientNumber), priorityScore(0) {}

void Patient::calculatePriorityScore() {
    if (disability) {
        priorityScore += 30;
    }
    if (age >= 65) {
        priorityScore += age - 65;
    }
}

bool Patient::operator<(const Patient& p) const {
    return priorityScore < p.priorityScore;
}

void Patient::print() {
    std::cout << "Patient number: " << patientNumber << std::endl;
    Person::print();
    std::cout << "Priority score: " << priorityScore << std::endl;
}

void Patient::writeToCSV(std::ofstream& file) const {
    file << patientNumber << "," << name << "," << age << "," << (disability ? "Yes" : "No") << "," << priorityScore << std::endl;
}
