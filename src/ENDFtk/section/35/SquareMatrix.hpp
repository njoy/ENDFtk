/**
 *  @class
 *  @brief NI-Type Sub-subsection with LB=7
 *
 *  See ENDF102, section 35.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT SquareMatrix : protected ListRecord {

  static void
  verifyLB( int LB ) {

    if ( LB != 7 ) {

        Log::error( "Encountered illegal LB value" );
        Log::info( "LB must be 7 for SquareMatrix in MF35" );
        Log::info( "LB value: {}", LB );
        throw std::exception();
    }
  }

  // intentionally taken from File 33

  static void
  verifySize( int LS, int NE, int NT ) {

    int num_values = NT-NE;

    // symmetric matrix
    if ( LS ) {

      if ( num_values != NE*(NE-1)/2 ) {

        Log::error( "Inconsistent number of values in symetric square matrix" );
        Log::info( "Expected (NE*(NE-1)/2): {}", NE*(NE-1)/2 );
        Log::info( "Observed value: {}", num_values );
        throw std::exception();
      }
    }

    // asymmetric matrix
    else {

      if ( num_values != (NE-1)*(NE-1) ) {

        Log::error( "Inconsistent number of values in symetric square matrix" );
        Log::info( "Expected ((NE-1)^2): {}", (NE-1)*(NE-1) );
        Log::info( "Observed value: {}", num_values );
        throw std::exception();
      }
    }

  }

  static std::vector< double >
  generateList( std::vector< double >&& energies,
                std::vector< double >&& values ) {

    std::vector< double > list;
    list.insert( list.end(), energies.begin(), energies.end() );
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
  SquareMatrix() = default;
  #endif

  /**
   *  @brief From list.
   *
   *  Needs to be public for read from Subsection.
   */
  SquareMatrix( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

      verifyLB( this->LB() );
      verifySize( 1, this->NE(), this->NT() );
  };

  /**
   *  @brief Constructor (LB=7)
   *
   *  @param[in] e1             lowest incident energy
   *  @param[in] e2             highest incident energy
   *  @param[in] energies       energies
   *  @param[in] values         matrix values
   */
  SquareMatrix( double e1, double e2,
                std::vector< double >&& energies,
                std::vector< double >&& values )
  try :
    SquareMatrix(
      ListRecord( e1, e2, 1, 7, energies.size(),
                  generateList( std::move( energies ),
                                std::move( values ) ) ) ) {

  } catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing SquareMatrix component" );
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
  SquareMatrix( Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT )
  try :
    SquareMatrix(
      ListRecord( it, end, lineNumber,
                  MAT, MF, MT ) ) {

  } catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing SquareMatrix component" );
    throw;
  }

  /* methods */

  /**
   *  @brief Return the lowest incident energy
   */
  int E1() const { return ListRecord::C1(); }

  /**
   *  @brief Return the lowest incident energy
   */
  int lowestEnergy() const { return this->E1(); }

  /**
   *  @brief Return the highest incident energy
   */
  int E2() const { return ListRecord::C2(); }

  /**
   *  @brief Return the highest incident energy
   */
  int highestEnergy() const { return this->E2(); }

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
   *  @brief Return the number of energies in the array
   */
  long NE() const { return this->N2(); }

  /**
   *  @brief Return the number of energies in the array
   */
  long numberEnergies() const { return this->NE(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::take( this->NE() );
  }

  /**
   *  @brief Return the matrix values
   */
  auto values() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( this->NE() );
  }

  using ListRecord::NC;
  using ListRecord::print;

};
