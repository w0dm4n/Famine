/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:05:22 by frmarinh          #+#    #+#             */
/*   Updated: 2017/07/01 18:07:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <stdio.h>
# include <locale.h>
# include <windows.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/includes/libft.h"
# include <stdarg.h>
# include <signal.h>

# define APP_ENV			"APPDATA"
# define TEMP_PATH			"\\Local\\Temp"
# define BACKSLASH			"\\"
# define DEBUG_MODE			"DEBUG"
# define bool				int
# define true				1
# define false				0
# define NO_FLAGS			0
# define EXIT_CODE			-1
# define MAGIC_LENGTH		2
# define DOS_MAGIC			"4D5A" // MZ - constant signature
# define PE_SIGNATURE		"4550" // soit "PE\0\0"
# define ARCHITECTURE_64	"20b" // 64b hex
# define SIGNATURE 			"frmarinh-jguyet"
# define STARTUP_VALUE		"Famine startup"
# define ARGS_STARTUP		" %DEBUG"

typedef __int32				int32_t;
typedef unsigned __int32	uint32_t;

#ifndef _WINDEF_
	# define _WINDEF_
	/*
	**	Variable type definition
	*/
	typedef unsigned long       DWORD;
	typedef int                 BOOL;
	typedef unsigned char       BYTE;
	typedef unsigned short      WORD;
	typedef float               FLOAT;
	typedef FLOAT               *PFLOAT;
	typedef BOOL near           *PBOOL;
	typedef BOOL far            *LPBOOL;
	typedef BYTE near           *PBYTE;
	typedef BYTE far            *LPBYTE;
	typedef int near            *PINT;
	typedef int far             *LPINT;
	typedef WORD near           *PWORD;
	typedef WORD far            *LPWORD;
	typedef long far            *LPLONG;
	typedef DWORD near          *PDWORD;
	typedef DWORD far           *LPDWORD;
	typedef void far            *LPVOID;
	typedef CONST void far      *LPCVOID;
	typedef void                *HANDLE;
	typedef int                 INT;
	typedef unsigned int        UINT;
	typedef unsigned int        *PUINT;
	typedef UINT_PTR            WPARAM;
	typedef LONG_PTR            LPARAM;
	typedef LONG_PTR            LRESULT;

	/*
	**	DOS Header
	*/
	typedef struct	_IMAGE_DOS_HEADER
	{
		WORD   e_magic;                     // Magic number
	    WORD   e_cblp;                      // Bytes on last page of file
	    WORD   e_cp;                        // Pages in file
	    WORD   e_crlc;                      // Relocations
	    WORD   e_cparhdr;                   // Size of header in paragraphs
	    WORD   e_minalloc;                  // Minimum extra paragraphs needed
	    WORD   e_maxalloc;                  // Maximum extra paragraphs needed
	    WORD   e_ss;                        // Initial (relative) SS value
	    WORD   e_sp;                        // Initial SP value
	    WORD   e_csum;                      // Checksum
	    WORD   e_ip;                        // Initial IP value
	    WORD   e_cs;                        // Initial (relative) CS value
	    WORD   e_lfarlc;                    // File address of relocation table
	    WORD   e_ovno;                      // Overlay number
	    WORD   e_res[4];                    // Reserved words
	    WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
	    WORD   e_oeminfo;                   // OEM information; e_oemid specific
	    WORD   e_res2[10];                  // Reserved words
	    LONG   e_lfanew;                    // File address of new exe header
	}				IMAGE_DOS_HEADER;

	/*
	**	Les répertoires sont des parties du fichier utilisées lors de son chargement.
	**	La position et la taille des données de ces répertoires sont indiquées.
	*/
	typedef struct			_IMAGE_DATA_DIRECTORY
	{
		DWORD				VirtualAddress;
		DWORD				Size;
	}						IMAGE_DATA_DIRECTORY;

	typedef struct		_IMAGE_FILE_HEADER
	{
	  WORD  			Machine;
	  WORD  			NumberOfSections;
	  DWORD 			TimeDateStamp;
	  DWORD 			PointerToSymbolTable;
	  DWORD 			NumberOfSymbols;
	  WORD  			SizeOfOptionalHeader;
	  WORD  			Characteristics;
  	}					IMAGE_FILE_HEADER;

	/*
	**	Optional information about PE
	*/
	typedef struct				_IMAGE_OPTIONAL_HEADER
	{
		WORD					Magic;
		UCHAR					MajorLinkerVersion;
		UCHAR					MinorLinkerVersion;
		ULONG					SizeOfCode;
		ULONG					SizeOfInitializedData;
		ULONG					SizeOfUninitializedData;
		ULONG					AddressOfEntryPoint;
		ULONG					BaseOfCode;
		ULONG					BaseOfData;
		ULONG					ImageBase;
		ULONG					SectionAlignment;
		ULONG					FileAlignment;
		WORD					MajorOperatingSystemVersion;
		WORD					MinorOperatingSystemVersion;
		WORD					MajorImageVersion;
		WORD					MinorImageVersion;
		WORD					MajorSubsystemVersion;
		WORD					MinorSubsystemVersion;
		ULONG					Win32VersionValue;
		ULONG					SizeOfImage;
		ULONG					SizeOfHeaders;
		ULONG					CheckSum;
		WORD					Subsystem;
		WORD					DllCharacteristics;
		ULONG					SizeOfStackReserve;
		ULONG					SizeOfStackCommit;
		ULONG					SizeOfHeapReserve;
		ULONG					SizeOfHeapCommit;
		ULONG					LoaderFlags;
		ULONG					NumberOfRvaAndSizes;
		IMAGE_DATA_DIRECTORY	DataDirectory[16];
	}							IMAGE_OPTIONAL_HEADER;

	/*
	**	La Table des Sections est située juste derrière l'en-tête PE. Il s'agit d'un tableau contenant plusieurs structures IMAGE_SECTION_HEADER.
	**	Ces structures contiennent les informations sur les sections du binaire devant être chargé en mémoire.
	*/
	typedef struct			_IMAGE_SECTION_HEADER
	{
	  BYTE					Name[IMAGE_SIZEOF_SHORT_NAME];
	  union {
	      DWORD PhysicalAddress;
	      DWORD VirtualSize;
	  } Misc;
	  DWORD					VirtualAddress;
	  DWORD					SizeOfRawData;
	  DWORD					PointerToRawData;
	  DWORD					PointerToRelocations;
	  DWORD					PointerToLinenumbers;
	  WORD					NumberOfRelocations;
	  WORD					NumberOfLinenumbers;
	  DWORD					Characteristics;
	}						IMAGE_SECTION_HEADER;

	/*
	**	PE Header
	*/
	typedef struct			_IMAGE_NT_HEADER
	{
  		DWORD                 	Signature;
  		IMAGE_FILE_HEADER     	FileHeader;
  		IMAGE_OPTIONAL_HEADER 	OptionalHeader;
	}						IMAGE_NT_HEADERS;
#endif

typedef struct		s_pe
{
	char				*name;
	char				*path;
	int					len;
	char				*buffer;
	char				*new_buffer;
	IMAGE_DOS_HEADER*	dos_header;
	IMAGE_NT_HEADERS*	pe_header;
}					t_pe;

typedef struct		s_famine
{
	char			*path;
	bool			debug;
	char			*executable_path;
	char			*buffer;
	int				buffer_len;
}					t_famine;

/*
**	MAIN
*/
void				close_console();
void				start_debug_console();

/*
**	UTILS
*/
void				*ft_mmap(int fd, size_t size);
void				print_message(t_famine *famine, char *message, bool leave);

/*
**	ASPRINTF
*/
int					vasprintf(char **, const char *, va_list);
int					asprintf(char **, const char *, ...);


/*
**	FAMINE
*/
void				init_famine(int, char**);

/*
**	INFECTION
*/
void				infect_folder(t_famine *famine, char *folder_name);

/*
**	ACCESS FILE
*/
struct stat			*check_access_file(char *file, t_famine *famine);

/*
**	READ PE
*/
t_pe				*pe(t_famine *famine, char *folder_path, char *file_name);

/*
**	REGISTERY
*/
void				startup_registery(t_famine *famine);
#endif
