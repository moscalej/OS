#include <stdlib.h>
#include <unordered_map>
#include <iostream>
#include "HelpFunc.h"

using namespace std;

#define PHYSMEMSZ 262144

/*
 * Provide by curse Staff
 */
class PhysMem {
friend class VirtualMemory;
public:
	static PhysMem& Access();
	private:
		PhysMem() {}
		static int* physMem;

	public:
		PhysMem(PhysMem const&) = delete;
		void operator=(PhysMem const&) = delete;
		int* GetFrame(int frameNumber);
};
