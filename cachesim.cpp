//Elliot Goldman
//Cache Simulation
//CS 472 B1 - Assignment 2

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct cache  //struct definition representing CPU cache
{
	int valid;
	int dirty;
	int tag;
	int data[16];
	int block;
} slot[16];  //initialize array of 16 cache objects called slots

int main()
{
	ofstream output;
	output.open("Cache Output.txt");
	if (output.fail())
	{
		cerr << "Error - output file could not be opened";
		exit(EXIT_FAILURE);
	}
	int mainMem[2048];  //2K array representing main memory
	for (int init = 0x0; init <= 0xFF; init++)  //initialize array elements with byte values 0 through FF
	{
		mainMem[init] = init;
		mainMem[init + 0x100] = init;
		mainMem[init + 0x200] = init;
		mainMem[init + 0x300] = init;
		mainMem[init + 0x400] = init;
		mainMem[init + 0x500] = init;
		mainMem[init + 0x600] = init;
		mainMem[init + 0x700] = init;
	}
	for (int count = 0; count <= 15; count++)  //initialize all cache members to 0
	{
		slot[count].valid = 0;
		slot[count].dirty = 0;
		slot[count].tag = 0;
		slot[count].data[count] = 0;
		slot[count].block = 0;
	}
	char ops[25] = "RRRRRRRRRRRDWWRDRRDRRRRD";  //hard-coded operation sequence from assignment specs
	int vals[22] = { 0x5, 0x6, 0x7, 0x14C, 0x14D, 0x14E, 0x14F, 0x150, 0x151, 0x3A6, 0x4C3, 0x14C, 0x99, 0x63B, 0x7, 0x582, 0x348, 0x3F, 0x14B, 0x14C, 0x63F, 0x83 };  //hard-coded addresses and write data
	int valCount = 0;
	int address, most, mid, least;
	output << "Elliot Goldman\nCache Sim Output\nCS 472 B1 - Assignment 2\n\n";
	output << hex << uppercase;
	for (int run = 0; run <= 23; run++)  //adjust runtime here to match the operation sequence length above
	{
		output << "(R)ead, (W)rite, or (D)isplay cache?\n" << ops[run] << "\n";
		switch (ops[run])  //switch statement to execute simulated cache operations
		{
		case 'R':  //read byte
			output << "Address to read: " << vals[valCount] << "\n";
			address = vals[valCount];
			most = (address & 0xF00) >> 8;
			mid = (address & 0xF0) >> 4;
			least = address & 0xF;
			if (slot[mid].valid == 1 && slot[mid].tag == most)  //hit
			{
				output << "At that byte the value is: " << slot[mid].data[least] << " (cache hit)\n\n";
			}
			else  //miss
			{
				if (slot[mid].dirty == 1)  //write back to mainMem
				{
					for (int index = 0; index <= 15; index++)
						mainMem[slot[mid].block + index] = slot[mid].data[index];
					slot[mid].dirty = 0;
				}
				for (int index = 0; index <= 15; index++)
					slot[mid].data[index] = mainMem[(address & 0xFF0) + index];
				slot[mid].valid = 1;
				slot[mid].tag = most;
				slot[mid].block = address & 0xFF0;
				output << "At that byte the value is: " << slot[mid].data[least] << " (cache miss)\n\n";
			}
			valCount++;
			break;
		case 'W':  //write byte
			output << "Address to write to: " << vals[valCount] << "\n";
			address = vals[valCount];
			most = (address & 0xF00) >> 8;
			mid = (address & 0xF0) >> 4;
			least = address & 0xF;
			valCount++;
			output << "Data to write to that address: " << vals[valCount] << "\n";
			if (slot[mid].valid == 1 && slot[mid].tag == most)  //hit
			{
				slot[mid].data[least] = vals[valCount];
				slot[mid].dirty = 1;
				output << "Input value " << vals[valCount] << " has been written to address " << address << " (cache hit)\n\n";
			}
			else  //miss
			{
				if (slot[mid].dirty == 1)  //write back to mainMem
				{
					for (int index = 0; index <= 15; index++)
						mainMem[slot[mid].block + index] = slot[mid].data[index];
					slot[mid].dirty = 0;
				}
				for (int index = 0; index <= 15; index++)
					slot[mid].data[index] = mainMem[(address & 0xFF0) + index];
				slot[mid].valid = 1;
				slot[mid].tag = most;
				slot[mid].block = address & 0xFF0;
				slot[mid].data[least] = vals[valCount];
				slot[mid].dirty = 1;
				output << "Input value " << vals[valCount] << " has been written to address " << address << " (cache miss)\n\n";
			}
			valCount++;
			break;
		case 'D':  //display full cache
			output << "\nSlot Valid Dirty Tag      Data\n";
			for (int count = 0; count <= 15; count++)
			{
				output << setw(3) << count << setw(5) << slot[count].valid << setw(6) << slot[count].dirty << setw(5) << slot[count].tag << setw(9);
				for (int print = 0; print <= 15; print++)
				{
					if (slot[count].data[print] <= 0xF && slot[count].data[print - 1] > 0xF)
						output << " " << slot[count].data[print] << " ";
					else if (slot[count].data[print] <= 0xF)
						output << slot[count].data[print] << "  ";
					else
						output << slot[count].data[print] << " ";
				}
				output << "\n";
			}
			output << "\n";
			break;
		}
	}
	output.close();
	return 0;
}

