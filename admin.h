#include "header.h"
#include <iomanip>

using namespace std;

int admin_menu();
int myStrCmp(const char *str1, const char *str2);
void admin_login();
void WriteNotification(const char *itemName, int quantity, int price, int index);
void DisplayNotification();


void Stop();

void ReadStockFile();


int SearchItem(char *itemname);

void WriteDataToFile(char **name_of_stock, int *Quantity, int *Price, int size);


void RemoveItem(char *itemname);

void AddItem(int items_to_be_added);


void viewComplaints();

void ViewOnlineOrder();

void UpdateItem(char *itemname);

void OrderItems();

void myStrCpy(char *dest, const char *src);
void manageEmployee();


void Bestseller();

int admin_menu();
