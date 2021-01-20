#ifndef DRIVER_H_INCLUDED
#define DRIVER_H_INCLUDED

#include <string>
#include <iomanip>

class Driver {

private:
    int id;
    int employerId;
    std::string name;
    std::tm startDate;
    std::string carModel;

public:
    Driver(int newId, int newEmployerId, std::string newName,
            std::tm newStartDate, std::string newCarModel);
    virtual ~Driver()=default;
    int getId() const;
    std::string getName() const;
    std::string toString() const;
    bool operator<(const Driver& dr) const;
    Driver& operator=(const Driver &dr);

};
#endif