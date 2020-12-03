class DecayConstant : protected ListRecord {

public:
  /* constructor */
  using ListRecord::ListRecord;

  /* get methods */
  using ListRecord::NPL;

  int NNF() const { return ListRecord::NPL() / 2; }

  double energy() const { return ListRecord::C2(); }

  auto lambdas() const { return ListRecord::list()
                                | ranges::view::stride( 2 ); }

  auto alphas() const { return ListRecord::list()
                               | ranges::view::drop_exactly( 1 ) 
                               |     ranges::view::stride( 2 ); }

  using ListRecord::NC;
  using ListRecord::print;
};

