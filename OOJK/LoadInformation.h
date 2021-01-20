#ifndef LOADINFORMATION_H_INCLUDED
#define LOADINFORMATION_H_INCLUDED

#include <string>
#include <vector>
#include "Agency.h"
#include "Customer.h"
#include "Driver.h"
#include "Travel.h"

class LoadInformation {

private:
    std::vector<std::string> files;

    std::vector<Agency> agencies;
    std::vector<Customer> customers;   
    std::vector<Driver> drivers;   
    std::vector<Travel> travels;   


public:
    LoadInformation(std::string agencyf, std::string customerf,
                    std::string driverf, std::string travelf);
    virtual ~LoadInformation()=default;

    void ReadFiles();

    void LoadAgency(std::istringstream& information);
    void LoadCustomer(std::istringstream& information);
    void LoadDriver(std::istringstream& information);
    void LoadTravel(std::istringstream& information);

    std::tm MakeTimeStamp(std::string time, int format);

    std::vector<Agency>& getAgencies();
    std::vector<Customer>& getCustomers();
    std::vector<Driver>& getDrivers();
    std::vector<Travel>& getTravels();

};
#endif