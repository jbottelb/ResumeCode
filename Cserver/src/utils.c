/* utils.c: spidey utilities */

#include "spidey.h"

#include <ctype.h>
#include <errno.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>

#include <limits.h>
#include <stdlib.h>

/**
 * Determine mime-type from file extension.
 *
 * @param   path        Path to file.
 * @return  An allocated string containing the mime-type of the specified file.
 *
 * This function first finds the file's extension and then scans the contents
 * of the MimeTypesPath file to determine which mimetype the file has.
 *
 * The MimeTypesPath file (typically /etc/mime.types) consists of rules in the
 * following format:
 *
 *  <MIMETYPE>      <EXT1> <EXT2> ...
 *
 * This function simply checks the file extension version each extension for
 * each mimetype and returns the mimetype on the first match.
 *
 * If no extension exists or no matching mimetype is found, then return
 * DefaultMimeType.
 *
 * This function returns an allocated string that must be free'd.
 **/
char * determine_mimetype(const char *path)
{
    char *mimetype;

   /* Find file extension */
    char *ext = strrchr(path, '.');
    if( !ext )
    {
      debug("Extension does not exist");
      free(ext);
      mimetype = strdup(DefaultMimeType);
      return mimetype;
    }
    ext++;

    /* Open MimeTypesPath file */
    FILE *fs = fopen(MimeTypesPath, "r");

    /* Scan file for matching file extensions */
    char buffer[BUFSIZ];
    char *token;

    while( fgets(buffer, BUFSIZ, fs) )
    {
        if (buffer[0] == '#' || buffer[0] == '\n')
            continue;

        chomp(buffer);
        mimetype = strtok(buffer, WHITESPACE);
        token = buffer;

        while (token)
        {
            token = skip_whitespace(token);
            token = strtok(NULL, " ");
            if (!token)
                break;
            token = skip_whitespace(token);
            if (streq(token, ext))
            {
                return strdup(mimetype);
            }
        }
    }

    mimetype = DefaultMimeType;
    return strdup(mimetype);
}

/**
 * Determine actual filesystem path based on RootPath and URI.
 *
 * @param   uri         Resource path of URI.
 * @return  An allocated string containing the full path of the resource on the
 * local filesystem.
 *
 * This function uses realpath(3) to generate the realpath of the
 * file requested in the URI.
 *
 * As a security check, if the real path does not begin with the RootPath, then
 * return NULL.
 *
 * Otherwise, return a newly allocated string containing the real path.  This
 * string must later be free'd.
 **/
 char * determine_request_path(const char *uri)
 {
     char buff[BUFSIZ];
     sprintf(buff, "%s/%s", RootPath, uri);

     char buff2[BUFSIZ];
     if (!realpath(buff, buff2))
         log("error getting uri path");

     if (strncmp(RootPath, buff2, strlen(RootPath)) == 0)
     {
         return strdup(buff2);
     }
     else
         return NULL;
 }


/**
 * Return static string corresponding to HTTP Status code.
 *
 * @param   status      HTTP Status.
 * @return  Corresponding HTTP Status string (or NULL if not present).
 *
 * http://en.wikipedia.org/wiki/List_of_HTTP_status_codes
 **/
const char * http_status_string(Status status)
{
    // Slightly less efficient, but should avoid Segfaulting
    switch(status){
      case HTTP_STATUS_OK:                    return "200 OK";
      case HTTP_STATUS_BAD_REQUEST:           return "400 Bad Request";
      case HTTP_STATUS_NOT_FOUND:             return "404 Not Found";
      case HTTP_STATUS_INTERNAL_SERVER_ERROR: return "500 Internal Server Error";
      default:  return NULL;
    }

    return NULL;
}

/**
 * Advance string pointer pass all nonwhitespace characters
 *
 * @param   s           String.
 * @return  Point to first whitespace character in s.
 **/
char * skip_nonwhitespace(char *s)
{
    while( *s && !isspace(*s) ) { s++; }
    return s;
}

/**
 * Advance string pointer pass all whitespace characters
 *
 * @param   s           String.
 * @return  Point to first non-whitespace character in s.
 **/
char * skip_whitespace(char *s)
{
    while( *s && isspace(*s) ) { s++; }
    return s;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
