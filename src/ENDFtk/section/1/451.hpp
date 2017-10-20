template<>
class Type< 1, 451 > : protected Base {
protected:
  /* fields */
  int lrp_;
  int lfi_;
  int nlib_;
  int nmod_;
  std::array< ControlRecord, 3 > parameters_;
  std::vector< TextRecord > description_;
  std::vector< DirectoryRecord > index_;

  /* auxiliary functions */
  #include "ENDFtk/section/1/451/src/readParameters.hpp"
  #include "ENDFtk/section/1/451/src/readRecords.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/1/451/src/ctor.hpp"

  /* get methods */
  static constexpr int MT(){ return 451; }

  int LRP() const { return this->lrp_; }
  int LFI() const { return this->lfi_; }
  int NLIB() const { return this->nlib_; }
  int NMOD() const { return this->nmod_; }

  double ELIS() const { return std::get< 0 >( this->parameters_ ).C1(); }
  double STA() const { return std::get< 0 >( this->parameters_ ).C2(); }
  int LIS() const { return std::get< 0 >( this->parameters_ ).L1(); }
  int LISO() const { return std::get< 0 >( this->parameters_ ).L2(); }
  int NFOR() const { return std::get< 0 >( this->parameters_ ).N2(); }

  double AWI() const { return std::get< 1 >( this->parameters_ ).C1(); }
  double EMAX() const { return std::get< 1 >( this->parameters_ ).C2(); }
  int LREL() const { return std::get< 1 >( this->parameters_ ).L1(); }
  int NSUB() const { return std::get< 1 >( this->parameters_ ).N1(); }
  int NVER() const { return std::get< 1 >( this->parameters_ ).N2(); }

  double TEMP() const { return std::get< 2 >( this->parameters_ ).C1(); }
  int LDRV() const { return std::get< 2 >( this->parameters_ ).L1(); }
  int NWD() const { return static_cast< int >( this->description_.size() ); }
  int NXC() const { return static_cast< int >( this->index_.size() ); }

  auto index() const {
    return ranges::make_iterator_range( this->index_.begin(),
                                        this->index_.end() );
  }

  long NC() const { return 4 + this->NWD() + this->NXC(); }

  #include "ENDFtk/section/1/451/src/description.hpp"
  #include "ENDFtk/section/1/451/src/print.hpp"

  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;

  /* implement set methods on ContRecord to enable this
  int& LRP() const { return this->lrp_; }
  int& LFI() const { return this->lfi_; }
  int& NLIB() const { return this->nlib_; }
  int& NMOD() const { return this->nmod_; }


  double& ELIS() { return std::get<0>( this->parameters_ ).C1(); }
  double& STA() { return std::get<0>( this->parameters_ ).C2(); }
  int& LIS() { return std::get<0>( this->parameters_ ).L1(); }
  int& LISO() { return std::get<0>( this->parameters_ ).L2(); }
  int& NFOR() { return std::get<0>( this->parameters_ ).N2(); }

  double& AWI() { return std::get<1>( this->parameters_ ).C1(); }
  double& EMAX() { return std::get<1>( this->parameters_ ).C2(); }
  int& LREL() { return std::get<1>( this->parameters_ ).L1(); }
  int& NSUB() { return std::get<1>( this->parameters_ ).N1(); }
  int& NVER() { return std::get<1>( this->parameters_ ).N2(); }

  double& TEMP() { return std::get<2>( this->parameters_ ).C1(); }
  int& LDRV() { return std::get<2>( this->parameters_ ).L1(); }
  */

  // @todo add function to erase and replace/add descriptive text

  // @todo add function to erase and replace/add index
};

