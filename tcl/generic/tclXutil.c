/*
 * tclXutil.c
 *
 * Utility functions for Extended Tcl.
 *-----------------------------------------------------------------------------
 * Copyright 1991-1993 Karl Lehenbauer and Mark Diekhans.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies.  Karl Lehenbauer and
 * Mark Diekhans make no representations about the suitability of this
 * software for any purpose.  It is provided "as is" without express or
 * implied warranty.
 *-----------------------------------------------------------------------------
 * $Id: tclXutil.c,v 2.4 1993/05/04 06:29:22 markd Exp markd $
 *-----------------------------------------------------------------------------
 */

#include "tclExtdInt.h"

#ifndef _tolower
#  define _tolower tolower
#  define _toupper toupper
#endif

/*
 * Used to return argument messages by most commands.
 */
char *tclXWrongArgs = "wrong # args: ";

#ifndef pow
extern double pow ();
#endif


/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_StrToLong --
 *      Convert an Ascii string to an long number of the specified base.
 *
 * Parameters:
 *   o string (I) - String containing a number.
 *   o base (I) - The base to use for the number 8, 10 or 16 or zero to decide
 *     based on the leading characters of the number.  Zero to let the number
 *     determine the base.
 *   o longPtr (O) - Place to return the converted number.  Will be 
 *     unchanged if there is an error.
 *
 * Returns:
 *      Returns 1 if the string was a valid number, 0 invalid.
 *-----------------------------------------------------------------------------
 */
int
Tcl_StrToLong (string, base, longPtr)
    CONST char *string;
    int         base;
    long       *longPtr;
{
    char *end;
    long  num;

    num = strtol(string, &end, base);
    while ((*end != '\0') && isspace(*end)) {
        end++;
    }
    if ((end == string) || (*end != 0))
        return FALSE;
    *longPtr = num;
    return TRUE;

}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_StrToInt --
 *      Convert an Ascii string to an number of the specified base.
 *
 * Parameters:
 *   o string (I) - String containing a number.
 *   o base (I) - The base to use for the number 8, 10 or 16 or zero to decide
 *     based on the leading characters of the number.  Zero to let the number
 *     determine the base.
 *   o intPtr (O) - Place to return the converted number.  Will be 
 *     unchanged if there is an error.
 *
 * Returns:
 *      Returns 1 if the string was a valid number, 0 invalid.
 *-----------------------------------------------------------------------------
 */
int
Tcl_StrToInt (string, base, intPtr)
    CONST char *string;
    int         base;
    int        *intPtr;
{
    char *end;
    int   num;

    num = strtol(string, &end, base);
    while ((*end != '\0') && isspace(*end)) {
        end++;
    }
    if ((end == string) || (*end != 0))
        return FALSE;
    *intPtr = num;
    return TRUE;

}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_StrToUnsigned --
 *      Convert an Ascii string to an unsigned int of the specified base.
 *
 * Parameters:
 *   o string (I) - String containing a number.
 *   o base (I) - The base to use for the number 8, 10 or 16 or zero to decide
 *     based on the leading characters of the number.  Zero to let the number
 *     determine the base.
 *   o unsignedPtr (O) - Place to return the converted number.  Will be 
 *     unchanged if there is an error.
 *
 * Returns:
 *      Returns 1 if the string was a valid number, 0 invalid.
 *-----------------------------------------------------------------------------
 */
int
Tcl_StrToUnsigned (string, base, unsignedPtr)
    CONST char *string;
    int         base;
    unsigned   *unsignedPtr;
{
    char          *end;
    unsigned long  num;

    num = strtoul (string, &end, base);
    while ((*end != '\0') && isspace(*end)) {
        end++;
    }
    if ((end == string) || (*end != 0))
        return FALSE;
    *unsignedPtr = num;
    return TRUE;

}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_StrToDouble --
 *   Convert a string to a double percision floating point number.
 *
 * Parameters:
 *   string (I) - Buffer containing double value to convert.
 *   doublePtr (O) - The convert floating point number.
 * Returns:
 *   TRUE if the number is ok, FALSE if it is illegal.
 *-----------------------------------------------------------------------------
 */
int
Tcl_StrToDouble (string, doublePtr)
    CONST char *string;
    double     *doublePtr;
{
    char   *end;
    double  num;

    num = strtod (string, &end);
    while ((*end != '\0') && isspace(*end)) {
        end++;
    }
    if ((end == string) || (*end != 0))
        return FALSE;

    *doublePtr = num;
    return TRUE;

}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_DownShift --
 *     Utility procedure to down-shift a string.  It is written in such
 *     a way as that the target string maybe the same as the source string.
 *
 * Parameters:
 *   o targetStr (I) - String to store the down-shifted string in.  Must
 *     have enough space allocated to store the string.  If NULL is specified,
 *     then the string will be dynamicly allocated and returned as the
 *     result of the function. May also be the same as the source string to
 *     shift in place.
 *   o sourceStr (I) - The string to down-shift.
 *
 * Returns:
 *   A pointer to the down-shifted string
 *-----------------------------------------------------------------------------
 */
char *
Tcl_DownShift (targetStr, sourceStr)
    char       *targetStr;
    CONST char *sourceStr;
{
    register char theChar;

    if (targetStr == NULL)
        targetStr = ckalloc (strlen ((char *) sourceStr) + 1);

    for (; (theChar = *sourceStr) != '\0'; sourceStr++) {
        if (isupper (theChar))
            theChar = _tolower (theChar);
        *targetStr++ = theChar;
    }
    *targetStr = '\0';
    return targetStr;
}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_UpShift --
 *     Utility procedure to up-shift a string.
 *
 * Parameters:
 *   o targetStr (I) - String to store the up-shifted string in.  Must
 *     have enough space allocated to store the string.  If NULL is specified,
 *     then the string will be dynamicly allocated and returned as the
 *     result of the function. May also be the same as the source string to
 *     shift in place.
 *   o sourceStr (I) - The string to up-shift.
 *
 * Returns:
 *   A pointer to the up-shifted string
 *-----------------------------------------------------------------------------
 */
char *
Tcl_UpShift (targetStr, sourceStr)
    char       *targetStr;
    CONST char *sourceStr;
{
    register char theChar;

    if (targetStr == NULL)
        targetStr = ckalloc (strlen ((char *) sourceStr) + 1);

    for (; (theChar = *sourceStr) != '\0'; sourceStr++) {
        if (islower (theChar))
            theChar = _toupper (theChar);
        *targetStr++ = theChar;
    }
    *targetStr = '\0';
    return targetStr;
}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_DStringGets --
 *
 *    Reads a line from a file into a dynamic string.  The string will be
 * expanded, if necessary and reads are done until EOL or EOF is reached.
 *
 * Parameter
 *   o filePtr (I) - File to read from.
 *   o dynStrPtr (I) - String to return the data in.
 * Returns:
 *    0 - EOF
 *    1 - If data was transfered.
 *   -1 - An error occured.
 *-----------------------------------------------------------------------------
 */
int
Tcl_DStringGets (filePtr, dynStrPtr)
    FILE         *filePtr;
    Tcl_DString  *dynStrPtr;
{
    char           buffer [128];
    register char *bufPtr, *bufEnd;
    register int   readVal;

    Tcl_DStringFree (dynStrPtr);

    bufPtr = buffer;
    bufEnd = buffer + sizeof (buffer) - 1;

    while (TRUE) {
        readVal = getc (filePtr);
        if (readVal == '\n')      /* Is it a new-line? */
            break;
        if (readVal == EOF)
            break;
        *bufPtr++ = readVal;
        if (bufPtr > bufEnd) {
            Tcl_DStringAppend (dynStrPtr, buffer, sizeof (buffer));
            bufPtr = buffer;
        }
    }
    if ((readVal == EOF) && ferror (filePtr))
        return -1;   /* Error */

    if (bufPtr != buffer) {
        Tcl_DStringAppend (dynStrPtr, buffer, bufPtr - buffer);
    }

    return (readVal == EOF) ? 0 : 1;
}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_GetLong --
 *
 *      Given a string, produce the corresponding long value.
 *
 * Results:
 *      The return value is normally TCL_OK;  in this case *intPtr
 *      will be set to the integer value equivalent to string.  If
 *      string is improperly formed then TCL_ERROR is returned and
 *      an error message will be left in interp->result.
 *
 * Side effects:
 *      None.
 *
 *-----------------------------------------------------------------------------
 */
int
Tcl_GetLong(interp, string, longPtr)
    Tcl_Interp *interp;         /* Interpreter to use for error reporting. */
    CONST char *string;         /* String containing a (possibly signed)
                                 * integer in a form acceptable to strtol. */
    long       *longPtr;        /* Place to store converted result. */
{
    char *end;
    long  i;

    i = strtol(string, &end, 0);
    while ((*end != '\0') && isspace(*end)) {
        end++;
    }
    if ((end == string) || (*end != 0)) {
        Tcl_AppendResult (interp, "expected integer but got \"", string,
                          "\"", (char *) NULL);
        return TCL_ERROR;
    }
    *longPtr = i;
    return TCL_OK;
}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_GetUnsigned --
 *
 *      Given a string, produce the corresponding unsigned integer value.
 *
 * Results:
 *      The return value is normally TCL_OK;  in this case *intPtr
 *      will be set to the integer value equivalent to string.  If
 *      string is improperly formed then TCL_ERROR is returned and
 *      an error message will be left in interp->result.
 *
 * Side effects:
 *      None.
 *
 *-----------------------------------------------------------------------------
 */
int
Tcl_GetUnsigned(interp, string, unsignedPtr)
    Tcl_Interp *interp;         /* Interpreter to use for error reporting. */
    CONST char *string;         /* String containing a (possibly signed)
                                 * integer in a form acceptable to strtoul. */
    unsigned   *unsignedPtr;    /* Place to store converted result. */
{
    char          *end;
    unsigned long  i;

    /*
     * Since some strtoul functions don't detect negative numbers, check
     * in advance.
     */
    while (isspace(*string))
        string++;
    if (string [0] == '-')
        goto badUnsigned;

    i = strtoul(string, &end, 0);
    while ((*end != '\0') && isspace(*end))
        end++;

    if ((end == string) || (*end != '\0'))
        goto badUnsigned;

    *unsignedPtr = i;
    return TCL_OK;

  badUnsigned:
    Tcl_AppendResult (interp, "expected unsigned integer but got \"", 
                      string, "\"", (char *) NULL);
    return TCL_ERROR;
}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_GetOpenFileStruct --
 *
 *    Convert a file handle to a pointer to the internal Tcl file structure.
 *
 * Parameters:
 *   o interp (I) - Current interpreter.
 *   o handle (I) - The file handle to convert.
 * Returns:
 *   A pointer to the open file structure for the file, or NULL if an error
 * occured.
 *-----------------------------------------------------------------------------
 */
OpenFile *
Tcl_GetOpenFileStruct (interp, handle)
    Tcl_Interp *interp;
    char       *handle;
{
    Interp *iPtr = (Interp *) interp;
    FILE   *filePtr;

    if (Tcl_GetOpenFile (interp, handle,
                         FALSE, FALSE,  /* No checking */
                         &filePtr) != TCL_OK)
        return NULL;

    return iPtr->oFilePtrArray [fileno (filePtr)];
}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_SetupFileEntry --
 *
 * Set up an entry in the Tcl file table for a file number, including the stdio
 * FILE structure.
 *
 * Parameters:
 *   o interp (I) - Current interpreter.
 *   o fileNum (I) - File number to set up the entry for.
 *   o readable (I) - TRUE if read access to the file.
 *   o writable (I) - TRUE if  write access to the file.
 * Returns:
 *   A pointer to the FILE structure for the file, or NULL if an error
 * occured.
 *-----------------------------------------------------------------------------
 */
FILE *
Tcl_SetupFileEntry (interp, fileNum, readable, writable)
    Tcl_Interp *interp;
    int         fileNum;
    int         readable;
    int         writable;
{
    Interp   *iPtr = (Interp *) interp;
    char     *mode;
    FILE     *filePtr;

    /*
     * Set up a stdio FILE control block for the new file.
     */
    if (readable && writable) {
        mode = "r+";
    } else if (writable) {
        mode = "w";
    } else {
        mode = "r";
    }
    filePtr = fdopen (fileNum, mode);
    if (filePtr == NULL) {
        iPtr->result = Tcl_PosixError (interp);
        return NULL;
    }
    
    Tcl_EnterFile (interp, filePtr, readable, writable);

    return filePtr;
}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_CloseForError --
 *
 *   Close a file number on error.  If the file is in the Tcl file table, clean
 * it up too. The variable errno, and interp->result and the errorCode variable
 * will be saved and not lost.
 *
 * Parameters:
 *   o interp (I) - Current interpreter.
 *   o fileNum (I) - File number to close.
 *-----------------------------------------------------------------------------
 */
void
Tcl_CloseForError (interp, fileNum)
    Tcl_Interp *interp;
    int         fileNum;
{
    static char *ERROR_CODE = "errorCode";
    int          saveErrNo = errno;
    char        *saveResult, *errorCode, *saveErrorCode, *argv [2], buf [32];

    saveResult = strdup (interp->result);

    errorCode = Tcl_GetVar (interp, ERROR_CODE, TCL_GLOBAL_ONLY);
    if (errorCode != NULL)
        saveErrorCode = strdup (errorCode);
    else
        saveErrorCode = NULL;

    sprintf (buf, "file%d", fileNum);

    argv [0] = "close";
    argv [1] = buf;
    Tcl_CloseCmd (NULL, interp, 2, argv);
    Tcl_ResetResult (interp);

    if (saveErrorCode != NULL) {
        Tcl_SetVar (interp, ERROR_CODE, saveErrorCode, TCL_GLOBAL_ONLY);
        free (saveErrorCode);
    }
    Tcl_SetResult (interp, saveResult, TCL_VOLATILE);
    free (saveResult);

    close (fileNum);  /* In case Tcl didn't have it open */
    
    errno = saveErrNo;
}
     
