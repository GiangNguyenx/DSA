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
	// Customer *curCustomer;
	Customer *curCustomer;
	Customer *headQueue;
	Customer *tailQueue;
	Customer *headOrderQ;
	Customer *tailOrderQ;

public:
	imp_res() : headQueue(nullptr), tailQueue(nullptr), curCustomer(nullptr), headOrderQ(nullptr), tailOrderQ(nullptr), numCustomers(0), currSizeQueue(0), jujutsu(0), jurei(0), numAfterKick(0) {}

	Customer* findMaxDifference(Customer *newCustomer, int& rootDiff){
		Customer *temp = curCustomer;
		Customer *flagCustomer = temp;
		int rootCurDifference = newCustomer->energy - temp->energy;
		int curDifference = abs(rootCurDifference);
		int maxRes = curDifference;

		temp = temp->next;

		while (temp != curCustomer){
			rootCurDifference = newCustomer->energy - temp->energy;
			curDifference = abs(rootCurDifference);

			if (curDifference > maxRes){
				maxRes = curDifference;
				flagCustomer = temp;
			}

			temp = temp->next;
		}

		rootDiff = rootCurDifference;
		// cout << flagCustomer->name << endl;
		return flagCustomer;
	}
	void findMaxDifference(Customer *newCustomer)
	{
		Customer *temp = curCustomer;
		int curDifference = curCustomer -> energy;
		curDifference = abs((newCustomer->energy) - (temp->energy));
		Customer *flagCustomer = temp;
		int maxRes = max(maxRes, curDifference);
		temp = temp -> next;
		while (temp -> next != curCustomer -> next)
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
				insertToRight(newCustomer, curCustomer);
			}
			else {
				if (curCustomer -> next == curCustomer){
					curCustomer -> next = newCustomer;
					newCustomer -> prev = curCustomer;
					newCustomer -> next = curCustomer;
					curCustomer = newCustomer;
					numCustomers++;
				}
				else {
					insertToRight(newCustomer, curCustomer);
					Customer *temp = headTable;
					temp = temp -> next;
					while (temp != curCustomer)
					{
						temp = temp -> next;
					}
					temp -> next = curCustomer;
					curCustomer -> prev = temp;
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
			if (numCustomers != MAXSIZE - 1)
			{
				insertToLeft(newCustomer, curCustomer);
			}
			else {
				// if (curCustomer == curCustomer){
				// 	curCustomer -> prev = newCustomer;
				// 	newCustomer -> next = curCustomer;
				// 	newCustomer -> next = curCustomer;
				// 	curCustomer = newCustomer;
				// 	numCustomers++;
				// }
				// else {
				// 	insertToRight(newCustomer);
				// 	Customer *temp = curCustomer;
				// 	temp = temp -> next;
				// 	while (temp != curCustomer)
				// 	{
				// 		temp = temp -> next;
				// 	}
				// 	temp -> next = curCustomer;
				// 	curCustomer -> prev = temp;
				// }
		}
	}
	}
	void printTable()
	{
		// cout << "Print table: " << headTable->next->name << endl;
		Customer *temp = curCustomer;

		while (temp->next != curCustomer)
		{
			cout << temp->name << '/' << temp->energy;
			if (temp->next != nullptr)
				cout << " -> ";
			temp = temp->next;
		}
		cout  << temp->name << '/' << temp->energy;
		cout << endl;
	}

	void insertToLeft(Customer *newCustomer, Customer *flagPostion){
		// Get prev node of current customer
		Customer *prevCustomer = flagPostion->prev;

		// Point current customer and prev to new customer, point new customer to cur and prev
		flagPostion->prev = newCustomer;
		prevCustomer->next = newCustomer;
		newCustomer->next = flagPostion;
		newCustomer->prev = prevCustomer;

		// Change current customer
		curCustomer = newCustomer;

		cout << curCustomer->next->name << endl;
		// Increse customer
		numCustomers++;
	}
	void insertToRight(Customer *newCustomer, Customer *flagPostion){
		// Get prev node of current customer
		Customer *nextCustomer = flagPostion->next;

		// Point current customer and prev to new customer, point new customer to cur and prev
		flagPostion->next = newCustomer;
		nextCustomer->prev = newCustomer;
		newCustomer->next = nextCustomer;
		newCustomer->prev = flagPostion;

		// Change current customer
		curCustomer = newCustomer;

		// Increse customer
		numCustomers++;
	}
	// void insertToHead(Customer *newCustomer)
	// {
	// 	// Last element in list
	// 	Customer *lastCustomer = curCustomer->prev;

	// 	// Connect old head to new head
	// 	curCustomer->prev = newCustomer;
	// 	newCustomer->next = curCustomer;

	// 	// Connect new head to current tail
	// 	newCustomer->prev = lastCustomer;
	// 	lastCustomer->next = newCustomer;

	// 	// Change new head
	// 	curCustomer = newCustomer;

	// 	// Increase num of customers
	// 	numCustomers++;
	// }
	// void insertToTail(Customer *newCustomer)
	// {
	// 	// Last element in list
	// 	Customer *lastCustomer = curCustomer->prev;

	// 	// Connect to head
	// 	newCustomer->next = curCustomer;

	// 	// Connect prev to old tail
	// 	newCustomer->prev = lastCustomer;

	// 	// Connect to new tail
	// 	curCustomer->prev = newCustomer;

	// 	// Connect old tail to new tail
	// 	lastCustomer->next = newCustomer;
		
	// 	// Add flag to new Customer
	// 	curCustomer = newCustomer;
	// 	// cout << "Insert to table: " << curCustomer->name << ' ' << curCustomer->energy << endl;

	// 	// Increase num of customers
	// 	numCustomers++;
	// }
	void insertToTable(string name, int energy)
	{
		Customer *newCustomer = new Customer(name, energy, nullptr, nullptr);
		// cout << numCustomers << ' ' << MAXSIZE  << endl;
		// cout << "Insert to table: " << name << ' ' << energy << endl;

		// If restaurant just opened right now
		if (numCustomers == 0 || !curCustomer)
		{
			if (energy != 0)
			{
				// Point to itself
				newCustomer->next = newCustomer;
				newCustomer->prev = newCustomer;

				// New head
				curCustomer = newCustomer;
				// curCustomer = headTable;
			
				numCustomers++;
			}
		}
		else if (numCustomers < MAXSIZE)
		{
			// cout << numCustomers << ' ' << MAXSIZE  << endl;
			if (numCustomers < ceil(float(MAXSIZE) / 2))
			{
				if (energy == 0)
				{
					cout << "Cut ra ngoai" << endl;
					/* code */
				}
				else if (energy >= curCustomer->energy)
				{
					// cout << "Insert to table != 0: " << endl;

					this->insertToRight(newCustomer, curCustomer);
				}
				else if (energy < curCustomer->energy)
				{
					// cout << "\nEnergy < 0\n";
					this->insertToLeft(newCustomer, curCustomer);
				}
			}
			else if (numCustomers >= ceil(float(MAXSIZE) / 2))
			{
				int diff = 0;
				Customer *positionToAdd = this->findMaxDifference(newCustomer, diff);

				// cout << positionToAdd->name << " " << positionToAdd->energy << " " << diff << endl;
				
				if (diff >= 0){
					this->insertToRight(newCustomer, positionToAdd);
				}
				else if (diff < 0){
					this->insertToLeft(newCustomer, positionToAdd);
				}
				// if (numCustomers == MAXSIZE - 1)
				// {
				// 	Customer *temp = curCustomer;
				// 	while (!temp)
				// 	{
				// 		if (temp)
				// 		{
				// 			temp->next = curCustomer;
				// 			curCustomer->prev = temp;
				// 			break;
				// 		}
				// 		temp = temp->next;
				// 	}
				// }
			}
		}

		else if (numCustomers >= MAXSIZE)
		{
			// Customer *cus = new Customer(name, energy, nullptr, nullptr);
			addCustomerInQueue(newCustomer);
		}

		
		// if (currSizeQueue == 0)
		// {
		// 	return;
		// }
		// else
		// {
		// 	Customer *cus = FIFO();
		// 	if (numAfterKick < MAXSIZE / 2)
		// 	{
		// 		if (cus -> energy >= curCustomer -> energy){
		// 			this->insertToTail(cus);
		// 		}
		// 		else this->insertToHead(cus);
		// 	}
		// 	if (numAfterKick > MAXSIZE / 2){
		// 		this -> findMaxDifference(cus);
		// 		if (numCustomers == MAXSIZE - 1)
		// 		{
		// 			Customer *temp = headTable;
		// 			while (!temp)
		// 			{
		// 				if (temp)
		// 				{
		// 					temp->next = headTable;
		// 					headTable->prev = temp;
		// 					break;
		// 				}
		// 				temp = temp->next;
		// 			}
		// 		}
		// 		numCustomers++;
		// 	}
		// }
	}
	void checkNameOfCustomer(string name, int energy)
	{
		Customer *temp = curCustomer;
		Customer *newCustomer = new Customer(name, energy, nullptr, nullptr);
		// if (newCustomer -> name == curCustomer -> name) cout << "Cook" << endl;
		while (temp -> next != curCustomer)
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
		// numAfterKick = numCustomers;
		Customer *temp1 = headOrderQ;
		Customer *temp2 = curCustomer;
		if (num >= numCustomers)
		{
			num = numCustomers;
		}
		if (numCustomers == 0){
			return;
		}
		for (int i = 1; i <= num; i++)
		{
			while (temp1 -> next != nullptr && temp2->next != curCustomer)
			{
				Customer *temp = temp2 -> next;
				if (temp2 -> name == temp1 -> name && temp2 -> energy == temp1 ->energy)
				{
					temp2 -> prev -> next = temp2 -> next;
					temp2 -> next -> prev = temp2 -> prev;
					if (temp2 -> energy > 0) 
					{
						curCustomer = temp2 -> next;
					}
					else 
					{
						curCustomer = temp2 -> prev;
					}
					delete temp2; 
					break;
				}
				else temp2 = temp;
				// Customer *temp = temp2;
				// if (temp2 == curCustomer)
				// {
				// 	temp->next = curCustomer->next;
				// 	temp->prev = curCustomer->prev;
				// 	if (curCustomer->energy > 0)
				// 	{
				// 		curCustomer = curCustomer->next;
				// 		curCustomer->prev = temp->prev;
				// 		curCustomer = curCustomer;
				// 	}
				// 	if (curCustomer->energy < 0)
				// 	{
				// 		curCustomer = curCustomer->prev;
				// 		curCustomer->next = temp->next;
				// 		curCustomer = curCustomer;
				// 	}
				// 	temp2 = temp2->next;
				// 	delete temp;
				// 	numAfterKick--;
				// }
				// else
				// {
				// 	if (temp1->name == temp2->name)
				// 	{
				// 		temp->next = temp2->next;
				// 		temp->prev = temp2->prev;
				// 		if (temp2->energy > 0)
				// 		{
				// 			curCustomer = temp2 -> next;
				// 		}
				// 		if (temp2->energy < 0)
				// 		{
				// 			curCustomer = temp2 -> prev; 
				// 		}
				// 		temp2 = temp2->next;
				// 		delete temp;
				// 		numAfterKick--;
				// 	}
				// 	else
				// 	{
				// 		temp2 = temp2->next;
				// 	}
				// }
			}
			if (temp1 -> next == nullptr) break;
			temp1 = temp1->next;
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
		Customer *count = curCustomer;
		Customer *temp1 = curCustomer;
		Customer *temp2 = curCustomer;
		Customer *temp3 = curCustomer;
		Customer *temp4 = curCustomer;
		while (count->next != curCustomer)
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
			if (curCustomer->energy < 0)
				break;
			else
				temp2 = temp2->prev;
		}
		while (temp1->energy > 0)
		{
			if (curCustomer->energy < 0)
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
			if (curCustomer->energy > 0)
				break;
			else
				temp4 = temp4->prev;
		}
		while (temp3->energy < 0)
		{
			if (curCustomer->energy > 0)
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
		Customer *cur = curCustomer;
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
	// 	Customer *temp = curCustomer -> prev;
	// 	Customer *temp1 = curCustomer;
	// 	Customer *temp2 = headOrderQ;
	// 	int sumJujutsuEnergy = 0;
	// 	int sumJureiEnergy = 0;
	// 	if (numCustomers == 0 || jujutsu == 0 || jurei == 0){
	// 		return;
	// 	}
	// 	while (temp1 -> next != curCustomer){
	// 		if (temp1 -> energy > 0) sumJujutsuEnergy += temp1 -> energy;
	// 		else sumJureiEnergy += temp1 -> energy;
	// 		temp1 = temp1 -> next;
	// 	}
	// 	if (sumJujutsuEnergy > abs(sumJureiEnergy)){
	// 		// if (curCustomer -> energy < 0) 
	// 		// {
	// 		// 	temp -> prev -> next = temp -> next;
	// 		// 	temp -> next -> prev = temp -> prev;
	// 		// 	curCustomer = temp -> prev;
	// 		// 	curCustomer = curCustomer;
	// 		// 	cout << temp -> energy << "-" << temp -> name << endl;
	// 		// 	delete temp;
	// 		// }
	// 		// temp2 = temp2 -> next;
	// 		for (int i = 1; i <= numCustomers; i++){
	// 			do {
	// 				Customer *nextCustomer = temp -> next;
	// 				if (temp -> energy < 0 && temp -> name == temp2 ->name)
	// 				{
	// 					Customer *prevCustomer = temp;
	// 					while (prevCustomer -> next != temp)
	// 					{
	// 						prevCustomer = prevCustomer -> next;
	// 					}
	// 					prevCustomer -> next = nextCustomer;
	// 					delete temp;
	// 				}
	// 				temp = nextCustomer;
	// 			} while (temp != curCustomer);
	// 			temp2 = temp2 -> next;
	// 		}			
	// 	}
	// 	else if (sumJujutsuEnergy < abs(sumJureiEnergy)) {
	// 		for (int i = 1; i <= numCustomers; i++) {
	// 			if (temp2 -> energy > 0){
	// 				Customer *temp3 = curCustomer;
	// 				while (temp3 -> next ! curCustomer) {
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
		kickOutCustomer(num);
		this->printTable();
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
		this -> printMinInSubString();
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



