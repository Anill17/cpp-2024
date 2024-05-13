#ifndef EMPLOYEEPROJECT2DLL_H
#define EMPLOYEEPROJECT2DLL_H

#include <string>

using namespace std;

struct ProjectNode {
    string project_name;
    int project_priority;
    ProjectNode *next;
    ProjectNode *prev;
    ProjectNode(string name = "", int priority = 0, ProjectNode *nxt = nullptr, ProjectNode *previous = nullptr)
            : project_name(name), project_priority(priority), next(nxt), prev(previous) {}
};

struct EmployeeNode {
    string employee_name;
    ProjectNode *head;
    ProjectNode *tail;
    EmployeeNode *down;
    EmployeeNode(std::string name) : employee_name(name), down(nullptr), head(nullptr) {}
};

class EmployeeProject2DLL {
public:
    EmployeeProject2DLL();
    ~EmployeeProject2DLL();
    bool isEmployeeAssignedToProject(const string& employeeName, const string& projectName);
    bool updateProjectPriority(const string& employeeName, const string& projectName, int& priority);
    bool assignEmployeeToProject(const string& employeeName, const string& projectName, int priority);
    void withdrawEmployeeFromProject(const string& employeeName, const string& projectName, int& priority);
    void printTheEntireList() const;
    void printEmployeeProjects(const string& employeeName, bool ascending) const;
    void undo(char operation, const string& employeeName, const string& projectName, int priority);

    void clear();

private:
    EmployeeNode *head;
    void printProjectsInReverse(const ProjectNode* node) const;

    // Additional private helper functions can be declared here
};




#endif // EMPLOYEEPROJECT2DLL_H
