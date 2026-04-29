"""
MF14 - angular distributions of photons
"""
from __future__ import annotations
import pybind11_stubgen.typing_ext
import typing
__all__: list[str] = ['File', 'IsotropicDiscretePhoton', 'LegendreCoefficients', 'LegendreDistributions', 'Section', 'TabulatedDistribution', 'TabulatedDistributions']
class File:
    """
    MF14 file - angular distributions of secondary photons
    """
    @staticmethod
    def from_string(file: str) -> File:
        """
        Read the file from a string
        
        An exception is raised if something goes wrong while reading the
        file
        
        Arguments:
            file    the string representing the file
        """
    def MT(self, mt: int) -> Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    @typing.overload
    def __init__(self, sections: list[Section]) -> None:
        """
        Initialise the file
        
        Arguments:
            self       the file
            sections   the sections to be put into the file
        """
    @typing.overload
    def __init__(self, file: File) -> None:
        """
        Initialise the file with another file
        
        Arguments:
            self    the file
            file    the file to be copied
        """
    def has_MT(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def has_section(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def section(self, mt: int) -> Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    def to_string(self, mat: int) -> str:
        """
        The string representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    @property
    def MF(self) -> int:
        """
        The MF number of the file
        """
    @property
    def MTs(self) -> ...:
        """
        The sections defined in the file
        """
    @property
    def file_number(self) -> int:
        """
        The MF number of the file
        """
    @property
    def sections(self) -> ...:
        """
        The sections defined in the file
        """
class IsotropicDiscretePhoton:
    """
    MF14 section - the angular distribution for a specific discrete photon 
                   is isotropic
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> IsotropicDiscretePhoton:
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
    def __init__(self, energy: float, level: float) -> None:
        """
        Initialise the component
        
        Arguments:
            self     the component
            energy   the photon energy
            level    the energy of the level from which the photon originates
        """
    @typing.overload
    def __init__(self, component: IsotropicDiscretePhoton) -> None:
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
    def EG(self) -> float:
        """
        The photon energy
        """
    @property
    def ES(self) -> float:
        """
        The energy of the level from which the photon originates
        """
    @property
    def LAW(self) -> int:
        """
        The distribution law
        """
    @property
    def LI(self) -> bool:
        """
        The isotropic angular distribution flag
        """
    @property
    def LTT(self) -> int:
        """
        The distribution law
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def isotropic_distributions(self) -> bool:
        """
        The isotropic angular distribution flag
        """
    @property
    def level_energy(self) -> float:
        """
        The energy of the level from which the photon originates
        """
    @property
    def photon_energy(self) -> float:
        """
        The photon energy or the binding energy
        """
class LegendreCoefficients:
    """
    MF14 section - an angular distribution given as Legendre coefficients
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
            energy          the incident energy
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
        The Legendre coefficients in the distribution (a0 is not present and
        assumed to be equal to 1)
        """
    @property
    def E(self) -> float:
        """
        The incident energy for which the angular distribution is given
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NL(self) -> int:
        """
        The Legendre order for the angular distribution
        """
    @property
    def coefficients(self) -> ...:
        """
        The Legendre coefficients in the distribution (a0 is not present and
        assumed to be equal to 1)
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy for which the angular distribution is given
        """
    @property
    def legendre_order(self) -> int:
        """
        The Legendre order for the angular distribution
        """
class LegendreDistributions:
    """
    MF14 section - angular distributions as a function of incident energy
                   using Legendre coefficients (LTT=1) for a given discrete
                   photon
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> LegendreDistributions:
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
    def __init__(self, energy: float, level: float, boundaries: list[int], interpolants: list[int], distributions: list[LegendreCoefficients]) -> None:
        """
        Initialise the scattering radius
        
        Arguments:
            self             the component
            energy           the photon energy
            level            the energy of the level from which the photon
                             originates
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the sequence of angular distributions
        """
    @typing.overload
    def __init__(self, component: LegendreDistributions) -> None:
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
    def EG(self) -> float:
        """
        The photon energy
        """
    @property
    def ES(self) -> float:
        """
        The energy of the level from which the photon originates
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LAW(self) -> int:
        """
        The distribution law
        """
    @property
    def LI(self) -> bool:
        """
        The isotropic angular distribution flag
        """
    @property
    def LTT(self) -> int:
        """
        The distribution law
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
    def NE(self) -> int:
        """
        The number of incident energy values for which angular distributions
        are given
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def angular_distributions(self) -> ...:
        """
        The angular distributions (one for each incident energy)
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energies
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def isotropic_distributions(self) -> bool:
        """
        The isotropic angular distribution flag
        """
    @property
    def level_energy(self) -> float:
        """
        The energy of the level from which the photon originates
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def photon_energy(self) -> float:
        """
        The photon energy
        """
class Section:
    """
    MF14 section - angular distributions of secondary photons
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
    def __init__(self, mt: int, zaid: int, awr: float, nk: int) -> None:
        """
        Initialise the section for all isotropic photons
        
        Arguments:
            self   the section
            mt     the MT number
            zaid   the ZA  identifier
            awr    the atomic mass ratio
            nk     the total number of photons
        """
    @typing.overload
    def __init__(self, mt: int, zaid: int, awr: float, photons: list[IsotropicDiscretePhoton | LegendreDistributions | TabulatedDistributions]) -> None:
        """
        Initialise the section
        
        Arguments:
            self      the section
            mt        the MT number
            zaid      the ZA  identifier
            awr       the atomic mass ratio
            photons   the photon distribution data
        """
    @typing.overload
    def __init__(self, mt: int, zaid: int, awr: float, isotropic: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]], anisotropic: list[LegendreDistributions | TabulatedDistributions]) -> None:
        """
        Initialise the section
        
        Arguments:
            self          the section
            mt            the MT number
            zaid          the ZA  identifier
            awr           the atomic mass ratio
            isotropic     the photon and level energy for each isotropic photon
            anisotropic   the distribution data for the anisotropic photons
        """
    @typing.overload
    def __init__(self, mt: int, zaid: int, awr: float, energies: list[float], levels: list[float], anisotropic: list[LegendreDistributions | TabulatedDistributions]) -> None:
        """
        Initialise the section
        
        Arguments:
            self          the section
            mt            the MT number
            zaid          the ZA  identifier
            awr           the atomic mass ratio
            energies      the photon energy for each isotropic photon
            levels        the level energy for each isotropic photon
            anisotropic   the distribution data for the anisotropic photons
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
    def LAW(self) -> int:
        """
        The distribution law
        """
    @property
    def LI(self) -> bool:
        """
        The isotropic angular distribution flag
        """
    @property
    def LTT(self) -> int:
        """
        The distribution law
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
    def NI(self) -> int:
        """
        The number of photons with an isotropic angular distribution
        """
    @property
    def NK(self) -> int:
        """
        The number of photons (discrete and continuum) with angular distributions
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
    def isotropic_distributions(self) -> bool:
        """
        The isotropic angular distribution flag
        """
    @property
    def number_isotropic_photons(self) -> int:
        """
        The number of photons with an isotropic angular distribution
        """
    @property
    def number_photons(self) -> int:
        """
        The number of photons (discrete and continuum) with angular distributions
        """
    @property
    def photon_angular_distributions(self) -> list[IsotropicDiscretePhoton | LegendreDistributions | TabulatedDistributions]:
        """
        The secondary photons with their angular distribution
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
class TabulatedDistribution:
    """
    MF14 section - an angular distribution given as a tabulated function
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
    def __init__(self, energy: float, boundaries: list[int], interpolants: list[int], cosines: list[float], probabilities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            incident         the incident energy value
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            cosines          the cosine values
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
    def probabilities(self) -> ...:
        """
        The distribution probabilities
        """
class TabulatedDistributions:
    """
    MF4 section - angular distributions as a function of incident energy using
                  tabulated functions (LTT=2) for a given discrete photon
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> TabulatedDistributions:
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
    def __init__(self, energy: float, level: float, boundaries: list[int], interpolants: list[int], distributions: list[TabulatedDistribution]) -> None:
        """
        Initialise the scattering radius
        
        Arguments:
            self             the component
            energy           the photon energy
            level            the energy of the level from which the photon
                             originates
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the sequence of angular distributions
        """
    @typing.overload
    def __init__(self, component: TabulatedDistributions) -> None:
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
    def EG(self) -> float:
        """
        The photon energy
        """
    @property
    def ES(self) -> float:
        """
        The energy of the level from which the photon originates
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LAW(self) -> int:
        """
        The distribution law
        """
    @property
    def LI(self) -> bool:
        """
        The isotropic angular distribution flag
        """
    @property
    def LTT(self) -> int:
        """
        The distribution law
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
    def NE(self) -> int:
        """
        The number of incident energy values for which angular distributions
        are given
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def angular_distributions(self) -> ...:
        """
        The angular distributions (one for each incident energy)
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energies
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def isotropic_distributions(self) -> bool:
        """
        The isotropic angular distribution flag
        """
    @property
    def level_energy(self) -> float:
        """
        The energy of the level from which the photon originates
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values for which angular distributions
        are given
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def photon_energy(self) -> float:
        """
        The photon energy
        """
