ReactionProduct( Multiplicity&& multiplicity,
                 Distribution&& distribution ) :
  multiplicity_( multiplicity ), law_( distribution ) {

  verifyLAW( this->multiplicity_.LAW(),
             std::visit( [] ( const auto& v ) -> int { return v.LAW(); },
                         this->law_ ) );
}

private:
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
template< typename Iterator >
ReactionProduct( Iterator& begin, const Iterator& end,
                 long& lineNumber, int MAT, int MF, int MT ) :
  ReactionProduct(
      Multiplicity( begin, end, lineNumber, MAT, MF, MT ),
      begin, end, lineNumber, MAT, MF, MT ) {}

