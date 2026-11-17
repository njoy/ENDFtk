"""
MT451 - thermal scattering general information
"""
from __future__ import annotations
import typing
__all__: list[str] = ['ElementInformation', 'Section']
class ElementInformation:
    """
    MF7 MT451 component - element information for thermal scattering moderators
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ElementInformation:
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
    def __init__(self, atoms: int, identifiers: list[int], states: list[int], abundances: list[float], weights: list[float], xs: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the component
            atoms          the number of atoms in the molecule or unit cell
            identifiers    the isotope identifiers (ZA identifier)
            states         the isomeric state for each isotope
            abundances     the isotope abundances
            weights        the atomic weight ratios
            xs             the free atom scattering cross sections
        """
    @typing.overload
    def __init__(self, component: ElementInformation) -> None:
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
    def AFI(self) -> ...:
        """
        The isotope abundancies
        """
    @property
    def AWRI(self) -> ...:
        """
        The isotope atomic weight ratios
        """
    @property
    def LISI(self) -> ...:
        """
        The isotope isomeric states
        """
    @property
    def NAS(self) -> int:
        """
        The number of atoms in the molecule or unit cell
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NI(self) -> int:
        """
        The number of isotopes in the element
        """
    @property
    def SFI(self) -> ...:
        """
        The isotope free atom scattering cross sections
        """
    @property
    def ZAI(self) -> ...:
        """
        The isotope ZA identifiers
        """
    @property
    def abundances(self) -> ...:
        """
        The isotope abundancies
        """
    @property
    def atomic_weight_ratios(self) -> ...:
        """
        The isotope atomic weight ratios
        """
    @property
    def free_scattering_cross_sections(self) -> ...:
        """
        The isotope free atom scattering cross sections
        """
    @property
    def isomeric_states(self) -> ...:
        """
        The isotope isomeric states
        """
    @property
    def isotope_identifiers(self) -> ...:
        """
        The isotope ZA identifiers
        """
    @property
    def number_atoms(self) -> int:
        """
        The number of atoms in the molecule or unit cell
        """
    @property
    def number_isotopes(self) -> int:
        """
        The number of isotopes in the element
        """
class Section:
    """
    MF7 MT451 section - thermal scattering general information
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
    def __init__(self, zaid: float, awr: float, elements: list[ElementInformation]) -> None:
        """
        Initialise the section using isotopes
        
        Arguments:
            self        the section
            zaid        the ZA value of the material
            awr         the atomic weight ratio
            elements    the elements (at least 1)
        """
    @typing.overload
    def __init__(self, zaid: float, awr: float, element: ElementInformation) -> None:
        """
        Initialise the section using isotopes
        
        Arguments:
            self       the section
            zaid       the ZA value of the material
            awr        the atomic weight ratio
            element    the element information
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
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NA(self) -> int:
        """
        The number of elements
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
    def elements(self) -> ...:
        """
        The element data
        """
    @property
    def number_elements(self) -> int:
        """
        The number of elements
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
