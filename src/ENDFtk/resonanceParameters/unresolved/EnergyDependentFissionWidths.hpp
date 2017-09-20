class EnergyDependentFissionWidths : public Unresolved {
protected:
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/ctor.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/Unresolved/src/readLStates.hpp"

  std::vector< LState > lStates;
  LIST list;

public:

  double NE() const { return this->list.NPL(); }
  const LIST& energyLIST() const { return this->list; }

  int NLS() const { return this->lStates.size(); }

  auto LStates() const {
    return ranges::make_iterator_range( this->lStates.begin(), 
                                        this->lStates.end() );
  }
};
