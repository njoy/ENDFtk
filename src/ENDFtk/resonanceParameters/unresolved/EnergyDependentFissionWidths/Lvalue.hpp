class Lvalue {
protected:
  std::vector< LIST > lists;
  double awri;
  int l;
  
public:
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/Lvalue/src/ctor.hpp"
  
  double AWRI() const { return this->awri; }
  int L() const { return this->l; }
  int NJS() const { return this->lists.size(); }

  auto jValues() const {
    return
      this->lists
      | ranges::view::transform( 
          []( const auto& list ){ return Jvalue( list ); } );
  }

  long NC() const {
    return 1
      + ranges::accumulate( 
          this->lists
            | ranges::view::transform( 
                []( const auto& list ){ return list.NC(); } ), 0 );
  }

  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/Lvalue/src/print.hpp"
};
