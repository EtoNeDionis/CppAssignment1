#include <iostream>
#include <sstream>
#include <vector>

class HashTable
{
public:
	HashTable();
	~HashTable();
	struct Entry
	{
		std::string Name;
		std::string Status = "never used";
	};

	void Print()
	{
		for (intptr_t i = 0; i < _size; i++)
		{
			if(_entries[i].Status == "occupied")
				std::cout << _entries[i].Name << " ";
		}
	}

	void Insert(const std::string entry)
	{
		if (IsEntryExists(entry))
			return;

		const int newIndex = GetInsertionIndex(entry);
		if (newIndex == -1)
			return;
		_entries[newIndex] = { entry.substr(1, entry.size()), "occupied"};

	}
	void Delete(const std::string entry)
	{
		if (!IsEntryExists(entry))
			return;
		_entries[GetIndex(entry)].Status = "tombstone";
	}

private:
	static const int _size = 26;
	Entry _entries[_size];
	
	int GetExpectedIndex(const std::string entry)
	{
		return entry.back() - 'a';
	}

	int GetIndex(const std::string entry)
	{
		const auto expectedIndex = GetExpectedIndex(entry);

		for (intptr_t i = expectedIndex; i < _size; i++)
		{
			if (_entries[i].Name == entry.substr(1, entry.size()))
				return i;
		}

		return -1;
	}

	bool IsEntryExists(const std::string entry) 
	{
		int index = GetExpectedIndex(entry);
		while (index < _size)
		{
			if (_entries[index].Name == entry.substr(1, entry.size()))
				return true;
			
			index++;
		}
		return false;
	}


	int GetInsertionIndex(const std::string entry)
	{
		int index = GetExpectedIndex(entry);
		while (index < _size)
		{
			if (_entries[index].Status == "never used" || _entries[index].Status == "tombstone")
				return index;

			index++;
		}

		return -1;
	}
};

HashTable::HashTable()
{
}

HashTable::~HashTable()
{
} 

int main()
{
	//DFsBa Asadpfoarange Aapple banana orange 
	std::string inputValues;
	std::vector<std::string> keys;
	HashTable hashTable;
	
	//get values
	std::getline(std::cin, inputValues);
	std::stringstream ss(inputValues);
	while (ss.good())
	{
		std::string token;
		ss >> token;

		switch (token.front())
		{
		case 'A':
			hashTable.Insert(token);
			break;

		case 'D':
			hashTable.Delete(token);
			break;

		default:
			break;
		}
	}

	hashTable.Print();
	return 0;
}

/*
	Aapple Apear Aorange Dpear Aapple Aapple Atomato Dapple Abanana
*/