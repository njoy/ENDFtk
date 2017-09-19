protected:
EnergyDependentFissionWidths( double EL, double EH, int NAPS,
                              std::optional<TAB1>&& APE,
                              LIST&& list,
                              std::vector< Lvalue >&& lValues ) :
  lValues_( std::move(lValues) ),
  ape( std::move(APE) ),
  list( std::move(list) ),
  el( EL ), eh( EH ), naps( NAPS ){}

public:
EnergyDependentFissionWidths( double EL, double EH, int NAPS,
                              LIST&& list,
                              std::vector< Lvalue >&& lValues ) :
  EnergyDependentFissionWidths( EL, EH, NAPS, std::nullopt,
                                std::move(list),
                                std::move(lValues) ){}

EnergyDependentFissionWidths( double EL, double EH, int NAPS,
                              TAB1&& APE,
                              LIST&& list,
                              std::vector< Lvalue >&& lValues ) :
  EnergyDependentFissionWidths( EL, EH, NAPS,
                                std::optional<TAB1>( std::move(APE) ),
                                std::move(list),
                                std::move(lValues) ){}

protected:
template< typename Iterator >
EnergyDependentFissionWidths( const Base& base,
                              std::optional<TAB1>&& APE,
                              LIST&& list,
                              Iterator& it, const Iterator& end,
                              long& lineNumber,
                              int MAT, int MF, int MT ) :
  EnergyDependentFissionWidths( base.EL(),
                                base.EH(),
                                base.NAPS(),
                                std::move( APE ),
                                std::move( list ),
                                read<Lvalue>( list.N2(),
                                              it, end, lineNumber,
                                              MAT, MF, MT ) ){} 

template< typename Iterator >
EnergyDependentFissionWidths( const Base& base,
                              std::optional<TAB1>&& APE,
                              Iterator& it, const Iterator& end,
                              long& lineNumber,
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
                              int MAT, int MF, int MT )
  try : 
    EnergyDependentFissionWidths( base, 
                                  readAPE( base, it, end, lineNumber, MAT, MF, MT ),
                                  it, end, lineNumber, MAT, MF, MT ) {
  } catch( std::exception& e ) {
    Log::info( "Trouble encountered when parsing energy-dependent fission "
               "width unresolved resonances (Case B)." );
    throw e;
  }
