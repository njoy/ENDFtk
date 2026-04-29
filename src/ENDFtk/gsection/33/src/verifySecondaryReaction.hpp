void verifySecondaryReaction( std::size_t sec_rxn ) const {

  std::vector< std::size_t > sec_rxns;
  sec_rxns.reserve( this->covr_.size() );
  for ( const auto& [sec_rxn, _ ] : this->covr_ ) {

      sec_rxns.push_back( sec_rxn );
  }

  if ( std::find( sec_rxns.begin(), sec_rxns.end(), sec_rxn ) == sec_rxns.end() ) {

    Log::error( "The requested secondary reaction is out of range.");

    std::ostringstream out;
    out << "Present secondary reactions are: ";
    for ( std::size_t i = 0; i < sec_rxns.size(); ++i ) {

      out << std::to_string( sec_rxns[i] );
      if ( i != sec_rxns.size() - 1 ) {

        out << ", ";
      }
    }
    Log::info( out.str() );
    throw std::exception();
  }
}