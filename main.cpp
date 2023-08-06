#include <bits/stdc++.h>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;

const int consoleWidth = 80, consoleHeight = 200;
const double rent_per_day = 49.5;

class admin;
class user;
void head();
void setConsoleSize(int width, int height);                                             // Function to set the console window size
string centerText(const string& text);                                                  //Function to center the text
tm stringToDate(const string& dateStr);                                                 //Function to convert string to date
double dateDifference(const string& date1, const string& date2);                        //Function to calclate difference between two dates

class admin{

    string pass;

    protected:
        vector<string> arr;
        string element;
        string name, cont, addr, roomType, inDate, outDate, bill, foodItem;
        int roomNo, i = 0, temp = 0, foodNo;
        double foodPrice;

    public:
        char choice;
        void adminLogin();
        void adminOptions();
        void checkIn();
        void mMenu();
        void guestList();
        int showMenu();

}ad;

class user : public admin{

    int roomN;  

    public:
        void userLogin();
        void userOptions();
        void viewBill();
        void orderFood();
        void checkOut();
        void faq();
    
}us;


int main(){

    int choice;
    setConsoleSize(consoleHeight * 8, consoleWidth * 8);
    
    do{
        head();
        cout << centerText("Check-in and Debug Out: Unwind and Code Away!") << endl <<endl << endl;
        cout << setw(80) << "" << "1. User Login" << endl << endl;
        cout << setw(80) << "" << "2. Staff Login" << endl <<endl;
        cout << setw(80) << "" << "3. Exit" << endl << endl <<endl;
        cout << setw(80) << "" << "Enter you choice: ";
        cin >> choice;

        if(choice == 1){
            us.userLogin();
        }
        else if(choice == 2){
            ad.adminLogin();
        }

        else if(choice == 3){
            exit(1);
        }

        else{
            head();
            cout << "WRONG CHOICE!!!";
            cin.get();
        }
    }while(choice != 3);
    cin.get();  //waits for user input as to keep program running and not exiting after showing output
    cin.get();
}   

void setConsoleSize(int width, int height) {
    HWND console = GetConsoleWindow();
    RECT rect;
    GetWindowRect(console, &rect);

    MoveWindow(console, rect.left, rect.top, width, height, TRUE);
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_SIZEBOX);
}

string centerText(const string& text) {
    int totalPadding = consoleHeight - text.length();
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;
    return string(leftPadding, ' ') + text;
}

tm stringToDate(const string& dateStr) {
    tm t = {};
    istringstream iss(dateStr);
    iss >> get_time(&t, "%d-%m-%y");
    return t;
}

double dateDifference(const string& date1, const string& date2) {
    tm t1 = {}, t2 = {};
    istringstream iss1(date1);
    istringstream iss2(date2);
    iss1 >> get_time(&t1, "%d-%m-%y");
    iss2 >> get_time(&t2, "%d-%m-%y");

    time_t time1 = mktime(&t1);
    time_t time2 = mktime(&t2);

    const double secondsPerDay = 24.0 * 60.0 * 60.0;
    return abs(difftime(time1, time2)) / secondsPerDay;
}

void head(){
    system("CLS");
    cout << "**************************************************************************************************************************************************************************************************" << endl;
    cout << centerText("THE DEBUGGING DEN") << endl;
    cout << "**************************************************************************************************************************************************************************************************" << endl << endl;
}

void admin :: adminLogin(){

    head();
    cout << "\t\t\tEnter Login:";
    cin >> pass;
    //Sleep(100);
    ifstream fin("pass.txt");

    fin.open("pass.txt");

    if(!fin.is_open())
        cout << "ERROR!!!" << "\t" << "Couldn't confirm password, please contact admin.";
    
    string line((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    if(pass == line){
        cout <<centerText("Correct...");
        Sleep(5);
        adminOptions();
        }
    
    else{
        cout <<centerText("WRONG PASSWORD") << endl;
        Sleep(5);
        cout << centerText("EXITING");
        Sleep(3000);
        cout << ".";
        Sleep(3000);
        cout << ".";
        Sleep(3000);
        cout << ".";
        Sleep(3000);
        cout << ".";
        Sleep(3000);
        exit(1);
    }
}

void admin :: adminOptions(){

        do{
        head();
        cout << setw(80) << "" << "1. Guest Check-in" << endl << endl ;
        cout << setw(80) << "" << "2. Manage Menu" << endl << endl ;
        cout << setw(80) << "" << "3. Display Guest-List" << endl << endl ;
        cout << setw(80) << "" << "4. Back" << endl << endl ;
        // cout << centerText("5. Exit" << endl << endl ;
        cout << setw(80) << "" << "Enter Choice: ";
        cin >> choice;

        switch(choice){
            case '1':{
                checkIn();
                break;
            }
            case '2':{
                mMenu();
                break;
            }
            case '3':{
                guestList();
                break;
            }
            case '4':{
                
                break;
            }
            default:{
                head();
                cout << "WRONG CHOICE!!!";
                cin.get();
            }
        }}while(choice != '4');
}

void admin :: checkIn(){
    head();
    fstream fout;
    
     // Get the current time
    time_t currentTime = time(nullptr);
    // Convert the current time to a string in the desired format
    tm* timeInfo = localtime(&currentTime);
    ostringstream oss;
    oss << put_time(timeInfo, "%d-%m-%y"); // Format: DD-MM-YYY
    inDate = oss.str();

    cin.get();

    fout.open("room.txt",ios::in);
    fout >> roomNo;
    fout.close();

    fout.open("room.txt", ios::out | ios::trunc);
    fout << roomNo + 1;
    fout.close();

    cout << "Room No.: " << roomNo << endl;
    
    cout << "Enter Room Type: ";
    getline(cin,roomType);

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Address: ";
    getline(cin, addr);

    cout << "Enter Contact No: ";
    getline(cin, cont);

    bill = outDate = "0";

    fout.open("guestList.csv", ios::out | ios::app);

    if(!fout.is_open())
        cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List, please contact admin.";

    fout << roomNo << "," << roomType << "," << inDate << "," << outDate << "," << name << "," << addr << "," << cont << "," << bill << "\n";

    fout.close();
}

int admin::showMenu() {
    head();

    fstream fout;
    fout.open("menu.csv", ios::in);

    cout << left << setw(10) << "" << setw(20) << "ITEM No." << setw(30) << "FOOD ITEM" << "PRICE" << endl << endl;

    temp = 1;
    string line;
    while (getline(fout, line)) {
        ++temp;
        istringstream iss(line);
        string element;
        while (getline(iss, element, ',')) {
            arr.push_back(element);
        }
        cout << left << setw(10) << "" << setw(20) << arr[0] << setw(30) << arr[1] << stod(arr[2]) << endl << endl;
        arr.clear();
    }
    fout.close();

    return temp;
}

void admin :: mMenu(){

    cin.ignore();

    temp = us.showMenu();

    fstream fout;

    cout << endl << endl << endl << left << setw(80) << "" << "1. Code a Dish :: Add" << endl << setw(80) << "" << "2. Menu Malfunction? Debug :: Delete" <<endl<<endl;
    cout << left << setw(80) << "" << "Enter your Choice: ";
    cin >> choice;

    fout.open("menu.csv", ios :: in | ios :: out | ios :: app);

    switch(choice){
        case '1':{

            cout << endl << endl << "Item No.: " << temp << endl;

            cin.ignore();

            cout << "Enter Food Name: ";
            getline(cin, foodItem);

            cout << endl << "Enter Price: ";
            cin >> foodPrice;

            fout << temp << "," << foodItem << "," << foodPrice << "\n";
            
            break;
        }

        case '2':{
            cout << endl << endl << "Enter Item No.: ";
            cin >> foodNo;

            vector<string> tempData;
            string line;

            // Read the file and store data in tempData excluding the line to delete
            while (getline(fout, line)) {
                istringstream iss(line);
                string element;
                getline(iss, element, ',');
                int currentFoodNo = stoi(element);
                if (currentFoodNo != foodNo) {
                    // Modify the item number in the line to maintain the order
                    line.replace(0, element.size(), to_string(tempData.size() + 1));
                    tempData.push_back(line);
                }
            }

            fout.close();

            fout.open("menu.csv", ios::out | ios::trunc);
            for (const string& data : tempData) {
                fout << data << endl;
            }

            cout << "Item No. " << foodNo << " has been debugged from the menu." << endl;
            break;
        }

        default :
            cout << "Wrong Choice!!!";
    }

    fout.close();
   
}

void admin :: guestList(){

    head();

    fstream fout;
    fout.open("guestList.csv", ios :: in);

    if(!fout.is_open())
        cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List, please contact admin.";
    
    cout << left << setw(10) <<  ""  << endl << setw(20) << "Room No." << setw(21)  << "Room Type" << setw(15) << "Check-In" << setw(15) << "Check-Out" << setw(20) << "Guest Name" << setw(60) << "Address" << setw(20) << "Contact No." << setw(20) << "Total Bill" << endl << endl;

    string line;

    while (getline(fout, line)){ // Read each line from the file
        istringstream iss(line);
        string element;
        while (getline(iss, element, ',')) { // Split the line by tab ('\t')
            arr.push_back(element); // Print each element
            ++i;
        }
        cout << left << setw(10) <<  ""  << endl << setw(20) << arr[0] << setw(21) << arr[1] << setw(15) << arr[2] << setw(15) << arr[3] << setw(20) << arr[4] << setw(60) << arr[5] << setw(20) << arr[6] <<setw(20) << arr[7] << endl;
        
        arr.clear();
        i = 0;
    }
    cin.get();
    cin.get();
    fout.close();
}

void user :: userLogin(){

    head();
            cout << "\t\t\tEnter Room No.: ";

            cin >> roomN;

            ifstream fin("guestList.csv");
            if (!fin.is_open()) {
                cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List, please contact admin." << endl;
                cin.get();
                cin.get();
            }

            bool found = false;
            string line;
            while (getline(fin, line)) {
                istringstream iss(line);
                string element;
                getline(iss, element, ',');
                int currentRoomNo = stoi(element);
                if (currentRoomNo == roomN) {
                    found = true;
                    break;
                }
            }

            fin.close();

            if (found){
                Sleep(3);
                userOptions();
            } else {
                head();
                cout << centerText("Room number not found. Please try again or exit.") << endl;
                cin.get();
            }

}

void user::userOptions() {
    do {
        head();
        cout << left << setw(80) << "" << "1. View Menu" << endl << endl;
        cout << left << setw(80) << "" << "2. Order Food" << endl << endl;
        cout << left << setw(80) << "" << "3. View Bill" << endl << endl;
        cout << left << setw(80) << "" << "4. Check-out" << endl << endl;
        cout << left << setw(80) << "" << "5. FAQs" << endl << endl;
        cout << left << setw(80) << "" << "6. Back" << endl << endl << endl;
        cout << left << setw(80) << "" << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            showMenu();
            break;
        }
        case '2': {
            orderFood();
            break;
        }
        case '3': {
            viewBill();
            break;
        }
        case '4': {
            checkOut();
            break;
        }
        case '5': {
            faq();
            break;
        }
        default: {
            head();
            cout << "WRONG CHOICE!!!";
            cin.get();
        }
        }
    } while (choice != '6');
}

void user :: checkOut(){

}

void user::orderFood() {
    head();
    cout << centerText("Order Food") << endl << endl;

    // Show the menu to the user
    int menuItems = showMenu();

    // Ask the user to choose an item
    int choice;
    cout << "Enter the item number to order (1-" << menuItems - 1 << "): ";
    cin >> choice;

    // Check if the input is valid
    if (choice < 1 || choice >= menuItems) {
        cout << "Invalid choice. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();
        return;
    }

    // Get the selected food item and price
    ifstream fin("menu.csv");
    if (!fin.is_open()) {
        cout << "ERROR!!!" << "\t" << "Couldn't open Menu file, please contact admin." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();
        return;
    }

    string line;
    int currentItem = 1;
    string foodItem;
    string priceStr;
    double foodPrice = 0.0;

    while (getline(fin, line)) {
        if (currentItem == choice) {
            istringstream iss(line);
            getline(iss, foodItem, ',');
            getline(iss, foodItem, ',');
            getline(iss, priceStr, ',');
            break;
        }
        // currentItem++;
    }
    fin.close();

    // Convert the priceStr to a double using stringstream
    foodPrice = 0.0;
    istringstream issPrice(priceStr);
    if (!(issPrice >> foodPrice)) {
        cout << "Error parsing the food price. Please contact admin." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();
        return;
    }

    // Ask the user for the quantity of the item
    int quantity;
    cout << "Enter the quantity: ";
    cin >> quantity;

    // Check if the quantity is valid
    if (quantity <= 0) {
        cout << "Invalid quantity. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();
        return;
    }

    // Calculate the total cost of the food items
    double totalCost = foodPrice * quantity;

    // Update the food bill for the guest
    ofstream fout("foodBill.csv", ios::app);
    if (!fout.is_open()) {
        cout << "ERROR!!!" << "\t" << "Couldn't open Food Bill file, please contact admin." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();
        return;
    }

    fout << roomN << "," << totalCost << endl; // Use the stored roomNumber

    fout.close();

    head();
    cout << centerText("Order Successful!") << endl;
    cout << "You have ordered " << quantity << " " << foodItem << "(s) for a total cost of $" << totalCost << "." << endl;
    cout << "Thank you for ordering!" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    cin.get();
}

void user::viewBill() {
    head();
    cout << centerText("View Bill") << endl << endl;

    ifstream fin("guestList.csv");
    if (!fin.is_open()) {
        cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List, please contact admin." << endl;
        cin.get();
        cin.get();
        return;
    }

    bool found = false;
    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        string element;
        getline(iss, element, ',');
        int currentRoomNo = stoi(element);
        if (currentRoomNo == roomN) {
            getline(iss, roomType, ','); // Skip room type
            getline(iss, inDate, ',');   // Read check-in date
            found = true;
            break;
        }
    }
    fin.close();


    if (!found) {
        cout << "Guest with room number " << roomN << " not found." << endl;
        cin.get();
        cin.get();
        return;
    }


    // Get the current date
    time_t currentTime = time(nullptr);
    tm* timeInfo = localtime(&currentTime);
    ostringstream oss;
    oss << put_time(timeInfo, "%d-%m-%y"); // Format: DD-MM-YYY
    string currentDate = oss.str();

    // Convert the inDate and currentDate to tm structures
    tm checkInTime = stringToDate(inDate);
    tm currentTimeStruct = stringToDate(currentDate);

    // Calculate the difference between check-in date and current date
    double daysStayed = dateDifference(inDate, currentDate);


    // Calculate the total bill based on rent_per_day and food bill
    double foodBill = 0.0;
    ifstream finFoodBill("foodBill.csv");
    if (finFoodBill.is_open()) {
        string foodBillLine;
        while (getline(finFoodBill, foodBillLine)) {
            istringstream issBill(foodBillLine);
            string roomNoStr;
            double foodCost;
            getline(issBill, roomNoStr, ',');
            issBill >> foodCost;
            int roomNo = stoi(roomNoStr);
            if (roomNo == roomN) {
                foodBill += foodCost;
            }
        }
        finFoodBill.close();
    }

    double totalBill = daysStayed * rent_per_day + foodBill;

    // Display the bill to the user
    head();
    cout << centerText("Your Bill") << endl << endl << endl;
    cout << left << setw(80) << " " << setw(25) << "Room No.: " << roomN << endl << endl;
    cout << left << setw(80) << " " << setw(25) << "Room Type: " << roomType << endl << endl;
    cout << left << setw(80) << " " << setw(25) << "Check-In Date: " << inDate << endl << endl;
    cout << left << setw(80) << " " << setw(25) << "Days Stayed: " << fixed << setprecision(2) << daysStayed << endl << endl;
    cout << left << setw(80) << " " << setw(25) << "Room Rent: $" << fixed << setprecision(2) << daysStayed * rent_per_day << endl << endl;
    cout << left << setw(80) << " " << setw(25) << "Food Bill: $" << fixed << setprecision(2) << foodBill << endl << endl;
    cout << left << setw(80) << " " << setw(25) << "Total Bill: $" << fixed << setprecision(2) << totalBill << endl << endl;

    cin.get();
    cin.get();
}

void user :: faq(){

}