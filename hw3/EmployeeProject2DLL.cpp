#include "EmployeeProject2DLL.h"
#include "UndoStack.h"
#include <string>
#include <iostream>
using namespace std;
// Constructor
EmployeeProject2DLL::EmployeeProject2DLL() : head(nullptr) {}

// Destructor
EmployeeProject2DLL::~EmployeeProject2DLL() {
    clear();
}

// Clear memory
void EmployeeProject2DLL::clear() {
    while (head != nullptr) {
        EmployeeNode* tempEmp = head;
        head = head->down;
        ProjectNode* tempProj = tempEmp->head;
        while (tempProj != nullptr) {
            ProjectNode* nextProj = tempProj->next;
            delete tempProj;
            tempProj = nextProj;
        }
        delete tempEmp;
    }
}


bool EmployeeProject2DLL::isEmployeeAssignedToProject(const string& employeeName, const string& projectName) {
    EmployeeNode* currentEmployee = head;
    while (currentEmployee != nullptr) {
        if (currentEmployee->employee_name == employeeName) {
            ProjectNode* currentProject = currentEmployee->head;
            while (currentProject != nullptr) {
                if (currentProject->project_name == projectName) {
                    return true; // Employee is assigned to the project
                }
                currentProject = currentProject->next;
            }
            return false; // Employee found but project not found
        }
        currentEmployee = currentEmployee->down;
    }
    return false; // Employee not found
}

bool EmployeeProject2DLL::updateProjectPriority(const string& employeeName, const string& projectName, int& priority) {
    EmployeeNode* currentEmployee = head;
    while (currentEmployee != nullptr) {
        if (currentEmployee->employee_name == employeeName) {
            ProjectNode* currentProject = currentEmployee->head;
            while (currentProject != nullptr) {
                if (currentProject->project_name == projectName) {
                    if (currentProject->project_priority == priority) {
                        return false; // Priority is the same as the new priority
                    }
                    // Check for duplicate priority among other projects
                    ProjectNode* otherProject = currentEmployee->head;
                    while (otherProject != nullptr) {
                        if (otherProject != currentProject && otherProject->project_priority == priority) {
                            return false; // Another project with the same priority found
                        }
                        otherProject = otherProject->next;
                    }
                    // No duplicates found, update priority
                    currentProject->project_priority = priority;
                    // Additional steps might be needed to reorder the projects based on the new priority
                    return true;
                }
                currentProject = currentProject->next;
            }
            return false; // Project not found for employee
        }
        currentEmployee = currentEmployee->down;
    }
    return false; // Employee not found
}
bool EmployeeProject2DLL::assignEmployeeToProject(const string& employeeName, const string& projectName, int priority) {
    EmployeeNode* currentEmployee = head;
    EmployeeNode* lastEmployee = nullptr;
    bool employeeExists = false;

    // Search for the employee
    while (currentEmployee != nullptr) {
        if (currentEmployee->employee_name == employeeName) {
            employeeExists = true;
            break;
        }
        lastEmployee = currentEmployee;
        currentEmployee = currentEmployee->down;
    }

    if (!employeeExists) {
        // Create a new employee node if not found
        currentEmployee = new EmployeeNode(employeeName);
        if (lastEmployee == nullptr) { // First employee in the list
            head = currentEmployee;
        } else {
            lastEmployee->down = currentEmployee;
        }
    }

    // At this point, currentEmployee points to the employee where we want to insert the project
    ProjectNode* newProject = new ProjectNode(projectName, priority, nullptr, nullptr);

    // Insert the new project in the correct position
    // Check if the employee has no projects or if the new project's priority is lower than the first project's priority
    if (currentEmployee->head == nullptr || priority < currentEmployee->head->project_priority) {
        newProject->next = currentEmployee->head;
        currentEmployee->head = newProject;
    } else {
        // Find the correct position for the new project
        ProjectNode* prevProject = nullptr;
        ProjectNode* currentProject = currentEmployee->head;
        while (currentProject != nullptr && currentProject->project_priority <= priority) {
            prevProject = currentProject;
            currentProject = currentProject->next;
        }

        // Insert the new project
        newProject->next = prevProject->next;
        prevProject->next = newProject;
    }

    return true;
}


void EmployeeProject2DLL::withdrawEmployeeFromProject(const string& employeeName, const string& projectName, int& priority) {
    EmployeeNode *currentEmployee = head;
    EmployeeNode *prevEmployee = nullptr;
    while (currentEmployee != nullptr) {
        if (currentEmployee->employee_name == employeeName) {
            ProjectNode *currentProject = currentEmployee->head;
            ProjectNode *prevProject = nullptr;
            while (currentProject != nullptr) {
                if (currentProject->project_name == projectName) {
                    priority = currentProject->project_priority;
                    if (prevProject == nullptr) { // First project in the list
                        currentEmployee->head = currentProject->next;
                    } else {
                        prevProject->next = currentProject->next;
                    }
                    if (currentProject->next == nullptr) { // Last project, update tail
                        currentEmployee->tail = prevProject;
                    }
                    delete currentProject;
                    if (currentEmployee->head == nullptr) { // No more projects, remove employee
                        if (prevEmployee == nullptr) {
                            head = currentEmployee->down;
                        } else {
                            prevEmployee->down = currentEmployee->down;
                        }
                        delete currentEmployee;
                    }
                    return;
                }
                prevProject = currentProject;
                currentProject = currentProject->next;
            }
        }
        prevEmployee = currentEmployee;
        currentEmployee = currentEmployee->down;


    }
}

void EmployeeProject2DLL::undo(char operation, const string& employeeName, const string& projectName, int priority) {
    // Display a message based on the operation type
    switch (operation) {
        case 'a': // Undoing the assignment of a project
            cout << "Undoing the assignment of a project." << endl;
            // Logic to remove the project assuming it was the last action for this employee
            withdrawEmployeeFromProject(employeeName, projectName,priority);
            return;
        case 'w': // Undoing the withdrawal of a project
            cout << "Undoing the withdrawal of a project." << endl;
            // Logic to re-assign the project assuming it was removed last for this employee
            assignEmployeeToProject(employeeName, projectName, priority);
            return;
        case 'u': // Undoing the update of a project priority
            cout << "Undoing the update of a project priority." << endl;
            // Logic to revert the project priority change
            // This might require storing previous priority values somewhere if not currently handled
            updateProjectPriority(employeeName, projectName, priority);
            return;
        default:
            cout << "Unknown operation. Cannot undo." << endl;
            return;
    }
}

#include <algorithm>

void EmployeeProject2DLL::printTheEntireList() const {
    if (!head) {
        cout << "The list is empty." << endl;
        return;
    }

    const EmployeeNode* emp = head;
    while (emp != nullptr) {
        cout << emp->employee_name << ": ";

        const ProjectNode* startProject = nullptr; // Start with no project (to find the first alphabetically)
        while (true) {
            const ProjectNode* nextProject = nullptr;
            string nextProjectName; // Initialize with an empty string to ensure comparison starts with the first project name

            // Find the alphabetically next project to print
            for (const ProjectNode* proj = emp->head; proj != nullptr; proj = proj->next) {
                if ((startProject == nullptr || proj->project_name > startProject->project_name) && // Project is after the current "startProject"
                    (nextProject == nullptr || proj->project_name < nextProjectName)) { // and is the next alphabetically
                    nextProject = proj;
                    nextProjectName = proj->project_name;
                }
            }

            // Break the loop if no next project is found, meaning we have printed all for this employee
            if (nextProject == nullptr) break;

            // Print the found project
            cout << "(" << nextProject->project_name << ", " << nextProject->project_priority << ") ";

            // Set this project as the new "startProject" for the next iteration to find the next one
            startProject = nextProject;
        }

        cout << endl;
        emp = emp->down; // Move to the next employee
    }
}



// Assuming the EmployeeNode and other class declarations remain the same
// Recursive helper function for printing projects in reverse
void printProjectsInReverse(const ProjectNode* node) {
    if (node == nullptr) return; // Base case
    printProjectsInReverse(node->next); // Recursive call
    cout << "(" << node->project_name << " " << node->project_priority << ") "; // Process current node
}

void EmployeeProject2DLL::printEmployeeProjects(const string& employeeName, bool ascending) const {
    // Check if the list is empty first
    if (head == nullptr) {
        cout << "There are no employees in the list." << endl;
        return;
    }

    const EmployeeNode* emp = head;
    bool found = false;

    // Search for the employee
    while (emp != nullptr) {
        if (emp->employee_name == employeeName) {
            found = true;
            break;
        }
        emp = emp->down;
    }

    // If employee is not found
    if (!found) {
        cout << "The employee is not in the list." << endl;
        return;
    }

    // If found but no projects assigned
    if (emp->head == nullptr) {
        cout << employeeName << " has no projects assigned." << endl;
        return;
    }

    // Found the employee and they have projects, now print their projects


    if (ascending) {
        // For ascending order, just iterate normally through the projects
        const ProjectNode* proj = emp->head;
        while (proj != nullptr) {
            cout << "(" << proj->project_name << ", " << proj->project_priority << ")";
            if (proj->next != nullptr) {
                cout << " "; // Add space between projects if there is a next project
            }
            proj = proj->next;
        }
    } else {
        // For descending order, you could use recursion or collect the projects first and then print in reverse
        // Here is a simple recursive approach for printing in reverse
        printProjectsInReverse(emp->head);
    }

    cout << endl;
}


// Helper recursive function to print projects in reverse (for descending order)
void EmployeeProject2DLL::printProjectsInReverse(const ProjectNode* node) const {
    if (node == nullptr) return; // Base case: reached the end of the project list
    printProjectsInReverse(node->next); // Recursive call to process the next project first
    cout << "(" << node->project_name << ", " << node->project_priority << ") "; // Process the current node after the recursive call
}




