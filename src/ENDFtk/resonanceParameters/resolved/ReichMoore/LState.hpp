class LState: protected BreitWigner::LState {

public:
  #include "ENDFtk/resonanceParameters/resolved/ReichMoore/LState/Resonance.hpp"

  using BreitWigner::LState::AWRI;
  using BreitWigner::LState::L;
  using BreitWigner::LState::NRS;

  using BreitWigner::LState::LState;

  using BreitWigner::LState::resonanceEnergies;
  using BreitWigner::LState::AJs;
  auto neutronWidths() const              { return stride( 2 ); }
  auto radiationWidths() const            { return stride( 3 ); }
  auto firstPartialFissionWidths() const  { return stride( 4 ); }
  auto secondPartialFissionWidths() const { return stride( 5 ); }

  double APL() const { return list.C2(); }

  auto resonances() const {
    return 
      this->list.B()
        | ranges::view::chunk(6)
        | ranges::view::transform(
            []( Chunk&& chunk ) -> Resonance
              { return Resonance( std::move( chunk ) ); }
          );
  }
};
