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
		T_clas value;	// дані
		Node* next;	// зв'язок з наступним елементом
		Node* prev;	// зв'язок з попереднім елементом
	};

	Node* head;	// вказівник на голову списка
	Node* tail; // вказівник на хвіст списка

	int size;	// розмір списка
public:
	// Конструктор за замовчуванням
	List() : head(nullptr), tail(nullptr), size(0) { }
	// Деструктор
	~List()
	{
		// Очищення списка
		while (!IsEmpty())
		{
			DeleteHead();
		}
	}

	// Перевірка чи список порожній
	bool IsEmpty() const
	{
		return size == 0;
	}
	// Повернення кількості елементів
	int GetCount() const
	{
		return size;
	}

	// Додати елемент на початок
	void AddToHead(T_clas value)
	{
		// створення нового елемента
		Node* newElem = new Node;
		// задавання значення новогму елементу
		newElem->value = value;
		// наступним елементом буде поточна голова
		newElem->next = head;
		// попереднього елемента не існує
		newElem->prev = nullptr;

		// якщо список був порожній
		if (IsEmpty())
		{
			// новий елемент стає головою та хвостом
			head = tail = newElem;
		}
		// якщо елементи вже існують
		else
		{
			// зв'язуємо поточну голову з новим елементом
			head->prev = newElem;
			// оновлюємо вказівник на голову
			head = newElem;
		}
		++size; // збільшуємо розмір списка
	}

	// Додати елемент в кінець
	void AddToTail(T_clas value)
	{
		// створення нового елемента
		Node* newElem = new Node;
		// задавання значення новому елементу
		newElem->value = value;
		// за хвостом елементів немає
		newElem->next = nullptr;
		// зв'язуємо новий елемент з попереднім (поточним хвостом)
		newElem->prev = tail;

		// якщо список був порожній
		if (IsEmpty())
		{
			// новий елемент стає головою та хвостом
			head = tail = newElem;
		}
		// якщо елементи вже існують
		else
		{
			// зв'язуємо останній елемен з новим хвістом
			tail->next = newElem;
			// оновлюємо вказівник на хвіст
			tail = newElem;
		}
		++size; // збільшуємо розмір списка
	}

	// Видалити елемент з початку
	void DeleteHead()
	{
		// якщо список порожній, тоді видалення не відбувається
		if (IsEmpty()) return;

		// якщо елементи існують, тоді зберігаємо елемент після голови
		Node* temp = head->next;
		// видаляємо голову
		delete head;

		// якщо елемента після голови не існувало (тобто елемент був єдиним в списку)
		if (temp == nullptr)
		{
			// очищаємо голову та хвіст
			head = tail = nullptr;
		}
		// якщо елемент після голови наявний
		else
		{
			// очищаємо зв'язок з видаленою головою
			temp->prev = nullptr;
			// елемент після видаленої голови стає поточною головою
			head = temp;
		}
		--size; // зменшуємо розмір списка
	}

	// Видалити елемент з кінця
	void DeleteTail()
	{
		// якщо список порожній, тоді видалення не відбувається
		if (IsEmpty()) return;

		// якщо елемента після голови не існує (тобто елемент єдиний в списку) 
		if (head->next == nullptr)
		{
			// видаляємо голову (єдиний елемент)
			delete head;
			// очищаємо голову та хвіст
			head = tail = nullptr;
		}
		// якщо елементи існували
		else
		{
			// знаходимо вказівник на передостанній елемент (елемент перед поточним хвостом)
			Node* temp = tail->prev;

			// видаляємо останній елемент
			delete temp->next;
			// очищаємо зв'язок з останнім елементом
			temp->next = nullptr;
			// оновлюємо хвіст
			tail = temp;
		}
		--size; // зменшуємо розмір списка
	}

	// Додавання елемента в позицію
	void Add(T_clas value, int pos)
	{
		// якщо позиція не вірна, додавання не відбувається
		if (pos <= 0 || pos > size + 1) return;
		// якщо додаємо на початок, то використовуємо готовий метод
		if (pos == 1)
		{
			AddToHead(value);
			return;
		}
		// якщо додаємо в кінець, то використовуємо готовий метод
		if (pos == size + 1)
		{
			AddToTail(value);
			return;
		}

		// якщо додаємо в середину
		// створюємо новий елемент
		Node* newElem = new Node;
		// задаємо йому значення
		newElem->value = value;

		// знаходимо елемент на тій позиції, яка буде містити новий елемент
		Node* current = head;
		for (int i = 0; i < pos - 1; ++i)
		{
			current = current->next;
		}

		// зв'язуємо новий елемент з наступним
		newElem->prev = current->prev;
		// зв'язуємо наступний елемент з новим
		current->prev->next = newElem;

		// зв'язуємо попередній елемент з новим
		current->prev = newElem;
		// зв'язуємо новий елемент з попереднім
		newElem->next = current;

		++size; // збільшуємо розмір списка
	}

	// Видалення елемента з позиції
	void Delete(int pos)
	{
		// якщо позиція не вірна, видалення не відбувається
		if (pos <= 0 || pos > size) return;
		// якщо видаляємо з початку, то використовуємо готовий метод
		if (pos == 1)
		{
			DeleteHead();
			return;
		}
		// якщо видаляємо з кінця, то використовуємо готовий метод
		if (pos == size)
		{
			DeleteTail();
			return;
		}

		// знаходимо елемент, який будемо видаляти
		Node* current = head;
		for (int i = 0; i < pos - 1; ++i)
		{
			current = current->next;
		}

		// зв'язуємо попередній елемент з наступним, тобто проходимо повз елемента для видалення
		current->prev->next = current->next;
		// зв'язуємо наступний елемент з попереднім, тобто проходячи повз елемента для видалення
		current->next->prev = current->prev;
		// видаляємо елемент
		delete current;

		--size; // зменшуємо розмір списка
	}

	// Показ всіх елементів
	void Show() const
	{
		// показ всіх елементів списка (while)
		Node* elem = head;
		while (elem != nullptr)
		{
			// вивід занчення поточного елемента
			cout << elem->value << ", ";
			elem = elem->next;
		}

		// інші варіанти проходження по списку
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
