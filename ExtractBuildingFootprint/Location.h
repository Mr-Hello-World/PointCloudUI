#ifndef LOCATION_HEADER
#define LOCATION_HEADER

struct Location
{
	int i, j;
	Location()
	{
		i = j = 0;
	}
	Location(int a, int b)
	{
		i = a; j = b;
	}
};

struct  ComLocation
{
	bool operator()(const Location &a, const Location &b)
	{
		if (a.i != b.i)return a.i < b.i;
		if (a.j != b.j)return a.j < b.j;
		return false;
	}
};
#endif