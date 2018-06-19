ReactionProduct( Multiplicity&& multiplicity,
                 Distribution&& distribution ) :
  multiplicity_( multiplicity ), law_( distribution ) {

  verifyLAW( this->multiplicity_.LAW(),
             std::visit( [] ( const auto& v ) -> int { return v.LAW(); },
                         this->law_ ) );
}

template< typename Iterator >
ReactionProduct( Iterator& begin, const Iterator& end,
                 long& lineNumber, int MAT, int MF, int MT ) :
  multiplicity_( begin, end, lineNumber, MAT, MF, MT ),
  law_( readDistribution( begin, end, lineNumber, MAT, MF, MT, 
                          this->multiplicity_.LAW(),
                          lineNumber - this->multiplicity_.NC() + 1 ) ) {}

