private:
/**
 *  @brief Private intermediate constructor
 */
LimitedBreitWignerLValue( ListRecord&& list ) :
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
 *  @param[in] gt         the total widths (NRS values)
 *  @param[in] gn         the neutron widths (NRS values)
 *  @param[in] gg         the gamma widths (NRS values)
 *  @param[in] gf         the fission widths (NRS values)
 *  @param[in] de2        the energy variances (NRS values)
 *  @param[in] dn2        the neutron width variances (NRS values)
 *  @param[in] dndg       the neutron and gamma width covariances (NRS values)
 *  @param[in] dg2        the gamma width variances (NRS values)
 *  @param[in] dndf       the neutron and fission width covariances (NRS values)
 *  @param[in] dgdf       the gamma and fission width covariances (NRS values)
 *  @param[in] df2        the fission width variances (NRS values)
 *  @param[in] djdn       the spin and neutron width covariances (NRS values)
 *  @param[in] djdg       the spin and gamma width covariances (NRS values)
 *  @param[in] djdf       the spin and fission width covariances (NRS values)
 *  @param[in] df2        the spin variances (NRS values)
 */
LimitedBreitWignerLValue( double awri, int l,
                          std::vector< double >&& energies,
                          std::vector< double >&& spins,
                          std::vector< double >&& gt,
                          std::vector< double >&& gn,
                          std::vector< double >&& gg,
                          std::vector< double >&& gf,
                          std::vector< double >&& de2,
                          std::vector< double >&& dn2,
                          std::vector< double >&& dndg,
                          std::vector< double >&& dg2,
                          std::vector< double >&& dndf,
                          std::vector< double >&& dgdf,
                          std::vector< double >&& df2,
                          std::vector< double >&& djdn,
                          std::vector< double >&& djdg,
                          std::vector< double >&& djdf,
                          std::vector< double >&& dj2 ) :
  // no try ... catch: exceptions will be handled in the derived class
  LimitedBreitWignerLValue(
          ListRecord( awri, 0., l, 0, energies.size(),
                      generateList( std::move( energies ),
                                    std::move( spins ),
                                    std::move( gt ), std::move( gn ),
                                    std::move( gg ), std::move( gf ),
                                    std::move( de2 ), std::move( dn2 ),
                                    std::move( dndg ), std::move( dg2 ),
                                    std::move( dndf ), std::move( dgdf ),
                                    std::move( df2 ), std::move( djdn ),
                                    std::move( djdg ), std::move( djdf ),
                                    std::move( dj2 ) ) ) ) {}

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
LimitedBreitWignerLValue( Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT ) :
   // no try ... catch: exceptions will be handled in the derived class
  LimitedBreitWignerLValue( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
