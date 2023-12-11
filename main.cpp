#include "med_center.h"

int main() {
    // Read initial data from the text file
    readInitialData();

    // Handle customer queue
    handleCustomerQueue();

    // Record output data in a text file
    recordOutput();

    // Free allocated memory
    freeMemory();

    return 0;
}
