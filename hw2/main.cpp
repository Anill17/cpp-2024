// anil sumer topaloglu 22589
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


struct NodeLike {
    string subject;
    string object;
    NodeLike *next;

    // Constructor
    NodeLike(string sub, string obj, NodeLike *nxt = nullptr)
            : subject(sub), object(obj), next(nxt) {}
};


struct NodeTaken {
    string name;
    NodeTaken *next;

    // Constructor
    NodeTaken(string nm, NodeTaken *nxt = nullptr)
            : name(nm), next(nxt) {}
};

void linked_list_printer( NodeLike * head){
    cout << "Likes list: ";
    NodeLike * current = head;
    while (current != nullptr){
        cout << "(" << current -> subject << ", " << current -> object << ") ";
        current = current -> next;
    }
    cout << endl;
}
void taken_list_printer( NodeTaken * head){
    cout << "Taken list: ";
    NodeTaken * current = head;
    while (current != nullptr){
        cout << current -> name;
        cout << " ";
        current = current -> next;
    }
    cout << endl;
}


NodeLike *headLikes = nullptr;
NodeTaken* headTaken = nullptr;



void addToLikesList(NodeLike* &head, const string& subject, const string& object) {
    NodeLike *traverser = head;
    NodeLike *previous_traverser = traverser;

    while (traverser && traverser->subject != subject) {
        previous_traverser = traverser;
        traverser = traverser->next;

    }
    if (!head) {
        //empty head
        head = new NodeLike(subject, object, nullptr);
    } else if (!traverser) {
        // no matching subject add to end
        previous_traverser->next = new NodeLike(subject, object, nullptr);
    } else {
        //traverser on same subject name
        while (traverser && traverser->subject == subject) {
            previous_traverser = traverser;
            traverser = traverser->next;
        }
        previous_traverser->next = new NodeLike(subject, object, traverser);
    }
}
void addToTakenList(NodeTaken* &head, const string& name) {
    NodeTaken* traverser=head;
    NodeTaken* prev_traverser=traverser;
    while(traverser && traverser->name < name){
        prev_traverser=traverser;
        traverser=traverser->next;
    }
    if(!traverser && !prev_traverser){
        head=new NodeTaken(name);
    }else if(!traverser && prev_traverser){
        prev_traverser->next=new NodeTaken(name);
    }else if(traverser && prev_traverser && traverser!=prev_traverser){
        prev_traverser->next=new NodeTaken(name,traverser);
    }else{
        NodeTaken* oldHead=head;
        head=new NodeTaken(name,oldHead);
    }
}



bool in_liked_list(NodeLike* head, string& subject, string& object){
    NodeLike* current = head;
    while (current != nullptr){

        if (current->subject == subject && current->object == object){
            return true;
        }
        current = current->next;
    }
    return false;
}

bool in_taken_list(NodeTaken* head,  string & name) {
    NodeTaken* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            return true; // Name found in the taken list
        }
        current = current->next;
    }
    return false; // Name not found in the taken list
}

bool delete_node_subject(NodeLike** head,  string & person) {
    NodeLike *temp = *head, *prev = nullptr;

    // If the matching pair is the first (head) node
    if (temp != nullptr && temp->subject == person) {
        *head = temp->next; // Changed head
        delete temp; // free old head
        return true;
    }

    //search the linked list
    while (temp != nullptr && !(temp->subject == person )) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == nullptr){
        return false;
    }

    // link prev and the one after temp to link the list
    prev->next = temp->next;

    delete temp; // deleting the matching pair from linked list
    return true;
}

bool delete_node_object(NodeLike** head,  string & person) {
    NodeLike *temp = *head, *prev = nullptr;

    // If the matching pair is the first (head) node
    if (temp != nullptr && temp->object == person) {
        *head = temp->next; // Changed head
        delete temp; // free old head
        return true;
    }

    //search the linked list
    while (temp != nullptr && !(temp->object == person )) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == nullptr){
        return false;
    }

    // link prev and the one after temp to link the list
    prev->next = temp->next;

    delete temp; // deleting the matching pair from linked list
    return true;
}
void deleteAllLikes(NodeLike** head) {
    while (*head != nullptr) {
        NodeLike* temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}
void deleteAllTaken(NodeTaken** head) {
    while (*head != nullptr) {
        NodeTaken* temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}



int main() {
    string file_name;
    ifstream file;
    cout << "Please enter the file name: " << endl;
    cin >> file_name;
    file.open(file_name);

    // to check the input txt file is valid.
    while (!file.is_open())
    {
        cout << "Could not open the file. Please enter a valid file name: " << endl;
        cin.clear();
        cin >> file_name;
        file.open(file_name);
    }
    // likes goes to dummy from ss
    string line, subject, object, dummy;
    int ct = 1;
    while (getline(file, line))
    {   if (ct > 1) {
            cout << endl;
        }
        cout << "Read line number (" << ct << ")" << ": " << line << endl;
        ct++;
        stringstream ss(line);
        ss >> subject >> dummy >> object;
        // I twisted the subject object order to find matching pair.
        if (in_taken_list(headTaken,subject)){
            cout << "Either " << subject <<  " or "<< object << " or both is/are already taken, so the like relation is not added." << endl;
            linked_list_printer(headLikes);
            taken_list_printer(headTaken);
        }
        else if (in_taken_list(headTaken,object)){
            cout << "Either " << subject <<  " or "<< object << " or both is/are already taken, so the like relation is not added." << endl;
            linked_list_printer(headLikes);
            taken_list_printer(headTaken);
        }
        else if (in_liked_list(headLikes,object,subject)){
            cout << "Match found: " << subject << " likes " << object << " and " << object << " likes " << subject << "."<< endl;
            bool flag1 = delete_node_subject(&headLikes, subject);
            bool flag2 = delete_node_object(&headLikes, subject);
            bool flag3 = delete_node_object(&headLikes, object);
            bool flag4 = delete_node_subject(&headLikes, object);
            while(flag1){
                flag1 = delete_node_subject(&headLikes, subject);

            };
            while(flag2){
                flag2 = delete_node_object(&headLikes, subject);

            };while(flag3){
                flag3 = delete_node_object(&headLikes, object);

            };
            while(flag4){
                flag4 = delete_node_subject(&headLikes, object);

            };

            cout << "Added to taken list: " << subject << endl;
            cout << "Added to taken list: " << object << endl;
            cout << "Any node that has "<<  subject << " or " << object << " or both in it is removed from the likes list." << endl;

            addToTakenList(headTaken,subject);
            addToTakenList(headTaken,object);

            linked_list_printer(headLikes);
            taken_list_printer(headTaken);

        }
        else if (!(in_liked_list(headLikes,subject,object))){
            addToLikesList(headLikes, subject, object);
            cout << line << " relation has been added to the likes list." << endl;
            linked_list_printer(headLikes);
            taken_list_printer(headTaken);
        }
        else{
            cout << subject << " likes " << object << " relation already exists in the likes list, so it is not added to it." << endl;
            linked_list_printer(headLikes);
            taken_list_printer(headTaken);
        }
    }


    deleteAllLikes(&headLikes);
    deleteAllTaken(&headTaken);
    cout << endl << "Lists are deleted and the program ends successfully." << endl;
    return 0;
}
