long NC() const {
  long NC = 1;
  NC += this->energies_.NC();
  return NC;
};

