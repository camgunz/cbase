#ifndef FILE_H__
#define FILE_H__

typedef struct {
    Buffer local_path;
    String normal_path;
} Path;

typedef void* File

bool path_init(Path *path, Slice *path_slice, Status *status);
bool path_init_non_local(Path *path, Slice *non_local_path, Status *status);
bool path_init_non_local_from_cstr(Path *path, const char *non_local_path,
                                               Status *status);
bool path_new(Path **path, Slice *path_slice, Status *status);
bool path_new_non_local(Path *path, Slice *non_local_path, Status *status);
bool path_new_non_local_from_cstr(Path *path, const char *non_local_path,
                                              Status *status);
bool path_new(Path **path, Slice *path_slice, Status *status);
bool path_new_non_local(Path *path, Slice *non_local_path, Status *status);
bool path_new_non_local_from_cstr(Path *path, const char *non_local_path,
                                              Status *status);
bool path_set(Path *path, Slice *path_slice, Status *status);
bool path_set_non_local(Path *path, Slice *non_local_path, Status *status);
bool path_set_non_local_from_cstr(Path *path, const char *non_local_path,
                                              Status *status);
bool path_dirname(Path *path, SSlice *dirname, Status *status);
bool path_basename(Path *path, SSlice *basename, Status *status);
bool path_extension(Path *path, SSlice *extension, Status *status);

bool path_exists(Path *path, bool *exists, Status *status);
bool path_dirname_exists(Path *path, bool *exists, Status *status);
bool path_is_folder(Path *path, bool *is_folder, Status *status);
bool path_is_file(Path *path, bool *is_file, Status *status);
bool path_is_regular_file(Path *path, bool *is_regular_file, Status *status);
bool path_is_symlink(Path *path, bool *is_symlink, Status *status);
bool path_is_readable(Path *path, bool *readable, Status *status);
bool path_is_writable(Path *path, bool *writable, Status *status);
bool path_is_readable_and_writable(Path *path, bool *readable_and_writable,,
                                               Status *status);

bool path_strip_absolute_path(Path *path, Status *status);
bool path_strip_extension(Path *path, Status *status);
bool path_rename(Path *old_path, Path *new_path, Status *status);
bool path_delete(Path *path, Status *status);
bool path_join(Path *out, Path *path1, Path *path2, Status *status);

bool path_folder_contains_file(Path *path, const char *filename,
                                           bool *contains_file,
                                           Status *status);
bool path_folder_create(Path *path, int mode, Status *status);
bool path_folder_delete(Path *path, Status *status);
bool path_folder_delete_file(Path *path, const char *filename, Status *status);
bool path_folder_list_files(Path *path, PArray *files, Status *status);
bool path_folder_list_folders(Path *path, PArray *folders, Status *status);
bool path_folder_list_files_and_folders(Path *path, PArray *files_and_folders,
                                                    Status *status);

bool path_file_create(Path *path, int mode, Status *status);
bool path_file_delete(Path *path, Status *status);

bool path_file_open(Path *path, const char *mode);
bool path_file_fdopen(Path *path, int flags, int mode, int *fd,
                                                       Status *status);

bool file_read(File *file, void *buf, size_t byte_count, Status *status);
bool file_write(File *file, const void *buf, size_t byte_count, Status *status);
bool file_seek(File *file, off_t offset, int whence, Status *status);
bool file_tell(File *file, size_t *pos, Status *status);
bool file_size(File *file, size_t *size, Status *status);
bool file_close(File *file, Status *status);
bool file_flush(File *file, Status *status);
bool file_is_eof(File *file);
int  file_get_error(File *file);
void file_clear_error(File *file);
int  file_get_fd(File *file);

bool file_fdread(int fd, void *buf, size_t byte_count, Status *status);
bool file_fdwrite(int fd, const void *buf, size_t byte_count, Status *status);
bool file_fdseek(int fd, off_t offset, int whence, Status *status);
bool file_fdtell(int fd, size_t *pos, Status *status);
bool file_fdsize(int fd, size_t *size, Status *status);
bool file_fdclose(int fd, Status *status);

#endif

/* vi: set et ts=4 sw=4: */
