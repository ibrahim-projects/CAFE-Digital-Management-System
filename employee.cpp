#pragma once
#include "employee.h"
// using namespace std;

// employee login details
int employee_login()
{
    char inputUsername[20];
    char inputPassword[20];

    cin.ignore();
    cout << "Enter username: ";
    cin.getline(inputUsername, 20);

    cout << "Enter password: ";
    cin.getline(inputPassword, 20);
    ifstream file("employee_data.txt");

    if (!file)
    {
        cerr << "Error opening file: employee_data.txt" << endl;
        return false;
    }

    char fileUsername[5][20];
    char filePassword[5][20];
    char comma; // To ignore the comma
    int i = 0;
    while (i < 5 && file.getline(fileUsername[i], sizeof(fileUsername[i]), ',') && file >> filePassword[i])
    {
        file.ignore(); // Consume the newline character

        if (myStrCmp(fileUsername[i], inputUsername) == 0 && myStrCmp(filePassword[i], inputPassword) == 0)
        {
            file.close();
            return 1; // Credentials are valid
        }
        i++;
    }

    file.close();
    return 0; // Credentials not found or incorrect
}


// Order receipt ka function
void giveTheOrder(char *name, int value, int price)
{
    cout << endl;
    cout << endl;
    cout << "|========================================================" << endl;
    cout << "|                          Receipt                        " << endl;
    cout << "|                                                        " << endl;
    cout << "| Item Name: " << setw(30) << left << name << endl;
    cout << "| Quantity : " << setw(29) << left << value << endl;
    cout << "|                                                        " << endl;
    cout << "|========================================================" << endl;
    cout << "|   Price of item is : " << setw(25) << left << price << endl;
    cout << "|   " << price << "*" << value << " Total" << endl;
    cout << "|   Your Bill will be " << price * value << "\\-\n";
    cout << "|========================================================" << endl;

    cout << endl;
    cout << endl;
    int hours = 0;
    int min = 0;
    cout << "Enter Time" << endl;
    cout << "Enter Hour(hours = 24,hh/mm):" << endl;
    cin >> hours;
    cout << "Enter minutes(hours = 24,hh/mm):" << endl;
    cin >> min;

    ofstream file("onlineorder.txt", ios::app);
    if (!file)
    {
        cerr << "Error opening file: onlineorder.txt" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        file << name << "," << value << "," << price << endl;
        cout << "your order has been placed." << endl;
        cout << "Come at " << hours << ":" << min << " to pick your order." << endl;
    }
}



// Order lenay ke liye
void TakeOrder()
{
    string line = "";
    int size = 0;
    fstream file1("stocks.txt");
    if (!file1)
    {
        cout << "Error Opening : Stocks.txt \n";
    }
    else
    {
        while (getline(file1, line))
        {
            size++;
        }
    }
    const int MAX_STOCKS = size;
    const int MAX_NAME_LENGTH = 100;

    char **name_of_stock = new char *[MAX_STOCKS];
    int *Quantity = new int[MAX_STOCKS];
    int *Price = new int[MAX_STOCKS];
    int index;
    bool isAvailable = false;

    file1.close();
    ifstream file("stocks.txt");

    if (!file)
    {
        cout << "Error opening file: stocks.txt" << endl;
        exit(EXIT_FAILURE);
    }

    int itemCount = 0;
    // File se data parh kar memory mein daalna
    while (getline(file, line))
    {
        stringstream ss(line);

        name_of_stock[itemCount] = new char[MAX_NAME_LENGTH];

        ss.getline(name_of_stock[itemCount], MAX_NAME_LENGTH, ',');
        ss >> Quantity[itemCount];
        ss.ignore(); // Ignore the comma
        ss >> Price[itemCount];

        itemCount++;
    }

    for (int i = 0; i < itemCount; i++)
    {
        cout << name_of_stock[i] << endl;
    }
    cout << endl;
    cout << "Enter the name of Item: ";
    char Searchedname[20] = {'\0'};
    cin.ignore(); // You can include or exclude this line for testing
    cin.getline(Searchedname, sizeof(Searchedname));
    for (int i = 0; i < itemCount; i++)
    {
        if (myStrCmp(name_of_stock[i], Searchedname) == 0)
        {
            index = i;
            isAvailable = true;
            break;
        }
    }

    if (isAvailable)
    {
        cout << "Item: " << name_of_stock[index] << " with Quantity : " << Quantity[index] << " and Price: " << Price[index] << " Found." << endl;

        int orderchoice = -1;
        cout << "Do you want to order? (yes =1 /No = 0)" << endl;
        cin >> orderchoice;

        if (orderchoice == 1)
        {
            int tempQuantity = 0;
            cout << "Enter Quantity: " << endl;
            cin >> tempQuantity;
            if (tempQuantity >= Quantity[index])
            {
                cout << "That Much Quantity is not available Right now." << endl;
            }
            else
            {
                Quantity[index] -= tempQuantity;
                giveTheOrder(name_of_stock[index], tempQuantity, Price[index]);
                WriteDataToFile(name_of_stock, Quantity, Price, size);
            }
        }
    }
    else
    {
        cout << Searchedname << " not available" << endl;
        return;
    }
    // Clean up memory
    for (int i = 0; i < itemCount; ++i)
    {
        delete[] name_of_stock[i];
    }

    delete[] name_of_stock;
    delete[] Quantity;
    delete[] Price;
}

    // Order handling ka function
void OrderHandling()
{

    string line = "";
    int size = 0;
    int index = 0;
    fstream file1("onlineorder.txt");
    if (!file1)
    {
        cout << "Error Opening : Onlineorder.txt \n";
    }
    else
    {
        while (getline(file1, line))
        {
            size++;
        }
    }
    const int MAX_STOCKS = size;
    const int MAX_NAME_LENGTH = 100;

    char Searchedname[20] = {'\0'};

    char **name_of_stock = new char *[MAX_STOCKS];
    int *Quantity = new int[MAX_STOCKS];
    int *Price = new int[MAX_STOCKS];
    bool isAvailable = false;

    file1.close();
    ifstream file("onlineorder.txt");

    if (!file)
    {
        cout << "Error opening file: Onlineorder.txt" << endl;
        exit(EXIT_FAILURE);
    }

    int itemCount = 0;

    while (getline(file, line))
    {
        stringstream ss(line);

        name_of_stock[itemCount] = new char[MAX_NAME_LENGTH];

        ss.getline(name_of_stock[itemCount], MAX_NAME_LENGTH, ',');
        ss >> Quantity[itemCount];
        ss.ignore(); // Ignore the comma
        ss >> Price[itemCount];

        itemCount++;
    }
        // Agar online orders mojood hain

    if (name_of_stock != nullptr)
    {
        cout << left << setw(30) << "Name" << setw(20) << "Quantity" << setw(10) << "Price" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << left << setw(30) << name_of_stock[i] << setw(20) << Quantity[i] << setw(10) << Price[i] << endl;
        }
        cout << "Orders Delivered\n";
        ofstream file1("onlineorder.txt", ios::trunc);
        if (!file1)
        {
            cout << "Error opening file." << endl;
            return;
        }
        else
        {
        }
        file1.close();
    }
    else
    {
        cout << "No online orders are available" << endl;
        return;
    }
    // Clean up memory
    for (int i = 0; i < itemCount; ++i)
    {
        delete[] name_of_stock[i];
    }

    delete[] name_of_stock;
    delete[] Quantity;
    delete[] Price;
}

// Employee menu ka function
int employee_menu()
{
    int choice = 0;

    cout << "******************" << endl;
    cout << "--------------------Emoloyee MENU--------------------" << endl;
    cout << "******************" << endl;
    cout << "0. Exit" << endl;
    cout << "1. Take Order:" << endl;
    cout << "2. Search item" << endl;
    cout << "3. Schedule Order Handling" << endl;
    cin >> choice;

    return choice;
}
