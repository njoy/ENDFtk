#ifndef NJOY_ENDFTK_SECTION_EXPLICITCOVARIANCE
#define NJOY_ENDFTK_SECTION_EXPLICITCOVARIANCE

// system includes
#include <variant>
#include <vector>

// other includes
#include "ENDFtk/section/CovariancePairs.hpp"
#include "ENDFtk/section/SquareMatrix.hpp"
#include "ENDFtk/section/RectangularMatrix.hpp"
#include "ENDFtk/readSequence.hpp"

namespace njoy {
namespace ENDFtk {

namespace section{

  using ExplicitCovariance = std::variant< CovariancePairs,
                                           SquareMatrix,
                                           RectangularMatrix >;

} // section namespace

  /**
   *  @brief Function to read a sequence of ENDF components
   *
   *  @tparam Component        an ENDF component
   *  @tparam Iterator         an input iterator
   *
   *  This function requires the ENDF component to have a read style
   *  constructor.
   */
  template< typename Iterator >
  std::vector< section::ExplicitCovariance >
  readSequence( Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT,
                int size ) {

    std::vector< section::ExplicitCovariance > sequence;
    sequence.reserve( size );

    while ( size-- ) {

      ListRecord list( begin, end, lineNumber, MAT, MF, MT );

      switch ( list.L2() ) {

        // CovariancePairs
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 8:
        case 9:
          sequence.emplace_back( section::CovariancePairs( std::move( list ) ) );
          break;

        // SquareMatrix
        case 5:
          sequence.emplace_back( section::SquareMatrix( std::move( list ) ) );
          break;

        // RectangularMatrix
        case 6:
          sequence.emplace_back( section::RectangularMatrix( std::move( list ) ) );
          break;

        // Error
        default:
          Log::error( "Encountered illegal LB value" );
          Log::info( "LB can only be 0,1,2,3,4,5,6,8,9" );
          Log::info( "LB value: {}", list.L2() );
          Log::info( "Line number: {}", lineNumber - 1 );
          throw std::exception();
      }
    }

    return sequence;
  }

} // ENDFtk namespace
} // njoy namespace

#endif
