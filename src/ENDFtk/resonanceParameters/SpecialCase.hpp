class SpecialCase {
  double el;
  double eh;
  double spi;
  double ap;
  
public:
  double EL() const { return this->el; }
  double EH() const { return this->eh; }
  double SPI() const { return this->spi; }
  double AP() const { return this->ap; }
  
  SpecialCase( double EL, double EH, double SPI, double AP ) :
    el( EL ), eh( EH ), spi( SPI ), ap( AP ) {
    try{
      Base{ this->EL(), this->EH(), 0, 0, 0, 0 };
    } catch (int) {
      throw std::exception();
    }
  }

protected:
  SpecialCase( const Base& base, const CONT& cont ) :
    el( base.EL() ), eh( base.EH() ), spi( cont.C1() ), ap( cont.C2() ){
    assert( base.LRU() == 0 );
    assert( base.LRF() == 0 );
  }
  
public:
  template< typename Iterator >
  SpecialCase( const Base& base,
               Iterator& it, const Iterator& end, long& lineNumber,
               int MAT, int MF, int MT )
    try:
      SpecialCase( base, CONT( it, end, lineNumber, MAT, MF, MT ) ){
      } catch( std::exception& e ){
      Log::info( "Encountered error while reading scattering-radius"
                 " resonance parameter subsections" );
      throw e;
    }
};
