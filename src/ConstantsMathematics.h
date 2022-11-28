//                                                                      
// Copyright (C) 2015-2017 Shell International Exploration & Production.
// All rights reserved.
// 
// Developed under license for Shell by PDS BV.
// 
// Confidential and proprietary source code of Shell.
// Do not distribute without written permission from Shell.
// 

/// @file ConstantsMathematics.h
/// @brief This file stores the mathematical constants used by all IBS applications and libraries

#ifndef UTILITIES_CONSTANTSMATHEMATICS_H
#define UTILITIES_CONSTANTSMATHEMATICS_H

#include <cmath>
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

namespace Utilities
{
   namespace Maths {

      /// @defgroup ConversionTools
      /// List of constants to be used in unit conversions
      /// @{
      // Darcy conversion tools
      constexpr double MilliDarcyToM2 = 0.9869233e-15;         ///< millyDarcy to squared meter conversion factor
      constexpr double M2ToMilliDarcy = (1 / MilliDarcyToM2);  ///< squared meter to millyDarcy conversion factor

      // Pressure conversion tools
      constexpr double PaToMegaPa = 1.0e-6; ///< Pascals to Mega Pascals conversion factor
      constexpr double MegaPaToPa = 1.0e+6; ///< Mega Pascals to Pascals conversion factor

      // Watts conversion tools
      constexpr double MicroWattsToWatts = 0.000001; ///< microWatt to Watts conversion factor
      constexpr double MilliWattsToWatts = 0.001;    ///< millyWatts to Watts conversion factor

      // Joules conversion tools
      constexpr double KiloJouleToJoule = 1000.0; ///< Kilo Joule to Joule conversion factor

      // Temperature conversion tools
      constexpr double CelciusToKelvin = 273.15;  ///< Celcius to Kelvin conversion additive
      constexpr double KelvinToCelcius = -273.15; ///< Kelvin to Celcius conversion additive

      // Time conversion tools
      constexpr double MillionYearToSecond = 3.15576e+13; ///< Million Years to Seconds conversion factor
      constexpr double YearToSecond = 3.15576e7;          ///< Year to Seconds conversion factor(under the assumption that there are 365.25 days per year)
      constexpr double MicroSecondToSecond = 1e-6; ///< microsecond to second conversion factor      
      constexpr double SecondToMicroSecond = 1e6; ///< second to microsecond conversion factor
      constexpr double YearsToMillionYears = 1e-6;  ///< Years to Million Years conversion factor
      constexpr double MilliSecondToSecond = 1e-3;  ///< millisecond to second conversion factor


      // Distance conversion tools
      constexpr double KilometerToMeter = 1.0e3; ///< Kilometer to Meter conversion factor
      constexpr double MeterToKilometer = 1.0e-3; ///< Meter to Kilometer conversion factor

      // Volume conversion tools 
      constexpr double CubicMetresToCubicFeet = 35.3146667;                                              ///< Cubic-feet to cubic-metre conversion factor
      constexpr double CubicMetresToBarrel    = 6.2898107704;                                            ///< Cubic-meter to barrel conversion factor
      constexpr double GorConversionFactor    = CubicMetresToCubicFeet / CubicMetresToBarrel;            ///< Standard cubic-feet per barrel Conversion of gas-oil ratio to field units.
      constexpr double CgrConversionFactor    = CubicMetresToBarrel / (1.0e-3 * CubicMetresToCubicFeet); ///< Barrels per thousand cubic-feet.  (used in conversion of condensate-gas ratio to field units)

      // Weight conversion tools
      constexpr double KilogrammeToUSTon = 1.0 / 907.18474; ///< Kilograme to US ton conversion factor

      // Area conersion tools
      constexpr double KilometreSquaredToAcres = 247.10538147; ///< Squared kilometers to acres conversion factor

      // Statistic conversion tools
      constexpr double FractionToPercentage = 100; ///< Fraction to percentage conversion fasctor
      constexpr double PercentageToFraction = 0.01; ///< Percentage to fraction conversion fasctor

      
      // Data conversion tools
      constexpr double KiloBytesToMegaBytes = 1024; ///< Positive value to convert kilobytes to megabytes
      /// @}

      /// @defgroup Values
      /// List of mathematical values to be used in IBS code
      /// @
      // Scalar values
      /// \details Value to be passed by pointer in PETSC
      constexpr double Zero    =   0.0;
      /// \details Value to be passed by pointer in PETSC
      constexpr double NegOne  =  -1.0;
      /// \details Value to be passed by pointer in PETSC
      constexpr double One     =   1.0;
      /// \details Value to be passed by pointer in PETSC
      constexpr double Hundred = 100.0;

      // Logarithmic values
      /// \brief Equivalent to std::log(10);
      constexpr double Log10 = 2.30258509299404568;

      // Trigonometric values
      /*constexpr double Pi      = M_PI;
      constexpr double Pi2     = Pi*Pi;
      constexpr double Pi2by8  = Pi2 / 8;*/
      /// @}

   }
}
#endif
