#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <string>

using namespace std;

struct PrintRequest {
    string clientName;
    int priority;
    time_t timestamp;

    PrintRequest(string name, int prio)
        : clientName(name), priority(prio), timestamp(std::time(nullptr)) {}

    bool operator<(const PrintRequest& other) const {
        return priority < other.priority;
    }
};


void printStats(const vector<PrintRequest>& printLog) {
    cout << "Printing Statistics:" << endl;
    for (const auto& req : printLog) {
        cout << "Client: " << req.clientName
            << ", Priority: " << req.priority
            << ", Timestamp: " << std::ctime(&req.timestamp);
    }
}

int main() {
    priority_queue<PrintRequest> printQueue;
    vector<PrintRequest> printLog;

  
    printQueue.push(PrintRequest("Client1", 2));
    printQueue.push(PrintRequest("Client2", 1));
    printQueue.push(PrintRequest("Client3", 3));

    // ƒрукуЇмо запити в черз≥
    while (!printQueue.empty()) {
        PrintRequest currentRequest = printQueue.top();
        printQueue.pop();

       
        printLog.push_back(currentRequest);

        cout << "Printing request from " << currentRequest.clientName
            << " with priority " << currentRequest.priority
            << " at " << std::ctime(&currentRequest.timestamp);
    }

    
    printStats(printLog);

    return 0;
}
