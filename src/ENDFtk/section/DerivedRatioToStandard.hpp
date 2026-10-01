#ifndef NJOY_ENDFTK_SECTION_DERIVEDRATIOTOSTANDARD
#define NJOY_ENDFTK_SECTION_DERIVEDRATIOTOSTANDARD

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
 *  @brief NC-Type Sub-subsection with LTY=1,2,3
 *
 *  See ENDF102, section 33.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT DerivedRatioToStandard {

   /* fields */

   int lty_;
   ListRecord list_;

   /* auxiliary functions */

   static void
   verifyLTY( int LTY ) {

     if ( LTY < 1 || LTY > 3 ) {

         Log::error( "Encountered illegal LTY value" );
         Log::info( "LTY must be 1,2,3 for DerivedRatioToStandard" );
         Log::info( "LTY value: {}", LTY );
         throw std::exception();
     }
   }

   static std::vector< double >
   generateList( double XMFS, double XLFSS,
                 std::vector< double >&& energies,
                 std::vector< double >&& weights ) {

     if ( energies.size() != weights.size() ) {

       Log::error( "The number of energies and weights are not consistent" );
       Log::info( "energies.size(): {}", energies.size() );
       Log::info( "weights.size(): {}", weights.size() );
       throw std::exception();
     }

     std::vector< double > list = { XMFS, XLFSS };

     for ( unsigned int i = 0; i < energies.size(); ++i ) {

       list.push_back( energies[i] );
       list.push_back( weights[i] );
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
  DerivedRatioToStandard() = default;
  #endif

  /**
   *  @brief Cascade for buffer iterator
   *
   *  Needs to be public for reading from Subsection.
   *
   */
  template< typename Iterator >
  DerivedRatioToStandard( int LTY,
                    Iterator& it, const Iterator& end, long& lineNumber,
                    int MAT, int MF, int MT ) :
    lty_( LTY ),
    list_( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {

      verifyLTY( this->LTY() );
    }

  /**
   *  @brief Constructor
   *
   *  @param[in] lty            covariance procedure
   *  @param[in] e1             lower energy
   *  @param[in] e2             upper energy
   *  @param[in] mats           standard's material number
   *  @param[in] mts            standard's MT number
   *  @param[in] xmfs           standard's MF number
   *  @param[in] xlfss          standard's final excited state
   *  @param[in] energies       energy boundaries of intervals
   *  @param[in] weights        weights of energies
   */
  DerivedRatioToStandard( int lty, double e1, double e2,
                    int mats, int mts, int xmfs, int xlfss,
                    std::vector< double >&& energies,
                    std::vector< double >&& weights )
  try :
    lty_( lty ),
    list_(
      ListRecord( e1, e2, mats, mts, energies.size(),
                  generateList( xmfs, xlfss,
                                std::move( energies ),
                                std::move( weights ) ) ) ) {

  } catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing DerivedRatioToStandard component" );
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
  DerivedRatioToStandard( Iterator& it, const Iterator& end, long& lineNumber,
                          int MAT, int MF, int MT )
  try :
    DerivedRatioToStandard(
      ControlRecord( it, end, lineNumber, MAT, MF, MT ).L2(),
      it, end, lineNumber, MAT, MF, MT ) {

  } catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing DerivedRatioToStandard component" );
    throw;
  }

  /* methods */

  /**
   *  @brief Return the procedure
   */
  int LTY() const { return this->lty_; }

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
   *  @brief Return the standard's material number
   */
  int MATS() const { return this->list_.L1(); }

  /**
   *  @brief Return the standard's material number
   */
  int standardMaterialNumber() const { return this->MATS(); }

  /**
   *  @brief Return the standard's MT number
   */
  int MTS() const { return this->list_.L2(); }

  /**
   *  @brief Return the standard's MT number
   */
  int standardSectionNumber() const { return this->MTS(); }

  /**
   *  @brief Return the number of energies
   */
  int NEI() const { return this->list_.N2(); }

  /**
   *  @brief Return the number of energies
   */
  int numberEnergies() const { return this->NEI(); }

  /**
   *  @brief Return the standard's MF number
   */
  int XMFS() const { return this->list_.list()[0]; }

  /**
   *  @brief Return the standard's MF number
   */
  int standardFileNumber() const { return this->XMFS(); }

  /**
   *  @brief Return the standard's final excited state
   */
  int XLFSS() const { return this->list_.list()[1]; }

  /**
   *  @brief Return the standard's final excited state
   */
  int standardFinalExcitedState() const { return this->XLFSS(); }

  /**
   *  @brief Return the energies
   */
  auto EI() const {

    using namespace njoy::tools;
    return this->list_.list() | std20::views::drop( 2 )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the energies
   */
  auto energies() const { return this->EI(); }

  /**
   *  @brief Return the weights
   */
  auto WEI() const {

    using namespace njoy::tools;
    return this->list_.list() | std20::views::drop( 3 )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the coefficients
   */
  auto weights() const { return this->WEI(); }


  /**
   *  @brief Return the number of lines in this MF33 component
   */
  long NC() const { return 1 + this->list_.NC(); }

  /**
   *  @brief Print the DerivedRatioToStandard component
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

    ControlRecord( 0.0, 0.0, 0, this->LTY(), 0, 0).print( it, MAT, MF, MT );
    this->list_.print( it, MAT, MF, MT );
  }

};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
