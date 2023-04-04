#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray(int _capacity = 10);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T& operator[](int);    
    void sort();
    bool is_sorted();
    void reverse();
    string array_to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->capacity = _capacity;
    this->array = new T[_capacity];
    this->front = this->back = -1;//empty
}

template <class T>
CircularArray<T>::~CircularArray()
{
	delete [] array;
}

template <class T>
void CircularArray<T>::push_front(T data) {
	if (is_empty()) {
		front = back = 0;
		array[front] = data;
	} else if (is_full()) {
		cout << "Error: Array is full\n";
	} else {
		front = prev(front);
		array[front] = data;
	}
}

template <class T>
void CircularArray<T>::push_back(T data) {
	if (is_empty()) {
		front = back = 0;
		array[back] = data;
	} else if (is_full()) {
		cout << "Error: Array is full\n";
	} else {
		back = next(back);
		array[back] = data;
	}
}

template <class T>
void CircularArray<T>::insert(T data, int pos) {
	if (is_full()) {
		cout << "Error: Array is full\n";
	} else if (pos == 0 || pos > size()) {
		cout << "Error: Invalid position\n";
	} else if (pos == 0) {
		push_front(data);
	} else if (pos == size()) {
		push_back(data);
	} else {
		int i = back;
		while (i != prev(front)) {
			array[next(i)] = array[i];
			if (next(i) == next(pos + front)) {
				break;
			}
			i = prev(i);
		}
		array[next(pos+front)] = data;
		back = next(back);
	}
}

template <class T>
T CircularArray<T>::pop_front() {
	if (is_empty()) {
		cout << "Error: Array is empty\n";
		return T();
	} else {
		T data = array[front];
		if (front == back) {
			front = back = -1;
		} else {
			front = next(front);
		}
		return data;
	}
}

template <class T>
T CircularArray<T>::pop_back() { 
	if (is_empty()) {
		cout << "Error: Array is empty\n";
		return T();
	} else {
		T data = array[back];
		if (front == back) {
			front = back = -1;
		} else {
			back = prev(back);
		}
		return data;
	}
}

template <class T>
bool CircularArray<T>::is_full() {
    return (size() == capacity);
}

template <class T>
bool CircularArray<T>::is_empty()
{
    return front == -1 && back == -1;
}

template <class T>
int CircularArray<T>::size() {
	if (is_empty()) {
		return 0;
	} else if (back >= front) {
		int size = (back - front + 1);
		cout << size << endl;
		return size;
	} else {
		int size = (capacity - front + back + 1);
		cout << size << endl;
		return size;
	}
}

template <class T>
void CircularArray<T>::clear() {
	front = back = -1;
}

template <class T>
T& CircularArray<T>::operator[](int index) {
	if (index < 0 || index >= size()) {
		throw out_of_range("Index out of bounds");
	} else {
		return array[(front + index) % capacity];
	}
}

template <class T>
void CircularArray<T>::sort() {
	// sort the elements in the array
	int n = size();
	if (n > 1) {
		for (int i = 0; i < n - 1; i++) {
			int min_idx = i;
			for (int j = i + 1; j < n; j++) {
				if (array[(front + j) % capacity] < array[(front + min_idx) % capacity]) {
				min_idx = j;
				}
			}
			T temp = array[(front + i) % capacity];
			array[(front + i) % capacity] = array[(front + min_idx) % capacity];
			array[(front + min_idx) % capacity] = temp;
		}
	}
}

template <class T>
bool CircularArray<T>::is_sorted() {
	int n = size();
	if (n > 1) {
		for (int i = 0; i < n - 1; i++) {
			if (array[(front + i) % capacity] > array[(front + i + 1) % capacity]) {
				return false;
			}
		}
	}
	return true;
}

template <class T>
void CircularArray<T>::reverse() {
	int n = size();
	if (n > 1) {
		int i = front;
		int j = back;
		while (i < j) {
			T temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i = next(i);
			j = prev(j);
		}
	}
}

template <class T>
string CircularArray<T>::array_to_string(string sep) {
	int n = size();
	cout << n << endl;
	if (n == 0) {
		return "";
	} else {
		string s = to_string(array[front]);
		for (int i = 1; i < n; i++) {
			s += sep + to_string(array[(front + i) % capacity]);
		}
		cout << s << endl;
		return s;
	}
}

template <class T>
int CircularArray<T>::next(int index) {
	return (index + 1) % capacity;
}

template <class T>
int CircularArray<T>::prev(int index) {
	return (index - 1 + capacity) % capacity;
}