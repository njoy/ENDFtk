class LegendreCoefficients : protected ListRecord {

public:
  /* constructor */
  using ListRecord::ListRecord;
  LegendreCoefficients ( ListRecord&& list ) :  ListRecord( std::move( list ) ) {}

  /* get methods */
  static constexpr int LANG() { return 1; }

  double energy() const { return ListRecord::C2(); }
  long ND() const { return ListRecord::L1(); }
  long NA() const { return ListRecord::L2(); }
  long NW() const { return ListRecord::NPL(); }
  long NEP() const { return ListRecord::N2(); }

  auto energies() const { return ListRecord::list()
                            | ranges::view::stride( 1 + ListRecord::NA() ); }

  using ListRecord::NC;
  using ListRecord::print;
};
