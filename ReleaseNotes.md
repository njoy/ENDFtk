# Release Notes&mdash;ENDFtk
Given here are some release notes for ENDFtk.

## [ENDFtk v1.0.2](https://github.com/njoy/ENDFtk/pull/xxx)
This update does not add any additional functionality.

## [ENDFtk v1.0.1](https://github.com/njoy/ENDFtk/pull/194)
This update does not add any additional functionality.

This update fixes the following issues:
  - A compilation issue in a unit test that still used the old catch-adapter (see issue #193).

## [ENDFtk v1.0.0](https://github.com/njoy/ENDFtk/pull/192)
This release of ENDFtk has the following changes:
  - All ZA values in the interface (the ZA value in the HEAD records, the ZAP values in the MF6 and MF26 reaction products, etc.) are now changed to integer types instead of a floating point type
  - MF6 and MF26 now have additional functions that allow a user to look for specific reaction products
  - MF9 and MF10 now have additional functions that allow a user to look for specific excited states

The CMake files have also been updated to simplify adding new unit tests.

This release cleans up some of the dependencies and updates most of the dependencies to more recent versions. In particular the Catch2 unit testing framework was updated to version 3.3.2. All unit tests were updated to use better floating point comparison available in this version of Catch2. A number of NJOY dependencies have also been consolidated into a single new dependency (the NJOY tools library) to reduce the number of dependencies to a more manageable level.
