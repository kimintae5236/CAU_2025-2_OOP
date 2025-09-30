#include "StudentDatabase.h"
#include <iostream>
#include <string>
using namespace std;

void run(StudentDatabase &db);

// Main Menu enum
enum Main_option
{
    INSERTION = 1,
    SEARCH,
    SORTING_OPTION,
    EXIT
};

int main(int argc, char *argv[])
{
    string file_name = argv[1];
    StudentDatabase db(file_name);

    run(db);
}

void run(StudentDatabase &db)
{
    int choice;

    while (true)
    {
        cout << "\n- Main menu -" << std::endl;
        cout << "1. Insertion" << endl;
        cout << "2. Search" << endl;
        cout << "3. Sorting Option" << endl;
        cout << "4. Exit" << endl;
        cout << " > ";

        cin >> choice;

        switch (choice)
        {
        case INSERTION:
            db.insertMenu();
            break;
        case SEARCH:
            db.searchMenu();
            break;
        case SORTING_OPTION:
            db.sortMenu();
            break;
        case EXIT: // 무한 루프 탈출
            db.save();
            return;
        default:
            std::cout << "Enter a number between 1 and 4." << std::endl;
            break;
        }
    }
}
