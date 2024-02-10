// main.cpp
#include "Menu.hpp"
#include "Displaymenu.hpp"
#include "mainfunction.hpp"
#include <iostream>

int main() {
    std::string clientname;
    std::string clientsurname;
    std::string gendertoadress;
    int choice;

    
    std::cout << "****** Welcome to ZES Restaurant ******" << std::endl;
    std::cout << "Name: " << std::endl;
    getline(std::cin,clientname);
    std::cout << "Surname: " << std::endl;
    getline(std::cin,clientsurname);
    std::cout << "Gender address:\n1-Mr\n2-Mrs" << std::endl;
    std::cin >> choice;
    if (choice==1) {
        gendertoadress = "Mr";
    }else {
        gendertoadress = "Mrs";
    }
    
    User client(clientname,clientsurname);
    client.set_gender(gendertoadress);

    showmenu();

    client.get_name();
    client.get_surname();
    client.get_gender();
    
    
    return 0;
}