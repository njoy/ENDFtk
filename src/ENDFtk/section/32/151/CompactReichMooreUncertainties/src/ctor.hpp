private:
/**
 *  @brief Private intermediate constructor
 */
CompactReichMooreUncertainties( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifySize( this->NPL(), this->N2() );
}

public:
//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
CompactReichMooreUncertainties() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] awri       the atomic weight ratio
 *  @param[in] apl        the l dependent scattering radius
 *  @param[in] energies   the resonance energies (NRSA values)
 *  @param[in] spins      the spin values (NRSA values)
 *  @param[in] gn         the neutron widths (NRSA values)
 *  @param[in] gg         the gamma widths (NRSA values)
 *  @param[in] gfa        the first fission widths (NRSA values)
 *  @param[in] gfb        the second fission widths (NRSA values)
 *  @param[in] der        the energy uncertainties (NRSA values)
 *  @param[in] dgn        the neutron width uncertainties (NRSA values)
 *  @param[in] dgg        the gamma width uncertainties (NRSA values)
 *  @param[in] dgfa       the first fission width uncertainties (NRSA values)
 *  @param[in] dgfb       the second fission width uncertainties (NRSA values)
 */
CompactReichMooreUncertainties( double awri, double apl,
                                std::vector< double >&& energies,
                                std::vector< double >&& spins,
                                std::vector< double >&& gn,
                                std::vector< double >&& gg,
                                std::vector< double >&& gfa,
                                std::vector< double >&& gfb,
                                std::vector< double >&& der,
                                std::vector< double >&& dgn,
                                std::vector< double >&& dgg,
                                std::vector< double >&& dgfa,
                                std::vector< double >&& dgfb ) :
  // no try ... catch: exceptions will be handled in the derived class
  CompactReichMooreUncertainties(
          ListRecord( awri, apl, 0, 0, energies.size(),
                      generateList( std::move( energies ),
                                    std::move( spins ),
                                    std::move( gn ), std::move( gg ),
                                    std::move( gfa ), std::move( gfb ),
                                    std::move( der ), std::move( dgn ),
                                    std::move( dgg ), std::move( dgfa ),
                                    std::move( dgfb ) ) ) ) {}

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
CompactReichMooreUncertainties( Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT ) :
   // no try ... catch: exceptions will be handled in the derived class
  CompactReichMooreUncertainties( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}

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
 *  @param[in] unused       placeholder
 */
template< typename Iterator >
CompactReichMooreUncertainties( Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT, int ) :
   // no try ... catch: exceptions will be handled in the derived class
  CompactReichMooreUncertainties( it, end, lineNumber, MAT, MF, MT ) {}
