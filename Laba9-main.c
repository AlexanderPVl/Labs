#include "Struct.h"

void main()
{
	HEAD *List1 = NULL, *List2 = NULL, *List3 = NULL;
	List1 = MakeList(4);
	List2 = MakeList(3);
	List3 = FormNew(List1, List2);

	PrintList(List1);
	PrintList(List2);
	PrintList(List3);

	DeleteList(List1);
	DeleteList(List2);
	DeleteList(List3);
}
