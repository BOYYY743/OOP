#include <iostream>
using namespace std;


class CMyString {

private:
	int size;
	char* Array;
	int count1 = 0;

public:

	CMyString()
	{
		size = 50;
		Array = new char[size];
	}

	CMyString(char arr[50])
	{
		this->Array = Array;
	}

	CMyString(int size)
	{
		this->size = size;
		Array = new char[size];
	}

	~CMyString() {};

	int getSize()
	{
		return size;
	}

	char getArray()
	{
		char* arr = new char[size];
		for (int i = 0; i < size; i++)
		{
			*(arr + i) = this->Array[i];
		}
		return *arr;
	}

	// input stream operator overloading

	friend istream& operator >> (istream& input, CMyString& other)
	{

		other.Array = new char[other.size];

		for (int i = 0; i < other.size; i++)
		{

			input >> other.Array[i];
		}

		return input;

	}

	// output stream operator overloading

	friend ostream& operator << (ostream& output, CMyString& other)
	{

		for (int i = 0; (other.Array[i] >= 0 && other.Array[i] < 123); i++)
		{
			output << other.Array[i];
		}

		return output;

	}

	// + overloading

	CMyString operator+ (const CMyString& other)
	{
		CMyString obj;

		int i = size;

		for (int x = 0; x < size; x++)
		{
			obj.Array[x] = Array[x];

		}

		for (int j = 0; (other.Array[j] >= 0 && other.Array[j] < 123); j++, i++)
		{
			obj.Array[i] = other.Array[j];

		}


		return obj;

	}

	// += overloading 

	CMyString operator+= (const CMyString& other)
	{

		int i = size;

		for (int j = 0; (other.Array[j] >= 0 && other.Array[j] < 123), j < size; j++, i++)
		{
			Array[i] = other.Array[j];

		}

		return *this;
	}

	// [] overloading 

	char& operator[](int i) {
		if (i > size) {
			cout << "Index out of bounds" << endl;
			return Array[0];
		}

		return Array[i];
	}

	// == overloading

	bool operator ==(const CMyString& other) {
		int count = 0;

		for (int i = 0; i < size; i++)
		{
			if (Array[i] == other.Array[i])
			{
				count++;
			}

		}

		if (count == size) {
			return true;
		}
		else
		{
			return false;
		}
	}

	// != overloading

	bool operator !=(const CMyString& other) {
		int count = 0;

		for (int i = 0; i < size; i++)
		{
			if (Array[i] == other.Array[i])
			{
				count++;
			}

		}

		if (count == size) {
			return false;
		}
		else
		{
			return true;
		}
	}

	// > overloading

	bool operator >(const CMyString& other) {
		int count = 0;

		for (int i = 0; i < size; i++)
		{
			if (Array[i] > other.Array[i])
			{
				count++;
				break;
			}

		}

		if (count != 0) {
			return true;
		}
		else
		{
			return false;
		}
	}

	// < overloading

	bool operator <(const CMyString& other) {
		int count = 0;

		for (int i = 0; i < size; i++)
		{
			if (Array[i] < other.Array[i])
			{
				return true;
				break;
			}

		}

		if (count != 0) {
			return true;
		}
		else
		{
			return false;
		}
	}

	// () substring overloading

	CMyString operator()(int a, int b)
	{
		CMyString obj;

		for (int i = a; i <= b; i++)
		{
			obj.Array[i] = Array[i];
		}

		return obj;

	}

	// = overloading

	CMyString& operator = (const CMyString& obj)
	{
		for (int i = 0; i < size; i++)
		{
			Array[i] = obj.Array[i];
		}

		return *this;
	}

	// << string right shift overloading

	CMyString operator << (int a)
	{
		CMyString obj;

		for (int i = 0; i < a; i++)
		{
			obj.Array[i] = Array[i];
		}

		for (int i = a, j = 0; i < size; i++, j++)
		{
			Array[j] = Array[i];
		}

		for (int i = size - a; i < size; i++)
		{
			Array[i] = '�';
		}

		return obj;
	}

	// >> string left shift overloading
	CMyString operator >> (int a)
	{
		CMyString obj;

		a = a + count1;

		for (int i = size, j = 0; i > size - a; i--)
		{
			if (Array[i - 1] >= 0 && Array[i - 1] < 123)
			{
				obj.Array[j] = Array[i - 1];
				Array[i - 1] = '�';
				j++;
			}

		}

		count1++;

		return obj;
	}



};

int main()
{

	int size, choice = 0;
	char menu;

	cout << "Enter size of Array: ";
	cin >> size;

	CMyString a(size);
	cout << "\nEnter string a: " << endl;
	cin >> a;                                            //stream insertion for array a

	CMyString b(size);
	cout << "\n\nEnter string b: " << endl;
	cin >> b;                                           // stream insertion for array b

	do
	{
		cout << "\n**ENTER YOUR CHOICE FROM THEE MENU BELOW**\n\n";

			cout << " 1. Concanecate Strings (c=a+b).\n";
			cout << " 2. Concanecate Strings (a +=b).\n";
			cout << " 3. Get individual characters.\n";
			cout << " 4. Set individual characters.\n";
			cout << " 5. Check for Equality (a == b).\n";
			cout << " 6. Check for Equality (a == a).\n";
			cout << " 7. Check string inequality.\n";
			cout << " 8. Compare strings (>)\n";
			cout << " 9. Compare strings (<)\n";
			cout << "10. Get substring\n";
			cout << "11. Assign String(b=a)\n";
			cout << "12. String left shift (a<<n)\n";	
			cout << "13. String right shift (a>>n)\n";
			cin >> choice;

		cout << endl;

		switch (choice)
		{
		case 1:
		{
			CMyString c((size * 2));

			c = a + b;

			cout << "c = \"" << c << "\"" << endl;
			break;
		}
		case 2:
		{
			a += b;

			cout << "a = \"" << a << "\"" << endl;
			break;
		}
		case 3:
		{
			char d = a[1];

			cout << "d = \"" << d << "\"" << endl;
			break;
		}
		case 4:
		{
			b[4] = '1';

			cout << "b = \"" << b << "\"" << endl;
			break;
		}
		case 5:
		{
			bool t = (a == b);

			if (t == 1)
				cout << "t = True\n";
			else
				cout << "t = False\n";

			break;
		}
		case 6:
		{
			bool p = (a == a);

			if (p == 1)
				cout << "\np = True\n";
			else
				cout << "\np = False\n";

			break;
		}
		case 7:
		{
			if (a != b)
				cout << "Condition False\n";
			else
				cout << "Condition True\n";

			break;
		}
		case 8:
		{
			if (a > b)
				cout << "Condition True\n";
			else
				cout << "Condition False\n";

			break;
		}
		case 9:
		{
			if (a < b)
				cout << "Condition True\n";
			else
				cout << "Condition False\n";

			break;

		}
		case 10:
		{
			CMyString c(4);
			c = a(0, 3);

			cout << "c = \"" << c << "\"" << endl;
			break;
		}
		case 11:
		{
			b = a;

			cout << "b = \"" << b << "\"" << endl;
			break;
		}
		case 12:
		{
			CMyString c(4);
			c = a << 1;

			cout << "\nc = \"" << c << "\" and a = \"" << a << "\"" << endl;

			c = a << 3;

			cout << "\nc = \"" << c << "\" and a = \"" << a << "\"" << endl;
			break;
		}
		case 13:
		{

			CMyString c(4);
			c = a >> 1;

			cout << "\nc = \"" << c << "\" and a = \"" << a << "\"" << endl;

			c = a >> 3;

			cout << "\nc = \"" << c << "\" and a = \"" << a << "\"" << endl;
			break;
		}
		}

		cout << "\nDo you want to overload another operator example? Enter Y to continue!  ";
		cin >> menu;

	} while (menu == 'y' || menu == 'Y');


	return 0;
}