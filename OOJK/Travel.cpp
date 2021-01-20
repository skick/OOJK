#include "Travel.h"
#include <sstream>
#include <iomanip>

#pragma warning(disable : 4996)


Travel::Travel(int newId, int newDriverId, time_t newStartTime, int newCustomerId,
               std::string newFrom, std::string newTo, double newReward){
    id = newId;
    driverId = newDriverId;
    startTime = newStartTime;
    customerId = newCustomerId;
    from = newFrom;
    to = newTo;
    reward = newReward;
}

int Travel::getId() const{
    return id;
}

int Travel::getCustomerId() const{
    return customerId;
}

int Travel::getDriverId() const{
    return driverId;
}

time_t Travel::getStartTime() const{
    return startTime;
}

//Compares dates
bool Travel::operator<(const Travel& tr) const{
    return (0 > difftime(tr.getStartTime(), this->getStartTime()));
}

std::string Travel::toString() const {
    std::stringstream output;
    std::string time = ctime(&startTime);
    time = time.substr(0, time.length() - 1); //substracts '\n' from the end
    output << "ID: " << id << " | Driver's ID: " << driverId << " | Starting time: " << time << " | Customers ID: " << customerId << " | From: " << from << " | To: " << to << " | Reward: " << reward << "\n";
    return output.str();
}