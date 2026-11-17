"""
MF28 - atomic relaxation data
"""
from __future__ import annotations
import typing
__all__: list[str] = ['File', 'Section', 'SubshellData']
class File:
    """
    MF28 file - atomic relaxation data
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
class Section:
    """
    MF28 section - atomic relaxation data
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
    def __init__(self, mt: int, zaid: int, awr: float, subshells: list[SubshellData]) -> None:
        """
        Initialise the section
        
        Arguments:
            self        the section
            mt          the MT number
            zaid        the material ZAID value
            awr         the atomic weight ratio
            subshells   the subshell data
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
    def NSS(self) -> int:
        """
        The number of subshells
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
    def number_subshells(self) -> int:
        """
        The number of subshells
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def subshells(self) -> ...:
        """
        The subshell data
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
class SubshellData:
    """
    MF28 component - transition energies and probabilities for a given subshell
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> SubshellData:
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
    def __init__(self, subshell: int, energy: float, eln: float) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            subshell        the subshell designator
            energy          the binding energy of the subshell
            eln             the number of electrons in the subshell
        """
    @typing.overload
    def __init__(self, subshell: int, energy: float, eln: float, secondary: list[int], tertiary: list[int], energies: list[float], probabilities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            subshell        the subshell designator
            energy          the binding energy of the subshell
            eln             the number of electrons in the subshell
            secondary       the secondary subshell designators (NTR values)
            tertiary        the tertiary subshell designators (NTR values)
            energies        the transition energies (NTR values)
            probabilities   the transition probabilities (NTR values)
        """
    @typing.overload
    def __init__(self, component: SubshellData) -> None:
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
    def EBI(self) -> float:
        """
        The subshell binding energy
        """
    @property
    def ELN(self) -> float:
        """
        The number of electrons in the subshell
        """
    @property
    def ETR(self) -> ...:
        """
        The transition energies
        """
    @property
    def FTR(self) -> ...:
        """
        The transition probabilities
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NTR(self) -> int:
        """
        The number of transitions
        """
    @property
    def SUBI(self) -> int:
        """
        The subshell designator
        """
    @property
    def SUBJ(self) -> ...:
        """
        The secondary subshell designators (one for each transition)
        """
    @property
    def SUBK(self) -> ...:
        """
        The tertiary subshell designators (one for each transition)
        """
    @property
    def number_subshell_electrons(self) -> float:
        """
        The number of electrons in the subshell
        """
    @property
    def number_transitions(self) -> int:
        """
        The number of transitions
        """
    @property
    def secondary_subshell_designators(self) -> ...:
        """
        The secondary subshell designators (one for each transition)
        """
    @property
    def subshell_binding_energy(self) -> float:
        """
        The subshell binding energy
        """
    @property
    def subshell_designator(self) -> int:
        """
        The subshell designator
        """
    @property
    def tertiary_subshell_designators(self) -> ...:
        """
        The tertiary subshell designators (one for each transition)
        """
    @property
    def transition_energies(self) -> ...:
        """
        The transition energies
        """
    @property
    def transition_probabilities(self) -> ...:
        """
        The transition probabilities
        """
