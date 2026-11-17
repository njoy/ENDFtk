"""
LAW5 - charged particle elastic scattering
"""
from __future__ import annotations
import typing
__all__: list[str] = ['LegendreCoefficients', 'NuclearAmplitudeExpansion', 'NuclearPlusInterference']
class LegendreCoefficients:
    """
    MF6 section - LAW=5 - charged particle elastic scattering given as
                          Legendre coeffcients
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
    def __init__(self, energy: float, coefficients: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            energy          the incident energy value
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
    def LTP(self) -> int:
        """
        The representation type
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NL(self) -> int:
        """
        The Legendre order or number of cosine values
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
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def legendre_order(self) -> int:
        """
        The Legendre order or number of cosine values
        """
    @property
    def representation(self) -> int:
        """
        The representation type
        """
class NuclearAmplitudeExpansion:
    """
    MF6 section - LAW=5 - charged particle elastic scattering given
                          as nuclear amplitude expansion
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> NuclearAmplitudeExpansion:
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
    def __init__(self, energy: float, nl: int, b: list[float], a: list[complex]) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            energy    the incident energy value
            nl        the Legendre order
            b         the scattering coefficients (for expanding the nuclear
                      scattering cross section)
            a         the interference coefficients (for expanding the
                      nuclear scattering amplitude matrix)
        """
    @typing.overload
    def __init__(self, component: NuclearAmplitudeExpansion) -> None:
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
        The interference coefficients
        """
    @property
    def AI(self) -> ...:
        """
        The interference coefficients
        """
    @property
    def AR(self) -> ...:
        """
        The interference coefficients
        """
    @property
    def B(self) -> ...:
        """
        The scattering coefficients
        """
    @property
    def E(self) -> float:
        """
        The incident energy value
        """
    @property
    def LTP(self) -> int:
        """
        The representation type
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NL(self) -> int:
        """
        The Legendre order or number of cosine values
        """
    @property
    def NW(self) -> int:
        """
        The number of values in this component
        """
    @property
    def imaginary_interference_coefficients(self) -> ...:
        """
        The interference coefficients
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def interference_coefficients(self) -> ...:
        """
        The interference coefficients
        """
    @property
    def real_interference_coefficients(self) -> ...:
        """
        The interference coefficients
        """
    @property
    def representation(self) -> int:
        """
        The representation type
        """
    @property
    def scattering_coefficients(self) -> ...:
        """
        The scattering coefficients
        """
class NuclearPlusInterference:
    """
    MF6 section - LAW=5 - charged particle elastic scattering given as
                          nuclear plus interference distribution
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> NuclearPlusInterference:
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
    def __init__(self, energy: float, ltp: int, cosines: list[float], probabilities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            energy           the incident energy value
            ltp              the representation type
            cosines          the cosine values
            probabilities    the probability values
        """
    @typing.overload
    def __init__(self, component: NuclearPlusInterference) -> None:
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
    def LTP(self) -> int:
        """
        The representation type
        """
    @property
    def MU(self) -> ...:
        """
        The cosine values
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NL(self) -> int:
        """
        The Legendre order or number of cosine values
        """
    @property
    def NW(self) -> int:
        """
        The number of values in this component
        """
    @property
    def PNI(self) -> ...:
        """
        The probability values
        """
    @property
    def cosines(self) -> ...:
        """
        The cosine values
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def probabilities(self) -> ...:
        """
        The probability values
        """
    @property
    def representation(self) -> int:
        """
        The representation type
        """
