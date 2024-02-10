#include "HospitalRegistration.hpp"



void HospitalRegistration::registerPatient(Person& p) {
    Patient patient(registrationQueue.size() + 1, p);
    registrationQueue.push_back(patient);
    examinationQueue.push(patient);
}

void HospitalRegistration::printRegistrationQueue() const {
    std::cout << "Patient registration queue start" << std::endl;
    if (registrationQueue.empty()) {
        std::cout << "No registered patients" << std::endl;
    } else {
        std::list<Patient>::const_iterator iter = registrationQueue.begin();
        while (iter != registrationQueue.end()) {
            Patient p = *iter;
            p.print();
            iter++;
            if (iter != registrationQueue.end()) {
                std::cout << std::endl;
            }
        }
    }
    std::cout << "Patient registration queue end" << std::endl;
}

void HospitalRegistration::printExaminationQueue() const {
    std::cout << "Examination queue start" << std::endl;
    if (examinationQueue.empty()) {
        std::cout << "No patients waiting for examination" << std::endl;
    } else {
        std::priority_queue<Patient> tempQueue = examinationQueue;
        while (!tempQueue.empty()) {
            Patient p = tempQueue.top();
            p.print();
            tempQueue.pop();
            if (!tempQueue.empty()) {
                std::cout << std::endl;
            }
        }
    }
    std::cout << "Examination queue end" << std::endl;
}

void HospitalRegistration::printExaminationQueueMessage() const {
    std::cout << "### Printing examination queue ###" << std::endl;
    if (examinationQueue.empty()) {
        std::cout << "No patients waiting for examination." << std::endl;
    } else {
        std::priority_queue<Patient> queueCopy = examinationQueue;
        while (!queueCopy.empty()) {
            Patient p = queueCopy.top();
            p.print();
            queueCopy.pop();
            if (!queueCopy.empty()) {
                std::cout << std::endl;
            }
        }
    }
    std::cout << "### Examination queue end ###" << std::endl;
}

void HospitalRegistration::callPatient() {
    if (examinationQueue.empty()) {
        std::cout << "No patients waiting for examination." << std::endl;
    } else {
        std::cout << "Patient called for examination." << std::endl;
        Patient p = examinationQueue.top();
        p.print();
        examinationQueue.pop();
    }
}

void HospitalRegistration::writeToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& p : registrationQueue) {
            p.writeToCSV(file);
        }
        file.close();
        std::cout << "Patient information written to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}