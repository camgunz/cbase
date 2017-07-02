#include "cbase.h"

#include <stdio.h>

#include <unistd.h>
#include <sys/stat.h>

#define INIT_BUFFER_ALLOC 64

#define permission_denied(status) status_error( \
    status,                                     \
    "path",                                     \
    PATH_PERMISSION_DENIED,                     \
    "path has no dirname"                       \
)

#define invalid_file_descriptor(status) status_error( \
    status,                                           \
    "path",                                           \
    PATH_INVALID_FILE_DESCRIPTOR,                     \
    "invalid file descriptor"                         \
)

#define invalid_memory_address(status) status_error( \
    status,                                          \
    "path",                                          \
    PATH_INVALID_MEMORY_ADDRESS,                     \
    "invalid memory address"                         \
)

#define symbolic_link_depth_exceeded(status) status_error( \
    status,                                                \
    "path",                                                \
    PATH_SYMBOLIC_LINK_DEPTH_EXCEEDED,                     \
    "symbolic link depth exceeded"                         \
)

#define path_too_long(status) status_error( \
    status,                                 \
    "path",                                 \
    PATH_TOO_LONG,                          \
    "path too long"                         \
)

#define path_not_found(status) status_error( \
    status,                                  \
    "path",                                  \
    PATH_NOT_FOUND,                          \
    "path not found"                         \
)

#define out_of_memory(status) status_error( \
    status,                                 \
    "path",                                 \
    PATH_OUT_OF_MEMORY,                     \
    "out of memory"                         \
)

#define path_not_folder(status) status_error( \
    status,                                   \
    "path",                                   \
    PATH_NOT_FOLDER,                          \
    "path or path component is not a folder"  \
)

#define data_overflow(status) status_error( \
    status,                                 \
    "path",                                 \
    PATH_INVALID_FILE_DESCRIPTOR,           \
    "invalid file descriptor"               \
)

#define invalid_mode(status) status_error( \
    status,                                \
    "path",                                \
    PATH_INVALID_MODE,                     \
    "invalid mode"                         \
)

#define read_only_filesystem(status) status_error( \
    status,                                        \
    "path",                                        \
    PATH_READ_ONLY_FILESYSTEM,                     \
    "read-only filesystem"                         \
)

#define io_error(status) status_error( \
    status,                            \
    "path",                            \
    PATH_IO_ERROR,                     \
    "i/o error"                        \
)

#define file_busy(status) status_error( \
    status,                             \
    "path",                             \
    PATH_FILE_BUSY,                     \
    "file busy"                         \
)

#define quota_exceeded(status) status_error( \
    status,                                  \
    "path",                                  \
    PATH_QUOTA_EXCEEDED,                     \
    "quota exceeded"                         \
)

#define rename_to_subfolder_of_self(status) status_error( \
    status,                                               \
    "path",                                               \
    PATH_RENAME_TO_SUBFOLDER_OF_SELF,                     \
    "path renamed to a subfolder of itself"               \
)

#define rename_folder_to_file(status) status_error( \
    status,                                         \
    "path",                                         \
    PATH_RENAME_FOLDER_TO_FILE,                     \
    "new path is a folder, but old path is not"     \
)

#define link_count_exceeded(status) status_error( \
    status,                                       \
    "path",                                       \
    PATH_LINK_COUNT_EXCEEDED,                     \
    "link count exceeded"                         \
)

#define device_full(status) status_error( \
    status,                               \
    "path",                               \
    PATH_DEVICE_FULL,                     \
    "device full"                         \
)

#define folder_not_empty(status) status_error( \
    status,                                    \
    "path",                                    \
    PATH_FOLDER_NOT_EMPTY,                     \
    "folder not empty"                         \
)

#define sticky_permission_denied(status) status_error( \
    status,                                            \
    "path",                                            \
    PATH_STICKY_PERMISSION_DENIED,                     \
    "permission denied (sticky)"                       \
)

#define different_filesystems(status) status_error( \
    status,                                         \
    "path",                                         \
    PATH_DIFFERENT_FILESYSTEMS,                     \
    "operation not allowed across filesystems"      \
)

#define unlink_folder(status) status_error( \
    status,                                 \
    "path",                                 \
    PATH_UNLINK_FOLDER,                     \
    "attempted to unlink folder"            \
)

#define invalid_path(status) status_error( \
    status,                                \
    "path",                                \
    PATH_INVALID_PATH,                     \
    "invalid path"                         \
)

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

#define path_end_of_file(status) status_error( \
    status,                                    \
    "path",                                    \
    PATH_END_OF_FILE,                          \
    "end of file"                              \
)

#define already_exists(status) status_error( \
    status,                                  \
    "path",                                  \
    PATH_ALREADY_EXISTS,                     \
    "path already exists"                    \
)

#define operation_interrupted(status) status_error( \
    status,                                         \
    "path",                                         \
    PATH_OPERATION_INTERRUPTED,                     \
    "operation interrupted"                         \
)

#define invalid_flags(status) status_error( \
    status,                                 \
    "path",                                 \
    PATH_INVALID_FLAGS,                     \
    "invalid flags"                         \
)

#define per_process_file_limit_reached(status) status_error( \
    status,                                                  \
    "path",                                                  \
    PATH_PER_PROCESS_FILE_LIMIT_REACHED,                     \
    "per-process file limit reached"                         \
)

#define system_wide_file_limit_reached(status) status_error( \
    status,                                                  \
    "path",                                                  \
    PATH_SYSTEM_WIDE_FILE_LIMIT_REACHED,                     \
    "system-wide file limit reached"                         \
)

#define no_peer(status) status_error( \
    status,                           \
    "path",                           \
    PATH_NO_PEER,                     \
    "no peer on other side of file"   \
)

#define operation_not_supported(status) status_error( \
    status,                                           \
    "path",                                           \
    PATH_OPERATION_NOT_SUPPORTED,                     \
    "operation not supported"                         \
)

#define file_too_large(status) status_error( \
    status,                                  \
    "path",                                  \
    PATH_FILE_TOO_LARGE,                     \
    "file too large"                         \
)

#define would_block(status) status_error( \
    status,                               \
    "path",                               \
    PATH_WOULD_BLOCK,                     \
    "operation would block"               \
)

#define invalid_mode_or_flags(status) status_error( \
    status,                                         \
    "path",                                         \
    PATH_INVALID_MODE_OR_FLAGS,                     \
    "invalid mode or flags"                         \
)

#define expected_file(status) status_error( \
    status,                                 \
    "path",                                 \
    PATH_EXPECTED_FILE,                     \
    "expected file"                         \
)

#define expected_folder(status) status_error( \
    status,                                   \
    "path",                                   \
    PATH_EXPECTED_FOLDER,                     \
    "expected folder"                         \
)

#define folder_busy(status) status_error( \
    status,                               \
    "path",                               \
    PATH_FOLDER_BUSY,                     \
    "folder busy"                         \
)

#define no_space(status) status_error( \
    status,                            \
    "path",                            \
    PATH_NO_SPACE,                     \
    "no space"                         \
)

#define file_is_named_stream(status) status_error( \
    status,                                        \
    "path",                                        \
    PATH_FILE_IS_NAMED_STREAM,                     \
    "file is named_stream"                         \
)

#define is_already_root(status) status_error( \
    status,                                   \
    "path",                                   \
    PATH_ALREADY_ROOT,                        \
    "path is already the root path"           \
)

#define unknown_error(status) status_error( \
    status,                                 \
    "path",                                 \
    PATH_UNKNOWN_ERROR,                     \
    "unknown error"                         \
)

static bool canonicalize_path(Path *path, Status *status) {
    char buf[PATH_MAX + 1];
    char *canonicalized_path = realpath(path->normal_path.data, buf);

    if (!canonicalized_path) {
        switch (errno) {
            case EACCES:
                return permission_denied(status);
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
            default:
                return unknown_error(status);
                break;
        }
    }

    string_clear(&path->normal_path);

    return string_assign(&path->normal_path, buf, status);
}

static bool rebuild_normal_path(Path *path, Status *status) {
    Slice ss;

    if (!buffer_slice(&path->local_path, 0, path->local_path.len, &ss,
                                                                  status)) {
        return false;
    }

    string_clear(&path->normal_path);

    return charset_unlocalize_to_string(&ss, &path->normal_path, status);
}

static bool rebuild_local_path(Path *path, Status *status) {
    SSlice ss;

    if (!string_slice(&path->normal_path, 0, path->normal_path.len, &ss,
                                                                    status)) {
        return false;
    }

    buffer_clear(&path->local_path);

    return charset_localize_from_string(&ss, &path->local_path, status);
}

static bool base_set_local_path(Path *path, Slice *input, bool init,
                                                          Status *status) {
    if (init) {
        if (!string_init(&path->normal_path, "", status)) {
            return false;
        }
    }

    return (
        charset_unlocalize_to_string(input, &path->normal_path, status) &&
        rebuild_normal_path(path, status)
    );
}

static bool base_set_normal_path(Path *path, Slice *input, bool init,
                                                           Status *status) {
    SSlice ss;

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

    if (!string_slice(&path->normal_path, 0, path->normal_path.len,
                                             &ss,
                                             status)) {
        if (init) {
            string_free(&path->normal_path);
        }
        else {
            string_clear(&path->normal_path);
        }

        return false;
    }

    if (!charset_localize_from_string(&ss, &path->local_path, status)) {
        if (init) {
            string_free(&path->normal_path);
        }
        else {
            string_clear(&path->normal_path);
        }

        return false;
    }

    return rebuild_normal_path(path, status);
}

static bool base_set_path(Path *path, Slice *input, bool init,
                                                    bool local,
                                                    Status *status) {
    if (local) {
        return base_set_local_path(path, input, init, status);
    }

    return base_set_normal_path(path, input, init, status);
}

static inline bool set_path(Path *path, Slice *input, bool local,
                                                      Status *status) {
    return base_set_path(path, input, false, local, status);
}

static inline bool init_path(Path *path, Slice *input, bool local,
                                                       Status *status) {
    return base_set_path(path, input, true, local, status);
}

static bool stat_path(const char *path, struct stat *stat_obj, Status *status) {
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

bool path_new_non_local(Path **path, Slice *non_local_path, Status *status) {
    Path *new_path = cbmalloc(1, sizeof(Path));

    if (!new_path) {
        return alloc_failure(status);
    }

    if (!path_init_non_local(new_path, non_local_path, status)) {
        cbfree(new_path);
        return false;
    }

    *path = new_path;

    return true;
}

bool path_new_non_local_from_cstr(Path **path, const char *non_local_path,
                                              Status *status) {
    Path *new_path = cbmalloc(1, sizeof(Path));

    if (!new_path) {
        return alloc_failure(status);
    }

    if (!path_init_non_local_from_cstr(new_path, non_local_path, status)) {
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
    return set_path(path, non_local_path, false, status);
}

bool path_set_non_local_from_cstr(Path *path, const char *non_local_path,
                                              Status *status) {
    Slice s;

    s.data = (char *)non_local_path;
    s.len = strlen(non_local_path);

    return path_set_non_local(path, &s, status);
}

bool path_dirname(Path *path, SSlice *dirname, Status *status) {
    if (!string_slice(&path->normal_path, 0, path->normal_path.len, dirname,
                                                                    status)) {
        return false;
    }

    if (!sslice_truncate_at(dirname, '/', status)) {
        sslice_clear(dirname);

        if (status_match(status, "base", ERROR_NOT_FOUND)) {
            return path_has_no_dirname(status);
        }

        return false;
    }

    return true;
}

bool path_basename(Path *path, SSlice *basename, Status *status) {
    if (!string_slice(&path->normal_path, 0, path->normal_path.len, basename,
                                                                    status)) {
        return false;
    }

    while (true) {
        if (!sslice_seek_to(basename, '/', status)) {
            if (!status_match(status, "base", ERROR_NOT_FOUND)) {
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

        if (status_match(status, "base", ERROR_NOT_FOUND)) {
            return path_has_no_extension(status);
        }

        return false;
    }

    return sslice_skip_rune(extension, status);
}

bool path_strip_extension(Path *path, Status *status) {
    SSlice extension;

    return (
        path_extension(path, &extension, status) &&
        string_truncate(&path->normal_path, extension.len, status) &&
        rebuild_local_path(path, status)
    );
}

bool path_exists(Path *path, bool *exists, Status *status) {
    struct stat stat_obj;

    if (stat_path(path->local_path.data, &stat_obj, status)) {
        *exists = true;
    } else if (status_match(status, "path", PATH_NOT_FOUND)) {
        *exists = false;
    }
    else {
        return false;
    }

    return true;
}

bool path_dirname_exists(Path *path, bool *exists, Status *status) {
    SSlice dirname;
    Buffer local_dirname;
    struct stat stat_obj;

    if (!path_dirname(path, &dirname, status)) {
        return false;
    }

    buffer_init(&local_dirname);

    if (!charset_localize_from_string(&dirname, &local_dirname, status)) {
        buffer_free(&local_dirname);
    }

    if (!stat_path(local_dirname.data, &stat_obj, status)) {
        if (status_match(status, "path", PATH_NOT_FOUND)) {
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

bool path_set_to_dirname(Path *path, Status *status) {
    size_t dir_count = 0;
    SSlice dirname;

    for (size_t i = 0; i < path->normal_path.byte_len; i++) {
        if (path->normal_path.data[i] == '/') {
            dir_count++;
            if (dir_count > 1) {
                break;
            }
        }
    }

    if (dir_count < 2) {
        return is_already_root(status);
    }

    return (
        path_dirname(path, &dirname, status) &&
        string_truncate(
            &path->normal_path,
            path->normal_path.len - dirname.len,
            status
        ) &&
        rebuild_local_path(path, status)
    );
}

bool path_is_file(Path *path, bool *is_file, Status *status) {
    struct stat stat_obj;

    if (!stat_path(path->local_path.data, &stat_obj, status)) {
        return false;
    }

    *is_file = (
        ((stat_obj.st_mode & S_IFBLK ) == S_IFBLK ) ||
        ((stat_obj.st_mode & S_IFCHR ) == S_IFCHR ) ||
        ((stat_obj.st_mode & S_IFIFO ) == S_IFIFO ) ||
        ((stat_obj.st_mode & S_IFREG ) == S_IFREG ) ||
        ((stat_obj.st_mode & S_IFLNK ) == S_IFLNK ) ||
        ((stat_obj.st_mode & S_IFSOCK) == S_IFSOCK)
    );

    return true;
}

bool path_is_regular_file(Path *path, bool *is_regular_file, Status *status) {
    struct stat stat_obj;

    if (!stat_path(path->local_path.data, &stat_obj, status)) {
        return false;
    }

    *is_regular_file = ((stat_obj.st_mode & S_IFREG) == S_IFREG);

    return true;
}

bool path_is_folder(Path *path, bool *is_folder, Status *status) {
    struct stat stat_obj;

    if (!stat_path(path->local_path.data, &stat_obj, status)) {
        return false;
    }

    *is_folder = ((stat_obj.st_mode & S_IFDIR) == S_IFDIR);

    return true;
}

bool path_is_symlink(Path *path, bool *is_symlink, Status *status) {
    struct stat stat_obj;

    if (!stat_path(path->local_path.data, &stat_obj, status)) {
        return false;
    }

    *is_symlink = ((stat_obj.st_mode & S_IFLNK) == S_IFLNK);

    return true;
}

bool path_is_readable(Path *path, bool *readable, Status *status) {
    if (access(path->local_path.data, R_OK) == 0) {
        *readable = true;
        return true;
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

    return true;
}

bool path_is_writable(Path *path, bool *writable, Status *status) {
    if (access(path->local_path.data, W_OK) == 0) {
        *writable = true;
        return true;
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

    return true;
}

bool path_is_readable_and_writable(Path *path, bool *readable_and_writable,
                                               Status *status) {
    if (access(path->local_path.data, R_OK | W_OK) == 0) {
        *readable_and_writable = true;
        return true;
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

    return true;
}

bool path_size(Path *path, size_t *size, Status *status) {
    struct stat stat_buf;

    if (!stat_path(path->local_path.data, &stat_buf, status)) {
        return false;
    }

    *size = (size_t)stat_buf.st_size;

    return true;
}

bool path_rename(Path *old_path, Path *new_path, Status *status) {
    if (rename(old_path->local_path.data, new_path->local_path.data) != 0) {

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

    return true;
}

bool path_delete(Path *path, Status *status) {
    if (remove(path->local_path.data) != 0) {
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

    return true;
}

bool path_join(Path *out, Path *path1, const char *path2, Status *status) {
    string_clear(&out->normal_path);

    return (
        string_copy(&out->normal_path, &path1->normal_path, status) &&
        string_ensure_capacity(
            &out->normal_path,
            out->normal_path.byte_len + strlen(path2) + 1,
            status
        ) &&
        string_append_cstr(&out->normal_path, "/", status) &&
        string_append_cstr(&out->normal_path, path2, status) &&
        canonicalize_path(out, status) &&
        rebuild_local_path(out, status)
    );
}

bool path_folder_create(Path *path, int mode, Status *status) {
    if (mkdir(path->local_path.data, mode) != 0) {
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

    return true;
}

bool path_folder_delete(Path *path, Status *status) {
    if (rmdir(path->local_path.data) != 0) {
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

    return true;
}

bool path_file_create(Path *path, int mode, Status *status) {
    (void)path;
    (void)mode;
    (void)status;
    return false;
}

bool path_file_delete(Path *path, Status *status) {
    if (unlink(path->local_path.data) != 0) {
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

    return true;
}

bool path_file_read(Path *path, Buffer *buffer, Status *status) {
    File *file = NULL;
    size_t file_size = 0;

    if (!path_size(path, &file_size, status)) {
        return false;
    }

    if (!buffer_ensure_capacity(buffer, buffer->len + file_size, status)) {
        return false;
    }

    if (!path_file_open(path, &file, "rb", status)) {
        return false;
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

        return false;
    }

    return file_close(file, status);
}

bool path_file_open(Path *path, File **file, const char *mode, Status *status) {
    FILE *fobj = fopen(path->local_path.data, mode);

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
    return true;
}

bool file_read(File *file, Buffer *buffer, size_t count, size_t size,
                                                         Status *status) {
    FILE *fobj = (FILE *)file;
    size_t bytes_read = 0;
    size_t bytes_requested = 0;

    if (!check_overflow(count, size)) {
        return numeric_overflow(status);
    }

    bytes_requested = count * size;

    if (!buffer_ensure_capacity(buffer, buffer->len + bytes_requested, status)) {
        return false;
    }

    bytes_read = fread(buffer->data + buffer->len, size, count, fobj);

    buffer->len += bytes_read;

    if (bytes_read != bytes_requested) {
        if (feof(fobj)) {
            return path_end_of_file(status);
        }
        if (ferror(fobj) == -1) {
            return invalid_file_descriptor(status);
        }

        return unknown_error(status);
    }

    return true;
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

    return true;
}

// ssize_t read(int fildes, void *buf, size_t nbyte);
// ssize_t write(int fildes, const void *buf, size_t nbyte);
// off_t lseek(int fildes, off_t offset, int whence);
// off_t lseek(int fildes, off_t offset, int whence);
// int close(int filedes);

/* vi: set et ts=4 sw=4: */
