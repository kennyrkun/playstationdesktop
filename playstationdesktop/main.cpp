//#include "Interpolate.hpp"

#include "PlaystationDesktop.hpp"

int main(int argc, char* argv[])
{
	ApplicationSettings appSettings;
	// TODO: command line arguments

	PlaystationDesktop psdk(appSettings);

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
