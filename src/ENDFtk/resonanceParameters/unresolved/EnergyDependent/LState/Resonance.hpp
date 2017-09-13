class Resonance {
protected:
  Chunk chunk;

public:
  Resonance( Chunk&& chunk )
    : chunk( std::move( chunk ) )
  { }

  double ES() const { return this->chunk[0]; }
  double D() const { return this->chunk[1]; }
  double GX() const { return this->chunk[2]; }
  double GNO() const { return this->chunk[3]; }
  double GG() const { return this->chunk[4]; }
  double GF() const { return this->chunk[5]; }
};

