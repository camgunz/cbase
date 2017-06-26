#ifndef FILE_H__
#define FILE_H__

const char* M_GetFileError(void);
char*       M_LocalizePath(const char *path);
char*       M_UnLocalizePath(const char *local_path);
bool        M_PathExists(const char *path);
char*       M_GetCurrentFolder(void);
bool        M_SetCurrentFolder(const char *path);
char*       M_Dirname(const char *path);
char*       M_Basename(const char *path);
bool        M_DirnameIsFolder(const char *path);
bool        M_PathJoinBuf(buf_t *buf, const char *one, const char *two);
char*       M_PathJoin(const char *one, const char *two);
bool        M_IsFolder(const char *path);
bool        M_IsFile(const char *path);
bool        M_IsRegularFile(const char *path);
bool        M_IsSymlink(const char *path);
bool        M_CheckAccess(const char *path, int flags);
bool        M_IsFileInFolder(const char *folder, const char *file);
bool        M_IsRootFolder(const char *path);
bool        M_IsAbsolutePath(const char *path);
char*       M_StripAbsolutePath(const char *path);
char*       M_StripExtension(const char *path);
bool        M_RenamePath(const char *oldpath, const char *newpath);

bool        M_CreateFolder(const char *path, int mode);
bool        M_CreateFile(const char *path, int mode);
bool        M_DeletePath(const char *path);
bool        M_DeleteFolder(const char *path);
bool        M_DeleteFile(const char *path);
bool        M_DeleteFileInFolder(const char *folder, const char *file);

GPtrArray*  M_ListFiles(const char *path);
bool        M_ListFilesBuf(const char *path, GPtrArray *files);
GPtrArray*  M_ListFolders(const char *path);
bool        M_ListFoldersBuf(const char *path, GPtrArray *folders);
GPtrArray*  M_ListFilesAndFolders(const char *path);
bool        M_ListFilesAndFoldersBuf(const char *path,
                                     GPtrArray *files_and_folders);

#if 0
bool        M_IterateFiles(const char *path, file_iterator iterator);
bool        M_WalkFiles(const char *path, file_walker walker);
bool        M_DeleteFolderAndContents(const char *path);
bool        M_ReadFromFile(void *ptr, size_t size, size_t count, FILE *f);
bool        M_WriteToFile(const void *ptr, size_t size, size_t count, FILE *f);
#endif

bool        M_ReadFile(const char *path, char **data, size_t *size);
bool        M_ReadFileBuf(buf_t *buf, const char *path);
bool        M_WriteFile(const char* name, const char *source, size_t size);

int         M_FDOpen(const char *path, int flags, int mode);
bool        M_FDClose(int fd);
bool        M_FDSeek(int fd, off_t offset, int origin);
bool        M_FDRead(int fd, void *vbuf, size_t sz);
uint32_t    M_FDLength(int fd);
FILE*       M_FileOpen(const char *path, const char *mode);
FILE*       M_FileFromFD(int fd, const char *mode);
bool        M_FileRead(FILE *f, char *data, size_t member_count,
                                            size_t member_size);
bool        M_FileWrite(FILE *f, const char *source, size_t member_count,
                                                     size_t member_size);
long        M_FileGetPosition(FILE *f);
bool        M_FileSeek(FILE *f, long int offset, int origin);
uint32_t    M_FileLength(FILE *f);
bool        M_FileFlush(FILE *f);
bool        M_FileClose(FILE *f);
int         M_FileGetFD(FILE *f);

// killough
void        M_ExtractFileBase(const char *path, char *dest);
// killough 1/18/98
char*       M_AddDefaultExtension(const char *path, const char *ext);
char*       M_SetFileExtension(const char *path, const char *ext);

#endif

/* vi: set et ts=4 sw=4: */
