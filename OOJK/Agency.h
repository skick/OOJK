#ifndef AGENCY_H_INCLUDED
#define AGENCY_H_INCLUDED

#include <string>
#include <iomanip>
#include <ctime>

class Agency {

private:
    int id;
    std::string name;
    std::tm registerDate;
    int staffAmount;
    std::string managerName;

public:
    Agency(int newId, std::string newName, std::tm newRegisterDate,
            int newStaffAmount, std::string newManagerName);
    virtual ~Agency()=default;
    int getId() const;
    std::string getName() const;
    std::string toString() const;
    Agency& operator=(const Agency &dr);

};
#endif