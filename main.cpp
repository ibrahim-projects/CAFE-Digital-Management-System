#include "header.h"
using namespace std;

int main()
{





     cout << "************************************************************" << endl;
     cout << "*************** CDF System **********************"  << endl;
     cout << "************************************************************" << endl<<endl<<endl;


//           Starting Main Program       





     cout << "____________________________________________________________________" << endl;
     cout << "____________________________________________________________________" << endl;
     cout << "____________________________________________________________________" << endl;

     cout << "               WELCOME TO Cafe Digital System                       " << endl;

     cout << "____________________________________________________________________" << endl;
     cout << "____________________________________________________________________" << endl;
     cout << "____________________________________________________________________" << endl;
     
     
     
     int choice, option;

     cout << "\n\nSelect Your Role From [1-3]\n\n";

     cout << "1.Administration\n";
     cout << "2.Employee\n";
     cout << "3.Student or Staff\n\n";

     cin >> choice;

     switch (choice)
     {
     case 1:                                    // Admin ka case
     {
          option = -1;

          // function for admin login detail
          admin_login();
          // function for admin menu

          do
          {

               option = admin_menu();

               switch (option)
               {
               case 0:            // Exit case
               {
                    cout << "exiting..." << endl;
                    Stop();
                    exit(0);
                    break;
               }
               case 1:             // Stock data read karne ke liye case
               {
                    ReadStockFile(); 
                    break;
               }
               case 2:             // Item search karne ke liye case
               {
                    cout << "Enter item name: " << endl;
                    char Searchedname[20] = {'\0'};
                    cin.ignore();                                  // ignore the newline character left in the buffer
                    cin.getline(Searchedname, sizeof(Searchedname));
                    SearchItem(Searchedname);
                    break;
               }
               case 3:           // Item remove karne ke liye case
               {
                    char RemoveName[20] = {'\0'};
                    cin.ignore(); // ignore the newline character left in the buffer
                    cin.getline(RemoveName, sizeof(RemoveName));
                    RemoveItem(RemoveName);
                    break;
               }
               case 4:          // Item update karne ke liye case
               {
                    cout << "Enter the name of the item to be updated: ";
                    char UpdateName[20] = {'\0'};
                    cin.ignore(); // ignore the newline character left in the buffer
                    cin.getline(UpdateName, sizeof(UpdateName));
                    UpdateItem(UpdateName);
                    break;
               }
               case 5:           // Item add karne ke liye case
               {
                    int count;
                    cout << "How many items to be added: ";
                    cin >> count;
                    AddItem(count);
                    break;
               }
               case 6:          // Employee management ke liye case
               {
                    manageEmployee();
                    break;
               }

               case 7:             // Notification display karne ke liye case
               {
                    DisplayNotification();
                    break;
               }
               case 8:             // Online orders display karne ke liye case
               {
                    ViewOnlineOrder();
                    break;
               }

               case 9:           // Bestsellers display karne ke liye case
               {
                    Bestseller();
                    break;
               }
               case 10:          // Order items ke liye case
               {
                    OrderItems();
                    break;
               }
                case 11:            // Complaints display karne ke liye case
               {
                    viewComplaints();
                    break;
               }
               }
          } while (option != 0);
     }
     break;

     case 2:  // Employee ka case
     {
          option = -1;

          if (employee_login())
          {
               cout << "Login successful!" << endl;
               do
               {
                    option = employee_menu();
                    switch (option)
                    {
                    case 1:         // Order lenay ke liye case
                    {
                         TakeOrder();
                         break;
                    }
                    case 2:        // Item search karne ke liye case
                    {
                         char Searchedname[20] = {'\0'};
                         cin.ignore();                                                        // ignore the newline character left in the buffer
                         cin.getline(Searchedname, sizeof(Searchedname));
                         SearchItem(Searchedname);
                         break;
                    }
                    case 3:        // Order handling ke liye case
                    {
                         OrderHandling();
                         break;
                    }
                    default:
                         break;
                    }

               } while (option != 0);
          }
          else
          {
               cout << "Invalid username or password." << endl;
          }

          break;
     }
     case 3:     // Student Case
     {
          int option = -1;

          do
          {
               option = StudentMenu();
               switch (option)
               {
               case 1:           // Complaints denay ke liye case
               {
                    GiveComplaints();
                    break;
               }
               case 2:           // Search and display karne ke liye case
               {
                    JustSearchandDisplay();
                    break;
               }
               case 3:           // Item search karke order denay ke liye case
               {
                    searchitemandorder();
                    break;
               }
               case 4:         // Students ke liye notifications display karne ke liye case

               {

                    viewStudentsNotifications();
                    break;
               }

               case 0:           // Exit case
               {
                    cout << "Exiting..." << endl;
                    exit(0);
               }
               default:
                    break;
               }
          } while (option != 0);

          break;
     }
     }
     return 0;
}
