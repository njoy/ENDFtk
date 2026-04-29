"""
MF6 - product energy-angle distributions
"""
from __future__ import annotations
import typing
from . import LAW1
from . import LAW2
from . import LAW5
from . import LAW7
__all__: list[str] = ['ChargedParticleElasticScattering', 'ContinuumEnergyAngle', 'DefinedElsewhere', 'DiscreteTwoBodyRecoils', 'DiscreteTwoBodyScattering', 'File', 'GSection', 'IsotropicDiscreteEmission', 'LAW1', 'LAW2', 'LAW5', 'LAW7', 'LaboratoryAngleEnergy', 'Multiplicity', 'NBodyPhaseSpace', 'ReactionProduct', 'Section', 'Unknown']
class ChargedParticleElasticScattering:
    """
    MF6 section - LAW=5 - charged particle elastic scattering
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ChargedParticleElasticScattering:
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
    def __init__(self, spin: float, lidp: int, boundaries: list[int], interpolants: list[int], distributions: list[LAW5.NuclearAmplitudeExpansion | LAW5.LegendreCoefficients | LAW5.NuclearPlusInterference]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            spin             the spin of the charged particle
            lidp             the identicle particle flag
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the data for each incident energy value
        """
    @typing.overload
    def __init__(self, component: ChargedParticleElasticScattering) -> None:
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
    def E(self) -> ...:
        """
        The incident energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LAW(self) -> int:
        """
        The distribution type (the LAW flag)
        """
    @property
    def LIDP(self) -> bool:
        """
        Whether or not the particles are identical
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
    def SPI(self) -> float:
        """
        The spin of the particle
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def distributions(self) -> ...:
        """
        The distributions
        """
    @property
    def identical_particles(self) -> bool:
        """
        Whether or not the particles are identical
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
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
    def spin(self) -> float:
        """
        The spin of the particle
        """
class ContinuumEnergyAngle:
    """
    MF6 section - LAW=1 - continuum energy-angle data for secondary particles
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ContinuumEnergyAngle:
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
    def __init__(self, lep: float, boundaries: list[int], interpolants: list[int], distributions: list[LAW1.LegendreCoefficients | LAW1.KalbachMann | LAW1.ThermalScatteringData | LAW1.TabulatedDistribution]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            lep              the secondary energy interpolation scheme
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the data for each incident energy value
        """
    @typing.overload
    def __init__(self, component: ContinuumEnergyAngle) -> None:
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
    def E(self) -> ...:
        """
        The incident energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LAW(self) -> int:
        """
        The distribution type (the LAW flag)
        """
    @property
    def LEP(self) -> int:
        """
        The interpolation scheme for secondary energies
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
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def distributions(self) -> ...:
        """
        The distributions
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def interpolation_scheme(self) -> int:
        """
        The interpolation scheme for secondary energies
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
class DefinedElsewhere:
    """
    MF6 section - LAW<0 - the distributions are defined elsewhere and no
                          data is given
    """
    @typing.overload
    def __init__(self, arg0: int) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the component
            law     the law number to be used (-4, -5, -14, -15 only)
        """
    @typing.overload
    def __init__(self, component: DefinedElsewhere) -> None:
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
        The distribution type (the LAW flag)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
class DiscreteTwoBodyRecoils:
    """
    MF6 section - LAW=4 - the energy and angular distribution can be
                          determined from kinematics and no data is given
    """
    @typing.overload
    def __init__(self) -> None:
        """
        Initialise the component
        
        Arguments:
            self              the component
        """
    @typing.overload
    def __init__(self, component: DiscreteTwoBodyRecoils) -> None:
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
        The distribution type (the LAW flag)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
class DiscreteTwoBodyScattering:
    """
    MF6 section - LAW=2 - discrete two-body scattering data
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> DiscreteTwoBodyScattering:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], distributions: list[LAW2.LegendreCoefficients | LAW2.TabulatedDistribution]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the data for each incident energy value
        """
    @typing.overload
    def __init__(self, component: DiscreteTwoBodyScattering) -> None:
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
    def E(self) -> ...:
        """
        The incident energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LAW(self) -> int:
        """
        The distribution type (the LAW flag)
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
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def distributions(self) -> ...:
        """
        The distributions
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
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
class File:
    """
    MF6 file - product energy-angle distributions
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
class GSection:
    """
    MF6 gsection - scattering matrices and fission matrices
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
    def __init__(self, mt: int, zaid: int, awr: float, lr: int = 0, ngn: int, temp: float, flux: list[list[list[float]]], matrix: list[list[list[list[float]]]], cutoff_ig: int, chi: list[list[float]]) -> None:
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
           matrix      4D array of cross-sections ( nl, nz, ngn, ngn )
        """
    @typing.overload
    def __init__(self, mt: int, zaid: int, awr: float, lr: int = 0, ngn: int, temp: float, flux: list[list[list[float]]], matrix: list[list[list[list[float]]]]) -> None:
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
           matrix      4D array of cross-sections ( nl, nz, ngn, ngn )
        """
    @typing.overload
    def __init__(self, gsection: GSection) -> None:
        """
        Initialise the gsection with another gsection
        
        Arguments:
            self       the gsection
            section    the gsection to be copied
        """
    def chi(self, dilution: int) -> list[float]:
        """
        The prompt fission spectrum for a given dilution
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
    def break_up(self) -> int:
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
class IsotropicDiscreteEmission:
    """
    MF6 section - LAW=3 - the angular distribution is isotropic in CM and
                          no data is given
    """
    @typing.overload
    def __init__(self) -> None:
        """
        Initialise the component
        
        Arguments:
            self              the component
        """
    @typing.overload
    def __init__(self, component: IsotropicDiscreteEmission) -> None:
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
        The distribution type (the LAW flag)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
class LaboratoryAngleEnergy:
    """
    MF6 section - LAW=7 - distributions are given in the E,mu,E' ordering
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> LaboratoryAngleEnergy:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], distributions: list[LAW7.AngularDistribution]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the secondary energy distributions
        """
    @typing.overload
    def __init__(self, component: LaboratoryAngleEnergy) -> None:
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
    def E(self) -> ...:
        """
        The incident energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LAW(self) -> int:
        """
        The distribution type (the LAW flag)
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
        The angular distributions
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
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
class Multiplicity:
    """
    MF6 section - reaction product multiplicity
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> Multiplicity:
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
    def __init__(self, zap: int, awp: float, lip: int, law: int, boundaries: list[int], interpolants: list[int], energies: list[float], multiplicities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self              the component
            zap               the ZAID value for the reaction product
            awp               the atomic weight ratio for the reaction
                              product
            lip               the product modifier flag
            law               the distribution type
            boundaries        the interpolation range boundaries
            interpolants      the interpolation types for each range
            energies          the x values
            multiplicities    the function values
        """
    @typing.overload
    def __init__(self, component: Multiplicity) -> None:
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
    def AWP(self) -> float:
        """
        The atomic weight ratio of the reaction product
        """
    @property
    def E(self) -> ...:
        """
        The incident energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LAW(self) -> int:
        """
        The distribution type (the LAW flag)
        """
    @property
    def LIP(self) -> int:
        """
        The product modifier flag
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
    def Y(self) -> ...:
        """
        The multiplicity values
        """
    @property
    def ZAP(self) -> int:
        """
        The ZA identifier of the reaction product
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def multiplicities(self) -> ...:
        """
        The multiplicity values
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
    def product_identifier(self) -> int:
        """
        The ZA identifier of the reaction product
        """
    @property
    def product_modifier_flag(self) -> int:
        """
        The product modifier flag
        """
    @property
    def product_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the reaction product
        """
class NBodyPhaseSpace:
    """
    MF6 section - LAW=6 - a simplified distribution for neutron and charged
                           particles
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> NBodyPhaseSpace:
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
    def __init__(self, apsx: float, npsx: int) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the component
            apsx    the particle mass (in neutron mass units)
            npsx    the number of particles
        """
    @typing.overload
    def __init__(self, component: NBodyPhaseSpace) -> None:
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
    def APSX(self) -> float:
        """
        The total mass of all particles (in neutron mass units)
        """
    @property
    def LAW(self) -> int:
        """
        The distribution type (the LAW flag)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NPSX(self) -> int:
        """
        The number of particles
        """
    @property
    def number_particles(self) -> int:
        """
        The number of particles
        """
    @property
    def total_mass(self) -> float:
        """
        The total mass of all particles (in neutron mass units)
        """
class ReactionProduct:
    """
    MF6 section - a reaction product with multiplicity and distribution data
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ReactionProduct:
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
    def __init__(self, multiplicity: Multiplicity, distribution: DefinedElsewhere | Unknown | ContinuumEnergyAngle | DiscreteTwoBodyScattering | IsotropicDiscreteEmission | DiscreteTwoBodyRecoils | ChargedParticleElasticScattering | NBodyPhaseSpace | LaboratoryAngleEnergy) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            multiplicity    the multiplicity
            distribution    the distribution
        """
    @typing.overload
    def __init__(self, component: ReactionProduct) -> None:
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
    def AWP(self) -> float:
        """
        The atomic weight ratio of the reaction product
        """
    @property
    def LAW(self) -> int:
        """
        The distribution type (the LAW flag)
        """
    @property
    def LIP(self) -> int:
        """
        The product modifier flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def ZAP(self) -> int:
        """
        The ZA identifier of the reaction product
        """
    @property
    def distribution(self) -> DefinedElsewhere | Unknown | ContinuumEnergyAngle | DiscreteTwoBodyScattering | IsotropicDiscreteEmission | DiscreteTwoBodyRecoils | ChargedParticleElasticScattering | NBodyPhaseSpace | LaboratoryAngleEnergy:
        """
        The distribution
        """
    @property
    def multiplicity(self) -> Multiplicity:
        """
        The multiplicity
        """
    @property
    def product_identifier(self) -> int:
        """
        The ZA identifier of the reaction product
        """
    @property
    def product_modifier_flag(self) -> int:
        """
        The product modifier flag
        """
    @property
    def product_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the reaction product
        """
class Section:
    """
    MF6 section - product energy-angle distributions
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
    def __init__(self, mt: int, zaid: int, awr: float, jp: int, lct: int, products: list[ReactionProduct]) -> None:
        """
        Initialise the section
        
        Arguments:
            self        the section
            mt          the MT number
            zaid        the ZA  identifier
            awr         the atomic mass ratio
            jp          the particle spectrum type flag
            lct         the reference frame
            products    the reaction products (at least 1)
        """
    @typing.overload
    def __init__(self, section: Section) -> None:
        """
        Initialise the section with another section
        
        Arguments:
            self       the section
            section    the section to be copied
        """
    def has_reaction_product(self, zap: int) -> bool:
        """
        Return whether or not the reaction product is present
        
        Arguments:
            self   the section
            zap    the reaction product to retrieve
        """
    def reaction_product(self, zap: int) -> ReactionProduct:
        """
        Return the requested reaction product
        
        Arguments:
            self   the section
            zap    the reaction product to retrieve
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
    def JP(self) -> int:
        """
        The particle spectrum type flag
        """
    @property
    def LCT(self) -> int:
        """
        The reference frame (LAB or CM)
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
    def NK(self) -> int:
        """
        The number of reaction products
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
    def average_multiple_particles_flag(self) -> int:
        """
        The particle spectrum type flag
        """
    @property
    def number_reaction_products(self) -> int:
        """
        The number of reaction products
        """
    @property
    def reaction_products(self) -> ...:
        """
        The reaction products defined in this section
        """
    @property
    def reference_frame(self) -> int:
        """
        The reference frame (LAB or CM)
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
class Unknown:
    """
    MF6 section - LAW=0 - the distribution is unknown and no data is given
    """
    @typing.overload
    def __init__(self) -> None:
        """
        Initialise the component
        
        Arguments:
            self              the component
        """
    @typing.overload
    def __init__(self, component: Unknown) -> None:
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
        The distribution type (the LAW flag)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
