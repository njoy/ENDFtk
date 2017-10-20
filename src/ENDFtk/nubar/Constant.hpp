class Constant : protected ListRecord {

public:
  /* constructor */
  using ListRecord::ListRecord;

  /* get methods */
  static constexpr int LDG(){ return 0; }
  int NNF() const { return ListRecord::NPL(); }
  auto lambdas() const { return ListRecord::list(); }
  using ListRecord::NC;
  using ListRecord::print;
};

