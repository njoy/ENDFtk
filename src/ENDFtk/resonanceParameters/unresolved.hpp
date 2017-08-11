namespace unresolved {

#include "ENDFtk/resonanceParameters/unresolved/LState.hpp"

class Unresolved{
protected:
  std::vector< LState > lists;
  std::optional< TAB1 > ape;
  double el;
  double eh;
  int naps;
  double spi;
  double ap;
  int lssf;

#include "ENDFtk/resonanceParameters/unresolved/src/ctor.hpp"
#include "ENDFtk/resonanceParameters/unresolved/src/readLStates.hpp"

public:
#include "ENDFtk/resonanceParameters/unresolved/src/readAPE.hpp"

  double EL() const { return this->el; }
  double EH() const { return this->eh; }
  int NRO() const { return bool(this->ape); }
  int NAPS() const { return this->naps; }
  
  const auto& APE() const { return *(this->ape); }

  double SPI() const { return this->spi; }
  double AP() const { return this->ap; }
  int LSSF() const { return this->lssf; }
  int NLS() const { return this->lists.size(); }

  auto LISTS() const {
    return ranges::make_iterator_range( this->lists.begin(), this->lists.end() );
  }
};

#include "ENDFtk/resonanceParameters/unresolved/EnergyDependent.hpp"
#include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths.hpp"
#include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent.hpp"

}
