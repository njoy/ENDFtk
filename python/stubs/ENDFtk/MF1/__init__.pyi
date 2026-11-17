"""
MF1 - general information
"""
from __future__ import annotations
import typing
from . import MT451
from . import MT452
from . import MT455
from . import MT456
from . import MT458
from . import MT460
__all__: list[str] = ['File', 'MT451', 'MT452', 'MT455', 'MT456', 'MT458', 'MT460', 'PolynomialMultiplicity', 'TabulatedMultiplicity']
class File:
    """
    MF1 file - general information
    """
    @staticmethod
    def from_string(file: str) -> File:
        """
        Read the file from a string
        
        An exception is raised if something goes wrong while reading the
        file
        
        Arguments:
            file    the string representing the file
        """
    def MT(self, mt: int) -> MT451.Section | MT452.Section | MT455.Section | MT456.Section | MT458.Section | MT460.Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    @typing.overload
    def __init__(self, information: MT451.Section) -> None:
        """
        Initialise the file with descriptive data
        
        Arguments:
            self          the file
            information   the descriptive information (MT451)
        """
    @typing.overload
    def __init__(self, sections: list[MT451.Section | MT452.Section | MT455.Section | MT456.Section | MT458.Section | MT460.Section]) -> None:
        """
        Initialise the file
        
        Arguments:
            self       the file
            sections   the sections to be put into the file
        """
    @typing.overload
    def __init__(self, file: File) -> None:
        """
        Initialise the file with another file
        
        Arguments:
            self    the file
            file    the file to be copied
        """
    def has_MT(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def has_section(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def section(self, mt: int) -> MT451.Section | MT452.Section | MT455.Section | MT456.Section | MT458.Section | MT460.Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    def to_string(self, mat: int) -> str:
        """
        The string representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    @property
    def MF(self) -> int:
        """
        The MF number of the file
        """
    @property
    def MTs(self) -> ...:
        """
        The sections defined in the file
        """
    @property
    def file_number(self) -> int:
        """
        The MF number of the file
        """
    @property
    def sections(self) -> ...:
        """
        The sections defined in the file
        """
class PolynomialMultiplicity:
    """
    MF1 component - fission multiplicity given as a polynomial expansion
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> PolynomialMultiplicity:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, coefficients: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            coefficients    the polynomial coefficients
        """
    @typing.overload
    def __init__(self, component: PolynomialMultiplicity) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def C(self) -> ...:
        """
        The coefficients
        """
    @property
    def LNU(self) -> int:
        """
        The fission multiplicity representation type
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NCO(self) -> int:
        """
        The number of coefficients in the polynomial expansion
        """
    @property
    def coefficients(self) -> ...:
        """
        The coefficients
        """
    @property
    def number_coefficients(self) -> int:
        """
        The number of coefficients in the polynomial expansion
        """
    @property
    def representation(self) -> int:
        """
        The fission multiplicity representation type
        """
class TabulatedMultiplicity:
    """
    MF1 component - energy dependent fission multiplicity
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> TabulatedMultiplicity:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], multiplicities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self              the component
            boundaries        the interpolation range boundaries
            interpolants      the interpolation types for each range
            energies          the cosine values
            multiplicities    the fission multiplicity values
        """
    @typing.overload
    def __init__(self, component: TabulatedMultiplicity) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def E(self) -> ...:
        """
        The energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LNU(self) -> int:
        """
        The fission multiplicity representation type
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NP(self) -> int:
        """
        The number of points
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NU(self) -> ...:
        """
        The fission multiplicity values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def multiplicities(self) -> ...:
        """
        The fission multiplicity values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_points(self) -> int:
        """
        The number of points
        """
    @property
    def representation(self) -> int:
        """
        The fission multiplicity representation type
        """
