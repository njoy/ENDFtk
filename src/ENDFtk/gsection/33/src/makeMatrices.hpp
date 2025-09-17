static auto
makeMatrices( const std::vector< std::pair< size_t, std::vector< DataRecord > > > records,
              int ngroups ) {
    
    std::map< size_t, 
        std::vector< std::vector< double > > > covr_matrices;
    size_t sec_mt;
    size_t pri_mt;

    if ( records.size() != 0 ) {
    
        for ( const auto& matrix : records ) {

            size_t sec_mt = matrix.first;
            covr_matrices[ sec_mt ]  = std::vector< std::vector< double > >
                                       ( ngroups , std::vector< double >( ngroups, 0.0 ) );
            
            if ( matrix.second.size() != 0 ) {
                for ( const auto& record : matrix.second ) {

                    auto g_i = ( record.IG() - 1 );
                    for ( size_t g_o = record.IG2LO() - 1;
                          g_o <= ( record.IG2LO() + record.NW() - 1 ); ++g_o ) {
                        
                        covr_matrices[ sec_mt ][g_i][g_o] = record.list()[ g_o ];
                    } // outgoing energy
                } // records
            } // endif

            else {
                covr_matrices[ sec_mt ] = std::vector< std::vector< double > > {};
            }

        } // matrix

    } //endif

    else {
        throw std::runtime_error( "Vector of DataRecords is empty!" );
    }

    return covr_matrices;
}