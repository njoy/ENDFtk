"""
MF40 - covariances for radionuclide production
"""
import ENDFtk
from __future__ import annotations
import typing
__all__: list[str] = ['File', 'LevelBlock', 'Section']
class File:
    """
    MF40 file - covariances for radionuclide production
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
class LevelBlock:
    """
    MF40 section - a subsection of an MF40 section
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> LevelBlock:
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
    def __init__(self, qm: float, qi: float, izap: int, lfs: int, reactions: list[ENDFtk.ReactionBlock]) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the component
            qm            the mass difference Q-value
            qi            the reaction Q-value
            izap          the product identifier (ZA)
            lfs           the excited level of the product
            reactions     the reaction blocks
        """
    @typing.overload
    def __init__(self, component: LevelBlock) -> None:
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
    def IZAP(self) -> int:
        """
        the product ZA identifier
        """
    @property
    def LFS(self) -> int:
        """
        the level number of the product
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NL(self) -> int:
        """
        the number of reaction blocks
        """
    @property
    def QI(self) -> float:
        """
        the reaction Q-value
        """
    @property
    def QM(self) -> float:
        """
        the mass-difference Q-value
        """
    @property
    def excited_level(self) -> int:
        """
        the level number of the product
        """
    @property
    def mass_difference_q_value(self) -> float:
        """
        the mass-difference Q-value
        """
    @property
    def number_reactions(self) -> int:
        """
        the number of reaction blocks
        """
    @property
    def product_identifier(self) -> int:
        """
        the product ZA identifier
        """
    @property
    def reaction_blocks(self) -> ...:
        """
        the reaction blocks
        """
    @property
    def reaction_q_value(self) -> float:
        """
        the reaction Q-value
        """
class Section:
    """
    MF40 section - covariances for radionuclide production
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
    def __init__(self, mt: int, zaid: int, awr: float, lis: int, blocks: list[LevelBlock]) -> None:
        """
        Initialise the section
        
        Arguments:
            self       the section
            mt         the MT number
            zaid       the ZA  identifier
            awr        the atomic mass ratio
            lis        the level number of target
            blocks     the level blocks (subsections) (at least 1)
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
    def LIS(self) -> int:
        """
        the excited level number of the target
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
    def NS(self) -> int:
        """
        the number of level blocks (subsections)
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
    def excited_level(self) -> int:
        """
        the excited level number of the target
        """
    @property
    def level_blocks(self) -> ...:
        """
        the level blocks (subsections) defined in this section
        """
    @property
    def number_level_blocks(self) -> int:
        """
        the number of level blocks (subsections)
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
