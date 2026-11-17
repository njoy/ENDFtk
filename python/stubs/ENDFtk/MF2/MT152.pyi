"""
MT152 - internal NJOY section
"""
from __future__ import annotations
import typing
__all__: list[str] = ['Section']
class Section:
    """
    MF2 MT152 section - internal NJOY section
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
    def __init__(self, zaid: int, awr: float, lssf: bool, interpolation: int, temperature: float, dilutions: list[float], energies: list[float], total: list[list[float]], elastic: list[list[float]], fission: list[list[float]], capture: list[list[float]], cwtotal: list[list[float]]) -> None:
        """
        Initialise the section
        
        Arguments:
            self             the section
            zaid             the material ZAID value
            awr              the atomic weight ratio
            lssf             the lssf flag
            interpolation    the interpolation scheme
            temperature      the temperature
            dilutions        the dilution values (nsigz values)
            energies         the energy values (nunr values)
            total            the total cross section values (nunr values of
                             nsigz values)
            elastic          the elastic cross section values (nunr values of
                             nsigz values)
            fission          the fission cross section values (nunr values of
                             nsigz values)
            capture          the capture cross section values (nunr values of
                             nsigz values)
            cwTotal          the current weighted total cross section values
                             (nunr values of nsigz values)
        """
    @typing.overload
    def __init__(self, zaid: float, awr: float, lssf: bool, interpolation: int, temperature: float, energies: list[float], total: list[float], elastic: list[float], fission: list[float], capture: list[float], cwtotal: list[float]) -> None:
        """
        Initialise the section for infinite dilution only
        
        Arguments:
            self             the section
            zaid             the material ZAID value
            awr              the atomic weight ratio
            lssf             the lssf flag
            interpolation    the interpolation scheme
            temperature      the temperature
            energies         the energy values (nunr values)
            total            the total cross section values (nunr values)
            elastic          the elastic cross section values (nunr values)
            fission          the fission cross section values (nunr values)
            capture          the capture cross section values (nunr values)
            cwTotal          the current weighted total cross section values
                             (nunr values)
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
    def EUNR(self) -> ...:
        """
        The unresolved resonance energies
        """
    @property
    def LSSF(self) -> bool:
        """
        The self-shielding only flag
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
    def NREAC(self) -> int:
        """
        The number of reactions (normally 5)
        """
    @property
    def NSIGZ(self) -> int:
        """
        The number of dilution or sigma zero values
        """
    @property
    def NUNR(self) -> int:
        """
        The number of energy values
        """
    @property
    def NW(self) -> int:
        """
        The number of data values
        """
    @property
    def SIGZ(self) -> ...:
        """
        The dilution or sigma zero values
        """
    @property
    def TEMZ(self) -> float:
        """
        The temperature
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
    def capture(self) -> ...:
        """
        The capture cross section values for each energy and dilution
        """
    @property
    def current_weighted_total(self) -> ...:
        """
        The current weighted total cross section values for each energy and dilution
        """
    @property
    def dilutions(self) -> ...:
        """
        The dilution or sigma zero values
        """
    @property
    def elastic(self) -> ...:
        """
        The elastic cross section values for each energy and dilution
        """
    @property
    def energies(self) -> ...:
        """
        The unresolved resonance energies
        """
    @property
    def fission(self) -> ...:
        """
        The fission cross section values for each energy and dilution
        """
    @property
    def interpolation(self) -> int:
        """
        The interpolation flag
        """
    @property
    def number_dilutions(self) -> int:
        """
        The number of dilution or sigma zero values
        """
    @property
    def number_energies(self) -> int:
        """
        The number of energy valuess
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of reactions (normally 5)
        """
    @property
    def number_values(self) -> int:
        """
        The number of data values
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def self_shielding_only(self) -> bool:
        """
        The self-shielding only flag
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
    @property
    def total(self) -> ...:
        """
        The total cross section values for each energy and dilution
        """
