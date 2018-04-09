#pragma once
#include <vector>
#include <unordered_set>
#include <future>

template <typename T>
class SetUF
{
public:

	T									item;
	int									rank = 0;
	int									size = 1;
	SetUF<T>*							parrent = nullptr;
	std::unordered_set<SetUF<T>*>		successors;

	static SetUF<T>* makeSet(T item);
	static SetUF<T>* unionByRank(SetUF<T>* first, SetUF<T>* second);
	static SetUF<T>* find(SetUF<T>* item);
	static SetUF<T>* findRec(SetUF<T>* item);
	static SetUF<T>* findWithoutCompression(SetUF<T>* item);
	static void	  destroy();
	
	~SetUF();
private:
	static std::vector<SetUF<T>*> all_created;
	SetUF(T item);
	
};

template <typename T>
std::vector<SetUF<T>*> SetUF<T>::all_created;

template <typename T>
SetUF<T>* SetUF<T>::makeSet(T item)
{
	SetUF<T>* singleton = new SetUF<T>(item);
	all_created.push_back(singleton);
	return singleton;
}

template <typename T>
SetUF<T>* SetUF<T>::unionByRank(SetUF<T>* first, SetUF<T>* second)
{
	SetUF<T>* repre_first = find(first);
	SetUF<T>* repre_second = find(second);

	if (repre_first == repre_second) {
		return repre_first;
	}

	if (repre_first->rank < repre_second->rank) {
		SetUF<T>* tmp;
		tmp = repre_first;
		repre_first = repre_second;
		repre_second = tmp;
	}

	repre_first->successors.insert(repre_second);
	repre_second->parrent = repre_first;
	repre_first->rank += 1;
	repre_first->size += repre_second->size;

	return repre_first;

}

template <typename T>
SetUF<T>* SetUF<T>::find(SetUF<T>* item)
{
	if (item->parrent == nullptr) return item;

	SetUF<T>* current = item;
	std::vector<SetUF<T>*> to_rewire;
	while (current->parrent != nullptr)
	{
		to_rewire.push_back(current);
		current->parrent->successors.erase(current);
		current = current->parrent;
	}

	for (SetUF<T>* s : to_rewire)
	{
		s->parrent = current;
		current->successors.insert(s);
	}

	return current;
}

template <typename T>
SetUF<T>* findRec(SetUF<T>* item, std::vector<SetUF<T>*>& successors)
{
	if (item->parrent == nullptr) return item;
	successors.insert(item);
	item->parrent = findRec(item->parrent);
}

template <typename T>
SetUF<T>* SetUF<T>::findRec(SetUF<T>* item)
{
	std::vector<SetUF<T>*> to_rewire;
	SetUF<T>* representant = findRec(item, to_rewire);

	for (SetUF<T>* s : to_rewire)
	{
		representant->successors.insert(s);
	}
	return representant;
}

template <typename T>
SetUF<T>* SetUF<T>::findWithoutCompression(SetUF<T>* item)
{
	if (item->parrent == nullptr) return item;

	SetUF<T>* current = item;
	while (current->parrent != nullptr)
	{
		current = current->parrent;
	}
	return current;
}

template <typename T>
void SetUF<T>::destroy()
{
	for (SetUF<T>* s : all_created)
	{
		delete s;
	}
}

template <typename T>
SetUF<T>::SetUF(T item) : item(item)
{
}

template <typename T>
SetUF<T>::~SetUF()
{
}




