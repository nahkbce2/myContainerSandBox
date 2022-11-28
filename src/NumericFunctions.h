#ifndef _NUMERIC_FUNCTIONS_H_
#define _NUMERIC_FUNCTIONS_H_

#include <cmath>
#include <limits>

namespace NumericFunctions {

   /// \brief Maximum value of any two objects.
   ///
   /// Returns \f$ r=\max ( x, y )\f$
   /// The type must have a '>' defined.
   template<class Number>
   Number Maximum ( const Number& x,
                    const Number& y );

   /// \brief Maximum value of any three objects.
   ///
   /// Returns \f$ r=\max ( x, y, z )\f$
   /// The type must have a '>' defined.
   template<class Number>
   Number Maximum3 ( const Number& x,
                     const Number& y,
                     const Number& z );

   /// \brief Minimum value of any two objects.
   ///
   /// Returns \f$ r=\min ( x, y )\f$
   /// The type must have a '<' defined.
   template<class Number>
   Number Minimum ( const Number& x,
                    const Number& y );

   /// \brief Minimum value of any three objects.
   ///
   /// Returns \f$ r=\min ( x, y, z )\f$
   /// The type must have a '<' defined.
   template<class Number>
   Number Minimum3 ( const Number& x,
                     const Number& y,
                     const Number& z );

   /// \brief Return whether or not a value is in the closed range.
   ///
   /// Returns \f$ r= \mbox{value} \in \left[ \mbox{lower}, \mbox{upper}\right]\f$
   /// The function '<=' must be defined.
   template<class Number>
   bool inRange ( const Number& value,
                  const Number& lowerBound,
                  const Number& upperBound );

   template<class Number>
   bool isEqual ( const Number& x, const Number& y, const Number& tolerance);

   /// \brief Clips a value so that it lies within the desired range.
   ///
   /// Returns \f$ r=\max( \mbox{lower}, \min ( \mbox{upper}, \mbox{value} ))\f$
   template<typename Scalar>
   Scalar clipValueToRange ( const Scalar value, const Scalar lowerBound, const Scalar upperBound );

   /// \brief Copies the sign of the value.
   ///
   /// Returns 1 if value >= 0, -1 if value < 0.
   template<typename Scalar>
   Scalar copySign ( const Scalar value );

   template<typename Scalar>
   struct ScalarValues;


   #if defined(_WIN32) || defined (_WIN64)
   #else


   template<>
   struct ScalarValues<double> {
      static constexpr double Zero = 0.0;
      static constexpr double One  = 1.0;
   };

   template<>
   struct ScalarValues<float> {
      static constexpr float Zero = 0.0;
      static constexpr float One  = 1.0;
   };


   template<>
   struct ScalarValues<int> {
      static const int Zero = 0;
      static const int One  = 1;
   };
  #endif
}

//------------------------------------------------------------//
// Implementation of template functions

template<class Number>
Number NumericFunctions::Maximum ( const Number& x,
                                   const Number& y ) {
   if ( x > y ) {
      return x;
   } else {
      return y;
   }

}

//------------------------------------------------------------//

template<class Number>
Number NumericFunctions::Maximum3 ( const Number& x,
                                    const Number& y,
                                    const Number& z ) {
   return Maximum<Number>( x, Maximum<Number> ( y, z ));
}

//------------------------------------------------------------//

template<class Number>
Number NumericFunctions::Minimum ( const Number& x,
                                   const Number& y ) {
   if ( x < y ) {
      return x;
   } else {
      return y;
   }

}

//------------------------------------------------------------//

template<class Number>
Number NumericFunctions::Minimum3 ( const Number& x,
                                    const Number& y,
                                    const Number& z ) {
   return Minimum<Number>( x, Minimum<Number> ( y, z ));
}

//------------------------------------------------------------//

template<class Number>
bool NumericFunctions::inRange ( const Number& value,
                                 const Number& lowerBound,
                                 const Number& upperBound ) {

   return lowerBound <= value && value <= upperBound;
}

//------------------------------------------------------------//

template<typename Number>
bool NumericFunctions::isEqual ( const Number& x, const Number& y, const Number& tolerance ) {

   if ( x == y ) {
      return true;
   } else {

    Number absX = std::abs ( x );
    Number absY = std::abs ( y );

    if ( absX > absY ) {
       return std::abs ( x - y ) <= tolerance * absX;
    } else {
       return std::abs ( x - y ) <= tolerance * absY;
    }

   }

}

//------------------------------------------------------------//

template<typename Scalar>
Scalar NumericFunctions::clipValueToRange ( const Scalar value, const Scalar lowerBound, const Scalar upperBound ) {

   if ( value > upperBound ) {
      return upperBound;
   } else if ( value < lowerBound ) {
      return lowerBound;
   } else {
      return value;
   }

}

//------------------------------------------------------------//

   #if defined(_WIN32) || defined (_WIN64)
   #else

template<typename Scalar>
Scalar NumericFunctions::copySign ( const Scalar value ) {

   if ( value >= ScalarValues<Scalar>::Zero ) {
      return ScalarValues<Scalar>::One;
   } else {
      return -ScalarValues<Scalar>::One;
   }


}
   #endif


#endif // _NUMERIC_FUNCTIONS_H_
