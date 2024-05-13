/*
* Date	22/04/2024
* Programming : C++
* Developer : Roeun keovisal
*/
#include<iostream>
#include<string>
#include<algorithm> // For sorting
#include <fstream> // Function to register into file
#define forLoop(count) for(int i=0;i<count;i++)

using namespace std;

enum Gender { Male=1, Female, Other };
enum Position { Manager=1, Developer, Sales };

//Role for user login
enum UserRole {
	ADMIN,
	USER

};
//Declear struct for user login and register
struct User {
	string username;
	string password;
	UserRole role;
};

//Declear a structure id/name of Item
struct Data {
	int id;
	string name;
};
//Declear a strcuture for address employee
struct address {
	int addressNo;
	string addressHouse;
	string addresscity;

};

//Declear a structure for Item
struct Item {
	Data data;
	float price;
	int quantity;
	double total;

	//Comparative for sorting items by id
	static bool compareByID(const Item& a, const Item& b) {
		return a.data.id < b.data.id;
	}
	static bool compareByName(const Item& a, const Item& b) {
		return a.data.name < b.data.name;
	}
};
struct DateOfBirth {
	int day;
	int month;
	int year;
};
struct Person {
	struct {
		int id;
		string name;
	};
	Gender gender;
	DateOfBirth DOB;
	Position position;
	float salary;

};

enum Menu {
	EXIT,
	ADD,
	VIEW,
	UPDATE,
	SEARCH,
	SORT,
	Delete,
	BACK
};

string getPosition(Position &position) {
	switch (position)
	{
	case Manager:
		return "Manager";
	case Developer:
		return "Developer";
	case Sales:
		return "Sales";
	default:
		return "Unknow";
	}
	return "Unspecified";
}
string getGender(Gender &gender) {
	switch (gender)
	{
		case Male:
			return "Male";
		case Female:
			return "Female";
		case Other:
			return "Other";
		default:
			return "Unknown";
	}
	return "Unspecified";
}

void getMenuUser();
void getMenuAdmin();
int getChoice();
template <typename T>
T getNumber(const string& message = 0);
string getString(const string& message = 0);
//bool validateLogin(const string& username, const string& password);
void addProduct();
void viewProduct();
void updateProduct();
void searchProduct();
void sortProduct();
void app();
void deleteProduct();
bool isDuplicateID(Person person[], int count, int id);
bool isDuplicateID(int& id);
void registerUser(User users[], int& userCount);
bool loginUser(User users[], int userCount, UserRole& userRole);
void adminControl();
void hireEmployee(Person person[],int& count);
void viewEmployee(Person person[], const int& count);
void welcomeFunction();
bool readUserFromFile(User users[], int& userCount, const string& username, const string& password, UserRole& userRole);
void updateEmployee(Person person[], const int& count);
void searchEmployee(Person person[], const int& count);
void displayEmployeeHeader();
void displayEmployee(Person& person);
void bubbleSort(Person person[], int count);
void deleteEmployee(Person person[], int& count);

const int MAX_SIZE = 100;
Item items[MAX_SIZE];
int itemCount = 0;

int main() {

	User users[MAX_SIZE];
	int userCount = 0;
	bool loggedIn = false;
	UserRole currentUserRole;
	int choice;

	do {
		welcomeFunction();
		// Display menu options
		cout << "WELCOME TO MAKERT MANAGEMENT SYSTEM" << endl;
		cout << "=== AUTHORIZATION MENU ===" << endl;
		cout << "1. Register" << endl;
		cout << "2. Login" << endl;
		cout << "3. Quit" << endl;
		choice = getChoice();
		switch (choice) {
		case 1:
			registerUser(users, userCount);
			system("cls");
			break;
		case 2:
			loggedIn = loginUser(users, userCount, currentUserRole);
			if (loggedIn) {
				if (currentUserRole == ADMIN) {
					system("cls");
					adminControl();
				}
				else {
					system("cls");
					app();
				}
			}
			else {
				cout << "Login failed. Invalid username or password." << endl;
			}
			break;
		case 3:
			exit(0);
			cout << "Exiting program." << endl;
			break;
		default:
			cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
		}
	} while (choice != 3);

	return 0;
}
//Function check ID if already taken of employee
bool isDuplicateID(Person person[], int count, int id) {
	forLoop(count) {
		if (person[i].id == id) {
			return true;
		}
	}
	return false;
}
//Function check ID if already taken of product
bool isDuplicateID(int &id) {
	for (int i = 0; i < itemCount; i++) {
		if (items[i].data.id == id) {
			return true;
		}
	}
	return false;
}
//Function first opening
void welcomeFunction() {

	cout << "---------------------------------------------------------" << endl;
	cout << "\t\t MAKERT MANAGENMENT SYSTEM " << endl;
	cout << "\t\t\t(Version 0.1)" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "MADE BY : ROEUN KEOVISAL" << endl;
	cout << "FT SD E 17, PROJECT C++\n" << endl;
}
//Function admin menu 
void getMenuAdmin() {
	cout << "======== WELCOME TO ADMIN MENU =======" << endl
		<< "| 1. Hire the employee" << endl
		<< "| 2. Display list information" << endl
		<< "| 3. Update the employee information" << endl
		<< "| 4. Search employee information" << endl
		<< "| 5. Sort list information" << endl
		<< "| 6. Delete the employee" << endl
		<< "| 7. Back to login menu" << endl
		<< "| 0. Exiting program" << endl
		<< "------------------------------------" << endl;
}

//Function menu in product
void getMenuUser() {

	cout << "======== WELCOME TO PRODUCT MENU =======" << endl
		<< "| 1. Add the product" << endl
		<< "| 2. Display the product" << endl
		<< "| 3. Update the prouduct" << endl
		<< "| 4. Search the product" << endl
		<< "| 5. Sort" << endl
		<< "| 6. Delete"<<endl
		<< "| 7. Back to login menu" << endl
		<< "| 0. Exiting program" << endl
		<< "------------------------------------" << endl;
}

void displayEmployeeHeader() {
	cout << "================ DISPLAY EMPLOYEE INFORMATION LIST =======================" << endl
		<< "ID \t Name \t Gender \t Date of Birth \t Position \t Salary " << endl
		<< "----------------------------------------------------------------------------" << endl;

}

//Function input number (int ,float ,double...)
template <typename T>
T getNumber(const string& message) {
	T number = T();
	cout << message;
	while (!(cin >> number)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input, Enter again..!\n" << message;
	}
	return number;
}

//Function use for geting string Input
string getString(const string& message) {
	string text;
	cout << message;
	cin.ignore();
	getline(cin, text);
	return text;
}

//Function for geting option choice
int getChoice() {
	return getNumber<int>("Choose an option: ");
}

//Function display employee information
void displayEmployee(Person& person) {
	cout << person.id << "\t"
		<< person.name << "\t"
		<< getGender(person.gender) << "\t\t"
		<< person.DOB.day << "/"
		<< person.DOB.month << "/" << person.DOB.year << "\t"
		<< getPosition(person.position) << "\t\t"
		<< person.salary << "$" << endl;
}


// Function to write user data to a file during registration
void writeUserToFile(const User& newUser) {
	ofstream outFile("users.txt", ios::app); // Open file in append mode
	if (outFile.is_open()) {
		// Write user data to file
		outFile << newUser.username << " " << newUser.password << " " << newUser.role << endl;
		outFile.close(); // Close file
		cout << "User registered successfully!" << endl;
	}
	else {
		cout << "Error: Unable to open file for writing." << endl;
	}
}

// Function to read user data from a file during login
bool readUserFromFile(User users[], int& userCount, const string& username, const string& password, UserRole& userRole) {
	ifstream inFile("users.txt");
	if (inFile.is_open()) {
		string fileUsername, filePassword;
		int fileRole;
		while (inFile >> fileUsername >> filePassword >> fileRole) {
			if (fileUsername == username && filePassword == password) {
				userRole = static_cast<UserRole>(fileRole);
				return true; // Login successful
			}
		}
		inFile.close(); // Close file
	}
	else {
		cout << "Error: Unable to open file for reading." << endl;
	}
	return false; // Login failed
}

// Updated function for user registration
void registerUser(User users[], int& userCount) {
	const int MAX_USERNAME_LENGTH = 20;
	const int MAX_PASSWORD_LENGTH = 20;

	if (userCount < MAX_SIZE) {
		User newUser;
		cout << "Enter username: ";
		cin >> newUser.username;
		cout << "Enter password: ";
		cin >> newUser.password;

		int roleInput;
		cout << "Enter role (1 for ADMIN or 2 for USER): ";
		cin >> roleInput;

		if (roleInput == 1) {
			newUser.role = ADMIN;
		}
		else {
			newUser.role = USER;
		}

		// Write user data to file
		writeUserToFile(newUser);

		userCount++;
	}
	else {
		cout << "Cannot register more users. Maximum limit reached." << endl;
	}
}

//function for login
bool loginUser(User users[], int userCount, UserRole& userRole) {
	string username, password;
	int attempts = 3;
	while (attempts > 0) {
		cout << "WELCOME TO LOGIN MENU" << endl;
		cout << "--------------------------" << endl;
		cout << "Enter username: ";

		cin >> username;
		cout << "Enter password: ";
		cin>>password;
		
		if (readUserFromFile(users, userCount, username, password, userRole)) {
			cout << "Login successful!" << endl;
			return true;
		}
		else {
		
			attempts--;
			cout << "Invalid username or password. Please try again." << endl;
		}
	}
	// Read user data from file and check for login credentials
	cout << "you're have been blocked, so many incorrect INPUT!!" << endl;
	exit(0);
}


//Function admin control all of employee information
void adminControl() {
	int choice;
	Person person[MAX_SIZE];
	int count = 0;

	while(true){
		getMenuAdmin();
		choice = getChoice();

		switch (choice) {
		case ADD: hireEmployee(person,count); 
			break;
		case VIEW: viewEmployee(person, count); 
			break;
		case UPDATE: updateEmployee(person, count); 
			break;
		case SEARCH: searchEmployee(person, count);
			break;
		case SORT: bubbleSort(person, count);
			break;
		case Delete: deleteEmployee(person, count);
			break;
		case EXIT:
			exit(0);
			cout << "Exit program!!" << endl;
		case 7: 
			system("cls");
			main();
		default:
			cout << "Invalid input, try again..!" << endl;
			break;
		}
		cout << "\nPress enter to continue...";
		cin.get();
		cin.ignore();
		system("cls");
	} 
}

//Function product that's employee can control an option 
void app() {
	int choice;
	do {
		getMenuUser();//Call function menu of product
		choice = getChoice();

		switch (choice) {
		case ADD: addProduct(); 
			break;
		case VIEW:	viewProduct(); 
			break;
		case UPDATE: updateProduct(); 
			break;
		case SEARCH: searchProduct(); 
			break;
		case SORT:  sortProduct(); 
			break;
		case Delete: deleteProduct();  
			break;
		case BACK: system("cls"); main(); 
			break;
		case EXIT:
			exit(0);
			cout << "Exit program!!" << endl;
		default:
			cout << "Invalid input, try again..!" << endl;
			break;
		}
		cout << "Press any key to continue..!!" ;
		cin.get();
		cin.ignore();
		system("cls");

	} while (choice != 0);
}

//Function that's add new employee
void hireEmployee(Person person[],int& count) {
	int addEmployee = getNumber<int>("How to many employee to hire: ");
	forLoop(addEmployee) {
		if (count < MAX_SIZE) {
			cout << "================ Add new Employee ===============" << endl;
			int id;
			do {
				id = getNumber<int>("Enter the ID (3 digits): ");
				if (id < 100 || id > 999) {
					cout << "ID MUST BE EXACTLY 3 DIGITS." << endl;
				}
				else if (isDuplicateID(person, count, id)) {
					cout << "ID already exists. Please enter a unique ID." << endl;
				}
				else {
					break;
				}
			} while (true);

			person[count].id = id;
			person[count].name = getString("Enter employee name: ");
			person[count].gender = static_cast<Gender>(getNumber<int>("ENTER GENDER:\n\t1.Male \n\t2.Female\n\t3.Other\nChoice one: "));
			cout << "Enter employee DOB (dd/mm/yyyy):\n";
			person[count].DOB.day = getNumber<int>("Day  : ");
			person[count].DOB.month = getNumber<int>("Month: ");
			person[count].DOB.year = getNumber<int>("Year : ");
			person[count].position = static_cast<Position>(getNumber<int>("ENTER POSITION:\n\t1.Manager \n\t2.Developer\n\t3.Sales\nChoice one: "));
			person[count].salary = getNumber<double>("Enter employee salary: ");
			count++; // Increment the count
		}
		else {
			cout << "-----------------------------------------------------------" << endl;
			cout << "Cannot add more information, maximum limit reached." << endl;
		}

	}

}

//Function view employee information list
void viewEmployee(Person person[],const int& count) {
	if (count == 0) {
		cout << "NO INFORMATION TO DISPLAY...!!" << endl;
		return;
	}
	else {
		displayEmployeeHeader();
		forLoop(count){
			displayEmployee(person[i]);
		}
	}
}
//Function Update employee informatio list
void updateEmployee(Person person[], const int& count) {
	bool valid = false;

	cout << "................. UPDATE OPTION .............." << endl;
	int searchID = getNumber<int>("Enter id to search the employee: ");
	forLoop(count) {
		if (person[i].id == searchID) {
			// Update the employee's information
			valid = true;
			int id;
			do {
				id = getNumber<int>("Enter the ID (3 digits): ");
				if (id < 100 || id > 999) {
					cout << "ID MUST BE EXACTLY 3 DIGITS." << endl;
				}
				else {
					break;
				}
			} while (true);

			person[i].id = id;
			person[i].name = getString("Enter employee name: ");
			person[i].gender = static_cast<Gender>(getNumber<int>("ENTER GENDER:\n\t1.Male \n\t2.Female\n\t3.Other\nChoice one: "));
			cout << "Enter employee DOB (dd/mm/yyyy):\n";
			person[i].DOB.day = getNumber<int>("Day  : ");
			person[i].DOB.month = getNumber<int>("Month: ");
			person[i].DOB.year = getNumber<int>("Year : ");
			person[i].position = static_cast<Position>(getNumber<int>("ENTER POSITION:\n\t1.Manager \n\t2.Developer\n\t3.Sales\nChoice one: "));
			person[i].salary = getNumber<double>("Enter employee salary: ");

			cout << "Employee information updated successfully." << endl;
			break;
		
		}
	
	}
	if (!valid) { // If no employee was found after searching all items
		cout << "No employee found with ID: " << searchID << endl;
	}
}


void searchEmployee(Person person[], const int& count) {
	bool flag = false;
	int choice;
	cout << "................. SEARCH OPTION .............." << endl;
	int searchID = getNumber<int>("Enter id to search employee : ");
	forLoop(count) {
		if (person[i].id == searchID) {
			if (!flag) {
				cout << "Search Found : "<<searchID << endl;
				displayEmployeeHeader();
				flag = true;
			}
			//Display employee found 
			displayEmployee(person[i]);
			//adminControl();
		}
	}
	if (!flag) {
		cout << "No employee found with ID: " << searchID << endl;
	}
	/*
	* do {
		cout << "................. SEARCH OPTION .............." << endl;
		cout << " 1| Search by ID" << endl;
		cout << " 2| Search by Name" << endl;
		cout << " 3| Back to Main Menu" << endl;
		choice = getChoice();

		switch (choice)
		{
		case 1: {
			int searchID = getNumber<int>("Enter id to search employee : ");
			forLoop(count) {
				if (person[i].id == searchID) {
					if (!flag) {
						displayEmployeeHeader();
						flag = true;
					}
					//Display employee found 
					displayEmployee(person[i]);
					adminControl();
				}
			}
			if (!flag) {
				cout << "No employee found with ID: " << searchID << endl;
			}break;
		}
		case 2: {
			string searchName = getString("Enter employee name to search : ");
			forLoop(count) {
				if (person[i].name == searchName) {
					if (!flag) {
						displayEmployeeHeader();
						
						
						flag = true;
					}
					//Display employee found 
					displayEmployee(person[i]);
					adminControl();
				}
			}
			if (!flag) {
				cout << "No employee found with ID: " << searchName<< endl;
			}
			break;

		}
		case 3:
			adminControl();
			break;
		default:
			cout << "Invalid input, Please try again!!" << endl;
			break;
		}
		
	} while (choice != 0);
	*/
	
}

//Function for sort information employee by ID
void bubbleSort(Person person[], int count) {
	bool swapped;
	if (count == 0) {
		cout << "------------------------------------" << endl;
		cout << "No information employee to sort..!!" << endl;
	}
	else {		
		do {
			swapped = false;
			for (int i = 0; i < count - 1; i++) {
				if (person[i].id > person[i + 1].id) {
					// Swap the Person records
					Person temp = person[i];
					person[i] = person[i + 1];
					person[i + 1] = temp;
					swapped = true;
				}
			}
		} while (swapped);
		cout << "------------------------------------" << endl;
		cout << "The information has been sorted..!" << endl;
	}
	
}
//Function that's delete employee 
void deleteEmployee(Person person[],int& count) {
	bool found = false;
	cout << "................. DELETE OPTION .............." << endl;
	int idToDelete = getNumber<int>("Enter ID to fire employee: ");

	// Find the index of the employee to delete
	forLoop(count) {
		if (person[i].id == idToDelete) {
			found = true;
			char confirmation;
			cout << "Are you sure you want to delete employee with ID " << idToDelete << "? (yes/no): ";
			cin >> confirmation;
			if (confirmation == 'y' || confirmation == 'Y') {
				for (int j = i; j < count - 1; j++) {
					person[j] = person[j + 1];
				}
				count--;
				cout << "Employee with ID " << idToDelete << " has been deleted." << endl;
			}
			else {
				cout << "Deletion cancelled." << endl;
			}
			break;
		}
	}
	if (!found) {
		cout << "-----------------------------------" << endl;
		cout << "No employee found with ID: " << idToDelete << endl;
	}

}


//Function add product data 
void addProduct() {
	bool valid = false;
	cout << "................. ADDITION PRODUCT .............." << endl;
	int numberOfProducts = getNumber<int>("Enter the number of products to add: ");
	for (int i = 0; i < numberOfProducts; ++i) {
		valid = true;
		if (itemCount >= MAX_SIZE) {
			cout << "Inventory is full! Cannot add more products." << endl;
			break;
		}

		cout << "Adding product " << itemCount + 1 << endl;
		int id = 0;
		do {
			id = getNumber<int>("Enter the item ID (3 digits): ");
			if (id < 100 || id > 999) {//check input only 3digit
				cout << "ID must be exactly 3 digits." << endl;
			}
			else if (isDuplicateID(id)) { // ID if already taken
				cout << "ID already exists. Please enter a unique ID." << endl;
			}
			else {
				break;
			}
		} while (true);

		items[itemCount].data.id = id;
		items[itemCount].data.name = getString("Enter the item name: ");
		items[itemCount].price = getNumber<float>("Enter the item price: ");
		items[itemCount].quantity = getNumber<int>("Enter the item quantity: ");
		items[itemCount].total = items[itemCount].price * items[itemCount].quantity;
		itemCount++;
	}

	if (valid) {
		cout << "--------------Message-------------" << endl;
		cout << "The product has been added!" << endl;
		cout << "----------------------------------" << endl;
	}
	else {
		cout << "-----------------------" << endl;
		cout << "Incorrect Input, Please try again!" << endl;
	}
}

//Function for view all product informations
void viewProduct() {
	if (itemCount > 0) {
		cout << "................. DISPLAY PRODUCT .............." << endl;
		cout << ">> View all product information list << " << endl
			<< "ID \t Name \t Price \t Quantity \t Total " << endl
			<< "----------------------------------------------" << endl;
		forLoop(itemCount) {
			cout << items[i].data.id << "\t"
				<< items[i].data.name << "\t "
				<< items[i].price << "\t\t"
				<< items[i].quantity << "\t"
				<< items[i].total << "$" << endl;
		}
	}
	else {
		cout << "No product to display!" << endl;
	}

}

// Function to search for update an Item by ID
void updateProduct() {
	cout << "................. UPDATE PRODUCT .............." << endl;
	int id = getNumber<int>("Enter ID to update : ");
	// Check if the entered ID is valid
	if (id <= 0 || id < itemCount) {
		cout << "Invalid product ID!" << endl;
		return;
	}

	// Find the product with the given ID
	forLoop(itemCount) {
		if (items[i].data.id == id) {
			cout << "Updating product " << id << endl;
			items[i].data.id = getNumber<int>("Enter new item ID: ");
			items[i].data.name = getString("Enter new item name: ");
			items[i].price = getNumber<float>("Enter new item price: ");
			items[i].quantity = getNumber<int>("Enter new item quantity: ");
			items[i].total = items[i].price * items[i].quantity;
			cout << "Product details updated successfully!" << endl;
			return; // Exit the function after updating the product
		}
	}

	// If the loop completes without finding the product
	cout << "Product with ID " << id << " not found!" << endl;
		
}

//Function search for product data 
void searchProduct() {
	cout << "................. SEARCH PRODUCT .............." << endl;
	bool valid = false;
	int searchID = getNumber<int>("Enter id to search the product: ");

	forLoop (itemCount) {
		if (items[i].data.id == searchID) {
			if (!valid) {
				cout << "Search was found: " << searchID << endl;
				cout << "-------------------------------------" << endl;
				cout << ">> View all product information list <<" << endl
					<< "ID \t Name \t Price \t Quantity \t Total" << endl
					<< "----------------------------------------------" << endl;
				valid = true;
			}
			// Display the found item
			cout << items[i].data.id << "\t"
				<< items[i].data.name << "\t "
				<< items[i].price << "\t\t"
				<< items[i].quantity << "\t"
				<< items[i].total << "$" << endl;
		}

	}
	if (!valid) { //If no product was fount after searching all items
		cout << "No items found with ID: " << searchID << endl;
	}
}
// Function for sorting Product an item
void sortProduct() {
	if (itemCount > 0) {
		int choice;
		do {
			cout << "---- Sort Options ----" << endl;
			cout << "1.Sort by ID" << endl;
			cout << "2.Sort by name" << endl;
			cout << "3.Back Menu" << endl;
			choice = getChoice();
			switch (choice)
			{
				case 1:
					sort(items, items + itemCount, Item::compareByID); //use static bool in structure compare by ID to sort
					cout << "The product has been sorted..!" << endl;
					break;
				case 2:
					sort(items, items + itemCount, Item::compareByName); //use static bool in structure compare by name to sort
					cout << "The product has been sorted..!" << endl;
					break;
				default:
					cout << "Invalid input, Please try again.!!" << endl;
					break;
			}

		} while (choice != 0);
		
	}
	else {
		cout << "------------------------" << endl;
		cout << "No product to sort!" << endl;
	}
}

//Function search ID for delete an product Item
void deleteProduct() {
	cout << "................. DELETE PRODUCT .............." << endl;
	int deleteID = getNumber<int>("Enter ID of the employee to delete: ");
	bool foundByID = false;
	forLoop(itemCount) {
		if (items[i].data.id == deleteID) {
				foundByID = true;			
			char confirmation;
			cout << "Are you sure you want to delete product with ID " << deleteID << "? (yes/no): ";
			cin >> confirmation;
			if (confirmation == 'y' || confirmation == 'Y') {
				for (int j = i; j < itemCount - 1;j++) {
					items[j] = items[j + 1];
				}
				itemCount--;
				cout << "product with ID " << deleteID << " has been deleted." << endl;
			}
			else {
				cout << "Deletion cancelled." << endl;
			}
			break; // Exit loop once the employee is found (or not)
		}
	}
	if (!foundByID) {
		cout << "-----------------------------------" << endl;
		cout << "No product found with ID: " << deleteID << endl;
	}
}