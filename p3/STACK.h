#ifndef STACKPAC
#define STACKPAC

template <class T, int n>
class STACK
{
private:
	T a[n];
	int counter;

public:
	void createStack()
	{
		counter = 0;
	}

	bool fullStack()
	{
		if (counter == n){ return true; }
		else		  { return false; }
	}

	bool emptyStack()
	{
		if (counter == 0){ return true; }
		else		  { return false; }
	}

	void pushStack(T x)
	{
		a[counter] = x;
		counter++;
	}

	T popStack()
	{
		counter--;
		return a[counter];
	}
};

#endif
