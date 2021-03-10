#pragma once

template <typename T>
class LinkedList
{
public:
	struct Node
	{
		T value;
		Node* next = nullptr;
	};

	~LinkedList();

	void PushFront(const T& value);
	void InsertAfter(Node* node, const T& value);
	void RemoveAfter(Node* node);
	void PopFront();

	Node* GetHead() { return head; }
	const Node* GetHead() const { return head; }

private:
	Node* head = nullptr;
	Node* _end = nullptr;
};

template <typename T>
LinkedList<T>::~LinkedList()
{
	auto* ptr = head;
	
	while (ptr != nullptr)
	{
		auto* tmp = ptr->next;
		delete ptr;

		ptr = tmp;
	}
}

template <typename T>
void LinkedList<T>::PushFront(const T& value)
{
	Node* newNode = new Node { value };
	newNode->next = head;

	head = newNode;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& value)
{
	if (node == nullptr)
	{
		PushFront(value);
	}
	else
	{
		Node* newNode = new Node { value, node->next };
		node->next = newNode;
	}
	
}

template <typename T>
void LinkedList<T>::RemoveAfter(Node* node)
{
	if (node == nullptr)
	{
		PopFront();
	}
	else
	{
		if(node->next != nullptr)
		{
			Node* tmp = node->next;
			node->next = tmp->next;
			delete tmp;
		}
	}
}

template <typename T>
void LinkedList<T>::PopFront()
{
	if (head == nullptr)
		return;

	auto tmp = head->next;
	delete head;

	head = tmp;
}