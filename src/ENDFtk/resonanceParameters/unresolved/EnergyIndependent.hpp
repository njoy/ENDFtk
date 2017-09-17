class EnergyIndependent {
public:
  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/Jvalue.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/Lvalue.hpp"
  
protected:
  std::vector< LIST > lists;
  std::optional< TAB1 > ape;
  double el;
  double eh;
  int naps;
  double spi;
  double ap;
  int lssf;
  
public:
  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/src/ctor.hpp"
  
  double EL() const { return this->el; }
  double EH() const { return this->eh; }
  int NRO() const { return bool( this->ape ); }
  int NAPS() const { return this->naps; }

  static constexpr int LRU(){ return 2; }
  static constexpr int LRF(){ return 1; }
  
  const auto& APE() const { return *(this->ape); }

  double SPI() const { return this->spi; }
  double AP() const { return this->ap; }
  int LSSF() const { return this->lssf; }
  int NLS() const { return this->lists.size(); }

  auto lValues() const {
    return
      this->lists
      | ranges::view::transform
        ( []( const auto& list ){ return Lvalue( list ); } );
  }

  int NC() const {
    return 2
      + ( ( this->ape ) ? this->ape->NC() : 0 )
      + ranges::accumulate
        ( this->lists
          | ranges::view::transform
            ( []( const auto& list ){ return list.NC(); } ), 0 );
  }

  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/src/print.hpp"
};
