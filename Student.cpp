#include "Student.h"
#include <iostream>
#include <string>
using namespace std;

Student::Student(std::string name, std::string id, std::string bYear, std::string dept, std::string tel)
{
    this->name = name;
    this->student_id = id;
    this->birth_year = bYear;
    this->department = dept;
    this->tel = tel;
}

Student::~Student()
{
}

std::string Student::getName() const { return name; }
std::string Student::getStudent_id() const { return student_id; }
std::string Student::getBirth_year() const { return birth_year; }
std::string Student::getDepartment() const { return department; }
std::string Student::getTel() const { return tel; }
