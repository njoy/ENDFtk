class BreitWigner : public Base {
public:
  ranges::optional< TAB1 > tab1;
  CONT cont;
  LIST list;

  #include "ENDFtk/ResonanceParameters/Resolved/BreitWigner/src/ctor.hpp"

};
