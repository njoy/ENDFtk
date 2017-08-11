private:
template< typename Iterator >
EnergyIndependent( const Base& base,
                   std::optional<TAB1>&& APE,
                   const CONT& cont,
                   Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT ) 
  try:
    lists( readLISTs( cont.N1(), it, end, lineNumber, MAT, MF, MT ) ),
    ape( std::move( APE ) ),
    el( base.EL() ),
    eh( base.EH() ),
    naps( base.NAPS() ),
    spi( cont.C1() ),
    ap( cont.C2() ),
    lssf( cont.L1() ){
  } catch( std::exception& e ){
    Log::info( "Trouble encountered when parsing energy-independent unresolved "
               "resonances." );
    throw e;
  }

template< typename Iterator >
EnergyIndependent( const Base& base,
                   std::optional<TAB1>&& APE,
                   Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT ) :
  EnergyIndependent( base, 
                     std::move( APE ),
                     CONT( it, end, lineNumber, MAT, MF, MT ),
                     it, end, lineNumber, MAT, MF, MT ){}

public:  
template< typename Iterator >
EnergyIndependent( const Base& base, 
                   Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT ) :
  EnergyIndependent( base, 
                     unresolved::Unresolved::readAPE( base, it, end, lineNumber, MAT, MF, MT ),
                     it, end, lineNumber, MAT, MF, MT ) {}
