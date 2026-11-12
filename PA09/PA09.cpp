#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>

using namespace std;

struct Person {
    string firstName;
    string lastName;
    string email;
};

//read the whole file into one string returns "" if the file doesnt exist
string readFile(const string &fileName) {
    ifstream in(fileName);
    if (!in.is_open()) {
        return "";
    }
    stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

//turn the JSON array in the file into a std::queue of Person
queue<Person> loadQueue(const string &fileName) {
    queue<Person> people;
    string data = readFile(fileName);
    if (data.empty()) {
        return people;
    }

    json::JSON obj = json::JSON::Load(data);
    if (obj.JSONType() != json::JSON::Class::Array) {
        return people; //"null" or anything else means an empty queue
    }

    for (auto &entry : obj.ArrayRange()) {
        Person p;
        p.firstName = entry["firstName"].ToString();
        p.lastName = entry["lastName"].ToString();
        p.email = entry["email"].ToString();
        people.push(p);
    }
    return people;
}

//write the queue back to the file an empty queue is written as null
void saveQueue(const string &fileName, queue<Person> people) {
    ofstream out(fileName);
    if (people.empty()) {
        out << "null" << endl;
        return;
    }

    json::JSON arr = json::Array();
    while (!people.empty()) {
        Person p = people.front();
        people.pop();

        json::JSON entry;
        entry["firstName"] = p.firstName;
        entry["lastName"] = p.lastName;
        entry["email"] = p.email;
        arr.append(entry);
    }
    out << arr << endl;
}

//check every person in the queue for a matching email
bool emailInQueue(queue<Person> people, const string &email) {
    while (!people.empty()) {
        if (people.front().email == email) {
            return true;
        }
        people.pop();
    }
    return false;
}

void printUsage() {
    cout << "Usage: ./PA09 <filename> <command> [<args>]" << endl;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printUsage();
        return 1;
    }

    string fileName = argv[1];
    string command = argv[2];
    queue<Person> people = loadQueue(fileName);

    if (command == "add") {
        if (argc != 6) {
            printUsage();
            return 1;
        }
        Person p;
        p.firstName = argv[3];
        p.lastName = argv[4];
        p.email = argv[5];

        if (emailInQueue(people, p.email)) {
            cout << "Person already in queue" << endl;
        } else {
            people.push(p);
        }
    } else if (command == "remove") {
        if (!people.empty()) {
            people.pop();
        }
    } else if (command == "clear") {
        while (!people.empty()) {
            people.pop();
        }
    } else {
        printUsage();
        return 1;
    }

    saveQueue(fileName, people);
    return 0;
}


