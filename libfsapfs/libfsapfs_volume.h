/*
 * Volume functions
 *
 * Copyright (C) 2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBFSAPFS_INTERNAL_VOLUME_H )
#define _LIBFSAPFS_INTERNAL_VOLUME_H

#include <common.h>
#include <types.h>

#include "libfsapfs_container_key_bag.h"
#include "libfsapfs_extern.h"
#include "libfsapfs_file_system_btree.h"
#include "libfsapfs_io_handle.h"
#include "libfsapfs_libbfio.h"
#include "libfsapfs_libcerror.h"
#include "libfsapfs_libcthreads.h"
#include "libfsapfs_object_map_btree.h"
#include "libfsapfs_volume_key_bag.h"
#include "libfsapfs_volume_superblock.h"
#include "libfsapfs_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsapfs_internal_volume libfsapfs_internal_volume_t;

struct libfsapfs_internal_volume
{
	/* The block size
	 */
	uint32_t block_size;

	/* The container size
	 */
	size64_t container_size;

	/* The volume superblock
	 */
	libfsapfs_volume_superblock_t *superblock;

	/* The volume object map B-tree
	 */
	libfsapfs_object_map_btree_t *object_map_btree;

	/* The container key bag
	 */
	libfsapfs_container_key_bag_t *container_key_bag;

	/* The volume key bag
	 */
	libfsapfs_volume_key_bag_t *key_bag;

	/* The volume master key
	 */
	uint8_t volume_master_key[ 32 ];

	/* The file system B-tree
	 */
	libfsapfs_file_system_btree_t *file_system_btree;

	/* The IO handle
	 */
	libfsapfs_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

#if defined( HAVE_LIBFSAPFS_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

LIBFSAPFS_EXTERN \
int libfsapfs_volume_initialize(
     libfsapfs_volume_t **volume,
     libcerror_error_t **error );

LIBFSAPFS_EXTERN \
int libfsapfs_volume_free(
     libfsapfs_volume_t **volume,
     libcerror_error_t **error );

LIBFSAPFS_EXTERN \
int libfsapfs_volume_signal_abort(
     libfsapfs_volume_t *volume,
     libcerror_error_t **error );

LIBFSAPFS_EXTERN \
int libfsapfs_volume_open(
     libfsapfs_volume_t *volume,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBFSAPFS_EXTERN \
int libfsapfs_volume_open_wide(
     libfsapfs_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBFSAPFS_EXTERN \
int libfsapfs_volume_open_file_io_handle(
     libfsapfs_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBFSAPFS_EXTERN \
int libfsapfs_volume_close(
     libfsapfs_volume_t *volume,
     libcerror_error_t **error );

int libfsapfs_internal_volume_open_read(
     libfsapfs_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

LIBFSAPFS_EXTERN \
int libfsapfs_volume_get_size(
     libfsapfs_volume_t *volume,
     size64_t *size,
     libcerror_error_t **error );

LIBFSAPFS_EXTERN \
int libfsapfs_volume_get_identifier(
     libfsapfs_volume_t *volume,
     uint8_t *uuid_data,
     size_t uuid_data_size,
     libcerror_error_t **error );

LIBFSAPFS_EXTERN \
int libfsapfs_volume_get_utf8_name_size(
     libfsapfs_volume_t *volume,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFSAPFS_EXTERN \
int libfsapfs_volume_get_utf8_name(
     libfsapfs_volume_t *volume,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFSAPFS_EXTERN \
int libfsapfs_volume_get_utf16_name_size(
     libfsapfs_volume_t *volume,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFSAPFS_EXTERN \
int libfsapfs_volume_get_utf16_name(
     libfsapfs_volume_t *volume,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFSAPFS_EXTERN \
int libfsapfs_volume_get_root_directory(
     libfsapfs_volume_t *volume,
     libfsapfs_file_entry_t **file_entry,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSAPFS_INTERNAL_VOLUME_H ) */
