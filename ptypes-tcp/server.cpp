#include <ptypes/ptypes.h>
#include <ptypes/pstreams.h>
#include <ptypes/ptime.h>
#include <ptypes/pinet.h>

#pragma comment(lib, "ptypes.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "ws2_32.lib")

USING_PTYPES

const int port = 8085;
const int maxtoken = 4096;

void servermain(ipstmserver& svr)
{
    ipstream client;
	
	pout.putf("Ready to answer queries on port %d\n", port);

    while(true)
    {
		svr.serve(client);
		if (client.get_active())
        {
            try
            {
                string req = lowercase(client.line(maxtoken));
                if (req == "hello")
                {
                    string host = phostbyaddr(client.get_ip());
                    if (isempty(host))
                        host = iptostring(client.get_ip());
					int timestamp = (now() - _unixepoch) / 1000;
					client.putline("Hello, the current timestamp is - " + itostring(timestamp));
                    client.flush();

                    pout.putf("%t  greeting received from %s (%a)\n",
                        now(), pconst(host), long(client.get_ip()));
                }

                client.close();
            }
            catch(estream* e)
            {
                perr.putf("Error: %s\n", pconst(e->get_message()));
                delete e;
            }
        }
	}
}

int main()
{
    ipstmserver svr;

    try
    {
        svr.bindall(port);

        servermain(svr);
    }
    catch(estream* e)
    {
        perr.putf("FATAL: %s\n", pconst(e->get_message()));
        delete e;
    }

    return 0;
}