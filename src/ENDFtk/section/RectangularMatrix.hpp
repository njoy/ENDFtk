#ifndef NJOY_ENDFTK_SECTION_RECTANGULARMATRIX
#define NJOY_ENDFTK_SECTION_RECTANGULARMATRIX

// system includes

// other includes
#include "ENDFtk/macros.hpp"
#include "tools/std20/views.hpp"
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

/**
 *  @class
 *  @brief NI-Type Sub-subsection with LB=6
 *
 *  See ENDF102, section 33.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT RectangularMatrix : protected ListRecord {

  static void
  verifyLB( int LB ) {

    if ( LB != 6 ) {

        Log::error( "Encountered illegal LB value" );
        Log::info( "LB must be 6 for RectangularMatrix" );
        Log::info( "LB value: {}", LB );
        throw std::exception();
    }
  }

  /*
   * @brief Verify that sizes are consistent/possible.
   *
   * NEC can be derived from NER, but this requires an appropriate selection
   * of values.  NEC = (NT-1)/NER.  The remainder in this division must be 0.
   */
  static void
  verifySize( int NT, int NER ) {

    // check remainder
    if ( (NT-1) % NER != 0 ) {

      Log::error( "Inconsistent number of values in rectangular matrix" );
      Log::info( "NT: {}", NT );
      Log::info( "NER: {}", NER );
      Log::info( "NEC Remainder: {}", (NT-1) % NER );
      throw std::exception();
    }

  }

  static std::vector< double >
  generateList( std::vector< double >&& rowEnergies,
                std::vector< double >&& columnEnergies,
                std::vector< double >&& values ) {

    std::vector< double > list;

    int NER = rowEnergies.size();
    int NEC = columnEnergies.size();
    int NV = values.size();

    if ( (NER-1)*(NEC-1) != NV ) {
      Log::error( "Inconsistent number of values in rectangular matrix" );
      Log::info( "NER: {}", NER );
      Log::info( "NEC: {}", NEC );
      Log::info( "Expected: {}", (NER-1)*(NEC-1) );
      Log::info( "Observed: {}", NV );
      throw std::exception();
    }

    list.insert( list.end(), rowEnergies.begin(), rowEnergies.end() );
    list.insert( list.end(), columnEnergies.begin(), columnEnergies.end() );
    list.insert( list.end(), values.begin(), values.end() );
    return list;
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  RectangularMatrix() = default;
  #endif

  /**
   *  @brief From list.
   *
   *  Needs to be public for read from Subsection.
   */
  RectangularMatrix( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

      verifyLB( this->LB() );
      verifySize( this->NT(), this->NER() );
  }

  /**
   *  @brief Constructor (LB=5)
   *
   *  @param[in] ls               symmetry flag (0=asymmetric, 1=symmetric)
   *  @param[in] rowEnergies      row energies
   *  @param[in] columnEnergies   column energies
   *  @param[in] values           matrix values
   */
  RectangularMatrix( std::vector< double >&& rowEnergies,
                     std::vector< double >&& columnEnergies,
                     std::vector< double >&& values )
  try :
    RectangularMatrix(
      ListRecord( 0.0, 0.0, 0, 6, rowEnergies.size(),
                  generateList( std::move( rowEnergies ),
                                std::move( columnEnergies ),
                                std::move( values ) ) ) ) {

  } catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing RectangularMatrix component" );
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
  RectangularMatrix( Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT )
  try :
    RectangularMatrix(
      ListRecord( it, end, lineNumber,
                  MAT, MF, MT ) ) {

  } catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing RectangularMatrix component" );
    throw;
  }

  /* methods */

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
   *  @brief Return the number of energies representing a row
   */
  long NER() const { return this->N2(); }

  /**
   *  @brief Return the number of energies representing a row
   */
  long numberRowEnergies() const { return this->NER(); }

  /**
   *  @brief Return the number of energies representing a column
   */
  long NEC() const { return ( this->NT() - 1 ) / this->NER(); }

  /**
   *  @brief Return the number of energies representing a column
   */
  long numberColumnEnergies() const { return this->NEC(); }

  /**
   *  @brief Return the row energy values
   */
  auto rowEnergies() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::take( this->NER() );
  }

  /**
   *  @brief Return the row energy values
   */
  auto columnEnergies() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::take( this->NER() + this->NEC() )
                              | std20::views::drop( this->NER() );
  }

  /**
   *  @brief Return the matrix values
   */
  auto values() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( this->NER() + this->NEC() );
  }

  using ListRecord::NC;
  using ListRecord::print;
};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
