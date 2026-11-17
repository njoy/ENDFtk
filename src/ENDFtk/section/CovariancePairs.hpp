#ifndef NJOY_ENDFTK_SECTION_COVARIANCEPAIRS
#define NJOY_ENDFTK_SECTION_COVARIANCEPAIRS

// system includes

// other includes
#include "ENDFtk/macros.hpp"
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

/**
 *  @class
 *  @brief NI-Type Sub-subsection with LB=0,1,2,3,4,8,9
 *
 *  See ENDF102, section 33.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT CovariancePairs : protected ListRecord {

  static void
  verifyLB( int LB, int LT ) {

    switch( LB ) {

      case 0:
      case 1:
      case 2:
      case 8:
      case 9:
        if ( LT != 0 ) {
          Log::error( "Encountered illegal LT value" );
          Log::info( "LT must be equal to 0 for LB=0,1,2,8,9" );
          Log::info( "LT value: {}", LT );
          throw std::exception();
        }
        break;

      case 3:
      case 4:
        if ( LT <= 0 ) {
          Log::error( "Encountered illegal LT value" );
          Log::info( "LT must be positive for LB=3,4" );
          Log::info( "LT value: {}", LT );
          throw std::exception();
        }
        break;

      default:
        Log::error( "Encountered illegal LB value" );
        Log::info( "LB must be 0,1,2,3,4,8,9 for CovariancePairs" );
        Log::info( "LB value: {}", LB );
        throw std::exception();

    }

  }

  static void
  verifySize( int NT, int NP ) {

    if ( NT != 2*NP ) {
      Log::error( "Number of pairs inconsistent with vector size" );
      Log::info( "NT value: {}", NT );
      Log::info( "NP value: {}", NP );
      throw std::exception();
    }

  }

  static std::vector< double >
  generateList( std::vector< double >&& ek,
                std::vector< double >&& fk ) {

    if ( ek.size() != fk.size() ) {

      Log::error( "The number of energies and F values are not consistent" );
      Log::info( "energies.size(): {}", ek.size() );
      Log::info( "fvalues.size(): {}", fk.size() );
      throw std::exception();
    }

    std::vector< double > list;

    for ( unsigned int i = 0; i < ek.size(); ++i ) {

      list.push_back( ek[i] );
      list.push_back( fk[i] );
    }

    return list;
  }

  static std::vector< double >
  generateList( std::vector< double >&& ek,
                std::vector< double >&& fk,
                std::vector< double >&& el,
                std::vector< double >&& fl ) {

    if ( ek.size() != fk.size() ) {

      Log::error( "The number of first array energies and F values "
                  "are not consistent" );
      Log::info( "energies.size(): {}", ek.size() );
      Log::info( "fvalues.size(): {}", fk.size() );
      throw std::exception();
    }

    else if ( el.size() != fl.size() ) {

      Log::error( "The number of second array energies and F values "
                  "are not consistent" );
      Log::info( "energies.size(): {}", el.size() );
      Log::info( "fvalues.size(): {}", fl.size() );
      throw std::exception();
    }

    std::vector< double > list;

    for ( unsigned int i = 0; i < ek.size(); ++i ) {

      list.push_back( ek[i] );
      list.push_back( fk[i] );
    }
    for ( unsigned int i = 0; i < el.size(); ++i ) {

      list.push_back( el[i] );
      list.push_back( fl[i] );
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
  CovariancePairs() = default;
  #endif

  /**
   *  @brief From list.
   *
   *  Needs to be public for read from Subsection.
   */
  CovariancePairs( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

      verifyLB( this->LB(), this->LT() );
      verifySize( this->NT(), this->N2() );
  }

  /**
   *  @brief Constructor (LB=0,1,2,8,9)
   *
   *  @param[in] lb             the procedure type flag
   *  @param[in] energies       energies
   *  @param[in] fvalues        F values
   */
  CovariancePairs( int lb,
                   std::vector< double >&& energies,
                   std::vector< double >&& fvalues )
  try :
    CovariancePairs(
      ListRecord( 0.0, 0.0, 0, lb, energies.size(),
                  generateList( std::move( energies ),
                                std::move( fvalues ) ) ) ) {

  } catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing CovariancePairs component" );
    throw;
  }

  /**
   *  @brief Constructor (LB=3,4)
   *
   *  @param[in] lb             the procedure type flag
   *  @param[in] ek             first array energies
   *  @param[in] fk             first array F values
   *  @param[in] el             second array energies
   *  @param[in] fl             second array F values
   */
  CovariancePairs( int lb,
                   std::vector< double>&& ek,
                   std::vector< double >&& fk,
                   std::vector< double>&& el,
                   std::vector< double >&& fl )
  try :
    CovariancePairs(
      ListRecord( 0.0, 0.0, el.size(), lb, ek.size()+el.size(),
                  generateList( std::move( ek ),
                                std::move( fk ),
                                std::move( el ),
                                std::move( fl ) ) ) ) {

  } catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing CovariancePairs component" );
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
  CovariancePairs( Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT )
  try :
    CovariancePairs(
      ListRecord( it, end, lineNumber,
                  MAT, MF, MT ) ) {

  } catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing CovariancePairs component" );
    throw;
  }

  /* methods */

  /**
   *  @brief Return the number of pairs in the second array
   */
  int LT() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of pairs in the second array
   */
  int numberSecondPairs() const { return this->LT(); }

  /**
   *  @brief Return the procedure type
   */
  int LB() const { return this->L2(); }

  /**
   *  @brief Return the procedure type
   */
  int procedure() const { return this->LB(); }

  /**
   *  @brief Return the number of values in this component
   */
  long NT() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the number of values in this component
   */
  long numberValues() const { return this->NT(); }

  /**
   *  @brief Return the total number of pairs
   */
  long NP() const { return this->NT()/2; }

  /**
   *  @brief Return the total number of pairs
   */
  long numberPairs() const { return this->NP(); }

  /**
   *  @brief Return the energy values from the first array
   */
  auto EK() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::take( 2 * ( this->NP() - this->LT() ) )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the energy values from the first array
   */
  auto firstArrayEnergies() const { return this->EK(); }

  /**
   *  @brief Return the F values from the first array
   */
  auto FK() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::take(  2 * ( this->NP() - this->LT() ) )
                              | std20::views::drop( 1 )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the F values from the first array
   */
  auto firstArrayFValues() const { return this->FK(); }

  /**
   *  @brief Return the energy values from the second array
   */
  auto EL() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 2 * ( this->NP() - this->LT() ) )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the energy values from the second array
   */
  auto secondArrayEnergies() const { return this->EL(); }

  /**
   *  @brief Return the F values from the second array
   */
  auto FL() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 2 * ( this->NP() - this->LT() ) + 1 )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the F values from the second array
   */
  auto secondArrayFValues() const { return this->FL(); }

  using ListRecord::NC;
  using ListRecord::print;
};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
