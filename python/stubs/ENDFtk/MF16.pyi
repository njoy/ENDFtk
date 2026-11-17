"""
MF16 - photon energy-angle distributions
"""
from __future__ import annotations
import typing
__all__: list[str] = ['GSection']
class GSection:
    """
    MF16 gsection - neutron-gamma matrices
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
    def __init__(self, mt: int, zaid: int, awr: float, lr: int, ngn: int, temp: float, flux: list[list[list[float]]], matrix: list[list[list[list[float]]]]) -> None:
        """
        Initialise the section
        
        Arguments:
           self        the section
           mt          the MT number
           zaid        the ZA identifier
           awr         the atomic mass ratio
           lr          the complex breakup flag (default 0)
           ngn         the number of neutron groups
           temp        the temperature
           flux        3D array of the group-wise fluxes (nl, nz, ngn)
           matrix      4D array of photon yields ( nl, nz, ngn, ngg )
        """
    @typing.overload
    def __init__(self, gsection: GSection) -> None:
        """
        Initialise the gsection with another gsection
        
        Arguments:
            self       the gsection
            section    the gsection to be copied
        """
    def flux(self, moment: int, dilution: int) -> list[float]:
        """
        The group fluxes for a given moment and dilution index
        """
    def matrix(self, moment: int, dilution: int) -> list[list[float]]:
        """
        The matrix for a given moment and dilution index
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
    def LRFLAG(self) -> int:
        """
        The break up identifier flag
        """
    @property
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NGN(self) -> int:
        """
        The number of neutron energy bins
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
    def break_up_id(self) -> int:
        """
        The break up identifier flag
        """
    @property
    def number_dilutions(self) -> int:
        """
        The number of diltuion values
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
