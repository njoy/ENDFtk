class IsotropicDiscreteEmission : protected NoLawDataGiven {

public:

  /* get methods */
  static constexpr int LAW() { return 3; }

  using NoLawDataGiven::NC;
  using NoLawDataGiven::print;
};
