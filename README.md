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
git checkout feature/python-v2
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make ENDFtk.python -j8
```

Since the python bindings for ENDFtk are still a work in progress, we have to check out the feature/python-v2 branch. Once these go into production this step will no longer be required.

The compilation will produce a dynamic library linked to the python libraries on the user's computer. In order to use them in python, the user should make sure that the library is within the python path. You can set that up by using `sys.path.append(...)` in your python code, or by launching python in the directory where the library can be found.

### A minimal user guide:

Opening up a tape:
```
import ENDFtk
tape = ENDFtk.tree.Tape.from_file( 'n-001_H_001.endf' )
```

This opens the ENDF file as an index tree from which a user can parse components (entire materials, files or sections) as follows:
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
but since they are already parsed, no need to use the `.parse()` at the end. There are also ENDF-speak equivalents to this:
```
mat = tape.MAT(125).parse()
file = mat.MF(6)
section = file.MT(102)
```

A simple example for looking at the different secondary particles and the distribution types used for them:
```
pu = tape.material(9437).parse()
for product in pu.file(6).section(102).reaction_products :

    print( product.ZAP, product.LAW )
```

ENDFtk uses a concept called ranges so as a result, anything coming out as a range will be a custom type. These custom range types allow subscripting and iteration like any other list. To convert such a range into a proper list, you can use the `to_list()` method or slicing. This will do a deep copy of primitive types (int, doubles, etc.). It will not do a deep copy for custom types like sections or underlying components. To deep copy a range of custom types, a user can use the `copy()` method on the range.

For example:
```
file = tape.material(125).file(6).parse()
sections = file.sections           # this is the custom range type for MF6 sections
sections = file.sections.to_list() # this is a list of MF6 sections, with the same memory address as those contained in the file object

sections = file.sections[:]        # this is also a list of MF6 sections, with the same memory address as those contained in the file object
sections = file.sections.copy()    # this is a list of MF6 sections that have been copied, with a different memory addressed as those contained in the file object
```

## LICENSE
The software contained in this repository is covered under the associated [LICENSE](LICENSE) file.
