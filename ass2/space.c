////////////////////////////////////////////////////////////////////////
// COMP1521 24T1 --- Assignment 2: `space', a simple file archiver
// <https://www.cse.unsw.edu.au/~cs1521/24T1/assignments/ass2/index.html>
//
// Written by Brandon Chikandiwa (z5495844) on 17-04-2024.
//
// 2024-03-08   v1.1    Team COMP1521 <cs1521 at cse.unsw.edu.au>

#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "space.h"

// CONSTANTS //

/**
 * @brief Maximum length of a string.
 */
#define MAX_STR_LEN 256

/**
 * @brief Size of a 48-bit unsigned integer in bytes.
 */
#define UINT48_SIZE 6

/**
 * @brief Size of permissions information for a file in bytes.
 */
#define PERMISSION_LEN_SIZE 10

/**
 * @brief Size of the field that stores the length of the pathname in bytes.
 */
#define PATHNAME_LEN_SIZE 2

/**
 * @brief Size of the content length field in bytes.
 */
#define CONTENT_LEN_SIZE 6

/**
 * @brief Magic number identifying the beginning of a star in the galaxy file.
 */
#define MAGIC_NUMBER 0x63

/**
 * @brief Start bit position of the magic number in a star.
 */
#define MAGIC_NUMBER_START_BIT 0

/**
 * @brief Start bit position of the star format in a star.
 */
#define STAR_FORMAT_START_BIT 1

/**
 * @brief Start bit position of the permissions in a star.
 */
#define PERMISSION_START_BIT 2

/**
 * @brief Start bit position of the pathname length field in a star.
 */
#define PATHNAME_LENGTH_START_BIT 12

/**
 * @brief Start bit position of the pathname in a star.
 */
#define PATHNAME_START_BIT 14

/**
 * @brief File open mode for reading.
 */
#define READ "r"

/**
 * @brief File open mode for writing.
 */
#define WRITE "w"

/**
 * @brief File open mode for appending(writing but without overriding
 * existing content).
 */
#define APPEND "a"

// STRUCTS //

struct Star {
    uint8_t magic_number;
    uint8_t star_format;
    char *permissions;
    uint16_t pathname_length;
    char *pathname;
    uint64_t content_length;
    char *content;
    uint8_t hash;
};

// FUNCTION PROTOTYPES //

/**
 * @brief This will list the files in a galaxy.
 * @param galaxy_pathname This is the pathname of the galaxy to be listed.
 * @param long_listing This is an int that determines the listing type of a
 * file, wether it be long listing or just listing the files.
 */
void list_galaxy(char *galaxy_pathname, int long_listing);

/**
 * @brief Checks the integrity of a galaxy file by verifying the magic number
 * and hash of each star.
 * @param galaxy_pathname The pathname of the galaxy file to be checked.
 */
void check_galaxy(char *galaxy_pathname);

/**
 * @brief Extracts the contents of a galaxy file, creating files and
 * directories where necessary.
 * @param galaxy_pathname The pathname of the galaxy file to be extracted.
 */
void extract_galaxy(char *galaxy_pathname);

/**
 * @brief Creates a new galaxy file or appends to an existing one with
 * specified stars.
 * @param galaxy_pathname The pathname of the galaxy file to be written or
 * appended to.
 * @param append Flag indicating whether to append/create to a galaxy file.
 * @param format The format of the galaxy file either.
 * @param n_pathnames The number of pathnames provided.
 * @param pathnames An array of pathnames to be included as stars in the
 * galaxy file.
 */
void create_galaxy(char *galaxy_pathname, int append, int format,
                   int n_pathnames, char *pathnames[n_pathnames]);

/**
 * @brief Calculates the length of a star in bytes.
 * @param current The current position in the galaxy file.
 * @param star Pointer to the star structure.
 * @return long integer of length of bytes of star.
 */
long star_len(int current, struct Star *star);

/**
 * @brief Reads a star from a galaxy file and returns a pointer to the star
 * structure.
 * @param galaxy_pathname The pathname of the galaxy file.
 * @param start The position in the galaxy file where the star begins.
 * @returns struct Star* containing all information of a star from a
 *  galaxy at a specific starting point
 */
struct Star *get_star(char *galaxy_pathname, int start);

/**
 * @brief Creates a star structure for a file specified by its pathname.
 * @param galaxy_pathname The pathname of the galaxy file.
 * @param format The format of the star.
 * @param pathname The pathname of the file.
 * @returns struct Star* containng the information of a star that has been
 * created from various information provided.
 */
struct Star *create_star(char *galaxy_pathname, int format, char *pathname);

/**
 * @brief Calculates the hash of a portion of data in the galaxy file.
 * @param galaxy_pathname The pathname of the galaxy file.
 * @param position The starting position of the data.
 * @param size The size of the data in bytes.
 * @ retuns 8 bit, little edian hash for a galaxy file that is specific size,
 * starting at a position in the galaxy_pathname
 */
uint8_t calculate_hash(char *galaxy_pathname, long position, int size);

/**
 * @brief Converts file permissions from octal representation to a
 * character array.
 * @param mode File permissions in octal format.
 * @returns char array permission from stat mode_t
 */
char *oct_to_chr_arr(mode_t mode);

/**
 * @brief Extracts the contents of a star to a file and sets permissions
 * accordingly.
 * @param start The starting position of the star in the galaxy file.
 * @param star Pointer to the star structure.
 */
void extract_star(int start, struct Star *star);

/**
 * @brief Writes the contents of a star to a galaxy file.
 * @param file Pointer to the galaxy file.
 * @param star Pointer to the star structure.
 */
void add_star(FILE *file, struct Star *star);

/**
 * @brief Creates directories specified by the pathname of a star.
 * @param star Pointer to the star structure.
 */
void create_dir(struct Star *star);

/**
 * @brief Creates a new galaxy file or appends to an existing one with
 * specified stars.
 * @param galaxy_pathname The pathname of the galaxy file to be written or
 * appended to.
 * @param append Flag indicating whether to append/create to a galaxy file.
 * @param format The format of the galaxy file either.
 * @param n_pathnames The number of pathnames provided.
 * @param pathnames An array of pathnames to be included as stars in the
 * galaxy file.
 */
void create_gal(char *galaxy_pathname, int append, int format,
                  int n_pathnames, char *pathnames[n_pathnames]);

/**
 * @brief Reads the magic number of a star from the galaxy file to a star
 * structure.
 * @param galaxy_pathname The pathname of the galaxy file.
 * @param position The position of the magic number in the galaxy file.
 * @param star Pointer to the star structure.
 */
void get_magic_num(char *galaxy_pathname, long position, struct Star *star);

/**
 * @brief Reads the format of a star from the galaxy file to a star structure.
 * @param galaxy_pathname The pathname of the galaxy file.
 * @param position The position of the star format in the galaxy file.
 * @param star Pointer to the star structure.
 */
void get_star_format(char *galaxy_pathname, long position, struct Star *star);

/**
 * @brief Reads the permissions of a star from the galaxy file
 * to a star structure.
 * @param galaxy_pathname The pathname of the galaxy file.
 * @param position The position of the permissions in the galaxy file.
 * @param star Pointer to the star structure.
 */
void get_perms(char *galaxy_pathname, long position, struct Star *star);

/**
 * @brief Reads the length of the pathname of a star from the galaxy file to a
 * star structure.
 * @param galaxy_pathname The pathname of the galaxy file.
 * @param position The position of the pathname length in the galaxy file.
 * @param star Pointer to the star structure.
 */
void get_path_len(char *galaxy_pathname, long position, struct Star *star);

/**
 * @brief Reads the pathname of a star from the galaxy file  to a star
 * structure.
 * @param galaxy_pathname The pathname of the galaxy file.
 * @param position The starting position of the pathname in the galaxy file.
 * @param path_len The length of the pathname.
 * @param star Pointer to the star structure.
 */
void get_path(char *galaxy_pathname, int position, uint8_t path_len,
              struct Star *star);

/**
 * @brief Reads the content length of a star from the galaxy file to a star
 * structure.
 * @param galaxy_pathname The pathname of the galaxy file.
 * @param position The position of the content length in the galaxy file.
 * @param star Pointer to the star structure.
 */
void get_cont_len(char *galaxy_pathname, long position, struct Star *star);

/**
 * @brief Reads the content of a star from the galaxy file  to a star structure.
 * @param galaxy_pathname The pathname of the galaxy file.
 * @param position The starting position of the content in the galaxy file.
 * @param content_len The length of the content.
 * @param star Pointer to the star structure.
 */
void get_cont(char *galaxy_pathname, int position, uint64_t content_len,
              struct Star *star);

/**
 * @brief Reads the hash of a star from the galaxy file to a star structure.
 * @param galaxy_pathname The pathname of the galaxy file.
 * @param position The position of the hash in the galaxy file.
 * @param star Pointer to the star structure.
 */
void get_hash(char *galaxy_pathname, long position, struct Star *star);

// FUNCTIONS //

// INITIALISATION FUNCTIONS //

void list_galaxy(char *galaxy_pathname, int long_listing) {
    FILE *galaxy = fopen(galaxy_pathname, READ);

    int next;
    int star_position = 0;

    while ((next = fgetc(galaxy)) != EOF) {
        struct Star *star = get_star(galaxy_pathname, star_position);

        if (long_listing) {
            printf("%-10s %2c  %5lu  %s\n", star->permissions,
                   star->star_format, star->content_length, star->pathname);
        } else {
            printf("%s\n", star->pathname);
        }

        star_position = star_len(star_position, star);

        fseek(galaxy, star_position, SEEK_SET);
        free(star);
    }

    fclose(galaxy);
}

void check_galaxy(char *galaxy_pathname) {

    FILE *galaxy = fopen(galaxy_pathname, READ);

    int next;
    int star_position = 0;

    while ((next = fgetc(galaxy)) != EOF) {
        struct Star *star = get_star(galaxy_pathname, star_position);

        if (star->magic_number != MAGIC_NUMBER) {
            fprintf(stderr, "error: incorrect first star byte:");
            fprintf(stderr, " 0x%2x should be 0x63\n", star->magic_number);
            break;
        }

        uint8_t calculated_hash = calculate_hash(galaxy_pathname, star_position,
                                                 star_len(star_position, star));

        if (calculated_hash == star->hash) {
            printf("%s - correct hash\n", star->pathname);
        } else {
            printf("%s - incorrect hash 0x%2x should be 0x%2x\n",
                   star->pathname, calculated_hash, star->hash);
        }

        star_position = star_len(star_position, star);
        fseek(galaxy, star_position, SEEK_SET);
        free(star);
    }

    fclose(galaxy);
}

void extract_galaxy(char *galaxy_pathname) {
    FILE *galaxy = fopen(galaxy_pathname, READ);

    int next;
    int star_position = 0;

    while ((next = fgetc(galaxy)) != EOF) {
        struct Star *star = get_star(galaxy_pathname, star_position);

        // create_dir(star);
        extract_star(star_position, star);

        star_position = star_len(star_position, star);

        fseek(galaxy, star_position, SEEK_SET);
        free(star);
    }

    fclose(galaxy);
}

void create_galaxy(char *galaxy_pathname, int append, int format,
                   int n_pathnames, char *pathnames[n_pathnames]) {

    create_gal(galaxy_pathname, append, format, n_pathnames, pathnames);
}

// CONVERSION FUNCTIONS //

long star_len(int current, struct Star *star) {
    int next_position = (current + 21 + star->pathname_length +
                         star->content_length);
    return (long)next_position;
}

struct Star *get_star(char *galaxy_pathname, int start) {
    struct Star *star = malloc(sizeof(struct Star));

    get_magic_num(galaxy_pathname, start + MAGIC_NUMBER_START_BIT, star);
    get_star_format(galaxy_pathname, start + STAR_FORMAT_START_BIT, star);
    get_perms(galaxy_pathname, start + PERMISSION_START_BIT, star);
    get_path_len(galaxy_pathname, start + PATHNAME_LENGTH_START_BIT, star);
    get_path(galaxy_pathname, start + PATHNAME_START_BIT,
             star->pathname_length, star);
    int cont_len_start = start + PATHNAME_START_BIT + star->pathname_length;
    get_cont_len(galaxy_pathname, cont_len_start, star);
    int cont_start = start + 20 + star->pathname_length;
    get_cont(galaxy_pathname, cont_start, star->content_length, star);
    int hash_start = start + 20 + star->pathname_length + star->content_length;
    get_hash(galaxy_pathname, hash_start, star);

    return star;
}

struct Star *create_star(char *galaxy_pathname, int format, char *pathname) {

    int file_char;
    struct Star *star = malloc(sizeof(struct Star));

    star->magic_number = MAGIC_NUMBER;
    star->star_format = format;

    struct stat fileStat;
    stat(pathname, &fileStat);

    star->permissions = oct_to_chr_arr(fileStat.st_mode & 0777);
    star->pathname_length = strlen(pathname);
    star->pathname = pathname;
    star->content_length = 0;

    FILE *file = fopen(pathname, READ);

    while ((file_char = fgetc(file)) != EOF) {
        star->content_length++;
    }

    star->content = malloc((star->content_length + 1) * sizeof(char));

    fclose(file);
    file = fopen(pathname, READ);
    int position = 0;
    while ((file_char = fgetc(file)) != EOF) {
        star->content[position] = file_char;
        position++;
    }

    star->content[star->content_length] = '\0';

    fclose(file);

    return star;
}

uint8_t calculate_hash(char *galaxy_pathname, long position, int size) {
    FILE *galaxy = fopen(galaxy_pathname, READ);
    uint8_t new_hash = 0;
    fseek(galaxy, position, SEEK_SET);

    for (int i = position; i < size - 1; i++) {
        int file_char = fgetc(galaxy);

        new_hash = galaxy_hash(new_hash, (uint8_t)file_char);
    }

    fclose(galaxy);
    return new_hash;
}

char *oct_to_chr_arr(mode_t mode) {
    char *permissions = malloc(10 * sizeof(char));

    permissions[0] = (S_ISDIR(mode)) ? 'd' : '-';
    permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (mode & S_IXOTH) ? 'x' : '-';
    

    return permissions;
}

// ACTION FUNCTIONS //

void extract_star(int start, struct Star *star) {
    FILE *star_file = fopen(star->pathname, WRITE);

    for (int i = 0; i < star->content_length; i++) {
        fputc((star->content)[i], star_file);
    }

    mode_t mode = 0;

    for (int i = 1; i < PERMISSION_LEN_SIZE; ++i) {
        mode <<= 1;
        if ((star->permissions)[i] != '-') {
            mode |= 1;
        }
    }

    chmod(star->pathname, mode);
    fclose(star_file);

    printf("Extracting: %s\n", star->pathname);
}

void add_star(FILE *file, struct Star *star) {

    uint8_t new_hash = 0;

    char pathname_length_c[PATHNAME_LEN_SIZE];
    pathname_length_c[0] = (uint8_t)(star->pathname_length >> 0) & 0xFF;
    pathname_length_c[1] = (uint8_t)(star->pathname_length >> 8) & 0xFF;

    char content_length_c[CONTENT_LEN_SIZE];

    for (size_t i = 0; i < CONTENT_LEN_SIZE; i++) {
        content_length_c[i] = (uint8_t)(star->content_length >> (i * 8)) & 0xFF;
    }

    fputc(star->magic_number, file);
    new_hash = galaxy_hash(new_hash, star->magic_number);

    fputc(star->star_format, file);
    new_hash = galaxy_hash(new_hash, (uint8_t)star->star_format);

    for (int i = 0; i < PERMISSION_LEN_SIZE; i++) {
        fputc(star->permissions[i], file);
        new_hash = galaxy_hash(new_hash, (uint8_t)star->permissions[i]);
    }

    for (int i = 0; i < PATHNAME_LEN_SIZE; i++) {
        fputc(pathname_length_c[i], file);
        new_hash = galaxy_hash(new_hash, (uint8_t)pathname_length_c[i]);
    }

    for (int i = 0; i < star->pathname_length; i++) {
        fputc(star->pathname[i], file);
        new_hash = galaxy_hash(new_hash, (uint8_t)star->pathname[i]);
    }

    for (int i = 0; i < CONTENT_LEN_SIZE; i++) {
        fputc(content_length_c[i], file);
        new_hash = galaxy_hash(new_hash, (uint8_t)content_length_c[i]);
    }

    for (int i = 0; i < star->content_length; i++) {
        fputc(star->content[i], file);
        new_hash = galaxy_hash(new_hash, (uint8_t)star->content[i]);
    }

    fputc(new_hash, file);
}

void create_gal(char *galaxy_pathname, int append, int format,
                  int n_pathnames, char *pathnames[n_pathnames]) {
    FILE *star_file = fopen(galaxy_pathname, READ);

    if (!append) {
        star_file = fopen(galaxy_pathname, WRITE);
    } else {
        star_file = fopen(galaxy_pathname, APPEND);
    }

    for (int i = 0; i < n_pathnames; i++) {
        struct Star *star = create_star(galaxy_pathname, format, pathnames[i]);

        add_star(star_file, star);

        free(star);

        printf("Adding: %s\n", pathnames[i]);
    }

    fclose(star_file);
}

void create_dir(struct Star *star) {
    int count = 0;
    char delim = '/';

    for (int i = 0; i < star->pathname_length; i++) {
        if (star->pathname[i] == delim) {
            count++;
        }
    }

    char *token = strtok(star->pathname, &delim);

    for (int j = 0; j < count; j++) {
        mode_t mode = 0;

        for (int k = 1; k < PERMISSION_LEN_SIZE; ++k) {
            mode <<= 1;
            if ((star->permissions)[k] != '-') {
                mode |= 1;
            }
        }

        mkdir(token, mode);
        chdir(token);

        printf("Creating directory: %s\n", token);
        token = strtok(NULL, &delim);
    }
}

// UTILITY FUNCTIONS //

void get_magic_num(char *galaxy_pathname, long position, struct Star *star) {
    FILE *galaxy = fopen(galaxy_pathname, READ);
    fseek(galaxy, position, SEEK_SET);
    uint8_t magic_number = (uint8_t)fgetc(galaxy);
    fclose(galaxy);

    star->magic_number = magic_number;
}

void get_star_format(char *galaxy_pathname, long position, struct Star *star) {
    FILE *galaxy = fopen(galaxy_pathname, READ);
    fseek(galaxy, position, SEEK_SET);
    uint8_t star_format = (uint8_t)fgetc(galaxy);
    fclose(galaxy);

    star->star_format = star_format;
}

void get_perms(char *galaxy_pathname, long position, struct Star *star) {
    FILE *galaxy = fopen(galaxy_pathname, READ);
    fseek(galaxy, position, SEEK_SET);
    char *permissions = malloc(11 * sizeof(char));

    for (int i = 0; i < PERMISSION_LEN_SIZE; i++) {
        permissions[i] = fgetc(galaxy);
    }

    permissions[PERMISSION_LEN_SIZE] = '\0';
    fclose(galaxy);

    star->permissions = permissions;
}

void get_path_len(char *galaxy_pathname, long position, struct Star *star) {
    FILE *galaxy = fopen(galaxy_pathname, READ);
    fseek(galaxy, position, SEEK_SET);

    unsigned char path_length_bytes[PATHNAME_LEN_SIZE];
    path_length_bytes[0] = fgetc(galaxy);
    path_length_bytes[1] = fgetc(galaxy);

    fclose(galaxy);

    uint16_t content_length = 0;
    content_length |= (uint16_t)path_length_bytes[0] << 0 |
                      (uint16_t)path_length_bytes[1] << 8;

    star->pathname_length = content_length;
}

void get_path(char *galaxy_pathname, int position, uint8_t path_len,
              struct Star *star) {
    FILE *galaxy = fopen(galaxy_pathname, READ);
    fseek(galaxy, position, SEEK_SET);
    char *pathname = malloc((path_len + 1) * sizeof(char));

    for (int i = 0; i < path_len; i++) {
        pathname[i] = fgetc(galaxy);
    }

    pathname[path_len] = '\0';
    fclose(galaxy);
    star->pathname = pathname;
}

void get_cont_len(char *galaxy_pathname, long position, struct Star *star) {
    FILE *galaxy = fopen(galaxy_pathname, READ);
    fseek(galaxy, position, SEEK_SET);

    unsigned char content_length_bytes[CONTENT_LEN_SIZE];

    for (int i = 0; i < CONTENT_LEN_SIZE; i++) {
        int file_char = fgetc(galaxy);
        content_length_bytes[i] = file_char;
    }

    fclose(galaxy);

    uint64_t content_length = 0;

    for (int i = 0; i < CONTENT_LEN_SIZE; i++) {
        content_length |= (uint64_t)content_length_bytes[i] << (i * 8);
    }

    star->content_length = content_length;
}

void get_cont(char *galaxy_pathname, int position, uint64_t content_len,
              struct Star *star) {
    FILE *galaxy = fopen(galaxy_pathname, READ);
    fseek(galaxy, position, SEEK_SET);
    char *content = malloc((content_len + 1) * sizeof(char));

    for (int i = 0; i < content_len; i++) {
        int file_char = fgetc(galaxy);
        content[i] = file_char;
    }

    content[content_len] = '\0';
    fclose(galaxy);
    star->content = content;
}

void get_hash(char *galaxy_pathname, long position, struct Star *star) {
    FILE *galaxy = fopen(galaxy_pathname, READ);
    fseek(galaxy, position, SEEK_SET);
    uint8_t hash = (uint8_t)fgetc(galaxy);
    fclose(galaxy);

    star->hash = hash;
}
