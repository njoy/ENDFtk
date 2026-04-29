"""
MF26 - secondary distributions for photo- and electro-atomic interactions
"""
from __future__ import annotations
import typing
from . import LAW1
from . import LAW2
__all__: list[str] = ['ContinuumEnergyAngle', 'DiscreteTwoBodyScattering', 'EnergyTransfer', 'File', 'LAW1', 'LAW2', 'Multiplicity', 'ReactionProduct', 'Section']
class ContinuumEnergyAngle:
    """
    MF26 section - LAW=1 - continuum energy-angle data for secondary particles
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
    def __init__(self, lep: float, boundaries: list[int], interpolants: list[int], distributions: list[LAW1.LegendreCoefficients]) -> None:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], distributions: list[LAW2.TabulatedDistribution]) -> None:
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
class EnergyTransfer:
    """
    MF6 section - LAW=8 - only energy transfer during electro-atomic excitation
                          or bremsstrahlung is given
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> EnergyTransfer:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], transfer: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            transfer        the energy transfer values
        """
    @typing.overload
    def __init__(self, component: EnergyTransfer) -> None:
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
    def ET(self) -> ...:
        """
        The energy transfer values
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
    def energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def energy_transfer_values(self) -> ...:
        """
        The energy transfer values
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
class File:
    """
    MF26 file - secondary distributions for photo- and electro-atomic interactions
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
class Multiplicity:
    """
    MF26 section - multiplicity for a photon or electron
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
    def __init__(self, zap: int, awi: float, law: int, boundaries: list[int], interpolants: list[int], energies: list[float], multiplicities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self              the component
            zap               the ZAID value for the reaction product
            awi               the atomic weight ratio for the projectile
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
    def AWI(self) -> float:
        """
        The atomic weight ratio of the projectile
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
    def product_identifier(self) -> float:
        """
        The ZA identifier of the reaction product
        """
    @property
    def projectile_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the projectile
        """
class ReactionProduct:
    """
    MF26 section - a reaction product with multiplicity and distribution data
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
    def __init__(self, multiplicity: Multiplicity, distribution: ContinuumEnergyAngle | DiscreteTwoBodyScattering | EnergyTransfer) -> None:
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
    def AWI(self) -> float:
        """
        The atomic weight ratio of the projectile
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
    def ZAP(self) -> int:
        """
        The ZA identifier of the reaction product
        """
    @property
    def distribution(self) -> ContinuumEnergyAngle | DiscreteTwoBodyScattering | EnergyTransfer:
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
    def projectile_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the projectile
        """
class Section:
    """
    MF26 section - secondary distributions for photo- and electro-atomic interactions
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
    def __init__(self, mt: int, zaid: int, awr: float, products: list[ReactionProduct]) -> None:
        """
        Initialise the section
        
        Arguments:
            self        the section
            mt          the MT number
            zaid        the ZA  identifier
            awr         the atomic mass ratio
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
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
