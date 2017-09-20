class Resonance: protected BreitWigner::LState::Resonance {

public:
  using BreitWigner::LState::Resonance::Resonance;

  using BreitWigner::LState::Resonance::ER;
  using BreitWigner::LState::Resonance::AJ;

  double GN() const { return this->chunk[2]; }
  double GG() const { return this->chunk[3]; }
  double GFA() const { return this->chunk[4]; }
  double GFB() const { return this->chunk[5]; }
};
