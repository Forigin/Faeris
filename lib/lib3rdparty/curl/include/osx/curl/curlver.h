<<<<<<< HEAD:lib/lib3rdparty/curl/src/include/curl/curlver.h
#ifndef __CURL_CURLVER_H
#define __CURL_CURLVER_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

/* This header file contains nothing but libcurl version info, generated by
   a script at release-time. This was made its own header file in 7.11.2 */

/* This is the global package copyright */
#define LIBCURL_COPYRIGHT "1996 - 2014 Daniel Stenberg, <daniel@haxx.se>."

/* This is the version number of the libcurl package from which this header
   file origins: */
#define LIBCURL_VERSION "7.38.0"

/* The numeric version number is also available "in parts" by using these
   defines: */
#define LIBCURL_VERSION_MAJOR 7
#define LIBCURL_VERSION_MINOR 38
#define LIBCURL_VERSION_PATCH 0

/* This is the numeric version of the libcurl version number, meant for easier
   parsing and comparions by programs. The LIBCURL_VERSION_NUM define will
   always follow this syntax:

         0xXXYYZZ

   Where XX, YY and ZZ are the main version, release and patch numbers in
   hexadecimal (using 8 bits each). All three numbers are always represented
   using two digits.  1.2 would appear as "0x010200" while version 9.11.7
   appears as "0x090b07".

   This 6-digit (24 bits) hexadecimal number does not show pre-release number,
   and it is always a greater number in a more recent release. It makes
   comparisons with greater than and less than work.
*/
#define LIBCURL_VERSION_NUM 0x072600

/*
 * This is the date and time when the full source package was created. The
 * timestamp is not stored in git, as the timestamp is properly set in the
 * tarballs by the maketgz script.
 *
 * The format of the date should follow this template:
 *
 * "Mon Feb 12 11:35:33 UTC 2007"
 */
#define LIBCURL_TIMESTAMP "Wed Sep 10 06:19:50 UTC 2014"

#endif /* __CURL_CURLVER_H */
=======
#ifndef __CURL_CURLVER_H
#define __CURL_CURLVER_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

/* This header file contains nothing but libcurl version info, generated by
   a script at release-time. This was made its own header file in 7.11.2 */

/* This is the global package copyright */
#define LIBCURL_COPYRIGHT "1996 - 2014 Daniel Stenberg, <daniel@haxx.se>."

/* This is the version number of the libcurl package from which this header
   file origins: */
#define LIBCURL_VERSION "7.39.0"

/* The numeric version number is also available "in parts" by using these
   defines: */
#define LIBCURL_VERSION_MAJOR 7
#define LIBCURL_VERSION_MINOR 39
#define LIBCURL_VERSION_PATCH 0

/* This is the numeric version of the libcurl version number, meant for easier
   parsing and comparions by programs. The LIBCURL_VERSION_NUM define will
   always follow this syntax:

         0xXXYYZZ

   Where XX, YY and ZZ are the main version, release and patch numbers in
   hexadecimal (using 8 bits each). All three numbers are always represented
   using two digits.  1.2 would appear as "0x010200" while version 9.11.7
   appears as "0x090b07".

   This 6-digit (24 bits) hexadecimal number does not show pre-release number,
   and it is always a greater number in a more recent release. It makes
   comparisons with greater than and less than work.
*/
#define LIBCURL_VERSION_NUM 0x072700

/*
 * This is the date and time when the full source package was created. The
 * timestamp is not stored in git, as the timestamp is properly set in the
 * tarballs by the maketgz script.
 *
 * The format of the date should follow this template:
 *
 * "Mon Feb 12 11:35:33 UTC 2007"
 */
#define LIBCURL_TIMESTAMP "Wed Nov  5 07:24:58 UTC 2014"

#endif /* __CURL_CURLVER_H */
>>>>>>> 378167ab2d80c71198812b963b6e2eb4d0f8d759:lib/lib3rdparty/curl/include/osx/curl/curlver.h
