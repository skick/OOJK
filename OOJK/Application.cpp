#include "Application.h"
#include "LoadInformation.h"
#include "DataUtilities.h"
#include <iostream>

void Application::Run(){

    Setup();

    while (true)
    {
        char decision;
        std::cout << "\n";
        std::cout << "Find (A)gency\n";
        std::cout << "Find (D)river\n";
        std::cout << "Find (C)ustomer\n";
        std::cout << "Add, find or delete (T)ravel\n";
        std::cout << "(P)rint customer's information by ID\n";
        std::cout << "Print travellers (B)etween dates\n";
        std::cout << "(Q)uit\n";
        std::cout << "\n";
        std::cin >> decision;
        switch (decision)
        {
        case 'A':
        case 'a':
            {
                try{
                    Agency ag = FindItem(agencies);
                    std::cout << ag.toString();
                    WaitInput();
                }catch(const char* msg){
                    std::cout << msg;
                }
                continue;
            }
        case 'D':
        case 'd':
            {
                try{
                    Driver dr = FindItem(drivers);
                    std::cout << dr.toString();
                    WaitInput();
                }catch(const char* msg){
                    std::cout << msg;
                }
                continue;
            }
        case 'C':
        case 'c':
            {
                try{
                    Customer cu = FindItem(customers);
                    std::cout << cu.toString();
                    WaitInput();
                } catch(const char* msg){
                    std::cout << msg;
                }
                continue;
            }
        case 'T':
        case 't':
            TravelOperations();
            continue;
        case 'P':
        case 'p':
            CustomerOperations();
            continue;
        case 'B':
        case 'b':
            du.PrintCustomersBetweenDates(travels, customers);
            WaitInput();
            continue;
        case 'q':
            return;
        default:
            std::cout << "Not valid input.\n";
            WaitInput();
            continue;
        }
    }
}

void Application::Setup(){
    char filetype;
    while (true)
    {
        std::cout << "Select filetype:\n (T)iny\n (S)mall\n (M)edium\n (B)ig\n";
        std::cin >> filetype;
        switch (filetype)
        {
        case 't':
        case 'T':
            Load("txtfiles/tiny/");
            return;
        case 's':
        case 'S':
            Load("txtfiles/small/");
            return;        
        case 'm':
        case 'M':
            Load("txtfiles/medium/");
            return;    
        case 'b':
        case 'B':
            Load("txtfiles/big/");
            return;   
        default:
            std::cout << "Invalid input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }

}

void Application::Load(std::string file){
    LoadInformation li(file + "agencies.txt",
                       file + "customers.txt",
                       file + "drivers.txt",
                       file + "travels.txt");
    li.ReadFiles();
    agencies = li.getAgencies();
    customers = li.getCustomers();
    drivers = li.getDrivers();
    travels = li.getTravels();
}

template<class T>
T Application::FindItem(std::vector<T>& group){
    char idorname;
    while(true)
    {
        std::cout << "\n";
        std::cout << "Do you want to find by (I)d or (N)ame?\n";
        std::cout << "(E)xit\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> idorname;
        switch (idorname)
        {
            case 'N':
            case 'n':
            {
                std::string name;
                std::cout << "\n";
                std::cout << "Enter name: \n";
                std::cin >> name;
                return du.FindItemByName(group, name);
            }
            case 'I':
            case 'i':
            {
                int id;
                std::cout << "\n";
                std::cout << "Enter ID\n";
                std::cin >> id;
                if(!std::cin.fail())
                {
                    return du.FindItemById(group, id); 
                }
                else
                {
                    std::cout << "Not a valid input.\n";
                    std::cin.clear();
                    continue;
                }    
                break;
            case 'E':
            case 'e':
            {
                throw "Exited from finding item.\n";
            }
            }
            default:
                std::cout << "Not a valid input.\n";
                std::cin.clear();
                continue;
        }
    }
}

void Application::TravelOperations(){
    char decision;
    while (true)
    {
        std::cout << "(A)dd travel\n";
        std::cout << "(D)elete travel\n";
        std::cout << "(F)ind travel\n";
        std::cout << "(E)xit\n";
        std::cin >> decision;
        switch (decision)
        {
            case 'A':
            case 'a':
                {
                    du.AddTravel(travels, drivers, customers);
                    continue;
                }
            case 'D':
            case 'd':
                {
                    int id;
                    std::cout << "Enter id: \n";
                    std::cin >> id;
                    if(!std::cin.fail())
                    {
                        du.DeleteItemById(travels, id);
                        continue;
                    }
                    else
                    {
                        std::cout << "Not valid input.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    continue;
                }
            case 'F':
            case 'f':
                {
                    int id;
                    std::cout << "Enter id: \n";
                    std::cin >> id;
                    if(!std::cin.fail())
                    {
                        try{
                            Travel tr = du.FindItemById(travels, id);
                            std::cout << tr.toString();
                            WaitInput();
                        }catch(const char* msg){
                            std::cout << msg;
                        }
                        continue;
                    }
                    else
                    {
                        std::cout << "Not valid input.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    continue;
                }
            case 'e':
            case 'E': 
                return;
            default:
                std::cout << "Not valid input.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
        }
    }
    return;
}

void Application::CustomerOperations(){
    int id;
    char decision;
    while (true)
    {
        std::cout << "Enter customer's ID: \n";
        std::cin >> id;
        try{
            du.FindItemById(customers, id);
        } catch(const char* msg){
            std::cout << msg;
        }
        break;
    }
    while (true)
    {
        std::cout << "Print (T)ravels\n";
        std::cout << "Print (D)rivers\n";
        std::cout << "(E)xit\n";
        std::cin >> decision;
        switch (decision)
        {
        case 'T':
        case 't':
            du.PrintCustomerTravels(travels, id);
            break;
        case 'D':
        case 'd':
            du.PrintCustomerDrivers(travels, drivers, id);
            break;
        case 'E':
        case 'e':
            return;
        default:
            std::cout << "Not valid input. \n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    return;
}

void Application::WaitInput(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Press enter.\n";
    std::cin.get();
    return;
}

