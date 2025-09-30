#pragma once

#include "Student.h"
#include <string>
#include <vector>

// Insert Menu enum
enum Search_option
{
    SEARCH_BY_NAME = 1,
    SEARCH_BY_STUDENT_ID,
    SEARCH_BY_ADMISSION_YEAR,
    SEARCH_BY_BIRTH_YEAR,
    SEARCH_BY_DEPARTMENT_NAME,
    LIST_ALL
};

// Sort Menu enum
enum Sort_option
{
    SORT_BY_NAME = 1,
    SORT_BY_STUDENT_ID,
    SORT_BY_BIRTH_YEAR,
    SORT_BY_DEPARTMENT_NAME
};

class StudentDatabase
{

private: // 맴버 변수
    std::vector<Student> students;
    std::string file_name;
    Sort_option sort_option = SORT_BY_NAME; // default value: search by name // enum으로 바꿔서 구현함.

    // Helper 함수
    void search(std::vector<Student> &results, int choice);
    void sort(std::vector<Student> &results);
    bool isAllDigits(std::string &s); // insert시 제약 조건을 위반하는지 검사
    bool isAllEng(std::string &s);
    std::string toUpper(std::string s);

public:
    // 생성자, 소멸자
    StudentDatabase(std::string file_name);
    ~StudentDatabase();

    // 메소드
    void insertMenu();
    void searchMenu();
    void sortMenu();
    void load();
    void save();
};