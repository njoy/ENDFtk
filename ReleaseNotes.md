# Release Notes&mdash;ENDFtk
Given here are some release notes for ENDFtk.

NOTES FOR range-v3 REMOVAL:
  - look for a solution on the angularDistributions function in MF4 (commented out for now)

## [ENDFtk v1.1.1](https://github.com/njoy/ENDFtk/pull/xxx)
This update makes the following changes on interface functions:
  - The regions() and pairs() interface functions on the TAB1 record interface functions have been removed. The removal of these interface functions has no impact on the Python interface as these interface functions were not included on the Python side. Miscellaneous documentation updates were made as well.
  - When using the C++ interface for atomic relaxation data, a Transition now has a isRadiative() and isNonRadiative() function returning a boolean so that a user can check if a given transition emits a photon or electron without having to look at subshell identifiers. Since Transition is not exposed ont he Python side, this is not available on the Python side.
  - NBT(), INT(), boundaries(), interpolants(), NR(), numberInterpolationRegions() interface functions were added on TwoBodyScattering::TabulatedDistribution in MF6 and MF26 that mimic the behaviour of a TAB1 record.
  - For LCOMP1 RMatrix Limited, the GAM() and resonanceParameters() functions have been changed to work the same way as the MF2 version. The size of the returned arrays is no longer equal to the number of channels.

In addition, the following issues were corrected:
  - A minor bug in the rectangular matrix covariance block was corrected. The values for the row and column energies are lifted out of a larger array using the std::ranges::take and std::ranges::drop function. For the column energies, we forgot to properly end the sequence. As a result, the end() iterator of the range did not point to the end of the column energies but to the end of the covariance values, which is now corrected.
  - In MF8 MT457 DiscreteSpectrum, NT=8 (which can occur for electrons, i.e. STYP=8), was explicitly disallowed by ENDFtk. This was corrected and a new constructor reflecting this usage was added as well.
  - The STA variable in MF1 MT451 was interpreted incorrectly and this has now been fixed. An additional isUnstable() function has been added to the interface.
  - The NJSX value (the number of spin groups) is now read from the CONT record before the particle pairs in MF32 R-matrix limited uncertainties since SAMMY does not print the NJSX value on the particle pairs (the ENDF format basically has the NJSX value appear in two places and ENDFtk used the second one while SAMMY only prints out the first one). This "breaks" some interface functions (the R-matrix limited uncertainties from_string() function now requires the number of spin groups while previously it did not).
  - In MF28 MT533, the electron population was being returned as an integer value while this can be a floating point value. This has been corrected.
  - All electron subshell identifiers in MF26 MT533 are returned as an integers.

A few changes were also made to remove some range-v3 code in MF1 MT451. These changes have no impact on functionality.

## [ENDFtk v1.1.0](https://github.com/njoy/ENDFtk/pull/198)
This update adds additional interface functions to complete the human readable and ENDF speak interface for many objects:
  - the NBT() and INT() interface functions to complement the boundaries() and interpolants() functions already present in TAB1 and TAB2 style components
  - the numberInterpolationRegions() functions to complement the NR() function already present in TAB1 and TAB2 style components.

This update fixes the following issues:
  - Older versions of ENDFtk sometimes read numbers like '2.0000000+0' as 1.999999999 instead of 2. The disco library was replaced with a new version included in the tools library that fixes this issue. In addition to fixing this issue, parsing ENDF files is now 10-20% faster.

## [ENDFtk v1.0.1](https://github.com/njoy/ENDFtk/pull/195)
This update does not add any additional functionality.

This update fixes the following issues:
  - A compilation issue in a unit test that still used the old catch-adapter (see issue #193).
  - Macros for pybind11 were added where required so that other pybind11 bond libraries can accept ENDFtk components as input arguments on the python side (e.g. covariance matrice blocks). This is currently limited to all ENDFtk section components.

## [ENDFtk v1.0.0](https://github.com/njoy/ENDFtk/pull/192)
This release of ENDFtk has the following changes:
  - All ZA values in the interface (the ZA value in the HEAD records, the ZAP values in the MF6 and MF26 reaction products, etc.) are now changed to integer types instead of a floating point type
  - MF6 and MF26 now have additional functions that allow a user to look for specific reaction products
  - MF9 and MF10 now have additional functions that allow a user to look for specific excited states

The CMake files have also been updated to simplify adding new unit tests.

This release cleans up some of the dependencies and updates most of the dependencies to more recent versions. In particular the Catch2 unit testing framework was updated to version 3.3.2. All unit tests were updated to use better floating point comparison available in this version of Catch2. A number of NJOY dependencies have also been consolidated into a single new dependency (the NJOY tools library) to reduce the number of dependencies to a more manageable level.
