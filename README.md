# External Sorting

## General information
The program implements the **external sorting methods** in order to sort a set of records too big to store in memory and thus stored in an external file.

## Goal
The project's goal is to demonstrate the external sorting alghorithms. The program is **not** written as a general utility that enables you to sort set of any kind of records, because of the imposed format of the record. Although the door to generalize the problem was left open and it is highly possible that the project will be refactored in the future so that it will allow sorting of a file containing any kind of records.

## Setup notes
1. Clone or download the repository.
2. To build the solution, either you'll need to open the project directly in Visual Studio IDE or use the `devenv` command line tool shipped with Microsoft Windows SDK. In order to use this tool to build the project, open the Visual Studio Developer Command Prompt and type `devenv /build Debug PATH_TO_SLN_FILE`.

## Usage

### Command line options
| Short option | Long option      | Argument      | Description                                                                                                 |
|--------------|------------------|---------------|-------------------------------------------------------------------------------------------------------------|
| `-r`         | `--random`       |               | Randomly generates input file.                                                                              |
| `-f`         | `--file`         | `[FILE_PATH]` | By supplying this option, the user is allowed to specify a path to the binary input file.                   |
| `-u`         | `--user`         |               | Guides user through the process of typing the records with the keyboard.                                    |
| `-s`         | `--step-by-step` |               | Lets user go through sorting step by step. This option also sets maximum verbosity.                         |
| `-v`         | `--verbose`      |               | Sets maximum verbosity level. This means displaying each tape during the sorting process.                   |
| `-t`         | `--tapes`        | `[TAPES_NUM]` | Sets the number of tapes used in distribution phase. Default is 2.                                          |
| `-b`         | `--buffer`       | `[BUFF_SIZE]` | Sets the buffer size in bytes. The buffer size must be divisible by the record byte length. Default is ??B. |
| `-h`         | `--help`         |               | Outputs help message.                                                                                       |
If none of the flags `-r`, `-f` and `-u` is specified, the input is generated randomly just as if `-r` flag was provided.

## Input data

### File format

Input file should be a raw binary file containing the **database of the records**. See [record information](###Records) on more on how each record should be composed.
If you are using `-f` option and supplying your hand-generated file, please make sure your file is prepared correctly.

### Records
The assumption is made that the single record is the 2D vector. Therefore each record in the binary file should be a pair of 4-byte long integers. This implies that the **byte length of the file should be divisible by 8**, since each record should be exactly 8-byte long.

### Sample input data
Sample input files can be found in [input subdirectory](sorting/input) of the project.

## Sorting

### Sorting methods

* Natural merge sort
* Polyphase merge sort - *to be implemented in the future*

### Sorting criteria
As for now the sorting criteria is fixed to be the euclidian norm of the vector.

