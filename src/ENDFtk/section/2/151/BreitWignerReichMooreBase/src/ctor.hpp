//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
BreitWignerReichMooreBase() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] lad       the angular distributions flag
 *  @param[in] nlsc      the number of l values for convergence
 *  @param[in] lvalues   the l values and the resonance parameters
 */
BreitWignerReichMooreBase( double spi, double ap, bool lad, int nlsc,
                           std::vector< LValue >&& lvalues ) :
    // no need for a try ... catch: nothing can go wrong here
    spi_( spi ), ap_( ap ), lad_( lad ), nlsc_( nlsc ),
    lvalues_( std::move( lvalues ) ) {

      verifySize( this->NLS() );
    }

private:
/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
BreitWignerReichMooreBase( ControlRecord&& cont,
                           Iterator& it, const Iterator& end, long& lineNumber,
                           int MAT, int MF, int MT ) :
   // no try ... catch: exceptions will be handled in the derived class
  BreitWignerReichMooreBase( cont.C1(), cont.C2(), cont.L1(), cont.N2(),
                             readSequence< LValue >(
                                 it, end, lineNumber,
                                 MAT, MF, MT, cont.N1() ) ) {}

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
 BreitWignerReichMooreBase( Iterator& it, const Iterator& end, long& lineNumber,
                            int MAT, int MF, int MT ) :
   // no try ... catch: exceptions will be handled in the derived class
   BreitWignerReichMooreBase(
     ControlRecord( it, end, lineNumber, MAT, MF, MT ),
     it, end, lineNumber, MAT, MF, MT ) {}
