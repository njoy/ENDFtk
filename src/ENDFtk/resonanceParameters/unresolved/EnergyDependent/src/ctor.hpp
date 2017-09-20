protected:
EnergyDependent( double EL, double EH, int NAPS,
                 std::optional< TAB1 >&& APE,
                 double SPI, double AP, int LSSF,
                 std::vector< Lvalue >&& lValues ) :
  lValues_( std::move(lValues) ),
  ape( std::move(APE) ),
  el( EL ), eh( EH ), naps( NAPS ),
  spi( SPI ), ap( AP ), lssf( LSSF ) {}

public:
EnergyDependent( double EL, double EH, int NAPS,
                 TAB1&& APE,
                 double SPI, double AP, int LSSF,
                 std::vector< Lvalue >&& lValues ) :
  EnergyDependent( EL, EH, NAPS,
                   std::optional< TAB1 >( std::move(APE) ),
                   SPI, AP, LSSF,
                   std::move(lValues) ){}

EnergyDependent( double EL, double EH, int NAPS,
                 double SPI, double AP, int LSSF,
                 std::vector< Lvalue >&& lValues ) :
  EnergyDependent( EL, EH, NAPS,
                   std::nullopt,
                   SPI, AP, LSSF,
                   std::move(lValues) ){}

protected:
template< typename Iterator >
EnergyDependent( const Base& base,
                 std::optional<TAB1>&& APE,
                 const CONT& cont,
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) :
    EnergyDependent( base.EL(), base.EH(), base.NAPS(),
                     std::move( APE ),
                     cont.C1(), cont.C2(), cont.L1(),
                     read<Lvalue>( cont.N1(),
                                   it, end, lineNumber, MAT, MF, MT ) ){}
  
template< typename Iterator >
EnergyDependent( const Base& base,
                 std::optional<TAB1>&& APE,
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) :
  EnergyDependent( base, 
                   std::move( APE ),
                   CONT( it, end, lineNumber, MAT, MF, MT ),
                   it, end, lineNumber, MAT, MF, MT ){}

public:  
template< typename Iterator >
EnergyDependent( const Base& base, 
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT )
  try:
    EnergyDependent( base, 
                     readAPE( base, it, end, lineNumber, MAT, MF, MT ),
                     it, end, lineNumber, MAT, MF, MT ) {
  } catch( std::exception& e ) {
    Log::info( "Trouble encountered when parsing energy-dependent unresolved "
               "resonances (Case C)." );
    throw e;
  }
