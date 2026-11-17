"""
LAW1 - continuum energy-angle data for secondary particles
"""
from __future__ import annotations
import typing
__all__: list[str] = ['LegendreCoefficients']
class LegendreCoefficients:
    """
    MF26 section - LAW=1 - angular distributions are given as Legendre
                           coefficients
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> LegendreCoefficients:
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
    def __init__(self, energy: float, nd: int, na: int, energies: list[float], coefficients: list[list[float]]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            energy          the incident energy value
            nd              the number of discrete energies
            na              the number of angular parameters
            energies        the energy values
            coefficients    the Legendre coefficients
        """
    @typing.overload
    def __init__(self, component: LegendreCoefficients) -> None:
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
    def A(self) -> ...:
        """
        The Legendre coefficients
        """
    @property
    def E(self) -> float:
        """
        The incident energy value
        """
    @property
    def EP(self) -> ...:
        """
        The secondary energy values
        """
    @property
    def F0(self) -> ...:
        """
        The total emission probabilities
        """
    @property
    def LANG(self) -> int:
        """
        The representation type
        """
    @property
    def NA(self) -> int:
        """
        The number of angular parameter values
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def ND(self) -> int:
        """
        The number of discrete energies
        """
    @property
    def NEP(self) -> int:
        """
        The number of secondary energy values
        """
    @property
    def NL(self) -> int:
        """
        The Legendre order
        """
    @property
    def NW(self) -> int:
        """
        The number of values in this component
        """
    @property
    def coefficients(self) -> ...:
        """
        The Legendre coefficients
        """
    @property
    def energies(self) -> ...:
        """
        The secondary energy values
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def legendre_order(self) -> int:
        """
        The Legendre order
        """
    @property
    def number_angular_parameters(self) -> int:
        """
        The number of angular parameter values
        """
    @property
    def number_discrete_energies(self) -> int:
        """
        The number of discrete energies
        """
    @property
    def number_secondary_energies(self) -> int:
        """
        The number of secondary energy values
        """
    @property
    def representation(self) -> int:
        """
        The representation type
        """
    @property
    def total_emission_probabilities(self) -> ...:
        """
        The total emission probabilities
        """
