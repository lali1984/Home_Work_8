//шаблон двусвязного списка
#pragma once
#include<stdexcept>
#include<iostream>

template <typename T>
struct Member
{
	T data_; //данные хронящиеся в члене списка
	Member<T>* next_; //указатель на следующий член
	Member<T>* prev_;//указатель на предыдущий член
};


template <typename T>
class List
{
private:
	
	//получение члена списка
	Member<T>* GetMember(int index)
	{

		Member<T>* it = begine_;//указатель на начало списка
		try {
			for (int i = 0; i < index; ++i)
				it = it->next_; //указатель вперед на указаное кол. index

			return it;
		}
		catch(std::out_of_range e) {
			std::cout << e.what();
		}
		
	}
	
	//проверка корректности индекса
	const bool  CorrectIndex(int index)
	{
		return (index >= 0) && (index < size_);
	}

public:
	// конструктор создает нулевой список
	List() : begine_(nullptr), end_(nullptr), size_(0) {} 

	// конструктор копирования
	List(List<T>& that)
	{
		Copy(that);
	}

	~List() 
	{
		Clear();
	}

	Member<T>* End()
	{
		return end_;
	}

	Member<T>* Begin()
	{
		return begine_;
	}


	Member<T>* NextIt()
	{
		Member<T>* it = it->next_;
		return it;
 	}

	//создание копии
	void Copy(List<T>& that) 
	{
		Clear();
		
		Member<T>* it = that.begine_;

		while (it != nullptr)
		{
			AddEnd(it->data_);
			it = it->next_;
		}
	}

	List<T>& operator=(List<T>& that)
	{
		Copy(that);
		return *this;
	}
	
	//оператор индексирования
	T& operator[](int index)
	{
		return GetMember(index)->data_;
	}

	//оператор индексирования константный
	const T& operator[](int index) const
	{
		return GetMember(index)->data_;
	}

	//узнать размер списка
	const int Size() const
	{
		return size_;
	}

	//добавление в конец списка
	void AddEnd(T data)
	{
		try
		{
			//создаем новый элемент списка
			Member<T>* that = new Member<T>;
			that->data_ = data;
			that->next_ = nullptr;
			that->prev_ = end_;

			if (end_ != nullptr)
				end_->next_ = that;

			if (size_ == 0)
				begine_ = end_ = that;
			else
				end_ = that;

			++size_;

		}
		// если не выделена память
		catch (std::bad_alloc e) 
		{
			std::cout << e.what() << "\n";
			return;
		}

	}
	
	//добавление в начало списка
	void AddBegine(T data)
	{
		try
		{
			Member<T>* that = new Member<T>;
			that->data_ = data;
			that->next_ = begine_;
			that->prev_ = nullptr;
		
			if (size_ > 0) {
				begine_->prev_ = that;
				begine_ = that;
			}
			else {
				begine_ = that;
				end_ = that;
			}

			++size_;
		}
		catch (std::bad_alloc e) {
			std::cout << e.what() << "\n";
		}
	}

	//вставка в заданое место
	void Insert(T data, int index)
	{
		if (!CorrectIndex(index))
			return;

		if (index == size_ - 1) {
			AddEnd(data);
			return;
		}

		if (index == 0) {
			AddBegine(data);
			return;
		}

		try	{
		Member<T>* prevInd = GetMember(index - 1);
		Member<T>* Ind = GetMember(index);
		Member<T>* that = new Member<T>;

		that->data_ = data;
		that->next_ = Ind;
		that->prev_ = prevInd;

		++size_;
		}
		catch (std::bad_alloc e) {
			std::cout << e.what() << "\n";
		}
	}

	//удалене по индексу
	void Dell(int index)
	{
		if (IsEmpty()) //проверяет пустой ли список
			return;

		if (!CorrectIndex(index)) //проверяет коректность индекса
			return;

		Member<T>* prevIn = GetMember(index - 1);
		Member<T>* nextIn = GetMember(index + 1);
		Member<T>* In = GetMember(index);

		if (prevIn != nullptr && size_ > 0)
			prevIn->next_ = nextIn;

		if (nextIn != nullptr && size_ > 0)
			nextIn->prev_ = prevIn;
	
		if (index == 0)
			begine_ = nextIn;

		if (index == size_ - 1)
			end_ = prevIn;

		delete In;

		--size_;
	}
	
	//удаление начала списка
	void DellBegine()
	{
		Dell(0);
	}

	//удаление конца списка
	void DellEnd()
	{
		Dell(size_ - 1);
	}

	//очистка списка
	void Clear()
	{
		int n = size_;
		for (int i = 0; i < n; ++i)
			Dell(0);
	}

	//постой ли список
	const bool IsEmpty()
	{
		return size_ == 0;
	}

private:
	//указатель на начало списка
	Member<T>* begine_;
	// указатель на конец списка
	Member<T>* end_; 
	// размер списка
	int size_; 
};

template <typename T>
const void Print(List<T>& list)
{
	for (int i = 0; i < list.Size(); ++i)
		std::cout << list[i] << " -> ";
	std::cout << "\n";
}

//***сортировка (быстрая)
//замена
template<typename T>
void Swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

//разбиение
template<typename T>
int Partition(List<T>& that, int start, int end)
{
	T pivot = that[end];
	int pIndex = start;

	for (int i = start; i < end; i++) {
		if (that[i] <= pivot) {
			Swap(that[i], that[pIndex]);
			pIndex++;
		}
	}

	Swap(that[pIndex], that[end]);
	return pIndex;
}

//процедура быстрой сортировки
template <typename T>
void Sort(List<T>& that, int start, int end)
{
	if (start >= end) {
		return;
	}

	int pivot = Partition(that, start, end);
	Sort(that, start, pivot - 1);
	Sort(that, pivot + 1, end);
}