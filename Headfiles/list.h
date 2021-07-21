#include"common.h"
template<typename T>
struct Node
{
	T value;
	Node* previous;
	Node* next;
	Node(T myvalue) {
		value = myvalue;
		previous = NULL;
		next = NULL;
	}
	Node* push_back(T newvalue)
	{
		Node* p = new Node(newvalue);
		Node* h = this;
		while (h->next != NULL)
		{
			h = h->next;
		}
		p->previous = h;
		h->next = p;
		return p;
	}
	Node* push_front(T newvalue)
	{
		Node* p = new Node(newvalue);
		p->next = this;
		this->previous = p;
		return p;
	}
};

template<class T>
class list {
private:
	Node<T>* head;
	Node<T>* tail;
	int nsize;
public:
	list() {
		head = NULL;
		tail = NULL;
		nsize = 0;
	}
	list(int n) {
		head = new Node<T>(T());
		tail = head;
		for (int i = 0; i < n - 1; i++) {
			tail = head->push_back(T());
		}
		nsize = n;
	}
	list(int n, T value) {
		head = new Node<T>(value);
		tail = head;
		for (int i = 0; i < n - 1; i++) {
			tail = head->push_back(value);
		}
		nsize = n;
	}
	list(const list& fat) {
		head = new Node<T>(fat.head->value);
		Node<T>* p = fat.head->next;
		while (p != NULL) {
			tail = head->push_back(p->value);
			p = p->next;
		}
		nsize = fat.nsize;
	}
	void push_back(T value) {
		if (head == NULL)
			head = new Node<T>(value);
		else
			tail = head->push_back(value);
		nsize++;
	}
	void push_front(T value) {
		if (head == NULL)
			head = new Node<T>(value);
		else
			head = head->push_front(value);
		nsize++;
	}
	int size() { return nsize; }
	bool empty() { return nsize == 0; }
	void clear() {
		while (tail != NULL)
		{
			Node<T>* ntail = tail->previous;
			delete tail;
			tail = ntail;
		}
		head = NULL;
		nsize = 0;
	}
	void resize(int n) {
		if (nsize > n) {
			Node<T>* p = head;
			for (int i = 0; i < n; i++) {
				p = p->next;
			}
			tail = p->previous;
			tail->next = NULL;
			while (p != NULL) {
				Node<T>* np = p;
				p = p->next;
				delete np;
				np = NULL;
			}
		}
		else if (nsize < n) {
			for (int i = nsize; i < n; i++) {
				head->push_back(T());
			}
		}
		nsize = n;
	}
	T& front() {
		if (nsize > 0) {
			return head->value;
		}
	}
	T& back() {
		if (nsize > 0) {
			return tail->value;
		}
	}
	void pop_back() {
		if (nsize <= 1) {
			delete head;
			head = NULL;
			tail = NULL;
			nsize = 0;
		}
		else {
			Node<T>* ntail = tail;
			tail = tail->previous;
			tail->next = NULL;
			delete ntail;
			ntail = NULL;
			nsize--;
		}
	}
	void pop_front() {
		if (nsize <= 1) {
			delete head;
			head = NULL;
			tail = NULL;
			nsize = 0;
		}
		else {
			Node<T>* nhead = head;
			head = head->next;
			head->previous = NULL;
			delete nhead;
			nhead = NULL;
			nsize--;
		}
	}
	void reverse() {
		Node<T>* p = tail;
		while (p != NULL) {
			swap(p->next, p->previous);
			p = p->next;
		}
		swap(head, tail);
	}
	void merge(list& p) {
		T* data = new T[nsize + p.nsize];
		tail->next = p.head;
		p.head->previous = tail;
		tail = p.tail;
		Node<T>* nhead = head;
		int i = 0;
		while (nhead != NULL) {
			data[i++] = nhead->value;
			nhead = nhead->next;
		}
		sort(data, data + nsize + p.nsize);
		nhead = head;
		i = 0;
		while (nhead != NULL) {
			nhead->value = data[i++];
			nhead = nhead->next;
		}
		nsize += p.nsize;
	}
	void insert(int index, T value) {
		if (index < nsize) {
			if (index == 0) {
				push_front(value);
			}
			else if (index == nsize - 1) {
				push_back(value);
			}
			else {
				Node<T>* node = new Node<T>(value);
				Node<T>* p = head;
				for (int i = 0; i < index && i < nsize; i++) {
					p = p->next;
				}
				node->previous = p->previous;
				node->next = p;
				node->previous->next = node;
				node->next->previous = node;
				nsize++;
			}
		}
		else {
			cout << "index out of range" << endl;
		}
	}
	void insert(int index, int num, T value)
	{
		if (index < nsize && num>0) {
			if (index == 0) {
				for (int i = 0; i < num; i++) {
					push_front(value);
				}
			}
			else if (index == nsize - 1) {
				for (int i = 0; i < num; i++) {
					push_back(value);
				}
			}
			else {
				Node<T>* node = new Node<T>(value);
				Node<T>* p = head;
				for (int i = 0; i < index && i < nsize; i++) {
					p = p->next;
				}
				Node<T>* nodetail = node;
				for (int i = 0; i < num - 1; i++)
				{
					nodetail = node->push_back(value);
				}
				node->previous = p->previous;
				nodetail->next = p;
				node->previous->next = node;
				nodetail->next->previous = nodetail;
				nsize += num;
			}
		}
		else {
			cout << "index out of range or num is illegal" << endl;
		}
	}
	void erase(int index) {
		if (index < nsize) {
			if (index == 0) {
				pop_front();
			}
			else if (index == nsize - 1) {
				pop_back();
			}
			else {
				Node<T>* p = head;
				for (int i = 0; i < index && i < nsize; i++) {
					p = p->next;
				}
				p->previous->next = p->next;
				p->next->previous = p->previous;
				delete p;
				p = NULL;
				nsize--;
			}
		}
		else {
			cout << "index out of range" << endl;
		}
	}

};