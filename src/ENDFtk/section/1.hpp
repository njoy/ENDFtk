template<>
class Type< 1 > {
public:

  // forward declaration, need to declare bool as template parameter to overcome compiler issue
  template < int T, bool B = true > class DataType;

  // MT451 descriptive data
  template < bool B > class DataType< 451, B > : protected Base {

    /* fields */
    long lrp_;
    long lfi_;
    long nlib_;
    long nmod_;
    std::array< ControlRecord, 3 > parameters_;
    std::vector< TextRecord > description_;
    std::vector< DirectoryRecord > index_;

    // @todo store the first 3 text records as separate fields, or provide getters?
    // @todo store index here or erase it?

    /* auxiliary functions */
#include "ENDFtk/section/1/src/readRecords.hpp"

  public:

    /* constructor */
#include "ENDFtk/section/1/src/ctor-451.hpp"

    /* set methods */
    long& LRP() { return this->lrp_; }
    long& LFI() { return this->lfi_; }
    long& NLIB() { return this->nlib_; }
    long& NMOD() { return this->nmod_; }

    /* implement set methods on ContRecord to enable this
    double& ELIS() { return std::get<0>(this->parameters_).C1(); }
    double& STA() { return std::get<0>(this->parameters_).C2(); }
    long& LIS() { return std::get<0>(this->parameters_).L1(); }
    long& LISO() { return std::get<0>(this->parameters_).L2(); }
    long& NFOR() { return std::get<0>(this->parameters_).N2(); }

    double& AWI() { return std::get<1>(this->parameters_).C1(); }
    double& EMAX() { return std::get<1>(this->parameters_).C2(); }
    long& LREL() { return std::get<1>(this->parameters_).L1(); }
    long& NSUB() { return std::get<1>(this->parameters_).N1(); }
    long& NVER() { return std::get<1>(this->parameters_).N2(); }

    double& TEMP() { return std::get<2>(this->parameters_).C1(); }
    long& LDRV() { return std::get<2>(this->parameters_).L1(); }
    */

    // @todo erase and replace descriptive text

    // @todo erase and replace index

    /* get methods */
    long LRP() const { return const_cast< DataType* >( this )->LRP(); }
    long LFI() const { return const_cast< DataType* >( this )->LFI(); }
    long NLIB() const { return const_cast< DataType* >( this )->NLIB(); }
    long NMOD() const { return const_cast< DataType* >( this )->NMOD(); }

    double ELIS() const { return std::get< 0 >( this->parameters_ ).C1(); }
    double STA() const { return std::get< 0 >( this->parameters_ ).C2(); }
    long LIS() const { return std::get< 0 >( this->parameters_ ).L1(); }
    long LISO() const { return std::get< 0 >( this->parameters_ ).L2(); }
    long NFOR() const { return std::get< 0 >( this->parameters_ ).N2(); }

    double AWI() const { return std::get< 1 >( this->parameters_ ).C1(); }
    double EMAX() const { return std::get< 1 >( this->parameters_ ).C2(); }
    long LREL() const { return std::get< 1 >( this->parameters_ ).L1(); }
    long NSUB() const { return std::get< 1 >( this->parameters_ ).N1(); }
    long NVER() const { return std::get< 1 >( this->parameters_ ).N2(); }

    double TEMP() const { return std::get< 2 >( this->parameters_ ).C1(); }
    long LDRV() const { return std::get< 2 >( this->parameters_ ).L1(); }
    long NWD() const { return static_cast< long >( this->index_.size() ); }
    long NXC() const { return static_cast< long >( this->description_.size() ); }

    // @todo extract descriptive text
    const std::vector< TextRecord >& description() const { return this->description_; }

    // @todo extract index
    const std::vector< DirectoryRecord >& index() const { return this->index_; }

    using Base::MT;
    using Base::ZA;
    using Base::atomicWeightRatio;
  };
    
  // MT452 total nubar data
  template < bool B > class DataType< 452, B > : protected Base {
        
    /* fields */
    long lnu_;
    ListRecord polynomial_;
    UnivariateTabulation tabulated_;

  public:

    /* constructor */
#include "ENDFtk/section/1/src/ctor-452.hpp"
        
    /* set methods */
        
    /* get methods */
    long LNU() const { return this->lnu_; }

    // @todo extract values
    const ListRecord& polynomial() const { return this->polynomial_; }
    const UnivariateTabulation& tabulated() const { return this->tabulated_; }

    using Base::MT;
    using Base::ZA;
    using Base::atomicWeightRatio;
  };

  // MT455 delayed nubar data
  template < bool B > class DataType< 455, B > : protected DataType< 452, B > {

    /* fields */
    ListRecord independent_; // LDG=0
    // @todo need TAB2
    // std::vector< ListRecord > // LDG=1

  public:

    /* constructor */
#include "ENDFtk/section/1/src/ctor-456.hpp"

    /* set methods */

    /* get methods */
    using DataType< 452 >::LNU;

    // @todo extract values
    const ListRecord& independent() const { return this->independent_; }
    using DataType< 452 >::polynomial;
    using DataType< 452 >::tabulated;

    using DataType< 452 >::MT;
    using DataType< 452 >::ZA;
    using DataType< 452 >::atomicWeightRatio;
  };

  // MT456 prompt nubar data
  template < bool B > class DataType< 456, B > : protected DataType< 452, B > {

  public:

    /* constructor */
#include "ENDFtk/section/1/src/ctor-456.hpp"

    /* set methods */

    /* get methods */
    using DataType< 452 >::LNU;
        
    // @todo extract values
    using DataType< 452 >::polynomial;
    using DataType< 452 >::tabulated;

    using DataType< 452 >::MT;
    using DataType< 452 >::ZA;
    using DataType< 452 >::atomicWeightRatio;
  };

  // MT458 fission Q value data
  template < bool B > class DataType< 458, B > : protected Base {

    /* fields */
    ListRecord data_;

  public:

    /* constructor */
#include "ENDFtk/section/1/src/ctor-458.hpp"

    /* set methods */
    /* implement set methods on ListRecord to enable this
    long& NPLY() { return data_.L2() }
    */

    /* get methods */
      long NPLY() const { return data_.L2(); }

    // @todo extract values
    const ListRecord& data() const { return this->data_; }

    using Base::MT;
    using Base::ZA;
    using Base::atomicWeightRatio;
  };
    
  // MT460 delayed photon data
  template < bool B > class DataType< 460, B > : protected Base {

    /* fields */
    std::vector< UnivariateTabulation > discrete_; // LO=1
    ListRecord continuous_;                        // LO=2

    // @todo store this as a variant because it is either of these two?

    /* auxiliary functions */
#include "ENDFtk/section/1/src/readRecords.hpp"

  public:

    /* constructor */
#include "ENDFtk/section/1/src/ctor-460.hpp"

    /* set methods */

    /* get methods */
    long LO() const { return ( this->NG() != 0 ? 1 : 2 ); }
    long NG() const { return static_cast<long>( this->discrete_.size() ); }

    using Base::MT;
    using Base::ZA;
    using Base::atomicWeightRatio;
  };
};
