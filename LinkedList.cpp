#include <iostream>
#include <initializer_list>
using namespace std;

typedef unsigned int uint;

template<typename T>
class LinkedList
{
	private:
		class Node
		{
			public:
				T value;
				Node* next;

				Node(T value) : value{ value }, next{ nullptr } {}
		};

		Node* _first;
		Node* _last;

		Node* getNodeByIndex(uint index) const
		{
			if (index >= getSize())
				throw "Out of range";

			Node* current = _first;
			for (size_t i = 0; i < index; i++)
			{
				current = current->next;
			}

			return current;
		}

	public:
		LinkedList() : _first{ nullptr }, _last{ nullptr } {}

		LinkedList(initializer_list<T> list) : LinkedList()
		{
			for (auto i : list)
			{
				addBack(i);
			}
		}

		LinkedList(const LinkedList& list) : LinkedList()
		{
			Node* current = list._first;
			while (current)
			{
				addBack(current->value);
				current   = current->next;
			}
		}

		LinkedList(LinkedList&& list)
		{
			Node* current    = list._first;
			_first           = current;
			_last            = list._last;

			while (current)
			{
				_first->next = current->next;
				_first       = _first->next;

				current      = current->next;
			}
			_first           = list._first;

			list._first      = nullptr;
			list._last       = nullptr;
		}

		~LinkedList()
		{
			if (!isEmpty())
			{
				Node* current = _first->next;

				while (current)
				{
					delete _first;
					_first    = current;
					current   = current->next;
				}

				delete _first;

				_first        = nullptr;
				_last         = nullptr;
			}
		}

		bool isEmpty() const
		{
			return _first == nullptr;
		}

		uint getSize() const
		{
			uint counter  = 0;

			Node* current = _first;
			while (current)
			{
				current   = current->next;
				counter++;
			}

			return counter;
		}

		LinkedList& clear()
		{
			this->~LinkedList();

			return *this;
		}

		T getLast()
		{
			return _last->value;
		}

		T getFirst()
		{
			return _first->value;
		}

		T getByIndex(uint index)
		{
			return getNodeByIndex(index)->value;
		}

		T setByIndex(uint index, T value)
		{
			Node* node  = getNodeByIndex(index);
			T current   = node->value;

			node->value = value;

			return current;
		}

		T deleteByIndex(uint index) 
		{
			if (index >= getSize())
				throw "Out of range";

			T value;

			if (index == 0)
				value            = deleteForward();

			else if (index == getSize() - 1)
				value            = deleteBack();

			else
			{
				Node* nodeDist       = getNodeByIndex(index);
				Node* nodeBeforeDist = getNodeByIndex(index - 1);
				
				value                = nodeDist->value;

				nodeBeforeDist->next = nodeDist->next;

				delete nodeDist;
			}

			return value;
		}

		LinkedList& insertByIndex(uint index, T value)
		{
			if (index >= getSize())
				throw "Out of range";

			if (index == 0)
				addForward(value);

			else if (index == getSize() - 1)
			{
				Node* node = getNodeByIndex(index);

				addBack(_last->value);

				node->value = value;
			}

			else
			{
				Node* newNode = new Node(value);
				Node* nodeDist = getNodeByIndex(index);
				Node* nodeBeforeDist = getNodeByIndex(index - 1);

				nodeBeforeDist->next = newNode;
				newNode->next = nodeDist;
			}
		}

		LinkedList& addBack(T value)
		{
			Node* node      = new Node(value);

			if (isEmpty())
			{
				_first      = node;
				_last       = node;
			}
			else
			{
				_last->next = node;
				_last       = node;
			}

			return *this;
		}

		LinkedList& addForward(T value)
		{
			Node* node     = new Node(value);

			if (isEmpty())
			{
				_first     = node;
				_last      = node;
			}
			else
			{
				node->next = _first;
				_first     = node;
			}

			return *this;
		}

		T deleteBack()
		{
			if (isEmpty())
				throw "Out of range";

			Node* nodeBeforeDist = getNodeByIndex(getSize() - 1 - 1);
			T value              = _last->value;

			delete _last;

			nodeBeforeDist->next = nullptr;
			_last                = nodeBeforeDist;

			return value;
		}

		T deleteForward()
		{
			if (isEmpty())
				throw "Out of range";

			Node* current = _first;
			T value       = current->value;

			_first = current->next;

			delete current;

			return value;
		}

		T& operator[](uint index)
		{
			return getNodeByIndex(index)->value;
		}

		uint operator()()
		{
			return getSize();
		}

		T operator()(uint index)
		{
			return deleteByIndex(index);
		}

		T operator()(uint index, T value)
		{
			return setByIndex(index, value);
		}

		friend ostream& operator<<(ostream& out, const LinkedList& list)
		{
			Node* current = list._first;

			while (current)
			{
				out << current->value << '\t';
				current   = current->next;
			}
			out << endl;

			return out;
		}
};

int main()
{
	LinkedList<int> list;

	list.addBack(4);
	list.addBack(8);
	list.addBack(16);

	cout << list << endl;

	return 0;
}
