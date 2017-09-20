class Base : protected CONT {
public:
  auto EL() const { return CONT::C1(); }
  auto EH() const { return CONT::C2(); }
  auto LRU() const { return CONT::L1(); }
  auto LRF() const { return CONT::L2(); }
  auto NRO() const { return CONT::N1(); }
  auto NAPS() const { return CONT::N2(); }

  using CONT::NC;
  using CONT::print;
  
  #include "ENDFtk/resonanceParameters/Base/src/ctor.hpp"
};
