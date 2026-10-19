#ifndef NJOY_ENDFTK_INTERPOLATIONSEQUENCERECORD
#define NJOY_ENDFTK_INTERPOLATIONSEQUENCERECORD

// system includes
#include <variant>
#include <vector>

// other includes
#include "tools/std20/views.hpp"
#include "tools/Log.hpp"
#include "ENDFtk/InterpolationRecord.hpp"
#include "ENDFtk/readSequence.hpp"

namespace njoy {
namespace ENDFtk {

  /**
   *  @brief Function to print an ENDF component
   *
   *  This function is used in the InterpolationSequenceRecord print() function.
   *
   *  @tparam OutputIterator   an output iterator
   *  @tparam Component        an ENDF component
   *
   *  @param[in] component     the ENDF component to be printed
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template < typename OutputIterator, typename Component >
  void print( const Component& component,
              OutputIterator& it, int MAT, int MF, int MT ) {

    component.print( it, MAT, MF, MT );
  }

  /**
   *  @brief Function to retrieve the number of lines NC of an ENDF component
   *
   *  This function is used in the InterpolationSequenceRecord class.
   */
  template < typename Component >
  long NC( const Component& component ) {

    return component.NC();
  }

  /**
   *  @brief Function to print a variant of ENDF components
   *
   *  This function is used in the InterpolationSequenceRecord print() function.
   *
   *  @tparam OutputIterator   an output iterator
   *  @tparam Components       a list of ENDF components
   *
   *  @param[in] variant       the variant of ENDF components to be printed
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template < typename OutputIterator, typename... Components >
  void print( const std::variant< Components... >& variant,
              OutputIterator& it, int MAT, int MF, int MT ) {

    std::visit( [&] ( const auto& record ) { record.print( it, MAT, MF, MT ); },
                variant );
  }

  /**
  *  @brief Function to retrieve the number of lines NC of a variant of ENDF
  *         components
  *
  *  This function is used in the InterpolationSequenceRecord class.
   */
  template < typename... Components >
  long NC( const std::variant< Components... >& variant ) {

    return std::visit( [&] ( const auto& record ) { return record.NC(); },
                       variant );
  }

  /**
   *  @brief Auxiliary function to validate a sequence of ENDF components
   *
   *  This function is used in the InterpolationSequenceRecord constructor.
   */
  template < typename Component >
  void validateSequence( const std::vector< Component >& ) { return; }

  /**
   *  @class
   *  @brief A helper class to store a TAB2 and associated sequence of ENDF
   *         components or variants of ENDF components
   *
   *  The CoherentElastic class is used to represent the coherent elastic
   *  scattering law of MF7/MT2.
   *
   *  The S(E) functions are given as tabulated S(E) for a set of temperature
   *  values.
   *
   *  See ENDF102, section 7.2 for more information.
   */
  template < typename Component >
  class InterpolationSequenceRecord {

    /* fields */

    InterpolationRecord interpolation_;
    std::vector< Component > sequence_;

    /* auxiliary functions */

    static void
    verifyNZ( unsigned int index, unsigned int NZ ) {

      if ( NZ == 0 ) {

        Log::error( "NZ should be larger than 0" );
        throw std::exception();
      }

      const bool inconsistentNZ = ( index != NZ );

      if ( inconsistentNZ ) {

        Log::error( "Inconsistent NZ value between interpolation table and "
                    "data points" );
        Log::info( "Last index interpolation table: {}", index );
        Log::info( "Number of points in data: {}", NZ );
        throw std::exception();
      }
    }

  public:

    /* constructor */

    //! @todo pybind11 variant needs default constructor workaround
    #ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    InterpolationSequenceRecord() = default;
    #endif

    /**
     *  @brief Constructor
     *
     *  @param[in] interpolation   the interpolation record associated to the data
     *  @param[in] sequence        the data
     */
    InterpolationSequenceRecord ( InterpolationRecord&& interpolation,
                                  std::vector< Component >&& sequence ) :
      interpolation_( interpolation ),
      sequence_( sequence ) {

      verifyNZ( this->tab2().NZ(), sequence.size() );
      validateSequence( sequence );
    }

    /* get methods */

    /**
     *  @brief Return TAB2 record in the interpolation sequence record
     */
    const InterpolationRecord& tab2() const { return this->interpolation_; }

    /**
     *  @brief Return the sequence of records in the interpolation sequence record
     */
    auto records() const {

      using namespace njoy::tools;
      return std20::views::all( this->sequence_ );
    }

    /**
     *  @brief Return the number of lines in this ENDF component
     */
    auto NC() const {

      auto NC = this->interpolation_.NC();
      for ( const auto& entry : this->sequence_ ) { NC += ENDFtk::NC( entry ); }
      return NC;
    };

    /**
     *  @brief Print the interpolation sequence record
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     *  @param[in] MT            the MT number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF, int MT ) const {

      this->interpolation_.print( it, MAT, MF, MT );
      for ( const auto& entry : this->sequence_ ) {

        ENDFtk::print( entry, it, MAT, MF, MT );
      }
    }
  };

  /**
   *  @brief Function to read an interpolation sequence using an ENDF component
   *
   *  @tparam Component        an ENDF component
   *  @tparam Iterator         an input iterator
   *
   *  This function requires the ENDF component to have a read style constructor.
   */
  template< typename Component, typename Iterator >
  InterpolationSequenceRecord< Component >
  readInterpolationSequenceRecord( Iterator& begin,
                                   const Iterator& end,
                                   long& lineNumber,
                                   int MAT,
                                   int MF,
                                   int MT ) {

    InterpolationRecord interpolation( begin, end, lineNumber, MAT, MF, MT );
    return InterpolationSequenceRecord(
               std::move( interpolation ),
               readSequence< Component >( begin, end, lineNumber, MAT, MF, MT,
                                          interpolation.NZ() ) );
  }

} // ENDFtk namespace
} // njoy namespace

#endif
