private:
/**
 *  @brief Private intermediate constructor
 */
BreitWignerReichMooreLValueBase( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifySize( this->NPL(), this->N2() );
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
 *  @param[in] column1    the the first width (NRS values)
 *  @param[in] column2    the the second width (NRS values)
 *  @param[in] column3    the the third width (NRS values)
 *  @param[in] column4    the the fourth width (NRS values)
 */
BreitWignerReichMooreLValueBase( double awri, double c2, int l, bool l2,
                                 std::vector< double >&& energies,
                                 std::vector< double >&& spins,
                                 std::vector< double >&& column1,
                                 std::vector< double >&& column2,
                                 std::vector< double >&& column3,
                                 std::vector< double >&& column4 ) :
  // no try ... catch: exceptions will be handled in the derived class
  BreitWignerReichMooreLValueBase(
          ListRecord( awri, c2, l, l2, energies.size(),
                      generateList( std::move( energies ),
                                    std::move( spins ),
                                    std::move( column1 ),
                                    std::move( column2 ),
                                    std::move( column3 ),
                                    std::move( column4 ) ) ) ) {}

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
BreitWignerReichMooreLValueBase(
        Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT ) :
   // no try ... catch: exceptions will be handled in the derived class
  BreitWignerReichMooreLValueBase( ListRecord( it, end, lineNumber,
                                               MAT, MF, MT ) ) {}
