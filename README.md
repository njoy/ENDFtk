![Continuous Integration](https://github.com/njoy/ENDFtk/workflows/Continuous%20Integration/badge.svg)

# ENDFtk
Toolkit for reading and interacting with ENDF-6 formatted files. This toolkit provides a full C++ library along with python bindings.

## ENDFtk in python

The python bindings for ENDFtk are still work in progress and should be used accordingly. Please report any issues encountered while using the python bindings using the issue tracker on this repository.

### Installing ENDFtk for python

First of all, a user should clone the ENDFtk repository and build the python bindings:
```
git clone https://github.com/njoy/ENDFtk
cd ENDFtk
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make ENDFtk.python -j8
```

ENDFtk in python requires python 3.x so you will need to have at least one python 3.x installed. When multiple python versions are installed, it may be beneficial to include ```-DPYTHON_EXECUTABLE=$(which python3)``` in the cmake configuration step so that the default python3 version will be picked. The compilation will produce a dynamic library linked to the python libraries on the user's computer (it'll be named something like `ENDFtk.cpython-37m-darwin.so`). This name will also indicate which version of the python libraries this library is linked to. This is important since you will need to use the associated python version with the ENDFtk python package.

In order to use the ENDFtk python package, the user should make sure that the library is within the python path. This can be done in multiple ways. You can set that up by adding the ENDFtk build path to the python path `$PYTHONPATH` environmental variable on your machine, or by using the following in your python code:
```
import sys
sys.path.append( < ENDFtk-build-path > )
```
where `< ENDFtk-build-path >` is the path to the ENDFtk python dynamic library.

When running python in the build directory directly, none of these steps are required.

#### Troubleshooting ####

##### CMake doesn’t detect the right Python version #####

Taken from the pybind11 FAQ.

The CMake-based build system will try to automatically detect the installed version of Python and link against that. When this fails, or when there are multiple versions of Python and it finds the wrong one, delete CMakeCache.txt and then add -DPYTHON_EXECUTABLE=$(which python) to your CMake configure line. (Replace $(which python) with a path to python if your prefer.)

A version of python 3.x is preferred.

##### importError cannot import name <sysconfig> #####

This error sometimes comes up when running the cmake command. This appears to be related to an incomplete/corrupted python installation. It can be rectified by installing the distutils package for the python version that is being used. On a linux system, the following command should install the distutils package:
```
sudo apt install python3-distutils
```

##### cannot find python.h #####

When compiling the python bindings, this error indicates that the python header files and static library we need to link to are not installed on your system. This appears to be related to an incomplete python installation. It can be rectified by installing the python3-dev package (when using python 3). On a linux system, the following command should install the header files:
```
sudo apt install python3-dev
```

### A minimal user guide:

Opening up a tape:
```
import ENDFtk
tape = ENDFtk.tree.Tape.from_file( 'n-001_H_001.endf' )
```

An `ENDFtk.tree.Tape` effectively indexes the file into available materials, files and sections, which can be parsed at will by the user. The `ENDFtk.tree` submodule also provides an `ENDFtk.tree.Material`, `ENDFtk.tree.File` and `ENDFtk.tree.Section` that the user can look through before parsing the data that is contained in any of these. Parsing the data requires strict adherence to the ENDF6 format but loading the data into an `ENDFtk.tree.Tape` does not. As a result, the `ENDFtk.tree.Tape` is also capable of indexing older ENDF files that do not conform with the ENDF6 standard (tests have shown that we can index files as old as ENDF/B-II).

Once the data is indexed, a user can retrieve an/or parse components (entire materials, files or sections) as follows:
```
mat = tape.material(125).parse()
file = tape.material(125).file(6).parse()
section = tape.material(125).file(6).section(102).parse()
```

Accessing the underlying files and sections from parsed materials and sections uses the same function names:
```
mat = tape.material(125).parse()
file = mat.file(6)
section = file.section(102)
```
but since they are already parsed, no need to use the `.parse()` at the end. There are also ENDF-speak equivalents to this for both the `ENDFtk.tree` components as well as the parsed components:
```
mat = tape.MAT(125).parse()
file = mat.MF(6)
section = file.MT(102)
```

Every component in ENDFtk has python documentation associated to it that can be viewed using the `help(...)` function in python:
```
mat = tape.material(125).parse()
file = tape.material(125).file(6).parse()
section = tape.material(125).file(6).section(102).parse()
help( section ) # this will display the help for an ENDF MF6 section
```

A simple example for looking at the different secondary particles and the distribution types used for them:
```
pu = tape.material(9437).parse()
for product in pu.file(6).section(102).reaction_products :

    print( product.ZAP, product.LAW )
```

ENDFtk uses a concept called ranges (aka sequences) so as a result, anything coming out as a range will be a custom type. These custom range types allow subscripting and iteration like any other sequence or list. To convert such a range into a proper list, you can use the `to_list()` method or slicing. This will do a deep copy of primitive types (int, doubles, etc.). It will not do a deep copy for custom types like sections or underlying components. To deep copy a range of custom types, a user can use the `copy()` method on the range.

For example:
```
file = tape.material(125).file(6).parse()
sections = file.sections           # this is the custom range type for MF6 sections
sections = file.sections.to_list() # this is a list of MF6 sections, with the same memory address as those contained in the file object

sections = file.sections[:]        # this is also a list of MF6 sections, with the same memory address as those contained in the file object
sections = file.sections.copy()    # this is a list of MF6 sections that have been copied, with a different memory address as those contained in the file object
```

## LICENSE
This software is copyrighted by Los Alamos National Laboratory and distributed
according to the conditions in the accompanying [LICENSE](LICENSE) file.
