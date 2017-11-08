class NuclearAmplitudeExpansion : protected ListRecord {

public:
  /* constructor */
  using ListRecord::ListRecord;
  NuclearAmplitudeExpansion( ListRecord&& list ) : ListRecord( std::move( list ) ) {}; 

  /* get methods */
  double energy() const { return ListRecord::C2(); }
  int LTP() const { return ListRecord::L1(); }
  long NW() const { return ListRecord::NPL(); }
  long NL() const { return ListRecord::N2(); }

  auto real_a() const {
    return ranges::view::drop_exactly( ListRecord::list(), 
                                       this->NW() - 2 * this->NL() - 2 )
             | ranges::view::stride( 2 );
  }
  auto imaginary_a() const {
    return ranges::view::drop_exactly( ListRecord::list(), 
                                       this->NW() - 2 * this->NL() - 1 )
             | ranges::view::stride( 2 );
  }
  auto b() const {
    return ListRecord::list()
             | ranges::view::take( this->NW() - 2 * this->NL() - 2 );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
