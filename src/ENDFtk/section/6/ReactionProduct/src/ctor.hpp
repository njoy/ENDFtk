/**
 *  @brief Constructor (one total and multiple partials)
 *
 *  @param[in] multiplicity    the multiplicity
 *  @param[in] distribution    the distribution
 */
ReactionProduct( Multiplicity&& multiplicity,
                 Distribution&& distribution ) :
  multiplicity_( multiplicity ), law_( distribution ) {

  verifyLAW( this->multiplicity_.LAW(),
             std::visit( [] ( const auto& v ) -> int { return v.LAW(); },
                         this->law_ ) );
}

private:

/**
 *  @brief Private constructor
 */
template< typename Iterator >
ReactionProduct( Multiplicity&& multiplicity,
                 Iterator& begin, const Iterator& end,
                 long& lineNumber, int MAT, int MF, int MT ) :
  ReactionProduct(
    std::move( multiplicity ),
    readDistribution( begin, end, lineNumber, MAT, MF, MT,
                      multiplicity.LAW(),
                      lineNumber - multiplicity.NC() + 1 ) ) {}

public:

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
 *  @param[in] NK           the number of partials
 */
template< typename Iterator >
ReactionProduct( Iterator& begin, const Iterator& end,
                 long& lineNumber, int MAT, int MF, int MT ) :
  ReactionProduct(
      Multiplicity( begin, end, lineNumber, MAT, MF, MT ),
      begin, end, lineNumber, MAT, MF, MT ) {}
