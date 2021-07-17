#ifndef NJOY_ENDFTK_PYTHON_VARIANTS
#define NJOY_ENDFTK_PYTHON_VARIANTS

// system includes

// other includes
#include "ENDFtk/tree/Tape.hpp"

/**
 *  @brief Type aliases for parsed section and files
 */

using MF1MT451 = njoy::ENDFtk::section::Type< 1, 451 >;
using MF1MT452 = njoy::ENDFtk::section::Type< 1, 452 >;
using MF1MT455 = njoy::ENDFtk::section::Type< 1, 455 >;
using MF1MT456 = njoy::ENDFtk::section::Type< 1, 456 >;
using MF1MT458 = njoy::ENDFtk::section::Type< 1, 458 >;
using MF1MT460 = njoy::ENDFtk::section::Type< 1, 460 >;
using MF2MT151 = njoy::ENDFtk::section::Type< 2, 151 >;
using MF2MT152 = njoy::ENDFtk::section::Type< 2, 152 >;
using MF3MTxxx = njoy::ENDFtk::section::Type< 3 >;
using MF4MTxxx = njoy::ENDFtk::section::Type< 4 >;
using MF5MTxxx = njoy::ENDFtk::section::Type< 5 >;
using MF6MTxxx = njoy::ENDFtk::section::Type< 6 >;
using MF7MT2 = njoy::ENDFtk::section::Type< 7, 2 >;
using MF7MT4 = njoy::ENDFtk::section::Type< 7, 4 >;
using MF8MT454 = njoy::ENDFtk::section::Type< 8, 454 >;
using MF8MT457 = njoy::ENDFtk::section::Type< 8, 457 >;
using MF8MT459 = njoy::ENDFtk::section::Type< 8, 459 >;
using MF9MTxxx = njoy::ENDFtk::section::Type< 9 >;
using MF10MTxxx = njoy::ENDFtk::section::Type< 10 >;
using MF12MTxxx = njoy::ENDFtk::section::Type< 12 >;
using MF13MTxxx = njoy::ENDFtk::section::Type< 13 >;
using MF14MTxxx = njoy::ENDFtk::section::Type< 14 >;
using MF15MTxxx = njoy::ENDFtk::section::Type< 15 >;
using MF23MTxxx = njoy::ENDFtk::section::Type< 23 >;
using MF26MTxxx = njoy::ENDFtk::section::Type< 26 >;
using MF27MTxxx = njoy::ENDFtk::section::Type< 27 >;
using MF28MTxxx = njoy::ENDFtk::section::Type< 28 >;
using SectionVariant = std::variant< MF1MT451, MF1MT452, MF1MT455,
                                     MF1MT456, MF1MT458, MF1MT460,
                                     MF2MT151, MF2MT152,
                                     MF3MTxxx, MF4MTxxx, MF5MTxxx,
                                     MF6MTxxx, MF7MT2, MF7MT4,
                                     MF8MT454, MF8MT457, MF8MT459,
                                     MF9MTxxx, MF10MTxxx,
                                     MF12MTxxx, MF13MTxxx, MF14MTxxx, MF15MTxxx,
                                     MF23MTxxx, MF26MTxxx, MF27MTxxx, MF28MTxxx >;

using MF1 = njoy::ENDFtk::file::Type< 1 >;
using MF2 = njoy::ENDFtk::file::Type< 2 >;
using MF3 = njoy::ENDFtk::file::Type< 3 >;
using MF4 = njoy::ENDFtk::file::Type< 4 >;
using MF5 = njoy::ENDFtk::file::Type< 5 >;
using MF6 = njoy::ENDFtk::file::Type< 6 >;
using MF7 = njoy::ENDFtk::file::Type< 7 >;
using MF8 = njoy::ENDFtk::file::Type< 8 >;
using MF9 = njoy::ENDFtk::file::Type< 9 >;
using MF10 = njoy::ENDFtk::file::Type< 10 >;
using MF12 = njoy::ENDFtk::file::Type< 12 >;
using MF13 = njoy::ENDFtk::file::Type< 13 >;
using MF14 = njoy::ENDFtk::file::Type< 14 >;
using MF15 = njoy::ENDFtk::file::Type< 15 >;
using MF23 = njoy::ENDFtk::file::Type< 23 >;
using MF26 = njoy::ENDFtk::file::Type< 26 >;
using MF27 = njoy::ENDFtk::file::Type< 27 >;
using MF28 = njoy::ENDFtk::file::Type< 28 >;
using FileVariant = std::variant< MF1, MF2, MF3, MF4, MF5, MF6,
                                  MF7, MF8, MF9, MF10, MF12, MF13,
                                  MF14, MF15, MF23, MF26, MF27, MF28 >;

#endif
