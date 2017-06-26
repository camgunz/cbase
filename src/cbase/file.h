#ifndef FILE_H__
#define FILE_H__

typedef struct {
    SSlice dirname;
    SSlice basename;
    SSlice extension;
    String full_path;
} Path;

typedef void* File

void path_init(Path *path, const char *dirname, const char *basename,
                                                const char *extension);
bool path_init_from_local_full_path(Path *path, const char *local_full_path,
                                                Status *status);
bool path_new(Path **path, const char *dirname, const char *basename,
                                                const char *extension,
                                                Status *status);
bool path_new_from_local_full_path(Path **path, const char *local_full_path,
                                                Status *status);
bool path_get_local_full_path(Path *path, Status *status);
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

#if 0
bool        M_IterateFiles(const char *path, file_iterator iterator);
bool        M_WalkFiles(const char *path, file_walker walker);
bool        M_DeleteFolderAndContents(const char *path);
bool        M_ReadFromFile(void *ptr, size_t size, size_t count, FILE *f);
bool        M_WriteToFile(const void *ptr, size_t size, size_t count, FILE *f);
#endif
int         M_Open(const char *path, int flags, int mode);
bool        M_Close(int fd);
bool        M_Seek(int fd, off_t offset, int origin);
bool        M_Read(int fd, void *vbuf, size_t sz);
uint32_t    M_FDLength(int fd);
FILE*       M_OpenFile(const char *path, const char *mode);
FILE*       M_OpenFD(int fd, const char *mode);
bool        M_ReadFile(const char *path, char **data, size_t *size);
bool        M_ReadFileBuf(buf_t *buf, const char *path);
bool        M_WriteFile(const char* name, const char* source, size_t size);
long        M_GetFilePosition(FILE *f);
bool        M_SeekFile(FILE *f, long int offset, int origin);
uint32_t    M_FileLength(FILE *f);
bool        M_FlushFile(FILE *f);
bool        M_CloseFile(FILE *f);

#endif

/* vi: set et ts=4 sw=4: */
