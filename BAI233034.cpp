#include <iostream>
#include <fstream>
#include<cstring>
#include<string>
using namespace std;
class User {
protected:
    string name;
    string idnum;
    string rank;
    string department;
    string username;
    string password;
    string role;
    string searchname;
    string searchidnum;
    string searchpass;
    //string tempusername;
   // string temppassword;

public:
    User(const string& name_ = "", const string& idnum_ = "", const string& rank_ = "",
        const string& department_ = "", const string& username_ = "", const string& password_ = "",
        const string& role_ = "")
        : name(name_), idnum(idnum_), rank(rank_), department(department_), username(username_),
        password(password_), role(role_) {}

    fstream file;

    // Function overloading for login and signup (optional)
   virtual  bool login (bool signup = false) ;
     virtual void signup() ;
    void forgetpass();
};
void User::signup() {
    cout << "\n                                                ---------------------------------------" << endl;
    cout << "\n                                                                SIGN-UP                " << endl;
    cout << "\n                                                ---------------------------------------" << endl;
    cout << "\nEnter Your User Name :: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter id-number:: ";
    
    getline(cin, idnum);
    cout << "Enter Your Password :: ";
  
    getline(cin, password);
    cout << "Enter your Name :: ";
  
    getline(cin, name);
    cout << "Enter your role :: ";
    
    getline(cin, role);
    cout << "Enter your Department :: ";
    
    getline(cin, department);
    cout << "Enter Rank :: ";
   
    getline(cin, rank);
    file.open("user.txt", ios::out | ios::app);
    file << username << "*" << idnum << "*" << password << endl;
    file.close();
}
bool User::login(bool signup) {
    if (signup) {
        return false; // Signup not implemented in base class
    }
    cout << "\n                                            -----------------------------------------                " << endl;
    cout << "                                                             LOGIN                                     " << endl;
    cout << "\n                                            -----------------------------------------                " << endl;

    cout << "Enter Your User Name :: " << endl;
    cin.ignore();
    getline(cin, searchname);
    cout << "Enter Your Password :: " << endl;
    // cin.ignore();
    getline(cin, searchpass);
    file.open("user.txt", ios::in);
    getline(file, username, '*');
    getline(file, idnum, '*');
    getline(file, password, '\n');
    while (!file.eof()) {
        if (username == searchname) {
            if (password == searchpass) {
                cout << "\nAccount Login Succesfull...!";
                cout << "\nUsername :: " << username << endl;
                cout << "\nid-num :: " << idnum << endl;
                break;
                //bool login1 = true;
            }
            else {
                cout << "Password is Incorrect...!";
            }
        }
        else {
            cout << "Password or username incorrect";
            break;
        }
        getline(file, username, '*');
        getline(file, idnum, '*');
        getline(file, password, '\n');
    }
    file.close();

}

void User::forgetpass() {
    //  logic to retrieve password based on username and ID number
    cout << "Enter Your UserName :: ";
    cin.ignore();
    getline(cin, searchname);
    cout << "\nEnter Your ID-NUMBER :: ";
    getline(cin, searchidnum);

    file.open("user.txt", ios::in);
    if (!file.is_open()) {
        cout << "Unable to open file\n";
        return;
    }

    getline(file, username, '*');
    getline(file, idnum, '*');
    getline(file, password, '\n');

    while (!file.eof()) {
        if (username == searchname && idnum == searchidnum) {
            cout << "\nAccount Found...!" << endl;
            cout << "Your Password :: " << password << endl;
            break;
        }
        else {
            cout << "Not found!" << endl;
        }
        getline(file, username, '*');
        getline(file, idnum, '*');
        getline(file, password, '\n');
    }
    file.close();
}
class Weapon : public User {
protected:
    string weaponid;
    string weaponname;
    double caliber;
    string price;
    string manufacturer;
    string searchweaponid;

public:
    Weapon(const string& username_ = "", const string& password_ = "", const string& role_ = "")
        : User(username_, password_, role_) {}

    fstream file;

    void weapondata();
    void searchweapon();
};

void Weapon::weapondata() {
    // Validate user login before weapon data entry
    if (!login()){
        cout << "Access denied. Please login first." << endl;
        return;
    }

    string inputid;
    cout << "Enter your ID-NUMBER :: ";
   // cin.ignore();
    getline(cin, inputid);

    bool idMatched = false;
    file.open("user.txt", ios::in);
    if (!file.is_open()) {
        cout << "Unable to open file\n";
        return;
    }

    while (getline(file, username, '*')) {
        getline(file, idnum, '*');
        getline(file, password); // Reading the rest of the line for password
        if (inputid == idnum) {
            idMatched = true;
            break;
        }
    }
    file.close();

    if (idMatched) {
        cout << "YOUR ID NUMBER MATCHED" << endl;
        cout << "Enter the Weapon ID :: ";
        getline(cin, weaponid);
        cout << "Enter the Name OF WEAPON :: ";
        getline(cin, weaponname);
        cout << "Enter the Caliber of WEAPON :: ";
        cin >> caliber;
        cin.ignore();
        cout << "Enter Price :: ";
        getline(cin, price);
        cout << "Enter the Manufacturer :: ";
        getline(cin, manufacturer);

        file.open("weapondata.txt", ios::out | ios::app);
        if (!file.is_open()) {
            cout << "Unable to open file\n";
            return;
        }

        file << weaponid << "*" << weaponname << "*"  << price << "\n"  << endl;
        file.close();

        cout << "Weapon Data Added Successfully!" << endl;
    }
    else {
        cout << "ID number does not match. Please try again." << endl;
    }
}

void Weapon::searchweapon() {
    // Validate user login before weapon search
    if (!login()) {
        cout << "Access denied. Please login first." << endl;
        return ;
    }
    

    cout << "Enter the Weapon ID you want to search :: ";
   
    getline(cin, searchweaponid);
    cout << "Enter caliber size of weapon" << endl;
    cin >> caliber; // Assuming caliber is a double
   // cin.ignore();
    file.open("weapondata.txt", ios::in);
    if (!file.is_open()) {
        cout << "Unable to open file\n";
        return;
    }
   

    bool found = false;
    while (!file.eof()) {
       
        getline(file, weaponid, '*');
        getline(file, weaponname, '*');
        getline(file, price, '\n');
       // getline(file, manufacturer, '\n');
        if (searchweaponid == weaponid) {
            found = true;
            cout << "** Weapon Data Found **" << endl;
            cout << "Weapon ID: " << weaponid << endl;
            cout << "Weapon Name: " << weaponname << endl;
            cout << "Caliber: " << caliber << endl;
            cout << "Price: $" << price << endl;
           // cout << "Manufacturer: " << manufacturer << endl;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Weapon ID not found." << endl;
    }
}
 class Ammunition : public Weapon {
                protected:
                    string quantityrequired;
                    string roundsize;
                    string pricepermagzine;
                    bool availablity=false;
                    static string quantityavailable; // Static member for shared ammo availability
                    int a = 0;
                    int b = 0;
                public:
                    Ammunition(const string& username_ = "", const string& password_ = "", const string& role_ = "")
                        : Weapon(username_, password_, role_) {}

                    fstream file;

                    void ammo();
                    void ammoinstock();
                    void displayammodata() const;

                private:
                    int convertToInt(const string& str) const { // Helper function for string to int conversion
                        return stoi(str);
                    }
            };

            string Ammunition:: quantityavailable = "5000"; 

            void Ammunition::ammo() {
                // Validate user login before ammo entry
                if (!login()) {
                    cout << "Access denied. Please login first." << endl;
                    return;
                }
                cout << "\n             ---------------------------------------" << endl;
                cout << "\n                                 AMMO" << endl;
                cout << "\n               ---------------------------------------" << endl;
                cout << "Enter quntity required" << endl;
                //cin.ignore();
                getline(cin, quantityrequired);
                //b = stoi(quantityrequired);
                cout << "Enter round-size" << endl;
                // cin.ignore();
                getline(cin, roundsize);
                cout << "Enter Price per magzine" << endl;
                // cin.ignore();
                getline(cin, pricepermagzine);
                file.open("ammodata.txt", ios::out | ios::app);
                file << quantityavailable <<"*" << quantityrequired << "*" << roundsize << "*" << pricepermagzine << endl;
                file.close();
               
            
                cout << "Ammo added successfully!" << endl;
            }

            void Ammunition::ammoinstock() {
                file.open("ammodata.txt", ios::in);
                if (!file.is_open()) {
                    cout << "Unable to open file\n";
                    return;
                }
                getline(file, quantityavailable, '*');
                getline(file, quantityrequired, '*');
                getline(file, roundsize, '*');
                getline(file, pricepermagzine, '\n');
                a = stoi(quantityavailable);
                if (a > 0) {
                    availablity = true;
                }
                else {
                    availablity = false;
                }
              //  cout << "availablity" << availablity << endl;
              
                
                cout << "Ammo status " << (availablity ? "Available" : "Not available") << endl;
                getline(file, quantityavailable, '*');
                getline(file, quantityrequired, '*');
                getline(file, roundsize, '*');
                getline(file, pricepermagzine, '\n');
                file.close();
            }

            void Ammunition::displayammodata() const {
                cout << "\n                       -------------------------------------------------------- " << endl;
                cout << "\n                                           DISPLAY RECENT DATA                      " << endl;
                cout << "\n                       -------------------------------------------------------- " << endl;
                cout << "Quantity Available:: " << quantityavailable << endl;
                cout << "Quantity Required:: " << quantityrequired << endl;
                cout << "Round Size:: " << roundsize << endl;
                cout << "Price Per Magazine:: $" << pricepermagzine << endl;
            }

            

    
            class Transction : public Ammunition {
            protected:
                string transctionid;
                string weaponid;
                string type;
                string remarks;
                string Reciptent;
            public:
                Transction() : Ammunition(), transctionid(""), type(""), remarks("") {}

                void Transection();
                void genratebill();
                string weapon1;
                string round;
                fstream file;
            };

            void Transction::Transection() {
                if (!login()) {
                    cout << "Access denied. Please login first." << endl;
                    return;
                }
                cout << "Genrating your Transaction ID:: " << endl;
                srand(time(0));
                transctionid = to_string(rand() * rand() + rand() * rand());
                cout << "Enter Weapon ID:: ";
               // cin.ignore();
                getline(cin, weapon1);

                cout << "Enter Type of Transaction:: ";
                
                getline(cin, type);
                cout << "Enter Remarks:: ";
               
                getline(cin, remarks);
               
               
            }
            void Transction::genratebill() {
                double weapon_price = 0.0;
                double magazine_price = 0.0;
                if (!login()) {
                    cout << "Access denied. Please login first." << endl;
                    return;
                }
                cout << "Enter Reciptent Name" << endl;
                getline(cin, Reciptent);
                cout << "Transaction ID: " << transctionid << endl;
                cout << "Enter Round-size:: ";               
                getline(cin, round);
                file.open("weapondata.txt", ios::in);
                if (!file) {
                    cout << "Unable to open file";
                    return;
                }
                getline(file, weaponid, '*');
                getline(file, weaponname, '*');
                getline(file, price, '\n');
                while (!file.eof()) {
                    if (this->weaponid == weapon1) {
                        weapon_price = stod(price);
                        break;
                    }
                    getline(file, weaponid, '*');
                    getline(file, weaponname, '*');
                    getline(file, price, '\n');
                }
                file.close();
                

                file.open("ammodata.txt", ios::in);
                if (!file) {
                    cout << "Unable to open file";
                    return;
                }
                getline(file, quantityavailable, '*');
                getline(file, quantityrequired, '*');
                getline(file, roundsize, '*');
                getline(file, pricepermagzine, '\n');
                //cout << roundsize;
                // cout << round;
               
                while (!file.eof()) {
                    if (this->roundsize == this->round) {
                        cout << "Round matches data in file" << endl;
                        magazine_price = stod(pricepermagzine);
                        break;
                    }
                    getline(file, quantityavailable, '*');
                    getline(file, quantityrequired, '*');
                    getline(file, roundsize, '*');
                    getline(file, pricepermagzine, '\n');
                }
                
                file.close();
              

                file.open("transactiondata.txt", ios::out | ios::app);
                if (!file.is_open()) {
                    cout << "Unable to open file\n";
                    return;
                }
                file << transctionid << "*" << weaponid << "*" << type << "*" << remarks << endl;
                file.close();

                double total_price = weapon_price + magazine_price;
                cout << "\n                                               -----------------------------------------"<< endl;
                cout << "\n                                                              BILL MEMO                 "<< endl;
                cout << "\n                                               -----------------------------------------"<< endl;
                cout << "Owner Name:" << Reciptent << endl;
                cout << "Weapon ID: " << weaponid << endl;
                cout << "Weapon price: RS" << weapon_price << endl;
                cout << "Price per magazine: $" << magazine_price << endl;
                cout << "Total price: $" << total_price << endl;
                cout << "Transaction Type: " << type << endl;
                cout << "Remarks: " << remarks << endl;
            }






           int main() {
               // Menu-driven interface for user interaction
               int choice;
           
               do {
                              cout << "\n                                    ---------------------------------------------" << endl;
                              cout << "\n                                           ** Arms Management System **          " << endl;
                              cout << "\n                                    ---------------------------------------------" << endl;
                   cout << "1. Login" << endl;
                   cout << "2. Sign-up" << endl;
                   cout << "3. Forget Password" << endl;
                   cout << "4. Exit" << endl;
                   cout << "Enter your choice: ";
                   cin >> choice;

                   switch (choice) {
                   case 1: {
                       Transction user;
                       
                       if (user.login()) {
                           int user_choice;
                           do {
                               cout << "\n** User Menu **" << endl;
                               cout << "1. Weapon Data Entry" << endl;
                               cout << "2. Search Weapon" << endl;
                               cout << "3. Add Ammunition" << endl;
                               cout << "4. Check Ammo Availability" << endl;
                               cout << "5. View Ammo Data" << endl;
                               cout << "6. Transaction (Issue/Return)" << endl;
                               cout << "7. Generate Bill" << endl;
                               cout << "8. Logout" << endl;
                               cout << "Enter your choice: ";
                               cin >> user_choice;

                               switch (user_choice) {
                               case 1: {
                                   
                                   user.weapondata();
                                   break;
                               }
                               case 2: {
                                   user.searchweapon();
                                   break;
                               }
                               case 3: {
                                   user.ammo();
                                   break;
                               }
                               case 4: {
                                   user.ammoinstock();
                                   break;
                               }
                               case 5: {
                                   user.displayammodata();
                                   break;
                               }
                               case 6: {
                                   user.Transection();
                                   break;
                               }
                               case 7: {
                                   user.genratebill();
                                   break;
                               }
                               case 8: {
                                   cout << "Logged out successfully!" << endl;
                                   break;
                               }
                               default: {
                                   cout << "Invalid choice." << endl;
                               }
                               }
                           } while (user_choice != 8);
                       }
                   }
                         break;
                   case 2:
                   {
                       Transction user;
                       user.signup();
                       break;
                   }
                   case 3: {
                       Transction user;
                       user.forgetpass();
                       break;
                   }
                   case 4: {
                       cout << "Exiting Arms Management System." << endl;
                       break;
                   }
                   default: {
                       cout << "Invalid choice." << endl;
                   }

                   }
               } while (choice != 4);
           }
           