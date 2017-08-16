private:
template< typename Iterator >
EnergyDependentFissionWidths( const Base& base,
                              std::optional<TAB1>&& APE,
                              const LIST&& list,
                              Iterator& it, const Iterator& end, long& lineNumber,
                              int MAT, int MF, int MT ) 
  try:
    Unresolved( base, std::move( APE ),
                CONT( list.C1(), list.C2(), 
                      list.L1(), list.L2(), 
                      list.NPL(), list.N2() ),
                readLStates( list.N2(), it, end, lineNumber, MAT, MF, MT ) ),
    list( std::move( list ) ){
  } catch( std::exception& e ){
    Log::info( "Trouble encountered when parsing energy-dependent fission "
               "width unresolved resonances." );
    throw e;
  }

template< typename Iterator >
EnergyDependentFissionWidths( const Base& base,
                              std::optional<TAB1>&& APE,
                              Iterator& it, const Iterator& end, long& lineNumber,
                              int MAT, int MF, int MT ) :
  EnergyDependentFissionWidths( base, 
                                std::move( APE ),
                                LIST( it, end, lineNumber, MAT, MF, MT ),
                                it, end, lineNumber, 
                                MAT, MF, MT ){}

public:  
template< typename Iterator >
EnergyDependentFissionWidths( const Base& base, 
                              Iterator& it, const Iterator& end, long& lineNumber,
                              int MAT, int MF, int MT ) :
  EnergyDependentFissionWidths( base, 
                                readAPE( base, it, end, lineNumber, MAT, MF, MT ),
                                it, end, lineNumber, MAT, MF, MT ) {}
