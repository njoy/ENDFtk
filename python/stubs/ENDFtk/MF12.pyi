"""
MF12 - photon production multiplicities and transition probability arrays
"""
from __future__ import annotations
import typing
__all__: list[str] = ['File', 'Multiplicities', 'PartialMultiplicity', 'Section', 'TotalMultiplicity', 'TransitionProbabilities']
class File:
    """
    MF12 file - photon production multiplicities and transition probability
                arrays
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
class Multiplicities:
    """
    MF12 section - the energy dependence of the photon production cross
                   section is given as multiplicities
    """
    @typing.overload
    def __init__(self, partial: PartialMultiplicity) -> None:
        """
        Initialise the component (only one partial given, no total required)
        
        Arguments:
            self       the component
            partial    the partial multiplicity
        """
    @typing.overload
    def __init__(self, total: TotalMultiplicity, partials: list[PartialMultiplicity]) -> None:
        """
        Initialise the component (one total and multiple partials)
        
        Arguments:
            self        the component
            total       the total multiplicity
            partials    the partial multiplicities
        """
    @typing.overload
    def __init__(self, component: Multiplicities) -> None:
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
        The photon production representation type
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NK(self) -> int:
        """
        The the number of photons (discrete and continuum) with partial multiplicities
        """
    @property
    def number_photons(self) -> int:
        """
        The the number of photons (discrete and continuum) with partial multiplicities
        """
    @property
    def photon_partial_multiplicities(self) -> ...:
        """
        The partial multiplicities
        """
    @property
    def representation(self) -> int:
        """
        The photon production representation type
        """
    @property
    def total_multiplicity(self) -> TotalMultiplicity | None:
        """
        The total multiplicity (optional)
        """
class PartialMultiplicity:
    """
    MF12 section - a partial photon multiplicity (either for the continuum
                   or a discrete photon)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> PartialMultiplicity:
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
    def __init__(self, energy: float, level: float, lp: int, lf: int, boundaries: list[int], interpolants: list[int], energies: list[float], multiplicities: list[float]) -> None:
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
            multiplicities    the multiplicity values
        """
    @typing.overload
    def __init__(self, component: PartialMultiplicity) -> None:
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
    def Y(self) -> ...:
        """
        The multiplicity values
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
    def level_energy(self) -> float:
        """
        The energy of the level from which the photon originates
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
    MF12 section - photon production multiplicities and transition
                   probability arrays
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
    def __init__(self, mt: int, zaid: int, awr: float, production: Multiplicities | TransitionProbabilities) -> None:
        """
        Initialise the section
        
        Arguments:
            self          the section
            mt            the MT number for the section
            zaid          the material ZAID value
            awr           the atomic weight ratio
            production    the photon production data
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
        The data type for the photon production data
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
    def photon_production(self) -> Multiplicities | TransitionProbabilities:
        """
        The photon production data
        """
    @property
    def representation(self) -> int:
        """
        The data type for the photon production data
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
class TotalMultiplicity:
    """
    MF12 section - the total photon multiplicity
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> TotalMultiplicity:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], multiplicities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self              the component
            boundaries        the interpolation range boundaries
            interpolants      the interpolation types for each range
            energies          the energy values
            multiplicities    the multiplicity values
        """
    @typing.overload
    def __init__(self, component: TotalMultiplicity) -> None:
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
    def Y(self) -> ...:
        """
        The multiplicity values
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
class TransitionProbabilities:
    """
    MF12 section - photon production cross section are calculated from MF3
                   and the transition probabilities
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> TransitionProbabilities:
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
    def __init__(self, energy: float, energies: list[float], probabilities: list[float]) -> None:
        """
        Initialise the component (for the simple case, LG = 1)
        
        Arguments:
            self             the component
            energy           the highest energy level
            energies         the energy levels below the highest level
                             (NT values)
            probabilities    the transition probabilities (NT values)
        """
    @typing.overload
    def __init__(self, energy: float, energies: list[float], probabilities: list[float], conditionals: list[float]) -> None:
        """
        Initialise the component (for the complex case, LG = 2)
        
        Arguments:
            self             the component
            energy           the highest energy level
            energies         the energy levels below the highest level
                             (NT values)
            probabilities    the transition probabilities (NT values)
            conditionals     the conditional photon probabilities (NT values)
        """
    @typing.overload
    def __init__(self, component: TransitionProbabilities) -> None:
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
        The energy values
        """
    @property
    def ES(self) -> float:
        """
        The energy of the highest energy level
        """
    @property
    def GP(self) -> ...:
        """
        The conditional probabilities
        """
    @property
    def LG(self) -> int:
        """
        Whether the data is simple (pairs) or complex (triplets)
        """
    @property
    def LO(self) -> int:
        """
        The photon production representation type
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NT(self) -> int:
        """
        The number of transitions that are given
        """
    @property
    def TP(self) -> ...:
        """
        The transition probabilities
        """
    @property
    def conditional_probabilities(self) -> ...:
        """
        The conditional probabilities
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def highest_energy_level(self) -> float:
        """
        The energy of the highest energy level
        """
    @property
    def number_transitions(self) -> int:
        """
        The number of transitions that are given
        """
    @property
    def representation(self) -> int:
        """
        The photon production representation type
        """
    @property
    def transition_probabilities(self) -> ...:
        """
        The transition probabilities
        """
    @property
    def transition_type(self) -> int:
        """
        Whether the data is simple (pairs) or complex (triplets)
        """
