#include "cbase.h"

#include <ctypes.h>
#include <stdio.h>

#include <sys/stat.h>

#ifdef _WIN32

#define cbstat _stat
typedef struct _stat CBStat

#else

#define cbstat stat
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

static void normalize_path(Path *path) {
#ifdef _WIN32
    char   *lp = path->normal_path.data;
    size_t  sz = path->normal_path.byte_len;

    for (size_t i = 0; i < sz; i++) {
        if (lp->data[i] == '\\') {
            lp->data[i] = '/';
        }
    }

    if ((sz > 1) && isalpha(lp[0]) && (lp[1] == ':') && ((sz == 2) ||
                                                         (lp[2] == '/'))) {
        lp[1] = toupper(lp[0]);
        lp[0] = '/';

        path->starts_with_drive = true;
    }
#else
    path->starts_with_drive = false;
#endif
}

static void unnormalize_path(Path *path) {
#ifdef _WIN32
    char   *lp = path->normal_path.data;
    size_t  sz = path->normal_path.byte_len;

    if (path->starts_with_drive && (sz > 1) && (lp[0] == '/') &&
                                               isalpha(lp[1]) &&
                                               ((sz == 2) || (lp[2] == '/'))) {
        lp[0] = toupper(lp[0]);
        lp[1] = ':';
    }

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

static bool set_path_from_local_path(Path *path, Slice *local_path,
                                                 bool init,
                                                 Status *status) {
    Buffer buffer;
    Slice s;
    Slice s2;
    SSlice ss;
    bool res;

    if (init) {
        if (!string_init_len(&path->local_path, local_path.data,
                                                local_path.len,
                                                status)) {
            return false;
        }

        if (!string_init_len(&path->normal_local_path, local_path.data,
                                                       local_path.len,
                                                       status)) {
            return false;
        }
    }
    else {
        if (!string_assign_len(&path->local_path, local_path.data,
                                                  local_path.len,
                                                  status)) {
            return false;
        }

        if (!string_assign_len(&path->normal_local_path, local_path.data,
                                                         local_path.len,
                                                         status)) {
            return false;
        }
    }

    normalize_path(&path->normal_local_path);

    if (!buffer_init_alloc(&buffer, INIT_BUFFER_ALLOC, status)) {
        return false;
    }

    if (!charset_unlocalize(local_path, &buffer, status)) {
        buffer_free(&buffer);
        return false;
    }

    s.data = path->full_path.data;
    s.len = path->full_path.byte_len;

    buffer_clear(&buffer);

    if (!charset_localize(&s, &buffer, status)) {
        buffer_free(&buffer);
        return false;
    }

    if (init) {
        res = string_init_len(
            &path->normal_path,
            buffer.data,
            buffer.len,
            status
        );
    }
    else {
        res = string_assign_len(
            &path->normal_path,
            buffer.data,
            buffer.len,
            status
        );
    }

    buffer_free(&buffer);

    if (!res) {
        return false;
    }

    normalize_path(&path->normal_path);

    return recalculate_path_parts(path, status);
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

static bool recalculate_path_parts(Path *path, Status *status) {
    if (!string_slice(&path->normal_path, 0, path->normal_path.len,
                                             &path->dirname,
                                             status)) {
        return false;
    }

    if (!string_slice(&path->normal_path, 0, path->normal_path.len,
                                             &path->basename,
                                             status)) {
        return false;
    }

    if (!string_slice(&path->normal_path, 0, path->normal_path.len,
                                             &path->extension,
                                             status)) {
        return false;
    }

    if (sslice_truncate_at(&path, '/', status)) {
        if (!sslice_seek_past_subslice(&path->basename, &path->dirname,
                                                        status)) {
            return false;
        }
    }
    else if (status_match("base", ERROR_NOT_FOUND)) {
        sslice_clear(&path->dirname);
        status_clear(status);
    }
    else {
        return false;
    }

    if (sslice_seek_to(&path->extension, '.', status)) {
        if (!sslice_truncate_at_subslice(&path->basename, &path->extension,
                                                          status)) {
            return false;
        }
    }
    else if (status_match("base", ERROR_NOT_FOUND)) {
        sslice_clear(&path->extension);
    }
    else {
        return false;
    }
}

/*
 * For ASCII or UTF-8 paths, we can use a `const char *` as the initial path
 * argument.  Otherwise we need a `Buffer`, because there may be NULLs in the
 * encoding.
 */

static bool init_path(Path *path, Buffer *input, bool is_normalized,
                                                 bool is_utf8,
                                                 Status *status) {
    if (!is_utf8) {
        Slice s;

        s.data = input.data;
        s.len = input.len;

        if (!string_init(&path->normal_path, "", status)) {
            return false;
        }

        if (!charset_unlocalize_to_string(&s, &path->normal_path, status)) {

    if (is_normalized && is_utf8) {
        if (!string_init_len(&path->normal_path, buffer->data, buffer->len,
                                                               status)) {
            return false;
        }
    }
    else if (is_utf8) {
        if (!string_init_len(&path->normal_path, buffer->data, buffer->len,
                                                               status)) {
            return false;
        }

        path->starts_with_drive = normalize_string_path(&path->normal_path);
    }
    else {
        Slice s;

        s.data = input.data;
        s.len = input.len;

        if (is_normalized) {
            if (!buffer_init(&path->normal_local_path)) {
                return false;
            }

            if (!charset_localize(&s, &path->normal_local_path, status)) {
                return false;
            }
        }
        else {
            if (!buffer_init(&path->local_path)) {
                return false;
            }

            if (!charset_localize(&s, &path->local_path, status)) {
                return false;
            }
        }

        if (!buffer_copy(&path->normal_local_path, input, status)) {
            return false;
        }
    }
    else {
        if (!buffer_init(&path->
    }
}

bool path_init_from_cstr(Path *path, const char *path_str, Status *status) {
    /*
     * Localization is idempotent, so it only hurts performance to reapply it.
     * Same goes for transcoding to UTF-8.  But to avoid unnecessary
     * performance drains, use parameters to disable these steps.
     */
}

bool path_init(Path *path, Slice *local_full_path, Status *status) {
    set_path_full_local_path(path, local_full_path, true, status);
}

bool path_new(Path **path, const char *local_full_path, Status *status) {
    Path *new_path = cbmalloc(1, sizeof(Path));

    if (!new_path) {
        return alloc_failure(status);
    }

    if (!path_init(new_path, local_full_path, status)) {
        cbfree(new_path);
        return false;
    }

    *path = new_path;

    return true;
}

bool path_new_from_basename(Path **path, Path *basename_path, Status *status) {
    Slice s;

    s.data = basename_path->basename.data;
    s.data = basename_path->basename.data;
}

bool path_get_local_full_path(Path *path, Buffer *out, Status *status) {
    Slice s;

    s.data = path->full_path.data;
    s.len = path->full_path.byte_len;

    return charset_localize(&s, out, status);
}

bool path_set_local_full_path(Path *path, Slice *local_full_path,
                                          Status *status) {
    Buffer unlocalized_buffer;

    if (!buffer_init_alloc(&unlocalized_buffer, INIT_BUFFER_ALLOC, status)) {
        return false;
    }

    if (!charset_unlocalize(local_full_path, &unlocalized_buffer, status)) {
        buffer_free(&unlocalized_buffer);
        return false;
    }

    if (!string_assign_len(&path->full_path, unlocalized_buffer.data,
                                             unlocalized_buffer.len,
                                             status)) {
        buffer_free(&unlocalized_buffer);
        return false;
    }

    buffer_free(&unlocalized_buffer);

    return recalculate_path_parts(path, status);
}

bool path_exists(Path *path, bool *exists, Status *status) {
    int res = cbstat(
}

bool path_dirname_is_folder(Path *path, bool *is_folder, Status *status) {
}

bool path_is_folder(Path *path, bool *is_folder, Status *status) {
}

bool path_is_file(Path *path, bool *is_file, Status *status) {
}

bool path_is_regular_file(Path *path, bool *is_regular_file, Status *status) {
}

bool path_is_symlink(Path *path, bool *is_symlink, Status *status) {
}

bool path_check_access(Path *path, bool *access, int flags, Status *status) {
}

bool path_is_absolute(Path *path, bool *is_absolute, Status *status) {
}

bool path_strip_absolute_path(Path *path, Status *status) {
}

bool path_strip_extension(Path *path, Status *status) {
}

bool path_rename(Path *old, Path *new, Status *status) {
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

int  file_get_error(File *file) {
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
