class LState : protected BreitWigner::LState {
protected:
  using Chunk = BreitWigner::LState::Chunk;
  
public:
  #include "ENDFtk/resonanceParameters/resolved/ReichMoore/LState/Resonance.hpp"

  using BreitWigner::LState::LState;
  using BreitWigner::LState::AWRI;
  using BreitWigner::LState::L;
  using BreitWigner::LState::LRX;
  double APL() const { return BreitWigner::LState::list.C2(); }

  auto resonances() const {
    return
      this->list.B()
      | ranges::view::chunk(6)
      | ranges::view::transform
        ( []( Chunk&& chunk ) -> Resonance
          { return { std::move(chunk) }; } );
  }
};
