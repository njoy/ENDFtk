private:
/**
 *  @brief Private intermediate constructor
 */
CompactBreitWignerUncertainties( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifySize( this->NPL(), this->N2() );
}

public:
//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
CompactBreitWignerUncertainties() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] awri       the atomic weight ratio
 *  @param[in] qx         the competitive Q value
 *  @param[in] lrx        the competitive width flag
 *  @param[in] energies   the resonance energies (NRSA values)
 *  @param[in] spins      the spin values (NRSA values)
 *  @param[in] gt         the total widths (NRSA values)
 *  @param[in] gn         the neutron widths (NRSA values)
 *  @param[in] gg         the gamma widths (NRSA values)
 *  @param[in] gf         the fission widths (NRSA values)
 *  @param[in] der        the energy uncertainties (NRSA values)
 *  @param[in] dgn        the neutron width uncertainties (NRSA values)
 *  @param[in] dgg        the gamma width uncertainties (NRSA values)
 *  @param[in] dgf        the fission width uncertainties (NRSA values)
 */
CompactBreitWignerUncertainties( double awri, double qx, bool lrx,
                                 std::vector< double >&& energies,
                                 std::vector< double >&& spins,
                                 std::vector< double >&& gt,
                                 std::vector< double >&& gn,
                                 std::vector< double >&& gg,
                                 std::vector< double >&& gf,
                                 std::vector< double >&& der,
                                 std::vector< double >&& dgn,
                                 std::vector< double >&& dgg,
                                 std::vector< double >&& dgf ) :
  // no try ... catch: exceptions will be handled in the derived class
  CompactBreitWignerUncertainties(
          ListRecord( awri, qx, 0, lrx, energies.size(),
                      generateList( std::move( energies ),
                                    std::move( spins ),
                                    std::move( gt ), std::move( gn ),
                                    std::move( gg ), std::move( gf ),
                                    std::move( der ), std::move( dgn ),
                                    std::move( dgg ), std::move( dgf ) ) ) ) {}

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
CompactBreitWignerUncertainties( Iterator& it, const Iterator& end, long& lineNumber,
                                 int MAT, int MF, int MT ) :
   // no try ... catch: exceptions will be handled in the derived class
  CompactBreitWignerUncertainties( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
