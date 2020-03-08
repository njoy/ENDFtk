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
    spi_( spi ), ap_( ap ), lssf_( lssf ),
    lvalues_( std::move( lvalues ) ) {}
