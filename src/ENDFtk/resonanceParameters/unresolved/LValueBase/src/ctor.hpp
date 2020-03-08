/**
 *  @brief Constructor
 *
 *  @param[in] awri       the atomic weight ratio
 *  @param[in] l          the orbital angular momentum value
 *  @param[in] jvalues    the unresolved resonance parameters for every J value
 *                        (NJS elements)
 */
LValueBase( double awri, int l, std::vector< JValue >&& jvalues ) :
  awri_( awri ), l_( l ), jvalues_( std::move( jvalues ) ) {}

private:
/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
LValueBase( ControlRecord&& cont,
            Iterator& it, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT ) :
  awri_( cont.C1() ), l_( cont.L1() ),
  jvalues_( readJValues( it, end, lineNumber,
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
LValueBase( Iterator& it, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT ) :
  LValueBase( ControlRecord( it, end, lineNumber, MAT, MF, MT ),
              it, end, lineNumber, MAT, MF, MT ) {}
