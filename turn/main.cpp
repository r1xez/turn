#include <iostream>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

class Passenger {
public:
    double arrivalTime;
    double serviceTime;

    Passenger(double arrival, double service) : arrivalTime(arrival), serviceTime(service) {}
};

class BusStop {
private:
    queue<Passenger> passengers;
    double busInterval;
    bool isTerminal;
    double currentTime; 

public:
    BusStop(double busInt, bool terminal)
        : busInterval(busInt), isTerminal(terminal), currentTime(0.0) {}

    void addPassenger(double arrivalTime, double serviceTime) {
        passengers.push(Passenger(arrivalTime, serviceTime));
    }

    void process(int simulationTime) {
        int peopleOnStop = 0;

        while (!passengers.empty() && currentTime < simulationTime) {
            Passenger p = passengers.front();
            passengers.pop();

           
            currentTime = p.arrivalTime;
            peopleOnStop++;

            cout << "Passenger arrived at time " << currentTime << " with service time " << p.serviceTime << " seconds.\n";

           
            currentTime += p.serviceTime;
            peopleOnStop--;

            cout << "Passenger left at time " << currentTime << ".\n";

            
            if (peopleOnStop > 0) {
                cout << "Currently " << peopleOnStop << " people on the bus stop.\n";
            }

           
            double nextBusArrival = currentTime + busInterval;
            if (nextBusArrival < simulationTime) {
                cout << "Next bus arrives at time " << nextBusArrival << ".\n";
            }
            else {
                cout << "No more buses for the day.\n";
            }
        }

        cout << "\nSimulation complete.\n";
        cout << "Total passengers served: " << passengers.size() << "\n";
        cout << "Average wait time: " << calculateAverageWaitTime() << " seconds.\n";
    }

    double calculateAverageWaitTime() {
        double totalWaitTime = 0.0;
        int count = 0;

        queue<Passenger> tempQueue = passengers;

        while (!tempQueue.empty()) {
            totalWaitTime += (currentTime - tempQueue.front().arrivalTime);
            tempQueue.pop();
            count++;
        }

        return (count > 0) ? totalWaitTime / count : 0.0; 
    }
};

int main() {
    int simulationTime = 3600;
    BusStop busStop(300, true);

    int numPassengers;
    cout << "Enter number of passengers: ";
    cin >> numPassengers;

    for (int i = 0; i < numPassengers; ++i) {
        double arrivalTime, serviceTime;

        cout << "Enter arrival time (seconds) for passenger " << i + 1 << ": ";
        cin >> arrivalTime;
        cout << "Enter service time (seconds) for passenger " << i + 1 << ": ";
        cin >> serviceTime;

        busStop.addPassenger(arrivalTime, serviceTime);
    }

    busStop.process(simulationTime);

    return 0;
}
