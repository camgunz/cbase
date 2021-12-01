#include "cbase/internal.h"

#include <ctype.h>
#include <stdio.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

/* [TODO] Make configurable */
#define INIT_ALLOC 64

#define permission_denied(status)                                             \
    status_error(status, "path", PATH_PERMISSION_DENIED, "permission denied")

#define invalid_file_descriptor(status)                                       \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_INVALID_FILE_DESCRIPTOR,                                \
                 "invalid file descriptor")

#define invalid_memory_address(status)                                        \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_INVALID_MEMORY_ADDRESS,                                 \
                 "invalid memory address")

#define symbolic_link_depth_exceeded(status)                                  \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_SYMBOLIC_LINK_DEPTH_EXCEEDED,                           \
                 "symbolic link depth exceeded")

#define path_too_long(status)                                                 \
    status_error(status, "path", PATH_TOO_LONG, "path too long")

#define path_not_found(status)                                                \
    status_error(status, "path", PATH_NOT_FOUND, "path not found")

#define out_of_memory(status)                                                 \
    status_error(status, "path", PATH_OUT_OF_MEMORY, "out of memory")

#define path_not_folder(status)                                               \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_NOT_FOLDER,                                             \
                 "path or path component is not a folder")

#define data_overflow(status)                                                 \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_INVALID_FILE_DESCRIPTOR,                                \
                 "invalid file descriptor")

#define invalid_mode(status)                                                  \
    status_error(status, "path", PATH_INVALID_MODE, "invalid mode")

#define read_only_filesystem(status)                                          \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_READ_ONLY_FILESYSTEM,                                   \
                 "read-only filesystem")

#define io_error(status)                                                      \
    status_error(status, "path", PATH_IO_ERROR, "i/o error")

#define file_busy(status)                                                     \
    status_error(status, "path", PATH_FILE_BUSY, "file busy")

#define quota_exceeded(status)                                                \
    status_error(status, "path", PATH_QUOTA_EXCEEDED, "quota exceeded")

#define rename_to_subfolder_of_self(status)                                   \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_RENAME_TO_SUBFOLDER_OF_SELF,                            \
                 "path renamed to a subfolder of itself")

#define rename_folder_to_file(status)                                         \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_RENAME_FOLDER_TO_FILE,                                  \
                 "new path is a folder, but old path is not")

#define link_count_exceeded(status)                                           \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_LINK_COUNT_EXCEEDED,                                    \
                 "link count exceeded")

#define device_full(status)                                                   \
    status_error(status, "path", PATH_DEVICE_FULL, "device full")

#define folder_not_empty(status)                                              \
    status_error(status, "path", PATH_FOLDER_NOT_EMPTY, "folder not empty")

#define sticky_permission_denied(status)                                      \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_STICKY_PERMISSION_DENIED,                               \
                 "permission denied (sticky)")

#define different_filesystems(status)                                         \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_DIFFERENT_FILESYSTEMS,                                  \
                 "operation not allowed across filesystems")

#define unlink_folder(status)                                                 \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_UNLINK_FOLDER,                                          \
                 "attempted to unlink folder")

#define invalid_path(status)                                                  \
    status_error(status, "path", PATH_INVALID_PATH, "invalid path")

#define path_has_no_dirname(status)                                           \
    status_error(status, "path", PATH_HAS_NO_DIRNAME, "path has no dirname")

#define path_has_no_extension(status)                                         \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_HAS_NO_EXTENSION,                                       \
                 "path has no extension")

#define path_end_of_file(status)                                              \
    status_error(status, "path", PATH_END_OF_FILE, "end of file")

#define already_exists(status)                                                \
    status_error(status, "path", PATH_ALREADY_EXISTS, "path already exists")

#define operation_interrupted(status)                                         \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_OPERATION_INTERRUPTED,                                  \
                 "operation interrupted")

#define invalid_flags(status)                                                 \
    status_error(status, "path", PATH_INVALID_FLAGS, "invalid flags")

#define per_process_file_limit_reached(status)                                \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_PER_PROCESS_FILE_LIMIT_REACHED,                         \
                 "per-process file limit reached")

#define system_wide_file_limit_reached(status)                                \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_SYSTEM_WIDE_FILE_LIMIT_REACHED,                         \
                 "system-wide file limit reached")

#define no_peer(status)                                                       \
    status_error(status, "path", PATH_NO_PEER, "no peer on other side of file")

#define operation_not_supported(status)                                       \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_OPERATION_NOT_SUPPORTED,                                \
                 "operation not supported")

#define file_too_large(status)                                                \
    status_error(status, "path", PATH_FILE_TOO_LARGE, "file too large")

#define would_block(status)                                                   \
    status_error(status, "path", PATH_WOULD_BLOCK, "operation would block")

#define invalid_mode_or_flags(status)                                         \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_INVALID_MODE_OR_FLAGS,                                  \
                 "invalid mode or flags")

#define expected_file(status)                                                 \
    status_error(status, "path", PATH_EXPECTED_FILE, "expected file")

#define expected_folder(status)                                               \
    status_error(status, "path", PATH_EXPECTED_FOLDER, "expected folder")

#define folder_busy(status)                                                   \
    status_error(status, "path", PATH_FOLDER_BUSY, "folder busy")

#define no_space(status)                                                      \
    status_error(status, "path", PATH_NO_SPACE, "no space")

#define file_is_named_stream(status)                                          \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_FILE_IS_NAMED_STREAM,                                   \
                 "file is named_stream")

#define is_already_root(status)                                               \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_ALREADY_ROOT,                                           \
                 "path is already the root path")

#define subpath_is_absolute(status)                                           \
    status_error(status,                                                      \
                 "path",                                                      \
                 PATH_SUBPATH_IS_ABSOLUTE,                                    \
                 "subpath is an absolute path")

#define unknown_error(status)                                                 \
    status_error(status, "path", PATH_UNKNOWN_ERROR, "unknown error")

static inline bool sslice_is_absolute_path(SSlice *ss) {
    if ((ss->byte_len == 1) && (ss->data[0] == '/')) {
        return true;
    }

    /* "C:/" */
    if ((ss->byte_len == 3) && (isalpha(ss->data[0])) &&
        (ss->data[1] == ':') && (ss->data[2] == '/'))
    {
        return true;
    }

    /* "//?/C:/"                       */
    if ((ss->byte_len == 7) && (ss->data[0] == '/') && (ss->data[1] == '/') &&
        (ss->data[2] == '?') && (ss->data[3] == '/') &&
        (isalpha(ss->data[4])) && (ss->data[5] == ':') && (ss->data[6] == '/'))
    {
        return true;
    }

    /*
     * [TODO]
     *
     *   //SERVER01/share/
     *   //?/SERVER01/share/
     *   //?/UNC/[server]/[sharename]/
     *   //./[physical_device]/
     */

    return status_propagate(status);
}

static inline bool cstr_is_absolute_path(const char *cs) {
    SSlice ss;
    Status status;

    return (sslice_assign_cstr(&ss, (char *)cs, &status) &&
            sslice_is_absolute_path(&ss));
}

static bool stat_path(const char *path,
                      struct stat *stat_obj,
                      Status *status) {
    int res = stat(path, stat_obj);

    if (res != 0) {
        switch (errno) {
        case EACCES:
            return permission_denied(status);
            break;
        case EBADF:
            return invalid_file_descriptor(status);
            break;
        case EFAULT:
            return invalid_memory_address(status);
            break;
        case EIO:
            return io_error(status);
            break;
        case ELOOP:
            return symbolic_link_depth_exceeded(status);
            break;
        case ENAMETOOLONG:
            return path_too_long(status);
            break;
        case ENOENT:
            return path_not_found(status);
            break;
        case ENOMEM:
            return out_of_memory(status);
            break;
        case ENOTDIR:
            return path_not_folder(status);
            break;
        case EOVERFLOW:
            return data_overflow(status);
            break;
        default:
            return unknown_error(status);
        }
    }

    return status_ok(status);
}

static bool canonicalize_path(Path *path, Status *status) {
    SSlice ss1;
    SSlice ss2;
    bool ends_with = false;

    if (!string_replace_cstr(&path->normal_path, "\\", "/", status)) {
        return status_propagate(status);
    }

    if (!string_replace_cstr(&path->normal_path, "/./", "/", status)) {
        return status_propagate(status);
    }

    if (!string_slice(&path->normal_path,
                      0,
                      path->normal_path.len,
                      &ss1,
                      status)) {
        return status_propagate(status);
    }

    if (!string_slice(&path->normal_path,
                      0,
                      path->normal_path.len,
                      &ss2,
                      status)) {
        return status_propagate(status);
    }

    /* [TODO] Convert ".." into the enclosing folder. */

    while (true) {
        if (!string_ends_with_cstr(&path->normal_path,
                                   "/.",
                                   &ends_with,
                                   status)) {
            return status_propagate(status);
        }

        if (ends_with) {
            if (!string_truncate_runes(&path->normal_path, 2, status)) {
                return status_propagate(status);
            }

            continue;
        }

        if (!string_ends_with_cstr(&path->normal_path,
                                   "/",
                                   &ends_with,
                                   status)) {
            return status_propagate(status);
        }

        if (ends_with) {
            if (!string_truncate_runes(&path->normal_path, 1, status)) {
                return status_propagate(status);
            }
        }

        break;
    }

    return status_ok(status);
}

bool path_init(Path *path, Status *status) {
    buffer_init(&path->local_path);

    if (!string_init_from_cstr(&path->normal_path, "", status)) {
        buffer_free(&path->local_path);
        return status_propagate(status);
    }

    return status_ok(status);
}

bool path_init_and_set(Path *path, SSlice *input, Status *status) {
    if (!buffer_init_alloc(&path->local_path, INIT_ALLOC, status)) {
        return status_propagate(status);
    }

    if (!string_init_from_sslice(&path->normal_path, input, status)) {
        buffer_free(&path->local_path);
        return status_propagate(status);
    }

    if ((!canonicalize_path(path, status)) ||
        (!string_localize(&path->normal_path, &path->local_path, status)))
    {
        buffer_free(&path->local_path);
        string_free(&path->normal_path);
        return status_propagate(status);
    }

    return status_ok(status);
}

bool path_init_and_set_cstr(Path *path, const char *input, Status *status) {
    SSlice ss;

    if (!sslice_assign_cstr(&ss, (char *)input, status)) {
        return status_propagate(status);
    }

    return path_init_and_set(path, &ss, status);
}

bool path_init_and_set_local(Path *path, Slice *input, Status *status) {
    if (!buffer_init_alloc(&path->local_path, input->len, status)) {
        return status_propagate(status);
    }

    if (!buffer_append_slice(&path->local_path, input, status)) {
        buffer_free(&path->local_path);
        return status_propagate(status);
    }

    if (!string_init_from_cstr(&path->normal_path, "", status)) {
        buffer_free(&path->local_path);
        return status_propagate(status);
    }

    if (!string_ensure_capacity(&path->normal_path, INIT_ALLOC, status)) {
        buffer_free(&path->local_path);
        string_free(&path->normal_path);
        return status_propagate(status);
    }

    if (!string_init_from_local_buffer(&path->normal_path,
                                       &path->local_path,
                                       status))
    {
        buffer_free(&path->local_path);
        string_free(&path->normal_path);
        return status_propagate(status);
    }

    return status_ok(status);
}

bool path_new(Path **path, Status *status) {
    Path *new_path = NULL;

    if (!cbmalloc(1, sizeof(Path), &new_path, status)) {
        return status_propagate(status);
    }

    if (!path_init(new_path, status)) {
        cbfree(new_path);
        return status_propagate(status);
    }

    *path = new_path;

    return status_ok(status);
}

bool path_new_and_set(Path **path, SSlice *input, Status *status) {
    Path *new_path = NULL;

    if (!cbmalloc(1, sizeof(Path), &new_path, status)) {
        return status_propagate(status);
    }

    if (!path_init_and_set(new_path, input, status)) {
        cbfree(new_path);
        return status_propagate(status);
    }

    *path = new_path;

    return status_ok(status);
}

bool path_new_and_set_local(Path **path, Slice *input, Status *status) {
    Path *new_path = NULL;

    if (!cbmalloc(1, sizeof(Path), &new_path, status)) {
        return status_propagate(status);
    }

    if (!path_init_and_set_local(new_path, input, status)) {
        cbfree(new_path);
        return status_propagate(status);
    }

    *path = new_path;

    return status_ok(status);
}

bool path_new_and_set_cstr(Path **path, const char *input, Status *status) {
    Path *new_path = NULL;

    if (!cbmalloc(1, sizeof(Path), &new_path, status)) {
        return status_propagate(status);
    }

    if (!path_init_and_set_cstr(new_path, input, status)) {
        cbfree(new_path);
        return status_propagate(status);
    }

    *path = new_path;

    return status_ok(status);
}

bool path_set(Path *path, SSlice *new_path, Status *status) {
    buffer_clear(&path->local_path);
    string_clear(&path->normal_path);

    return (string_assign_sslice(&path->normal_path, new_path, status) &&
            canonicalize_path(path, status) &&
            string_localize(&path->normal_path, &path->local_path, status));
}

bool path_set_from_cstr(Path *path, const char *new_path, Status *status) {
    SSlice ss;

    ss.data = (char *)new_path;
    ss.len = strlen(new_path);

    return path_set(path, &ss, status);
}

bool path_set_local(Path *path, Slice *new_path, Status *status) {
    buffer_clear(&path->local_path);
    string_clear(&path->normal_path);

    return (string_assign_local_slice(&path->normal_path, new_path, status) &&
            canonicalize_path(path, status) &&
            string_localize(&path->normal_path, &path->local_path, status));
}

bool path_dirname(Path *path, Path *out, Status *status) {
    SSlice dirname;
    bool ends_with = false;

    if (path_is_root(path)) {
        return is_already_root(status);
    }

    if (!string_slice(&path->normal_path,
                      0,
                      path->normal_path.len,
                      &dirname,
                      status))
    {
        return status_propagate(status);
    }

    if (!sslice_ends_with_cstr(&dirname, "/", &ends_with, status)) {
        return status_propagate(status);
    }

    while (ends_with) {
        if (!sslice_truncate_rune(&dirname, status)) {
            return status_propagate(status);
        }

        if (!sslice_ends_with_cstr(&dirname, "/", &ends_with, status)) {
            return status_propagate(status);
        }
    }

    if (!sslice_truncate_at_rune(&dirname, '/', status)) {
        if (status_match(status, "base", ERROR_NOT_FOUND)) {
            return path_has_no_dirname(status);
        }

        return status_propagate(status);
    }

    return path_set(out, &dirname, status);
}

bool path_basename(Path *path, SSlice *basename, Status *status) {
    if (!string_slice(&path->normal_path,
                      0,
                      path->normal_path.len,
                      basename,
                      status))
    {
        return status_propagate(status);
    }

    while (true) {
        if (!sslice_seek_to_rune(basename, '/', status)) {
            if (!status_match(status, "base", ERROR_NOT_FOUND)) {
                sslice_clear(basename);
                return status_propagate(status);
            }

            status_clear(status);
            break;
        }

        if (!sslice_skip_rune(basename, status)) {
            return status_propagate(status);
        }
    }

    return status_ok(status);
}

bool path_extension(Path *path, SSlice *extension, Status *status) {
    if (!path_basename(path, extension, status)) {
        return status_propagate(status);
    }

    if (!sslice_seek_to_rune(extension, '.', status)) {
        sslice_clear(extension);

        if (status_match(status, "base", ERROR_NOT_FOUND)) {
            return path_has_no_extension(status);
        }

        return status_propagate(status);
    }

    return sslice_skip_rune(extension, status);
}

bool path_strip_extension(Path *path, Status *status) {
    SSlice extension;
    SSlice new_path;

    return (path_extension(path, &extension, status) &&
            string_truncate_runes(&path->normal_path, extension.len, status) &&
            string_slice(&path->normal_path,
                         0,
                         path->normal_path.len,
                         &new_path,
                         status) &&
            path_set(path, &new_path, status));
}

bool path_exists(Path *path, bool *exists, Status *status) {
    struct stat stat_obj;

    if (stat_path(path->local_path.array.elements, &stat_obj, status)) {
        *exists = true;
    }
    else if (status_match(status, "path", PATH_NOT_FOUND)) {
        *exists = false;
    }
    else {
        return status_propagate(status);
    }

    return status_ok(status);
}

bool path_is_file(Path *path, bool *is_file, Status *status) {
    struct stat stat_obj;

    if (!stat_path(path->local_path.array.elements, &stat_obj, status)) {
        return status_propagate(status);
    }

    *is_file = (((stat_obj.st_mode & S_IFBLK) == S_IFBLK) ||
                ((stat_obj.st_mode & S_IFCHR) == S_IFCHR) ||
                ((stat_obj.st_mode & S_IFIFO) == S_IFIFO) ||
                ((stat_obj.st_mode & S_IFREG) == S_IFREG) ||
                ((stat_obj.st_mode & S_IFLNK) == S_IFLNK) ||
                ((stat_obj.st_mode & S_IFSOCK) == S_IFSOCK));

    return status_ok(status);
}

bool path_is_regular_file(Path *path, bool *is_regular_file, Status *status) {
    struct stat stat_obj;

    if (!stat_path(path->local_path.array.elements, &stat_obj, status)) {
        return status_propagate(status);
    }

    *is_regular_file = ((stat_obj.st_mode & S_IFREG) == S_IFREG);

    return status_ok(status);
}

bool path_is_folder(Path *path, bool *is_folder, Status *status) {
    struct stat stat_obj;

    if (!stat_path(path->local_path.array.elements, &stat_obj, status)) {
        return status_propagate(status);
    }

    *is_folder = ((stat_obj.st_mode & S_IFDIR) == S_IFDIR);

    return status_ok(status);
}

bool path_is_symlink(Path *path, bool *is_symlink, Status *status) {
    struct stat stat_obj;

    if (!stat_path(path->local_path.array.elements, &stat_obj, status)) {
        return status_propagate(status);
    }

    *is_symlink = ((stat_obj.st_mode & S_IFLNK) == S_IFLNK);

    return status_ok(status);
}

bool path_is_root(Path *path) {
    SSlice sslice;

    string_slice_full(&path->normal_path, &sslice);

    return sslice_is_absolute_path(&sslice);
}

bool path_is_readable(Path *path, bool *readable, Status *status) {
    if (access(path->local_path.array.elements, R_OK) == 0) {
        *readable = true;
        return status_ok(status);
    }

    switch (errno) {
    case EACCES:
        *readable = false;
        break;
    case EFAULT:
        return invalid_memory_address(status);
        break;
    case EINVAL:
        return invalid_mode(status);
        break;
    case EIO:
        return io_error(status);
        break;
    case ELOOP:
        return symbolic_link_depth_exceeded(status);
        break;
    case ENAMETOOLONG:
        return path_too_long(status);
        break;
    case ENOENT:
        return path_not_found(status);
        break;
    case ENOMEM:
        return out_of_memory(status);
        break;
    case ENOTDIR:
        return path_not_folder(status);
        break;
    case EROFS:
        return read_only_filesystem(status);
        break;
    case ETXTBSY:
        return file_busy(status);
        break;
    default:
        return unknown_error(status);
        break;
    }

    return status_ok(status);
}

bool path_is_writable(Path *path, bool *writable, Status *status) {
    if (access(path->local_path.array.elements, W_OK) == 0) {
        *writable = true;
        return status_ok(status);
    }

    switch (errno) {
    case EACCES:
        *writable = false;
        break;
    case EFAULT:
        return invalid_memory_address(status);
        break;
    case EINVAL:
        return invalid_mode(status);
        break;
    case EIO:
        return io_error(status);
        break;
    case ELOOP:
        return symbolic_link_depth_exceeded(status);
        break;
    case ENAMETOOLONG:
        return path_too_long(status);
        break;
    case ENOENT:
        return path_not_found(status);
        break;
    case ENOMEM:
        return out_of_memory(status);
        break;
    case ENOTDIR:
        return path_not_folder(status);
        break;
    case EROFS:
        return read_only_filesystem(status);
        break;
    case ETXTBSY:
        return file_busy(status);
        break;
    default:
        return unknown_error(status);
        break;
    }

    return status_ok(status);
}

bool path_is_readable_and_writable(Path *path,
                                   bool *readable_and_writable,
                                   Status *status) {
    if (access(path->local_path.array.elements, R_OK | W_OK) == 0) {
        *readable_and_writable = true;
        return status_ok(status);
    }

    switch (errno) {
    case EACCES:
        *readable_and_writable = false;
        break;
    case EFAULT:
        return invalid_memory_address(status);
        break;
    case EINVAL:
        return invalid_mode(status);
        break;
    case EIO:
        return io_error(status);
        break;
    case ELOOP:
        return symbolic_link_depth_exceeded(status);
        break;
    case ENAMETOOLONG:
        return path_too_long(status);
        break;
    case ENOENT:
        return path_not_found(status);
        break;
    case ENOMEM:
        return out_of_memory(status);
        break;
    case ENOTDIR:
        return path_not_folder(status);
        break;
    case EROFS:
        return read_only_filesystem(status);
        break;
    case ETXTBSY:
        return file_busy(status);
        break;
    default:
        return unknown_error(status);
        break;
    }

    return status_ok(status);
}

bool path_size(Path *path, size_t *size, Status *status) {
    struct stat stat_buf;

    if (!stat_path(path->local_path.array.elements, &stat_buf, status)) {
        return status_propagate(status);
    }

    *size = (size_t)stat_buf.st_size;

    return status_ok(status);
}

bool path_rename(Path *old_path, Path *new_path, Status *status) {
    if (rename(old_path->local_path.array.elements,
               new_path->local_path.array.elements) != 0)
    {
        switch (errno) {
        case EACCES:
            return permission_denied(status);
            break;
        case EBADF:
            return invalid_file_descriptor(status);
            break;
        case EBUSY:
        case ETXTBSY:
            return file_busy(status);
            break;
        case EDQUOT:
            return quota_exceeded(status);
            break;
        case EEXIST:
        case ENOTEMPTY:
            return folder_not_empty(status);
            break;
        case EFAULT:
            return invalid_memory_address(status);
            break;
        case EINVAL:
            return rename_to_subfolder_of_self(status);
            break;
        case EIO:
            return io_error(status);
            break;
        case EISDIR:
            return rename_folder_to_file(status);
            break;
        case ELOOP:
            return symbolic_link_depth_exceeded(status);
            break;
        case EMLINK:
            return link_count_exceeded(status);
            break;
        case ENAMETOOLONG:
            return path_too_long(status);
            break;
        case ENOENT:
            return path_not_found(status);
            break;
        case ENOMEM:
            return out_of_memory(status);
            break;
        case ENOSPC:
            return device_full(status);
            break;
        case ENOTDIR:
            return path_not_folder(status);
            break;
        case EPERM:
            return sticky_permission_denied(status);
            break;
        case EROFS:
            return read_only_filesystem(status);
            break;
        case EXDEV:
            return different_filesystems(status);
            break;
        default:
            return unknown_error(status);
            break;
        }
    }

    return status_ok(status);
}

bool path_delete(Path *path, Status *status) {
    if (remove(path->local_path.array.elements) != 0) {
        switch (errno) {
        case EACCES:
        case EPERM:
            /*
             * EPERM is overloaded like crazy, so give up and just return
             * permission denied; the user will have to figure it out.
             */
            return permission_denied(status);
            break;
        case EBUSY:
            return file_busy(status);
            break;
        case EEXIST:
        case ENOTEMPTY:
            return folder_not_empty(status);
            break;
        case EFAULT:
            return invalid_memory_address(status);
            break;
        case EINVAL:
            return invalid_path(status);
            break;
        case EIO:
            return io_error(status);
            break;
        case ELOOP:
            return symbolic_link_depth_exceeded(status);
            break;
        case ENAMETOOLONG:
            return path_too_long(status);
            break;
        case ENOENT:
            return path_not_found(status);
            break;
        case ENOMEM:
            return out_of_memory(status);
            break;
        case ENOTDIR:
            return path_not_folder(status);
            break;
        case EROFS:
            return read_only_filesystem(status);
            break;
        default:
            return unknown_error(status);
            break;
        }
    }

    return status_ok(status);
}

bool path_join(Path *path, SSlice *path_addition, Status *status) {
    bool ends_with = false;

    if (sslice_is_absolute_path(path_addition)) {
        return subpath_is_absolute(status);
    }

    if (!string_ends_with_cstr(&path->normal_path, "/", &ends_with, status)) {
        return status_propagate(status);
    }

    if (ends_with) {
        if (!string_append_cstr(&path->normal_path, "/", status)) {
            return status_propagate(status);
        }
    }

    return (string_append_sslice(&path->normal_path, path_addition, status) &&
            canonicalize_path(path, status) &&
            string_localize(&path->normal_path, &path->local_path, status));
}

bool path_join_cstr(Path *path, const char *path_addition, Status *status) {
    bool ends_with = false;

    if (cstr_is_absolute_path(path_addition)) {
        return subpath_is_absolute(status);
    }

    if (!string_ends_with_cstr(&path->normal_path, "/", &ends_with, status)) {
        return status_propagate(status);
    }

    if (ends_with) {
        if (!string_append_cstr(&path->normal_path, "/", status)) {
            return status_propagate(status);
        }
    }

    return (string_append_cstr(&path->normal_path, path_addition, status) &&
            canonicalize_path(path, status) &&
            string_localize(&path->normal_path, &path->local_path, status));
}

bool path_folder_create(Path *path, int mode, Status *status) {
    if (mkdir(path->local_path.array.elements, mode) != 0) {
        switch (errno) {
        case EACCES:
        case EPERM:
            return permission_denied(status);
            break;
        case EDQUOT:
            return quota_exceeded(status);
            break;
        case EEXIST:
            return already_exists(status);
            break;
        case EFAULT:
            return invalid_memory_address(status);
            break;
        case ELOOP:
            return symbolic_link_depth_exceeded(status);
            break;
        case EMLINK:
            return link_count_exceeded(status);
            break;
        case ENAMETOOLONG:
            return path_too_long(status);
            break;
        case ENOENT:
            return path_not_found(status);
            break;
        case ENOMEM:
            return out_of_memory(status);
            break;
        case ENOSPC:
            return no_space(status);
            break;
        case ENOTDIR:
            return path_not_folder(status);
            break;
        case EROFS:
            return read_only_filesystem(status);
            break;
        default:
            return unknown_error(status);
            break;
        }
    }

    return status_ok(status);
}

bool path_folder_delete(Path *path, Status *status) {
    if (rmdir(path->local_path.array.elements) != 0) {
        switch (errno) {
        case EACCES:
        case EPERM:
            return permission_denied(status);
            break;
        case EBUSY:
            return file_busy(status);
            break;
        case EEXIST:
        case ENOTEMPTY:
            return folder_not_empty(status);
            break;
        case EFAULT:
            return invalid_memory_address(status);
            break;
        case EINVAL:
            return invalid_path(status);
            break;
        case EIO:
            return io_error(status);
            break;
        case ELOOP:
            return symbolic_link_depth_exceeded(status);
            break;
        case ENAMETOOLONG:
            return path_too_long(status);
            break;
        case ENOENT:
            return path_not_found(status);
            break;
        case ENOMEM:
            return out_of_memory(status);
            break;
        case ENOTDIR:
            return path_not_folder(status);
            break;
        case EROFS:
            return read_only_filesystem(status);
            break;
        default:
            return unknown_error(status);
            break;
        }
    }

    return status_ok(status);
}

bool path_file_create(Path *path, int mode, Status *status) {
    (void)path;
    (void)mode;
    (void)status;
    return status_propagate(status);
}

bool path_file_delete(Path *path, Status *status) {
    if (unlink(path->local_path.array.elements) != 0) {
        switch (errno) {
        case EACCES:
        case EPERM:
            /*
             * EPERM is overloaded like crazy, so give up and just return
             * permission denied; the user will have to figure it out.
             */
            return permission_denied(status);
            break;
        case EBUSY:
            return file_is_named_stream(status);
            break;
        case EFAULT:
            return invalid_memory_address(status);
            break;
        case EIO:
            return io_error(status);
            break;
        case EISDIR:
            return expected_folder(status);
            break;
        case ELOOP:
            return symbolic_link_depth_exceeded(status);
            break;
        case ENAMETOOLONG:
            return path_too_long(status);
            break;
        case ENOENT:
            return path_not_found(status);
            break;
        case ENOMEM:
            return out_of_memory(status);
            break;
        case ENOTDIR:
            return path_not_folder(status);
            break;
        case EROFS:
            return read_only_filesystem(status);
            break;
        case ETXTBSY:
            return file_busy(status);
            break;
        default:
            return unknown_error(status);
            break;
        }
    }

    return status_ok(status);
}

bool path_file_read(Path *path, Buffer *buffer, Status *status) {
    File *file = NULL;
    size_t file_size = 0;

    if (!path_size(path, &file_size, status)) {
        return status_propagate(status);
    }

    if (!buffer_ensure_capacity(buffer, buffer->array.len + file_size, status))
    {
        return status_propagate(status);
    }

    if (!path_file_open(path, &file, "rb", status)) {
        return status_propagate(status);
    }

    if (!file_read(file, buffer, file_size, sizeof(char), status)) {
        Status close_status;

        status_init(&close_status);

        /*
         * This is unfortunate, but just swallow this error.  The FILE* is
         * invalid at this point anyway (can't even call `fclose` on it again),
         * so there's nothing the user can really do anyway.  It would provide
         * more troubleshooting information, but too bad.
         */
        file_close(file, &close_status);

        return status_propagate(status);
    }

    return file_close(file, status);
}

bool path_file_open(Path *path,
                    File **file,
                    const char *mode,
                    Status *status) {
    FILE *fobj = fopen(path->local_path.array.elements, mode);

    if (!fobj) {
        switch (errno) {
        case EACCES:
            return permission_denied(status);
            break;
        case EDQUOT:
            return quota_exceeded(status);
            break;
        case EEXIST:
            return already_exists(status);
            break;
        case EFAULT:
            return invalid_memory_address(status);
            break;
        case EFBIG:
        case EOVERFLOW:
            return file_too_large(status);
            break;
        case EINTR:
            return operation_interrupted(status);
            break;
        case EINVAL:
            return invalid_mode_or_flags(status);
            break;
        case EISDIR:
            return expected_file(status);
            break;
        case ELOOP:
            return symbolic_link_depth_exceeded(status);
            break;
        case EMFILE:
            return per_process_file_limit_reached(status);
            break;
        case ENAMETOOLONG:
            return path_too_long(status);
            break;
        case ENFILE:
            return system_wide_file_limit_reached(status);
            break;
        case ENODEV:
        case ENXIO:
            return no_peer(status);
            break;
        case ENOENT:
            return path_not_found(status);
            break;
        case ENOMEM:
            return alloc_failure(status);
            break;
        case ENOSPC:
            return no_space(status);
            break;
        case ENOTDIR:
            return path_not_folder(status);
            break;
        case EOPNOTSUPP:
            return operation_not_supported(status);
            break;
        case EPERM:
            return permission_denied(status);
            break;
        case ETXTBSY:
            return file_busy(status);
            break;
        case EWOULDBLOCK:
            return would_block(status);
            break;
        default:
            return unknown_error(status);
            break;
        }
    }

    *file = (File *)fobj;

    return status_ok(status);
}

bool file_read(File *file,
               Buffer *buffer,
               size_t count,
               size_t size,
               Status *status) {
    FILE *fobj = (FILE *)file;
    size_t bytes_read = 0;
    size_t bytes_requested = 0;

    if (!check_overflow(count, size)) {
        return numeric_overflow(status);
    }

    bytes_requested = count * size;

    if (!buffer_ensure_capacity(buffer,
                                buffer->array.len + bytes_requested,
                                status))
    {
        return status_propagate(status);
    }

    bytes_read = fread(((char *)buffer->array.elements) + buffer->array.len,
                       size,
                       count,
                       fobj);

    buffer->array.len += bytes_read;

    if (bytes_read != bytes_requested) {
        if (feof(fobj)) {
            return path_end_of_file(status);
        }
        if (ferror(fobj) == -1) {
            return invalid_file_descriptor(status);
        }

        return unknown_error(status);
    }

    return status_ok(status);
}

bool file_read_raw(File *file, void *buf, size_t byte_count, Status *status) {
    FILE *fobj = (FILE *)file;
    size_t bytes_read = 0;

    bytes_read = fread(buf, byte_count, 1, fobj);

    if (bytes_read != byte_count) {
        if (feof(fobj)) {
            return path_end_of_file(status);
        }
        if (ferror(fobj) == -1) {
            return invalid_file_descriptor(status);
        }

        return unknown_error(status);
    }

    return status_ok(status);
}

bool file_close(File *file, Status *status) {
    FILE *fobj = (FILE *)file;

    if (fclose(fobj) == EOF) {
        switch (errno) {
        case EBADF:
            return invalid_file_descriptor(status);
            break;
        default:
            return unknown_error(status);
            break;
        }
    }

    return status_ok(status);
}

// ssize_t read(int fildes, void *buf, size_t nbyte);
// ssize_t write(int fildes, const void *buf, size_t nbyte);
// off_t lseek(int fildes, off_t offset, int whence);
// off_t lseek(int fildes, off_t offset, int whence);
// int close(int filedes);

/* vi: set et ts=4 sw=4: */
