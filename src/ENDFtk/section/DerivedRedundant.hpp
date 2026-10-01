#ifndef NJOY_ENDFTK_SECTION_DERIVEDREDUNDANT
#define NJOY_ENDFTK_SECTION_DERIVEDREDUNDANT

// system includes

// other includes
#include "ENDFtk/macros.hpp"
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

/**
 *  @class
 *  @brief NC-Type Sub-subsection with LTY=0
 *
 *  See ENDF102, section 33.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT DerivedRedundant {

   /* fields */

   ListRecord list_;

   /* auxiliary functions */

   static void
   verifyLTY( int LTY ) {

     if ( LTY != 0 ) {

         Log::error( "Encountered illegal LTY value" );
         Log::info( "LTY must be 0 for DerivedRedundant" );
         Log::info( "LTY value: {}", LTY );
         throw std::exception();
     }
   }

   static std::vector< double >
   generateList( std::vector< double >&& coefficients,
                 std::vector< int >&& reactions ) {

     if ( coefficients.size() != reactions.size() ) {

       Log::error( "The number of coefficients and reactions are not consistent" );
       Log::info( "coefficients.size(): {}", coefficients.size() );
       Log::info( "reactions.size(): {}", reactions.size() );
       throw std::exception();
     }

     std::vector< double > list;

     for ( unsigned int i = 0; i < coefficients.size(); ++i ) {

       list.push_back( coefficients[i] );
       list.push_back( reactions[i] );
     }

     return list;
   }

 public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  DerivedRedundant() = default;
  #endif


  /**
   *  @brief Cascade for buffer iterator
   *
   *  Needs to be public for reading from Subsection.
   *
   */
  template< typename Iterator >
  DerivedRedundant( int LTY,
                    Iterator& it, const Iterator& end, long& lineNumber,
                    int MAT, int MF, int MT ) :
    list_( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {

      verifyLTY( LTY );
    }

  /**
   *  @brief Constructor
   *
   *  @param[in] e1             lower energy
   *  @param[in] e2             upper energy
   *  @param[in] coefficients   coefficients to combine linearly
   *  @param[in] reactions      reaction MTs
   */
  DerivedRedundant( double e1, double e2,
                    std::vector< double >&& coefficients,
                    std::vector< int >&& reactions )
  try :
    list_(
      ListRecord( e1, e2, 0, 0, coefficients.size(),
                  generateList( std::move( coefficients ),
                                std::move( reactions ) ) ) ) {

  } catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing DerivedRedundant component" );
    throw;
  }

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   */
  template< typename Iterator >
  DerivedRedundant( Iterator& it, const Iterator& end, long& lineNumber,
                    int MAT, int MF, int MT )
  try :
    DerivedRedundant(
      ControlRecord( it, end, lineNumber, MAT, MF, MT ).L2(),
      it, end, lineNumber, MAT, MF, MT ) {

  } catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing DerivedRedundant component" );
    throw;
  }

  /* methods */

  /**
   *  @brief Return the procedure
   */
  static constexpr int LTY() { return 0; }

  /**
   *  @brief Return the procedure
   */
  int procedure() const { return this->LTY(); }

  /**
   *  @brief Return the lower energy bound
   */
  double E1() const { return this->list_.C1(); }

  /**
   *  @brief Return the lower energy bound
   */
  double lowerEnergy() const { return this->E1(); }

  /**
   *  @brief Return the upper energy bound
   */
  double E2() const { return this->list_.C2(); }

  /**
   *  @brief Return the upper energy bound
   */
  double upperEnergy() const { return this->E2(); }

  /**
   *  @brief Return the number of reactions
   */
  int NCI() const { return this->list_.N2(); }

  /**
   *  @brief Return the number of reactions
   */
  int numberReactions() const { return this->NCI(); }

  /**
   *  @brief Return the coefficients
   */
  auto CI() const {

    using namespace njoy::tools;
    return this->list_.list() | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the coefficients
   */
  auto coefficients() const { return this->CI(); }

  /**
   *  @brief Return the reaction MTs
   */
  auto XMTI() const {

    using namespace njoy::tools;
    return this->list_.list() | std20::views::drop( 1 )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the reaction MTs
   */
  auto reactions() const { return this->XMTI(); }

  /**
   *  @brief Return the number of lines in this MF15 component
   */
  long NC() const { return 1 + this->list_.NC(); }

  /**
   *  @brief Print the DerivedRedundant component
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

    ControlRecord( 0.0, 0.0, 0, 0, 0, 0).print( it, MAT, MF, MT );
    this->list_.print( it, MAT, MF, MT );
  }

};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
