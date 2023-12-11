#define _CRT_SECURE_NO_WARNINGS
#include "med_center.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables
struct Customer* front = NULL;
struct Customer* rear = NULL;

void readInitialData() {
    FILE* file = fopen("C:\\Users\\user\\Desktop\\data.txt", "r");
    if (file == NULL) {
        printf("Error opening initial_data.txt\n");
        exit(EXIT_FAILURE);
    }

    int id = rand() % 900 + 100;
    while (!feof(file)) {
        struct Customer* newCustomer = (struct Customer*)malloc(sizeof(struct Customer));
        if (newCustomer == NULL) {
            printf("Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }

        if (fscanf(file, "%s %s", newCustomer->service, newCustomer->time) == 2) {
            newCustomer->id = rand() % 900 + 100;
            snprintf(newCustomer->name, sizeof(newCustomer->name), "Customer%d", newCustomer->id);
            newCustomer->available = 1; // Initialize as available
            newCustomer->next = NULL;

            if (rear == NULL) {
                front = newCustomer;
                rear = newCustomer;
            }
            else {
                rear->next = newCustomer;
                rear = newCustomer;
            }
        }
        else {
            free(newCustomer); // Free memory if fscanf fails
        }
    }

    fclose(file);
}

void handleCustomerQueue() {
    struct Customer* newCustomer;

    printf("Welcome to our medical centre \n \n");
    while (1) {
        printf("Available Services:\n");

        // Display only available services
        int option = 1;
        struct Customer* current = front;
        while (current != NULL) {
            if (current->available) {
                printf("%d. %s (Time: %s)\n", option++, current->service, current->time);
            }
            current = current->next;
        }

        // Check if there are no more available services
        if (option == 1) {
            printf("The queue is full. No more available services for today.\n");
            break;
        }

        printf("Enter the service number you want (or any non-positive number to exit): ");
        int serviceNumber;
        scanf("%d", &serviceNumber);

        // Check if the user wants to exit
        if (serviceNumber <= 0) {
            break;
        }

        // Validate service number
        if (serviceNumber < 1 || serviceNumber > option - 1) {
            printf("Invalid service number.\n\n");
            continue;
        }

        // Find the selected service in the available services
        int selectedServiceIndex = 1;
        current = front;
        while (current != NULL) {
            if (current->available) {
                if (selectedServiceIndex == serviceNumber) {
                    break;
                }
                selectedServiceIndex++;
            }
            current = current->next;
        }

        // Check if the service is available
        if (current != NULL && current->available) {
            // Allocate memory for the new customer
            newCustomer = (struct Customer*)malloc(sizeof(struct Customer));
            if (newCustomer == NULL) {
                printf("Memory allocation error.\n");
                exit(EXIT_FAILURE);
            }

            // Assign service and time based on user input
            newCustomer->id = current->id; // Use the same ID as the selected service
            snprintf(newCustomer->name, sizeof(newCustomer->name), "Customer%d", newCustomer->id);
            snprintf(newCustomer->service, sizeof(newCustomer->service), "%s", current->service);
            snprintf(newCustomer->time, sizeof(newCustomer->time), "%s", current->time);
            newCustomer->available = 0;
            newCustomer->next = NULL;

            // Remove the selected service by updating pointers
            if (current == front) {
                front = current->next;
            }
            else {
                struct Customer* temp = front;
                while (temp->next != current) {
                    temp = temp->next;
                }
                temp->next = current->next;
            }

            free(current); // Free memory for the removed customer

            // If it's the first customer, update rear
            if (front == NULL) {
                rear = NULL;
            }

            // Add the new customer to the end of the queue
            if (rear == NULL) {
                front = newCustomer;
                rear = newCustomer;
            }
            else {
                rear->next = newCustomer;
                rear = newCustomer;
            }

            printf("You have been added to the queue. Your ID is: %d\n \n", newCustomer->id);
        }
        else {
            printf("Selected service is not available. Please choose another service.\n \n");
        }
    }
}

// Function to record output in a text file
void recordOutput() {
    FILE* file = fopen("C:\\Users\\user\\Desktop\\output.txt", "a"); // Open in append mode
    if (file == NULL) {
        printf("Error opening managed.txt\n");
        return;
    }

    fprintf(file, "Chosen Services:\n");

    struct Customer* current = front;
    while (current != NULL) {
        if (!current->available) {
            fprintf(file, "ID: %d, Name: %s, Service: %s, Time: %s\n",
                current->id, current->name, current->service, current->time);
        }
        current = current->next;
    }

    fclose(file);
}

// Function to free allocated memory
void freeMemory() {
    struct Customer* current = front;
    struct Customer* temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}
