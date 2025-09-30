#pragma once

#include <string>

class Student
{
private:                    // 맴버 변수
    std::string name;       // 15자 이하
    std::string student_id; // 10자리
    std::string birth_year; // 4자리
    std::string department;
    std::string tel; // 12자리 이하

public:
    // 생성자, 소멸자
    Student(std::string name, std::string student_id, std::string birth_year, std::string department, std::string tel);
    ~Student();

    // 메소드
    std::string getName() const;
    std::string getStudent_id() const;
    std::string getBirth_year() const;
    std::string getDepartment() const;
    std::string getTel() const;
};