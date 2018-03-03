#include <string>
#include <list>
#include <vector>
#include <iostream>
#define HASH_RANGE 3;

using namespace std;

int power2(int size){
	int a = 1;
	for(int i = 0; i < size; i++){
		a *= 2;
	}
	return a;
}
template <typename Key, typename Val>
class THash
{
public:
	vector <list <pair <Key, Val> > > Table;
	list <pair <Key, Val> > Temp;
	int hash_func(const int& a){
		return a;
	}
	int hash_func(const string& a){
		return a.size();
	}

public:
	THash(){
		//for (int i = 0; i < 3; i++){
			Table.push_back(Temp);
		//}
	};

	THash(Key a, Val b){
		Table.push_back(Temp);
		int i = hash_func(a), j = 0;
		while(i > 0){
			i /= 2;
			j++;
		}
		Table = resize(j);
		pair <Key, Val> pa = make_pair(a, b);
		Table[hash_func(a)].push_back(pa);
	};
	~THash(){
		Table.clear();
	};
	//resize
	vector <list <pair <Key, Val> > > resize(const int& size){
		int a = power2(size);
		vector <list <pair <Key, Val> > > TempTable(Table);
		TempTable.insert(TempTable.end(), a - Table.size(), Temp);
		return TempTable;
	}
	//push element
	void push(const Key& a, const Val& b){
		int i = hash_func(a), j = 0;
		while(i > 0){
			i /= 2;
			j++;
		}
		Table = resize(j);
		pair <Key, Val> pa = make_pair(a, b);
		Table[hash_func(a)].push_back(pa);
		//cout << "push " << hash_func(a) << endl;
	}
	//size of table
	int size(){
		int j = 0;
		for(int i = 0;i < Table.size(); i++){
			j += Table[i].size();
		}
		return j;
	}
	//search for element
	Val find(const Key& a){
		THash b = *this;
		return b[a];
	}
	//operator[]
	Val operator[](const Key& a){
		for(unsigned int i = 0; i < Table[hash_func(a)].size(); i++){
			pair<Key, Val> tempex = *next(Table[hash_func(a)].begin(), i);
			cout << "temporary value " << tempex.second << endl;
			if (a == tempex.first){
				return tempex.second;
			}

		}
		return 0;
	}
};
int main(){
	THash<int, int> a;
	a.push(0,3);
	a.push(10,5);
	//cout << a.find(1) << endl;
	cout << a.find(0) << endl;
	cout << a[10] << endl; 	
	cout << a.size() << endl; 
	return 0;
}