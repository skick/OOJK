#ifndef DATAUTILITIES_H_INCLUDED
#define DATAUTILITIES_H_INCLUDED

#include "Agency.h"
#include "Driver.h"
#include "Customer.h"
#include "Travel.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

class DataUtilities {

public:

    template<class T>
    T FindItemByName(std::vector<T>& group, std::string& name) const{
        for(auto i : group)
        {
            if(i.getName() == name)
            {
                return i;
            }
        }
        throw "Item was not found\n";
    }

    template<class T>
    T FindItemById(std::vector<T>& group, int& id) const{
        for(auto i : group)
        {
            if(i.getId() == id)
            {
                return i;
            }
        }
        throw "Item was not found\n";
    }

    template<class T>
    bool CheckItemById(std::vector<T>& group, int& id) const{
        for(auto i : group)
        {
            if(i.getId() == id)
            {
                return true;
            }
        }
        return false;
    }

    template<class T>
    void DeleteItemById(std::vector<T>& group, int& id){
        int i = 0;
        for(auto item : group)
        {
            if(item.getId() == id)
            {
                group.erase(group.begin()+i);
                return;
            }
            i++;
        }
        std::cout << "Item was not found.\n";
        return;
    }

    void AddTravel(std::vector<Travel>& travels,
                   std::vector<Driver>& drivers,
                   std::vector<Customer>& customers){
        int id;
        int driverId;
        time_t startTime;
        int customerId;
        std::string from;
        std::string to;
        double reward;

        while (true)
        {
            std::cout << "Enter ID for the travel: \n";
            std::cin >> id;
            while(std::cin.fail())
            {
                std::cout << "Input needs to be a integer. \n";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> id;  
            }
            if(CheckItemById(travels, id))
            {
                std::cout << "ID is already in use.\n";
            }
            else
                break;                 
        }

        while (true)
        {
            std::cout << "Enter driver's ID: \n";
            std::cin >> driverId;
            while(std::cin.fail())
            {
                std::cout << "Input needs to be a integer. \n";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> driverId;  
            }
            if(!CheckItemById(drivers, driverId))
            {
                std::cout << "Driver not found.\n";
            }
            else
                break;                 
        }

        while (true)
        {
            std::cout << "Enter customer's ID: \n";
            std::cin >> customerId;
            while(std::cin.fail())
            {
                std::cout << "Input needs to be a integer. \n";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> customerId;  
            }
            if(!CheckItemById(customers, customerId))
            {
                std::cout << "Customer not found.\n";
            }
            else
                break;                 
        }

        std::cout << "Enter starting time:\n";
        startTime = MakeDate();

        std::cout << "Enter departure location:\n";
        std::cin >> from;
        while ((getchar()) != '\n');

        std::cout << "Enter destination:\n";
        std::cin >> to;
        while ((getchar()) != '\n');

        while (true)
        {
            std::cout << "Enter reward:\n";
            std::cin >> reward;
            while(std::cin.fail())
            {
                std::cout << "Input needs to be a number.\n";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> reward;  
            }
            if(reward < 0)
            {
                std::cout << "Reward cannot be negative.\n";
            }
            else
                break;       
        }
        Travel travel(id, driverId, startTime, customerId, from, to, reward);
        std::cout << "Travel added!\n";
        travels.push_back(travel);
    }

    time_t MakeDate(){  
        std::string date, time;
        time_t t;
        while (true)
        {
            std::cout << "Enter date: YYYY.mm.dd\n";
            std::cin >> date;
            std::cout << "Enter time: HH:MM\n";
            std::cin >> time;
            std::string datetime = date + " " + time + ":00";
            struct std::tm tm;
            std::istringstream ss(datetime);
            ss >> std::get_time(&tm, "%Y.%m.%d %H:%M:%S");
            if(ss.fail())
            {
                std::cout << "Date was given in invalid form.\n";
                continue;
            }
            else
                t = mktime(&tm);
                return t;
        }
    }

    void PrintCustomerTravels(std::vector<Travel>& travels, int& id) const{
        std::vector<Travel> customerTravels;
        for(auto travel : travels)
        {
            if(travel.getCustomerId() == id)
            {
                customerTravels.push_back(travel);
            }
        }
        std::sort(customerTravels.begin(), customerTravels.end());
        for(auto item : customerTravels)
        {
            std::cout << item.toString();
        }
    }

    void PrintCustomerDrivers(std::vector<Travel>& travels, std::vector<Driver>& drivers, int& id) const{
        
        std::vector<int> driverIds;
        for(auto travel : travels)
        {
            if(travel.getCustomerId() == id)
            {   
                if(std::find(driverIds.begin(), driverIds.end(), travel.getDriverId()) != driverIds.end()) {
                    continue;
                } else {
                    driverIds.push_back(travel.getDriverId());
                }
                
            }
        }
        std::vector<Driver> customerDrivers;
        for(auto driver : drivers)
        {
            for(int i : driverIds)
            {
                if(driver.getId() == i)
                {
                    customerDrivers.push_back(driver);
                }
            }
        }
        std::sort(customerDrivers.begin(), customerDrivers.end());
        for(auto item : customerDrivers)
        {
            std::cout << item.toString();
        }
    }

    void PrintCustomersBetweenDates(std::vector<Travel>& travels, std::vector<Customer>& customers){
        std::cout << "Enter starting date:\n";
        time_t date1 = MakeDate();
        std::cout << "Enter ending date:\n";
        time_t date2 = MakeDate();
        std::vector<int> customerIds;

        double tdTravel;
        double td = difftime(date2, date1);
        for(auto travel : travels)
        {
            tdTravel = difftime(travel.getStartTime(), date1);
            if(tdTravel < td && tdTravel >= 0)
            {
                if(std::find(customerIds.begin(), customerIds.end(), travel.getCustomerId()) != customerIds.end()) {
                    continue;
                } else {
                    customerIds.push_back(travel.getCustomerId());
                }
            }
        }
        for(auto customer : customers)
        {
            for(int i : customerIds)
            {
                if(customer.getId() == i)
                {
                    std::cout << customer.toString();
                }
            }
        }
    }
};

#endif
