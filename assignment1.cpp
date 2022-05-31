#include <iostream>
using namespace std;

struct Book
{
int ID;
int price;
int pages;
string *BookName;
string *author;
string *ISBN;

void PrintAll(string book[])
{   
    cout<<"(:******DETAILS OF THE BOOK******:)"<<endl;
    cout<< "ID: "<<id<<endl;
    cout<< "Name: "<<bookName<<endl;
    cout<< "Author: "<<author<<endl;
    cout<< "ISBN: "<<id<<endl;
    cout<< "Price: "<<price<<endl;
    cout<< "Pages: "<<pages<<endl;       
}
};



struct BookList
{
 typedef string Book;
 Book books[5];
 
    void PrintAll(string books[])
    {
        cout<<"****This is the array of the books****"<<endl;
        for(int i =0;i<5;i++)
        {
            cout<< books[i]<<" ";
        }
    cout<<endl;
    }

void addBook(string books[])
{
    for(int i=0;i<5;i++)
    {
        cout<<"enter book name or press a to exit.";
        cin>>books[i];
        if (books[i] =="a")
        {
            break;
        }
    }
}

void ascending(string arr[])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if (arr[i] > arr[j])
			{
				string temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

}

void descending(string arr[])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{   
			if (arr[i] < arr[j])
			{
				string temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

}

void deleteAll(string books[])
{
    for (int i = 0; i < 5; i++)
    {
        arr[i] = { "" };
    }
}

};

struct Student
{
    int ID;
    string *StdName;
    int RollNo;

  void PrintAll(string books[])
    {
       
       cout<<"ID: "<<ID<<endl;
       cout<<"Student's Name: "<<StdName<<endl;
       cout<<"Roll No: "<<RollNo<<endl;

    }  

};

struct StudentList
{
    typedef string StudentList;
 StudentList std[5];

 void PrintAll()
 {
     for(int i=0;i<5;i++)
     {
         cout<<std[i]<<" ";
     }
     cout<<endl;
 }
void addStudent()
{
    cout<<"Add student ID: or press 7 to exit";
    for (int i=0;i<5;i++)
    {
        cin>>std[i];
    
    if (std[i]==7)
    {
    break;
    }
    }  
}
void deleteStudent()
{
    cout<<"Array contents: "<<endl;
    
     for(int i=0;i<5;i++)
     {
         cout<<std[i]<<" ";
     }
     cout<<endl;
int del;
cout<<"Enter reg no to be deleted: ";
cin>>del;
for(int i=0;i<5;i++)
{
if(del == std[i])
{
    std[i]=null;

}

}
cout<<"The new array is: "<<endl;

     for(int i=0;i<5;i++)
     {
         cout<<std[i]<<" ";
     }
     cout<<endl;


}

};






int main()
{
int x;
do
{
cout<<"\t\tMAIN MENU\n\n";
cout<<"1.\tAdd New Student.\n";
cout<<"2.\tDelete Existing Students.\n";
cout<<"3.\tShow all students.\n";
cout<<"4.\tAdd New Book.\n";
cout<<"5.\tDelete Existing Book.\n";
cout<<"6.\tShow particular Book.\n";
cout<<"7.\tShow all Books\n";
cout<<"8.\tSort Books in Ascending order.\n";
cout<<"9.\tSort Books in Descending order.\n";
cout<<"0.\tExit\n";
    
cin>>x;
switch (int x)
{
case 1:
{
    /* code */
}
   break;

case 2:
{
    /* code */
}
   break;

case 3:
{
    /* code */
}
   break;

case 4:
{
    /* code */
}
   break;

   case 5:
{
    /* code */
}
   break;

   case 6:
{
    /* code */
}
   break;

case 7:
{
    /* code */
}
   break;

case 8:
{
    /* code */
}
   break; 

case 9:
{
    /* code */
}
   break;     

 case 0:
{
    /* code */
}
   break;  
default:
cout<<"Please enter a valid integer";
    break;
}


}while (x!=0)


return 0;
}