#ifndef _UTILITIES__MPI_FUNCTIONS_H_
#define _UTILITIES__MPI_FUNCTIONS_H_

#include "mpi.h"

namespace MpiFunctions {


   /// template struct to determine the mpi-type from the template typename.
   namespace {
      template<typename Scalar>
      struct MpiType
      {
         static const MPI_Datatype type;  
      };

      /// Specialisation of mpi-type
      template <> const MPI_Datatype MpiType<char> :: type = MPI_CHAR;
      template <> const MPI_Datatype MpiType<int> :: type = MPI_INT;
      template <> const MPI_Datatype MpiType<float> :: type = MPI_FLOAT;
      template <> const MPI_Datatype MpiType<double> :: type = MPI_DOUBLE;
   }

   /// Get the maximum value from all processes in communicator.
   ///
   template<typename Scalar>
   Scalar Maximum ( MPI_Comm& communicator, const Scalar& operand ) {

      Scalar localOp = operand;
      Scalar result;

      MPI_Allreduce ( &localOp, &result, 1, 
                      MpiType<Scalar>::type, MPI_MAX, communicator );

      return result;
   }


   /// Get the minimum value from all processes.
   ///
   template<typename Scalar>
   Scalar Minimum ( MPI_Comm& communicator, const Scalar& operand ) {

      Scalar localOp = operand;
      Scalar result;

      MPI_Allreduce ( &localOp, &result, 1, 
                      MpiType<Scalar>::type, MPI_MIN, communicator );

      return result;
   }

   /// Get the sum of values from all processes.
   ///
   template<typename Scalar>
   Scalar Sum ( MPI_Comm& communicator, const Scalar& operand ) {

      Scalar localOp = operand;
      Scalar result;

      MPI_Allreduce ( &localOp, &result, 1, 
                      MpiType<Scalar>::type, MPI_SUM, communicator );

      return result;
   }


}

//------------------------------------------------------------//



#endif // _UTILITIES__MPI_FUNCTIONS_H_
