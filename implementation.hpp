

#include "ENDFtk/implementation/record.hpp"

namespace ENDFtk {
namespace implementation {

class TapeIdentification;
using TPID = TapeIdentification;

class StructureDivision;

StructureDivision
sectionEndRecord( int MAT, int MF );

StructureDivision
SEND( int MAT, int MF );

StructureDivision
fileEndRecord( int MAT );

StructureDivision
FEND( int MAT );

StructureDivision
materialEndRecord();

StructureDivision
MEND();

StructureDivision
tapeEndRecord();

StructureDivision
TEND();

class HeadRecord;
using HEAD = HeadRecord;

HeadRecord&
asHead( StructureDivision& record );

HeadRecord&
asHead( double expectedZA,
        double expectedAtomicWeightRatio,
        StructureDivision& record );

const HeadRecord&
asHead( const StructureDivision& record );

const HeadRecord&
asHead( double expectedZA,
        double expectedAtomicWeightRatio,
        const StructureDivision& record );

class TextRecord;
using TEXT = TextRecord;

class ControlRecord;
using CONT = ControlRecord;

class DirectoryRecord;
using DIR = DirectoryRecord;

class ListRecord;
using LIST = ListRecord;

class UnivariateTabulation;
using TAB1 = UnivariateTabulation;

class BivariateTabulation;
using TAB2 = BivariateTabulation;

class IntegerRecord;
using INTG = IntegerRecord;

class SkipRecord;

template< typename T >
using MutableReturnType =
  typename std::add_lvalue_reference< T >::type;

template< typename T >
using ImmutableReturnType =
  typename std::conditional
  < std::is_trivially_copyable< T >::value,
    T, typename std::add_lvalue_reference
       < typename std::add_const
         < T >::type >::type >::type;

template< typename T >
using clean = typename std::remove_const
              < typename std::remove_reference< T >::type >::type;

class SectionBase;

template<int MF>
class Section;

template<int MF>
class File;

template<typename Iterator>
class TapeSkeleton;

template<typename Iterator>
class MaterialSkeleton;

template<typename Iterator>
class FileSkeleton;

template<typename Iterator>
class SectionSkeleton;

} // namespace implementation
} // namespace ENDFtk

#include "ENDFtk/implementation/TapeIdentification.hpp"
#include "ENDFtk/implementation/StructureDivision.hpp"
#include "ENDFtk/implementation/HeadRecord.hpp"
#include "ENDFtk/implementation/TextRecord.hpp"
#include "ENDFtk/implementation/ControlRecord.hpp"
#include "ENDFtk/implementation/DirectoryRecord.hpp"
#include "ENDFtk/implementation/ListRecord.hpp"
#include "ENDFtk/implementation/UnivariateTabulation.hpp"
#include "ENDFtk/implementation/SectionBase.hpp"
#include "ENDFtk/implementation/SectionSkeleton.hpp"
#include "ENDFtk/implementation/FileSkeleton.hpp"
#include "ENDFtk/implementation/MaterialSkeleton.hpp"
#include "ENDFtk/implementation/TapeSkeleton.hpp"
#include "ENDFtk/implementation/File.hpp"
