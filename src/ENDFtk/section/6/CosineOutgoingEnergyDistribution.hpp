class CosineOutgoingEnergyDistribution : protected TabulationRecord {

public:
  /* constructor */
  using TabulationRecord::TabulationRecord;

  /* get methods */
  long NRP() const { return TabulationRecord::NR(); }
  long NEP() const { return TabulationRecord::NP(); }

  double cosine() const { return TabulationRecord::C2(); }

  auto energy() const { return TabulationRecord::x(); }
  auto distribution() const { return TabulationRecord::y(); }

  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;

  using TabulationRecord::NC;
  using TabulationRecord::print;
};
