class LState: protected BreitWigner::LState {

public:
  using BreitWigner::LState::AWRI;
  using BreitWigner::LState::L;
  using BreitWigner::LState::LRX;

  using BreitWigner::LState::LState;

  using BreitWigner::LState::resonanceEnergies;
  using BreitWigner::LState::AJ;

  auto neutronWidth() const              { return stride( 2 ); }
  auto radiationWidth() const            { return stride( 3 ); }
  auto firstPartialFissionWidth() const  { return stride( 4 ); }
  auto secondPartialFissionWidth() const { return stride( 5 ); }

};
