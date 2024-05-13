#include "UndoStack.h"
#include <iostream>
// Constructor
UndoStack::UndoStack() : top(nullptr) {}

// Destructor
UndoStack::~UndoStack() {
    clear();
}

// Push an action onto the stack
void UndoStack::push(char operation, const string& employeeName, const string& projectName, int projectPriority) {
    StackNode* newNode = new StackNode(operation, employeeName, projectName, projectPriority, top);
    top = newNode;
}

// Pop an action from the stack
bool UndoStack::pop(char& operation, std::string& employeeName, std::string& projectName, int& priority) {
    if (top == nullptr) return false; // Check for empty stack
    StackNode* nodeToRemove = top;
    top = top->next; // Move the top pointer to the next node
    // Copy data from the node to be removed
    operation = nodeToRemove->operation;
    employeeName = nodeToRemove->employee_name;
    projectName = nodeToRemove->project_name;
    priority = nodeToRemove->project_priority;

    delete nodeToRemove;
    return true;
}

// Check if the stack is empty
bool UndoStack::isEmpty() const {
    return top == nullptr;
}

// Clear the stack
void UndoStack::clear() {
    while (!isEmpty()) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}

