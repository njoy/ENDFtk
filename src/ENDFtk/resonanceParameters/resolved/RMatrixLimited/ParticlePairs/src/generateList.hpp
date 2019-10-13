static std::vector< double >
generateList( std::vector< double >&& ma, std::vector< double >&& mb,
              std::vector< double >&& za, std::vector< double >&& zb,
              std::vector< double >&& ia, std::vector< double >&& ib,
              std::vector< double >&& q, std::vector< int >&& pnt,
              std::vector< int >&& shf, std::vector< int >&& mt,
              std::vector< double >&& pa, std::vector< double >&& pb ) {

  unsigned int npp = ma.size();
  if ( ( mb.size() != npp ) or ( za.size() != npp ) or ( zb.size() != npp ) or
       ( ia.size() != npp ) or ( ib.size() != npp ) or
       ( q.size() != npp ) or ( pnt.size() != npp ) or
       ( shf.size() != npp ) or ( mt.size() != npp ) or
       ( pa.size() != npp ) or ( pb.size() != npp ) ) {

    Log::info( "The number of particle pairs and the particle pair is not "
               "consistent" );
    Log::info( "NPP value: {}", npp );
    Log::info( "ma.size(): {}", ma.size() );
    Log::info( "mb.size(): {}", mb.size() );
    Log::info( "za.size(): {}", za.size() );
    Log::info( "zb.size(): {}", zb.size() );
    Log::info( "ia.size(): {}", ia.size() );
    Log::info( "ib.size(): {}", ib.size() );
    Log::info( "q.size(): {}", q.size() );
    Log::info( "pnt.size(): {}", pnt.size() );
    Log::info( "shf.size(): {}", shf.size() );
    Log::info( "mt.size(): {}", mt.size() );
    Log::info( "pa.size(): {}", pa.size() );
    Log::info( "pb.size(): {}", pb.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < npp; ++i ) {

    list.push_back( ma[i] );
    list.push_back( mb[i] );
    list.push_back( za[i] );
    list.push_back( zb[i] );
    list.push_back( ia[i] );
    list.push_back( ib[i] );
    list.push_back( q[i] );
    list.push_back( pnt[i] );
    list.push_back( shf[i] );
    list.push_back( mt[i] );
    list.push_back( pa[i] );
    list.push_back( pb[i] );
  }
  return list;
}
