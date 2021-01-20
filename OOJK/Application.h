#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <vector>
#include "Agency.h"
#include "Customer.h"
#include "Driver.h"
#include "Travel.h"
#include "DataUtilities.h"

class Application {

private:
    std::vector<Agency> agencies;
    std::vector<Customer> customers;   
    std::vector<Driver> drivers;   
    std::vector<Travel> travels;
    DataUtilities du; 
public:
    void Run();
    void Setup();
    void Load(std::string file);

    template<class T>
    T FindItem(std::vector<T>& group);

    void TravelOperations();
    void CustomerOperations();
    void WaitInput();

};
#endif