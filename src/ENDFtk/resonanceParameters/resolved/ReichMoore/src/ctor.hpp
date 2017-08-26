public:
ReichMoore( double EL, double EH, int NAPS,
            double SPI, double AP, int LAD, int NLSC,
            std::vector< LIST >&& lists )
  try:
    BreitWigner( EL, EH, NAPS, SPI, AP, std::move(lists) ),
    lad( LAD ), nlsc( NLSC ) {
      this->validate();
  } catch( std::exception& e ) {
    Log::info( "Encountered error while constructing"
               " Reich-Moore resonance parameter subsection" );
    throw e;
  }
  
ReichMoore( double EL, double EH, int NAPS,
            TAB1&& APE, double SPI, int LAD, int NLSC,
            std::vector< LIST >&& lists )
  try:
    BreitWigner( EL, EH, NAPS, std::move(APE), SPI, std::move(lists) ),
    lad( LAD ), nlsc( NLSC ) {
      this->validate();
  } catch( std::exception& e ) {
      Log::info( "Encountered error while constructing"
                 " Reich-Moore resonance parameter subsection" );
      throw e;
  }

protected:
ReichMoore( const Base& base,
            std::optional<TAB1>&& APE,
            const CONT& cont,
            std::vector< LIST >&& lists ) :
  BreitWigner( base, std::move(APE), cont, std::move(lists) ),
  lad( cont.L1() ),
  nlsc( cont.N2() ){}

template< typename Iterator >
ReichMoore( const Base& base,
            std::optional<TAB1>&& APE,
            const CONT& cont,
            Iterator& it, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT ) :
  ReichMoore( base, std::move( APE ), cont, 
              readLists( cont, it, end, lineNumber, MAT, MF, MT ) ){}
  
template< typename Iterator >
ReichMoore( const Base& base,
            std::optional<TAB1>&& APE,
            Iterator& it, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT ) :
  ReichMoore( base, std::move( APE ),
              CONT( it, end, lineNumber, MAT, MF, MT ),
              it, end, lineNumber, MAT, MF, MT ){}

public:  
template< typename Iterator >
ReichMoore( const Base& base, 
            Iterator& it, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT )
  try:
    ReichMoore( base, 
                BreitWigner::readAPE( base, it, end, lineNumber, MAT, MF, MT ),
                it, end, lineNumber, MAT, MF, MT ) {
    this->validate();
  } catch( std::exception& e ) {
    Log::info( "Encountered error while constructing"
               " Reich-Moore resonance parameter subsection" );
    throw e;
  }
