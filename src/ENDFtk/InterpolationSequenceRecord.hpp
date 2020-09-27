#ifndef NJOY_ENDFTK_INTERPOLATIONSEQUENCERECORD
#define NJOY_ENDFTK_INTERPOLATIONSEQUENCERECORD

// system includes
#include <variant>
#include <vector>

// other includes
#include "range/v3/view/all.hpp"
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
   *
   *  @param[in] MT            the MT number
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
    #include "ENDFtk/InterpolationSequenceRecord/src/verifyNZ.hpp"

  public:

    /* type aliases */
    using ComponentRange =
    decltype( ranges::view::all( std::declval< const std::vector< Component > >() ) );

    /* constructor */
    #include "ENDFtk/InterpolationSequenceRecord/src/ctor.hpp"

    /* get methods */

    /**
     *  @brief Return TAB2 record in the interpolation sequence record
     */
    const InterpolationRecord& tab2() const { return this->interpolation_; }

    /**
     *  @brief Return the sequence of records in the interpolation sequence record
     */
    ComponentRange records() const {

      return ranges::view::all( this->sequence_ );
    }

    #include "ENDFtk/InterpolationSequenceRecord/src/NC.hpp"
    #include "ENDFtk/InterpolationSequenceRecord/src/print.hpp"
  };

  #include "ENDFtk/InterpolationSequenceRecord/src/readInterpolationSequenceRecord.hpp"

} // ENDFtk namespace
} // njoy namespace

#endif
