#ifndef MED_CENTER_H
#define MED_CENTER_H

#define MAX_NAME_LENGTH 50
#define MAX_SERVICE_LENGTH 50
#define MAX_TIME_LENGTH 50

struct Customer {
    int id;
    char name[MAX_NAME_LENGTH];
    char service[MAX_SERVICE_LENGTH];
    char time[MAX_TIME_LENGTH];
    int available;
    struct Customer* next;
};

void readInitialData();
void handleCustomerQueue();
void recordOutput();
void freeMemory();

#endif // MEDICAL_CENTER_H
