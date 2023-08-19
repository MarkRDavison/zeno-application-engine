#include <cstdlib>
#include <zae/Core/Log.hpp>

int main()
{
	zae::Log::Info("zae - Core - Logging - ", zae::Time::Now().GetDateTime(), '\n');

	return EXIT_SUCCESS;
}