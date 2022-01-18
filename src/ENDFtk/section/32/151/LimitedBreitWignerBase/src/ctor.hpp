private:

/**
 *  @brief Private constructor
 */
LimitedBreitWignerBase( double spi, double ap, std::optional< double >&& dap,
                        std::vector< LValue >&& lvalues ) :
    // no need for a try ... catch: nothing can go wrong here
    spi_( spi ), ap_( ap ), dap_( dap ),
    lvalues_( std::move( lvalues ) ) {

      verifySize( this->NLS() );
    }

public:
//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
LimitedBreitWignerBase() = default;
#endif

/**
 *  @brief Constructor with scattering radius uncertainty
 *
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] lvalues   the l values and the resonance parameters
 */
LimitedBreitWignerBase( double spi, double ap, double dap,
                        std::vector< LValue >&& lvalues ) :
  // no need for a try ... catch: nothing can go wrong here
  LimitedBreitWignerBase( spi, ap, std::make_optional( dap ),
                          std::move( lvalues ) ) {}

/**
 *  @brief Constructor without scattering radius uncertainty
 *
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] lvalues   the l values and the resonance parameters
 */
LimitedBreitWignerBase( double spi, double ap,
                        std::vector< LValue >&& lvalues ) :
  // no need for a try ... catch: nothing can go wrong here
  LimitedBreitWignerBase( spi, ap, std::nullopt, std::move( lvalues ) ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
LimitedBreitWignerBase( double spi, double ap, std::optional< double >&& dap,
                        Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT, int N ) :
  // no try ... catch: exceptions will be handled in the derived class
  LimitedBreitWignerBase( spi, ap, std::move( dap ),
                          readSequence< LValue >( it, end, lineNumber,
                                                  MAT, MF, MT, N ) ) {}

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
LimitedBreitWignerBase( ControlRecord&& cont,
                        Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT ) :
  // no try ... catch: exceptions will be handled in the derived class
  LimitedBreitWignerBase( cont.C1(), cont.C2(),
                          cont.N2()
                            ? std::make_optional( ControlRecord( it, end, lineNumber,
                                                                 MAT, MF, MT ).C2() )
                            : std::nullopt,
                          it, end, lineNumber, MAT, MF, MT, cont.N1() ) {}

protected:
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
 LimitedBreitWignerBase( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) :
   // no try ... catch: exceptions will be handled in the derived class
   LimitedBreitWignerBase(
     ControlRecord( it, end, lineNumber, MAT, MF, MT ),
     it, end, lineNumber, MAT, MF, MT ) {}
