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
  
  static constexpr int LRU(){ return 0; }
  static constexpr int LRF(){ return 0; }
  static constexpr int NRO(){ return 0; }
  static constexpr int NAPS(){ return 0; }
  static constexpr int NLS(){ return 0; }
  
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
    if( base.NRO() != 0 ){
      Log::error( "Illegal NRO value" );
      Log::info( "NRO must be zero for scattering-radius subsections" );
      Log::info( "NRO value: {}", base.NRO() );
      throw std::exception();
    }
    if( base.NAPS() != 0 ){
      Log::error( "Illegal NAPS value" );
      Log::info( "NAPS must be zero for scattering-radius subsections" );
      Log::info( "NAPS value: {}", base.NAPS() );
      throw std::exception();
    }
    if( cont.L1() ){
      Log::error( "Illegal L1 value" );
      Log::info( "L1 must be zero for scattering-radius subsections" );
      Log::info( "L1 value: {}", cont.L1() );
      throw std::exception();
    }
    if( cont.L2() ){
      Log::error( "Illegal L2 value" );
      Log::info( "L2 must be zero for scattering-radius subsections" );
      Log::info( "L2 value: {}", cont.L2() );
      throw std::exception();
    }
    if( cont.N1() ){
      Log::error( "Illegal N1 value" );
      Log::info( "N1 must be zero for scattering-radius subsections" );
      Log::info( "N1 value: {}", cont.N1() );
      throw std::exception();
    }
    if( cont.N2() ){
      Log::error( "Illegal N2 value" );
      Log::info( "N2 must be zero for scattering-radius subsections" );
      Log::info( "N2 value: {}", cont.N2() );
      throw std::exception();
    }
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

  long NC() const { return 2; }

  #include "ENDFtk/resonanceParameters/SpecialCase/src/print.hpp"
};
