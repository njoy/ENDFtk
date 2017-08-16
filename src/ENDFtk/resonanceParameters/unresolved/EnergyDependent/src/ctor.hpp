private:
template< typename Iterator >
EnergyDependent( const Base& base,
                 std::optional<TAB1>&& APE,
                 const CONT& cont,
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) 
  try:
    Unresolved( base, std::move( APE ), cont,
                readLStates( cont.N1(), it, end, lineNumber, MAT, MF, MT ) ){
  } catch( std::exception& e ){
    Log::info( "Trouble encountered when parsing energy-dependent unresolved "
               "resonances." );
    throw e;
  }
  
template< typename Iterator >
EnergyDependent( const Base& base,
                 std::optional<TAB1>&& APE,
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) :
  EnergyDependent( base, 
                   std::move( APE ),
                   CONT( it, end, lineNumber, MAT, MF, MT ),
                   it, end, lineNumber, 
                   MAT, MF, MT ){}

public:  
template< typename Iterator >
EnergyDependent( const Base& base, 
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) :
  EnergyDependent( base, 
                   readAPE( base, it, end, lineNumber, MAT, MF, MT ),
                   it, end, lineNumber, MAT, MF, MT ) {}
