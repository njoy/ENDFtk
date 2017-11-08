class Tabulated : protected ListRecord {

public:
  /* constructor */
  using ListRecord::ListRecord;
  Tabulated ( ListRecord&& list ) :  ListRecord( std::move( list ) ) {}

  /* get methods */
  double energy() const { return ListRecord::C2(); }
  int LANG() const { return ListRecord::L1(); }
  long NW() const { return ListRecord::NPL(); }
  long NL() const { return ListRecord::N2(); }

  auto cosines() const {
    return ListRecord::list() | ranges::view::stride( 2 );
  }
  auto p() const {
    return ranges::view::drop_exactly( ListRecord::list(), 1 )
             | ranges::view::stride( 2 );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
