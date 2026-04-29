"""
MT18 - prompt fission neutron spectra
"""
from __future__ import annotations
import typing
__all__: list[str] = ['GSection']
class GSection:
    """
    MF5 MT18 gsection - prompt fission neutron spectra
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
    def __init__(self, zaid: float, awr: float, lr: int = 0, temp: float, chi: list[float]) -> None:
        """
        Initialise the section
        
        Arguments:
           self            the section
           zaid            the ZA identifier
           awr             the atomic weight ratio
           lr              the complex breakup flag
           temp            the temperature
           chi             delayed neutron spectra (ngn)
        """
    @typing.overload
    def __init__(self, gsection: GSection) -> None:
        """
        Initialise the gsection with another gsection
        
        Arguments:
            self       the gsection
            section    the gsection to be copied
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
        The complex breakup flag
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
    def NZ(self) -> int:
        """
        The number of dilutions
        """
    @property
    def TEMP(self) -> float:
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
    def break_up(self) -> int:
        """
        The complex breakup flag
        """
    @property
    def chi(self) -> list[float]:
        """
        The prompt fission neutron spectra
        """
    @property
    def number_dilutions(self) -> int:
        """
        The number of dilutions
        """
    @property
    def number_neutron_groups(self) -> int:
        """
        The number of neutron groups
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
