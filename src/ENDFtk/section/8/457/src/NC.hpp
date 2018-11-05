long NC() const {
  long NC = 1;
  NC += this->energies_.NC();
  NC += this->modes_.NC();
  return NC;
};

