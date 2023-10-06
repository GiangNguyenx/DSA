// Test push code
// class circularTable : public Restaurant
// {
// protected:
// 	customer *currSeat;

// public:
// 	circularTable(){};
// 	circularTable() : currSeat(nullptr);
// 	void Insert(string name, int energy)
// 	{
// 		int numCus = 0;
// 		while (!(numCus >= MAXSIZE / 2))
// 		{
// 			customer *newCus = new customer(name, energy);
// 			if (currSeat == nullptr)
// 			{
// 				currSeat = newCus;
// 				newCus->next = newCus;
// 				numCus++;
// 			}
// 			else
// 			{
// 				numCus++;
// 				if (newCus->energy > 0)
// 				{
// 					newCus -> next = currSeat -> next;
// 					currSeat -> next = newCus;
// 				}
// 			}
// 		}
// 	}
// }
// void Restaurant :: RED(string name, int energy)
// {
// 	if (energy == 0)
// 		return;
// 	int pos;
// }

#include "main.h"

extern int MAXSIZE; // find MAXSIZE in another cpp / h file

class imp_res : public Restaurant
{
public:
	class Customer
	{
	private:
		string name;
		int energy;
		Customer *prev;
		Customer *next;
		friend class imp_res;

	public:
		Customer() {}
		Customer(string na, int e, Customer *p, Customer *ne) : name(na), energy(e), prev(p), next(ne) {}
		~Customer()
		{
			delete prev;
			delete next;
		}
		void print()
		{
			cout << name << "-" << energy << endl;
		}
	};

private:
	int numCustomers;
	int currSizeQueue;
	Customer *headTable;
	Customer *curCustomer;
	Customer *headQueue;
	Customer *tailQueue;
	Customer *headOrderQ;
	Customer *tailOrderQ;

public:
	imp_res() : headQueue(nullptr), tailQueue(nullptr), headTable(nullptr), curCustomer(nullptr), headOrderQ(nullptr), tailOrderQ(nullptr), numCustomers(0), currSizeQueue(0) {}

	void findMaxDifference(Customer *headTable, Customer *newCustomer)
	{
		Customer *temp = headTable;
		int curDifference = 0;
		Customer *flagCustomer = temp;
		int maxRes = max(maxRes, curDifference);
		while (temp != nullptr)
		{
			curDifference = abs((newCustomer->energy) - (temp->energy));
			if (curDifference > maxRes)
			{
				flagCustomer = temp;
			}
			temp = temp->next;
		}
		int unsignedMaxRes = (newCustomer->energy) - (flagCustomer->energy);
		if (unsignedMaxRes > 0)
		{
			newCustomer->next = flagCustomer->next;
			newCustomer->prev = flagCustomer;
			flagCustomer->next = newCustomer;
		}
		else
		{
			newCustomer->prev = flagCustomer->prev;
			newCustomer->next = flagCustomer;
			flagCustomer->prev = newCustomer;
		}
	}
	void printTable()
	{
		// cout << "Print table: " << headTable->next->name << endl;
		Customer *temp = headTable;

		while (temp)
		{
			cout << temp->name << '/' << temp->energy;
			if (temp->next != nullptr)
				cout << " -> ";
			temp = temp->next;
		}
		cout << endl;
	}
	void insertToTable(string name, int energy)
	{
		// If restaurant just opened right now
		// cout << "Insert to table\n";
		if (numCustomers == 0 || !headTable)
		{
			if (energy != 0)
			{
				Customer *cus = new Customer(name, energy, nullptr, nullptr);
				headTable = cus;
				curCustomer = headTable;
				numCustomers++;
			}
		}
		else
		{
			if (numCustomers < MAXSIZE / 2)
			{
				if (energy == 0)
				{
					cout << "Cut ra ngoai" << endl;
					/* code */
				}
				else if (energy > 0)
				{
					Customer *cus = new Customer(name, energy, curCustomer, nullptr);

					// cout << "Insert to table != 0: " << curCustomer->next->name << endl;
					curCustomer->next = cus;
					curCustomer = curCustomer->next;
					numCustomers++;
				}
				else if (energy < 0)
				{
					// cout << "\nEnergy < 0\n";
					Customer *cus = new Customer(name, energy, nullptr, curCustomer);
					curCustomer->prev = cus;
					curCustomer = curCustomer->prev;
					numCustomers++;
				}
			}
			else
			{
				Customer *cus = new Customer(name, energy, nullptr, nullptr);
				findMaxDifference(headTable, cus);
				if (numCustomers == MAXSIZE - 1){
					Customer *temp = headTable;
					while(!temp){
						if(temp){
							temp -> next = headTable;
							headTable -> prev = temp;
							break;
						}
						temp = temp -> next;
					}
				}
				numCustomers++;
			}
		}
		if (numCustomers >= MAXSIZE / 2  && currSizeQueue)
		if (numCustomers >= MAXSIZE)
		{
			Customer *cus = new Customer(name, energy, nullptr, nullptr);
			addCustomerInQueue(cus);
		}
	}
	void checkNameOfCustomer(string name, int energy)
	{
		Customer *temp = headTable;
		Customer *newCustomer = new Customer(name, energy, nullptr, nullptr);
		while (temp != nullptr)
		{
			if (newCustomer->name == temp->name)
			{
				cout << "Cook" << endl;
			}
			else
			{
				insertToTable(name, energy);
				break;
			}
			temp = temp->next;
		}
	}
	void addCustomerInQueue(Customer *newCustomer)
	{
		if (currSizeQueue >= MAXSIZE)
		{
			cout << " Het cho roi cook";
			return;
		}
		else
		{
			if (currSizeQueue == 0 || !headQueue)
			{
				headQueue = tailQueue = newCustomer;
				currSizeQueue++;
			}
			else
			{
				newCustomer->prev= tailQueue;
				tailQueue -> next = newCustomer;
				tailQueue = newCustomer;
				currSizeQueue++;
			}
		}
	}
	Customer FIFO(){
		if (currSizeQueue == 0 || !headQueue){
			return nullptr;
		}
		else {
			Customer *removedCustomer = headQueue;
			headQueue = headQueue -> next;
			if (headQueue){
				headQueue -> prev = nullptr;
			}
			else {
				tailQueue = nullptr;
			}
			removedCustomer -> next = nullptr;
			removedCustomer -> prev = nullptr;
			currSizeQueue--;
			return *removedCustomer;
		}
	}
	Customer orderOfCustomer(Customer *newCustomer){
		if (currSizeOrderQ == 0 || !headOrderQ)
			{
				headOrderQ = tailOrderQ = newCustomer;
			}
		else
			{
				newCustomer->prev= tailOrderQ;
				tailOrderQ -> next = newCustomer;
				tailOrderQ = newCustomer;
			}
	}
	void kickOutCustomer(int num){
		// if (num == 1) {
		// 	Customer *temp = headTable;
		// 	temp -> next = headTable -> next;
		// 	temp -> prev = headTable -> prev;
		// 	if (headTable -> energy > 0){
		// 		headTable = headTable -> next;
		// 		headTable -> prev = temp -> prev;
		// 	}
		// 	if (headTable -> energy < 0){
		// 		headTable = headTable -> prev;
		// 		headTable -> next = temp -> next;
		// 	}
		// 	delete temp;
		// }
		Customer *temp1 = headOrderQ;
		Customer *temp2 = headTable;
		for (int i = 1; i <= num; i++){
			while (temp1 != nullptr && temp2 -> next != headTable){
				Customer *temp = temp2;
				if (temp2 == headTable){
					temp -> next = headTable -> next;
					temp -> prev = headTable -> prev;
					if (headTable -> energy > 0){
						headTable = headTable -> next;
						headTable -> prev = temp -> prev;
					}
					if (headTable -> energy < 0){
						headTable = headTable -> prev;
						headTable -> next = temp -> next;
					}
					temp2 = temp2 -> next;
					delete temp;
				}
				else {
					if (temp1 -> name == temp2 -> name){
						temp -> next = temp2 -> next;
						temp -> prev = temp2 -> prev;
						temp2 = temp2 -> next;
						delete temp;
					}
					else {
						temp2 = temp2 -> next;
					}
				}
				temp1 = temp1 -> next;
			}
		}
	}
	void RED(string name, int energy)
	{
		// cout << name << " " << energy << endl;
		// cout << MAXSIZE << endl;
		this->insertToTable(name, energy);
		// this->printTable();
		// // If restaurant just opened right now
		// if (numCustomers == 0 || !headTable){
		// 	if (energy != 0) {
		// 		Customer *cus = new Customer (name, energy, nullptr, nullptr);
		// 		headTable = cus;
		// 		temp = headTable;
		// 		numCustomers++;
		// 	}
		// }
		// else {
		// 	if (energy == 0)
		// 	{
		// 		/* code */
		// 	}
		// 	else if (energy < 0) {
		// 		Customer *cus = new Customer(name, energy, temp, nullptr);
		// 		numCustomers++;
		// 	}
		// 	else if (energy > 0) {
		// 		Customer *cus = new Customer(name, energy, nullptr, temp);
		// 		numCustomers++;
		// 	}
		// }
	}
	void BLUE(int num)
	{
		cout << "blue " << num << endl;
	}
	void PURPLE()
	{
		cout << "purple" << endl;
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
	}
	void LIGHT(int num)
	{
		cout << "light " << num << endl;
	}
};