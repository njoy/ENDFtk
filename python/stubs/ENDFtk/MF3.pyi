"""
MF3 - reaction cross sections
"""
from __future__ import annotations
import typing
__all__: list[str] = ['File', 'GSection', 'Section']
class File:
    """
    MF3 file - reaction cross sections
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
    def MT(self, mt: int) -> Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    @typing.overload
    def __init__(self, sections: list[Section]) -> None:
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
    def section(self, mt: int) -> Section:
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
class GSection:
    """
    MF3 gsection - reaction cross sections and ratio quantities
    """
    @staticmethod
    def from_string(gsection: str) -> GSection:
        """
        Read the section from a string
        
        An exception is raised if something goes wrong while reading the
        section
        
        Arguments:
            section    the string representing the section
        """
    @typing.overload
    def __init__(self, mt: int, zaid: int, awr: float, lr: int, temp: float, flux: list[list[list[float]]], xs: list[list[list[float]]]) -> None:
        """
        Initialise the section
        
        Arguments:
            self     the section
            mt       the MT number
            zaid     the ZA identifier
            awr      the atomic mass ratio
            lr       the complex breakup flag
            temp     the temperature
            flux     3D array of the group-wise fluxes (nl, nz, ngn)
            xs       3D array of the group-wise cross sections (nl, nz, ngn)
        """
    @typing.overload
    def __init__(self, mt: int, zaid: int, awr: float, lr: int, temp: float, flux: list[list[list[float]]], xs: list[list[list[float]]], ratio: list[list[list[float]]]) -> None:
        """
        Initialise the section
        
        Arguments:
            self     the section
            mt       the MT number
            zaid     the ZA  identifier
            awr      the atomic mass ratio
            lr       the complex breakup flag (default 0)
            temp     the temperature
            flux     3D array of the group-wise fluxes (nl, nz, ngn)
            xs       3D array of the group-wise cross sections (nl, nz, ngn)
            ratio    3D array of the group-wise ratios (nl, nz, ngn)
        """
    @typing.overload
    def __init__(self, gsection: GSection) -> None:
        """
        Initialise the gsection with another gsection
        
        Arguments:
            self       the gsection
            section    the gsection to be copied
        """
    def cross_section(self, moment: int, dilution: int) -> list[float]:
        """
        The group cross sections for a given moment and dilution index
        """
    def flux(self, moment: int, dilution: int) -> list[float]:
        """
        The group fluxes for a given moment and dilution index
        """
    def ratio(self, moment: int, dilution: int) -> list[float]:
        """
        The group ratios for a given moment and dilution index
        """
    def to_string(self, mat: int, mf: int) -> str:
        """
        Return the string representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
            mf      the MF number to be used
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def LR(self) -> int:
        """
        The complex break up flag
        """
    @property
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NGN(self) -> int:
        """
        The number of neutron groups
        """
    @property
    def NL(self) -> int:
        """
        The number of legendre moments
        """
    @property
    def NZ(self) -> int:
        """
        The number of dilution values
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
    def break_up(self) -> int:
        """
        The complex break up flag
        """
    @property
    def number_dilutions(self) -> int:
        """
        The number of dilution values
        """
    @property
    def number_groups(self) -> int:
        """
        The number of neutron groups
        """
    @property
    def number_moments(self) -> int:
        """
        The number of legendre moments
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
    @property
    def temperature(self) -> float:
        """
        The temperature
        """
class Section:
    """
    MF3 section - reaction cross sections
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
    def __init__(self, mt: int, zaid: int, awr: float, qm: float, qi: float, lr: int, boundaries: list[int], interpolants: list[int], energies: list[float], xs: list[float]) -> None:
        """
        Initialise the section
        
        Arguments:
            self           the section
            mt             the MT number
            zaid           the ZA  identifier
            awr            the atomic mass ratio
            qm             the mass difference Q value
            qi             the reaction Q value
            lr             the complex breakup flag
            boundaries     the interpolation range boundaries
            interpolants   the interpolation types for each range
            energies       the energy values
            xs             the cross section values
        """
    @typing.overload
    def __init__(self, mt: int, zaid: int, awr: float, qm: float, qi: float, energies: list[float], xs: list[float], interpolant: int = 2, lr: int = 0) -> None:
        """
        Initialise the section
        
        Arguments:
            self          the section
            mt            the MT number
            zaid          the ZA  identifier
            awr           the atomic mass ratio
            qm            the mass difference Q value
            qi            the reaction Q value
            energies      the energy values
            xs            the cross section values
            interpolant   the interpolation type (default 2 - linlin)
            lr            the complex breakup flag (default 0)
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
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LR(self) -> int:
        """
        The complex break up flag
        """
    @property
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this section
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
    def QI(self) -> float:
        """
        The reaction Q value
        """
    @property
    def QM(self) -> float:
        """
        The mass difference Q value
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
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def complex_breakup(self) -> int:
        """
        The complex break up flag
        """
    @property
    def cross_sections(self) -> ...:
        """
        The cross section values
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
    def mass_difference_qvalue(self) -> float:
        """
        The mass difference Q value
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
    def reaction_qvalue(self) -> float:
        """
        The mass difference Q value
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
