protected:
Unresolved( double EL, double EH, int NAPS,
            const CONT& cont )
  try:
    ape( std::nullopt ),
    el( EL ),
    eh( EH ),
    naps( NAPS ),
    spi( cont.C1() ),
    ap( cont.C2() ),
    lssf( cont.L1() ){
  } catch ( std::exception& e ){
    Log::info( "Trouble encountered while creating Unresolved instance." );
    throw e;
  }

Unresolved( double EL, double EH, int NAPS,
            TAB1&& APE, const CONT& cont )
  try:
    ape( std::move( APE ) ),
    el( EL ),
    eh( EH ),
    naps( NAPS ),
    spi( cont.C1() ),
    ap( cont.C2() ),
    lssf( cont.L1() ){
  } catch ( std::exception& e ){
    Log::info( "Trouble encountered while creating Unresolved instance." );
    throw e;
  }

Unresolved( const Base& base,
            std::optional<TAB1>&& APE,
            const CONT& cont )
  try:
    ape( std::move( APE ) ),
    el( base.EL() ),
    eh( base.EH() ),
    naps( base.NAPS() ),
    spi( cont.C1() ),
    ap( cont.C2() ),
    lssf( cont.L1() ){
  } catch ( std::exception& e ){
    Log::info( "Trouble encountered while creating Unresolved instance." );
    throw e;
  }
