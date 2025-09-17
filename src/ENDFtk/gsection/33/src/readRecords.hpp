template< typename Iterator >
static auto readRecords( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT, int num_matrices ) {

    std::vector< std::pair< size_t, std::vector< DataRecord > > > records;
    int ngn;
    for ( int m = 0; m < num_matrices; ++m ) {
        
        ControlRecord cont( it, end, lineNumber, MAT, MF, MT );
        size_t sec_rxn = cont.L2();
        records.emplace_back( sec_rxn, std::vector< DataRecord >{} );
        ngn = cont.N2();

        do {
            records.back().second.emplace_back( it, end, lineNumber, MAT, MF, MT );
        }
        while ( records.back().second.back().IG() < ngn ); 

    }

   return std::make_tuple( ngn, records );
}