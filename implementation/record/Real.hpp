struct ENDFtk::implementation::record::Real {
  static constexpr std::size_t width = 11;
  using Type = double;
  using Parser = disco::ENDF;

  static constexpr Type defaultValue = 0.0;
};
