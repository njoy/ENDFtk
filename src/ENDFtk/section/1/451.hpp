template<>
class Type< 1, 451 > : protected Base {
public:

  /* fields */
  int lrp_;
  int lfi_;
  int nlib_;
  int nmod_;
  std::array< ControlRecord, 3 > parameters_;
  std::vector< TextRecord > description_;
  std::vector< DirectoryRecord > index_;

  /* auxiliary functions */
#include "ENDFtk/section/1/451/src/readRecords.hpp"

  public:
  /* constructor */
#include "ENDFtk/section/1/451/src/ctor.hpp"

  /* set methods */
  int& LRP() { return this->lrp_; }
  int& LFI() { return this->lfi_; }
  int& NLIB() { return this->nlib_; }
  int& NMOD() { return this->nmod_; }

  /* implement set methods on ContRecord to enable this
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

  /* get methods */
  int LRP() const { return const_cast< Type* >( this )->LRP(); }
  int LFI() const { return const_cast< Type* >( this )->LFI(); }
  int NLIB() const { return const_cast< Type* >( this )->NLIB(); }
  int NMOD() const { return const_cast< Type* >( this )->NMOD(); }

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

  auto description() const {
    return 
      ranges::view::concat
        ( this->description_
            | ranges::view::transform
              ( []( const auto& textRecord )->decltype(auto)
              { return textRecord.text(); } )
            | ranges::view::join( '\n' ),
          ranges::view::single( '\n' ) );
   }

  auto index() const { 
    return ranges::make_iterator_range( this->index_.begin(), 
                                        this->index_.end() ); 
  }

  long NC() const { return 4 + this->NWD() + this->NXC(); }

#include "ENDFtk/section/1/451/src/print.hpp"

  using Base::MT;
  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;

//
//  // MT452 total nubar data
//  template < bool B > class Type< 452, B > : protected Base {
//
//  /* fields */
//  int lnu_;
//  ListRecord polynomial_;
//  TabulationRecord tabulated_;
//
//  public:
//
//  /* constructor */
//#include "ENDFtk/section/1/451/src/ctor-452.hpp"
//
//  /* set methods */
//
//  /* get methods */
//  int LNU() const { return this->lnu_; }
//
//  // @todo extract values
//  const ListRecord& polynomial() const { return this->polynomial_; }
//  const TabulationRecord& tabulated() const { return this->tabulated_; }
//
//  using Base::MT;
//  using Base::ZA;
//  using Base::atomicWeightRatio;
//  };
//
//  // MT455 delayed nubar data
//  template < bool B > class Type< 455, B > : protected Type< 452, B > {
//
//  /* fields */
//  ListRecord independent_; // LDG=0
//  // @todo need TAB2
//  // std::vector< ListRecord > // LDG=1
//
//  public:
//
//  /* constructor */
//#include "ENDFtk/section/1/451/src/ctor-456.hpp"
//
//  /* set methods */
//
//  /* get methods */
//  using Type< 452 >::LNU;
//
//  // @todo extract values
//  const ListRecord& independent() const { return this->independent_; }
//  using Type< 452 >::polynomial;
//  using Type< 452 >::tabulated;
//
//  using Type< 452 >::MT;
//  using Type< 452 >::ZA;
//  using Type< 452 >::atomicWeightRatio;
//  };
//
//  // MT456 prompt nubar data
//  template < bool B > class Type< 456, B > : protected Type< 452, B > {
//
//  public:
//
//  /* constructor */
//#include "ENDFtk/section/1/451/src/ctor-456.hpp"
//
//  /* set methods */
//
//  /* get methods */
//  using Type< 452 >::LNU;
//
//  // @todo extract values
//  using Type< 452 >::polynomial;
//  using Type< 452 >::tabulated;
//
//  using Type< 452 >::MT;
//  using Type< 452 >::ZA;
//  using Type< 452 >::atomicWeightRatio;
//  };
//
//  // MT458 fission Q value data
//  template < bool B > class Type< 458, B > : protected Base {
//
//  /* fields */
//  ListRecord data_;
//
//  public:
//
//  /* constructor */
//#include "ENDFtk/section/1/451/src/ctor-458.hpp"
//
//  /* set methods */
//  /* implement set methods on ListRecord to enable this
//  int& NPLY() { return data_.L2() }
//  */
//
//  /* get methods */
//    int NPLY() const { return data_.L2(); }
//
//  // @todo extract values
//  const ListRecord& data() const { return this->data_; }
//
//  using Base::MT;
//  using Base::ZA;
//  using Base::atomicWeightRatio;
//  };
//
//  // MT460 delayed photon data
//  template < bool B > class Type< 460, B > : protected Base {
//
//  /* fields */
//  std::vector< TabulationRecord > discrete_;     // LO=1
//  ListRecord continuous_;                        // LO=2
//
//  // @todo store this as a variant because it is either of these two?
//
//  /* auxiliary functions */
//#include "ENDFtk/section/1/451/src/readRecords.hpp"
//
//  public:
//
//  /* constructor */
//#include "ENDFtk/section/1/451/src/ctor-460.hpp"
//
//  /* set methods */
//
//  /* get methods */
//  int LO() const { return ( this->NG() != 0 ? 1 : 2 ); }
//  int NG() const { return static_cast<int>( this->discrete_.size() ); }
//
//  using Base::MT;
//  using Base::ZA;
//  using Base::atomicWeightRatio;
//  };
};
