#include <ptypes/ptypes.h>
#include <ptypes/pasync.h>
#include <ptypes/pstreams.h>

USING_PTYPES

#define MAX 10

// Inspired on http://pages.cs.wisc.edu/~remzi/OSTEP/threads-monitors.pdf
class BoundedBuffer
{
private:
	int buffer[MAX];
	int fill, use;
	int fullEntries;
	trigger * empty;
	trigger * full;
	mutex m_lock;
	
	
public:
BoundedBuffer() : fullEntries(0), fill(0), use(0) { empty = new trigger(true, false); full = new trigger(true, false); }
~BoundedBuffer() { delete empty; delete full; }
	void produce(int element) {
		if (fullEntries == MAX)
			empty->wait();
		output("Produce " + itostring(element));
		buffer[fill] = element;
		fill = (fill + 1) % MAX;
		fullEntries++;
		full->signal();
	}
	
	int consume() {
		if (fullEntries == 0)
			full->wait();
		int tmp = buffer[use];
		output("Consume " + itostring(tmp));
		use = (use + 1) % MAX;
		fullEntries--;
		empty->signal();
		return tmp;
	}
	
	void output(string s)
	{
		scopelock l(m_lock);
		pout.put(s);
		pout.puteol();
	}
	
};

BoundedBuffer bb;

class threadtest1 : public thread
{
protected:
	virtual void execute() {
		for(int i = 0; i < MAX; i++)
			bb.produce(i);
	}
	virtual void cleanup() { }
public:
	threadtest1() : thread(false) { }
};

class threadtest2 : public thread
{
protected:
	virtual void execute() {
		for(int i = 0; i < MAX; i++)
			bb.consume();
	}
	virtual void cleanup() { }
public:
	threadtest2() : thread(false) { }
};

int main()
{
	threadtest1 t1;
	threadtest2 t2;
	
	t1.start();
	t2.start();
	
	t1.waitfor();
	t2.waitfor();
}