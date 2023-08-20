#include <bits/stdc++.h>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;

const int consoleWidth = 90, consoleHeight = 200;
const double rent_per_day = 49.5;

class admin;
class user;
void head();
void setConsoleSize(int width, int height);                                             // Function to set the console window size
string centerText(const string& text);                                                  //Function to center the text
string getCurrentDate();
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

    private:
        double calculateTotalBill(const string& checkInDate);
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
        cout << setw(90) << "" << "1. User Login" << endl << endl;
        cout << setw(90) << "" << "2. Staff Login" << endl <<endl;
        cout << setw(90) << "" << "3. Exit" << endl << endl <<endl;
        cout << setw(90) << "" << "Enter you choice: ";
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

string getCurrentDate() {
    time_t currentTime = time(nullptr);
    tm* timeInfo = localtime(&currentTime);
    char buffer[9]; // "DD-MM-YY\0" requires 9 characters
    strftime(buffer, sizeof(buffer), "%d-%m-%y", timeInfo);
    return std::string(buffer);
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
        cout << setw(90) << "" << "1. Guest Check-in" << endl << endl ;
        cout << setw(90) << "" << "2. Manage Menu" << endl << endl ;
        cout << setw(90) << "" << "3. Display Guest-List" << endl << endl ;
        cout << setw(90) << "" << "4. Back" << endl << endl ;
        // cout << centerText("5. Exit" << endl << endl ;
        cout << setw(90) << "" << "Enter Choice: ";
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

void admin::checkIn() {
head();

    inDate = getCurrentDate();

    fstream fin("guestList.csv", ios::in);
    if (!fin.is_open()) {
        cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List, please contact admin." << endl;
        cin.get();
        return;
    }

    // Find the lowest available room number
    set<int> allocatedRooms;
    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        string roomNoStr;
        getline(iss, roomNoStr, ',');
        int roomNo = stoi(roomNoStr);
        allocatedRooms.insert(roomNo);
    }
    fin.close();

    // Find the lowest unallocated room number
    int lowestRoomNo = 1;
    while (allocatedRooms.find(lowestRoomNo) != allocatedRooms.end()) {
        lowestRoomNo++;
    }

    roomNo = lowestRoomNo; // Assign the lowest available room number to the new guest

    cin.ignore();

    cout << "Room No.: " << roomNo << endl;

    cout << "Enter Room Type: ";
    getline(cin, roomType);

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Address: ";
    getline(cin, addr);

    cout << "Enter Contact No: ";
    getline(cin, cont);

    bill = outDate = "0";

    ofstream fout("guestList.csv", ios::out | ios::app);
    if (!fout.is_open()) {
        cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List, please contact admin." << endl;
        cin.get();
        return;
    }

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

    do{
        temp = us.showMenu();

        fstream fout;

        cout << endl << endl << endl << left << setw(90) << "" << "1. Code a Dish :: Add" << endl << setw(90) << "" << "2. Menu Malfunction? Debug :: Delete" << endl << setw(90) << "" << "3.Back" <<endl<<endl;
        cout << left << setw(90) << "" << "Enter your Choice: ";
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
    }while(choice != '3');
   
}

void admin :: guestList(){

    head();

    fstream fout;
    fout.open("guestList.csv", ios :: in);

    if(!fout.is_open())
        cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List, please contact admin.";
    
    cout << left << setw(10) <<  ""  << endl << setw(20) << "Room No." << setw(21)  << "Room Type" << setw(15) << "Check-In" << setw(15) << "Check-Out" << setw(20) << "Guest Name" << setw(60) << "Address" << setw(20) << "Contact No." << setw(20) << "Total Bill" << endl << endl;

    string line;

    while (getline(fout, line)){ 
        istringstream iss(line);
        string element;
        while (getline(iss, element, ',')) { 
            arr.push_back(element);
        }
        cout << left << setw(10) <<  ""  << endl << setw(20) << arr[0] << setw(21) << arr[1] << setw(15) << arr[2] << setw(15) << arr[3] << setw(20) << arr[4] << setw(60) << arr[5] << setw(20) << arr[6] <<setw(20) << arr[7] << endl;
        
        arr.clear();
    }
    fout.close();
    cin.get();
    cin.get();
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
        cout << left << setw(90) << "" << "1. View Menu" << endl << endl;
        cout << left << setw(90) << "" << "2. Order Food" << endl << endl;
        cout << left << setw(90) << "" << "3. View Bill" << endl << endl;
        cout << left << setw(90) << "" << "4. Check-out" << endl << endl;
        cout << left << setw(90) << "" << "5. FAQs" << endl << endl;
        cout << left << setw(90) << "" << "6. Back" << endl << endl << endl;
        cout << left << setw(90) << "" << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            showMenu();
            cin.get();
            cin.get();
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
    } while (choice != '6' && choice != '4');
}

void user::checkOut() {
    head();
    cout << centerText("Check-Out") << endl << endl;

    cout << centerText("Are you sure you want to check out? (Y/N): ");
    cin >> choice;
    cin.ignore(); // Clear the newline character from the input buffer

    if (choice != 'Y' && choice != 'y') {
        cout <<endl << endl << endl << endl << centerText("Check-out process canceled.") << endl;
        cin.get();
        return;
    }

    ifstream fin("guestList.csv");
    ofstream fout("temp_guestList.csv");
    if (!fin.is_open() || !fout.is_open()) {
        cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List or temporary file, please contact admin." << endl;
        cin.get();
        cin.get();
        return;
    }

    bool found = false;
    string line;
    string currentDate = getCurrentDate();

    while (getline(fin, line)) {
        istringstream iss(line);
        string element;
        getline(iss, element, ',');
        int currentRoomNo = stoi(element);

        if (currentRoomNo == roomN) {
            found = true;
            getline(iss, roomType, ','); // Skip room type
            getline(iss, inDate, ',');   // Read check-in date
            getline(iss, outDate, ',');  // Read check-out date
            getline(iss, name, ',');     // Read guest name
            getline(iss, addr, ',');     // Read address
            getline(iss, cont, ',');     // Read contact number
            getline(iss, bill, ',');     // Read total bill

            double stayTime = dateDifference(inDate, currentDate);
            double totalBill = calculateTotalBill(inDate);
            
            double Bill = totalBill - (stayTime * rent_per_day);

            head();
            cout << centerText("Your Bill") << endl << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Room No.: " << roomN << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Room Type: " << roomType << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Check-In Date: " << inDate << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Check-Out Date: " << outDate << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Days Stayed: " << fixed << setprecision(2) << stayTime << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Room Rent: $" << fixed << setprecision(2) << stayTime * rent_per_day << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Food Bill: $" << fixed << setprecision(2) << Bill << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Total Bill: $" << fixed << setprecision(2) << totalBill << endl << endl;
            cin.get();
            cin.get();
        } else {
            // Copy other guests' data to the temporary file
            fout << line << "\n";
        }
    }

    fin.close();
    fout.close();

    // Rename the temporary file to guestList.csv, effectively replacing the old file
    if (remove("guestList.csv") != 0) {
        cout << "ERROR!!!" << "\t" << "Couldn't remove the old Guest-List, please contact admin." << endl;
        cin.get();
        cin.get();
        return;
    }
    if (rename("temp_guestList.csv", "guestList.csv") != 0) {
        cout << "ERROR!!!" << "\t" << "Couldn't update the Guest-List, please contact admin." << endl;
        cin.get();
        cin.get();
        return;
    }

    // Remove the food bill file for the checked-out guest
    ifstream finFoodBill("foodBill.csv");
    ofstream foutTemp("temp_foodBill.csv");
    if (!finFoodBill.is_open() || !foutTemp.is_open()) {
        cout << "ERROR!!!" << "\t" << "Couldn't open Food Bill or temporary file, please contact admin." << endl;
        cin.get();
        cin.get();
        return;
    }

    string foodBillLine;
    while (getline(finFoodBill, foodBillLine)) {
        istringstream issBill(foodBillLine);
        string roomNoStr;
        double foodCost;
        getline(issBill, roomNoStr, ',');
        issBill >> foodCost;
        int roomNo = stoi(roomNoStr);
        if (roomNo != roomN) {
            foutTemp << foodBillLine << endl;
        }
    }
    finFoodBill.close();
    foutTemp.close();

    // Rename the temporary food bill file to foodBill.csv, effectively updating it
    if (remove("foodBill.csv") != 0) {
        cout << "ERROR!!!" << "\t" << "Couldn't remove the old Food Bill, please contact admin." << endl;
        cin.get();
        cin.get();
        return;
    }
    if (rename("temp_foodBill.csv", "foodBill.csv") != 0) {
        cout << "ERROR!!!" << "\t" << "Couldn't update the Food Bill, please contact admin." << endl;
        cin.get();
        cin.get();
        return;
    }

    head();
    cout << centerText("Check-Out Successful!") << endl;
    cout << "Thank you for staying with us. Have a safe journey!" << endl;

    cin.get();
    cin.get();
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
        currentItem++;
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
    return;
}

double user::calculateTotalBill(const string& checkInDate) {
    // Get the current date
    string currentDate = getCurrentDate();

    // Convert the inDate and currentDate to tm structures
    tm checkInTime = stringToDate(checkInDate);
    tm currentTimeStruct = stringToDate(currentDate);

    double daysStayed = dateDifference(checkInDate, currentDate);

    double foodBill = 0.0;
    ifstream finFoodBill("foodBill.csv");
    if (finFoodBill.is_open()) {
        string foodBillLine;
        while (getline(finFoodBill, foodBillLine)) {
            istringstream issBill(foodBillLine);
            string roomNoStr;
            double foodCost;
            getline(issBill, roomNoStr, ','); // Read room number as a string
            issBill >> foodCost;
            int roomNoFromFile = stoi(roomNoStr); // Convert room number string to int
            if (roomN == roomNoFromFile) { // Compare with the function parameter
                foodBill += foodCost;
            }
        }
        finFoodBill.close();
    }

    double totalBill = daysStayed * rent_per_day + foodBill;
    return totalBill;
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
    string currentDate = getCurrentDate();

    while (getline(fin, line)) {
        istringstream iss(line);
        string element;
        getline(iss, element, ',');
        int currentRoomNo = stoi(element);

        if (currentRoomNo == roomN) {
            found = true;
            getline(iss, roomType, ','); // Skip room type
            getline(iss, inDate, ',');   // Read check-in date
            getline(iss, outDate, ',');  // Read check-out date
            getline(iss, name, ',');     // Read guest name
            getline(iss, addr, ',');     // Read address
            getline(iss, cont, ',');     // Read contact number
            getline(iss, bill, ',');     // Read total bill

            double stayTime = dateDifference(inDate, currentDate);
            double totalBill = calculateTotalBill(inDate);
            
            double Bill = totalBill - (stayTime * rent_per_day);

            head();
            cout << centerText("Your Bill") << endl << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Room No.: " << roomN << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Room Type: " << roomType << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Check-In Date: " << inDate << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Check-Out Date: " << outDate << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Days Stayed: " << fixed << setprecision(2) << stayTime << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Room Rent: $" << fixed << setprecision(2) << stayTime * rent_per_day << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Food Bill: $" << fixed << setprecision(2) << Bill << endl << endl;
            cout << left << setw(80) << " " << setw(25) << "Total Bill: $" << fixed << setprecision(2) << totalBill << endl << endl;

            cin.get();
            cin.get();
        }
    }

    fin.close();

    if (!found) {
        cout << "Guest with room number " << roomN << " not found." << endl;
        cin.get();
        cin.get();
        return;
    }
}


void user::faq() {
    head();
    cout << centerText("Frequently Asked Questions (FAQ)") << endl << endl;

    cout << "Program Options FAQs:" << endl << endl;
    cout << "Q1. How do I log in as a user?" << endl;
    cout << "A1. To log in as a user, enter your room number when prompted during the login process." << endl << endl;

    cout << "Q2. How can I check-in to the hotel?" << endl;
    cout << "A2. During the login, you can choose 'Check-in' to start the process. Follow the instructions to check-in as a new guest." << endl << endl;

    cout << "Q3. How can I view the menu to order food?" << endl;
    cout << "A3. You can choose 'View Menu' from the options to see the available coding-themed food items and their prices." << endl << endl;

    cout << "Q4. Can I order food for multiple guests in the same room?" << endl;
    cout << "A4. Yes, you can order food for multiple guests sharing the same room. The total bill will include all the ordered items." << endl << endl;

    cout << "Q5. How can I check-out from the hotel?" << endl;
    cout << "A5. Choose 'Check-out' from the user options to initiate the process. The system will calculate the total bill and provide further instructions." << endl << endl;

    cout << "Q6. Is there a way to modify my food order after placing it?" << endl;
    cout << "A6. Unfortunately, the system does not support modifying food orders once they are placed. Please review your order before confirming." << endl << endl;

    cout << "Q7. Can I view my total bill before checking out?" << endl;
    cout << "A7. Yes, you can choose 'View Bill' from the user options to see the total bill, including room rent and the total food bill." << endl << endl;

    cout << "Q8. How can I view the list of all guests staying in the hotel?" << endl;
    cout << "A8. The system allows you to view the list of guests. Choose 'Guest List' from the user options to access the information." << endl << endl;

    cout << "Q9. What happens if I forget my room number?" << endl;
    cout << "A9. In case you forget your room number, please approach the front desk with your identification, and they will assist you in retrieving it." << endl << endl;

    cout << "Q10. How do I provide feedback about my stay?" << endl;
    cout << "A10. We highly value your feedback! You can share your thoughts and suggestions with our staff during check-out or through our online survey." << endl << endl;

    cout << "Hotel Services FAQs:" << endl << endl;
    cout << "Q11. Is there 24/7 customer support available?" << endl;
    cout << "A11. Yes, our customer support is available 24/7 to assist you with any queries or concerns during your stay." << endl << endl;

    cout << "Q12. Can I request additional coding-themed amenities for my room?" << endl;
    cout << "A12. Certainly! Feel free to request additional coding-themed amenities or services at the front desk during your stay." << endl << endl;

    cout << "Q13. Are there coding-themed events or workshops in the hotel?" << endl;
    cout << "A13. Yes, we frequently organize coding-themed events, workshops, and hackathons for our guests who share a passion for coding. Keep an eye on the notice board!" << endl << endl;

    cout << "Q14. Can I avail a complimentary workspace during my stay?" << endl;
    cout << "A14. Absolutely! We provide complimentary co-working spaces with high-speed internet for our coding enthusiast guests to work comfortably." << endl << endl;

    cout << "Q15. Is there a gaming lounge in the hotel?" << endl;
    cout << "A15. Yes, we have a dedicated gaming lounge with state-of-the-art setups for guests to relax and enjoy coding-related games." << endl << endl;

    cout << "Q16. What are the breakfast timings?" << endl;
    cout << "A16. Breakfast is served from 7:00 AM to 10:00 AM daily, offering a variety of coding-themed dishes to kickstart your day." << endl << endl;

    cout << "Q17. Can I host coding meetups or conferences at the hotel?" << endl;
    cout << "A17. Certainly! Our hotel provides spacious conference rooms and event venues for coding meetups and conferences. Contact the management to arrange the event." << endl << endl;

    cout << "Q18. Is there a rooftop lounge with a panoramic city view?" << endl;
    cout << "A18. Yes, our rooftop lounge offers a breathtaking view of the city skyline, providing the perfect ambiance for coding and relaxation." << endl << endl;

    cout << "Q19. Are there coding-themed decorations in the rooms?" << endl;
    cout << "A19. Yes, each room is tastefully decorated with coding-themed elements, creating a unique and immersive experience for our coding enthusiast guests." << endl << endl;

    cout << "Q20. Can I access coding-related books or resources during my stay?" << endl;
    cout << "A20. Absolutely! We offer a collection of coding-related books and resources in the library. Feel free to explore and gain knowledge during your stay." << endl << endl;

    cin.get();
    cin.get();
}