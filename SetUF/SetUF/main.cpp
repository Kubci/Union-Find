#include "SetUF.h"
#include <iostream>

int main()
{

	SetUF<int>* zero = SetUF<int>::makeSet(0);
	SetUF<int>* one = SetUF<int>::makeSet(1);
	SetUF<int>* two = SetUF<int>::makeSet(2);
	SetUF<int>* three = SetUF<int>::makeSet(3);
	SetUF<int>* four = SetUF<int>::makeSet(4);
	SetUF<int>* five = SetUF<int>::makeSet(5);

	SetUF<int>* zo = SetUF<int>::unionByRank(zero, one);
	SetUF<int>* tt = SetUF<int>::unionByRank(two, three);
	SetUF<int>* ff = SetUF<int>::unionByRank(four, five);

	SetUF<int>* zott = SetUF<int>::unionByRank(zo, tt);

	SetUF<int>* zottff = SetUF<int>::unionByRank(five, three);

	SetUF<int>::destroy();
	return 0;
}