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

	Customer *findMaxDifference(Customer *newCustomer, int &rootDiff)
	{
		Customer *temp = curCustomer;
		Customer *flagCustomer = temp;
		int rootCurDifference = newCustomer->energy - temp->energy;
		int curDifference = abs(rootCurDifference);
		int maxRes = curDifference;

		temp = temp->next;

		while (temp != curCustomer)
		{
			rootCurDifference = newCustomer->energy - temp->energy;
			curDifference = abs(rootCurDifference);

			if (curDifference > maxRes)
			{
				maxRes = curDifference;
				flagCustomer = temp;
			}

			temp = temp->next;
		}

		rootDiff = rootCurDifference;
		// cout << flagCustomer->name << endl;
		return flagCustomer;
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
		cout << temp->name << '/' << temp->energy;
		cout << endl;
	}

	void insertToLeft(Customer *newCustomer, Customer *flagPostion)
	{
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
	void insertToRight(Customer *newCustomer, Customer *flagPostion)
	{
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

				orderOfCustomer(name, energy);
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

				if (diff >= 0)
				{
					this->insertToRight(newCustomer, positionToAdd);
				}
				else if (diff < 0)
				{
					this->insertToLeft(newCustomer, positionToAdd);
				}
			}

			orderOfCustomer(name, energy);
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
		while (temp->next != curCustomer)
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
			cout << " Het cho trong hang cho roi cook" << endl;
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
	void orderOfCustomer(string name, int energy)
	{
		Customer *newCustomer = new Customer(name, energy, nullptr, nullptr);
		if (!headOrderQ)
		{
			headOrderQ = newCustomer;
			tailOrderQ = newCustomer;
			return;
		}

		tailOrderQ->next = newCustomer;
		newCustomer->prev = tailOrderQ;
		tailOrderQ = newCustomer;
	}

	void deleteHead(Customer *prevHead, Customer *curCustomer, Customer *temp)
	{
		prevHead = nullptr;
		temp = headQueue;

		prevHead = headQueue->prev;
		headQueue = headQueue->next;
		prevHead->next = headQueue;
		numCustomers--;
		delete temp;
	}
	void inserAfterKick()
	{
		Customer *queueToTable = headQueue;

		while (numCustomers < MAXSIZE)
		{
			insertToTable(queueToTable->name, queueToTable->energy);
		}
	}
	void insertAfterKick()
	{
		// Get customer from queue to table if queue has any and table has slot
		this->insertToTable(headQueue->name, headQueue->energy);
	}

	void deleteCustomer(int numToDelete, Customer *kickedCustomer)
	{
		if (!curCustomer)
			return; //

		Customer *temp = curCustomer;
		Customer *prev1 = nullptr;

		while (temp->name != kickedCustomer->name)
		{
			if (temp->next == curCustomer)
				return; // break?

			prev1 = temp;
			temp = temp->next;
		}

		if (temp->next == curCustomer && prev1 == nullptr)
		{
			curCustomer = nullptr;
			delete temp;
			return;
		}

		if (temp == curCustomer)
		{
			prev1 = curCustomer->prev;
			curCustomer = curCustomer->next;
			prev1->next = curCustomer;
			delete temp;
		}
		else if (temp->next == curCustomer)
		{
			prev1->next = curCustomer;
			curCustomer->prev = prev1;
			delete temp;
		}
		else
		{
			Customer *nextTemp = temp->next;

			prev1->next = nextTemp;
			nextTemp->prev = prev1;
			delete temp;
		}
	}
	void kickOutCustomer(int num)
	{
		// numAfterKick = numCustomers;
		Customer *temp1 = headOrderQ;
		Customer *temp2 = curCustomer;
		if (num >= numCustomers || num >= MAXSIZE)
		{
			num = numCustomers;
		}
		if (numCustomers == 0)
		{
			return;
		}
		for (int i = 0; i < num; i++)
		{
			// cout << temp1->name << endl;
			this->deleteCustomer(num, temp1);
			if (temp1 == tailOrderQ)
				break;
			temp1 = temp1->next;
		}
	}
		void swapCustomer(Customer *cus1, Customer *cus2)
	{
		Customer *prevCus1  = cus1 -> prev;
		Customer *prevCus2  = cus2 -> prev;
		Customer *nextCus1  = cus1 -> next;
		Customer *nextCus2  = cus2 -> next;
		if (prevCus1){
			prevCus1 -> next = cus2;
			cus2 -> prev = prevCus1;
		}
		if (prevCus2){
			prevCus2 -> next = cus1;
			cus1 -> prev = prevCus2;
		}
		if (nextCus1){
			nextCus1 -> prev = cus2;
			cus2 -> next = nextCus1;
		}
		if (nextCus2){
			nextCus2 -> prev = cus1;
			cus1 -> next = nextCus2;
		}
	}
	void purpleMurasaki(int n, int incr) 
	{
		Customer *temp = headQueue;
		Customer *tempSort = headQueue;
		if (n == 1)  return;
		if (!temp) return;
		for (int  i = 0; i < n; i++){
			temp = temp -> next;
		}
		for (int i = incr; i < n; i++){
			if (!temp) {
				break;
			}
			tempSort = temp;
			Customer *current = temp -> next;
			Customer *result = temp;
			int j = i;
			while (j >= 0 || i == j) {
				Customer *save = tempSort -> prev;
				if (j % incr == i % incr) {
					result = tempSort;
				}
				if ((j % incr == i % incr) && (abs(result -> energy) <= abs(temp -> energy))){
					if (abs(result -> energy) < abs(temp -> energy)){
						swapCustomer(result, temp);
					}
					else if (result -> prev -> energy > temp -> prev -> energy){
						swapCustomer(result, temp);
					}
					if (!(result == temp || !result || !temp)){
						++currSizeQueue;
					}
				}
				if ((j % incr == i % incr) && (abs(result -> energy) >= abs(temp -> energy))){
					break;
				}
				tempSort = save;
				--j;
			}
			temp = current;
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
		if (numCustomers == 0 || numCustomers == 1)
		{
			return;
		}
		if (curCustomer->prev->energy > 0)
		{
			jujutsu++;
		}
		else
		{
			jurei++;
		}
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
		cout << jujutsu << " " << jurei << endl;
		while (temp2->energy > 0)
		{
			if (curCustomer->energy < 0)
				break;
			else
				temp2 = temp2->prev;
		}
		temp1 = temp1->next;
		while (temp1->energy > 0)
		{
			if (temp1->energy < 0)
				break;
			temp1 = temp1->next;
		}
		if (jurei > 0 && jurei != 1)
		{
			while (jurei != 0)
			{
				if (temp1->energy < 0 && temp2->energy < 0)
				{
					this->swapInfo(temp1, temp2);
					jurei -= 2;
					temp1 = temp1->next;
					temp2 = temp2->prev;
				}
				else if (temp1->energy > 0 && temp2->energy > 0)
				{
					temp1 = temp1->next;
					temp2 = temp2->prev;
				}
				else if (temp1->energy > 0 && temp2->energy < 0)
				{
					temp1 = temp1->next;
				}
				else
				{
					temp2 = temp2->prev;
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
		temp3 = temp3->next;
		while (temp3->energy < 0)
		{
			if (temp3->energy > 0)
				break;
			temp3 = temp3->next;
		}
		if (jujutsu > 0 && jujutsu != 1)
		{
			while (jujutsu != 0)
			{
				if (temp3->energy > 0 && temp4->energy > 0)
				{
					this->swapInfo(temp3, temp4);
					jujutsu -= 2;
					temp3 = temp3->next;
					temp4 = temp4->prev;
				}
				else if (temp3->energy < 0 && temp4->energy < 0)
				{
					temp3 = temp3->next;
					temp4 = temp4->prev;
				}
				else if (temp3->energy < 0 && temp4->energy > 0)
				{
					temp3 = temp3->next;
				}
				else
				{
					temp4 = temp4->prev;
				}
				if (jujutsu == 1)
					break;
			}
		}
	}

	void calculateSum(Customer *temp, Customer *&flagCus, Customer *&flagFirst, int &curr)
	{
		Customer *current = temp;
		int tempSum = 0;
		for (int i = 0; i < numCustomers; i++)
		{
			tempSum += current->energy;
			if (i == 3 && tempSum < curr)
			{
				curr = tempSum;
				flagCus = current;
				flagFirst = temp;
			}
			else if (i > 3)
			{
				if (tempSum <= curr)
				{
					curr = tempSum;
					flagCus = current;
					flagFirst = temp;;
				}
			}
			current = current->next;
		}
	}
	void printMinInSubString()
	{
		Customer *flagCustomer = nullptr;
		Customer *temp = curCustomer;
		Customer *flagFirst = temp;
		int sum = 0;
		int current = temp->energy;
		int minEnergy = 2147483647 - 1;
		if (numCustomers < 4)
			return;
		if (numCustomers == 4)
		{
			while (temp->next != curCustomer)
			{
				if (temp->energy < minEnergy)
				{
					minEnergy = temp->energy;
					curCustomer = temp;
					temp = temp->next;
				}
				else
					temp = temp->next;
			}
			if (temp->energy < minEnergy)
			{
				minEnergy = temp->energy;
				curCustomer = temp;
			}
			temp = curCustomer;
			while (temp->next != curCustomer)
			{
				cout << temp->name << "-" << temp->energy << endl;
				temp = temp->next;
			}
			cout << temp->name << "-" << temp->energy << endl;
		}
		else
		{
			for (int i = 0; i < numCustomers; i++)
			{
				sum += temp->energy;
				if (i == 3)
				{
					current = sum;
					flagCustomer = temp;
				}
				else if (i > 3)
				{
					if (sum <= current)
					{
						current = sum;
						flagCustomer = temp->next;
					}
				}
				temp = temp->next;
			}
			temp = temp->next;
			for (int i = 0; i < numCustomers; i++)
			{
				calculateSum(temp, flagCustomer, flagFirst, current);
				temp = temp->next;
			}
			cout << flagCustomer->name << "-" << flagCustomer->energy << endl;
			while (flagFirst -> next != flagCustomer -> next)
			{
				cout << flagFirst->name << "-" << flagFirst->energy << endl;
				flagFirst = flagFirst->next;
			}
		}
	}

	void expansionKickOut(){
		Customer *temp = curCustomer -> prev;
		Customer *temp1 = curCustomer;
		Customer *temp2 = headQueue;
		Customer *temp3 = headOrderQ;
		int sumJujutsuEnergy = 0;
		int sumJureiEnergy = 0;
		while (temp1 -> next != curCustomer)
		{
			if (temp1 -> energy > 0) {
				jujutsu++;
				temp1 = temp1 -> next;
			}
			else {
				jurei++;
				temp1 = temp1 -> next;
			}
		}
		if (temp1 -> energy > 0) jujutsu++;
		else jurei++;
		while (temp2 -> next != nullptr)
		{
			if (temp2 -> energy > 0) {
				jujutsu++;
				temp2 = temp2 -> next;
			}
			else {
				jurei++;
				temp2 = temp2 -> next;
			}
		}
		if (temp2 -> energy > 0) jujutsu++;
		else jurei++;
		// cout << jujutsu << " " << jurei << endl;
		temp1 = curCustomer;
		temp2 = headQueue;
		if (numCustomers == 0 || jujutsu == 0 || jurei == 0){
			return;
		}
		while (temp1 -> next != curCustomer){
			if (temp1 -> energy > 0) sumJujutsuEnergy += temp1 -> energy;
			else sumJureiEnergy += temp1 -> energy;
			temp1 = temp1 -> next;
		}
		while (temp2 -> next != nullptr){
			if (temp2 -> energy < 0) 
			{
				sumJureiEnergy += temp2 -> energy;
				temp2 = temp2 -> next;
			}
			else temp2 = temp2 -> next;
		}
		if (temp2 -> energy < 0) sumJureiEnergy += temp2 -> energy;
		if (sumJujutsuEnergy > abs(sumJureiEnergy)){

		}
	}

	void lightPrint(int num)
	{
		Customer *temp1 = curCustomer;
		Customer *temp2 = headQueue;
		// cout << temp2 -> name << "-" << temp2 -> energy << endl;
		if (num > 0)
		{
			while (temp1->next != curCustomer)
			{
				cout << temp1->name << "-" << temp1->energy << endl;
				temp1 = temp1->next;
			}
			cout << temp1->name << "-" << temp1->energy << endl;
		}
		else if (num < 0)
		{
			while (temp1->prev != curCustomer)
			{
				cout << temp1->name << "-" << temp1->energy << endl;
				temp1 = temp1->prev;
			}
			cout << temp1->name << "-" << temp1->energy << endl;
		}
		else
		{
			if (currSizeQueue == 0)
				return;
			else
			{
				while (temp2->next != nullptr)
				{
					cout << temp2->name << "-" << temp2->energy << endl;
					temp2 = temp2->next;
				}
				cout << temp2->name << "-" << temp2->energy << endl;
			}
		}
	}
	void RED(string name, int energy)
	{
		// cout << name << " " << energy << endl;
		// cout << MAXSIZE << endl;
		// this->orderOfCustomer(name, energy);
		// Customer *temp = headOrderQ;
		// while (temp != tailOrderQ -> next ){
		// 	cout << temp ->name << "/" << endl;
		// 	temp = temp -> next;
		// }
		this->insertToTable(name, energy);
		// cout << headOrderQ << endl;
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
		int index = 0;
		int countPurple = 0;
		int maxValue = 0;
		Customer *temp = headQueue;
		for(int i = 0; i < currSizeQueue; i++)
		{
			if(abs(temp -> energy) >= maxValue)
			{
				index = i;
				maxValue = abs(maxValue);
			}
			temp = temp -> next;
		}
		for (int i = index / 2; i > 0; i /= 2)
        {
            for (int j = 0; j < i; j++)
            {
                this->purpleMurasaki(index - j, i);
            }
        }
		this->purpleMurasaki(index, 1);
		BLUE(countPurple % MAXSIZE);	
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
		this->printMinInSubString();
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
		this->expansionKickOut();
	}
	void LIGHT(int num)
	{
		cout << "light " << num << endl;
		this->lightPrint(num);
	}
};
