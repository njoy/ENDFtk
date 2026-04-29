"""
MT451 - descriptive data and directory
"""
import ENDFtk
from __future__ import annotations
import typing
__all__: list[str] = ['GSection', 'Section']
class GSection:
    """
    MF1 MT451 gsection - descriptive data and directory
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
    def __init__(self, zaid: int, awr: float, temp: float, sigz: list[float], egn: list[float], egg: list[float]) -> None:
        """
        Initialise the section
        
        Arguments:
            self           the section
            zaid           the ZA value of the material
            awr            the atomic weight ratio
            temp           the temperature
            sigz           the dilution values
            egn            the neutron group structure
            egg            the photon group structure
        """
    @typing.overload
    def __init__(self, gsection: GSection) -> None:
        """
        Initialise the gsection with another gsection
        
        Arguments:
            self       the gsection
            section    the gsection to be copied
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
    def EGG(self) -> ...:
        """
        The photon group structure
        """
    @property
    def EGN(self) -> ...:
        """
        The neutron group structure
        """
    @property
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NGG(self) -> int:
        """
        The number of photon groups
        """
    @property
    def NGN(self) -> int:
        """
        The number of neutron groups
        """
    @property
    def NZ(self) -> int:
        """
        The number of dilutions
        """
    @property
    def SIGZ(self) -> ...:
        """
        The dilution values
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
    def dilutions(self) -> ...:
        """
        The dilution values
        """
    @property
    def neutron_structure(self) -> ...:
        """
        The neutron group structure
        """
    @property
    def number_dilutions(self) -> int:
        """
        The number of dilutions
        """
    @property
    def number_neutron_groups(self) -> int:
        """
        The number of neutron groups
        """
    @property
    def number_photon_groups(self) -> int:
        """
        The number of photon groups
        """
    @property
    def photon_structure(self) -> ...:
        """
        The photon group structure
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
class Section:
    """
    MF1 MT451 section - descriptive data and directory
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
    def __init__(self, zaid: int, awr: float, lrp: int, lfi: int, nlib: int, nmod: int, elis: float, sta: float, lis: int, liso: int, nfor: int, awi: float, emax: float, lrel: int, nsub: int, nver: int, temp: float, ldrv: int, description: str, index: list[ENDFtk.DirectoryRecord], rtol: float = 0.0) -> None:
        """
        Initialise the section
        
        Arguments:
            self           the section
            zaid           the ZA value of the material
            awr            the atomic weight ratio
            lrp            the resonance parameter flag
            lfi            the fissile flag
            nlib           the library type
            nmod           the modification number
            elis           the excitation energy
            sta            the stability flag (whether or not the nuclide is unstable)
            lis            the excited level number
            liso           the isomeric state number
            nfor           the library format version number
            awi            the atomic weight ratio of the incident particle
            emax           the maximum incident energy
            lrel           the release number
            nsub           the sublibrary number
            nver           the version number
            temp           the temperature
            ldrv           the derived material flag
            description    the descriptive information
            index          the index
            rtol           the reconstruction tolerance (internal NJOY value)
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
    def AWI(self) -> float:
        """
        The atomic weight ratio of the incident particle
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def ELIS(self) -> float:
        """
        The excitation energy
        """
    @property
    def EMAX(self) -> float:
        """
        The maximum incident energy
        """
    @property
    def LDRV(self) -> int:
        """
        The derived material flag
        """
    @property
    def LFI(self) -> int:
        """
        The fissile flag
        """
    @property
    def LIS(self) -> int:
        """
        The excited level number
        """
    @property
    def LISO(self) -> int:
        """
        The isomeric state number
        """
    @property
    def LREL(self) -> int:
        """
        The release number
        """
    @property
    def LRP(self) -> int:
        """
        The resonance parameter flag
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
    def NFOR(self) -> int:
        """
        The library format version number
        """
    @property
    def NLIB(self) -> int:
        """
        The library type
        """
    @property
    def NMOD(self) -> int:
        """
        The modification number
        """
    @property
    def NSUB(self) -> int:
        """
        The sublibrary number
        """
    @property
    def NVER(self) -> int:
        """
        The version number
        """
    @property
    def NWD(self) -> int:
        """
        The number of lines of descriptive data
        """
    @property
    def NXC(self) -> int:
        """
        The number of index entries
        """
    @property
    def RTOL(self) -> float:
        """
        The reconstruction tolerance
        """
    @property
    def STA(self) -> float:
        """
        The stability flag
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
    def derived_material(self) -> int:
        """
        The derived material flag
        """
    @property
    def description(self) -> str:
        """
        The descriptive information
        """
    @property
    def excitation_energy(self) -> float:
        """
        The excitation energy
        """
    @property
    def excited_level(self) -> int:
        """
        The excited level number
        """
    @property
    def index(self) -> ...:
        """
        The index
        """
    @property
    def is_fissile(self) -> bool:
        """
        The fissile flag
        """
    @property
    def is_stable(self) -> bool:
        """
        Flag to indicate whether or not the nuclide is stable
        """
    @property
    def is_unstable(self) -> bool:
        """
        Flag to indicate whether or not the nuclide is unstable
        """
    @property
    def isomeric_level(self) -> int:
        """
        The isomeric state number
        """
    @property
    def library_format(self) -> int:
        """
        The library format version number
        """
    @property
    def library_type(self) -> int:
        """
        The library type
        """
    @property
    def maximum_energy(self) -> float:
        """
        The maximum incident energy
        """
    @property
    def modification_number(self) -> int:
        """
        The modification number
        """
    @property
    def projectile_atomic_mass_ratio(self) -> float:
        """
        The atomic weight ratio of the incident particle
        """
    @property
    def reconstruction_tolerance(self) -> float:
        """
        The reconstruction tolerance
        """
    @property
    def release_number(self) -> int:
        """
        The release number
        """
    @property
    def resonance_parameter_flag(self) -> int:
        """
        The resonance parameter flag
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def sublibrary(self) -> int:
        """
        The sublibrary number
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
    @property
    def version_number(self) -> int:
        """
        The version number
        """
