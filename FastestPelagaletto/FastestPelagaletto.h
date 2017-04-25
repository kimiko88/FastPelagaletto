using namespace std;

namespace Pelagaletto
{
	extern "C" { __declspec(dllexport) void PlayFromTo(__int8 from[40], __int8 to[40], __int8 bestCatch[40], __int8 bestPlayedCards[40], int &winsPlayer1, int &winsPlayer2, int &maxCatch, int &maxCardPlayed); }
}