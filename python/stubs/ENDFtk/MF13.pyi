"""
MF13 - photon production cross sections
"""
from __future__ import annotations
import typing
__all__: list[str] = ['File', 'PartialCrossSection', 'Section', 'TotalCrossSection']
class File:
    """
    MF13 file - photon production cross sections
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
class PartialCrossSection:
    """
    MF13 section - a partial photon cross section (either for the continuum
                   or a discrete photon)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> PartialCrossSection:
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
    def __init__(self, energy: float, level: float, lp: int, lf: int, boundaries: list[int], interpolants: list[int], energies: list[float], xs: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self              the component
            energy            the photon or binding energy
            level             the energy of the level from which the photon
                              originates
            lp                the primary photon flag (0, 1 or 2)
            lf                the photon energy distribution law
            boundaries        the interpolation range boundaries
            interpolants      the interpolation types for each range
            energies          the energy values
            xs                the cross section values
        """
    @typing.overload
    def __init__(self, component: PartialCrossSection) -> None:
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
    def EG(self) -> float:
        """
        The photon energy or the binding energy
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
        The photon energy distribution law number
        """
    @property
    def LF(self) -> int:
        """
        The photon energy distribution law number
        """
    @property
    def LP(self) -> int:
        """
        The primary photon flag value
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
    def XS(self) -> ...:
        """
        The cross section values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def cross_sections(self) -> ...:
        """
        The cross section values
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
    def number_points(self) -> int:
        """
        The number of points
        """
    @property
    def photon_or_binding_energy(self) -> float:
        """
        The photon energy or the binding energy
        """
    @property
    def primary_photon_flag(self) -> int:
        """
        The primary photon flag value
        """
class Section:
    """
    MF13 section - photon production cross sections
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
    def __init__(self, mt: int, zaid: int, awr: float, partial: PartialCrossSection) -> None:
        """
        Initialise the component (only one partial given, no total required)
        
        Arguments:
            self       the section
            mt         the MT number for the section
            zaid       the material ZAID value
            awr        the atomic weight ratio
            partial    the partial cross section
        """
    @typing.overload
    def __init__(self, mt: int, zaid: int, awr: float, total: TotalCrossSection, partials: list[PartialCrossSection]) -> None:
        """
        Initialise the component (one total and multiple partials)
        
        Arguments:
            self        the section
            mt          the MT number for the section
            zaid        the material ZAID value
            awr         the atomic weight ratio
            total       the total cross section
            partials    the partial cross sections
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
        The number of photons (discrete and continuum) with partial cross sections
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
    def number_photons(self) -> int:
        """
        The number of photons (discrete and continuum) with partial cross sections
        """
    @property
    def photon_partial_cross_sections(self) -> ...:
        """
        The partial cross sections
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
    def total_cross_section(self) -> TotalCrossSection | None:
        """
        The total cross section (optional)
        """
class TotalCrossSection:
    """
    MF13 section - the total photon production cross section
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> TotalCrossSection:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], xs: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self              the component
            boundaries        the interpolation range boundaries
            interpolants      the interpolation types for each range
            energies          the energy values
            xs                the cross section values
        """
    @typing.overload
    def __init__(self, component: TotalCrossSection) -> None:
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
    def XS(self) -> ...:
        """
        The cross section values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def cross_sections(self) -> ...:
        """
        The cross section values
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
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_points(self) -> int:
        """
        The number of points
        """
