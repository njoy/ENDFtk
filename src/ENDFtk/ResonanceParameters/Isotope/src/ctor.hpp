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
      switch( LRU ){
        case 0: {
          CONT cont( it, end, lineNumber, MAT, MF, MT );
          ranges.push_back( 
              SpecialCase( rangeCONT.C1(), rangeCONT.C2(),
                           cont.C1(), cont.C2(), cont.N1() ) );
          break;
        }
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
