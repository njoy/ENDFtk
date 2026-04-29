"""
MF4 - angular distributions of secondary particles
"""
from __future__ import annotations
import typing
__all__: list[str] = ['File', 'Isotropic', 'LegendreCoefficients', 'LegendreDistributions', 'MixedDistributions', 'Section', 'TabulatedDistribution', 'TabulatedDistributions']
class File:
    """
    MF4 file - angular distributions of secondary particles
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
class Isotropic:
    """
    MF4 section - the angular distributions are all isotropic
    """
    @typing.overload
    def __init__(self) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the component
        """
    @typing.overload
    def __init__(self, component: Isotropic) -> None:
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
    def isotropic_angular_distributions(self) -> bool:
        """
        The isotropic angular distribution flag
        """
class LegendreCoefficients:
    """
    MF4 section - an angular distribution given as Legendre coefficients
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
    MF4 section - angular distributions as a function of incident energy
                  using Legendre coefficients (LTT=1)
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
    def __init__(self, boundaries: list[int], interpolants: list[int], distributions: list[LegendreCoefficients]) -> None:
        """
        Initialise the scattering radius
        
        Arguments:
            self             the component
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
        The number of incident energy values
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
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
class MixedDistributions:
    """
    MF4 section - the angular distributions are mixed (Legendre coefficients
                  and tabulated distributions)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> MixedDistributions:
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
    def __init__(self, legendre: LegendreDistributions, tabulated: TabulatedDistributions) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            legendre         the legendre distributions
            tabulated        the tabulated distributions
        """
    @typing.overload
    def __init__(self, component: MixedDistributions) -> None:
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
        The number of incident energy values
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
    def legendre(self) -> LegendreDistributions:
        """
        The Legendre distributions
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def tabulated(self) -> TabulatedDistributions:
        """
        The tabulated distributions
        """
class Section:
    """
    MF4 section - angular distributions of secondary particles
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
    def __init__(self, mt: int, zaid: int, awr: float, lct: int, distributions: Isotropic | LegendreDistributions | TabulatedDistributions | MixedDistributions) -> None:
        """
        Initialise the section
        
        Arguments:
            self             the section
            mt               the MT number
            zaid             the ZA  identifier
            awr              the atomic mass ratio
            lct              the reference frame
            distributions    the distributions
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
    def LCT(self) -> int:
        """
        The reference frame
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
    def NBT(self) -> ...:
        """
        The interpolation boundaries
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
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def ZA(self) -> int:
        """
        The ZA identifier for the section
        """
    @property
    def angular_distributions(self) -> ...:
        """
        The angular distributions (one for each incident energy)
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def distributions(self) -> Isotropic | LegendreDistributions | TabulatedDistributions | MixedDistributions:
        """
        The partial distributions defined in this section
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
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def reference_frame(self) -> int:
        """
        The reference frame
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
    MF4 section - an angular distribution given as a tabulated function
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
            energy           the incident energy value
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
                  tabulated functions (LTT=2)
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
    def __init__(self, boundaries: list[int], interpolants: list[int], distributions: list[TabulatedDistribution]) -> None:
        """
        Initialise the scattering radius
        
        Arguments:
            self             the component
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
        The number of incident energy values
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
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
