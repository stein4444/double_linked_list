#pragma once
#include<iostream>
using namespace std;


template<class T_clas>
class List
{
private:
	// Структура елемента списка
	struct Node
	{
		T_clas value;	
		Node* next;	
		Node* prev;	
	};

	Node* head;	
	Node* tail;

	int size;	
public:
	// Конструктор за замовчуванням
	List() : head(nullptr), tail(nullptr), size(0) { }
	// Деструктор
	~List()
	{
		while (!IsEmpty())
		{
			DeleteHead();
		}
	}
	//c-py constructor
	List(const List& other)
	{
		Node* current = other.head;
		while (current != nullptr)
		{
			AddToHead(current->value);
			current = current->next;
		}
	}
	//constructor move
	List(List&& other) {
		head = other.head;
		tail = other.tail;

		other.head = nullptr;
		other.tail = nullptr;
	}
	//operator = 
	List& operator=(List&& other) {
		this->DeleteAll();
		head = other.head;
		tail = other.tail;

		other.head = nullptr;
		other.tail = nullptr;

		return *this;
	}
	// Перевірка чи список порожній
	bool IsEmpty() const
	{
		return size == 0;
	}
	int GetCount() const
	{
		return size;
	}

	// Додати елемент на початок
	void AddToHead(T_clas value)
	{
		Node* newElem = new Node;
		newElem->value = value;
		newElem->next = head;
		newElem->prev = nullptr;
		if (IsEmpty())
		{
			head = tail = newElem;
		}
		else
		{
			head->prev = newElem;
			head = newElem;
		}
		++size; 
	}

	void AddToTail(T_clas value)
	{
		Node* newElem = new Node;
		newElem->value = value;
		newElem->next = nullptr;
		newElem->prev = tail;
		if (IsEmpty())
		{
			head = tail = newElem;
		}
		else
		{
			tail->next = newElem;
			tail = newElem;
		}
		++size;
	}

	// Видалити елемент з початку
	void DeleteHead()
	{
		if (IsEmpty()) return;
		Node* temp = head->next;
		delete head;
		if (temp == nullptr)
		{
			head = tail = nullptr;
		}
		else
		{
			temp->prev = nullptr;
			head = temp;
		}
		--size; 
	}

	void DeleteTail()
	{
		if (IsEmpty()) 
			return;

		if (head->next == nullptr)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			Node* temp = tail->prev;
			delete temp->next;
			temp->next = nullptr;
			tail = temp;
		}
		--size; 
	}

	void Add(T_clas value, int pos)
	{
		if (pos <= 0 || pos > size + 1) return;
		if (pos == 1)
		{
			AddToHead(value);
			return;
		}
		if (pos == size + 1)
		{
			AddToTail(value);
			return;
		}
		Node* newElem = new Node;
		newElem->value = value;
		Node* current = head;
		for (int i = 0; i < pos - 1; ++i)
		{
			current = current->next;
		}
		newElem->prev = current->prev;
		current->prev->next = newElem;
		current->prev = newElem;
		newElem->next = current;

		++size;
	}
	void Delete(int pos)
	{
		if (pos <= 0 || pos > size)
			return;
		if (pos == 1)
		{
			DeleteHead();
			return;
		}
		if (pos == size)
		{
			DeleteTail();
			return;
		}

		Node* current = head;
		for (int i = 0; i < pos - 1; ++i)
		{
			current = current->next;
		}
		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;

		--size; 
	}

	// Показ всіх елементів
	void Show() const
	{
		Node* elem = head;
		while (elem != nullptr)
		{
			cout << elem->value << ", ";
			elem = elem->next;
		}

	}
	void DeleteAll()
	{
		while (!IsEmpty())
		{
			DeleteHead();
		}
	}
	List operator-() const
	{
		List tmp;
			for (Node* current = head; current->next != nullptr; current = current->next)
			{
				tmp.AddToHead(current->value);
			}
			return tmp;
	}
	List operator+(List& other) const
	{
		List tmp(*this);
		Node* current = other.head;
		for (int i = this->size; i < other.size; ++i) {
			tmp.AddToTail(current->value);
		}
		return tmp;
	}
};

