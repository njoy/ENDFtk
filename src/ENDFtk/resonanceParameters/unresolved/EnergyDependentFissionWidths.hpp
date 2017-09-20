class EnergyDependentFissionWidths {
public:
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/Jvalue.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/Lvalue.hpp"
  
protected:
  std::vector< Lvalue > lValues_;
  std::optional< TAB1 > ape; 
  LIST list;
  double el;
  double eh;
  int naps;

public:
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/ctor.hpp"
  
  double EL() const { return this->el; }
  double EH() const { return this->eh; }
  int NRO() const { return bool(this->ape); }
  int NAPS() const { return this->naps; }

  const auto& APE() const { return *(this->ape); }
  
  int NE() const { return this->list.NPL(); }
  double SPI() const { return this->list.C1(); }
  double AP() const { return this->list.C2(); }
  int LSSF() const { return this->list.L1(); }
  int NLS() const { return this->lValues_.size(); }

  static constexpr int LRU(){ return 2; }
  static constexpr int LRF(){ return 1; }

  auto ES() const { return this->list.B(); }

  auto lValues() const {
    return
      ranges::make_iterator_range( this->lValues_.begin(), this->lValues_.end() );
  }
  
  long NC() const {
    return 1
      + ( ( this->ape ) ? this->ape->NC() : 0 )
      + this->list.NC()
      + ranges::accumulate
        ( this->lValues_
          | ranges::view::transform
            ( []( const auto& lValue ){ return lValue.NC(); } ), 0 );
  }

  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/print.hpp"
};

