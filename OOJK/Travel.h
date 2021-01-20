#ifndef TRAVEL_H_INCLUDED
#define TRAVEL_H_INCLUDED

#include <iomanip>
#include <string>

class Travel {

private:
    int id;
    int driverId;
    time_t startTime;
    int customerId;
    std::string from;
    std::string to;
    double reward;

public:
    Travel(int newId, int driverId, time_t newStartTime, int newCustomerId,
            std::string newFrom, std::string newTo, double newReward);
    virtual ~Travel()=default;
    int getId() const;
    int getDriverId() const;
    int getCustomerId() const;
    time_t getStartTime() const;
    bool operator<(const Travel& tr) const; //compares dates
    std::string toString() const;
};
#endif