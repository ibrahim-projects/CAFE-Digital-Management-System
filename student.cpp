#pragma once
#include "student.h"
using namespace std;

//complaints ka lia function 
void GiveComplaints()
{
    int option;
    cout << "Complaint about " << endl;
    cout << "1. Related Food" << endl;
    cout << "2. Related Employee" << endl;
    cout << "3. Related Cleanliness" << endl;
    cout << "4. Others" << endl;
    cin >> option;
    char complaint[100];
    cout << "Enter your complaint(less than 100 words): " << endl;
    cin.ignore();
    cin.getline(complaint, 100);

    ofstream file("complaints.txt", ios::app);
    if (!file)
    {
        cerr << "Error opening file: complaints.txt" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        switch (option)
        {
        case 1:
        {
            file << "Complaint about Food : " << complaint << endl;
            file.close();

            break;
        }
        case 2:
        {
            file << "Complaint about Employee : " << complaint << endl;
            file.close();

            break;
        }
        case 3:
        {
            file << "Complaint about Cleanliness : " << complaint << endl;
            file.close();

            break;
        }
        case 4:
        {
            file << "Other Complaint : " << complaint << endl;
            file.close();

            break;
        }

        default:
        {
            cout << "Invalid choice" << endl;
        }
        break;
        }
    }
}



void giveOnlineorder()
{   //  online order ka function nicha diya gahi 2 functions ha jin ma saik function search item in order ka ha or dosra give order ka haa
}

void giveOrder(char *name, int value, int price)
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
void searchitemandorder()
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

    char Searchedname[20] = {'\0'};

    char **name_of_stock = new char *[MAX_STOCKS];
    int *Quantity = new int[MAX_STOCKS];
    int *Price = new int[MAX_STOCKS];
    int index = 0;
    bool isAvailable = false;
    file1.close();
    ifstream file("stocks.txt");

    if (!file)
    {
        cout << "Error opening file: stocks.txt" << endl;
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

    for (int i = 0; i < itemCount; i++)
    {
        cout << name_of_stock[i] << endl;
    }

    cout << endl;
    cout << "Enter item name: " << endl;

    cin.ignore(); // ignore the newline character left in the buffer
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
                giveOrder(name_of_stock[index], tempQuantity, Price[index]);
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


//only search and display karana ka function
void JustSearchandDisplay()
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

    char Searchedname[20] = {'\0'};

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
    cout << "Enter item name: " << endl;

    cin.ignore(); // ignore the newline character left in the buffer
    cin.getline(Searchedname, sizeof(Searchedname));

    for (int i = 0; i < itemCount; i++)
    {
        if (myStrCmp(name_of_stock[i], Searchedname) == 0)
        {
            isAvailable = true;
            break;
        }
    }
    if (isAvailable)
    {
        cout << "Yes its Available" << endl;
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


// students ka notification show karana ka function
void viewStudentsNotifications()
{
    const int MAX_NOTIFICATION_SIZE = 1000;

    ifstream file("notificationforStudent.txt");

    if (!file)
    {
        cout << "Error opening file: notificationforStudent.txt" << endl;
        return;
    }

    cout << "Viewing Notifications" << endl;
    cout << endl;
    char NotificationData[MAX_NOTIFICATION_SIZE];
    int index = 0;
    char ch;

    while (file.get(ch) && index < MAX_NOTIFICATION_SIZE - 1)
    {
        NotificationData[index++] = ch;
    }

    NotificationData[index] = '\0'; // Null-terminate the char array

    file.close();

    cout << NotificationData << endl;
    cout << endl;
}


//student menu display karan ka function

int StudentMenu()
{
    int choice = 0;

    cout << "****************************************************" << endl;
    cout << "--------------------STUDENT MENU--------------------" << endl;
    cout << "****************************************************" << endl;

    cout << "0. Exit" << endl;
    cout << "1. Give complaints " << endl;
    cout << "2. Just Searching item" << endl;
    cout << "3. Online Order" << endl;
    cout << "4. See Notifications" << endl;

    cin >> choice;

    return choice;
}
