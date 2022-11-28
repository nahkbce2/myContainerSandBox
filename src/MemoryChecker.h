#ifndef _MEMORY_CHECKER_H
#define _MEMORY_CHECKER_H

//#include <boost/thread/thread.hpp>

#include <thread>

namespace Utilities 
{
	namespace CheckMemory 
	{
		/// \brief Checks the memory usage and gives a warning if the memory allowed per process has been exceeded.
		///
		/// The memory per process is calculated as being the total ram on the compute node divided by the number
		/// of cores online
		class MemoryChecker {

		public:

			/// \brief Conversion factor from bytes to mega-bytes.
			///
			/// The bytes value should be divided by this value.
			static const unsigned int ToMegaBytes;

			/// \brief The default duration between samples being taken.
			static const unsigned int DefaultTimeBetweenSamples;

			/// \brief The minimum duration between samples being taken.
			static const unsigned int MinimumTimeBetweenSamples;

			/// \brief The maximum duration between samples being taken.
			static const unsigned int MaximumTimeBetweenSamples;


			/// \brief Constructor.
			///
			/// Start the thread that does the checking.
			/// If the time between samples is outside of the range of minimum and maximum then it will be clipped to this range.
			MemoryChecker(const int rank, const unsigned int timeBetweenSamples = DefaultTimeBetweenSamples);

			/// \brief Destructor.
			///
			/// Sets the exit condition for the thread so that it terminates.
			~MemoryChecker();

			/// \brief Get the amount of memory that is being used by the process.
			unsigned long getMemoryUsed() const;

		private:

			/// \brief Indicate whether or not the thread should terminate.
			bool exitLoop() const;

			/// \brief The function that is do be run on the thread.
		    static void checkMemory(const int rank, const MemoryChecker* mc);

			/// \brief The delay time between samples.
			const unsigned int m_timeBetweenSamples;

			/// \brief Indicate whether or not the thread should exit.
			volatile bool m_exit;

			/// \brief The thread on which the memory check function is to be run.
			std::thread m_thread;

		};
	}
}

#endif // _MEMORY_CHECKER_H
