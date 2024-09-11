#include "admin.h"






int admin_menu();

// Custom string comparison function
int myStrCmp(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 < *str2)
        {
            return -1;       // Agar pehla string choti hai
        }
        else if (*str1 > *str2)
        {
            return 1;        // Agar pehla string bara hai
        }
        str1++;
        str2++;
    }

    // Strings are equal up to the length of the shorter string
    if (*str1 == '\0' && *str2 == '\0')
    {
        return 0; // Both strings are equal
    }
    else if (*str1 == '\0')
    {
        return -1; // str1 is shorter
    }
    else
    {
        return 1; // str2 is shorter
    }
}


// Admin login ke liye function
void admin_login()
{
    char name_from_file[10];
    char pass_from_file[10];

    ifstream file("admin.txt");
    if (!file)
    {
        cout << "Error opening file." << endl;
        return;
    }

    if (file.getline(name_from_file, 10, ','))
    {
        file.getline(pass_from_file, 10, ';');
    }
    else
    {
        cout << "Error reading from file." << endl;
    }
    char name[10];
    char password[10];

    cout << "LOGIN*\n\n";

    cout << "Enter your Name :  \n";
    cin.ignore();
    cin.getline(name, 10);

    cout << "Enter the Password : " << endl;
    cin.getline(password, 10);
    if (myStrCmp(name, name_from_file) == 0 && myStrCmp(password, pass_from_file) == 0)
    {
        cout << "Welcome*\n";
        cout << "Access Granted\n";
        cout << endl;
    }
    else
    {
        cout << "Incorrect username or password" << endl;
        int choice = 0;
        cout << "Do you want to login again? (yes = 1 / No = 0)" << endl;
        cin >> choice;
        if (choice == 1)
        {
            admin_login();
        }
        else
        {
            return;
        }
    }
}


// Notification data ko file mein likhne ke liye function
void WriteNotification(const char *itemName, int quantity, int price, int index)
{
    // int notifi[100] = {0};
    static int i = 0;
    // notifi[i] = index;
    i++;
    ofstream notificationFile("notification.txt", ios::app); // ios::app opens the file in append mode

    if (!notificationFile)
    {
        cout << "Error opening notification file." << endl;
        return;
    }

    // Set width for each field for a more organized display
    notificationFile << itemName
                     << "," << quantity
                     << "," << price
                     << "," << index
                     << endl;

    notificationFile.close();
}


// Notifications ko display karne ke liye function
void DisplayNotification()
{
    ifstream file("notification.txt");
    if (!file)
    {
        cout << "Error opening file." << endl;
        return;
    }
    cout << "Displaying Notification" << endl;

    string DisplayString;

    cout << left << setw(30) << "Name" << setw(20) << "Quantity" << setw(10) << "Price" << endl;

    while (getline(file, DisplayString))
    {
        cout << DisplayString << endl;
    }

    file.close();
}


// Notifications ko clear karne ke liye function
void Stop()
{
    ofstream file("notification.txt", ios::trunc);
    if (!file)
    {
        cout << "Error opening file." << endl;
        return;
    }
}


// Stocks ke data ko file se parhne ke liye function
void ReadStockFile()
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

    file1.close();
    ifstream file("stocks.txt");

    if (!file)
    {
        cerr << "Error opening file: stocks.txt" << endl;
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

        if (itemCount >= MAX_STOCKS)
        {
            cout << endl;
            cout << "Maximum number of stock items reached." << endl;
            break;
        }
    }

    for (int i = 0; i < itemCount; i++)
    {
        if (Quantity[i] < 30) // set threshold as 30
        {
            WriteNotification(name_of_stock[i], Quantity[i], Price[i], i);
        }
    }

    file.close();

    cout << "==============================Displaying Stocks==============================" << endl;

    cout << left << setw(30) << "Name" << setw(20) << "Quantity" << setw(10) << "Price" << endl;
    for (int i = 0; i < itemCount; ++i)
    {
        cout << left << setw(30) << name_of_stock[i] << setw(20) << Quantity[i] << setw(10) << Price[i] << endl;
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


// Item search karne ke liye function
int SearchItem(char *itemname)
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

    while (getline(file, line))
    {
        stringstream ss(line);

        name_of_stock[itemCount] = new char[MAX_NAME_LENGTH];

        ss.getline(name_of_stock[itemCount], MAX_NAME_LENGTH, ',');
        ss >> Quantity[itemCount];
        ss.ignore(); // Ignore the comma
        ss >> Price[itemCount];

        itemCount++;
        if (myStrCmp(name_of_stock[itemCount - 1], itemname) == 0)
        {
            index = itemCount - 1;
            isAvailable = true;
            break; // Add this line to exit the loop
        }

        if (itemCount >= MAX_STOCKS)
        {
            cout << endl;
            cout << "Maximum number of stock items reached." << endl;
            break;
        }
    }

    if (isAvailable)
    {
        cout << "Item: " << name_of_stock[index] << " with Quantity : " << Quantity[index] << " and Price: " << Price[index] << " Found." << endl;
    }
    else
    {
        cout << itemname << " not available" << endl;
        return -1;
    }
    for (int i = 0; i < itemCount; ++i)
    {
        delete[] name_of_stock[i];
    }
    delete[] name_of_stock;
    delete[] Quantity;
    delete[] Price;
    return index;
}



// Stocks file mein data likhne ke liye function
void WriteDataToFile(char **name_of_stock, int *Quantity, int *Price, int size)
{
    ofstream file("stocks.txt");
    if (!file)
    {
        cerr << "Error opening file: Stock.txt" << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
    {
        // Check if name_of_stock is not empty
        if (name_of_stock[i] != nullptr)
        {
            file << name_of_stock[i] << "," << Quantity[i] << "," << Price[i] << endl;
        }
    }

    file.close();
}



// Item ko remove karne ke liye function
void RemoveItem(char *itemname)
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

    while (getline(file, line))
    {
        stringstream ss(line);

        name_of_stock[itemCount] = new char[MAX_NAME_LENGTH];

        ss.getline(name_of_stock[itemCount], MAX_NAME_LENGTH, ',');
        ss >> Quantity[itemCount];
        ss.ignore(); // Ignore the comma
        ss >> Price[itemCount];

        itemCount++;
        if (myStrCmp(name_of_stock[itemCount - 1], itemname) == 0)
        {
            index = itemCount - 1;
            isAvailable = true;
        }

        if (itemCount >= MAX_STOCKS)
        {
            cout << endl;
            cout << "Maximum number of stock items reached." << endl;
            break;
        }
    }

    if (isAvailable)
    {
        cout << "Item: " << name_of_stock[index] << " with Quantity : " << Quantity[index] << " and Price: " << Price[index] << " Removed." << endl;
        name_of_stock[index] = 0;
        Quantity[index] = 0;
        Price[index] = 0;
        WriteDataToFile(name_of_stock, Quantity, Price, size);
    }
    else
    {
        cout << itemname << " not available" << endl;
    }
    for (int i = 0; i < itemCount; ++i)
    {
        delete[] name_of_stock[i];
    }
    delete[] name_of_stock;
    delete[] Quantity;
    delete[] Price;
}


// Item ko add karne ke liye function
void AddItem(int items_to_be_added)
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
    size += items_to_be_added;
    const int MAX_STOCKS = size;
    const int MAX_NAME_LENGTH = 100;

    char **name_of_stock = new char *[MAX_STOCKS];
    int *Quantity = new int[MAX_STOCKS];
    int *Price = new int[MAX_STOCKS];
    int index;
    bool isAvailable = false;

    file1.close();
    ifstream file("stocks.txt", ios::app);

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
    for (int i = itemCount; i < size; i++)
    {
        name_of_stock[i] = new char[MAX_NAME_LENGTH];
        cout << "Enter the name of Item: ";
        cin.ignore(); // Ignore newline character left in the buffer
        cin.getline(name_of_stock[i], MAX_NAME_LENGTH);
        cout << "Enter the Quantity of Item: ";
        cin >> Quantity[i];

        cout << "Enter the Price of Item: ";
        cin >> Price[i];
    }
    WriteDataToFile(name_of_stock, Quantity, Price, size);
    cout << "\nAdded Successfully\n";
    for (int i = 0; i < itemCount; ++i)
    {
        delete[] name_of_stock[i];
    }
    delete[] name_of_stock;
    delete[] Quantity;
    delete[] Price;
}



// Complaints dekhne ke liye function
void viewComplaints()
{
    const int MAX_COMPLAINT_SIZE = 1000;

    ifstream file("complaints.txt");

    if (!file)
    {
        cout << "Error opening file: complaints.txt" << endl;
        return;
    }

    cout << "Viewing Complaints" << endl;

    char complaintsData[MAX_COMPLAINT_SIZE];
    int index = 0;
    char ch;

    while (file.get(ch) && index < MAX_COMPLAINT_SIZE - 1)
    {
        complaintsData[index++] = ch;
    }

    complaintsData[index] = '\0'; // Null-terminate the char array

    file.close();

    cout << complaintsData << endl;
}


// Online orders ko dekhne ke liye function
void ViewOnlineOrder()
{
    ifstream file("onlineorder.txt");

    if (!file)
    {
        cout << "Error opening file: online_orders.txt" << endl;
        return;
    }

    cout << "Viewing Online Orders" << endl;

    const int MAX_FILE_SIZE = 1000; // Adjust the size based on your expected file size
    char onlineOrdersData[MAX_FILE_SIZE];
    int index = 0;
    char ch;

    while (file.get(ch) && index < MAX_FILE_SIZE - 1)
    {
        onlineOrdersData[index++] = ch;
    }

    onlineOrdersData[index] = '\0'; // Null-terminate the char array

    file.close();

    cout << onlineOrdersData << endl;
}


// Item details ko update karne ke liye function
void UpdateItem(char *itemname)
{
    string line = "";
    int size = 0;
    fstream file1("stocks.txt");
    if (!file1)
    {
        cout << "Error in Opening : Stocks.txt \n";
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
        cout << "Error in opening the file: stocks.txt" << endl;
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
    int i = SearchItem(itemname);
    
    if (i == -1)
    {
        cout << "Cannot Update because Item was not found\n";
        return;
    }
    else
    {
        cout << "Enter the Quantity of Item: ";
        cin >> Quantity[i];

        cout << "Enter the Price of Item: ";
        cin >> Price[i];
        cout << "Item: " << name_of_stock[i] << " with Quantity : " << Quantity[i] << " and Price: " << Price[i] << " Updated." << endl;
    }
    WriteDataToFile(name_of_stock, Quantity, Price, size);
    for (int i = 0; i < itemCount; ++i)
    {
        delete[] name_of_stock[i];
    }
    delete[] name_of_stock;
    delete[] Quantity;
    delete[] Price;
}


// Threshold ke neeche items ko order karne ke liye function
void OrderItems()
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

    file1.close();
    ifstream file("stocks.txt");

    if (!file)
    {
        cerr << "Error opening file: stocks.txt" << endl;
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

        if (itemCount >= MAX_STOCKS)
        {
            cout << endl;
            cout << "Maximum number of stock items reached." << endl;
            break;
        }
    }

    for (int i = 0; i < itemCount; i++)
    {
        if (Quantity[i] < 30) // set threshold as 30
        {
            cout << "Enter the Quantity(Quantity>30) for the item " << name_of_stock[i] << " to be ordered:";
            int input;
            cin >> input;
            while (input < 30)
            {
                cout << "Wrong Input\n";
                cout << "Enter the Quantity(Quantity>30) for the item " << name_of_stock[i] << " to be ordered:";
                cin >> input;
            }
            Quantity[i] += input;
        }
    }

    file.close();
    WriteDataToFile(name_of_stock, Quantity, Price, itemCount);
}


// Ek string ko doosri mein copy karne ke liye function
void myStrCpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
}


// Employees ke data ko manage karne ke liye function
void manageEmployee()
{
    const int MAX_EMPLOYEES = 100;
    const int MAX_NAME_LENGTH = 50;
    const int MAX_PASSWORD_LENGTH = 20;
    cin.ignore();
    const char *filename = "employee_data.txt";
    char employees[MAX_EMPLOYEES][MAX_NAME_LENGTH + MAX_PASSWORD_LENGTH + 2]; // 2 for comma and newline

    int numEmployees = 0;

    // Read existing employees from the file
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    char line[MAX_NAME_LENGTH + MAX_PASSWORD_LENGTH + 2]; // 2 for comma and newline
    while (numEmployees < MAX_EMPLOYEES && inFile.getline(line, sizeof(line)))
    {
        myStrCpy(employees[numEmployees], line);
        ++numEmployees;
    }

    inFile.close();

    char employeeName[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    cout << "Enter employee name: ";
    cin.getline(employeeName, sizeof(employeeName));

    cout << "Enter password (press Enter if removing an employee): ";
    cin.getline(password, sizeof(password));

    if (password[0] == '\0')
    {
        // Remove employee
        int indexToRemove = -1;
        for (int i = 0; i < numEmployees; ++i)
        {
            if (myStrCmp(employees[i], employeeName) == 0)
            {
                indexToRemove = i;
                break;
            }
        }

        cout << "Employee " << employeeName << endl;
        if (indexToRemove != -1)
        {
            for (int i = indexToRemove; i < numEmployees - 1; ++i)
            {
                myStrCpy(employees[i], employees[i + 1]);
            }
            --numEmployees;
            cout << "Employee '" << employeeName << "' removed successfully.\n";
        }
        else
        {
            cout << "Employee '" << employeeName << "' not found.\n";
        }
    }
    else
    {
        // Add employee
        if (numEmployees < MAX_EMPLOYEES)
        {
            int i = 0;
            while (employeeName[i] != '\0')
            {
                employees[numEmployees][i] = employeeName[i];
                ++i;
            }
            employees[numEmployees][i] = ',';
            ++i;
            int j = 0;
            while (password[j] != '\0')
            {
                employees[numEmployees][i + j] = password[j];
                ++j;
            }
            employees[numEmployees][i + j] = '\0';
            ++numEmployees;
            cout << "Employee '" << employeeName << "' added successfully.\n";
        }
        else
        {
            cerr << "Maximum number of employees reached. Cannot add more.\n";
            return;
        }
    }

    // Write the updated employees back to the file
    ofstream outFile(filename);
    if (outFile.is_open())
    {
        for (int i = 0; i < numEmployees; ++i)
        {
            outFile << employees[i] << endl;
        }
        outFile.close();
    }
    else
    {
        cerr << "Error opening file: " << filename << endl;
    }
}


// Behtareen bechne wale employee ko pehchanne ke liye function
void Bestseller()
{
    string line = "";
    int size = 0;
    fstream file1("employee_data.txt");
    if (!file1)
    {
        cout << "Error Opening : employee_data.txt \n";
    }
    else
    {
        while (getline(file1, line))
        {
            size++;
        }
    }

    file1.close();

    srand(time(NULL));

    int emp = rand() % size;
    cout<<"employee"<<emp+1<<" is the best seller"<<endl;
}


// Admin menu ke liye function
int admin_menu()
{
    int choice = 0;

    cout << "**********************************************************" << endl;
    cout << "--------------------ADMIN MENU--------------------" << endl;
    cout << "**********************************************************" << endl;
    cout << "0. Exit" << endl;
    cout << "1. See details of cafe stock" << endl;
    cout << "2. Search item" << endl;
    cout << "3. Remove item" << endl;
    cout << "4. Update item" << endl;
    cout << "5. Add item " << endl;
    cout << "6. Add/Remove Credentials of Employees" << endl;
    cout << "7. Display Notification " << endl;
    cout << "8. See online Scheduled Order" << endl;
    cout << "9. BestSeller Employee " << endl;
    cout << "10. Order Items that are below ThresholdSee " << endl;
    cout << "11. See Complaints \n";
    cin >> choice;

    return choice;
}
