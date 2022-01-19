private:
/**
 *  @brief Private intermediate constructor
 */
ShortRangeBreitWignerReichMooreBlockBase( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifySize( this->NPL(), this->MPAR(), this->NRB() );
}

public:
/**
 *  @brief Constructor
 *
 *  @param[in] awri       the atomic weight ratio
 *  @param[in] c2         the value in C2
 *  @param[in] l          the orbital angular momentum value
 *  @param[in] l2         the value in l2
 *  @param[in] energies   the resonance energies (NRS values)
 *  @param[in] spins      the spin values (NRS values)
 *  @param[in] column1    the first width (NRS values)
 *  @param[in] column2    the second width (NRS values)
 *  @param[in] column3    the third width (NRS values)
 *  @param[in] column4    the fourth width (NRS values)
 */
ShortRangeBreitWignerReichMooreBlockBase( double awri, int mpar,
                                          std::vector< double >&& energies,
                                          std::vector< double >&& spins,
                                          std::vector< double >&& column1,
                                          std::vector< double >&& column2,
                                          std::vector< double >&& column3,
                                          std::vector< double >&& column4,
                                          std::vector< double >&& values ) :
  // no try ... catch: exceptions will be handled in the derived class
  ShortRangeBreitWignerReichMooreBlockBase(
          ListRecord( awri, 0., 0, mpar, energies.size(),
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
