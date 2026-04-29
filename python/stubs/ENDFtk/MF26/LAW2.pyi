"""
LAW2 - discrete two-body scattering data for secondary particles
"""
from __future__ import annotations
import typing
__all__: list[str] = ['TabulatedDistribution']
class TabulatedDistribution:
    """
    MF26 section - LAW=2 - an angular distribution given as a tabulated function
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> TabulatedDistribution:
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
    def __init__(self, energy: float, lang: int, cosines: list[float], probabilities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            energy           the incident energy value
            lang             the interpolation type for the distribution
            energies         the cosine values
            probabilities    the probability values
        """
    @typing.overload
    def __init__(self, component: TabulatedDistribution) -> None:
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
    def E(self) -> float:
        """
        The incident energy for which the angular distribution is given
        """
    @property
    def F(self) -> ...:
        """
        The distribution probabilities
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LANG(self) -> int:
        """
        The interpolation type for this distribution (12 or 14)
        """
    @property
    def MU(self) -> ...:
        """
        The cosine values
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
    def NL(self) -> int:
        """
        The number of cosine values
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NW(self) -> int:
        """
        The number of values (cosine and probabilities)
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def cosines(self) -> ...:
        """
        The cosine values
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy for which the angular distribution is given
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_cosine_values(self) -> int:
        """
        The number of cosine values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def probabilities(self) -> ...:
        """
        The distribution probabilities
        """
