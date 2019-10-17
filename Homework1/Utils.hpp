#include <iostream>
#include <string.h>

using namespace std;

// Function that chooses a random value between a minimum and a maximum value
int random(int min, int max)
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

void deleteExtraSpaces(unsigned char message[100]) {
    int length = strlen((char*)message);
    while(message[length-1] == ' ') {
        message[length-1] = '\0';
        length --;
    }
}