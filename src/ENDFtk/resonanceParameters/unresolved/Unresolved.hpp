class Unresolved{

public:
#include "ENDFtk/resonanceParameters/unresolved/Unresolved/LState.hpp"

protected:
  std::optional< TAB1 > ape;
  double el;
  double eh;
  int naps;
  double spi;
  double ap;
  int lssf;

#include "ENDFtk/resonanceParameters/unresolved/Unresolved/src/ctor.hpp"

public:
#include "ENDFtk/resonanceParameters/unresolved/Unresolved/src/readAPE.hpp"

  double EL() const { return this->el; }
  double EH() const { return this->eh; }
  int NRO() const { return bool(this->ape); }
  int NAPS() const { return this->naps; }
  
  const auto& APE() const { return *(this->ape); }

  double SPI() const { return this->spi; }
  double AP() const { return this->ap; }
  int LSSF() const { return this->lssf; }

};

