#include "Person.hpp"
#include "HospitalRegistration.hpp"
#include <iostream>

int main(){
    HospitalRegistration hospital;

    // Example patient registrations
    Person patient1("Ahmet", 70, true);
    Person patient2("Ayse", 45, false);
    Person patient3("Selin", 45, false);
    Person patient4("Baha",70,true);


    hospital.registerPatient(patient1);
    hospital.registerPatient(patient2);
    hospital.registerPatient(patient3);
    hospital.registerPatient(patient4);
    

    // Print patient registration and examination queues
    std::cout << std::endl;
    hospital.printExaminationQueue();
    hospital.writeToCSV("patient_info.csv");

    return 0;
}