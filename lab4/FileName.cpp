#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person() : name(""), age(0) {}

    Person(string name, int age) : name(name), age(age) {}

    virtual void printInfo(ostream& out) const {
        out << "Name: " << name << ", Age: " << age;
    }

    friend istream& operator>>(istream& in, Person& person) {
        cout << "Enter name: ";
        in >> person.name;
        cout << "Enter age: ";
        in >> person.age;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Person& person) {
        person.printInfo(out);
        return out;
    }

 
    Person& operator=(const Person& other) {
        if (this != &other) {
            this->name = other.name;
            this->age = other.age;
        }
        return *this;
    }
};

class Student : public Person {
protected:
    string groupNumber;
    double averageMark;

public:
  
    Student() : Person(), groupNumber(""), averageMark(0.0) {}

    Student(string name, int age, string groupNumber, double averageMark)
        : Person(name, age), groupNumber(groupNumber), averageMark(averageMark) {}

    
    void printInfo(ostream& out) const override {
        Person::printInfo(out);
        out << ", Group: " << groupNumber << ", Average Mark: " << averageMark;
    }

    friend istream& operator>>(istream& in, Student& student) {
        in >> static_cast<Person&>(student);
        cout << "Enter group number: ";
        in >> student.groupNumber;
        cout << "Enter average mark: ";
        in >> student.averageMark;
        return in;
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            Person::operator=(other); 
            this->groupNumber = other.groupNumber;
            this->averageMark = other.averageMark;
        }
        return *this;
    }
};


class Studunt : public Student {
private:
    string diplomaTopic;

public:
    Studunt() : Student(), diplomaTopic("") {}

    Studunt(string name, int age, string groupNumber, double averageMark, string diplomaTopic)
        : Student(name, age, groupNumber, averageMark), diplomaTopic(diplomaTopic) {}

    void printInfo(ostream& out) const override {
        Student::printInfo(out);
        out << ", Diploma Topic: " << diplomaTopic;
    }

   
    friend istream& operator>>(istream& in, Studunt& gradStudent) {
        in >> static_cast<Student&>(gradStudent);
        cout << "Enter diploma topic: ";
        getline(in, gradStudent.diplomaTopic);
        return in;
    }

    Studunt& operator=(const Studunt& other) {
        if (this != &other) {
            Student::operator=(other); 
            this->diplomaTopic = other.diplomaTopic;
        }
        return *this;
    }
};


int main() {
   Studunt gradStudent;

   
    cout << "Enter information about the graduate student:\n";
    cin >> gradStudent;

   
    cout << "\nGraduate Student Info:\n";
    cout << gradStudent << endl;

    ofstream outFile("student_info.txt");
    if (outFile.is_open()) {
        outFile << gradStudent << endl;
        outFile.close();
        cout << "Information saved to student_info.txt" << endl;
    }
    else {
        cout << "Unable to open file!" << endl;
    }

    return 0;
}
