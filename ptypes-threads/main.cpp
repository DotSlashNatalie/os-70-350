#include <ptypes/pasync.h>
#include <stdio.h>

#pragma comment(lib, "../ext/libs/ptypes.lib")
#pragma comment(lib, "user32.lib")

USING_PTYPES

class threadtest : public thread
{
protected:
	virtual void execute();
	virtual void cleanup() { }
public:
	threadtest() : thread(false) { }
};

void threadtest::execute()
{
	int i;
	for(i = 0; i < 10; i++)
		printf("%i\n", i);
}

int main()
{
	threadtest t1, t2;
	
	t1.start();
	t2.start();
	
	t1.waitfor();
	t2.waitfor();
}