/**
 *  @brief Constructor
 *
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] lssf      the self-shielding only flag
 *  @param[in] lvalues   the l values and the resonance parameters
 */
UnresolvedBase( double spi, double ap, bool lssf,
                std::vector< LValue >&& lvalues ) :
    // no need for a try ... catch: nothing can go wrong here
    UnresolvedBaseWithoutSpin< Derived >( std::move( lvalues ) ),
    spi_( spi ), ap_( ap ), lssf_( lssf ) {}

private:
/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
UnresolvedBase( ControlRecord&& cont,
                Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT ) :
  UnresolvedBase( cont.C1(), cont.C2(), cont.L1(),
                  readSequence< LValue >( it, end, lineNumber,
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
UnresolvedBase( Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT ) :
  UnresolvedBase( ControlRecord( it, end, lineNumber, MAT, MF, MT ),
                  it, end, lineNumber, MAT, MF, MT ) {}
