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
		~Customer() {}
		void print()
		{
			cout << name << "-" << energy << endl;
		}
	};

private:
	int numCustomers;
	int currSizeQueue;
	int jujutsu;
	int jurei;
	int numAfterKick;
	Customer *headTable;
	Customer *curCustomer;
	Customer *headQueue;
	Customer *tailQueue;
	Customer *headOrderQ;
	Customer *tailOrderQ;

public:
	imp_res() : headQueue(nullptr), tailQueue(nullptr), headTable(nullptr), curCustomer(nullptr), headOrderQ(nullptr), tailOrderQ(nullptr), numCustomers(0), currSizeQueue(0), jujutsu(0), jurei(0), numAfterKick(0) {}

	void findMaxDifference(Customer *newCustomer)
	{
		Customer *temp = headTable;
		int curDifference = headTable -> energy;
		curDifference = abs((newCustomer->energy) - (temp->energy));
		Customer *flagCustomer = temp;
		int maxRes = max(maxRes, curDifference);
		temp = temp -> next;
		while (temp -> next != headTable -> next)
		{
			curDifference = abs((newCustomer->energy) - (temp->energy));
			if (curDifference > maxRes)
			{
				maxRes = max(maxRes, curDifference);
				flagCustomer = temp;
			}
			temp = temp->next;
		}
		cout << maxRes << endl;
		int unsignedMaxRes = (newCustomer->energy) - (flagCustomer->energy);
		curCustomer = flagCustomer;
		if (unsignedMaxRes > 0)
		{
			if (numCustomers != MAXSIZE - 1)
			{
				insertToRight(newCustomer);
			}
			else {
				if (curCustomer -> next == headTable){
					curCustomer -> next = newCustomer;
					newCustomer -> prev = curCustomer;
					newCustomer -> next = headTable;
					curCustomer = newCustomer;
					numCustomers++;
				}
				else {
					insertToRight(newCustomer);
					Customer *temp = headTable;
					temp = temp -> next;
					while (temp != headTable)
					{
						temp = temp -> next;
					}
					temp -> next = headTable;
					headTable -> prev = temp;
				}
				// Customer *nextCustomer = curCustomer->next;
				// curCustomer->next = newCustomer;
				// nextCustomer->prev = newCustomer;
				// newCustomer->next = nextCustomer;
				// newCustomer->prev = curCustomer;
				// curCustomer = newCustomer;
				// numCustomers++;
			}
		}
		else
		{
			insertToLeft(newCustomer);
		}
	}
	void printTable()
	{
		// cout << "Print table: " << headTable->next->name << endl;
		Customer *temp = headTable;

		while (temp->next != headTable)
		{
			cout << temp->name << '/' << temp->energy;
			if (temp->next != nullptr)
				cout << " -> ";
			temp = temp->next;
		}
		cout  << temp->name << '/' << temp->energy;
		cout << endl;
	}

	void insertToLeft(Customer *newCustomer){
		// if (this->curCustomer->prev == this->headTable && this->numCustomers > 2){
		// 	this->insertToHead(newCustomer);
		// 	return;
		// } 

		// Get prev node of current customer
		Customer *prevCustomer = curCustomer->prev;

		// Point current customer and prev to new customer, point new customer to cur and prev
		curCustomer->prev = newCustomer;
		prevCustomer->next = newCustomer;
		newCustomer->next = curCustomer;
		newCustomer->prev = prevCustomer;

		// Change current customer
		curCustomer = newCustomer;

		// Increse customer
		numCustomers++;
	}
	void insertToRight(Customer *newCustomer){
		// if (this->curCustomer->next == this->headTable && this->numCustomers > 2){
		// 	this->insertToTail(newCustomer);
		// 	return;
		// } 

		// Get prev node of current customer
		Customer *nextCustomer = curCustomer->next;

		// Point current customer and prev to new customer, point new customer to cur and prev
		curCustomer->next = newCustomer;
		nextCustomer->prev = newCustomer;
		newCustomer->next = nextCustomer;
		newCustomer->prev = curCustomer;

		// Change current customer
		curCustomer = newCustomer;

		// Increse customer
		numCustomers++;
	}
	void insertToHead(Customer *newCustomer)
	{
		// Last element in list
		Customer *lastCustomer = headTable->prev;

		// Connect old head to new head
		headTable->prev = newCustomer;
		newCustomer->next = headTable;

		// Connect new head to current tail
		newCustomer->prev = lastCustomer;
		lastCustomer->next = newCustomer;

		// Change new head
		headTable = newCustomer;

		// Increase num of customers
		numCustomers++;
	}
	void insertToTail(Customer *newCustomer)
	{
		// Last element in list
		Customer *lastCustomer = headTable->prev;

		// Connect to head
		newCustomer->next = headTable;

		// Connect prev to old tail
		newCustomer->prev = lastCustomer;

		// Connect to new tail
		headTable->prev = newCustomer;

		// Connect old tail to new tail
		lastCustomer->next = newCustomer;
		
		// Add flag to new Customer
		curCustomer = newCustomer;
		// cout << "Insert to table: " << curCustomer->name << ' ' << curCustomer->energy << endl;

		// Increase num of customers
		numCustomers++;
	}
	void insertToTable(string name, int energy)
	{
		// cout << "Insert to table: " << name << ' ' << energy << endl;
		// If restaurant just opened right now
		if (numCustomers == 0 || !headTable)
		{
			if (energy != 0)
			{
				Customer *customer = new Customer(name, energy, nullptr, nullptr);

				// Point to itself
				customer->next = customer;
				customer->prev = customer;

				// New head
				headTable = customer;
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
				else if (energy >= curCustomer->energy)
				{
					// cout << "Insert to table != 0: " << endl;
					Customer *newCustomer = new Customer(name, energy, curCustomer, nullptr);

					this->insertToRight(newCustomer);
					// curCustomer->next = newCustomer;
					// curCustomer = curCustomer->next;
					// numCustomers++;
				}
				else if (energy < curCustomer->energy)
				{
					// cout << "\nEnergy < 0\n";
					Customer *newCustomer = new Customer(name, energy, nullptr, curCustomer);

					this->insertToLeft(newCustomer);
					// curCustomer->prev = cus;
					// curCustomer = curCustomer->prev;
					// numCustomers++;
				}
			}
			else if (numCustomers >= MAXSIZE / 2)
			{
				Customer *cus = new Customer(name, energy, nullptr, nullptr);
				this->findMaxDifference(cus);
				// if (numCustomers == MAXSIZE - 1)
				// {
				// 	Customer *temp = headTable;
				// 	while (!temp)
				// 	{
				// 		if (temp)
				// 		{
				// 			temp->next = headTable;
				// 			headTable->prev = temp;
				// 			break;
				// 		}
				// 		temp = temp->next;
				// 	}
				// }
			}
		}
		if (numCustomers >= MAXSIZE)
		{
			Customer *cus = new Customer(name, energy, nullptr, nullptr);
			addCustomerInQueue(cus);
		}
		if (currSizeQueue == 0)
		{
			return;
		}
		else
		{
			Customer *cus = FIFO();
			if (numAfterKick < MAXSIZE / 2)
			{
				if (cus -> energy >= curCustomer -> energy){
					this->insertToTail(cus);
				}
				else this->insertToHead(cus);
			}
			if (numAfterKick > MAXSIZE / 2){
				this -> findMaxDifference(cus);
				if (numCustomers == MAXSIZE - 1)
				{
					Customer *temp = headTable;
					while (!temp)
					{
						if (temp)
						{
							temp->next = headTable;
							headTable->prev = temp;
							break;
						}
						temp = temp->next;
					}
				}
				numCustomers++;
			}
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
		if (newCustomer->energy == 0)
		{
			cout << "Cook luon" << endl;
			return;
		}
		if (currSizeQueue >= MAXSIZE)
		{
			cout << " Het cho roi cook" << endl;
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
				newCustomer->prev = tailQueue;
				tailQueue->next = newCustomer;
				tailQueue = newCustomer;
				currSizeQueue++;
			}
		}
	}
	Customer *FIFO()
	{
		if (numCustomers < MAXSIZE && currSizeQueue <= MAXSIZE)
		{
			if (currSizeQueue == 0 || !headQueue)
			{
				return nullptr;
			}
			else
			{
				Customer *removedCustomer = headQueue;
				headQueue = headQueue->next;
				if (headQueue)
				{
					headQueue->prev = nullptr;
				}
				else
				{
					tailQueue = nullptr;
				}
				removedCustomer->next = nullptr;
				removedCustomer->prev = nullptr;
				currSizeQueue--;
				return removedCustomer;
			}
		}
		return nullptr; // need fix
	}
	void orderOfCustomer(Customer *newCustomer)
	{
		if (!headOrderQ)
		{
			headOrderQ = tailOrderQ = newCustomer;
		}
		else
		{
			newCustomer->prev = tailOrderQ;
			tailOrderQ->next = newCustomer;
			tailOrderQ = newCustomer;
		}
	}
	void kickOutCustomer(int num)
	{
		numAfterKick = numCustomers;
		Customer *temp1 = headOrderQ;
		Customer *temp2 = headTable;
		if (num >= numCustomers)
		{
			num = numCustomers;
		}
		for (int i = 1; i <= num; i++)
		{
			while (temp1 != nullptr && temp2->next != headTable)
			{
				Customer *temp = temp2;
				if (temp2 == headTable)
				{
					temp->next = headTable->next;
					temp->prev = headTable->prev;
					if (headTable->energy > 0)
					{
						headTable = headTable->next;
						headTable->prev = temp->prev;
						curCustomer = headTable;
					}
					if (headTable->energy < 0)
					{
						headTable = headTable->prev;
						headTable->next = temp->next;
						curCustomer = headTable;
					}
					temp2 = temp2->next;
					delete temp;
					numAfterKick--;
				}
				else
				{
					if (temp1->name == temp2->name)
					{
						temp->next = temp2->next;
						temp->prev = temp2->prev;
						if (temp2->energy > 0)
						{
							curCustomer = temp2 -> next;
						}
						if (temp2->energy < 0)
						{
							curCustomer = temp2 -> prev; 
						}
						temp2 = temp2->next;
						delete temp;
						numAfterKick--;
					}
					else
					{
						temp2 = temp2->next;
					}
				}
				temp1 = temp1->next;
			}
		}
	}
	void swapInfo(Customer *cus1, Customer *cus2)
	{
		int tempEnergy = cus1->energy;
		string tempName = cus1->name;
		cus1->energy = cus2->energy;
		cus1->name = cus2->name;
		cus2->energy = tempEnergy;
		cus2->name = tempName;
	}
	void reversalTable()
	{
		Customer *count = headTable;
		Customer *temp1 = headTable;
		Customer *temp2 = headTable;
		Customer *temp3 = headTable;
		Customer *temp4 = headTable;
		while (count->next != headTable)
		{
			if (count->energy > 0)
			{
				jujutsu++;
			}
			else
				jurei++;
			count = count->next;
		}
		while (temp2->energy > 0)
		{
			if (headTable->energy < 0)
				break;
			else
				temp2 = temp2->prev;
		}
		while (temp1->energy > 0)
		{
			if (headTable->energy < 0)
				temp1 = temp1->next;
			else
				temp1 = temp1->next;
		}
		if (jurei > 0)
		{
			while (jurei != 0)
			{
				if (temp1->energy < 0 && temp2->energy < 0)
				{
					this -> swapInfo(temp1, temp2);
					jurei -= 2;
					temp1 = temp1->next;
					temp2 = temp2->next;
				}
				else if (temp1->energy > 0 && temp2->energy > 0)
				{
					temp1 = temp1->next;
					temp2 = temp2->next;
				}
				else if (temp1->energy > 0 && temp2->energy < 0)
				{
					temp1 = temp1->next;
				}
				else
				{
					temp2 = temp2->next;
				}
				if (jurei == 1)
					break;
			}
		}
		while (temp4->energy < 0)
		{
			if (headTable->energy > 0)
				break;
			else
				temp4 = temp4->prev;
		}
		while (temp3->energy < 0)
		{
			if (headTable->energy > 0)
				temp3 = temp3->next;
			else
				temp3 = temp3->next;
		}
		if (jujutsu > 0)
		{
			while (jujutsu != 0)
			{
				if (temp3->energy > 0 && temp4->energy > 0)
				{
					this -> swapInfo(temp3, temp4);
					jurei -= 2;
					temp3 = temp3->next;
					temp4 = temp4->next;
				}
				else if (temp3->energy > 0 && temp4->energy > 0)
				{
					temp3 = temp3->next;
					temp4 = temp4->next;
				}
				else if (temp3->energy > 0 && temp4->energy < 0)
				{
					temp3 = temp3->next;
				}
				else
				{
					temp4 = temp4->next;
				}
				if (jujutsu == 1)
					break;
			}
		}
	}
	void printMinInSubString(){
		Customer *cur = headTable;
		Customer *minStart = nullptr;
		Customer *minEnd = nullptr;
		Customer *curStart = nullptr;
		Customer *curEnd = nullptr;
		int minSum = 2147483647 - 1;
		int curSum = 0;
		if (numCustomers == 0) return;
		while (cur != nullptr){
			if (cur -> energy <= 0){
				curStart = cur -> next;
				curEnd = nullptr;
				curSum = 0;
			}
			else {
				if (curEnd == nullptr){
					curStart = cur;
					curEnd = cur;
					curSum = cur -> energy;
				}
				else {
					curEnd = cur;
					curSum += cur -> energy;
				}
				if (curSum < minSum && curEnd != nullptr && curEnd -> next != nullptr){
					minSum = curSum;
					minStart = curStart;
					minEnd = curEnd;
				}
			}
			cur = cur -> next;
		}
		for (Customer *cus = minStart; cus != minEnd -> next; cus = cus -> next){
			cout << cus -> name << "-" << cus -> energy << endl;
		}
	}

	// void expansionKickOut(){
	// 	Customer *temp1 = headTable;
	// 	Customer *temp2 = headOrderQ;
	// 	int sumJujutsuEnergy = 0;
	// 	int sumJureiEnergy = 0;
	// 	while (temp1 -> next != headTable){
	// 		if (temp1 -> energy > 0) sumJujutsuEnergy += temp1 -> energy;
	// 		else sumJureiEnergy += temp1 -> energy;
	// 		temp1 = temp1 -> next;
	// 	}
	// 	if (sumJujutsuEnergy > abs(sumJureiEnergy)){
	// 		for (int i = 1; i <= numCustomers; i++) {
	// 			if (temp2 -> energy < 0){
	// 				Customer *temp3 = headTable;
	// 				while (temp3 -> next ! headTable) {
	// 					if (temp3 -> name == temp2 -> name){
	// 						cout << temp3 -> name << "-" << temp3 -> energy << endl;
	// 						Customer *temp = temp3;
	// 						temp -> next = temp3 -> next;
	// 						temp -> prev = temp3 -> prev;
	// 						delete temp3;
	// 						break;
	// 					}
	// 					else {
	// 						temp3 = temp3 -> next;
	// 					}
	// 				}
	// 				temp2 = temp2 -> next;
	// 			}
	// 			else temp2 = temp2 -> next;
	// 		}
	// 	}
	// 	else if (sumJujutsuEnergy < abs(sumJureiEnergy)) {
	// 		for (int i = 1; i <= numCustomers; i++) {
	// 			if (temp2 -> energy > 0){
	// 				Customer *temp3 = headTable;
	// 				while (temp3 -> next ! headTable) {
	// 					if (temp3 -> name == temp2 -> name){
	// 						cout << temp3 -> name << "-" << temp3 -> energy << endl;
	// 						Customer *temp = temp3;
	// 						temp -> next = temp3 -> next;
	// 						temp -> prev = temp3 -> prev;
							
	// 						delete temp3;
	// 						break;
	// 					}
	// 					else {
	// 						temp3 = temp3 -> next;
	// 					}
	// 				}
	// 				temp2 = temp2 -> next;
	// 			}
	// 			else temp2 = temp2 -> next;
	// 		}
	// 	}
	
	void RED(string name, int energy)
	{
		// cout << name << " " << energy << endl;
		// cout << MAXSIZE << endl;
		this->insertToTable(name, energy);
		this->printTable();
		// cout << this->numCustomers << endl;
	}
	void BLUE(int num)
	{
		cout << "blue " << num << endl;
		// numAfterKick = numCustomers - num;
		// kickOutCustomer(num);
		// this->printTable();
	}
	void PURPLE()
	{
		cout << "purple" << endl;
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
		// reversalTable();
		// this->printTable();
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



