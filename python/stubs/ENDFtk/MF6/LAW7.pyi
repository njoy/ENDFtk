"""
LAW7 - distributions are given in the E,mu,E' ordering
"""
from __future__ import annotations
import typing
__all__: list[str] = ['AngularDistribution', 'EnergyDistribution']
class AngularDistribution:
    """
    MF6 section - LAW=7 - the angular distributions associated to a given
                          incident energy
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> AngularDistribution:
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
    def __init__(self, energy: float, boundaries: list[int], interpolants: list[int], distributions: list[EnergyDistribution]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            energy           the incident energy
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the secondary energy distributions
        """
    @typing.overload
    def __init__(self, component: AngularDistribution) -> None:
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
        The incident energy value
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
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
    def NMU(self) -> int:
        """
        The number of cosine values
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NRM(self) -> int:
        """
        The number of interpolation regions for the cosines
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def cosines(self) -> ...:
        """
        The cosines values
        """
    @property
    def energy_distributions(self) -> ...:
        """
        The energy distributions
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_cosines(self) -> int:
        """
        The number of cosine values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
class EnergyDistribution:
    """
    MF6 section - LAW=7 - the secondary energy distribution associated to a
                          given cosine value
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> EnergyDistribution:
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
    def __init__(self, cosine: float, boundaries: list[int], interpolants: list[int], energies: list[float], probabilities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            cosine           the cosine value of the secondary energy distribution
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            energies         the energy values
            probabilities    the probability values
        """
    @typing.overload
    def __init__(self, component: EnergyDistribution) -> None:
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
    def EP(self) -> ...:
        """
        The outgoing energy values
        """
    @property
    def F(self) -> ...:
        """
        The probability values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def MU(self) -> float:
        """
        The cosine value for this secondary energy distribition
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
    def NEP(self) -> int:
        """
        The number of secondary energy values
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
    def NRP(self) -> int:
        """
        The number of interpolation regions for the secondary energy
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def cosine(self) -> float:
        """
        The cosine value for this secondary energy distribition
        """
    @property
    def energies(self) -> ...:
        """
        The outgoing energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_outgoing_energies(self) -> int:
        """
        The number of secondary energy values
        """
    @property
    def number_points(self) -> int:
        """
        The number of points
        """
    @property
    def probabilities(self) -> ...:
        """
        The probability values
        """
