private:

/**
 *  @brief Private intermediate constructor
 */
ShortRangeBreitWignerReichMooreBlockBase( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifySize( this->NPL(), this->MPAR(), this->NRB() );
}

public:

//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
ShortRangeBreitWignerReichMooreBlockBase() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] mpar       the number of parameters with covariances
 *  @param[in] energies   the resonance energies (NRB values)
 *  @param[in] spins      the spin values (NRB values)
 *  @param[in] column1    the first width (NRB values)
 *  @param[in] column2    the second width (NRB values)
 *  @param[in] column3    the third width (NRB values)
 *  @param[in] column4    the fourth width (NRB values)
 *  @param[in] values     the values of the upper diagonal covaraince matrix
 */
ShortRangeBreitWignerReichMooreBlockBase( int mpar,
                                          std::vector< double >&& energies,
                                          std::vector< double >&& spins,
                                          std::vector< double >&& column1,
                                          std::vector< double >&& column2,
                                          std::vector< double >&& column3,
                                          std::vector< double >&& column4,
                                          std::vector< double >&& values ) :
  // no try ... catch: exceptions will be handled in the derived class
  ShortRangeBreitWignerReichMooreBlockBase(
          ListRecord( 0., 0., mpar, 0, energies.size(),
                      generateList( std::move( energies ),
                                    std::move( spins ),
                                    std::move( column1 ),
                                    std::move( column2 ),
                                    std::move( column3 ),
                                    std::move( column4 ),
                                    std::move( values ) ) ) ) {}

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
ShortRangeBreitWignerReichMooreBlockBase(
        Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT ) :
   // no try ... catch: exceptions will be handled in the derived class
  ShortRangeBreitWignerReichMooreBlockBase( ListRecord( it, end, lineNumber,
                                                        MAT, MF, MT ) ) {}
