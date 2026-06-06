#include "persistent.h"

#include <hardware/flash.h>
#include "lfs.h"
#include "pico_lfs.h"
#include "log.h"

#define FS_SIZE (4 * FLASH_SECTOR_SIZE)

#ifdef PICO_CYW43_SUPPORTED
#include "pico/btstack_flash_bank.h"
#define FLASH_OFFSET (PICO_FLASH_BANK_STORAGE_OFFSET - FS_SIZE)
#else
#define FLASH_OFFSET (PICO_FLASH_SIZE_BYTES - FS_SIZE)
#endif

static struct lfs_config *lfs_cfg;
static lfs_t lfs;

static lfs_file_t file_word_count;
static const char *file_name_word_count = "file_word_count";

bool persistent_init()
{
	LOG_TRACE("\n");
	LOG_DEBUG("flash offset: %d, FS size: %d", FLASH_OFFSET, FS_SIZE);

	lfs_cfg = pico_lfs_init(FLASH_OFFSET, FS_SIZE);
	if (!lfs_cfg)
	{
		LOG_ERROR("out of memory");
		return true;
	}
	int err = lfs_mount(&lfs, lfs_cfg);
	if (err != LFS_ERR_OK)
	{
		/* Initialize new filesystem */
		err = lfs_format(&lfs, lfs_cfg);
		if (err != LFS_ERR_OK)
		{
			LOG_ERROR("failed to format filesystem");
			return true;
		}
		err = lfs_mount(&lfs, lfs_cfg);
		if (err != LFS_ERR_OK)
		{
			LOG_ERROR("failed to mount new filesystem");
			return true;
		}
	}
	return false;
}

bool persistent_setup()
{
	LOG_TRACE("\n");
	lfs_file_open(&lfs, &file_word_count, file_name_word_count, LFS_O_RDWR | LFS_O_CREAT);
	return false;
}

bool persistent_terminate()
{
	LOG_TRACE("\n");
	lfs_file_close(&lfs, &file_word_count);
	lfs_unmount(&lfs);
	LOG_DEBUG("closed and unmounted fs\n");
	pico_lfs_destroy(lfs_cfg);
	return false;
}

void get_word_count(uint32_t *dest)
{
	LOG_TRACE("\n");
	lfs_file_read(&lfs, &file_word_count, dest, sizeof(*dest));
	LOG_DEBUG("loaded word count and stored it into @%p with value %d\n", dest, *dest);
}

void save_word_count(uint32_t *source)
{
	LOG_TRACE("\n");
	lfs_file_rewind(&lfs, &file_word_count);
	lfs_file_write(&lfs, &file_word_count, source, sizeof(source));
	LOG_DEBUG("stored word count from @%p with value %d\n", source, *source);
}