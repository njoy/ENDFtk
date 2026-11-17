// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/GTape.hpp"
#include "tools/views/views-python.hpp"
#include "variants.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeGFile( python::module& module, python::module& viewmodule ) {

  // type aliases
  using File = njoy::ENDFtk::tree::GFile;
  using Section = njoy::ENDFtk::tree::GSection;
  using SectionRange = BidirectionalAnyView< Section >;

  // wrap views created by this tree component
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< tree::GSection, bidirectional >" );

  // create the tree component
  python::class_< File > tree(

    module,
    "GFile",
    "GENDF tree file"
  );

  // wrap the tree component
  tree
  .def(

    python::init< unsigned int, unsigned int >(),
    python::arg( "mat" ), python::arg( "mf" ),
    "Initialise an empty file with its MAT and MF number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mat     the MAT number of the file\n"
    "    mf      the MF number of the file"
  )
  .def(

    python::init< const File& >(),
    python::arg( "file" ),
    "Initialise the file with another file\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    file    the file to be copied"
  )
  .def_property_readonly(

    "MAT",
    &File::MAT,
    "The MAT number of the file"
  )
  .def_property_readonly(

    "material_number",
    &File::materialNumber,
    "The MAT number of the file"
  )
  .def_property_readonly(

    "MF",
    &File::MF,
    "The MF number of the file"
  )
  .def_property_readonly(

    "file_number",
    &File::fileNumber,
    "The MF number of the file"
  )
  .def(

    "has_MT",
    &File::hasMT,
    "Return whether or not the file has a section with the given MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section"
  )
  .def(

    "has_section",
    &File::hasSection,
    "Return whether or not the file has a section with the given MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section"
  )
  .def_property_readonly(

    "section_numbers",
    [] ( const File& self ) -> IntList
       { return self.sectionNumbers(); },
    "All section numbers in the file"
  )
  .def_property_readonly(

    "sections",
    [] ( File& self ) -> SectionRange
       { return self.sections(); },
    "All sections in the file"
  )
  .def(

    "section",
    python::overload_cast< int >( &File::section, python::const_ ),
    python::arg( "mt" ),
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "MT",
    python::overload_cast< int >( &File::MT, python::const_ ),
    python::arg( "mt" ),
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def_property_readonly(

    "content",
    &File::content,
    "The content of the file"
  )
  .def(

    "clean",
    &File::clean,
    "Clean up the file\n\n"
    "This function removes the sequence numbers from the file."
  );
}
