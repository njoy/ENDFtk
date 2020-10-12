/**
 *  @brief Constructor
 *
 *  @param[in] probability    the probability
 *  @param[in] spectrum       the spectrum
 */
PartialDistribution( Probability&& probability,
                     Distribution&& spectrum ) :
  probability_( std::move( probability ) ),
  distribution_( std::move( spectrum ) ) {

  verifyLF( this->probability_.LF(),
            std::visit( [&] ( const auto& entry )
                            { return entry.LF(); },
                        this->distribution_ ) );
}

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] begin        the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 *  @param[in] MF           the expected MF number
 *  @param[in] MT           the expected MT number
 */
template< typename Iterator >
PartialDistribution( Iterator& begin,
                     const Iterator& end,
                     long& lineNumber,
                     int MAT,
                     int MF,
                     int MT ) :
  PartialDistribution( readPartialDistribution( begin, end, lineNumber,
                                                MAT, MF, MT ) ) {}
