#include<iostream>
#include<string>
#include<vector>
#include<forward_list>
using namespace std;
template<class T>
class SLL;
class Complaint;
////////				~~~		Class User					~~~
class User
{
private:
	int userID;
	string userName;
	string email;
	string country;
	string Type;
public:
	User(int uid = 0, string uname = " ", string e = " ", string c = " ", string t = " ")
	{
		userID = uid;
		userName = uname;
		email = e;
		country = c;
		Type = t;
	}
	bool operator==(const User& other) const
	{
		return userID == other.userID;
	}

	// Getters to access private data members
	int getUserID() const { return userID; }
	string getUserName() const { return userName; }
	string getEmail() const { return email; }
	string getCountry() const { return country; }
	string getType() const { return Type; }

	void printUser()
	{
		cout << "\tUserID: " << getUserID() << "\nName: " << getUserName()
			<< "\nEmail: " << getEmail() << "\nCountry: " << getCountry()
			<< "\nType: " << getType() << endl;
	}
};
////////				~~~		Class DLL					~~~
template <class T>
class DLL
{
public:
	class Node
	{
	public:
		T data;
		Node* next;
		Node* prev;
		Node(T d, Node* p, Node* n)
		{
			data = d;
			next = n;
			prev = p;
		}
	};

	Node* head;
	Node* tail;

	DLL()
	{
		head = nullptr;
		tail = nullptr;
	}
	bool isEmpty()
	{
		if (head == nullptr)
		{
			return true;
		}
		else
			return false;
	}
	void insertAtStart(T const element)
	{
		Node* temp = new Node(element, nullptr, nullptr);

		if (head == nullptr)
		{
			head = tail = temp;
			head->next = nullptr;
			head->prev = nullptr;
		}
		else
		{
			head->prev = temp;
			temp->next = head;
			head = temp;
		}
	}
	void insertAtEnd(T element)
	{
		Node* temp = new Node(element, tail, nullptr);
		if (tail == nullptr)
		{
			head = tail = temp;
			head->next = nullptr;
			head->prev = nullptr;
		}
		else
		{
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
	}
	Node* insertAfter(Node* ptr, T val)
	{
		if (ptr != nullptr)
		{
			if (ptr == tail)
			{
				Node* temp = new Node(val, tail, nullptr);
				tail->next = temp;
				tail = temp;
				return temp;
			}
			else
			{
				Node* temp = new Node(val, ptr, ptr->next);
				ptr->next = temp;
				return temp;
			}
		}
	}
	Node* insertBefore(Node* ptr, T val)
	{
		if (ptr != nullptr)
		{
			if (ptr == head)
			{
				Node* temp = new Node(val, nullptr, head);
				ptr->prev = temp;
				head = temp;
				return temp;
			}
			else
			{
				Node* temp = new Node(val, ptr->prev, ptr);
				ptr->prev = temp;
				return temp;
			}
		}
	}
	void deleteElement(Node*& temp)
	{
		if (temp)
		{
			if (temp == head && temp == tail)
			{  //  one element
				head = tail = nullptr;
			}
			else if (temp == head)
			{  // deleting head
				head = head->next;
				head->prev = nullptr;
			}
			else if (temp == tail)
			{  // deleting tail
				tail = tail->prev;
				tail->next = nullptr;
			}
			else
			{  // Deleting middle node
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			}
			// delete temp;
			temp = nullptr;
		}
		else
		{
			cout << "Element not found for deletion.\n";
		}
	}
	void searchName(string n)
	{
		Node* current = head;
		while (current)
		{
			if (current->data.getUserName() == n)
			{
				current->data.printUser();
				return;
			}
			current = current->next;
		}
		cout << "\nUser with " << n << " name not found in DLL too \n";
	}
	void searchEmail(string e)
	{
		Node* current = head;
		while (current)
		{
			if (current->data.getEmail() == e)
			{
				current->data.printUser();
				return;
			}
			current = current->next;
		}
		cout << "\nUser with " << e << " email not found in DLL too \n";
	}
	void print()
	{
		DLL<User>::Node* temp = head;
		while (temp != nullptr)
		{
			temp->data.printUser();
			temp = temp->next;
		}
		cout << endl;
	}
};
////////				~~~		Class Hash Table			~~~
class HashTable //for user ID indexing only
{
private:
	struct HashNode
	{
		int key;               // UserID
		DLL<User>::Node* value;               // Pointer to the User node in the doubly linked list

		HashNode(int k, DLL<User>::Node* v)
		{
			key = k;
			value = v;
		}
	};

	vector<HashNode*> table;   // Hash table
	int capacity;              // Maximum size of the table
	int size;                  // Current number of elements in the table
	int prime;                 // Prime number for the Universal Hash Function
	int a, b;                  // Random coefficients for the Universal Hash Function

	int hash1(int key) const
	{
		return ((a * key + b) % prime) % capacity;
	}

	int hash2(int key) const
	{
		return prime - (key % prime);
	}

	int findNextPrime(int n) const
	{
		while (true) {
			if (isPrime(n)) return n;
			n++;
		}
	}

	bool isPrime(int n) const
	{
		if (n < 2) return false;
		for (int i = 2; i * i <= n; i++)
		{
			if (n % i == 0) return false;
		}
		return true;
	}

public:
	HashTable(int cap = 11) : capacity(cap), size(0), prime(findNextPrime(cap * 2)), a(rand() % prime), b(rand() % prime)
	{
		table.resize(capacity, nullptr);
	}

	int getSize() const
	{
		return size;
	}

	// Check if the hash table is empty
	bool isEmpty() const
	{
		return size == 0;
	}

	void insert(int key, DLL<User>::Node* value)
	{
		int index = hash1(key);     // Primary hash
		int index2 = hash2(key);    // Secondary hash
		int i = 0;

		while (table[index] != nullptr && table[index]->key != key)
		{
			index = (index + i * index2) % capacity;
			i++;
		}

		if (table[index] == nullptr)
		{
			size++;
		}
		table[index] = new HashNode(key, value);
	}
	DLL<User>::Node* search(int key) const
	{
		int index = hash1(key);     // Primary hash
		int offset = hash2(key);    // Secondary hash
		int i = 0;

		// Search for the key using double hashing
		while (table[index] != nullptr)
		{
			if (table[index]->key == key) {
				return table[index]->value; // Return the value if key is found
			}
			index = (index + i * offset) % capacity;
			i++;
		}

		return nullptr; // Key not found
	}

	void remove(int key)
	{
		int index = hash1(key);     // Primary hash
		int offset = hash2(key);    // Secondary hash
		int i = 0;
		int checkFound = false;

		// Search for the key to remove
		while (table[index] != nullptr)
		{
			if (table[index]->key == key)
			{
				delete table[index]; // Free the memory
				table[index] = nullptr;
				size--;
				checkFound = true;
			}
			index = (index + i * offset) % capacity;
			i++;
		}
		if (!checkFound)
		{
			//cout << "Key " << key << " not found in the hash table." << endl;
		}
	}

	void printHash() const
	{
		cout << "Printing users from the hash table:" << endl;
		for (int i = 0; i < capacity; i++)
		{
			if (table[i] != nullptr)
			{
				cout << "Hash Index " << i << ": ";
				table[i]->value->data.printUser();
			}
		}
	}
};
////////				~~~		Class AVLTree				~~~
template<class T>
class AVLTree  // this is AVLTree for Email and Name index
{
private:
	class AVLNode
	{
	public:
		T data;
		int height;
		AVLNode* left;
		AVLNode* right;

		DLL<User>::Node* userNode;

		AVLNode(T d, DLL<User>::Node* ptr = nullptr)
		{
			data = d;
			userNode = ptr;
			height = 0;
			left = nullptr;
			right = nullptr;
		}

	};

	void inorderTranversalR(AVLNode* r)
	{
		if (r == nullptr)
		{
			return;
		}
		inorderTranversalR(r->left);

		if (r->userNode)
		{
			r->userNode->data.printUser();
		}
		else
		{
			cout << "User with ID " << r->data << " not found in DLL." << endl;
		}

		inorderTranversalR(r->right);

	}

	AVLNode* root;

	AVLNode* insert(AVLNode* node, T key, DLL<User>::Node* dllptr)
	{
		if (!node)
		{
			return new AVLNode(key, dllptr);
		}
		if (key < node->data)
		{
			node->left = insert(node->left, key, dllptr);
		}
		else if (key > node->data)
		{
			node->right = insert(node->right, key, dllptr);
		}
		balance(node);
		return node;
	}


	AVLNode* search(AVLNode* node, T key)
	{
		if (node == nullptr || node->data == key)
		{
			return node;
		}
		if (key < node->data)
		{
			return search(node->left, key);
		}
		return search(node->right, key);
	}
public:
	AVLTree(AVLNode* r = nullptr)
	{
		root = r;
	}
	bool isEmpty()
	{
		if (root == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int Findheight(AVLNode*& t)
	{
		if (t == nullptr)
		{
			return -1;
		}
		int hleft = -1;
		int hright = -1;
		if (t->left)
		{
			hleft = t->left->height;
		}
		if (t->right)
		{
			hright = t->right->height;
		}
		t->height = max(hleft, hright) + 1;
		return t->height;
	}
	int getHeight(AVLNode* node)
	{
		if (node)
		{
			return node->height;
		}
		else
		{
			return -1;
		}
	}
	void rightRotate(AVLNode*& x)
	{
		if (x == nullptr || x->left == nullptr) {
			// Rotation is not possible if x or x->left is null
			return;
		}

		AVLNode* orphan = x->left->right;
		AVLNode* y = x->left;
		y->right = x;
		x->left = orphan;

		x->height = Findheight(x);
		y->height = Findheight(y);
		x = y;
	}
	void leftRotate(AVLNode*& x)
	{
		if (x == nullptr || x->right == nullptr) {
			// Rotation is not possible if x or x->left is null
			return;
		}
		AVLNode* orphan = x->right->left;
		AVLNode* y = x->right;
		y->left = x;
		x->right = orphan;

		x->height = Findheight(x);
		y->height = Findheight(y);
		x = y;
	}
	void doubleLeftRightRotation(AVLNode*& X)
	{
		leftRotate(X->left);
		rightRotate(X);
	}
	void doubleRightLeftRotation(AVLNode*& X)
	{
		rightRotate(X->right);
		leftRotate(X);
	}
	AVLNode* balance(AVLNode*& x)
	{
		if (x == nullptr) return nullptr;
		if (getHeight(x->left) > getHeight(x->right))
		{
			x->height = getHeight(x->left) + 1;
		}
		else
		{
			x->height = getHeight(x->right) + 1;
		}
		if (getHeight(x->left) - getHeight(x->right) > 1)
		{
			if (getHeight(x->left->left) >= getHeight(x->left->right))
			{
				rightRotate(x);
			}
			else
			{
				doubleLeftRightRotation(x);
			}
		}
		else if (getHeight(x->right) - getHeight(x->left) > 1) //(Findheight(x->right) - Findheight(x->left) > 1)
		{
			if (x->right != nullptr && getHeight(x->right->right) >= getHeight(x->right->left))
			{
				leftRotate(x);
			}
			else
			{
				doubleRightLeftRotation(x);
			}
		}
		if (getHeight(x->left) > getHeight(x->right))
		{
			x->height = getHeight(x->left) + 1;
		}
		else
		{
			x->height = getHeight(x->right) + 1;
		}
		return x;
	}
	void remove(T key)
	{
		root = remove(key, root);
	}

	AVLNode* remove(T x, AVLNode* t)
	{
		if (!t)
		{
			return nullptr; // Item not found; do nothing
		}
		if (x < t->data)
		{
			t->left = remove(x, t->left);
		}
		else if (t->data < x)
		{
			t->right = remove(x, t->right);
		}
		else
		{
			//cout << "User with  " << x << " deleted ." << endl;
			if (t->left != nullptr && t->right != nullptr)
			{//Two children
				AVLNode* minNode = findMin(t->right);
				t->data = minNode->data;  // Replace data with min node data
				t->userNode = minNode->userNode;
				t->right = remove(t->data, t->right);
			}
			else
			{
				AVLNode* oldNode = t;
				if (t->left != nullptr)
				{
					t = t->left;
				}
				else
				{
					t = t->right;
				}
				delete oldNode;
			}
		}
		return balance(t);
	}
	AVLNode* findMin(AVLNode* t)
	{
		if (!t) return nullptr;
		while (t->left) {
			t = t->left;
		}
		return t;
	}
	void insert(T key, DLL<User>::Node* userPtr)
	{
		root = insert(root, key, userPtr);
	}

	void inorderTranversalRecur()
	{
		if (isEmpty())
		{
			cout << "\nNo User exists for this index\n";
		}
		else
		{
			inorderTranversalR(root);
		}
		cout << endl;
	}
	int BalanceFactor(AVLNode* t)
	{
		int n = 0;
		n = getHeight(t->right) - getHeight(t->left);
		return n;
	}
	DLL<User>::Node* search(T key)
	{
		AVLNode* result = search(root, key);
		if (result)
		{
			return result->userNode;
		}
		return nullptr;
	}
	void searchAndDisplay(const T& key)
	{
		DLL<User>::Node* foundUser = search(key);
		if (foundUser)
		{
			foundUser->data.printUser();
		}
		else
		{
			cout << "\nUser " << key << " not found" << endl;
		}
	}
	DLL<User>::Node* findClosest(T key)// this function is made for helping in inseritng using Log(N) in dll 
	{
		AVLNode* nearest = nullptr;
		AVLNode* current = root;

		while (current != nullptr)
		{
			if (key < current->data)
			{
				nearest = current;
				current = current->left;
			}
			else if (key > current->data)
			{
				nearest = current;
				current = current->right;
			}
			else
			{
				if (nearest)
				{
					return  nearest->userNode;
				}
				else
					return nullptr;
			}
		}

		if (nearest)
		{
			return  nearest->userNode;
		}
		else
			return nullptr;

	}
};
////////				~~~		Class StringHashTable		~~~
class StringHashTable
{
private:
	struct HashNode
	{
		string key;                        // Key (e.g., username or email)
		DLL<User>::Node* value;           // Pointer to a DLL node containing the user
		HashNode(string k, DLL<User>::Node* v)
		{
			key = k;
			value = v;
		}
	};

	vector<forward_list<HashNode>> table; // Vector of singly linked lists for chaining
	int capacity;
	int size;

	int Hash(const string& key, int tableSize)
	{
		unsigned long hash = 0;
		for (char ch : key)
		{
			hash = hash * 37 + ch;
		}
		return hash % tableSize;
	}
public:
	StringHashTable(int cap = 11) : capacity(cap), size(0)
	{
		table.resize(capacity);
	}
	void insert(const string& key, DLL<User>::Node* value)
	{
		int index = Hash(key, capacity);
		forward_list<HashNode>& chain = table[index];

		for (auto it = chain.begin(); it != chain.end(); it++)
		{
			if (it->key == key)
			{
				it->value = value; // Update value if key exists
				return;
			}
		}

		chain.push_front(HashNode(key, value));
		size++;
	}

	// Search for a key and return the associated DLL<User>::Node*
	DLL<User>::Node* search(const string& key)
	{
		int index = Hash(key, capacity);
		forward_list<HashNode>& chain = table[index];

		for (auto it = chain.begin(); it != chain.end(); it++)
		{
			if (it->key == key)
			{
				return it->value; // Return the pointer to the DLL node
			}
		}

		return nullptr; // Return null if key not found
	}

	void remove(const string& key)
	{
		int index = Hash(key, capacity);
		forward_list<HashNode>& chain = table[index];

		forward_list<HashNode>::iterator prev = chain.before_begin(); // Iterator before the first element
		forward_list<HashNode>::iterator curr = chain.begin();        // Iterator to the first element

		while (curr != chain.end())
		{
			if (curr->key == key)
			{
				chain.erase_after(prev); // Remove the current element
				size--;                  // Decrease size of the hash table
				return;
			}
			++prev; // Move previous iterator forward
			++curr; // Move current iterator forward
		}
	}


	// Display the contents of the hash table
	void display()
	{
		for (int i = 0; i < capacity; i++)
		{
			if (!table[i].empty())
			{
				cout << "Index " << i << ": ";
				for (auto it = table[i].begin(); it != table[i].end(); it++)
				{
					cout << "(" << it->key << ", Node: " << it->value << ") ";
				}
				cout << endl;
			}
		}
	}
};
////////				~~~		Class Complaint				~~~
class Complaint
{
private:

	int userID;
	string text;
	string userType;
	int complaintID = 0;
public:
	Complaint(int uid = 0, string t = "", string ty = " ")
	{
		userID = uid;
		text = t;
		userType = ty;

		/*if (complaintID == 0)
		{
			complaintID = 1;
		}
		else
		{
			complaintID++;
		}*/
	}
	void setComplaintID(int cid)
	{
		complaintID = cid;
	}
	void clear()
	{
		complaintID = 0;
		userID = 0;
		text = " ";
		userType = " ";
	}
	int getComplaintID() const { return complaintID; }
	int getUserID() const { return userID; }
	string getText() const { return text; }
	string getUserType() const { return userType; }
	void setUserType(string us)
	{
		userType = us;
	}
	void printUser() const
	{
		cout << "\nComplaintID: " << complaintID
			<< ", \nUserID: " << userID
			<< ", \nText: " << text << endl;
	}

	int checkAndReturnPriority(string type) const
	{
		int priority = 0;
		if (type == "p" || type == "P")
		{
			priority = 5;
		}
		else if (type == "g" || type == "G")
		{
			priority = 4;
		}
		else if (type == "s" || type == "S")
		{
			priority = 3;
		}
		else if (type == "n" || type == "N")
		{
			priority = 2;
		}
		else if (type == "r" || type == "R")
		{
			priority = 1;
		}
		return priority;
	}
	int getPriority()
	{
		return checkAndReturnPriority(userType);
	}


	bool operator<(const Complaint& other)  const
	{

		string type1 = getUserType();
		string type2 = other.getUserType();

		int p1 = checkAndReturnPriority(type1);
		int p2 = other.checkAndReturnPriority(type2);

		if (p1 == p2)
		{
			return getComplaintID() > other.getComplaintID();
		}
		return p1 < p2;  // Example: compare by userID
	}

	// Overload the '>' operator
	bool operator>(const Complaint& other) const
	{
		string type1 = getUserType();
		string type2 = other.getUserType();

		int p1 = checkAndReturnPriority(type1);
		int p2 = other.checkAndReturnPriority(type2);

		if (p1 == p2)
		{
			return getComplaintID() < other.getComplaintID();//if priority is same compare complaintIDs
		}
		return p1 > p2;
	}

	bool operator==(const Complaint& other) const
	{
		if (this->getComplaintID() == other.complaintID && this->getText() == other.getText() && this->getUserID() == other.getUserID() && this->getUserType() == other.getUserType())
		{
			return true;
		}
		return false;
	}



};
////////				~~~		Class SLL					~~~
template<class T>
class SLL
{
protected:
	template<class U>
	class SLLNode
	{
	public:
		U data; //DLL<User>::Node* or //Complaint
		SLLNode<T>* next;
		SLLNode()
		{
			next = nullptr;
		}
		SLLNode(U val, SLLNode<T>* n = nullptr)
		{
			data = val;
			next = n;
		}
	};
public:
	SLLNode<T>* Head;
	SLLNode<T>* Tail;
	SLL()
	{
		Head = new SLLNode<T>();//i made the head dummy 
		Tail = nullptr;
	}
	void printSLLUsers()
	{
		//Node<DLL<User>::Node*>* temp = Head->next;
		SLLNode<T>* temp = Head->next;
		while (temp)
		{
			temp->data->data.printUser(); // dll class had a node which had a data varaible in node of it so that is why we need to separate print fucntions for complaint* and DLL node*
			temp = temp->next;
		}
	}
	void printSLLUsersComplaint()
	{
		SLLNode<T>* temp = Head->next;
		while (temp)
		{
			//cout << "UserID: " << temp->data->getUserID() << endl;
			temp->data->printUser();
			temp = temp->next;
		}


	}

	bool isEmpty()// O(1)
	{
		return (Head == nullptr);
	}
	void insertAtStart(T const element)//O(1)
	{
		SLLNode<T>* tmp = new SLLNode<T>(element);


		if (Head->next == nullptr)//no elements in list
		{
			Tail = tmp;
			Head->next = tmp;
		}
		else
		{
			tmp->next = Head->next;
			Head->next = tmp;
		}
	}
	void insertAtEnd(T const element)//O(n)
	{
		SLLNode<T>* tmp = new SLLNode<T>(element);

		if (Tail == nullptr)
		{
			Tail = tmp;
			Head->next = Tail;
		}
		else
		{
			Tail->next = tmp;
			Tail = tmp;
		}

	}

	bool search(DLL<User>::Node* user)
	{
		SLLNode<DLL<User>::Node*>* temp = Head->next;
		while (temp)
		{
			if (temp->data == user)
			{
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	bool searchComplaint(Complaint* comp)
	{
		SLLNode<Complaint*>* temp = Head->next;
		while (temp)
		{
			//if (temp->data->getComplaintID() == comp->getComplaintID())
			if (temp->data == comp)
			{
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	Complaint* searchAndReturn(Complaint* comp)
	{
		SLLNode<Complaint*>* temp = Head->next;
		while (temp)
		{
			if (temp->data == comp)
			{
				return temp->data;
			}
			temp = temp->next;
		}
		return nullptr;
	}
	void deleteC(Complaint* value)
	{
		if (!isEmpty()) {
			SLLNode<T>* current = Head->next;
			SLLNode<T>* previous = Head;

			while (current) {
				if (*(current->data) == *value) { // Use overloaded operator==
					previous->next = current->next;
					if (current == Tail) {
						Tail = previous;
					}
					delete current;
					return;
				}
				previous = current;
				current = current->next;
			}
		}
		cout << "Complaint not found for deletion.\n";
	}

	void deleteUserSLL(T userToDelete)
	{
		if (Head == nullptr || Head->next == nullptr)
		{
			cout << "List is empty. Nothing to delete.\n";
			return;
		}

		SLLNode<T>* current = Head->next;
		SLLNode<T>* previous = Head;

		while (current)
		{
			if (current->data == userToDelete)
			{
				previous->next = current->next;
				if (current == Tail)
				{
					Tail = previous;
				}
				delete current;
				//cout << "User successfully removed from the list.\n";
				return;
			}
			previous = current;
			current = current->next;
		}

		//cout << "User not found in the list.\n";
	}

	void deleteAllSLL()
	{
		SLLNode<T>* current = Head->next; // Start with the first actual node
		SLLNode<T>* nextNode = nullptr;

		while (current != nullptr)
		{
			nextNode = current->next; // Save the next node
			delete current;          // Delete the current node
			current = nextNode;      // Move to the next node
		}

		Head->next = nullptr; // Reset the dummy head's next pointer
		Tail = nullptr;       // Reset the tail pointer
	}


};
////////				~~~		Class AVLgroupTree			~~~
template<class T, class U>
class AVLgroupTree
{
private:
	class AVLgroupNode
	{
	public:
		T data;
		int height;
		AVLgroupNode* left;
		AVLgroupNode* right;

		U userSLLList;

		AVLgroupNode(T d, U sllp)
		{
			data = d;
			height = 0;
			userSLLList = sllp;
			left = nullptr;
			right = nullptr;
		}

	};

	void inorderTranversalR(AVLgroupNode* r)
	{
		if (r == nullptr)
		{
			return;
		}
		inorderTranversalR(r->left);

		cout << "Group : " << r->data << "\n Users: \n";
		r->userSLLList.printSLLUsers();   //getDataAndPrint();
		cout << endl;

		inorderTranversalR(r->right);

	}

	AVLgroupNode* root;

	AVLgroupNode* insert(AVLgroupNode* node, T key, U& sllptr)
	{
		if (!node)
		{
			return new AVLgroupNode(key, sllptr);
		}
		if (key < node->data)
		{
			node->left = insert(node->left, key, sllptr);
		}
		else if (key > node->data)
		{
			node->right = insert(node->right, key, sllptr);
		}
		balance(node);
		return node;
	}


	AVLgroupNode* search(AVLgroupNode* node, T key)
	{
		if (node == nullptr || node->data == key)
		{
			return node;
		}
		if (key < node->data)
		{
			return search(node->left, key);
		}
		return search(node->right, key);
	}

	AVLgroupNode* remove(T x, AVLgroupNode* t)
	{
		if (!t)
		{
			return nullptr; // Item not found; do nothing
		}
		if (x < t->data)
		{
			t->left = remove(x, t->left);
		}
		else if (t->data < x)
		{
			t->right = remove(x, t->right);
		}
		else
		{
			cout << "User with this " << x << " deleted ." << endl;
			if (t->left != nullptr && t->right != nullptr)
			{//Two children
				AVLgroupNode* minNode = findMin(t->right);
				t->data = minNode->data;		// Replace data with min node data
				t->userSLLList = minNode->userSLLList;
				t->right = remove(t->data, t->right);	//(minNode->data,t->right)
			}
			else
			{
				AVLgroupNode* oldNode = t;
				if (t->left != nullptr)
				{
					t = t->left;
				}
				else
				{
					t = t->right;
				}
				delete oldNode;
			}
		}
		return balance(t);
	}
	AVLgroupNode* findMin(AVLgroupNode* t)
	{
		if (!t) return nullptr;
		while (t->left) {
			t = t->left;
		}
		return t;
	}
public:
	AVLgroupTree(AVLgroupNode* r = nullptr)
	{
		root = r;
	}
	bool isEmpty()
	{
		if (root == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int Findheight(AVLgroupNode*& t)
	{
		if (t == nullptr)
		{
			return -1;
		}
		int hleft = -1;
		int hright = -1;
		if (t->left)
		{
			hleft = t->left->height;
		}
		if (t->right)
		{
			hright = t->right->height;
		}
		t->height = max(hleft, hright) + 1;
		return t->height;
	}
	int getHeight(AVLgroupNode* node)
	{
		if (node)
		{
			return node->height;
		}
		else
		{
			return -1;
		}
	}
	void rightRotate(AVLgroupNode*& x)
	{
		if (x == nullptr || x->left == nullptr) {
			// Rotation is not possible if x or x->left is null
			return;
		}

		AVLgroupNode* orphan = x->left->right;
		AVLgroupNode* y = x->left;
		y->right = x;
		x->left = orphan;

		x->height = Findheight(x);
		y->height = Findheight(y);
		x = y;
	}
	void leftRotate(AVLgroupNode*& x)
	{
		if (x == nullptr || x->right == nullptr) {
			// Rotation is not possible if x or x->left is null
			return;
		}
		AVLgroupNode* orphan = x->right->left;
		AVLgroupNode* y = x->right;
		y->left = x;
		x->right = orphan;

		x->height = Findheight(x);
		y->height = Findheight(y);
		x = y;
	}
	void doubleLeftRightRotation(AVLgroupNode*& X)
	{
		leftRotate(X->left);
		rightRotate(X);
	}
	void doubleRightLeftRotation(AVLgroupNode*& X)
	{
		rightRotate(X->right);
		leftRotate(X);
	}
	AVLgroupNode* balance(AVLgroupNode*& x)
	{
		if (x == nullptr) return nullptr;
		if (getHeight(x->left) > getHeight(x->right))
		{
			x->height = getHeight(x->left) + 1;
		}
		else
		{
			x->height = getHeight(x->right) + 1;
		}
		if (getHeight(x->left) - getHeight(x->right) > 1)
		{
			if (getHeight(x->left->left) >= getHeight(x->left->right))
			{
				rightRotate(x);
			}
			else
			{
				doubleLeftRightRotation(x);
			}
		}
		else if (getHeight(x->right) - getHeight(x->left) > 1) //(Findheight(x->right) - Findheight(x->left) > 1)
		{
			if (x->right != nullptr && getHeight(x->right->right) >= getHeight(x->right->left))
			{
				leftRotate(x);
			}
			else
			{
				doubleRightLeftRotation(x);
			}
		}
		if (getHeight(x->left) > getHeight(x->right))
		{
			x->height = getHeight(x->left) + 1;
		}
		else
		{
			x->height = getHeight(x->right) + 1;
		}
		return x;
	}
	void remove(T key)
	{
		root = remove(key, root);
	}


	void insert(T key, U& userPtr)
	{
		root = insert(root, key, userPtr);
	}

	void inorderTranversalRecurGroup()
	{
		if (isEmpty())
		{
			cout << "\n No User exists for this index \n";
		}
		else
		{
			inorderTranversalR(root);
		}
		cout << endl;
	}
	int BalanceFactor(AVLgroupNode* t)
	{
		int n = 0;
		n = getHeight(t->right) - getHeight(t->left);
		return n;
	}
	U* search(T key)
	{
		AVLgroupNode* result = search(root, key);
		if (result)
		{
			return &(result->userSLLList);
		}
	}
	void removeUserinSLL(T key, DLL<User>::Node* userToDelete)//to remove node form SLL
	{
		AVLgroupNode* result = search(root, key);
		if (result)
		{
			result->userSLLList.deleteUserSLL(userToDelete);
		}
		else
		{
			cout << "Group not found for key: " << key << ".\n";
		}
	}
	bool searchGroup(const T& key)
	{
		AVLgroupNode* foundUser = search(root, key);
		if (foundUser)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void searchAndDisplay(const T& key)
	{
		AVLgroupNode* foundUser = search(root, key);
		if (foundUser)
		{
			foundUser->userSLLList.printSLLUsers();
		}
		else
		{
			cout << "\nUser not found : " << key << endl;
		}
	}

	void searchAndDisplayComplaint(const T& key)
	{
		AVLgroupNode* foundUser = search(root, key);
		if (foundUser)
		{
			SLL<Complaint*> slist = foundUser->userSLLList;
			slist.printSLLUsersComplaint();
		}
		else
		{
			cout << "\nUser not found : " << key << endl;
		}
	}

	void removeNodeinSLL(int userID, Complaint* comp)//removing complaint* from SLL
	{
		AVLgroupNode* result = search(root, userID);
		if (result)
		{
			result->userSLLList.deleteC(comp);
			//result->userSLLList.deleteUserSLL(comp);
		}
		else
		{
			cout << "Group not found for key: " << userID << ".\n";
		}
	}
};
////////				~~~		Class GroupHash				~~~
template <typename T, typename U>
class GroupHash
{
private:
	class HashNode
	{
	public:
		T key;                // Key (string or int)
		SLL<U> userList;      // Singly Linked List of U (e.g., DLLNode*)
		bool isActive;        // To mark active/deleted nodes

		HashNode(T k = T(), bool active = false) : key(k), isActive(active) {}
	};

	vector<HashNode> hashTable;
	int tableSize;
	int currentSize;

	int hashFunction(const string& key)
	{
		int hash = 0;
		for (char c : key) 
		{
			hash = (hash * 31 + c) % tableSize;
		}
		return hash;
	}

	int findPositionLinear(const T& key)// Linear Probing for Country Collision
	{
		int hashIndex = hashFunction(key);
		int originalIndex = hashIndex;
		while (hashTable[hashIndex].isActive && hashTable[hashIndex].key != key)
		{
			hashIndex = (hashIndex + 1) % tableSize;
			if (hashIndex == originalIndex)
			{
				break;
			}
		}
		return hashIndex;
	}

	int findPositionQuadratic(const T& key)// Quadratic Probing for Type collision
	{
		int hashIndex = hashFunction(key);
		int i = 1;
		while (hashTable[hashIndex].isActive && hashTable[hashIndex].key != key)
		{
			hashIndex = (hashIndex + i * i) % tableSize;
			i++;
			if (i > tableSize)
			{
				break;
			}
		}
		return hashIndex;
	}

public:

	GroupHash(int size = 11) : tableSize(size), currentSize(0)
	{
		hashTable.resize(tableSize);
	}

	// Insert a user into the group index
	void insert(const T& key, U user, int groupType)
	{
		int position = 0;
		if (groupType == 1)
		{
			position = findPositionLinear(key);
		}

		else if (groupType == 2)
		{
			position = findPositionQuadratic(key);
		}
		else
		{
			cout << "\nInvalid GroupType\n ";
		}

		if (hashTable[position].isActive)
		{
			if (hashTable[position].key == key)
			{
				hashTable[position].key = key;
				hashTable[position].isActive = true;

				hashTable[position].userList.insertAtEnd(user);  // Add user to SLL
			}
			else
			{
				cout << "\nCollision detected! Key mismatch at position: " << position << endl;
				return;
			}
		}
		else
		{
			hashTable[position].key = key;
			hashTable[position].isActive = true;

			hashTable[position].userList.insertAtEnd(user);
			currentSize++;
		}
	}
	void searchAndListUsers(const T& key, int groupType)
	{
		int position = -1;
		if (groupType == 1)
		{
			position = findPositionLinear(key);
		}
		else if (groupType == 2)
		{
			position = findPositionQuadratic(key);
		}
		else
		{
			cout << "\nInvalid GroupType\n ";
		}
		if (hashTable[position].isActive && hashTable[position].key == key)
		{
			cout << "Users belonging to group " << key << ":\n";
			hashTable[position].userList.printSLLUsers();
		}
		else {
			cout << "No users found for group: " << key << endl;
		}
	}

	SLL<U>* search(const T& key, int groupType)
	{
		int position = -1;
		if (groupType == 1)
		{
			position = findPositionLinear(key); // Linear probing
		}
		else if (groupType == 2)
		{
			position = findPositionQuadratic(key); // Quadratic probing
		}
		else
		{
			cout << "\nInvalid GroupType\n";
			return nullptr;
		}

		if (hashTable[position].isActive && hashTable[position].key == key)
		{
			return &hashTable[position].userList; // Return a pointer to the SLL
		}
		else
		{
			cout << "No group found for key: " << key << endl;
			return nullptr;
		}
	}

	void displayAllHash()
	{
		for (int i = 0; i < tableSize; i++)
		{
			if (hashTable[i].isActive)
			{
				cout << "Group: " << hashTable[i].key << "\n";
				hashTable[i].userList.printSLLUsers();
				cout << endl;
			}
		}
	}
	bool isEmpty()
	{
		if (currentSize <= 0)
		{
			return true;
		}
		return false;
	}

	void deleteIndex(const T& key, int groupType)
	{
		int index = 0;
		if (groupType == 1)
		{
			index = findPositionLinear(key);
		}

		else if (groupType == 2)
		{
			index = findPositionQuadratic(key);
		}
		else
		{
			cout << "\nInvalid GroupType\n ";
		}

		if (hashTable[index].isActive && hashTable[index].key == key)
		{
			hashTable[index].isActive = false;
			hashTable[index].userList.deleteAllSLL(); // Assume clear() exists for SLL
			currentSize--;
			cout << "Group \"" << key << "\" and all its users have been deleted.\n";
		}
		else
		{
			cout << "Group \"" << key << "\" not found.\n";
		}
	}

	void deleteUserFromGroup(const T& key, U userNode, int groupType)
	{
		int index = -1;
		if (groupType == 1) 
		{
			index = findPositionLinear(key); // Linear probing for country group
		}
		else if (groupType == 2)
		{
			index = findPositionQuadratic(key); // Quadratic probing for type group
		}
		else {
			cout << "Invalid group type specified.\n";
			return;
		}

		if (index >= 0 && hashTable[index].isActive && hashTable[index].key == key)
		{
			hashTable[index].userList.deleteUserSLL(userNode);
			cout << "User deleted from group: " << key << endl;
		}
		else
		{
			cout << "No group found for key: " << key << endl;
		}
	}



};
////////				~~~		Class priorityQueue			~~~
template<class T>
class priorityQueue  //max Heap
{
private:
	vector<T> arrayVector;
	int currentSize = 0;
	int capacity = 0;

	void bubble_up(int root, int last) // A recursive method to heapify a subtree with the root at given index. It maintains heap property during insertion
	{
		int parent;
		if (last > root)
		{
			parent = (last - 1) / 2;
			if (arrayVector[parent] < arrayVector[last])
			{
				swap(arrayVector[parent], arrayVector[last]);
				bubble_up(root, parent);
			}
		}
	}
	void ReheapDown(int cnode, int last)
	{
		int maxChild, rightChild, leftChild;
		leftChild = 2 * cnode + 1;
		rightChild = 2 * cnode + 2;
		if (leftChild <= last)
		{ // left child is part of the heap

			if (leftChild == last) // only one child
				maxChild = leftChild;
			else
			{
				if (arrayVector[leftChild] > arrayVector[rightChild])
				{
					maxChild = leftChild;
				}

				else
				{
					maxChild = rightChild;
				}

			}
			if (arrayVector[cnode] < arrayVector[maxChild])
			{
				swap(arrayVector[cnode], arrayVector[maxChild]);
				ReheapDown(maxChild, last);
			}
		}
	}
	void bubble_down(int i) // It maintains heap property during deletion
	{
		ReheapDown(i, currentSize - 1);
	}
public:
	priorityQueue() : currentSize(0), capacity(50)
	{
		arrayVector.resize(capacity);
	}

	priorityQueue(T* arr, int N) // parameterizedconstructor that will take an arrayVector of random numbers and its size in parameters and initialize the heap with random values. It will call the buildMinHeap() function to convert the random values into a heap.
	{

		arrayVector.resize(N);

		for (int i = 0; i < N; i++)
		{
			arrayVector[i] = arr[i];
		}
		capacity = N;
		currentSize = N;
	}

	void buildMaxHeap() // It will generate heap from random values stored in the object.
	{
		int leafCounts = (currentSize / 2) - 1;

		for (int i = leafCounts; i >= 0; i--)
		{
			bubble_down(i);
		}


	}
	void insert(T& x) //  Inserts the key value in the heap arrayVector such that, the resultant heap tree is a complete binary tree and it follows min heap order. 
	{
		if (currentSize == capacity) //to increase size
		{
			capacity *= 2;
			arrayVector.resize(capacity);
		}


		arrayVector[currentSize++] = x;
		arrayVector[currentSize - 1].setComplaintID(currentSize);
		x.setComplaintID(currentSize);
		bubble_up(0, currentSize - 1);
	}
	bool isEmpty() const // returns true if it is empty
	{
		if (currentSize < 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	const T& getMax() const //returns minimum value this operation should be performed in O(1)
	{
		return arrayVector[0];
	}

	int getCurrentSize()
	{
		return currentSize;//current size will be equal to the complaintID of top complaint 
	}

	void deleteMax() // deletes minimum value this operation should be performed in O(logN)
	{
		if (currentSize == 0) return;
		arrayVector[0] = arrayVector[--currentSize];
		arrayVector[currentSize + 1].clear();
		bubble_down(0);
	}
	bool deleteAll(T key) //remove all occurrences of key value from the heap and update the heap accordingly.
	{
		bool found = false;
		for (int i = 0; i < currentSize;) {
			if (arrayVector[i] == key) {
				arrayVector[i] = arrayVector[--currentSize];
				bubble_down(i);
				found = true;
			}
			else
			{
				i++;
			}
		}
		return found;
	}
	void printHeap()
	{
		for (int i = 0; i < currentSize; i++)
		{

			arrayVector[i].printUser();
			cout << " ";
		}
		cout << endl;
	}
	int searchandReturnUID(int compID)
	{
		for (int i = 0; i < currentSize; i++)
		{
			if (arrayVector[i].getComplaintID() == compID)
			{
				return arrayVector[i].getUserID();
			}
		}
		return -1;
	}
	T* searchComplaint2(int compID)
	{
		for (int i = 0; i < currentSize; i++)
		{
			if (arrayVector[i].getComplaintID() == compID)
			{
				return &arrayVector[i];
			}
		}
		return nullptr;
	}
	void incrPriorirty(int compID)
	{
		T* complaint = searchComplaint2(compID);

		if (!complaint)
		{
			cout << "Complaint with ID " << compID << " not found.\n";
		}
		else
		{

			cout << "\nThis is the complaint you are prioritizing:\n";
			arrayVector[compID - 1].printUser();
			swap(arrayVector[compID - 1], arrayVector[0]);

			deleteMax();

			cout << "Priority for Complaint ID " << compID << " has been increased.\n";
		}

	}


};
////////				~~~		Class UserList				~~~
class UserList
{
private:
	DLL<User> myList;
	AVLTree<int> index;		//pointer of dll node + userid
	HashTable hashIdIndex;

	AVLTree<string> nameIndex;			//pointer of dll node + nameIndex
	AVLTree<string> emailIndex;			//pointer of dll node + emailIndex

	StringHashTable hashNameIndex;
	StringHashTable hashEmailIndex;

	AVLgroupTree<string, SLL<DLL<User>::Node*>> countryIndex;		//SLL of pointers of dll node + country
	AVLgroupTree<string, SLL<DLL<User>::Node*>> typeIndex;			//SLL of pointers of dll node + type

	GroupHash<string, DLL<User>::Node*> hashCountryIndex;
	GroupHash<string, DLL<User>::Node*> hashTypeIndex;

	priorityQueue<Complaint> complaintQueue;

	AVLgroupTree<int, SLL<Complaint*>>  complaintIndex;

public:
	void insertUser(int uid, string uname, string e, string c, string t)
	{
		User newUser(uid, uname, e, c, t);
		DLL<User>::Node* userNode = nullptr;
		if (myList.isEmpty())
		{
			myList.insertAtStart(newUser);
			userNode = myList.head;
		}
		else
		{
			if (searchNodeAndReturn(uid) != nullptr)
			{
				cout << "User with ID " << uid << " already exists." << endl;
				return;
			}

			DLL<User>::Node* parent = index.findClosest(uid);
			if (parent)
			{
				if (parent->data.getUserID() > uid)
				{
					userNode = myList.insertBefore(parent, newUser);
				}
				else
				{
					userNode = myList.insertAfter(parent, newUser);
				}
			}


		}
		index.insert(uid, userNode);
		hashIdIndex.insert(uid, userNode);

		insertUserByName();
		insertUserByEmail();

		insertUserByNameHash();
		insertUserByEmailHash();

		insertUserByCountry();
		insertUserByType();

		hashCountryIndex.insert(c, userNode, 1);
		hashTypeIndex.insert(t, userNode, 2);
	}
	void insertUserByName()//inserts user by name one by one i called it in insertUser we can also use it separatelt by writting in parameters
	{
		DLL<User>::Node* userNode = myList.head;

		nameIndex.insert(userNode->data.getUserName(), userNode);
		userNode = userNode->next;
		while (userNode != nullptr)
		{
			nameIndex.insert(userNode->data.getUserName(), userNode);
			userNode = userNode->next;
		}

	}
	void insertUserByEmail()
	{
		DLL<User>::Node* userNode = myList.head;
		{
			emailIndex.insert(userNode->data.getEmail(), userNode);
			userNode = userNode->next;
			while (userNode != nullptr)
			{
				emailIndex.insert(userNode->data.getEmail(), userNode);
				userNode = userNode->next;
			}
		}

	}
	void insertUserByCountry()
	{
		DLL<User>::Node* userNode = myList.head;
		while (userNode != nullptr)
		{
			string country = userNode->data.getCountry();
			if (countryIndex.searchGroup(country))//if the index with this cuntry already exists
			{
				SLL<DLL<User>::Node*>* existingSLL = countryIndex.search(country);
				if (existingSLL->search(userNode))
				{
					//cout << "\nUser ALready exists for this Country\n";
				}
				else
				{
					existingSLL->insertAtEnd(userNode);
				}
			}
			else                 //if doesnot already exists add Node* is in new made SLL in insert fucntion
			{
				SLL<DLL<User>::Node*> newSLL;
				newSLL.insertAtStart(userNode);
				countryIndex.insert(country, newSLL);
			}
			userNode = userNode->next;
		}
	}
	void insertUserByType()
	{
		DLL<User>::Node* userNode = myList.head;
		while (userNode != nullptr)
		{
			string type = userNode->data.getType();
			if (typeIndex.searchGroup(type))			//if the index with this ocuntry already exists
			{
				SLL<DLL<User>::Node*>* existingSLL = typeIndex.search(type);
				if (existingSLL->search(userNode))
				{
					//cout << "\nUser ALready exists for this Type\n";
				}
				else
				{
					existingSLL->insertAtEnd(userNode);
				}
			}
			else                                     //if doesnot already exists add Node* in new made SLL in insert fucntion
			{
				SLL<DLL<User>::Node*> newSLL;
				newSLL.insertAtStart(userNode);
				typeIndex.insert(type, newSLL);
			}
			userNode = userNode->next;
		}
	}

	void insertUserByNameHash()
	{
		DLL<User>::Node* userNode = myList.head;
		while (userNode != nullptr)
		{
			hashNameIndex.insert(userNode->data.getUserName(), userNode);
			userNode = userNode->next;
		}
	}
	void insertUserByEmailHash()
	{
		DLL<User>::Node* userNode = myList.head;
		while (userNode != nullptr)
		{
			hashEmailIndex.insert(userNode->data.getEmail(), userNode);
			userNode = userNode->next;
		}
	}

	void  searchUser(int userID)
	{
		index.searchAndDisplay(userID);
		cout << endl << endl;
	}
	void searchUserIdHash(int uid)
	{
		//DLL<User>::Node* result = index.search(uid);
		DLL<User>::Node* result = hashIdIndex.search(uid);
		if (result)
		{
			result->data.printUser();
		}
		else {
			cout << "User with ID " << uid << " not found.\n";
		}
	}

	void searchUserByNameHash(const string& name)
	{
		DLL<User>::Node* userNode = hashNameIndex.search(name);
		if (userNode != nullptr)
		{
			userNode->data.printUser();
		}
		else {
			cout << "User with name \"" << name << "\" not found." << endl;
		}
	}

	void searchUserByEmailHash(const string& email) {
		DLL<User>::Node* userNode = hashEmailIndex.search(email);
		if (userNode != nullptr) {
			userNode->data.printUser();
		}
		else {
			cout << "User with email \"" << email << "\" not found." << endl;
		}
	}
	void searchUserbyCountryHash(string country)
	{
		if (!hashCountryIndex.isEmpty())
		{
			hashCountryIndex.searchAndListUsers(country, 1);
		}
	}
	void searchUserbyTypeHash(string type)
	{
		if (!hashTypeIndex.isEmpty())
		{
			hashTypeIndex.searchAndListUsers(type, 2);
		}
	}

	void searchUserbyName(string n)
	{
		if (nameIndex.isEmpty())
		{
			cout << "\nName Index is Empty so Searching name in DLL:\n";
			myList.searchName(n);
		}
		else
		{
			nameIndex.searchAndDisplay(n);
		}
	}
	void searchUserbyEmail(string n)
	{
		if (emailIndex.isEmpty())
		{
			cout << "\nEmail Index is Empty so Searching email in DLL:\n";
			myList.searchEmail(n);
		}
		else
		{
			emailIndex.searchAndDisplay(n);
		}
	}
	void searchUserbyCountry(string country)
	{
		if (!countryIndex.isEmpty())
		{
			if (countryIndex.searchGroup(country))
			{
				cout << "\nUsers in Group Country Index are: " << country << " : \n";
				countryIndex.searchAndDisplay(country);
			}
			else
			{
				cout << "\nNo users found from " << country << ".\n";
			}
		}
	}
	void searchUserbyType(string type)
	{
		if (!typeIndex.isEmpty())
		{
			cout << "\nUsers in Group Type Index are: \n";
			typeIndex.searchAndDisplay(type);
		}
	}

	DLL<User>::Node* searchNodeAndReturn(int userID)
	{
		return index.search(userID);
	}
	DLL<User>::Node* searchNodeAndReturnByName(const string& name)
	{
		return nameIndex.search(name);
	}
	DLL<User>::Node* searchNodeAndReturnByEmail(const string& email)
	{
		return emailIndex.search(email);
	}

	void deleteUser(int userID)
	{
		DLL<User>::Node* userToDelete = searchNodeAndReturn(userID);
		if (userToDelete)
		{
			cout << "\nUser with ID " << userID << " deleted ." << endl;

			index.remove(userID);
			deleteUserIDHash(userID);

			deleteUserByName(userToDelete->data.getUserName());
			deleteUserByEmail(userToDelete->data.getEmail());

			deleteUserByNameHash(userToDelete->data.getUserName());
			deleteUserByEmailHash(userToDelete->data.getEmail());

			deleteUserFromCountryIndex(userToDelete->data.getCountry(), userID, userToDelete);
			deleteUserFromTypeIndex(userToDelete->data.getType(), userID, userToDelete);

			deleteUserFromCountryHash(userToDelete->data.getCountry(), userToDelete);
			deleteUserFromTypeHash(userToDelete->data.getType(), userToDelete);

			myList.deleteElement(userToDelete);

		}
		else
		{
			cout << "\nUser with ID " << userID << " not found." << endl;
		}
	}
	void deleteUserIDHash(int uid)
	{
		DLL<User>::Node* node = hashIdIndex.search(uid);
		if (node)
		{
			hashIdIndex.remove(uid);
			cout << "User with ID " << uid << " deleted.\n";
		}
		else {
			cout << "User with ID " << uid << " not found.\n";
		}
	}
	void deleteUserByNameHash(const string& name) {
		DLL<User>::Node* userNode = hashNameIndex.search(name);
		if (userNode != nullptr) {
			hashNameIndex.remove(name);
			cout << "User with name \"" << name << "\" removed from hash name index." << endl;
		}
		else {
			cout << "User with name \"" << name << "\" not found in hash name index." << endl;
		}
	}
	void deleteUserByEmailHash(const string& email)
	{
		DLL<User>::Node* userNode = hashEmailIndex.search(email);
		if (userNode != nullptr) {
			hashEmailIndex.remove(email);
			cout << "User with email \"" << email << "\" removed from hash email index." << endl;
		}
		else {
			cout << "User with email \"" << email << "\" not found in hash email index." << endl;
		}
	}
	//~~~~~~~~~~~~~~~ SINGLE DELETE FUNCTIONS TOO
	void deleteUserFromCountryHash(const string& country, DLL<User>::Node* userNode)
	{
		hashCountryIndex.deleteUserFromGroup(country, userNode, 1); // GroupType 1: Linear probing
	}

	void deleteUserFromTypeHash(const string& type, DLL<User>::Node* userNode)
	{
		hashTypeIndex.deleteUserFromGroup(type, userNode, 2); // GroupType 2: Quadratic probing
	}


	///~~~~~complete hashTable deletion
	void deleteUserByCountryHash(string Country)
	{
		if (!hashCountryIndex.isEmpty())
		{
			hashCountryIndex.deleteIndex(Country, 1);
		}
	}
	void deleteUserByTypeHash(string type)
	{
		if (!hashTypeIndex.isEmpty())
		{
			hashTypeIndex.deleteIndex(type, 2);
		}
	}




	void deleteUserByName(string name)
	{
		DLL<User>::Node* userToDelete = searchNodeAndReturnByName(name);
		if (userToDelete)
		{
			nameIndex.remove(name);
			cout << "User with Name " << name << " deleted ." << endl;
		}
		else
		{
			cout << "User with Name " << name << " not found." << endl;
		}
	}
	void deleteUserByEmail(string email)
	{
		DLL<User>::Node* userToDelete = searchNodeAndReturnByEmail(email);
		if (userToDelete)
		{
			emailIndex.remove(email);
			cout << "User with Email " << email << " deleted ." << endl;
		}
		else
		{
			cout << "User with Email " << email << " not found." << endl;
		}
	}
	void deleteUserFromCountryIndex(string country, int id, DLL<User>::Node* userToDelete)
	{
		if (countryIndex.searchGroup(country))
		{
			countryIndex.removeUserinSLL(country, userToDelete);
		}
	}
	void deleteUserFromTypeIndex(string type, int id, DLL<User>::Node* userToDelete)
	{
		if (typeIndex.searchGroup(type))
		{
			typeIndex.removeUserinSLL(type, userToDelete);
		}
	}
	void deleteUserByCountry(string Country)
	{
		if (countryIndex.isEmpty())
		{
			cout << "\nCountry Index is empty.\n";
			return;
		}
		countryIndex.remove(Country);
	}
	void deleteUserByType(string type)
	{
		if (typeIndex.isEmpty())
		{
			cout << "\nCountry Index is empty.\n";
			return;
		}
		typeIndex.remove(type);
	}


	void printAllUsersByID()
	{
		//both work fine 
		//printDLL();
		index.inorderTranversalRecur();
	}
	void printAllUsersByHashID()// it is happeing in O(logn) ------------------------------------------------
	{
		hashIdIndex.printHash();
	}
	void printAllUsersByHashName()
	{
		hashNameIndex.display(); // Assuming `StringHashTable` has a `display` function
	}
	void printAllUsersByHashEmail()
	{
		hashEmailIndex.display(); // Assuming `StringHashTable` has a `display` function
	}
	void printAllUsersByHashCountry()
	{
		if (!hashCountryIndex.isEmpty())
		{
			hashCountryIndex.displayAllHash(); // GroupType 1: Linear Probing
		}
		else
		{
			cout << "\nCountry hash table is empty.\n";
		}

	}
	void printAllUsersByHashType()
	{
		if (!hashTypeIndex.isEmpty())
		{
			hashTypeIndex.displayAllHash(); // GroupType 1: Linear Probing
		}
		else
		{
			cout << "\nType hash table is empty.\n";
		}

	}

	void displayUsersByCountryHash(const string& country)
	{
		if (!hashCountryIndex.isEmpty())
		{
			hashCountryIndex.searchAndListUsers(country, 1);
		}
		else
		{
			cout << "\nCountry hash table is empty.\n";
		}
	}
	void displayUsersByTypeHash(const string& type)
	{
		if (!hashTypeIndex.isEmpty())
		{
			hashTypeIndex.searchAndListUsers(type, 1);
		}
		else
		{
			cout << "\nType hash table is empty.\n";
		}
	}


	void printAllUsersByName()
	{
		nameIndex.inorderTranversalRecur();
	}
	void printAllUsersByEmail()
	{
		emailIndex.inorderTranversalRecur();
	}
	void printAllUsersByCountry()
	{

		countryIndex.inorderTranversalRecurGroup();

	}
	void printAllUsersByType()
	{
		typeIndex.inorderTranversalRecurGroup();
	}
	void displayUsersByCountry(string country)
	{
		if (countryIndex.isEmpty())
		{
			cout << "\n No User in this country exists\n";
		}
		else
		{
			cout << "\nUsers from " << country << ":\n";
			countryIndex.searchAndDisplay(country);
		}
	}
	void displayUsersByType(string type)
	{
		cout << "\nUsers of type " << type << ":\n";
		typeIndex.searchAndDisplay(type);
	}

	//q4 functions  
	void RegisterComplaint()// --insert a complaint in the priority queue based on user type.For users of the same type,
	{
		cout << "\nEnter User Details for Registering Complaint :" << endl;
		int id;
		string text, type;
		cout << "User ID: ";
		cin >> id;
		cin.ignore();
		cout << "Describing the complaint and issue: ";
		getline(cin, text);

		if (searchNodeAndReturn(id) == nullptr) {
			cout << "\nThere is no User with this ID! Try again with a different ID.\n";
			return;
		}

		DLL<User>::Node* user = searchNodeAndReturn(id);
		type = user->data.getType();

		Complaint* newComplaint = new Complaint(id, text, type);

		int priority = newComplaint->checkAndReturnPriority(type);
		cout << "\n\nPRIORITY FOR THIS IS: " << priority;


		complaintQueue.insert(*newComplaint);

		if (complaintIndex.searchGroup(id))
		{
			SLL<Complaint*>* existingSLL = complaintIndex.search(id);

			if (existingSLL->searchComplaint(newComplaint))
			{
				cout << "\nComplaint already exists.\n";
			}
			else
			{
				existingSLL->insertAtEnd(newComplaint);
			}
		}
		else
		{
			SLL<Complaint*>* newSLL = new SLL<Complaint*>;
			newSLL->insertAtStart(newComplaint);
			complaintIndex.insert(id, *newSLL);
		}
		cout << "\nComplaint Registered Successfully with Complaint ID: " << newComplaint->getComplaintID() << endl;

	}
	void ServiceComplaint()// --process and remove the highest priority complaint.
	{
		if (complaintQueue.isEmpty()) {
			cout << "No complaints to service.\n";
		}
		else
		{
			Complaint maxPriorityComp = complaintQueue.getMax(); // Get highest-priority complaint
			complaintQueue.deleteMax(); // Remove it from the priority queue

			cout << "Servicing Complaint:\n";
			maxPriorityComp.printUser();


			if (complaintIndex.searchGroup(maxPriorityComp.getUserID()))
			{
				complaintIndex.removeNodeinSLL(maxPriorityComp.getUserID(), &maxPriorityComp);
			}

			cout << "\n\nAfter Servicing, the priority queue is:\n\n";
			complaintQueue.printHeap();
		}
	}
	void displayComplaintsByUserID(int userID)
	{
		cout << "\n Complaint from User: " << userID << ":\n";
		complaintIndex.searchAndDisplayComplaint(userID);

	}
	void printComplaintsByCountryAVL(const string& country)
	{
		if (!countryIndex.isEmpty())
		{
			if (countryIndex.searchGroup(country))
			{
				cout << "\nUsers in Group Country Index are: " << country << " : \n";
				SLL<DLL<User>::Node*>* userSLL = countryIndex.search(country);


				DLL<User>::Node* temp = userSLL->Head->next->data;
				while (temp)
				{
					displayComplaintsByUserID(temp->data.getUserID());
					temp = temp->next;
				}
			}
			else
			{
				cout << "\nNo users found from " << country << ".\n";
			}
		}

	}

	void printComplaintsByCountryHash(const string& country)
	{
		if (!hashCountryIndex.isEmpty())
		{
			cout << "\nUsers in Group Country Index are: " << country << " : \n";
			SLL<DLL<User>::Node*>* userSLL = hashCountryIndex.search(country, 1);

			if (userSLL != nullptr && userSLL->Head != nullptr)
			{
				// Iterate through the user list to display complaints
				DLL<User>::Node* temp = userSLL->Head->next->data;
				while (temp != nullptr)
				{
					displayComplaintsByUserID(temp->data.getUserID());
					temp = temp->next;
				}
			}
			else
			{
				cout << "\nNo users found from " << country << ".\n";
			}
		}
		else
		{
			cout << "\nCountry index is empty.\n";
		}
	}


	void increasePriority()
	{
		int cid = 0;
		cout << "Enter the Complaint ID of the complaint you want to priotize : ";
		cin >> cid;
		complaintQueue.incrPriorirty(cid);
		cout << "\nHeap after increasing Priority\n";
		complaintQueue.printHeap();

	}

	void printDLL()
	{
		DLL<User>::Node* current = myList.head;
		while (current != nullptr)
		{
			User& user = current->data;
			user.printUser();
			current = current->next;
		}
	}


	bool isDuplicate(int id, const string& name, const string& email)
	{
		if (searchNodeAndReturn(id) != nullptr || searchNodeAndReturnByName(name) != nullptr || searchNodeAndReturnByEmail(email) != nullptr)
		{
			return true;
		}
		return false;
	}


};
////////				~~~			MAIN					~~~
int main()
{
	UserList myUserList;
	int choice = 0;
	cout << "\n~~~~~\t\tUser Management Menu\t\t~~~~~" << endl;
	cout << "1. Insert User" << endl;
	cout << "2. Search User " << endl;
	cout << "3. Delete User " << endl;
	cout << "4. Display All Users " << endl;
	cout << "5. Register a Complaint " << endl;
	cout << "6. Service a Complaint " << endl;
	cout << "7. Increase Priority of a Complaint " << endl;
	cout << "8. Display Complaints of a Specific UserID " << endl;
	cout << "9. Print complaints registered by users of the given country " << endl;
	cout << "10. Exit" << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	while (choice != 10)
	{
		if (choice == 1)
		{
			cout << "\nEnter User Details for Insertion:" << endl;
			int id;
			string name, email, country, type;
			cout << "ID: ";
			cin >> id;
			cin.ignore();
			cout << "Name: ";
			getline(cin, name);
			cout << "Email: ";
			getline(cin, email);
			cout << "Country: ";
			getline(cin, country);
			cout << "Type (p (platinum) / g (gold) / s (silver) / n (new) / r (regular)): ";
			getline(cin, type);

			if (type == "p" || type == "P" || type == "g" || type == "G" || type == "s" || type == "S" || type == "n" || type == "N" || type == "r" || type == "R")
			{
				if (myUserList.isDuplicate(id, name, email))
				{
					cout << "\nUser already exists !! Try again with different name , id or email";
				}
				else
				{
					myUserList.insertUser(id, name, email, country, type);
					cout << "\nUser added successfully!\n";
				}
			}
			else
			{
				cout << "\nNot insertrd !! You didn't entered valid type \n";
			}

		}
		else if (choice == 2)
		{
			int sChoice = 0;
			cout << "Now , Select one of these: \n";
			cout << "1. Search User by ID in AVL Index" << endl;
			cout << "2. Search User by Name in AVL Index" << endl;
			cout << "3. Search User by Email in AVL Index" << endl;
			cout << "4. Search Users by country in AVL Index" << endl;
			cout << "5. Search Users by Type in AVL Index" << endl << endl;

			cout << "6. Search User by ID in Hash Table" << endl;
			cout << "7. Search User by Name in Hash Table" << endl;
			cout << "8. Search User by Email in Hash Table" << endl;
			cout << "9. Search Users by country in Hash Table" << endl;
			cout << "10. Search Users by Type in Hash Table" << endl;
			cout << "Enter Choice: ";
			cin >> sChoice;

			if (sChoice == 1)
			{
				int searchId;
				cout << "\nEnter ID to Search: ";
				cin >> searchId;
				myUserList.searchUser(searchId);
			}
			else if (sChoice == 2)
			{
				string searchName;
				cout << "\nEnter Name to Search: ";
				cin.ignore();
				getline(cin, searchName);
				myUserList.searchUserbyName(searchName);
			}
			else if (sChoice == 3)
			{
				string searchEmail;
				cout << "\nEnter Email to Search: ";
				cin.ignore();
				getline(cin, searchEmail);
				myUserList.searchUserbyEmail(searchEmail);
			}
			else if (sChoice == 4)
			{
				string searchCountry;
				cout << "\nEnter Country to Search Users For: ";
				cin.ignore();
				getline(cin, searchCountry);
				myUserList.searchUserbyCountry(searchCountry);
			}
			else if (sChoice == 5)
			{
				string searchType;
				cout << "\nEnter Type to Search Users For: ";
				cin.ignore();
				getline(cin, searchType);
				myUserList.searchUserbyType(searchType);
			}
			else if (sChoice == 6)
			{
				int searchId;
				cout << "\nEnter ID to Search: ";
				cin >> searchId;
				myUserList.searchUserIdHash(searchId);
			}
			else if (sChoice == 7)
			{
				string searchName;
				cout << "\nEnter Name to Search: ";
				cin.ignore();
				getline(cin, searchName);
				myUserList.searchUserByNameHash(searchName);
			}
			else if (sChoice == 8)
			{
				string searchEmail;
				cout << "\nEnter Email to Search: ";
				cin.ignore();
				getline(cin, searchEmail);
				myUserList.searchUserByEmailHash(searchEmail);
			}
			else if (sChoice == 9)
			{
				string searchCountry;
				cout << "\nEnter Country to Search Users For: ";
				cin.ignore();
				getline(cin, searchCountry);
				myUserList.searchUserbyCountryHash(searchCountry);
			}
			else if (sChoice == 10)
			{
				string searchType;
				cout << "\nEnter Type to Search Users For: ";
				cin.ignore();
				getline(cin, searchType);
				myUserList.searchUserbyTypeHash(searchType);
			}
			else
			{
				cout << "\n Invalid Input ";
			}

		}
		else if (choice == 3)
		{
			int dChoice = 0;
			cout << "Now , Select one of these: \n";
			cout << "1. Delete User by ID in EveryThing " << endl;
			cout << "2. Delete User by Name in AVL index" << endl;
			cout << "3. Delete User by Email in AVL index" << endl;
			cout << "4. Delete Users by country in Group AVL index" << endl;
			cout << "5. Delete Users by Type in AVL Group index" << endl << endl << endl;

			cout << "6. Delete User by ID in Hash ID Table  " << endl;
			cout << "7. Delete User by Name in Hash Name Table " << endl;
			cout << "8. Delete User by Email in Email ID Table " << endl;
			cout << "9. Delete Users by country in Group Hash Country Table " << endl;
			cout << "10. Delete Users by Type in Group Hash Type Table " << endl;
			cout << "Enter Choice: ";
			cin >> dChoice;
			if (dChoice == 1)
			{
				int deleteId;
				cout << "\nEnter ID to Delete: ";
				cin >> deleteId;
				myUserList.deleteUser(deleteId);
			}
			else if (dChoice == 2)
			{
				string deleteName;
				cout << "\nEnter Name to Delete: ";
				cin.ignore();
				getline(cin, deleteName);
				myUserList.deleteUserByName(deleteName);
			}
			else if (dChoice == 3)
			{
				string deleteEmail;
				cout << "\nEnter Email to Delete: ";
				cin.ignore();
				getline(cin, deleteEmail);
				myUserList.deleteUserByEmail(deleteEmail);
			}
			else if (dChoice == 4)
			{
				string deleteCountry;
				cout << "\nEnter Country to delete Users For: ";
				cin.ignore();
				getline(cin, deleteCountry);
				myUserList.deleteUserByCountry(deleteCountry);
			}
			else if (dChoice == 5)
			{
				string deleteType;
				cout << "\nEnter Type to delete Users For: ";
				cin.ignore();
				getline(cin, deleteType);
				myUserList.deleteUserByType(deleteType);
			}
			else if (dChoice == 6)
			{
				int deleteId;
				cout << "\nEnter ID to Delete: ";
				cin >> deleteId;
				myUserList.deleteUserIDHash(deleteId);
			}
			else if (dChoice == 7)
			{
				string deleteName;
				cout << "\nEnter Name to Delete: ";
				cin.ignore();
				getline(cin, deleteName);
				myUserList.deleteUserByNameHash(deleteName);
			}
			else if (dChoice == 8)
			{
				string deleteEmail;
				cout << "\nEnter Email to Delete: ";
				cin.ignore();
				getline(cin, deleteEmail);
				myUserList.deleteUserByEmailHash(deleteEmail);
			}
			else if (dChoice == 9)
			{
				string deleteCountry;
				cout << "\nEnter Country to delete Users For: ";
				cin.ignore();
				getline(cin, deleteCountry);
				myUserList.deleteUserByCountryHash(deleteCountry);
			}
			else if (dChoice == 10)
			{
				string deleteType;
				cout << "\nEnter Type to delete Users For: ";
				cin.ignore();
				getline(cin, deleteType);
				myUserList.deleteUserByTypeHash(deleteType);
			}
			else
			{
				cout << "\n Invalid Input ";
			}

		}
		else if (choice == 4)
		{
			int displayChoice = 0;
			cout << "\n 1- Display from AVL Tree \n";
			cout << "\n 2- Display from HAsh Table \n";
			cout << "\nEnter your choice : ";
			cin >> displayChoice;
			if (displayChoice == 1)
			{
				int pChoice = 0;
				cout << "Now , Select one of these: \n";
				cout << "1. Display User by ID  " << endl;
				cout << "2. Display User by Name" << endl;
				cout << "3. Display User by Email" << endl;
				cout << "4. Display ALL Users by country" << endl;
				cout << "5. Display ALL Users by Type" << endl;
				cout << "6. Display ALL Users by a specific Country" << endl;
				cout << "7. Display ALL Users by a specific Type" << endl;
				cout << "Enter Choice: ";
				cin >> pChoice;
				if (pChoice == 1)
				{
					cout << "\nDisplaying All Users by ID:\n";
					myUserList.printAllUsersByID();
				}
				else if (pChoice == 2)
				{
					cout << "\nDisplaying All Users by Name:\n";
					myUserList.printAllUsersByName();
				}
				else if (pChoice == 3)
				{
					cout << "\nDisplaying All Users by Email:\n";
					myUserList.printAllUsersByEmail();
				}
				else if (pChoice == 4)
				{
					cout << "\nDisplaying All Users by Country:\n";
					myUserList.printAllUsersByCountry();
				}
				else if (pChoice == 5)
				{
					cout << "\nDisplaying All Users by Type:\n";
					myUserList.printAllUsersByType();
				}
				else if (pChoice == 6)
				{
					string todisplayCountry;
					cout << "\nEnter Country to find its Users: ";
					cin.ignore();
					getline(cin, todisplayCountry);
					cout << "\nDisplaying All Users by this Country:\n";
					myUserList.displayUsersByCountry(todisplayCountry);
				}
				else if (pChoice == 7)
				{
					string todisplayType;
					cout << "\nEnter Type to find its Users: ";
					cin.ignore();
					getline(cin, todisplayType);
					cout << "\nDisplaying All Users by this Type:\n";
					myUserList.displayUsersByType(todisplayType);
				}
				else
				{
					cout << "\nInvalid Input !!\n";
				}
			}

			else if (displayChoice == 2)
			{
				int pChoice = 0;
				cout << "Now , Select one of these: \n";
				cout << "1. Display User by ID  " << endl;
				cout << "2. Display User by Name" << endl;
				cout << "3. Display User by Email" << endl;
				cout << "4. Display ALL Users by country" << endl;
				cout << "5. Display ALL Users by Type" << endl;
				cout << "6. Display ALL Users by a specific Country" << endl;
				cout << "7. Display ALL Users by a specific Type" << endl;
				cout << "Enter Choice: ";
				cin >> pChoice;
				if (pChoice == 1)
				{
					cout << "\nDisplaying All Users by ID from hash Table:\n";
					myUserList.printAllUsersByHashID();
				}
				else if (pChoice == 2)
				{
					cout << "\nDisplaying All Users by Name from hash Table:\n";
					myUserList.printAllUsersByHashName();
				}
				else if (pChoice == 3)
				{
					cout << "\nDisplaying All Users by Email from hash Table :\n";
					myUserList.printAllUsersByHashEmail();
				}
				else if (pChoice == 4)
				{
					cout << "\nDisplaying All Users by Country from hash Table :\n";
					myUserList.printAllUsersByHashCountry();
				}
				else if (pChoice == 5)
				{
					cout << "\nDisplaying All Users by Type from hash Table :\n";
					myUserList.printAllUsersByHashType();
				}
				else if (pChoice == 6)
				{
					string todisplayCountry;
					cout << "\nEnter Country to find its Users: ";
					cin.ignore();
					getline(cin, todisplayCountry);
					cout << "\nDisplaying All Users by this Country from hash Table :\n";
					myUserList.displayUsersByCountryHash(todisplayCountry);
				}
				else if (pChoice == 7)
				{
					string todisplayType;
					cout << "\nEnter Type to find its Users: ";
					cin.ignore();
					getline(cin, todisplayType);
					cout << "\nDisplaying All Users by this Type from hash Table:\n";
					myUserList.displayUsersByTypeHash(todisplayType);
				}
				else
				{
					cout << "\nInvalid Input !!\n";
				}
			}
			else
			{
				cout << "\nInvalid Input !!\n";
			}
		}
		else if (choice == 5)
		{
			myUserList.RegisterComplaint();
		}
		else if (choice == 6)
		{
			myUserList.ServiceComplaint();
		}
		else if (choice == 7)
		{
			myUserList.increasePriority();
		}
		else if (choice == 8)
		{
			int id = 0;
			cout << "Enter the User ID of the complaint you want to display : ";
			cin >> id;
			myUserList.displayComplaintsByUserID(id);
		}
		else if (choice == 9)
		{
			string country;
			cout << "Enter the name of country you want user complaints to display : ";
			cin.ignore();
			getline(cin, country);

			cout << " \n1- AVL Index Printing\n2- Hash Table Printing\n";
			int input;
			cout << "\nEnter : ";
			cin >> input;
			if (input == 1)
			{
				myUserList.printComplaintsByCountryAVL(country);
			}
			else if (input == 2)
			{
				myUserList.printComplaintsByCountryHash(country);
			}
			else
			{
				cout << "\nInvalid Input\n";
			}
		}
		else
		{
			cout << "\nNot an option try Again!!!\n";
		}
		cout << "\t\t\n\nDone with this Service Try something else";
		cout << "\n~~~~~\t\tUser Management Menu\t\t~~~~~" << endl;
		cout << "1. Insert User" << endl;
		cout << "2. Search User" << endl;
		cout << "3. Delete User " << endl;
		cout << "4. Display All Users " << endl;
		cout << "5. Register a Complaint " << endl;
		cout << "6. Service a Complaint " << endl;
		cout << "7. Increase Priority of a Complaint " << endl;
		cout << "8. Display Complaints of a Specific UserID " << endl;
		cout << "9. Print complaints registered by users of the given country " << endl;
		cout << "10. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
	}
}
