// Mahala Covey
// CIS 1202 800
// March 14, 2024

#include <iostream>
#include <fstream>
using namespace std;

const int NAME_SIZE = 40; // Name's size

// Structure declaration
struct Product
{
	long number;
	char name[NAME_SIZE];
	double price;
	int quantity;
};

// Function prototypes
int showMenu();
void createFile(fstream&);
void displayFile(fstream&);
void displayRecord(fstream&, int);
void modifyRecord(fstream&);

int main()
{
	int choice; // User's menu choice
	int recordNum; // Number for record user wants to display

	fstream inventory("inventory.dat", ios::in | ios::out | ios::trunc | ios::binary ); 

	// Test for file errors
	if (!inventory)
	{
		cout << "Error creating or opening the file. Now force quiting the program." << endl;
		return 0;
	}

	// Call createFile 
	createFile(inventory);

	// Handle menu choice
	do
	{
		choice = showMenu();

		switch (choice)
		{
		case 1: // Display the entire inventory
			displayFile(inventory);
			cout << endl;
			break;

		case 2: // Display a particular product
			cout << "Enter record number to be displayed: "; // Get record number
			cin >> recordNum;
			displayRecord(inventory, recordNum);
			cout << endl;
			break;

		case 3: // Modify a program
			modifyRecord(inventory);
			cout << endl;
			break;

		case 4: // Exit the program
			break;
		}
	} while (choice != 4);

	// Close file
	inventory.close();

	return 0;
}

//*****************************************************************************************************************
// The showMenu function displays the menu, gets a choice of type int from the user, validates it to ensure it is *
// within the menu's range, and returns the choice once it is valid.											  *
//*****************************************************************************************************************

int showMenu()
{
	int chosen; // Holds user's menu choice

	// Display menu
	cout << "Product Inventory"
		<< "\n1. Display the entire inventory"
		<< "\n2. Display a particular product"
		<< "\n3. Modify a product"
		<< "\n4. Exit the program";

	// Get menu choice
	cout << "\nPlease enter your choice: ";
	cin >> chosen;

	// Validate menu choice
	while (chosen < 1 || chosen > 4)
	{
		cout << "Invalid choice. Please enter a number 1-4: ";
		cin >> chosen;
	}

	return chosen;
}

//***********************************************************************************************************************
// The createFile function populates the file through the filestream object file parameter with five Product structues. *
//***********************************************************************************************************************

void createFile(fstream &file)
{
	// Initialize records
	Product record1 = { 12345, "Dog", 11.99, 5 };
	Product record2 = { 12, "Cat", 800, 4 };
	Product record3 = { 10101010, "Bird", 0.99, 500 };
	Product record4 = { 784723, "Fish", 49.95, 509 };
	Product record5 = { 1818, "Zebra", 14500, 1 };

	// Write records to file
	file.write(reinterpret_cast<char *>(&record1), sizeof(record1));
	file.write(reinterpret_cast<char *>(&record2), sizeof(record2));
	file.write(reinterpret_cast<char *>(&record3), sizeof(record3));
	file.write(reinterpret_cast<char *>(&record4), sizeof(record4));
	file.write(reinterpret_cast<char *>(&record5), sizeof(record5));
}

//**************************************************************************************************************************
// The displayFile function reads the file through the filestream object file parameter, and displays them to the console. *
//**************************************************************************************************************************

void displayFile(fstream &file)
{
	int recordNum = 0; // Number of a given record
	Product record; // Holds record info to read

	file.clear(); // Clear eof flag
	file.seekg(0L, ios::beg); // Seek first record

	// Read first record
	file.read(reinterpret_cast<char *>(&record), sizeof(record));

	// While not at end of file, display records
	while (!file.eof())
	{
		cout << "Record #" << recordNum << endl;
		cout << "Product number: #" << record.number << endl;
		cout << "Product name: " << record.name << endl;
		cout << "Price: $" << record.price << endl;
		cout << "Quantity: " << record.quantity << endl;
 
		file.read(reinterpret_cast<char *>(&record), sizeof(record)); // Read next record

		recordNum++;
	}
}

//*****************************************************************************************************************************************************************
// The displayRecord function matches the int indicatedRec parameter with a record in the file. The file is read through filestream object file parameter and the *
// matching record's contents are displayed to the console.																										  *
//*****************************************************************************************************************************************************************

void displayRecord(fstream &file, int inicatedRec)
{
	Product record; // Holds record info to read

	file.clear(); // Clear eof flag
	file.seekg(inicatedRec * sizeof(record), ios::beg); // Seek indicated record

	file.read(reinterpret_cast<char*>(&record), sizeof(record)); // Read record

	// Display indicated record contents
	cout << "Product number: #" << record.number << endl;
	cout << "Product name: #" << record.name << endl;
	cout << "Price: $" << record.price << endl;
	cout << "Quantity: " << record.quantity << endl;
}

//****************************************************************************************************************************************************************************
// The modifyRecord function gets the record number the user wants to edit, along with the record's new values. It seeks the record in the file through the filstream object *
// parameter file. Lastly, the record's new values are written to the file and replace the old ones.																		 *
//****************************************************************************************************************************************************************************

void modifyRecord(fstream& file)
{
	int recordNum; // Number for record user wants to modify
	Product record; // Holds record info to write

	cout << "Enter record number to be modified: "; // Get record number
	cin >> recordNum;


	file.clear(); // Clear eof flag
	file.seekp(recordNum * sizeof(record), ios::beg); // Seek indicated record

	// Get new Product values
	cout << "Enter the new data.";
	cout << "\nProduct number: ";
	cin >> record.number;
	cout << "Product name: ";
	cin.ignore(); // Ignore character in keyboard buffer
	cin.getline(record.name, NAME_SIZE);
	cout << "Price: ";
	cin >> record.price;
	cout << "Quantity: ";
	cin >> record.quantity;

	// Write to record
	file.write(reinterpret_cast<char*>(&record), sizeof(record));
}