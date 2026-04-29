"""
MF35 - covariances for energy distributions
"""
from __future__ import annotations
import typing
__all__: list[str] = ['File', 'Section', 'SquareMatrix']
class File:
    """
    MF35 file - covariances for angular distributions
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
    MF35 section - covariances of energy distributions
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
    def __init__(self, mt: int, zaid: int, awr: float, blocks: list[SquareMatrix]) -> None:
        """
        Initialise the section
        
        Arguments:
            self        the section
            mt          the MT number
            zaid        the ZA  identifier
            awr         the atomic mass ratio
            blocks      the energy block subsections (at least 1)
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
        the number of energy blocks (subsections)
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
    def energy_blocks(self) -> ...:
        """
        the energy blocks (subsections) defined in this section
        """
    @property
    def number_energy_blocks(self) -> int:
        """
        the number of energy blocks (subsections)
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
class SquareMatrix:
    """
    MF35 section - energy block (subsection) given as a square matrix
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> SquareMatrix:
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
    def __init__(self, e1: float, e2: float, energies: list[float], values: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            e1             lowest incident energy
            e2             highest incident energy
            energies       energies
            values         matrix values
        """
    @typing.overload
    def __init__(self, component: SquareMatrix) -> None:
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
    def E1(self) -> int:
        """
        the lowest incident energy
        """
    @property
    def E2(self) -> int:
        """
        the highest incident energy
        """
    @property
    def LB(self) -> int:
        """
        the procedure
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NE(self) -> int:
        """
        the number of energies in the array
        """
    @property
    def NT(self) -> int:
        """
        the number of values in this component
        """
    @property
    def energies(self) -> ...:
        """
        the energy values
        """
    @property
    def highest_energy(self) -> int:
        """
        the highest incident energy
        """
    @property
    def lowest_energy(self) -> int:
        """
        the lowest incident energy
        """
    @property
    def number_energies(self) -> int:
        """
        the number of energies in the array
        """
    @property
    def number_values(self) -> int:
        """
        the number of values in this component
        """
    @property
    def procedure(self) -> int:
        """
        the procedure
        """
    @property
    def values(self) -> ...:
        """
        the matrix values
        """
