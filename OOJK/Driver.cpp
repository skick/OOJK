#include "Driver.h"
#include <sstream>
#include <ctime>



Driver::Driver(int newId, int newEmployerId, std::string newName,
               std::tm newStartDate, std::string newCarModel){
    id = newId;
    employerId = newEmployerId;
    name = newName;
    startDate = newStartDate;
    carModel = newCarModel;
}

int Driver::getId() const{
    return id;
}

std::string Driver::getName() const{
    return name;
}

//Compares names
bool Driver::operator<(const Driver& dr) const{
    return (dr.getName() < this->getName());
}

Driver& Driver::operator=(const Driver &dr){
    if(this == &dr)
    {
        return *this;
    }

    id = dr.id;
    employerId = dr.employerId;
    name = dr.name;
    startDate = dr.startDate;
    carModel = dr.carModel;
    return *this;
}

std::string Driver::toString() const {
    char buffer[80];
    std::stringstream output;
    strftime(buffer, 80, "%Y-%m-%d", &startDate);

    output << "ID: " << id << " | Agency ID: " << employerId << " | Name: " << name << " | Starting date: " << buffer << " | Car model:  " << carModel << "\n";
    return output.str();
}