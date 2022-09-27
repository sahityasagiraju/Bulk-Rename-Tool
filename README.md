# Bulk-Rename-Tool (Secure Coding)

C code that complies with CERT guidelines (prevents from various vulnerarabilities) and helps to rename multiple files at once.

# Functionalities:
1. Inputs source directory of files to be renamed (checks if NULL, if yes returns 0 and exits from entire program)
2. Allocates memory to source path (if path null after allocating, exits program)
3. Input string to rename the file names( checks if input is EOF; strlen>256; if yes print error)
4. Input option to rename files in numeric or alphabetic order( Frees all memory and exits program incase of any error)
5. Inputs choice if user wants to copy or move files to another directory (Checks if source and destination paths are same; checks for subdirectories(can rename only .txt files))

# Vulnerabilities handled:
1. Input data is sanitised - checking if null or not null 
2. Dynamic memory is properly allocated 
3. Used **snprintf** instead of sprintf or strcpy ( to handle buffer overflow )
4. File is opening and closing as expected
5. Looking for EOF triggers in input
6. Checking length of input directory ( < 256 char )

