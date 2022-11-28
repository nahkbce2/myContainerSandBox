#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include <string>

namespace Utilities 
{
	namespace CheckMemory 
	{

		double getResidentSetSize();

		int getCurrentLimit();

		int getProcPID();

		/// \brief Returns the number of cores that are on-line.
		long getNumberOfCoresOnline();

		/// \brief Returns the number of bytes in a page.
		long getPageSize();

		/// \brief Holds the values from the /proc/self/statm file.
		struct StatM {
			unsigned long size;
			unsigned long resident;
			unsigned long share;
			unsigned long text;
			unsigned long lib;
			unsigned long data;
			unsigned long dt;
		};

		/// \brief Get the values from the /proc/self/statm file.
		void getStatM(StatM& statm);
	}

	namespace times {
		const std::string timeStamp();
	}
}
#endif
