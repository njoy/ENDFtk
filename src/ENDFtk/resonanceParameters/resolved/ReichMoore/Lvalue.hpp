class Lvalue : protected BreitWigner::Lvalue {
protected:
  using Chunk = BreitWigner::Lvalue::Chunk;
  
public:
  #include "ENDFtk/resonanceParameters/resolved/ReichMoore/Lvalue/Resonance.hpp"

  using BreitWigner::Lvalue::Lvalue;
  using BreitWigner::Lvalue::AWRI;
  using BreitWigner::Lvalue::L;
  using BreitWigner::Lvalue::LRX;
  double APL() const { return BreitWigner::Lvalue::list.C2(); }

  auto resonances() const {
    return
      this->list.B()
      | ranges::view::chunk(6)
      | ranges::view::transform
        ( []( Chunk&& chunk ) -> Resonance
          { return { std::move(chunk) }; } );
  }
};
