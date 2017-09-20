class BreitWigner {
protected:
  std::vector< LIST > lists;
  std::optional< TAB1 > ape;
  double el;
  double eh;
  int naps;
  double spi;
  double ap;
  
#include "ENDFtk/resonanceParameters/resolved/BreitWigner/src/validate.hpp"
#include "ENDFtk/resonanceParameters/resolved/BreitWigner/src/ctor.hpp"

public:
  #include "ENDFtk/resonanceParameters/resolved/BreitWigner/Lvalue.hpp"
  
  double EL() const { return this->el; }
  double EH() const { return this->eh; }
  int NRO() const { return bool(this->ape); }
  int NAPS() const { return this->naps; }

  static constexpr int LRU() { return 1; }
  
  const auto& APE() const { return *(this->ape); }

  double SPI() const { return this->spi; }
  double AP() const { return this->ap; }
  int NLS() const { return this->lists.size(); }

  auto LISTS() const {
    return ranges::make_iterator_range( this->lists.begin(), this->lists.end() );
  }

  auto lValues() const {
    return
      this->LISTS()
      | ranges::view::transform
        ( []( const auto& list ) -> Lvalue { return { list }; } );
  }

  long NC() const {
    return 2
      + ( ( this->ape ) ? this->ape->NC() : 0 )
      + ranges::accumulate
        ( this->lists
          | ranges::view::transform
            ( []( const auto& list ){ return list.NC(); } ), 0 );
  }

  #include "ENDFtk/resonanceParameters/resolved/BreitWigner/src/print.hpp"

};
