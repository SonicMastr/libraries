/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_FIOS2_H
#define _VDSUITE_KERNEL_FIOS2_H

#include <stdint.h>
#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t SceFiosOverlayID;

typedef enum SceFiosOverlayType {
  // src replaces dst. All accesses to dst are redirected to src.
  SCE_FIOS_OVERLAY_TYPE_OPAQUE      = 0,

  // src merges with dst. Reads check src first, then dst. Writes go to dst.
  SCE_FIOS_OVERLAY_TYPE_TRANSLUCENT = 1,

  // src merges with dst. Reads check both src and dst, and use whichever has the most recent modification time.
  // If both src and dst have the same modification time, dst is used.
  // If no file exists at src or dst, dst is used; if no file exists at dst, but a file exists at src, src is used. Writes go to dst.
  SCE_FIOS_OVERLAY_TYPE_NEWER       = 2,

  // src merges with dst. Reads check src first, then dst. Writes go to src.
  SCE_FIOS_OVERLAY_TYPE_WRITABLE    = 3
} SceFiosOverlayType;

typedef struct SceFiosOverlay {
  uint8_t type; // see SceFiosOverlayType
  uint8_t order;
  uint16_t dst_len;
  uint16_t src_len;
  uint16_t unk2;
  SceUID pid;
  SceFiosOverlayID id;
  char dst[292];
  char src[292]; // src path replaces dst path based on type policy
} SceFiosOverlay;

/**
 * Overlay process file system overlay
 *
 * @param[in]  overlay - Overlay config pointer
 * @param[out] outID   - outID pointer
 *
 * @return     Error code or zero on success
 */
int sceFiosKernelOverlayAdd(SceFiosOverlay *overlay, SceFiosOverlayID *outID);

/**
 * Overlay process file system overlay
 *
 * @param[in]  pid     - Process id
 * @param[in]  overlay - Overlay config pointer
 * @param[out] outID   - outID pointer
 *
 * @return     Error code or zero on success
 */
int sceFiosKernelOverlayAddForProcess(SceUID pid, SceFiosOverlay *overlay, SceFiosOverlayID *outID);

/**
 * Remove process file system overlay
 *
 * @param[in] pid - Process id
 * @param[in] id  - Overlay id
 *
 * @return     Error code or zero on success
 */
int sceFiosKernelOverlayRemoveForProcess(SceUID pid, SceFiosOverlayID id);

/**
 * Resolve process file system overlay with sync
 *
 * @param[in]  pid         - Process id
 * @param[in]  resolveFlag - Some flags
 * @param[in]  inPath      - Path input
 * @param[out] outPath     - Path output
 * @param[in]  maxPath     - Path output max length
 *
 * @return     Error code or zero on success
 */
int sceFiosKernelOverlayResolveSync(SceUID pid, int resolveFlag, const char *inPath, char *outPath, SceSize maxPath);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_FIOS2_H */
