#include <iostream>	//std::cout
#include <string>	//std::string
#include <sstream>	//std::stringstream

using namespace std;

typedef struct Call Call;
struct Call
{
	long int start;
	long int duration;
	long int end;
}; // Call struct

typedef struct Interval Interval;
struct Interval
{
	long int start;
	long int duration;
	long int end;
}; // Interval struct

int main()
{
	string line;
	while(getline(cin, line))
	{
		// Get the count of calls and interval
		stringstream splitter(line);
		unsigned int calls;
		unsigned int intervals;
		splitter >> calls >> intervals;

		// Continue on N = M = 0
		if(calls == 0 && calls == intervals) continue;

		// Create structures containers
		Call callsStc[calls];
		Interval intervalsStc[intervals];

		// Load calls data
		for(unsigned int i = 0; i < calls; ++i)
		{
			getline(cin, line);
			stringstream callInfoSplitter(line);

			// Let's ignore source and destination (save space)
			int devnull;
			callInfoSplitter >> devnull >> devnull;
			Call currentCall;
			callInfoSplitter >> currentCall.start >> currentCall.duration;
			currentCall.end = currentCall.start + currentCall.duration;
			callsStc[i] = currentCall;
		}

		// Load intervals data
		for(unsigned int i = 0; i < intervals; ++i)
		{
			getline(cin, line);
			stringstream intervalsInfoSplitter(line);

			// Let's save start and duration
			Interval currentInterval;
			intervalsInfoSplitter >> currentInterval.start >> currentInterval.duration;
			currentInterval.end = currentInterval.start + currentInterval.duration;
			intervalsStc[i] = currentInterval;
		}

		// Process data
		for(unsigned int i = 0; i < intervals; ++i)
		{
			unsigned int operators = 0;
			for(unsigned j = 0; j < calls; ++j)
			{
				// Test if call duration is greater than 1 second and is it fits (at least one second of it) in the interval
				if(callsStc[j].duration >= 1 &&
				   callsStc[j].end > intervalsStc[i].start &&
				   callsStc[j].start < intervalsStc[i].end)
				{
					++operators;
				}
			}
			cout << operators << endl;
		}
	}
	return 0;
} // main()
