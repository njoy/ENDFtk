class EnergyDependent : public Unresolved {
public:
#include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/src/ctor.hpp"
#include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/LState.hpp"
#include "ENDFtk/resonanceParameters/unresolved/Unresolved/src/readLStates.hpp"

protected:
  std::vector< LState > lStates;

public:
  int NLS() const { return this->lStates.size(); }

  auto LStates() const {
    return ranges::make_iterator_range( this->lStates.begin(), 
                                        this->lStates.end() );
  }
};
