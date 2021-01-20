#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

#include <string>

class Customer {

private:
    int id;
    std::string name;
    std::string pNumber;
    std::string address;

public:
    Customer(int newId, std::string newName, std::string newPNumber, std::string newAddress);
    virtual ~Customer()=default;
    int getId() const;
    std::string getName() const;
    std::string toString() const;
    Customer& operator=(const Customer &dr);

};
#endif