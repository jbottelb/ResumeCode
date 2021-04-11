/* handler.c: HTTP Request Handlers */

#include "spidey.h"

#include <errno.h>
#include <limits.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

/* Internal Declarations */
Status handle_browse_request(Request *request);
Status handle_file_request(Request *request);
Status handle_cgi_request(Request *request);
Status handle_error(Request *request, Status status);

/**
 * Handle HTTP Request.
 *
 * @param   r           HTTP Request structure
 * @return  Status of the HTTP request.
 *
 * This parses a request, determines the request path, determines the request
 * type, and then dispatches to the appropriate handler type.
 *
 * On error, handle_error should be used with an appropriate HTTP status code.
 **/
Status  handle_request(Request *r)
{
    Status result;

    debug("attempting to parse request");
    /* Parse Request */
    if (parse_request(r) < 0)
    {
        debug("bad request");
        return handle_error(r, HTTP_STATUS_BAD_REQUEST);
    }

    r->path = determine_request_path(r->uri);
    debug("HTTP REQUEST PATH: %s", r->path);

    if (r->path == NULL)
        return handle_error(r, HTTP_STATUS_NOT_FOUND);

    /* dispatch appropriate request handler type based on file type */
    struct stat s;

    int n = stat(r->path, &s);
    debug("handling a %i and path is %s", n, r->path);

    if( n < 0 )
    {
        result = HTTP_STATUS_NOT_FOUND;
        debug("Failed to find %s result %i", r->path, result);
        return handle_error(r, result);
    }

    if (n == 0)
    {
        if (S_ISDIR(s.st_mode) && access(r->path, R_OK) == 0)
        {
            debug("handling a directory");
            result = handle_browse_request(r);
            if (result != HTTP_STATUS_OK)
                handle_error(r, result);
        }
        else if (access(r->path, X_OK) == 0)
        {
            debug("handling a cgi request");
            result = handle_cgi_request(r);
            if (result != HTTP_STATUS_OK)
                handle_error(r, result);
        }
        else if (S_ISREG(s.st_mode) && access(r->path, R_OK) == 0)
        {
            debug("handling a file");
            result = handle_file_request(r);
            if (result != HTTP_STATUS_OK)
                handle_error(r, result);
        }
        else
        {
            result = HTTP_STATUS_NOT_FOUND;
            debug("Failed to find %s result %i", r->path, result);
            handle_error(r, result);
        }
    }

    return HTTP_STATUS_OK;
}

/**
 * Handle browse request.
 *
 * @param   r           HTTP Request structure.
 * @return  Status of the HTTP browse request.
 *
 * This lists the contents of a directory in HTML.
 *
 * If the path cannot be opened or scanned as a directory, then handle error
 * with HTTP_STATUS_NOT_FOUND.
 **/
Status  handle_browse_request(Request *r)
{
    struct dirent **entries;
    int n = scandir(r->path, &entries, NULL, alphasort);

    /* Open a directory for reading or scanning */
    if (n < 0)
    {
        return handle_error(r, HTTP_STATUS_NOT_FOUND);
    }

    debug("Sending dir info...");

    /* Write HTTP Header with OK Status and text/html Content-Type */
    fprintf(r->stream, "HTTP/1.0 200 OK\r\n");
    fprintf(r->stream, "Content-Type: text/html\r\n");
    fprintf(r->stream, "\r\n");

    debug("open path for dir: %s", r->path);
    /* For each entry in directory, emit HTML list item */
    fprintf(r->stream, "<ul>\n");
    for (int i = 0; i < n; i++)
    {
        if (strcmp(".", entries[i]->d_name) == 0)
            continue;

        if (!strcmp(&r->uri[strlen(r->uri)-1], "/")){
            fprintf(r->stream, "<li><a href=\"%s%s\">%s\r\n</a></li>", r->uri, entries[i]->d_name, entries[i]->d_name);
        }
        else
        {
           fprintf(r->stream, "<li><a href=\"%s/%s\">%s\r\n</a></li>\n", r->uri, entries[i]->d_name, entries[i]->d_name);
        }
    }

    for (int i = 0; i < n; i++)
        free(entries[i]);

    free(entries);
    fprintf(r->stream, "</ul>\n");

    debug("info sent");

    return HTTP_STATUS_OK;
}

/**
 * Handle file request.
 *
 * @param   r           HTTP Request structure.
 * @return  Status of the HTTP file request.
 *
 * This opens and streams the contents of the specified file to the socket.
 *
 * If the path cannot be opened for reading, then handle error with
 * HTTP_STATUS_NOT_FOUND.
 **/
Status  handle_file_request(Request *r)
{
    FILE *fs;
    char buffer[BUFSIZ];

    /* Open file for reading */

    fs = fopen(r->path, "r");

    if (!fs)
        return handle_error(r, HTTP_STATUS_NOT_FOUND);

    /* Determine mimetype */
    char *mimetype = determine_mimetype(r->path);
    if (!mimetype)
    {
        debug("Mimetype not found. Defaulting");
        mimetype = strdup(DefaultMimeType);
    }

    log("MT: %s", mimetype);

    /* Write HTTP Headers with OK status and determined Content-Type */
    fprintf(r->stream, "HTTP/1.0 200 OK\r\n");
    fprintf(r->stream, "Content-Type: %s\r\n", mimetype);
    fprintf(r->stream, "\r\n");

    /* Read from file and write to socket in chunks */
    size_t nread = fread(buffer, 1, BUFSIZ, fs);
    while (nread > 0)
    {
        fwrite(buffer, 1, nread, r->stream);
        nread = fread(buffer, 1, BUFSIZ, fs);
    }

    /* Close file, deallocate mimetype, return OK */
    free(mimetype);
    fclose(fs);
    return HTTP_STATUS_OK;
}

/**
 * Handle CGI request
 *
 * @param   r           HTTP Request structure.
 * @return  Status of the HTTP file request.
 *
 * This popens and streams the results of the specified executables to the
 * socket.
 *
 * If the path cannot be popened, then handle error with
 * HTTP_STATUS_INTERNAL_SERVER_ERROR.
 **/
Status  handle_cgi_request(Request *r)
{
    /* Export CGI environment variables from request headers */

    setenv("DOCUMENT_ROOT", RootPath, 1);
    setenv("QUERY_STRING", r->query, 1);
    setenv("REMOTE_ADDR", r->host, 1);
    setenv("REMOTE_PORT", r->port, 1);
    setenv("REQUEST_METHOD", r->method, 1);
    setenv("REQUEST_URI", r->uri, 1);
    setenv("SCRIPT_FILENAME", r->path, 1);
    setenv("SERVER_PORT", Port, 1);

    for( Header *h = r->headers; h != NULL; h = h->next )
    {
      if(strlen(h->name) > 0){
        if(streq("Host", h->name)){
          setenv("HTTP_HOST", h->data, 1);
        }
        else if(streq("User-Agent", h->name)){
          setenv("HTTP_USER_AGENT", h->data, 1);
        }
      }
    }

    /* POpen CGI Script */
    FILE *pfs = popen(r->path, "r");       // where the first arg is the script that is run
    if(!pfs){
      debug("Path %s could not be opened", r->path);
      return handle_error(r, HTTP_STATUS_NOT_FOUND);
    }

    /* Copy data from popen to socket */
    char buffer[BUFSIZ];
    while (fgets(buffer, BUFSIZ, pfs))
    {
        fputs(buffer, r->stream);
    }

    /* Close popen, return OK */
    pclose(pfs);
    return HTTP_STATUS_OK;
}

/**
 * Handle displaying error page
 *
 * @param   r           HTTP Request structure.
 * @return  Status of the HTTP error request.
 *
 * This writes an HTTP status error code and then generates an HTML message to
 * notify the user of the error.
 **/
Status  handle_error(Request *r, Status status)
{
    const char *status_string = http_status_string(status);

    /* Write HTTP Header */
    fprintf(r->stream, "HTTP/1.0 %s\r\n", status_string);
    fprintf(r->stream, "Content-Type: text/html\r\n\r\n");

    /* Write HTML Description of Error*/
    fprintf(r->stream, "<h2>%s</h2>", status_string);

    /* Return specified status */
    return status;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
