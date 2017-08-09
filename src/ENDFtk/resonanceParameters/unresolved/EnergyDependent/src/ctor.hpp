protected:
EnergyDependent( double EL, double EH, int NAPS,
                 double SPI, double AP,
                 const CONT& cont,
                 std::vector< caseCTuple >&& lists ) :
  lists( std::move(lists) ),
  ape( std::nullopt ),
  el( EL ),
  eh( EH ),
  naps( NAPS ),
  spi( SPI ),
  ap( AP ),
  lssf( cont.L1() ){}

EnergyDependent( double EL, double EH, int NAPS,
                 TAB1&& APE, double SPI, 
                 const CONT& cont,
                 std::vector< caseCTuple >&& lists ) :
  lists( std::move(lists) ),
  ape( std::move(APE) ),
  el( EL ),
  eh( EH ),
  naps( NAPS ),
  spi( SPI ),
  ap( 0.0 ),
  lssf( cont.L1() ){}

EnergyDependent( const Base& base,
                 std::optional<TAB1>&& APE,
                 const CONT& cont,
                 std::vector< caseCTuple >&& lists ) :
  lists( std::move(lists) ),
  ape( std::move(APE) ),
  el( base.EL() ),
  eh( base.EH() ),
  naps( base.NAPS() ),
  spi( cont.C1() ),
  ap( cont.C2() ),
  lssf( cont.L1() ){}

private:
template< typename Iterator >
EnergyDependent( const Base& base,
                 std::optional<TAB1>&& APE,
                 const CONT& cont,
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) :
  EnergyDependent( base, std::move( APE ), cont,
                   readLists( cont, it, end, lineNumber, MAT, MF, MT ) ){}
  
template< typename Iterator >
EnergyDependent( const Base& base,
                 std::optional<TAB1>&& APE,
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) :
  EnergyDependent( base, std::move( APE ),
                   CONT( it, end, lineNumber, MAT, MF, MT ),
                   it, end, lineNumber, MAT, MF, MT ){}

protected:  
template< typename Iterator >
EnergyDependent( const Base& base, 
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) :
  EnergyDependent( base, 
                   readAPE( base, it, end, lineNumber, MAT, MF, MT ),
                   it, end, lineNumber, MAT, MF, MT ) {}

