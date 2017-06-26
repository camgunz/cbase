#include "cbase.h"

#include <stdio.h>

typedef struct {
    const char *dirname;
    const char *basename;
    const char *extension;
} Path;

typedef struct {
    Path path;
} Folder;

typedef struct {
    Path path;
} File;

void path_init(Path *path, const char *dirname, const char *basename,
                                                const char *extension);
bool path_new(Path **path, const char *dirname, const char *basename,
                                                const char *extension,
                                                Status *status);
bool path_exists(Path *path, bool *exists, Status *status);
bool path_dirname_is_folder(Path *path, bool *is_folder, Status *status);
bool path_is_folder(Path *path, bool *is_folder, Status *status);
bool path_is_file(Path *path, bool *is_folder, Status *status);
bool path_is_regular_file(Path *path, bool *is_regular_file, Status *status);
bool path_is_symlink(Path *path, bool *is_symlink, Status *status);
bool path_check_access(Path *path, bool *access, int flags, Status *status);
bool path_is_absolute(Path *path, bool *is_absolute, Status *status);
bool path_strip_absolute_path(Path *path, Status *status);
bool path_strip_extension(Path *path, Status *status);
bool path_rename(Path *old, Path *new, Status *status);
bool path_delete(Path *path, Status *status);
