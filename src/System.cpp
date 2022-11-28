//
// Copyright (C) 2015-2016 Shell International Exploration & Production.
// All rights reserved.
// 
// Developed under license for Shell by PDS BV.
// 
// Confidential and proprietary source code of Shell.
// Do not distribute without written permission from Shell.
// 
#include "System.h"
#include "ConstantsMathematics.h"

#ifndef _MSC_VER  //TODO_SK: this does not compile on Windows
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#endif

//You can try the following cross - platform code to get current date / time:
#include <stdio.h>
#include <time.h>

using Utilities::Maths::KiloBytesToMegaBytes;

namespace Utilities
{
    namespace CheckMemory
    {

#ifndef _MSC_VER  //TODO_SK: this does not compile on Windows

        double getResidentSetSize()
        {
            static struct rusage temp;

            getrusage(RUSAGE_SELF, &temp);

            return ((double)temp.ru_maxrss) / KiloBytesToMegaBytes;

        }

        int getCurrentLimit()
        {
#if defined(PARCH_linux) || defined(PARCH_solaris)
            static struct rlimit rlp;
            getrlimit(RLIMIT_DATA, &rlp);
#else
            static struct rlimit64 rlp;
            getrlimit64(RLIMIT_DATA, &rlp);
#endif


            return (int)rlp.rlim_cur;

        }

        long getPageSize()
        {
            return sysconf(_SC_PAGESIZE);
        }

        int getProcPID()
        {
            return (int)getpid();
        }

        long getNumberOfCoresOnline() {
            return sysconf(_SC_NPROCESSORS_ONLN);
        }

        void getStatM(StatM& statm) {

            const char* statm_path = "/proc/self/statm";

            FILE *f = fopen(statm_path, "r");

            if (!f) perror(statm_path);

            fscanf(f, "%ld %ld %ld %ld %ld %ld %ld", &statm.size, &statm.resident, &statm.share, &statm.text, &statm.lib, &statm.data, &statm.dt);
            fclose(f);
        }


#else

        double getResidentSetSize() { return 0; }
        int getCurrentLimit() { return 0; }
        long getPageSize() { return 0; }
        int getProcPID() { return 0; }

        long getNumberOfCoresOnline()
        {
            return 0;
        }

        void getStatM(StatM& statm) {
            statm.size = 0;
            statm.resident = 0;
            statm.share = 0;
            statm.text = 0;
            statm.lib = 0;
            statm.data = 0;
            statm.dt = 0;
        }
#endif
    }

    namespace times {
		const std::string timeStamp() {
			time_t     now = time(0);
			struct tm  tstruct;
			char       buf[80];
			tstruct = *localtime(&now);
			// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
			// for more information about date/time format
			strftime(buf, sizeof(buf), "%Y%m%d-%H%M%S", &tstruct);

			return buf;
		}
    }
}


