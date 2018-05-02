//#include "Interpolate.hpp"

#include "PlaystationDesktop.hpp"

int main()
{
	PlaystationDesktop psdk;

	psdk.start();

	while (psdk.running())
	{
		psdk.HandleEvents();
		psdk.Update();
		psdk.Draw();
	}

	psdk.shutdown();

	return 0;
}
