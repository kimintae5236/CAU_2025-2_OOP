#include "StudentDatabase.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>   // setw() 사용 -> 출력 포멧 정하기 위해 사용함
#include <algorithm> // sort() 사용 // 어려움
#include <cctype>    // toLower() 사용

StudentDatabase::StudentDatabase(std::string file_name) // 생성자
{
    this->file_name = file_name; // this: 현재 인스턴스의 주소를 가리키는 역할 따라서 -> 로 접근
    load();
}

StudentDatabase::~StudentDatabase() // 소멸자 -> 동적 할당된 메모리 해제하거나 파일 닫기할때 사용 // 여기선 구현 안해도 될듯?
{
}

void StudentDatabase::load() // 파일 열기
{
    std::ifstream myfile(this->file_name);

    if (myfile.is_open())
    {

        std::string line;
        while (std::getline(myfile, line)) // 한 문장씩 파싱하기
        {
            std::stringstream ss(line);
            std::string name, id, bYear, dept, tel;
            if (std::getline(ss, name, ':') && std::getline(ss, id, ':') && std::getline(ss, bYear, ':') && std::getline(ss, dept, ':') && std::getline(ss, tel, ':'))
            {
                students.emplace_back(name, id, bYear, dept, tel); // emplace_back함수로 student 객체를 만들고 이를 students 벡터에 자동으로 추가해줌
            }
        }
    }
    else
    {
        std::cout << "Unable to open file " << file_name;
        return;
    }

    myfile.close(); // 파일 닫기
}

void StudentDatabase::save()
{
    std::ofstream myfile(this->file_name);

    if (myfile.is_open())
    {

        for (int i = 0; i < students.size(); i++)
        {
            myfile << students[i].getName() << ":"
                   << students[i].getStudent_id() << ":"
                   << students[i].getBirth_year() << ":"
                   << students[i].getDepartment() << ":"
                   << students[i].getTel() << std::endl;
        }

        myfile.close();
    }
    else
    {
        std::cout << "Unable to save file " << file_name;
        return;
    }
}

bool StudentDatabase::isAllDigits(std::string &s)
{
    if (s.empty()) // 비어 있는 경우
    {
        return false;
    }
    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];

        if (c < '0' || c > '9') // 0~9 숫자가 아닌 경우 false 반환
        {
            return false;
        }
    }
    return true;
}
bool StudentDatabase::isAllEng(std::string &s)
{
    if (s.empty()) // 비어 있는 경우
    {
        return false;
    }
    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];

        if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) // 영어 문자가 아니면 false
        {
            return false;
        }
    }
    return true;
}

std::string StudentDatabase::toUpper(std::string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        s[i] = std::toupper(c);
    }
    return s;
}

void StudentDatabase::insertMenu() // Insertion // 제약조건을 추가해야됨
{
    std::string name, id, bYear, dept, tel;

    // 제약 조건에 위반하는 경우에 무한루프 즉시 탈출 -> 좀 더 효율적임
    while (true)
    {
        std::cout << "Name ? ";
        std::getline(std::cin, name);                                                            // cin -> name 하면 공백 앞에 문자가 입력받아서 문제가 생김 ex) a b 입력받으면 a만 name에 할당되고 버퍼에는 b\n가 남음.
        std::cin.ignore();                                                                       // 버퍼 지우기
        if (name.find(' ') != std::string::npos || name.length() > 15 || isAllEng(name) != true) // npos -> no position 찾을 수 없다는 의미(int 큰 숫자)
        {                                                                                        // 공백이 있거나 15자가 넘어가는 경우 또는 영어가 아닌 문자가 입력된 경우

            std::cout << "The name must be 15 English characters or less and cannot contain spaces." << std::endl;
            continue;
        }

        break;
    }
    while (true)
    {
        bool isExistingStudent = false;
        std::cout << "Student ID (10 digits) ? ";
        std::getline(std::cin, id);
        if (!isAllDigits(id) || id.length() != 10)
        { // 모두 숫자가 아니거나 10자가 아닌경우
            std::cout << "Student ID must be exactly 10 digits." << std::endl;
            continue;
        }
        for (int i = 0; i < students.size(); i++) // 이미 존재하는 학생인지 확인
        {
            if (students[i].getStudent_id() == id)
            {

                isExistingStudent = true;
                break;
            }
        }
        if (isExistingStudent) // 이미 존재하는 학생인 경우
        {
            std::cout << "Error : Already inserted" << std::endl;
            continue;
        }

        break;
    }

    while (true)
    {
        std::cout << "Birth Year (4 digits) ? ";
        std::getline(std::cin, bYear);
        if (!isAllDigits(bYear) || bYear.length() != 4)
        { // 모두 숫자가 아니거나 4자가 아닌경우
            std::cout << "Birth Year must be exactly 4 digits." << std::endl;
            continue;
        }

        break;
    }

    std::cout << "Department ? ";
    std::cin >> dept;

    while (true)
    {
        std::cout << "Tel ? ";
        std::getline(std::cin, tel);
        if (!isAllDigits(tel) || tel.length() > 12)
        {
            std::cout << "Tel must be 12 digits or less." << std::endl; // 모두 숫자가 아니거나 12자가 넘어가는 경우
            continue;
        }

        break;
    }
    // 모든 제약 조건을 통과하고 나서 객체 추가 해줌.
    students.emplace_back(name, id, bYear, dept, tel); // emplace_back함수로 student 객체를 만들고 이를 students 벡터에 자동으로 추가해줌
}

void StudentDatabase::searchMenu() // Search
{
    int choice; // 선택한 숫자

    std::vector<Student> results; // 선택한 case에 해당하는 결과를 results에 모으고 이를 출력함. -> 코드가 덜 복잡해짐

    while (true)
    {

        std::cout << "\n- Search -" << std::endl;
        std::cout << "1. Search by name" << std::endl;
        std::cout << "2. Search by student ID (10 digits)" << std::endl;
        std::cout << "3. Search by admission year (4 digits)" << std::endl;
        std::cout << "4. Search by birth year (4 digits)" << std::endl;
        std::cout << "5. Search by department name" << std::endl;
        std::cout << "6. List All" << std::endl;
        std::cout << "> ";

        std::cin >> choice;

        search(results, choice);
        sort(results);

        std::cout << std::left; // 왼쪽 정렬로 출력하기

        if (results.size() == 0)
        {
            std::cout << "No matching students found. " << std::endl;
            break;
        }
        std::cout << std::setw(16) << "\nName" << "| ";
        std::cout << std::setw(11) << "Student ID" << "| ";
        std::cout << std::setw(30) << "Dept" << "| ";
        std::cout << std::setw(11) << "Birth Year" << "| ";
        std::cout << std::setw(13) << "Tel" << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < results.size(); i++)
        {
            std::cout << std::setw(16) << results[i].getName() << "| ";
            std::cout << std::setw(11) << results[i].getStudent_id() << "| ";
            std::cout << std::setw(30) << results[i].getDepartment() << "| ";
            std::cout << std::setw(11) << results[i].getBirth_year() << "| ";
            std::cout << std::setw(13) << results[i].getTel() << std::endl;
        }
        break;
    }
}

void StudentDatabase::search(std::vector<Student> &results, int choice)
{
    std::string name, id, aYear, bYear, dept;

    switch (choice)
    {
    case SEARCH_BY_NAME:
        std::cout << "Name keyword? ";
        std::cin >> name;
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getName().find(name) != std::string::npos) // 키워드를 발견한 경우
            {
                results.push_back(students[i]);
            }
        }
        break;
    case SEARCH_BY_STUDENT_ID:
        std::cout << "Student ID keyword? ";
        std::cin >> id;
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getStudent_id().find(id) != std::string::npos) // 키워드를 발견한 경우
            {
                results.push_back(students[i]);
            }
        }
        break;
    case SEARCH_BY_ADMISSION_YEAR:
        std::cout << "Admssion year keyword? ";
        std::cin >> aYear;
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getStudent_id().substr(0, 4).find(aYear) != std::string::npos) // 키워드를 발견한 경우
            {
                results.push_back(students[i]);
            }
        }
        break;
    case SEARCH_BY_BIRTH_YEAR:
        std::cout << "Birth year keyword? ";
        std::cin >> bYear;
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getBirth_year().find(bYear) != std::string::npos) // 키워드를 발견한 경우
            {
                results.push_back(students[i]);
            }
        }
        break;
    case SEARCH_BY_DEPARTMENT_NAME:
        std::cout << "Department name keyword? ";
        std::cin >> dept;
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getDepartment().find(dept) != std::string::npos) // 키워드를 발견한 경우
            {
                results.push_back(students[i]);
            }
        }
        break;
    case LIST_ALL: // 모든 학생들의 리스트를 보여줌.
        for (int i = 0; i < students.size(); i++)
        {
            results.push_back(students[i]);
        }
        break;
    default:
        std::cout << "Enter a number between 1 and 6." << std::endl;
        break;
    }
}

void StudentDatabase::sort(std::vector<Student> &results)
{
    std::sort(results.begin(), results.end(), [this](const Student &a, const Student &b) { // 정렬
        switch (this->sort_option)
        {
        case SORT_BY_NAME: // 이름순 정렬 (알파벳 순서로)
            return StudentDatabase::toUpper(a.getName()) < StudentDatabase::toUpper(b.getName());

        case SORT_BY_STUDENT_ID: // 학번순 정렬 (숫자 크기 순서로)
            return std::stoll(a.getStudent_id()) < std::stoll(b.getStudent_id());

        case SORT_BY_BIRTH_YEAR: // 생년순 정렬 (숫자 크기 순서로)
            return std::stoi(a.getBirth_year()) < std::stoi(b.getBirth_year());
        case SORT_BY_DEPARTMENT_NAME: // 학과순 정렬 (알파벳 순서로)
            return StudentDatabase::toUpper(a.getDepartment()) < StudentDatabase::toUpper(b.getDepartment());
        default:
            return a.getName() < b.getName(); // 예외인 경우는 존재X
        }
    });
}

// 정렬을 언제 할지 고민 좀 해야될듯?
void StudentDatabase::sortMenu() // Sorting Option
{
    int choice; // 선택한 숫자

    while (true)
    {

        std::cout << "\n- Sorting Option -" << std::endl;
        std::cout << "1. Sort by name" << std::endl;
        std::cout << "2. Sort by student ID" << std::endl;
        std::cout << "3. Sort by birth year" << std::endl;
        std::cout << "4. Sort by department name" << std::endl;
        std::cout << "> ";

        std::cin >> choice;

        if (choice >= SORT_BY_NAME && choice <= SORT_BY_DEPARTMENT_NAME)
        {
            sort_option = (Sort_option)choice;
            break;
        }
        else
        {
            std::cout << "Enter a number between 1 and 4." << std::endl;
        }
    }
}
