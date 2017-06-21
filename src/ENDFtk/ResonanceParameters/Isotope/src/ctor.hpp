template< typename Iterator >
Isotope( CONT& cont, 
         Iterator& it, const Iterator& end, long& lineNumber,
         int MAT, int MF, int MT ):
  ZAI( cont.C1() ),
  abundance( cont.C2() ){

  try{
    for( long ner=0; ner < cont.N1(); ++ner ){
      CONT rangeCONT( it, end, lineNumber, MAT, MF, MT );

      auto LRU{ rangeCONT.L1() };
      auto LRF{ rangeCONT.L2() };
      switch( LRU ){
        case 0:
          Log::error( "LRU=0 is not yet implemented" );
          throw std::exception();
          break;
        case 1:
          ranges.push_back( std::move(
              resolvedRange( rangeCONT, it, end, lineNumber, 
                             MAT, MF, MT ) ) );
          break;
        case 2:
          Log::error( "LRU=2 is not yet implemented" );
          throw std::exception();
          break;
        default:
          Log::error( "Encountered invalid LRU value: {}", LRU );
          throw std::exception();
      }
    }

  } catch( std::exception& e ){
    Log::info( "Encountered error while parsing Resonance Parameter 'Isotope'" );
    throw e;
  }
}
