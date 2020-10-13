class IsotropicDiscreteEmission : protected NoLawDataGiven {

public:

  /* methods */
  static constexpr int LAW() { return 3; }

  using NoLawDataGiven::NC;
  using NoLawDataGiven::print;
};
