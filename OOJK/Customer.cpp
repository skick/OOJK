#include "Customer.h"
#include <sstream> 


Customer::Customer(int newId, std::string newName,
                   std::string newPNumber, std::string newAddress){
    id = newId;
    name = newName;
    pNumber = newPNumber;
    address = newAddress;
}

int Customer::getId() const{
    return id;
}

std::string Customer::getName() const{
    return name;
}


Customer& Customer::operator=(const Customer &cu){
    if(this == &cu)
    {
        return *this;
    }

    id = cu.id;
    name = cu.name;
    pNumber = cu.pNumber;
    address = cu.address;
    return *this;
}

std::string Customer::toString() const {
    std::stringstream output;
    output << "ID: " << id << " | Name: " << name << " | Phonenumber: " << pNumber << " | Address: " << address << "\n";
    return output.str();
}