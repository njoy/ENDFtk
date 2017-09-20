protected:
BreitWigner( double EL, double EH, int NAPS,
             double SPI, double AP,
             std::vector< LIST >&& lists ) :
  lists( std::move(lists) ),
  ape( std::nullopt ),
  el( EL ),
  eh( EH ),
  naps( NAPS ),
  spi( SPI ),
  ap( AP ){ this->validate(); }

BreitWigner( double EL, double EH, int NAPS,
             TAB1&& APE, double SPI,
             std::vector< LIST >&& lists ) :
  lists( std::move(lists) ),
  ape( std::move(APE) ),
  el( EL ),
  eh( EH ),
  naps( NAPS ),
  spi( SPI ),
  ap( 0.0 ){ this->validate(); }

BreitWigner( const Base& base,
             std::optional<TAB1>&& APE,
             const CONT& cont,
             std::vector< LIST >&& lists ) :
  lists( std::move(lists) ),
  ape( std::move(APE) ),
  el( base.EL() ),
  eh( base.EH() ),
  naps( base.NAPS() ),
  spi( cont.C1() ),
  ap( cont.C2() ){}

private:
template< typename Iterator >
BreitWigner( const Base& base,
             std::optional<TAB1>&& APE,
             const CONT& cont,
             Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT ) :
  BreitWigner( base, std::move( APE ), cont, 
               readLISTs( cont, it, end, lineNumber, MAT, MF, MT ) ){}
  
template< typename Iterator >
BreitWigner( const Base& base,
             std::optional<TAB1>&& APE,
             Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT ) :
  BreitWigner( base, std::move( APE ),
               CONT( it, end, lineNumber, MAT, MF, MT ),
               it, end, lineNumber, MAT, MF, MT ){}

protected:  
template< typename Iterator >
BreitWigner( const Base& base, 
             Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT ) :
  BreitWigner( base, 
               readAPE( base, it, end, lineNumber, MAT, MF, MT ),
               it, end, lineNumber, MAT, MF, MT ) {}
