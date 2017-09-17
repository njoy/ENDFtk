class Resonance {
  Chunk chunk;
public:
  Resonance( Chunk&& chunk ) : chunk( std::move(chunk) ){}
  double ER() const { return this->chunk[0]; }
  double AJ() const { return this->chunk[1]; }
  double GN() const { return this->chunk[2]; }
  double GG() const { return this->chunk[3]; }
  double GFA() const { return this->chunk[4]; }
  double GFB() const { return this->chunk[5]; }
};
