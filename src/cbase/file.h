#ifndef FILE_H__
#define FILE_H__

enum {
    PATH_PERMISSION_DENIED,
    PATH_INVALID_FILE_DESCRIPTOR,
    PATH_INVALID_MEMORY_ADDRESS,
    PATH_SYMBOLIC_LINK_DEPTH_EXCEEDED,
    PATH_TOO_LONG,
    PATH_NOT_FOUND,
    PATH_OUT_OF_MEMORY,
    PATH_NOT_FOLDER,
    PATH_READ_ONLY_FILESYSTEM,
    PATH_INVALID_MODE,
    PATH_IO_ERROR,
    PATH_FILE_BUSY,
    PATH_QUOTA_EXCEEDED,
    PATH_RENAME_TO_SUBFOLDER_OF_SELF,
    PATH_RENAME_FOLDER_TO_FILE,
    PATH_LINK_COUNT_EXCEEDED,
    PATH_DEVICE_FULL,
    PATH_FOLDER_NOT_EMPTY,
    PATH_STICKY_PERMISSION_DENIED,
    PATH_DIFFERENT_FILESYSTEMS,
    PATH_UNLINK_FOLDER,
    PATH_INVALID_PATH,
    PATH_HAS_NO_DIRNAME,
    PATH_HAS_NO_EXTENSION,
    PATH_END_OF_FILE,
    PATH_ALREADY_EXISTS,
    PATH_OPERATION_INTERRUPTED,
    PATH_INVALID_FLAGS,
    PATH_PER_PROCESS_FILE_LIMIT_REACHED,
    PATH_SYSTEM_WIDE_FILE_LIMIT_REACHED,
    PATH_NO_PEER,
    PATH_OPERATION_NOT_SUPPORTED,
    PATH_FILE_TOO_LARGE,
    PATH_WOULD_BLOCK,
    PATH_INVALID_MODE_OR_FLAGS,
    PATH_EXPECTED_FILE,
    PATH_EXPECTED_FOLDER,
    PATH_FOLDER_BUSY,
    PATH_NO_SPACE,
    PATH_FILE_IS_NAMED_STREAM,
    PATH_ALREADY_ROOT,
    PATH_SUBPATH_IS_ABSOLUTE,
    PATH_UNKNOWN_ERROR,
};

typedef struct {
    Buffer local_path;
    String normal_path;
} Path;

typedef void* File;

bool path_init(Path *path, SSlice *input, Status *status);
bool path_init_from_cstr(Path *path, const char *input, Status *status);
bool path_init_local(Path *path, Slice *input, Status *status);
bool path_new(Path **path, SSlice *input, Status *status);
bool path_new_from_cstr(Path **path, const char *input, Status *status);
bool path_new_local(Path **path, Slice *input, Status *status);
bool path_set(Path *path, SSlice *new_path, Status *status);
bool path_set_from_cstr(Path *path, const char *new_path, Status *status);
bool path_set_local(Path *path, Slice *new_path, Status *status);
bool path_dirname(Path *path, Path *out, Status *status);
bool path_basename(Path *path, SSlice *basename, Status *status);
bool path_extension(Path *path, SSlice *extension, Status *status);
bool path_strip_extension(Path *path, Status *status);
bool path_exists(Path *path, bool *exists, Status *status);
bool path_is_file(Path *path, bool *is_file, Status *status);
bool path_is_regular_file(Path *path, bool *is_regular_file, Status *status);
bool path_is_folder(Path *path, bool *is_folder, Status *status);
bool path_is_regular_file(Path *path, bool *is_regular_file, Status *status);
bool path_is_symlink(Path *path, bool *is_symlink, Status *status);
bool path_is_readable(Path *path, bool *readable, Status *status);
bool path_is_writable(Path *path, bool *writable, Status *status);
bool path_is_readable_and_writable(Path *path, bool *readable_and_writable,
                                               Status *status);
bool path_size(Path *path, size_t *size, Status *status);
bool path_rename(Path *old_path, Path *new_path, Status *status);
bool path_delete(Path *path, Status *status);
bool path_join(Path *path, SSlice *path_addition, Status *status);
bool path_join_cstr(Path *path, const char *path_addition, Status *status);

bool path_folder_create(Path *path, int mode, Status *status);
bool path_folder_delete(Path *path, Status *status);

/*
bool path_folder_list_files(Path *path, PArray *files, Status *status);
bool path_folder_list_folders(Path *path, PArray *folders, Status *status);
bool path_folder_list_files_and_folders(Path *path, PArray *files_and_folders,
                                                    Status *status);
*/

bool path_file_create(Path *path, int mode, Status *status);
bool path_file_delete(Path *path, Status *status);
bool path_file_read(Path *path, Buffer *buffer, Status *status);
/*
bool path_file_read_text(Path *path, String *string, Status *status);
bool path_file_read_local_text(Path *path, String *string, Status *status);
*/

bool path_file_open(Path *path, File **file, const char *mode, Status *status);
/*
bool path_file_fdopen(Path *path, int flags, int mode, int *fd,
                                                       Status *status);
*/

bool file_read(File *file, Buffer *buffer, size_t count, size_t size,
                                                         Status *status);
bool file_read_raw(File *file, void *buf, size_t byte_count, Status *status);
/*
bool file_write(File *file, Buffer *buffer, size_t byte_count, Status *status);
bool file_sync(File *file, Status *status);
bool file_seek(File *file, off_t offset, int whence, Status *status);
bool file_tell(File *file, size_t *pos, Status *status);
bool file_size(File *file, size_t *size, Status *status);
*/
bool file_close(File *file, Status *status);
/*
bool file_flush(File *file, Status *status);
bool file_is_eof(File *file);
bool file_has_error(File *file);
void file_clear_error(File *file);
int  file_get_fd(File *file);

bool file_fdread(int fd, void *buf, size_t byte_count, Status *status);
bool file_fdwrite(int fd, const void *buf, size_t byte_count, Status *status);
bool file_fdseek(int fd, off_t offset, int whence, Status *status);
bool file_fdtell(int fd, size_t *pos, Status *status);
bool file_fdsize(int fd, size_t *size, Status *status);
bool file_fdclose(int fd, Status *status);
*/

#endif

/* vi: set et ts=4 sw=4: */
