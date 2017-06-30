#include "cbase.h"

#include <ctypes.h>
#include <stdio.h>

#include <sys/stat.h>

#ifdef _WIN32

#define cbstat   _wstat
#define cbaccess _waccess
typedef struct _stat CBStat

#else

#define cbstat   stat
#define cbaccess access
typedef struct stat CBStat

#endif

#define INIT_BUFFER_ALLOC 64

#define path_has_no_dirname(status) status_error( \
    status,                                       \
    "path",                                       \
    PATH_HAS_NO_DIRNAME,                          \
    "path has no dirname"                         \
)

#define path_has_no_extension(status) status_error( \
    status,                                         \
    "path",                                         \
    PATH_HAS_NO_EXTENSION,                          \
    "path has no extension"                         \
)

#define file_errno_error(domain, status) status_error( \
    status,                                            \
    domain,                                            \
    errno,                                             \
    strerror(errno)                                    \
)

static void normalize_path(Path *path) {
#ifdef _WIN32
    char   *lp = path->normal_path.data;
    size_t  sz = path->normal_path.byte_len;

    for (size_t i = 0; i < sz; i++) {
        if (lp->data[i] == '\\') {
            lp->data[i] = '/';
        }
    }
#else
    (void)path;
#endif
}

static void unnormalize_path(Path *path) {
#ifdef _WIN32
    char   *lp = path->normal_path.data;
    size_t  sz = path->normal_path.byte_len;

    for (size_t i = 0; i < sz; i++) {
        if (lp[i] == '/') {
            lp[i] = '\\';
        }
    }
#else
    (void)path;
#endif
}

/*
 * path_init(&path, "C:\Program Files (x86)\SuperApp\config.ini", status);
 * path_init(&path, "/home/user/.config/SuperApp/config.ini", status);
 * Path *base_config_path = sys_get_config_folder();
 * Path *full_config_path = NULL;
 * // path_join returns an error if the 2nd path is absolute
 * path_new_join(&full_config_path, app_config_path, "SuperApp/config.ini", status)
 */

static bool base_set_path(Path *path, Slice *input, bool init,
                                                    bool local,
                                                    Status *status) {
    Slice s;

    if (local) {
        if (init) {
            if (!string_init(&path->normal_path, "", status)) {
                return false;
            }
        }

        if (!charset_unlocalize_to_string(&input, &path->normal_path,
                                                  status)) {
        }
    }
    else {
        if (init) {
            if (!string_init_len(&path->normal_path, input->data, input->len,
                                                                  status)) {
                return false;
            }
        }
        else if (!string_assign_len(&path->normal_path, input->data,
                                                        input->len,
                                                        status)) {
            return false;
        }
    }

    if (init) {
        if (!buffer_init(&path->local_path, status)) {
            string_free(&path->normal_path);
            return false;
        }
    }
    else {
        buffer_clear(&path->local_path);
    }

    unnormalize_path(&path->normal_path);

    s.data = path->normal_path.data;
    s.len = path->normal_path.len;

    if (!charset_localize(&s, &path->local_path, status)) {
        string_free(&path->normal_path);
        buffer_free(&path->local_path);
        return false;
    }

    normalize_path(&path->normal_path);

    return true;
}

static inline bool set_path(Path *path, Slice *input, bool local,
                                                      Status *status) {
    return base_set_path(path, input, false, local, status);
}

static inline bool init_path(Path *path, Slice *input, bool local,
                                                       Status *status) {
    return base_set_path(path, input, true, local, status);
}

static bool stat_path(const char *path, cbstat *stat_obj, Status *status) {
    CBStat stat_obj;
    int res = cbstat(path, &stat_obj);

    if (res != 0) {
        return file_errno_error("path", status);
    }

    *stat_obj = stat_obj;
    return true;
}

bool path_init(Path *path, Slice *path_slice, Status *status) {
    return init_path(path, path_slice, true, status);
}

bool path_init_non_local(Path *path, Slice *non_local_path, Status *status) {
    return init_path(path, non_local_path, false, status);
}

bool path_init_non_local_from_cstr(Path *path, const char *non_local_path,
                                               Status *status) {
    Slice s;

    s.data = (char *)non_local_path;
    s.len = strlen(non_local_path);

    return path_init_non_local(path, &s, status);
}

bool path_new(Path **path, Slice *path_slice, Status *status) {
    Path *new_path = cbmalloc(1, sizeof(Path));

    if (!new_path) {
        return alloc_failure(status);
    }

    if (!path_init(new_path, path_slice, status)) {
        cbfree(new_path);
        return false;
    }

    *path = new_path;

    return true;
}

bool path_new_non_local(Path *path, Slice *non_local_path, Status *status) {
    Path *new_path = cbmalloc(1, sizeof(Path));

    if (!new_path) {
        return alloc_failure(status);
    }

    if (!path_init_non_local(path, non_local_path, status)) {
        cbfree(new_path);
        return false;
    }

    *path = new_path;

    return true;
}

bool path_new_non_local_from_cstr(Path *path, const char *non_local_path,
                                              Status *status) {
    Path *new_path = cbmalloc(1, sizeof(Path));

    if (!new_path) {
        return alloc_failure(status);
    }

    if (!path_init_non_local_from_cstr(path, non_local_path, status)) {
        cbfree(new_path);
        return false;
    }

    *path = new_path;

    return true;
}

bool path_set(Path *path, Slice *path_slice, Status *status) {
    return set_path(path, path_slice, true, status);
}

bool path_set_non_local(Path *path, Slice *non_local_path, Status *status) {
    return set_path(path, path_slice, false, status);
}

bool path_set_non_local_from_cstr(Path *path, const char *non_local_path,
                                              Status *status) {
    Slice s;

    s.data = (char *)non_local_path;
    s.len = strlen(non_local_path);

    return path_set_non_local(path, &s, status);
}

bool path_dirname(Path *path, SSlice *dirname, Status *status) {
    if (!string_slice(&path->normal_path, dirname, path->normal_path->len,
                                                   status)) {
        return false;
    }

    if (!sslice_truncate_at(dirname, '/', status)) {
        sslice_clear(dirname);

        if (status_match("base", ERROR_NOT_FOUND)) {
            return path_has_no_dirname(status);
        }

        return false;
    }

    return true;
}

bool path_basename(Path *path, SSlice *basename, Status *status) {
    if (!string_slice(&path->normal_path, basename, 0, path->normal_path->len,
                                                       status)) {
        return false;
    }

    while (true) {
        if (!sslice_seek_to(basename, '/', status)) {
            if (!status_match("base", ERROR_NOT_FOUND)) {
                sslice_clear(basename);
                return false;
            }

            status_clear(status);
            break;
        }
    }

    return true;
}

bool path_extension(Path *path, SSlice *extension, Status *status) {
    if (!path_basename(path, extension, status)) {
        return false;
    }

    if (!sslice_seek_to(extension, '.', status)) {
        sslice_clear(extension);

        if (status_match("base", ERROR_NOT_FOUND)) {
            return path_has_no_extension(status);
        }

        return false;
    }

    return sslice_skip_rune(extension, status);
}

bool path_exists(Path *path, bool *exists, Status *status) {
    CBStat stat_obj;

    if (!stat_path(path, stat_obj)) {
        if (status_match(status, "path", PATH_DOES_NOT_EXIST)) {
            *exists = false;
        }
        else {
            return false;
        }
    }
    else {
        *exists = true;
    }

    return true;
}

bool path_dirname_exists(Path *path, bool *exists, Status *status) {
    SSlice dirname;
    Buffer local_dirname;
    CBStat stat_obj;

    if (!path_dirname(path, &dirname, status)) {
        return false;
    }

    if (!buffer_init(&local_dirname)) {
        return false;
    }

    if (!charset_localize_from_string(&dirname, &local_dirname, status)) {
        buffer_free(&local_dirname);
    }

    if (!stat_path(local_dirname->data, &stat_obj)) {
        if (status_match(status, "path", PATH_DOES_NOT_EXIST)) {
            *exists = false;
        }
        else {
            buffer_free(&local_dirname);
            return false;
        }
    }
    else {
        *exists = true;
    }

    buffer_free(&local_dirname);

    return true;
}

bool path_is_folder(Path *path, bool *is_folder, Status *status) {
    CBStat stat_obj;

    if (!stat_path(path, stat_obj)) {
        return false;
    }

    *is_folder = ((stat_obj.st_mode & S_IFDIR) == S_IFDIR);

    return true;
}

bool path_is_file(Path *path, bool *is_file, Status *status) {
    CBStat stat_obj;

    if (!stat_path(path, stat_obj)) {
        return false;
    }

    *is_file = (
        ((stat_obj.st_mode & S_IFBLK) == S_IFBLK) ||
        ((stat_obj.st_mode & S_IFCHR) == S_IFCHR) ||
        ((stat_obj.st_mode & S_IFIFO) == S_IFIFO) ||
        ((stat_obj.st_mode & S_IREG ) == S_IREG ) ||
        ((stat_obj.st_mode & S_ILNK ) == S_ILNK ) ||
        ((stat_obj.st_mode & S_ISOCK) == S_ISOCK)
    );

    return true;
}

bool path_is_regular_file(Path *path, bool *is_regular_file, Status *status) {
    CBStat stat_obj;

    if (!stat_path(path, stat_obj)) {
        return false;
    }

    *is_regular_file = ((stat_obj.st_mode & S_IFREG) == S_IFREG);

    return true;
}

bool path_is_symlink(Path *path, bool *is_symlink, Status *status) {
    CBStat stat_obj;

    if (!stat_path(path, stat_obj)) {
        return false;
    }

    *is_symlink = ((stat_obj.st_mode & S_IFLNK) == S_IFLNK);

    return true;
}

bool path_is_readable(Path *path, bool *readable, Status *status) {
#ifdef _WIN32
    if ((cbaccess(path->local_path.data, 4) == 0) ||
        (cbaccess(path->local_path.data, 6) == 0)) {
        *readable = true;
        return true;
    }
#else
    if (cbaccess(path->local_path.data, R_OK) == 0) {
        *readable = true;
        return true;
    }
#endif

    if (errno != EACCES) {
        return file_errno_error("path", status);
    }

    *readable = false;
    return true;
}

bool path_is_writable(Path *path, bool *writable, Status *status) {
#ifdef _WIN32
    if ((cbaccess(path->local_path.data, 2) == 0) ||
        (cbaccess(path->local_path.data, 6) == 0)) {
        *writable = true;
        return true;
    }
#else
    if (cbaccess(path->local_path.data, W_OK) == 0) {
        *writable = true;
        return true;
    }
#endif

    if (errno != EACCES) {
        return file_errno_error("path", status);
    }

    *writable = false;
    return true;
}

bool path_is_readable_and_writable(Path *path, bool *readable_and_writable,,
                                               Status *status) {
#ifdef _WIN32
    if (cbaccess(path->local_path.data, 6) == 0) {
        *readable_and_writable = true;
        return true;
    }
#else
    if (cbaccess(path->local_path.data, RW_OK) == 0) {
        *readable_and_writable = true;
        return true;
    }
#endif

    if (errno == EACCES) {
        return file_errno_error("path", status);
    }

    *readable_and_writable = false;
    return true;
}

bool path_is_absolute(Path *path, bool *is_absolute, Status *status) {
    SSlice ss;

    if (!string_slice(path->normal_path, 0, path->normal_path.len, &ss,
                                                                   status)) {
        return false;
    }

    if (
#ifdef _WIN32

}

bool path_strip_absolute_path(Path *path, Status *status) {
}

bool path_strip_extension(Path *path, Status *status) {
}

bool path_rename(Path *old_path, Path *new_path, Status *status) {
}

bool path_delete(Path *path, Status *status) {
}

bool path_join(Path *out, Path *path1, Path *path2, Status *status) {
}

bool path_folder_contains_file(Path *path, const char *filename,
                                           bool *contains_file,
                                           Status *status) {
}

bool path_folder_create(Path *path, int mode, Status *status) {
}

bool path_folder_delete(Path *path, Status *status) {
}

bool path_folder_delete_file(Path *path, const char *filename, Status *status) {
}

bool path_folder_list_files(Path *path, PArray *files, Status *status) {
}

bool path_folder_list_folders(Path *path, PArray *folders, Status *status) {
}

bool path_folder_list_files_and_folders(Path *path, PArray *files_and_folders,
                                                    Status *status) {
}

bool path_file_create(Path *path, int mode, Status *status) {
}

bool path_file_delete(Path *path, Status *status) {
}

bool path_file_open(Path *path, const char *mode) {
}

bool path_file_fdopen(Path *path, int flags, int mode, int *fd,
                                                       Status *status) {
}

bool file_read(File *file, void *buf, size_t byte_count, Status *status) {
}

bool file_write(File *file, const void *buf, size_t byte_count, Status *status) {
}

bool file_seek(File *file, off_t offset, int whence, Status *status) {
}

bool file_tell(File *file, size_t *pos, Status *status) {
}

bool file_size(File *file, size_t *size, Status *status) {
}

bool file_close(File *file, Status *status) {
}

bool file_flush(File *file, Status *status) {
}

bool file_is_eof(File *file) {
}

int file_get_error(File *file) {
}

void file_clear_error(File *file) {
}

int  file_get_fd(File *file) {
}

bool file_fdread(int fd, void *buf, size_t byte_count, Status *status) {
}

bool file_fdwrite(int fd, const void *buf, size_t byte_count, Status *status) {
}

bool file_fdseek(int fd, off_t offset, int whence, Status *status) {
}

bool file_fdtell(int fd, size_t *pos, Status *status) {
}

bool file_fdsize(int fd, size_t *size, Status *status) {
}

bool file_fdclose(int fd, Status *status) {
}

/* vi: set et ts=4 sw=4: */
