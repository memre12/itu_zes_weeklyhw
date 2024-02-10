# Hospital Queue Project
* This project is a simple hospital registration system implemented in C++. The system includes classes for handling patient registration, examination queues, and CSV file output.

## Person Class (Person.hpp, Person.cpp):

* Represents an individual with attributes such as name, age, and disability status. Provides methods to print person information and write it to a CSV file.
## Patient Class (HospitalRegistration.hpp, HospitalRegistration.cpp):
* Inherits from the Person class. Represents a patient in the hospital, with additional attributes such as a patient number and priority score. Calculates the priority score based on the presence of a disability and the patient's age. Overloads the less-than operator (<) to enable sorting patients based on their priority scores. Provides methods to print patient information and write it to a CSV file.
## HospitalRegistration Class (HospitalRegistration.hpp, HospitalRegistration.cpp):

* Manages the registration and examination queues for patients. Uses a standard queue (registrationQueue) for patient registrations and a priority queue (examinationQueue) for patients waiting for examination. Methods include registering a patient, printing the registration and examination queues, calling the next patient for examination, and writing patient information to a CSV file.
## Main Program (main.cpp):

* Creates an instance of the HospitalRegistration class. Creates several instances of the Person class representing different patients and registers them in the hospital. Prints the examination queue and writes patient information to a CSV file.
