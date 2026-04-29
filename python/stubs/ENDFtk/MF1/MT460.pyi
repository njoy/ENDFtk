"""
MT460 - delayed photon data for particle induced or spontaneous fission
"""
from __future__ import annotations
import typing
__all__: list[str] = ['ContinuousPhotons', 'DiscretePhotonMultiplicity', 'DiscretePhotons', 'Section']
class ContinuousPhotons:
    """
    MF1 MT460 component - decay constants for delayed photon precursors
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ContinuousPhotons:
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
    def __init__(self, constants: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            constants     the precursor families decay constants
        """
    @typing.overload
    def __init__(self, component: ContinuousPhotons) -> None:
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
    def LO(self) -> int:
        """
        The representation type for the delayed photon data
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NG(self) -> int:
        """
        The number of discrete photons
        """
    @property
    def NNF(self) -> int:
        """
        The number of delayed neutron precursors
        """
    @property
    def decay_constants(self) -> ...:
        """
        The decay constants
        """
    @property
    def lambdas(self) -> ...:
        """
        The decay constants
        """
    @property
    def number_discrete_photons(self) -> int:
        """
        The number of discrete photons
        """
    @property
    def number_precursors(self) -> int:
        """
        The number of delayed neutron precursors
        """
    @property
    def representation(self) -> int:
        """
        The representation type for the delayed photon data
        """
class DiscretePhotonMultiplicity:
    """
    MF1 MT460 component - tabulated time dependent multiplicity for a
                          discrete photon
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> DiscretePhotonMultiplicity:
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
    def __init__(self, energy: float, lph: int, boundaries: list[int], interpolants: list[int], time: list[float], multiplicities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self              the component
            energy            the discrete photon energyt
            lph               the index of the discrete photont
            boundaries        the interpolation range boundariest
            interpolants      the interpolation types for each ranget
            time              the time valuest
            multiplicities    the multiplicity valuest
        """
    @typing.overload
    def __init__(self, component: DiscretePhotonMultiplicity) -> None:
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
        The photon energy
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LPH(self) -> int:
        """
        The photon index (between 1 and NG)
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
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def energy(self) -> float:
        """
        The photon energy
        """
    @property
    def index(self) -> int:
        """
        The photon index (between 1 and NG)
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def multiplicities(self) -> ...:
        """
        The time dependent multiplicity values (in units of 1/s)
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
    def time(self) -> ...:
        """
        The time values
        """
class DiscretePhotons:
    """
    MF1 MT460 component - delayed photons given as discrete photon
                          multiplicities
    """
    @typing.overload
    def __init__(self, photons: list[DiscretePhotonMultiplicity]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            photons    the discrete photon data
        """
    @typing.overload
    def __init__(self, component: DiscretePhotons) -> None:
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
    def LO(self) -> int:
        """
        The representation type for the delayed photon data
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NG(self) -> int:
        """
        The number of discrete photons
        """
    @property
    def number_discrete_photons(self) -> int:
        """
        The number of discrete photons
        """
    @property
    def photons(self) -> ...:
        """
        The discrete photon data
        """
    @property
    def representation(self) -> int:
        """
        The representation type for the delayed photon data
        """
class Section:
    """
    MF1 MT460 section - delayed photon data for particle induced or 
                        spontaneous fission
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
    def __init__(self, zaid: int, awr: float, photons: DiscretePhotons | ContinuousPhotons) -> None:
        """
        Initialise the section
        
        Arguments:
            self       the section
            zaid       the ZA value of the material
            awr        the atomic weight ratio
            photons    the fission energy release data
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
    def LO(self) -> int:
        """
        The representation type for the delayed photon data
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
    def NG(self) -> int:
        """
        The number of discrete photons
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
    def delayed_photons(self) -> DiscretePhotons | ContinuousPhotons:
        """
        The delayed photon data
        """
    @property
    def number_discrete_photons(self) -> int:
        """
        The number of discrete photons
        """
    @property
    def representation(self) -> int:
        """
        The representation type for the delayed photon data
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
