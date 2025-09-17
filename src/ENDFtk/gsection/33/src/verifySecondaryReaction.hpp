void verifySecondaryReaction( std::size_t sec_rxn ) const {

    std::vector< size_t > sec_rxns;
        sec_rxns.reserve( this->covr_.size() );
        for ( const auto& [sec_rxn, _ ] : this->covr_ ) {
            sec_rxns.push_back( sec_rxn );
        }

    if ( std::find( sec_rxns.begin(), sec_rxns.end(), sec_rxn ) == sec_rxns.end() ) {
        Log::error( "The requested secondary reaction is out of range.");
        using namespace njoy::tools;
        auto rxns_as_strings = sec_rxns | std20::views::transform( []( size_t rxn ) 
                                { return std::to_string( rxn ); });
        Log::info( "Present secondary reactions are: {}", fmt::join( rxns_as_strings, ", " ) );
        throw std::exception();
    } 
}