#include <iostream>
#include <string>
using namespace std;

struct Book
{
    int ID;
    int price;
    int pages;
    string BookName;
    string author;
    string ISBN;    
};


struct BookList
{
    Book books[5];
};

struct Student
{
    int ID;
    string StdName;
    int RollNo;
};

struct StudentList
{
    Student std[5];
};

void PrintAll(Book one[5])
{

    cout << "(:**DETAILS OF THE BOOKs**:)" << endl;
    
    Book* ptrone;
    ptrone = one;
  
    for (int i = 0; i < 5; i++)
    {

        cout << "ID: " << (ptrone + i)->ID << endl;
        cout << "Name: " << (ptrone + i)->BookName << endl;
        cout << "Author: " << (ptrone + i)->author << endl;
        cout << "ISBN: " << (ptrone + i)->ISBN << endl;
        cout << "Price: " << (ptrone + i)->price << endl;
        cout << "Pages: " << (ptrone + i)->pages << endl;
    }
}

void Printbook(Book books[5])
{
    int x, count = 0;
    cout << "\nEnter book id to display";
    cin >> x;
    for (int i = 0; i < 5; i++)
    {
        if (books[i].BookName == "\0")
            continue;

        if (books[i].ID == x)
        {
            cout << "ID--> " << books[i].ID << endl;
            cout << "Book Name--> " << books[i].BookName << endl;
            cout << "Author--> " << books[i].author << endl;
            cout << "ISBN--> " << books[i].ISBN << endl;
            cout << "Price--> " << books[i].price << endl;
            cout << "Pages--> " << books[i].pages << endl;
            count++;
            break;
        }
    }

    if (count == 0)
        cout << "\nBook not found";

    cout << endl;
}


void addBook(Book books[5])
{
    char exit;
    int position;
    cout << "Which position do you want to add it to: ";
    cin >> position;
    for (int i = position; i < 5; i++)
    {
        cout << "\nEnter Book ID:";
        cin >> books[i].ID;
        cout << "\nEnter Book Name:";
        cin >> books[i].BookName;
        cout << "\nEnter Author's Name:";
        cin >> books[i].author;
        cout << "\nEnter Book's Price:";
        cin >> books[i].price;
        cout << "\nEnter Book's Pages:";
        cin >> books[i].pages;

        cout << "\nPress y or Y to add another book\n";
        cout << "Press any other character to exit:\n";
        cin >> exit;
        if (exit != 'y' || exit !='Y')
        {
            break;
        }
    }
}


void ascending(Book books[5])
{
    Book temp;
    for (int i = 0; i < 5; i++)
    {
        if (books[i].BookName == "\0")
        {
            continue;
        }
            for (int j = i + 1; j < 5; j++)
        {
            if (books[i].BookName > books[j].BookName)
            {
                temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }

}

void descending(Book books[5])
{
    Book temp;
    for (int i = 0; i < 5; i++)
    {
        if (books[i].BookName == "\0")
            continue;
        for (int j = i + 1; j < 5; j++)
        {
            if (books[i].BookName < books[j].BookName)
            {
                temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }

}

void deleteAll(Book books[5])
{
    memset(books, 0, sizeof(books));
    cout << "\nAll Books have been deleted:)\n";
}

void printStudents(Student std[5])
{
    Student* ptrstd;
    ptrstd = std;

    for (int i = 0; i < 5; i++)
    {
        if ((ptrstd + i)->StdName == "\0")
            continue;

        cout << "\n(:***DETAILS OF THE STUDENTS***:)\n\n" ;
        cout << "ID: " << std[i].ID << "\n\n";
        cout << "Name: " << (ptrstd + i)->StdName << "\n\n";
        cout << "RollNo: " << std[i].RollNo << "\n\n";
    }
}



void addStudent(Student std[5])
{
    cout << "Add Student ID or press 7 to exit: ";

    for (int i = 0; i < 5; i++)
    {
        if (std[i].ID == 7)
        {
            std[i].ID = 0;
            break;
        }
        else if (std[i].StdName == "\0")
        {
            cin >> std[i].ID;

            cout << "\nEnter name ";
            cin >> std[i].StdName;
            cout << "\nEnter roll no ";
            cin >> std[i].RollNo;

            cout << "\nStudent added succesfully";
            break;                      

        }
    }
}

void deleteStudent(Student std[5])
{

    cout << endl;
    int del;
    cout << "Enter Reg No. to be deleted: ";
    cin >> del;
    int x, count = 0;
    for (int i = 0; i < 5; i++)
    {
        if (del == std[i].ID)
        {
            x = i;

            for (int j = x; j <= 4; j++)
            {
                std[i] = std[i + 1];

                if (std[i + 1].StdName == "\0")         
                {                                       
                    std[i + 1].ID = 0;
                    std[i + 1].StdName = "";
                    std[i + 1].RollNo = 0;
                }
            }
            cout << "Deleted successfully." << endl;
            count++;
        }
    }
    if (count == 0)
    {
        cout << "Reg No. not found in array." << endl;
    }

}

int main()
{
    Book one[5];
    Student std[5];

    int x;

    do
    {
        cout << "\n\t\tMAIN MENU\n\n";
        cout << "1.\tAdd New Student." << endl;
        cout << "2.\tDelete Existing Students." << endl;;
        cout << "3.\tShow All students." << endl;;
        cout << "4.\tAdd New Book." << endl;;
        cout << "5.\tDelete All Books." << endl;;
        cout << "6.\tShow Particular Book." << endl;;
        cout << "7.\tShow All Books" << endl;;
        cout << "8.\tSort Books in Ascending order." << endl;;
        cout << "9.\tSort Books in Descending order." << endl;;
        cout << "10.\tExit." << endl;;
        cout << "\t\t\n";

        cin >> x;
        switch (x)
        {
        case 1:
        {
            addStudent(std);         
            break;
        }

        case 2:
        {
            deleteStudent(std);
            break;             
        }

        case 3:
        {
            printStudents(std);
            break;
        }

        case 4:
        {
            addBook(one);
            break;
        }
        case 5:
        {
            deleteAll(one);
            break;
        }

        case 6:
        {
            Printbook(one);
            break;
        }

        case 7:
        {
            PrintAll(one);
            break;
        }
        
        case 8:
        {
            ascending(one);
            break;
        }
        
        case 9:
        {
            descending(one);
            break;
        }
        case 10:
        {
            break;
        }
        default:
            cout << "Please enter a valid integer" << endl;
            break;
        }

    } while (x != 10);

    return 0;
}