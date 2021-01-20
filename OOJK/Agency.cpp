#include "Agency.h"
#include <sstream>

Agency::Agency(int newId, std::string newName, std::tm newRegisterDate,
                int newStaffAmount, std::string newManagerName){
    id = newId;
    name = newName;
    registerDate = newRegisterDate;
    staffAmount = newStaffAmount;
    managerName = newManagerName;
}

int Agency::getId() const{
    return id;
}

std::string Agency::getName() const {
    return name;
}

Agency& Agency::operator=(const Agency &ag){
    if(this == &ag)
    {
        return *this;
    }

    id = ag.id;
    name = ag.name;
    registerDate = ag.registerDate;
    staffAmount = ag.staffAmount;
    managerName = ag.managerName;
    return *this;
}

std::string Agency::toString() const {
    
    char buffer[80];
    std::stringstream output;
    strftime(buffer, 80, "%Y-%m-%d", &registerDate);

    output << "ID: " << id << " | Name: " << name << " | Date registered: " << buffer << " | Employees: " << staffAmount << " | Manager's ID: " << managerName << "\n";
    return output.str();
}