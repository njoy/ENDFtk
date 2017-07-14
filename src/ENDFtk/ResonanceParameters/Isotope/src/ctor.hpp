protected:
template< typename Iterator >
Isotope( const CONT& cont, 
         Iterator& it, const Iterator& end, long& lineNumber,
         int MAT, int MF, int MT ) :
  zai( cont.C1() ),
  abn( cont.C2() ),
  lfw( cont.L2() ),
  ranges( readRanges( cont.N1(), it, end, lineNumber, MAT, MF, MT  ) ) {}

public:
template< typename Iterator >
Isotope( Iterator& it, const Iterator& end, long& lineNumber,
         int MAT, int MF, int MT )
  try:
    Isotope( CONT( it, end, lineNumber, MAT, MF, MT ),
             it, end, lineNumber, MAT, MF, MT ){
  } catch( std::exception& e ){
    Log::info( "Encountered error while parsing resonance parameter Isotope" );
    throw e;
  }
  
  
Isotope( double ZAI, double ABN, int LFW, std::vector< EnergyRange >&& ranges ):
  zai(ZAI), abn(ABN), lfw(LFW), ranges( std::move(ranges) ){}
