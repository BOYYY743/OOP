#include <iostream>
#include <string>
using namespace std;
size_t Mystrlen(const char* s2)
{
	int count = 0;

	while (s2[count] != '\0')
		count++;

	return count;
}
char* Mystrcpy(char* s1, const char* s2)
{
	/*int size = 0;
	int size = Mystrlen(s2);*/

	for (int j = 0; j < Mystrlen(s2); j++)
	{
		if (s2[j] == '\0')
		{
			break;
		}
		s1[j] = s2[j];
	}
	return s1;
}
char* Mystrncpy(char* s1, const char* s2, size_t n)
{
	for (int j = 0; j < n; j++)
	{
		if (s2[j] == '\0')
		{
			break;
		}
		s1[j] = s2[j];
	}
	return s1;
}
char* Mystrcat(char* s1, const char* s2)//finds where string 1 is empty and starts string 2 from that position//
{
	int k = 0;
	int s = Mystrlen(s1);
	int S = Mystrlen(s2);
	for (int i = 0; i < 50; i++)
	{
		if (s1[i] == '\0')
		{
			s1[i] = s2[k];
			k++;	
			if (s2[k] == '\0') //if string 2 is empty it breaks from there//
			{
				break;
			}
		}
	}
	return s1;
}
char* Mystrncat(char* s1, const char* s2, size_t n)
{
	int k = 0;
	int s = Mystrlen(s1);
	int S = Mystrlen(s2);

	for (int i = 0; i < 50; i++)
	{
		if (s1[i] == '\0')
		{
			if (k < n)
			{
				s1[i] = s2[k];
				k++;
				if (s2[k] == '\0')
					break;
			}
		}
	}
	return s1;
}
int Mystrcmp(const char* s1, const char* s2)
{
	int count = 0;
	for (int i = 0; i < 50; i++)
	{
		if (s1[i] > s2[i])
			return 1;

		else if (s1[i] < s2[i])
			return -1;

		else if (s1[i] == s2[i])
			continue;

	}

	if (count == 0)
		return 0;
}
int Mystrncmp(const char* s1, const char* s2, size_t n)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (s1[i] > s2[i])
			return 1;

		else if (s1[i] < s2[i])
			return -1;

		else if (s1[i] == s2[i])
			continue;

	}

	if (count == 0)
		return 0;
}
int main()
{
	char s2[50] = { 0 }, s1[50] = { 0 };
	int n;
	/*cout << "\nEnter no. of characters you want copied: ";
	cin >> n;*/
	cout << "Enter array values for first array: ";
	cin.getline(s1, 50, '\n');
	cout << "Enter array values for second array: ";
	cin.getline(s2, 50, '\n');
	int x;
	do {
        cout << "\n\n\t\tMENU\n\n";
	cout << "0.Determines the length of string.\n\n";
	cout << "1.Copies string to array.\n\n";
	cout << "2.Copies n characters of the string into array.\n\n";
	cout << "3.Appends both strings.\n\n";
	cout << "4.Appends n characters of both strings.\n\n";
	cout << "5.Compares both strings.\n\n";
	cout << "6.Compares both strings until n characters.\n\n";
	cout << "7.Breaks string into tokens.\n\n";
	cout << "8.PRESS 8 TO EXIT\n\n";
		cin >> x;
		switch (x)
		{
		case 0:
			cout << Mystrlen(s2);
			break;
		case 1:
			cout << Mystrcpy(s1, s2);
			break;
		case 2:
			cout << "\nEnter no of characters to copy\n";
			cin >> n;
			cout << Mystrncpy(s1, s2, n);
			break;
		case 3:
			cout << Mystrcat(s1, s2);
			break;
		case 4:
			cout << "\nEnter no of characters to copy\n";
			cin >> n;
			cout << Mystrncat(s1, s2, n);
			break;
		case 5:
			cout << Mystrcmp(s1, s2);
			break;
		case 6:
			cout << "\nEnter no of characters to compare\n";
			cin >> n;
			cout << Mystrncmp(s1, s2, n);
			break;
		}
	} while (x != 8);


	return 0;
}
