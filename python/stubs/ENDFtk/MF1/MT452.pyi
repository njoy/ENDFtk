"""
MT452 - the total number of fission neutrons
"""
import ENDFtk.MF1
from __future__ import annotations
import typing
__all__: list[str] = ['Section']
class Section:
    """
    MF1 MT452 section - the total number of fission neutrons
    """
    @staticmethod
    def from_string(section: str) -> Section:
        """
        Read the section from a string
        
        An exception is raised if something goes wrong while reading the
        section
        
        Arguments:
            section    the string representing the section
        """
    @typing.overload
    def __init__(self, zaid: int, awr: float, multiplicity: ENDFtk.MF1.PolynomialMultiplicity | ENDFtk.MF1.TabulatedMultiplicity) -> None:
        """
        Initialise the section
        
        Arguments:
            self            the section
            zaid            the ZA value of the material
            awr            the atomic weight ratio
            multiplicity    the multiplicity data
        """
    @typing.overload
    def __init__(self, section: Section) -> None:
        """
        Initialise the section with another section
        
        Arguments:
            self       the section
            section    the section to be copied
        """
    def to_string(self, mat: int, mf: int) -> str:
        """
        Return the string representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
            mf      the MF number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def LNU(self) -> int:
        """
        The fission multiplicity representation type
        """
    @property
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this section
        """
    @property
    def ZA(self) -> int:
        """
        The ZA identifier for the section
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def nubar(self) -> ENDFtk.MF1.PolynomialMultiplicity | ENDFtk.MF1.TabulatedMultiplicity:
        """
        The fission multiplicity data
        """
    @property
    def representation(self) -> int:
        """
        The fission multiplicity representation type
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
