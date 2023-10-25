#include "main.h"

extern int MAXSIZE; // find MAXSIZE in another cpp / h file

class imp_res : public Restaurant
{

private:
	int numCustomers;
	int currSizeQueue;
	int jujutsu;
	int jurei;
	int numAfterKick;
	// customer *curCustomer;
	customer *curCustomer;
	customer *headQueue;
	customer *tailQueue;
	customer *headOrderTable;
	customer *tailOrderTable;
	customer *headOrderQ;
	customer *tailOrderQ;

public:
	imp_res() : headQueue(nullptr), tailQueue(nullptr), curCustomer(nullptr), headOrderTable(nullptr), tailOrderTable(nullptr), headOrderQ(nullptr), tailOrderQ(nullptr), numCustomers(0), currSizeQueue(0), jujutsu(0), jurei(0), numAfterKick(0) {}

	~imp_res()
	{
		customer *temp = curCustomer->next;
		customer *tempQ = headQueue;
		customer *tempOT = headOrderTable;
		customer *tempOQ = headOrderQ;

		if (curCustomer == NULL)
		{
			temp = NULL;
			return;
		}
		if (curCustomer->next == curCustomer)
		{
			delete curCustomer;
			temp = NULL;
			return;
		}
		customer *tmp;
		while (temp != curCustomer)
		{
			tmp = temp;
			temp = temp->next;
			delete tmp;
		}
		delete curCustomer;
		curCustomer = NULL;
		tmp = NULL;
		temp = NULL;

		while (tempQ != NULL)
		{
			customer *cur = tempQ;
			tempQ = tempQ->next;
			delete cur;
		}
		tempQ = NULL;
		headQueue = NULL;
		tailQueue = NULL;

		while (tempOT != NULL)
		{
			customer *cur = tempOT;
			tempOT = tempOT->next;
			delete cur;
		}
		tempOT = NULL;
		headOrderTable = NULL;
		tailOrderTable = NULL;

		while (tempOQ != NULL)
		{
			customer *cur = tempOQ;
			tempOQ = tempOQ->next;
			delete cur;
		}
		tempOQ = NULL;
		headOrderQ = NULL;
		tailOrderQ = NULL;
	}

	customer *findMaxDifference(customer *newCustomer, int &rootDiff)
	{
		customer *temp = curCustomer;
		customer *flagCustomer = temp;
		int rootCurDifference = newCustomer->energy - temp->energy;
		int curDifference = abs(rootCurDifference);
		int maxRes = curDifference;

		temp = temp->next;

		while (temp != curCustomer)
		{
			// cout << "Root:" << rootCurDifference << endl;
			curDifference = abs(newCustomer->energy - temp->energy);

			if (curDifference > maxRes)
			{
				rootCurDifference = newCustomer->energy - temp->energy;
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
		customer *temp = curCustomer;

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

	void insertToLeft(customer *newCustomer, customer *flagPostion)
	{
		// Get prev node of current customer
		customer *prevCustomer = flagPostion->prev;

		// Point current customer and prev to new customer, point new customer to cur and prev
		flagPostion->prev = newCustomer;
		prevCustomer->next = newCustomer;
		newCustomer->next = flagPostion;
		newCustomer->prev = prevCustomer;

		// Change current customer
		curCustomer = newCustomer;

		// cout << curCustomer->next->name << endl;
		// Increse customer
		numCustomers++;
	}

	void insertToRight(customer *newCustomer, customer *flagPostion)
	{
		// Get prev node of current customer
		customer *nextCustomer = flagPostion->next;

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
		customer *newCustomer = new customer(name, energy, nullptr, nullptr);
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
						// cout << "Cut ra ngoai" << endl;
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
					customer *positionToAdd = this->findMaxDifference(newCustomer, diff);

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
				// customer *cus = new customer(name, energy, nullptr, nullptr);
				addCustomerInQueue(newCustomer);
			}
		}
	
	// need fix
	bool checkDuplicatedNameInTable(string name)
	{
		if (numCustomers == 0) return true;

		customer* temp = curCustomer;

		while (temp->next != curCustomer){
			if (name == temp->name) return false;
			temp = temp->next;
		}
		return true; 
	}

	void addCustomerInQueue(customer *newCustomer)
	{
		if (newCustomer->energy == 0)
		{
			// cout << "Cook luon" << endl;
			return;
		}
		if (currSizeQueue >= MAXSIZE)
		{
			// cout << " Het cho trong hang cho roi cook" << endl;
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

	void orderOfCustomer(string name, int energy)
	{
		customer *newCustomer = new customer(name, energy, nullptr, nullptr);
		if (!headOrderTable)
		{
			headOrderTable = newCustomer;
			tailOrderTable = newCustomer;
			return;
		}

		tailOrderTable->next = newCustomer;
		newCustomer->prev = tailOrderTable;
		tailOrderTable = newCustomer;
	}

	void inserAfterKick()
	{
		// Get customer from queue to table if queue has any and table has slot
		customer *queueToTable = headQueue;

		while (numCustomers < MAXSIZE)
		{
			insertToTable(queueToTable->name, queueToTable->energy);
			queueToTable = queueToTable->next;
			deleteHeadList(headQueue);
			currSizeQueue--;
		}
	}

	void deleteHeadList(customer *headList)
	{
		customer *headPrev = headList->prev;
		customer *deleteNode = headList;
		headList = headList->next;
		headPrev->next = headList;

		delete deleteNode;
	}

	void deleteCustomerWithName(customer *listToDelete, customer *kickedCustomer)
	{
		// Delete kickedCustomer from table
		if (!listToDelete)
			return; //

		customer *temp = listToDelete;
		customer *prev1 = nullptr;

		while (temp->name != kickedCustomer->name)
		{
			if (temp->next == listToDelete)
				return; // break?

			prev1 = temp;
			temp = temp->next;
		}

		if (temp->next == listToDelete && prev1 == nullptr)
		{
			// List has only a node and that is kicked customer
			listToDelete = nullptr;
			delete temp;
			numCustomers--;
			return;
		}

		if (temp == listToDelete)
		{
			// Delete at head of table
			this->deleteHeadList(listToDelete);
			numCustomers--;
			// prev1 = listToDelete->prev;
			// listToDelete = listToDelete->next;
			// prev1->next = listToDelete;
			// delete temp;
		}
		else if (temp->next == listToDelete)
		{
			// Delete at tail
			prev1->next = listToDelete;
			listToDelete->prev = prev1;
			numCustomers--;
			delete temp;
		}
		else
		{
			// Delete at mid
			customer *nextTemp = temp->next;

			prev1->next = nextTemp;
			nextTemp->prev = prev1;
			numCustomers--;
			delete temp;
		}
	}

	void kickOutCustomer(int num)
	{
		// numAfterKick = numCustomers;
		customer *temp1 = headOrderTable;
		customer *temp2 = curCustomer;
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
			this->deleteCustomerWithName(curCustomer, temp1);
			if (temp1 == tailOrderTable)
				break;
			temp1 = temp1->next;
		}
	}

	void orderofQueue(string name, int energy)
	{
		customer *newCustomer = new customer(name, energy, nullptr, nullptr);
		if (!headQueue)
		{
			headQueue = newCustomer;
			tailQueue = newCustomer;
			return;
		}

		tailQueue->next = newCustomer;
		newCustomer->prev = tailQueue;
		tailQueue = newCustomer;
	}

	void swapCustomer(customer *cus1, customer *cus2)
	{
		customer *prevCus1 = cus1->prev;
		customer *prevCus2 = cus2->prev;
		customer *nextCus1 = cus1->next;
		customer *nextCus2 = cus2->next;
		if (prevCus1)
		{
			prevCus1->next = cus2;
			cus2->prev = prevCus1;
		}
		if (prevCus2)
		{
			prevCus2->next = cus1;
			cus1->prev = prevCus2;
		}
		if (nextCus1)
		{
			nextCus1->prev = cus2;
			cus2->next = nextCus1;
		}
		if (nextCus2)
		{
			nextCus2->prev = cus1;
			cus1->next = nextCus2;
		}
	}

	void purpleMurasaki(int countPurple)
	{
		if (currSizeQueue <= 1)
			return;
		customer *checkAbsEnergy = headQueue;
		customer *maxAbsEnergy;
		int maxAbs = 0;
		while (checkAbsEnergy != tailQueue)
		{
			if (abs(checkAbsEnergy->energy) >= maxAbs)
			{
				maxAbs = abs(checkAbsEnergy->energy);
				maxAbsEnergy = checkAbsEnergy;
			}
			checkAbsEnergy = checkAbsEnergy->next;
		}
		if (abs(checkAbsEnergy->energy) >= maxAbs)
		{
			maxAbs = abs(checkAbsEnergy->energy);
			maxAbsEnergy = checkAbsEnergy;
		}
		int numSort = 0;
		customer *temp = headQueue;
		// customer *tempSort = headQueue;
		if (maxAbsEnergy == headQueue)
			return;
		while (temp != maxAbsEnergy->next)
		{
			numSort++;
			temp = temp->next;
		}

		int incr = numSort / 2;
		while (incr > 0)
		{
			temp = headQueue;
			while (temp != maxAbsEnergy->next)
			{
				int count = 0;
				customer *tempSort = temp->next;
				while (tempSort != maxAbsEnergy->next)
				{
					count++;
					if (count == incr)
					{
						count = 0;
						if (abs(temp->energy) < abs(tempSort->energy) || (abs(temp->energy) == abs(tempSort->energy) && (temp->prev->energy > tempSort->prev->energy)))
						{
							if (temp == headQueue)
								headQueue = tempSort;
							if (tempSort == tailQueue)
								tailQueue = temp;
							if (tempSort == maxAbsEnergy)
								maxAbsEnergy = temp;
							swapInfo(temp, tempSort);
							customer *tmp = temp;
							temp = tempSort;
							tempSort = tmp;
							countPurple++;
						}
					}
					tempSort = tempSort->next;
				}
				temp = temp->next;
			}
		}
		incr /= 2;
	}

	void swapInfo(customer *cus1, customer *cus2)
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
		customer *count = curCustomer;
		customer *temp1 = curCustomer;
		customer *temp2 = curCustomer;
		customer *temp3 = curCustomer;
		customer *temp4 = curCustomer;
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
					if (temp1 == curCustomer)
						curCustomer = temp2;
					else if (temp2 == curCustomer)
						curCustomer = temp1;
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
					if (temp3 == curCustomer)
						curCustomer = temp4;
					else if (temp4 == curCustomer)
						curCustomer = temp3;
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

	void calculateSum(customer *temp, customer *&flagCus, customer *&flagFirst, int &curr)
	{
		customer *current = temp;
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
					flagFirst = temp;
				}
			}
			current = current->next;
		}
	}

	void printMinInSubString()
	{
		customer *flagCustomer = nullptr;
		customer *temp = curCustomer;
		customer *flagFirst = curCustomer;
		int sum = 0;
		int current = temp->energy;
		int minEnergy = 2147483647 - 1;
		if (numCustomers < 4)
			return;
		if (numCustomers == 4 || MAXSIZE == 4)
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
			customer *tempFlagF = flagFirst;
			customer *tempFlagC = flagCustomer;
			customer *minCustomer = tempFlagF;
			tempFlagF = tempFlagF->next;
			while (tempFlagF != tempFlagC->next)
			{
				if (tempFlagF->energy < minCustomer->energy)
				{
					minCustomer = tempFlagF;
					tempFlagF = tempFlagF->next;
				}
				else
					tempFlagF = tempFlagF->next;
			}
			customer *tempMin = minCustomer;
			while (tempMin != flagCustomer->next)
			{
				cout << tempMin->name << "-" << tempMin->energy << endl;
				tempMin = tempMin->next;
			}
			while (flagFirst->next != minCustomer)
			{
				cout << flagFirst->name << "-" << flagFirst->energy << endl;
				flagFirst = flagFirst->next;
			}
			cout << flagFirst->name << "-" << flagFirst->energy << endl;
		}
	}

	void expansionKickOut()
	{
		jujutsu = 0;
		jurei = 0;
		customer *temp = curCustomer->prev;
		customer *temp1 = curCustomer;
		customer *temp2 = headQueue;
		customer *temp3 = headOrderTable;
		int sumJujutsuEnergy = 0;
		int absSumCustomerEnergy = 0;

		if (numCustomers == 0 || !curCustomer) return;
		
		while (temp1->next != curCustomer)
		{
			if (temp1->energy > 0)
			{
				jujutsu++;
				temp1 = temp1->next;
			}
			else
			{
				jurei++;
				temp1 = temp1->next;
			}
		}
		// cout << jujutsu << " " << jurei << endl;
		if (temp1->energy > 0)
			jujutsu++;
		else
			jurei++;
		int jujutsuInTable = jujutsu;
		int jureiInTable = jurei;
		// cout << numCustomers << " " << jurei << endl;
		
		if (headQueue){
			while (temp2->next != nullptr)
			{
				if (temp2->energy > 0)
				{
					jujutsu++;
					temp2 = temp2->next;
				}
				else
				{
					jurei++;
					temp2 = temp2->next;
				}
			}

			if (temp2->energy > 0)
				jujutsu++;
			else
				jurei++;
		}

		// cout << numCustomers << " " << jurei << endl;
		// tính tổng chú thuật sư và oán linh có mặt trong nhà hàng

		temp1 = curCustomer;
		temp2 = headQueue;

		// If not have any "chu su" hoac "oan linh" thi ket thuc
		if (numCustomers == 0 || jujutsu == 0 || jurei == 0)
		{
			return;
		}

		while (temp1->next != curCustomer)
		{
			if (temp1->energy > 0)
				sumJujutsuEnergy += temp1->energy;
			else
				absSumCustomerEnergy += temp1->energy;
			temp1 = temp1->next;
		}
		if (temp1->energy > 0)
			sumJujutsuEnergy += temp1->energy;
		else
			absSumCustomerEnergy += temp1->energy;
		// 
		cout << numCustomers << " " << jurei << endl;
		if (headQueue){
			while (temp2->next != nullptr)
			{
				if (temp2->energy < 0)
					absSumCustomerEnergy += temp2->energy;
				else
					sumJujutsuEnergy += temp2->energy;
				temp2 = temp2->next;
			}
			if (temp2->energy > 0)
				sumJujutsuEnergy += temp2->energy;
			else
				absSumCustomerEnergy += temp2->energy;
		}
		absSumCustomerEnergy = abs(absSumCustomerEnergy + sumJujutsuEnergy);
		// đoạn trên tính tổng Energy chú thuật sư, trị tuyệt đối của tất cả chú linh

		if (sumJujutsuEnergy >= absSumCustomerEnergy)
		{
			// delete jurei
			cout << numCustomers << " " << jurei << endl;
			deleteInTableWithEnergy(false);
			deleteInOrderOrQueueWithEnergy(false, headOrderTable);
			deleteInOrderOrQueueWithEnergy(false, headQueue);
		}
		else if (sumJujutsuEnergy < absSumCustomerEnergy)
		{
			// delete jujutsu
			deleteInTableWithEnergy(true);
			deleteInOrderOrQueueWithEnergy(true, headOrderTable);
			deleteInOrderOrQueueWithEnergy(true, headQueue);
		}
	}

	void deleteInTable(customer *kickedCustomer)
	{
		if (kickedCustomer == curCustomer){
			curCustomer = curCustomer->next;
		}

		// Delete kickedCustomer from table
		customer *prevCustomer = kickedCustomer->prev;
		customer *nextCustomer = kickedCustomer->next;

		// Connect prev to next
		prevCustomer->next = nextCustomer;
		nextCustomer->prev = prevCustomer;

		delete kickedCustomer;
	}
	
	void deleteInTableWithEnergy(bool deleteJujutsu)
	{
		customer *temp = curCustomer;
		customer *kickedCustomer = nullptr;

		while (temp->next != curCustomer)
		{
			if (deleteJujutsu)
			{
				if (temp->energy > 0)
				{
					kickedCustomer = temp;
					temp = temp->next;
					deleteInTable(kickedCustomer);
				}
				else {
					temp = temp->next;
				}
			}
			else if (!deleteJujutsu)
			{
				if (temp->energy < 0)
				{
					kickedCustomer = temp;
					temp = temp->next;
					deleteInTable(kickedCustomer);
				}
				else {
					temp = temp->next;
				}
			}
		}

		if (deleteJujutsu)
		{
			if (temp->energy > 0)
			{
				kickedCustomer = temp;
				deleteInTable(kickedCustomer);
			}
		}
		else if (!deleteJujutsu)
		{
			if (temp->energy < 0)
			{
				kickedCustomer = temp;
				deleteInTable(kickedCustomer);
			}
		}
	}
	
	void deleteInOrderOrQueueWithEnergy(bool check, customer *headList)
	{
		if (!headList) return;
		
		customer *temp = headList;

		if (!check)
		{
			for (int i = 0; i < numCustomers; i++)
			{
				if (temp->energy < 0)
				{
					if (temp == headList)
					{
						headList = temp->next;
					}
					// Adjust the 'next' pointer of the previous node
					if (temp->prev != nullptr)
					{
						temp->prev->next = temp->next;
					}
					// Adjust the 'prev' pointer of the next node
					if (temp->next != nullptr)
					{
						temp->next->prev = temp->prev;
					}
					cout << temp->name << "-" << temp->energy << endl;
					delete temp;
				}
				temp = temp->next;
			}
			// temp = headList;
			// while (temp -> next != nullptr){
			// 	cout << temp -> name << " " << temp ->energy << endl;
			// 	temp = temp ->next;
			// }
		}
		else
		{
			for (int i = 0; i < numCustomers; i++)
			{
				if (temp->energy > 0)
				{
					if (temp == headList)
					{
						headList = temp->next;
					}
					// Adjust the 'next' pointer of the previous node
					if (temp->prev != nullptr)
					{
						temp->prev->next = temp->next;
					}
					// Adjust the 'prev' pointer of the next node
					if (temp->next != nullptr)
					{
						temp->next->prev = temp->prev;
					}
					cout << temp->name << "-" << temp->energy << endl;
					delete temp;
				}
				temp = temp->next;
			}
		}
	}

	void lightPrint(int num)
	{
		customer *temp1 = curCustomer;
		customer *temp2 = headQueue;
		if (numCustomers == 0) return;
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
		if (checkDuplicatedNameInTable(name) && energy != 0){
			this->insertToTable(name, energy);
		}
		// cout << headOrderTable << endl;
		// this->printTable();
		// cout << this->numCustomers << endl;
		// this -> checkNameOfCustomer(name,energy);
	}
	void BLUE(int num)
	{
		cout << "blue " << num << endl;
		this->kickOutCustomer(num);
	}
	void PURPLE()
	{
		cout << "purple" << endl;
		int countPurple = 0;
		this->purpleMurasaki(countPurple);
		BLUE(countPurple % MAXSIZE);
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
		reversalTable();
		this->printTable();
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
		this->printMinInSubString();
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
		this -> expansionKickOut();
	}
	void LIGHT(int num)
	{
		cout << "light " << num << endl;
		this->lightPrint(num);
	}
};
