/**
 *  @class
 *  @brief Convenience interface for a probability table at one energy
 *
 *  This is an internal NJOY component from MF2 MT153.
 */
template < typename Range >
class Table {

  /* fields */
  Range chunk_;
  unsigned int nbin_;

  /* auxiliary functions */
  auto column( unsigned int i ) const {

    const auto left = std::next( this->chunk_.begin(), 1 + i * this->nbin_ );
    const auto right = left + this->nbin_;
    return ranges::make_subrange( left, right );
  }

public:

  /* constructor */
  Table( Range&& chunk, unsigned int nbin ) :
    chunk_( std::move( chunk ) ), nbin_( nbin ) {}

  /**
   *  @brief Return the number of bins in the probability table
   */
  unsigned int NBIN() const { return this->nbin_; }

  /**
   *  @brief Return the number of bins in the probability table
   */
  unsigned int numberBins() const { return this->NBIN(); }

  /**
   *  @brief Return the unresolved resonance energy
   */
  double EUNR() const { return this->chunk_[0]; }

  /**
   *  @brief Return the unresolved resonance energy
   */
  double unresolvedResonanceEnergy() const { return this->EUNR(); }

  /**
   *  @brief Return the probability values
   */
  auto PROB() const { return this->column(0); }

  /**
   *  @brief Return the probability values
   */
  auto probabilities() const { return this->PROB(); }

  /**
   *  @brief Return the total cross section values
   */
  auto TOTL() const { return this->column(1); }

  /**
   *  @brief Return the total cross section values
   */
  auto total() const { return this->TOTL(); }

  /**
   *  @brief Return the elastic cross section values
   */
  auto ELAS() const { return this->column(2); }

  /**
   *  @brief Return the elastic cross section values
   */
  auto elastic() const { return this->ELAS(); }

  /**
   *  @brief Return the fission cross section values
   */
  auto FISS() const { return this->column(3); }

  /**
   *  @brief Return the elastic cross section values
   */
  auto fission() const { return this->FISS(); }

  /**
   *  @brief Return the capture cross section values
   */
  auto CAPT() const { return this->column(4); }

  /**
   *  @brief Return the elastic cross section values
   */
  auto capture() const { return this->CAPT(); }

  /**
   *  @brief Return the heating cross section values
   */
  auto HEAT() const { return this->column(5); }

  /**
   *  @brief Return the heating cross section values
   */
  auto heating() const { return this->HEAT(); }
};
