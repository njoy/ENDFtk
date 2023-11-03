//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
UnresolvedRelativeCovariances() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] lssf      the self-shielding only flag
 *  @param[in] lvalues   the l values and the resonance parameters
 */
UnresolvedRelativeCovariances( double spi, double ap,
                               std::vector< LValue >&& lvalues,
                               CovarianceMatrix&& matrix ) :
    // no need for a try ... catch: nothing can go wrong here
    spi_( spi ), ap_( ap ), lvalues_( std::move( lvalues ) ),
    matrix_( std::move( matrix ) ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
UnresolvedRelativeCovariances( double spi, double ap,
                               std::vector< LValue >&& lvalues,
                               Iterator& it, const Iterator& end, long& lineNumber,
                               int MAT, int MF, int MT ) :
  UnresolvedRelativeCovariances( spi, ap, std::move( lvalues ),
                                 CovarianceMatrix( it, end, lineNumber,
                                                   MAT, MF, MT ) ) {}

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
UnresolvedRelativeCovariances( ControlRecord&& cont,
                               Iterator& it, const Iterator& end, long& lineNumber,
                               int MAT, int MF, int MT ) :
  UnresolvedRelativeCovariances( cont.C1(), cont.C2(),
                                 readSequence< LValue >( it, end, lineNumber,
                                                         MAT, MF, MT,
                                                         cont.N1() ),
                                 it, end, lineNumber, MAT, MF, MT ) {}

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
UnresolvedRelativeCovariances(
    Iterator& it, const Iterator& end, long& lineNumber,
    int MAT, int MF, int MT ) :
  UnresolvedRelativeCovariances(
      ControlRecord( it, end, lineNumber, MAT, MF, MT ),
      it, end, lineNumber, MAT, MF, MT ) {}
