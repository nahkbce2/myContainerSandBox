#include "MemoryChecker.h"

//#include <boost/bind.hpp>
#include <functional>   // std::bind
#include <iostream>
#include <sstream>
#include <chrono>

#ifndef _MSC_VER
#include <sys/sysinfo.h>
#endif

#include "NumericFunctions.h"
#include "System.h"

const unsigned int Utilities::CheckMemory::MemoryChecker::ToMegaBytes = 1048576;
const unsigned int Utilities::CheckMemory::MemoryChecker::DefaultTimeBetweenSamples = 30;
const unsigned int Utilities::CheckMemory::MemoryChecker::MinimumTimeBetweenSamples = 1;
const unsigned int Utilities::CheckMemory::MemoryChecker::MaximumTimeBetweenSamples = 60;

namespace Utilities
{
	namespace CheckMemory
	{
		MemoryChecker::MemoryChecker(const int rank,const unsigned int timeBetweenSamples) :
			m_timeBetweenSamples(NumericFunctions::Maximum(MinimumTimeBetweenSamples, NumericFunctions::Minimum(timeBetweenSamples, MaximumTimeBetweenSamples))),
			m_exit(false),
			m_thread(std::bind(&checkMemory, rank, this))
		{
			m_thread.detach();
		}

		MemoryChecker::~MemoryChecker() {
			m_exit = true;
		}

		bool MemoryChecker::exitLoop() const {
			return m_exit;
		}

		unsigned long MemoryChecker::getMemoryUsed() const {

			StatM statm;

			getStatM(statm);

			return (statm.size * getPageSize()) / ToMegaBytes;

		}

		void MemoryChecker::checkMemory(const int rank, const MemoryChecker* mc) {

#ifndef _MSC_VER
			long nprocs = getNumberOfCoresOnline();

			if (nprocs == 0) {
				// If the number of cores is 0 (i.e. unknown) then we cannot calculate the memory per process.
				// This is probably only a result of the windows build.
				return;
			}

			unsigned long memoryPerProcess = 0;

			struct sysinfo inf;

			sysinfo(&inf);
			memoryPerProcess = inf.totalram / nprocs;
			memoryPerProcess /= ToMegaBytes;

			if (memoryPerProcess == 0) {
				// If the memory per process is zero then terminate the thread.
				return;
			}

			while (not mc->exitLoop()) {

				if (mc->getMemoryUsed() > memoryPerProcess) {
					std::cerr << " Basin_Warning: Current memory used in rank "<< rank <<" is " << mc->getMemoryUsed() << " MB, which exceeds the memory per process of " << memoryPerProcess << " MB" << std::endl;
				}

				//boost::this_thread::sleep(boost::posix_time::seconds(mc->m_timeBetweenSamples));
				std::this_thread::sleep_for(std::chrono::seconds(mc->m_timeBetweenSamples));
			}

#endif
			//using namespace std::chrono_literals;
			//std::this_thread::sleep_for(1ms);
		}
	}
}
