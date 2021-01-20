#include "LoadInformation.h"
#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>


LoadInformation::LoadInformation(std::string agencyf, std::string customerf,
                                    std::string driverf, std::string travelf){
    files.push_back(agencyf);
    files.push_back(customerf);
    files.push_back(driverf);
    files.push_back(travelf);
}

void LoadInformation::ReadFiles(){

    int classtype = 1; // 1=agency, 2=customer, 3=driver, 4=travel
    for (auto file : files) {
        std::fstream fs;
        fs.open(file, std::ios::in);
        if (!fs) {
            std::cout << "\nError occured while opening files!\n";
            return;
        }
        else 
        {
            std::string line;
            while (std::getline(fs, line))
            {
                std::istringstream strm(line);
                switch(classtype)
                {
                    case 1:
                        LoadAgency(strm);
                        break;
                    case 2:
                        LoadCustomer(strm);
                        break;
                    case 3:
                        LoadDriver(strm);
                        break;
                    case 4:
                        LoadTravel(strm);
                        break;
                    default:
                        break;
                }
                if (fs.eof())
                    break;
            }
        }
        fs.close();
        classtype++;
    }

}

void LoadInformation::LoadAgency(std::istringstream& information){
    //2	Agency#2	2012.04.23	33	Boss#2
    int id, staffAmount;
    std::string name, date, carModel, managerName;
    information >> id >> name >> date >> staffAmount >> managerName;
    std::tm tm = MakeTimeStamp(date, 2);
    Agency agency(id, name, tm, staffAmount, managerName);
    agencies.push_back(agency);
}

void LoadInformation::LoadCustomer(std::istringstream& information){
    //4	Customer#4	+3587449640342	Sreet#4
    int id;
    std::string name, pNumber, address;
    information >> id >> name >> pNumber >> address;
    Customer customer(id, name, pNumber, address);
    customers.push_back(customer);
}

void LoadInformation::LoadDriver(std::istringstream& information){
    //5	2	Driver#5	2015.05.18	Grit Dixus
    int id, employerId;
    std::string name, date, carModel, carModel2;
    information >> id >> employerId >> name >> date >> carModel >> carModel2;
    std::tm tm = MakeTimeStamp(date, 2);
    carModel = carModel + " " + carModel2;
    Driver driver(id, employerId, name, tm, carModel);
    drivers.push_back(driver);
}

void LoadInformation::LoadTravel(std::istringstream& information){
    //8	1	2016.03.01 08:14	10	Source#8	Destination#8	0.45
    int id, driverId, customerId;
    std::string startDate, startTime, from, to;
    double reward;
    information >> id >> driverId >> startDate >> startTime >> customerId >> from >> to >> reward;
    startDate = startDate + " " + startTime;
    std::tm tm = MakeTimeStamp(startDate, 1);
    time_t date = mktime(&tm);
    Travel travel(id, driverId, date, customerId, from, to, reward);
    travels.push_back(travel);
}

std::tm LoadInformation::MakeTimeStamp(std::string time, int format){
    
    if(format == 1)
    {
        time = time + ":00";
        struct std::tm tm;
        std::istringstream ss(time);
        ss >> std::get_time(&tm, "%Y.%m.%d %H:%M:%S");
        return tm;
    }
    else
    {
        struct std::tm tm;
        std::istringstream ss(time);
        ss >> std::get_time(&tm, "%Y.%m.%d");
        return tm;
    }
    

}






std::vector<Agency>& LoadInformation::getAgencies(){
    return agencies;
}

std::vector<Customer>& LoadInformation::getCustomers(){
    return customers;
}

std::vector<Driver>& LoadInformation::getDrivers(){
    return drivers;
}

std::vector<Travel>& LoadInformation::getTravels(){
    return travels;
}