#include <ptypes/pinet.h>
#include <ptypes/ptypes.h>
#include <ptypes/pstreams.h>

#pragma comment(lib, "ptypes.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "ws2_32.lib")


USING_PTYPES

const int port = 8085;

int main()
{
	ipstream client(ipaddress(127, 0, 0, 1), port);
	
	try
	{
		client.open();
		client.putline("Hello");
		client.flush();
		
		string rsp = client.line();
		pout.putf("Received: %s\n", pconst(rsp));
		client.close();
	} 
	catch(estream* e)
    {
        perr.putf("Error: %s\n", pconst(e->get_message()));
        delete e;
    }
	
	return 0;
}