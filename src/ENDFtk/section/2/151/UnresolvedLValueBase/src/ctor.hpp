/**
 *  @brief Constructor
 *
 *  @param[in] awri       the atomic weight ratio
 *  @param[in] l          the orbital angular momentum value
 *  @param[in] jvalues    the unresolved resonance parameters for every J value
 *                        (NJS elements)
 */
UnresolvedLValueBase( double awri, int l, std::vector< JValue >&& jvalues ) :
  awri_( awri ), l_( l ), jvalues_( std::move( jvalues ) ) {

    verifySize( this->NJS() );
  }

private:
/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
UnresolvedLValueBase( ControlRecord&& cont,
                      Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT ) :
  UnresolvedLValueBase( cont.C1(), cont.L1(),
                        readSequence< JValue >( it, end, lineNumber,
                                                MAT, MF, MT, cont.N1() ) ) {}

public:
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
UnresolvedLValueBase( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT ) :
  UnresolvedLValueBase( ControlRecord( it, end, lineNumber, MAT, MF, MT ),
                        it, end, lineNumber, MAT, MF, MT ) {}
