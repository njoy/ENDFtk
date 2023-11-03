static std::vector< double >
generateList( std::vector< double >&& energies,
              std::vector< double >&& spins,
              std::vector< double >&& gt,
              std::vector< double >&& gn,
              std::vector< double >&& gg,
              std::vector< double >&& gf,
              std::vector< double >&& de2,
              std::vector< double >&& dn2,
              std::vector< double >&& dndg,
              std::vector< double >&& dg2,
              std::vector< double >&& dndf,
              std::vector< double >&& dgdf,
              std::vector< double >&& df2,
              std::vector< double >&& djdn,
              std::vector< double >&& djdg,
              std::vector< double >&& djdf,
              std::vector< double >&& dj2 ) {

  unsigned int nrs = energies.size();
  if ( ( spins.size() != nrs ) or ( gt.size() != nrs ) or
       ( gn.size() != nrs ) or ( gg.size() != nrs ) or ( gf.size() != nrs ) or
       ( de2.size() != nrs ) or ( dn2.size() != nrs ) or
       ( dndg.size() != nrs ) or ( dg2.size() != nrs ) or
       ( dndf.size() != nrs ) or ( dgdf.size() != nrs ) or
       ( df2.size() != nrs ) or ( djdn.size() != nrs ) or
       ( djdg.size() != nrs ) or ( djdn.size() != nrs ) or
       ( dj2.size() != nrs ) ) {

    Log::info( "The number of resonances and the resonance parameters are not "
               "consistent" );
    Log::info( "NRS value: {}", nrs );
    Log::info( "energies.size(): {}", energies.size() );
    Log::info( "spins.size(): {}", spins.size() );
    Log::info( "gt.size(): {}", gt.size() );
    Log::info( "gn.size(): {}", gn.size() );
    Log::info( "gg.size(): {}", gg.size() );
    Log::info( "gf.size(): {}", gf.size() );
    Log::info( "de2.size(): {}", de2.size() );
    Log::info( "dn2.size(): {}", dn2.size() );
    Log::info( "dndg.size(): {}", dndg.size() );
    Log::info( "dg2.size(): {}", dg2.size() );
    Log::info( "dndf.size(): {}", dndf.size() );
    Log::info( "dgdf.size(): {}", dgdf.size() );
    Log::info( "df2.size(): {}", df2.size() );
    Log::info( "djdn.size(): {}", djdn.size() );
    Log::info( "djdg.size(): {}", djdg.size() );
    Log::info( "djdf.size(): {}", djdf.size() );
    Log::info( "dj2.size(): {}", dj2.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < nrs; ++i ) {

    list.push_back( energies[i] );
    list.push_back( spins[i] );
    list.push_back( gt[i] );
    list.push_back( gn[i] );
    list.push_back( gg[i] );
    list.push_back( gf[i] );
    list.push_back( de2[i] );
    list.push_back( dn2[i] );
    list.push_back( dndg[i] );
    list.push_back( dg2[i] );
    list.push_back( dndf[i] );
    list.push_back( dgdf[i] );
    list.push_back( df2[i] );
    list.push_back( djdn[i] );
    list.push_back( djdg[i] );
    list.push_back( djdf[i] );
    list.push_back( dj2[i] );
    list.push_back( 0. );
  }
  return list;
}
