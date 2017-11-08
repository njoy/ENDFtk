class LegendreCoefficients : protected ListRecord {

public:
  /* constructor */
  using ListRecord::ListRecord;
  LegendreCoefficients ( ListRecord&& list ) :  ListRecord( std::move( list ) ) {}

  /* get methods */
  double energy() const { return ListRecord::C2(); }
  int LTP() const { return ListRecord::L1(); }
  long NW() const { return ListRecord::NPL(); }
  long NL() const { return ListRecord::N2(); }

  auto coefficients() const { return ListRecord::list(); }

  using ListRecord::NC;
  using ListRecord::print;
};
