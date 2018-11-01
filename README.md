# External Sorting

## General information
This program implements the external sorting methods in order to sort a set of records stored in an external file. In this case, the external file contains the database of records, each of which is a 2-dimensional vector.
The database needs to be sorted by comparing the length of vectors.

## Usage

### Command line options

| short version    | long version         | meaning                                                                                   |
|------------------|----------------------|-------------------------------------------------------------------------------------------|
| `-r`             | `--random`           | Randomly generates input file.                                                            |
| `-f [FILE_PATH]` | `--file [FILE_PATH]` | By supplying this option, the user is allowed to specify a path to the binary input file. |
| `-u`             | `--user`             | Guides user through the process of typing the records with the keyboard.                  |
| `-s`             | `--step-by-step`     | Lets user go through sorting step by step. This option also sets maximum verbosity.       |
| `-v`             | `--verbose`          | Sets maximum verbosity level. This means displaying each tape during the sorting process. |

If no one of the flags `-r`, `-f` and `-u` is specified, the input is generated randomly just as if `-r` flag was provided.

## Input data

### File format

Input files should be binary files, containing the database of the records. Each record should be a pair of two 4-bytes-long integers. This implies that the byte length of the file should be divisible by 8, since each record should be exactly 8-byte long. If you are using `-f` option, please make sure your file is prepared correctly.
