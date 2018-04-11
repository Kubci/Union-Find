#include "SetUF.h"
#include <iostream>

int main()
{
	SetUF<int>* set_uf;

	SetUF<int>* zero = set_uf->makeSet(0);
	SetUF<int>* one = set_uf->makeSet(1);
	SetUF<int>* two = set_uf->makeSet(2);
	SetUF<int>* three = set_uf->makeSet(3);
	SetUF<int>* four = set_uf->makeSet(4);
	SetUF<int>* five = set_uf->makeSet(5);

	SetUF<int>* zo = set_uf->unionByRank(zero, one);
	SetUF<int>* tt = set_uf->unionByRank(two, three);
	SetUF<int>* ff = set_uf->unionByRank(four, five);

	SetUF<int>* zott = set_uf->unionByRank(zo, tt);

	SetUF<int>* zottff = set_uf->unionByRank(five, three);

	zottff->deleteSet();
	SetUF<int>::destroy(); 
	
	return 0;
}