#include "cbase.h"

#include <ctypes.h>
#include <stdio.h>

#define INIT_BUFFER_ALLOC 256

static void normalize_windows_path(const char *path) {
    size_t len = strlen(path);

    for (size_t i = 0; i < len; i++) {
        if (path[i] == '\\') {
            path[i] = '/';
        }
    }

    if ((len > 3) && isalpha(path[0]) && path[1] == ':' && path[2] == '/') {
        path[1] = toupper(path[0]);
        path[0] = '/';
    }
}

static bool recalculate_path_parts(Path *path, Status *status) {
    if (!string_slice(&path->full_path, 0, path->full_path.len, &path->dirname,
                                                                status)) {
        return false;
    }

    if (!string_slice(&path->full_path, 0, path->full_path.len, &path->basename,
                                                                status)) {
        return false;
    }

    if (!string_slice(&path->full_path, 0, path->full_path.len, &path->extension,
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

bool path_init(Path *path, Slice *local_full_path, Status *status) {
    Buffer unlocalized_buffer;

    if (!buffer_init_alloc(&unlocalized_buffer, INIT_BUFFER_ALLOC, status)) {
        return false;
    }

    if (!charset_unlocalize(local_full_path, &unlocalized_buffer, status)) {
        buffer_free(&unlocalized_buffer);
        return false;
    }

    if (!string_init_len(&path->full_path, unlocalized_buffer.data,
                                           unlocalized_buffer.len,
                                           status)) {
        buffer_free(&unlocalized_buffer);
        return false;
    }

    buffer_free(&unlocalized_buffer);

    return recalculate_path_parts(path, status);
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
}

bool path_dirname_is_folder(Path *path, bool *is_folder, Status *status) {
}

bool path_is_folder(Path *path, bool *is_folder, Status *status) {
}

bool path_is_file(Path *path, bool *is_folder, Status *status) {
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
