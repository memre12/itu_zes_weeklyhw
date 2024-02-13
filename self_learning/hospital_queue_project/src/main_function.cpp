#include "main_functions.hpp"
#include <iostream>
#include <string>
#include "HospitalRegistration.hpp"
#include "Person.hpp"
#include <fstream>


void main_functions::set_patient()
{
    std::string name;
    std::string age;  // You are not taking the patient's age input, consider adding a prompt for age input
    bool disability;
    int age_;

    std::cout << "Enter patient name: ";
    std::cin >> name;

    // Consider adding a prompt for the patient's age


    while (true) {
        std::cout << "Enter patient age: ";
        std::cin >> age;
        try {
            // std::stoi throws std::invalid_argument or std::out_of_range on failure
            age_ = std::move(std::stoi(age));
            
            // Validate the range of the choice
            if (age_ < 0 && age_ > 150) {
                throw std::out_of_range("Invalid choice");
            }

            // If no exception is thrown, the conversion was successful
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid argument. Please enter a number." << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: Out of range. The entered number is too large or too small. Please enter a valid number." << std::endl;
        }
    }

    // Input validation for disability (1 for yes, 0 for no)
    while (true) {
        std::cout << "Does the patient have a disability? (1 for yes, 0 for no): ";
        std::cin >> disability;

        if (std::cin.fail()) {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
            std::cerr << "Error: Invalid input. Please enter 1 or 0." << std::endl;
        } else {
            break;
        }
    }


    Person p(name, age_, disability);
    hospital.registerPatient(p);
}


void main_functions::register_patient(Person& p)
{
    hospital.registerPatient(p);
}

void main_functions::print_registration_queue()
{
    hospital.printRegistrationQueue();
}

void main_functions::print_examination_queue()
{
    hospital.printExaminationQueue();
}

void main_functions::print_examination_queue_message()
{
    hospital.printExaminationQueueMessage();
}

void main_functions::call_patient()
{
    hospital.callPatient();
}


main_functions::~main_functions()
{
}

main_functions::main_functions()
{
}

void main_functions::run()
{
    std::string choice;
    int convertedValue;
    while (true)
    {
        while (true) {
            std::cout << "1. Set patient\n2. Print registration queue\n3. Print examination queue\n4. Print examination queue message\n5. Call patient\n6. Write to CSV\n7. Exit\n";
            std::cin >> choice;
            try {
                // std::stoi throws std::invalid_argument or std::out_of_range on failure
                convertedValue = std::stoi(choice);
                if (convertedValue < 1 || convertedValue > 8) {
                    throw std::out_of_range("Invalid choice");
                }
                // If no exception is thrown, the conversion was successful
                break;
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid argument. Please enter a valid number." << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Error: Out of range. The entered number is too large or too small." << std::endl;
            }
        }
        
        switch (convertedValue)
        {
        case 1:
            set_patient();
            break;
        case 2:
            print_registration_queue();
            break;
        case 3:
            print_examination_queue();
            break;
        case 4:
            print_examination_queue_message();
            break;
        case 5:
            call_patient();
            break;
        case 6:
            hospital.writeToCSV("patient_info.csv");
            break;
        case 7:
            return;
        default:
            std::cout << "Invalid choice\n";
            break;
        }
    }
}