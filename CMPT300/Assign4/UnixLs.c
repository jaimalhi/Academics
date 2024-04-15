#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_PATH_LENGTH    400
#define PERMISSION_LENGTH  12
#define DATE_LENGTH        22
#define INODE_LENGTH       14

// structure to hold flags for command line options
typedef struct {
    unsigned int i: 1;  // inode flag
    unsigned int l: 1;  // long listing flag
} Flags;

// function declarations
static void processDirectory(const char *directoryName, const Flags *flags);
static void parseFlags(int argc, char *argv[], Flags *flags, int *start_index);
static void printFileDetails(const char *filePath, const Flags *flags);
static void printLongFormat(const char *filePath);
static long printFormattedNameWithInode(const char *filePath);
static void buildPermissionString(char *string, mode_t permissions);
static void formatDate(char *string, time_t time);

int main(int argc, char *argv[]) {
    Flags flags = {0};  // initialize flag structure
    int start_index = 1;  // initialize start index for directory arguments

    parseFlags(argc, argv, &flags, &start_index);  // parse command line flags

    // process directories specified on the command line or default to current directory
    if (start_index == argc) {
        processDirectory(".", &flags);  
    } else {
        for (int i = start_index; i < argc; i++) {
            processDirectory(argv[i], &flags);  
        }
    }

    return 0;
}

// process entries within a directory
static void processDirectory(const char *directoryName, const Flags *flags) {
    DIR *dir = opendir(directoryName); 
    struct dirent *entry;
    char filePath[MAX_PATH_LENGTH];

    if (dir == NULL) {  // check if directory is opened
        fprintf(stderr, "ls: %s: %s\n", directoryName, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // read directory entries
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {  // skip hidden files
            snprintf(filePath, sizeof(filePath), "%s/%s", directoryName, entry->d_name);
            printFileDetails(filePath, flags);  // print details based on flags
        }
    }

    closedir(dir); 
}

// parse command line arguments for flags
static void parseFlags(int argc, char *argv[], Flags *flags, int *start_index) {
    for (int i = 1; i < argc && argv[i][0] == '-'; i++) {
        char *arg = argv[i] + 1;
        while (*arg) {  // parse each character of the flag string
            switch (*arg++) {
                case 'i': flags->i = 1; break;  // inode flag
                case 'l': flags->l = 1; break;  // long listing flag
                default: 
                    fprintf(stderr, "ls: invalid option -- '%c'\n", *(arg - 1));
                    exit(EXIT_FAILURE);
            }
        }
        (*start_index)++;
    }
}

// print file details based on specified flags
static void printFileDetails(const char *filePath, const Flags *flags) {
    if (flags->i && flags->l) {
        long inode = printFormattedNameWithInode(filePath);
        printf("%*ld ", INODE_LENGTH, inode);
        printLongFormat(filePath); 
    } else if (flags->l) {
        printLongFormat(filePath);  
    } else if (flags->i){
        long inode = printFormattedNameWithInode(filePath);
        printf("%*ld %s\n", INODE_LENGTH, inode, filePath);
    } else {
        printf("%s\n", filePath);  // print name only
    }
}

// print inode and file path
static long printFormattedNameWithInode(const char *filePath) {
    struct stat statbuf;
    if (lstat(filePath, &statbuf) == -1) {
        fprintf(stderr, "ls: cannot access '%s': %s\n", filePath, strerror(errno));
        return -1;
    }
    return (long)statbuf.st_ino;
}

// print detailed file information in long format
static void printLongFormat(const char *filePath) {
    struct stat statbuf;
    char permissions[PERMISSION_LENGTH], dateStr[DATE_LENGTH];
    struct passwd *pwd;
    struct group *grp;

    if (lstat(filePath, &statbuf) == -1) {
        fprintf(stderr, "ls: cannot access '%s': %s\n", filePath, strerror(errno));
        return;
    }

    pwd = getpwuid(statbuf.st_uid);
    grp = getgrgid(statbuf.st_gid);
    buildPermissionString(permissions, statbuf.st_mode);
    formatDate(dateStr, statbuf.st_mtime);

    printf("%s %lu %s %s %5ld %s %s\n", permissions, (unsigned long)statbuf.st_nlink,
           pwd ? pwd->pw_name : "UNKNOWN", grp ? grp->gr_name : "UNKNOWN",
           (long)statbuf.st_size, dateStr, filePath);
}

// build permission string from mode
static void buildPermissionString(char *string, mode_t permissions) {
    strcpy(string, "----------");  // default to all permissions off
    if (S_ISDIR(permissions)) string[0] = 'd';  // directory
    if (permissions & S_IRUSR) string[1] = 'r';  // user read
    if (permissions & S_IWUSR) string[2] = 'w';  // user write
    if (permissions & S_IXUSR) string[3] = 'x';  // user execute
    if (permissions & S_IRGRP) string[4] = 'r';  // group read
    if (permissions & S_IWGRP) string[5] = 'w';  // group write
    if (permissions & S_IXGRP) string[6] = 'x';  // group execute
    if (permissions & S_IROTH) string[7] = 'r';  // others read
    if (permissions & S_IWOTH) string[8] = 'w';  // others write
    if (permissions & S_IXOTH) string[9] = 'x';  // others execute
}

// format date for output
static void formatDate(char *string, time_t time) {
    struct tm *timeInfo = localtime(&time);
    strftime(string, DATE_LENGTH, "%b %d %Y %H:%M", timeInfo);  // format date and time
}