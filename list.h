#pragma once
#include<iostream>
using namespace std;

template<class T_clas>
class List
{
private:
	// ��������� �������� ������
	struct Node
	{
		T_clas value;	// ���
		Node* next;	// ��'���� � ��������� ���������
		Node* prev;	// ��'���� � ��������� ���������
	};

	Node* head;	// �������� �� ������ ������
	Node* tail; // �������� �� ���� ������

	int size;	// ����� ������
public:
	// ����������� �� �������������
	List() : head(nullptr), tail(nullptr), size(0) { }
	// ����������
	~List()
	{
		// �������� ������
		while (!IsEmpty())
		{
			DeleteHead();
		}
	}

	// �������� �� ������ �������
	bool IsEmpty() const
	{
		return size == 0;
	}
	// ���������� ������� ��������
	int GetCount() const
	{
		return size;
	}

	// ������ ������� �� �������
	void AddToHead(T_clas value)
	{
		// ��������� ������ ��������
		Node* newElem = new Node;
		// ��������� �������� ������� ��������
		newElem->value = value;
		// ��������� ��������� ���� ������� ������
		newElem->next = head;
		// ������������ �������� �� ����
		newElem->prev = nullptr;

		// ���� ������ ��� �������
		if (IsEmpty())
		{
			// ����� ������� ��� ������� �� �������
			head = tail = newElem;
		}
		// ���� �������� ��� �������
		else
		{
			// ��'����� ������� ������ � ����� ���������
			head->prev = newElem;
			// ��������� �������� �� ������
			head = newElem;
		}
		++size; // �������� ����� ������
	}

	// ������ ������� � �����
	void AddToTail(T_clas value)
	{
		// ��������� ������ ��������
		Node* newElem = new Node;
		// ��������� �������� ������ ��������
		newElem->value = value;
		// �� ������� �������� ����
		newElem->next = nullptr;
		// ��'����� ����� ������� � ��������� (�������� �������)
		newElem->prev = tail;

		// ���� ������ ��� �������
		if (IsEmpty())
		{
			// ����� ������� ��� ������� �� �������
			head = tail = newElem;
		}
		// ���� �������� ��� �������
		else
		{
			// ��'����� ������� ������ � ����� ������
			tail->next = newElem;
			// ��������� �������� �� ����
			tail = newElem;
		}
		++size; // �������� ����� ������
	}

	// �������� ������� � �������
	void DeleteHead()
	{
		// ���� ������ �������, ��� ��������� �� ����������
		if (IsEmpty()) return;

		// ���� �������� �������, ��� �������� ������� ���� ������
		Node* temp = head->next;
		// ��������� ������
		delete head;

		// ���� �������� ���� ������ �� �������� (����� ������� ��� ������ � ������)
		if (temp == nullptr)
		{
			// ������� ������ �� ����
			head = tail = nullptr;
		}
		// ���� ������� ���� ������ �������
		else
		{
			// ������� ��'���� � ��������� �������
			temp->prev = nullptr;
			// ������� ���� �������� ������ ��� �������� �������
			head = temp;
		}
		--size; // �������� ����� ������
	}

	// �������� ������� � ����
	void DeleteTail()
	{
		// ���� ������ �������, ��� ��������� �� ����������
		if (IsEmpty()) return;

		// ���� �������� ���� ������ �� ���� (����� ������� ������ � ������) 
		if (head->next == nullptr)
		{
			// ��������� ������ (������ �������)
			delete head;
			// ������� ������ �� ����
			head = tail = nullptr;
		}
		// ���� �������� ��������
		else
		{
			// ��������� �������� �� ������������ ������� (������� ����� �������� �������)
			Node* temp = tail->prev;

			// ��������� ������� �������
			delete temp->next;
			// ������� ��'���� � ������� ���������
			temp->next = nullptr;
			// ��������� ����
			tail = temp;
		}
		--size; // �������� ����� ������
	}

	// ��������� �������� � �������
	void Add(T_clas value, int pos)
	{
		// ���� ������� �� ����, ��������� �� ����������
		if (pos <= 0 || pos > size + 1) return;
		// ���� ������ �� �������, �� ������������� ������� �����
		if (pos == 1)
		{
			AddToHead(value);
			return;
		}
		// ���� ������ � �����, �� ������������� ������� �����
		if (pos == size + 1)
		{
			AddToTail(value);
			return;
		}

		// ���� ������ � ��������
		// ��������� ����� �������
		Node* newElem = new Node;
		// ������ ���� ��������
		newElem->value = value;

		// ��������� ������� �� �� �������, ��� ���� ������ ����� �������
		Node* current = head;
		for (int i = 0; i < pos - 1; ++i)
		{
			current = current->next;
		}

		// ��'����� ����� ������� � ���������
		newElem->prev = current->prev;
		// ��'����� ��������� ������� � �����
		current->prev->next = newElem;

		// ��'����� ��������� ������� � �����
		current->prev = newElem;
		// ��'����� ����� ������� � ���������
		newElem->next = current;

		++size; // �������� ����� ������
	}

	// ��������� �������� � �������
	void Delete(int pos)
	{
		// ���� ������� �� ����, ��������� �� ����������
		if (pos <= 0 || pos > size) return;
		// ���� ��������� � �������, �� ������������� ������� �����
		if (pos == 1)
		{
			DeleteHead();
			return;
		}
		// ���� ��������� � ����, �� ������������� ������� �����
		if (pos == size)
		{
			DeleteTail();
			return;
		}

		// ��������� �������, ���� ������ ��������
		Node* current = head;
		for (int i = 0; i < pos - 1; ++i)
		{
			current = current->next;
		}

		// ��'����� ��������� ������� � ���������, ����� ��������� ���� �������� ��� ���������
		current->prev->next = current->next;
		// ��'����� ��������� ������� � ���������, ����� ��������� ���� �������� ��� ���������
		current->next->prev = current->prev;
		// ��������� �������
		delete current;

		--size; // �������� ����� ������
	}

	// ����� ��� ��������
	void Show() const
	{
		// ����� ��� �������� ������ (while)
		Node* elem = head;
		while (elem != nullptr)
		{
			// ���� �������� ��������� ��������
			cout << elem->value << ", ";
			elem = elem->next;
		}

		// ���� ������� ����������� �� ������
		// for
		for (Node* current = head; current != nullptr; current = current->next)
		{
			// TODO
		}

		// do while
		Node* current = head;
		do
		{
			// TODO
			current = current->next;
		} while (current->next != nullptr);
	}
};
