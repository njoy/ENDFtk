class EnergyDependent {
public:
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/Jvalue.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/Lvalue.hpp"
  
protected:
  std::vector< Lvalue > lValues_;
  std::optional< TAB1 > ape;
  
  double el;
  double eh;
  int naps;
  double spi;
  double ap;
  int lssf;

public:
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/src/ctor.hpp"
  
  double EL() const { return this->el; }
  double EH() const { return this->eh; }
  int NRO() const { return bool( this->ape ); }
  int NAPS() const { return this->naps; }
  const auto& APE() const { return *(this->ape); }

  static constexpr int LRU(){ return 2; }
  static constexpr int LRF(){ return 2; }  
  
  double SPI() const { return this->spi; }
  double AP() const { return this->ap; }
  int LSSF() const { return this->lssf; }
  int NLS() const { return this->lValues_.size(); }

  auto lValues() const {
    return ranges::make_iterator_range( this->lValues_.begin(),
                                        this->lValues_.end() );
  }

  long NC() const {
    return 2
      + ( ( this->ape ) ? this->ape->NC() : 0 )
      + ranges::accumulate
        ( this->lValues_
          | ranges::view::transform
            ( []( const auto& lValue ){ return lValue.NC(); } ), 0 );
  }

  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/src/print.hpp"
};
