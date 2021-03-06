#include <ptypes/ptypes.h>
#include <ptypes/pasync.h>
#include <ptypes/pstreams.h>
#include <vector>
#include <windows.h>

USING_PTYPES

#define MAX 100

std::vector<string> output_s;
std::vector<string> output_p;

// Inspired on http://pages.cs.wisc.edu/~remzi/OSTEP/threads-monitors.pdf
class BoundedBuffer
{
private:
	int buffer[MAX];
	int fill, use;
	unsigned int fullEntries;
	trigger * empty;
	trigger * full;
	mutex m_lock;
	
	
public:
BoundedBuffer() : fullEntries(0), fill(0), use(0) { fillbb(); empty = new trigger(true, false); full = new trigger(true, false); }
~BoundedBuffer() { delete empty; delete full; }
	void fillbb()
	{
		for(int i = 0; i < MAX; i++)
			buffer[i] = -2;
	}
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
		while (fullEntries == 0 || buffer[use] == -2)
			full->wait();

		int tmp = buffer[use];
		buffer[use] = -1;
		output("Consume " + itostring(tmp));
		use = (use + 1) % MAX;
		fullEntries--;
		empty->signal();
		return tmp;
	}
	
	void output(string s)
	{
		// Performing console I/O from a thread causes strange behavior
		// Even with a mutex lock
		scopelock l(m_lock);
		output_s.push_back(s);
	}
	
};

BoundedBuffer bb;

class threadtest1 : public thread
{
protected:
	virtual void execute() {
		for(int i = 0; i < MAX + 30; i++)
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
		for(int i = 0; i < MAX + 30; i++)
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
	
	t2.start();
	t1.start();
	
	t1.waitfor();
	t2.waitfor();
	for(size_t i = 0; i < output_s.size(); i++)
	{
		pout.put(output_s[i]);
		pout.put("\n");
	}

}