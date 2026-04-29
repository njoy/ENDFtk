"""
MT454 - independent fission product yields
"""
import ENDFtk.MF8
from __future__ import annotations
import pybind11_stubgen.typing_ext
import typing
__all__: list[str] = ['Section']
class Section:
    """
    MF8 MT454 section - independent fission product yields
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
    def __init__(self, zaid: float, awr: float, yields: list[ENDFtk.MF8.FissionYieldData]) -> None:
        """
        Initialise the section with fission yield data
        
        Arguments:
            self     the section
            zaid     the material ZAID value
            awr      the atomic weight ratio
            yields   the fission yield data
        """
    @typing.overload
    def __init__(self, zaid: float, awr: float, identifiers: list[int], states: list[int], yields: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]]) -> None:
        """
        Initialise the section with energy independent fission yields
        
        Arguments:
            self          the section
            zaid          the material ZAID value
            awr           the atomic weight ratio
            identifiers   the fission product identifiers (NFP values)
            states        the isomeric states (NFP values)
            yields        the fission yield values and uncertainties
                          (NFP pairs)
        """
    @typing.overload
    def __init__(self, zaid: float, awr: float, identifiers: list[int], states: list[int], energies: list[float], interpolants: list[int], yields: list[list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]]]) -> None:
        """
        Initialise the section with energy dependent fission yields
        
        Arguments:
            self           the section
            zaid           the material ZAID value
            awr            the atomic weight ratio
            identifiers    the fission product identifiers (NFP values)
            states         the isomeric states (NFP values)
            energies       the incident neutron energies (NE values)
            interpolants   the interpolation types (NE-1 values)
            yields         the fission yield values and uncertainties
                           (NFP arrays of NE pairs)
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
    def E(self) -> ...:
        """
        The incident energy values
        """
    @property
    def LE(self) -> bool:
        """
        Whether or not the fission yield data is energy independent
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
    def NE(self) -> int:
        """
        The number of incident energy values
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
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def is_energy_independent(self) -> bool:
        """
        Whether or not the fission yield data is energy independent
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
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
    def yields(self) -> ...:
        """
        The fission yield data, one for each incident energy
        """
