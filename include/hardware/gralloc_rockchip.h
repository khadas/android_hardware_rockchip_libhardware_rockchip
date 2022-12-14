#ifndef LIBHARDWARE_GRALLOC_ROCKCHIP_H
#define LIBHARDWARE_GRALLOC_ROCKCHIP_H

#include <hardware/gralloc.h>

__BEGIN_DECLS

/**
 * perform operation commands for rk gralloc.
 * Helpers for using the non-type-safe perform() extension functions. Use
 * these helpers instead of calling perform() directly in your application.
 */
enum {
  /****************Implement****************/
  GRALLOC_MODULE_PERFORM_GET_HADNLE_PHY_ADDR       = 0x08100001,
  GRALLOC_MODULE_PERFORM_GET_HADNLE_PRIME_FD       = 0x08100002,
  GRALLOC_MODULE_PERFORM_GET_HADNLE_ATTRIBUTES     = 0x08100004,
  GRALLOC_MODULE_PERFORM_GET_INTERNAL_FORMAT       = 0x08100006,
  GRALLOC_MODULE_PERFORM_GET_HADNLE_WIDTH          = 0x08100008,
  GRALLOC_MODULE_PERFORM_GET_HADNLE_HEIGHT         = 0x0810000A,
  GRALLOC_MODULE_PERFORM_GET_HADNLE_STRIDE         = 0x0810000C,
  GRALLOC_MODULE_PERFORM_GET_HADNLE_BYTE_STRIDE    = 0x0810000E,
  GRALLOC_MODULE_PERFORM_GET_HADNLE_FORMAT         = 0x08100010,
  GRALLOC_MODULE_PERFORM_GET_HADNLE_SIZE           = 0x08100012,

  GRALLOC_MODULE_PERFORM_GET_RK_ASHMEM             = 0x08100014,
  GRALLOC_MODULE_PERFORM_SET_RK_ASHMEM             = 0x08100016,

  /* perform(const struct gralloc_module_t *mod,
   *     int op,
   *     buffer_handle_t buffer,
   *     int *usage);
   */
  GRALLOC_MODULE_PERFORM_GET_USAGE = 0x0feeff03,


  /****************Not Implement****************/
  GRALLOC_MODULE_PERFORM_GET_DRM_FD                = 0x08000002,
  /* perform(const struct gralloc_module_t *mod,
   *       int op,
   *       int drm_fd,
   *       buffer_handle_t buffer,
   *       struct hwc_drm_bo *bo);
   */
  GRALLOC_MODULE_PERFORM_DRM_IMPORT = 0xffeeff00,

  /* perform(const struct gralloc_module_t *mod,
   *       int op,
   *       buffer_handle_t buffer,
   *       void (*free_callback)(void *),
   *       void *priv);
   */
  GRALLOC_MODULE_PERFORM_SET_IMPORTER_PRIVATE = 0xffeeff01,

  /* perform(const struct gralloc_module_t *mod,
   *       int op,
   *       buffer_handle_t buffer,
   *       void (*free_callback)(void *),
   *       void **priv);
   */
  GRALLOC_MODULE_PERFORM_GET_IMPORTER_PRIVATE = 0xffeeff02,
};

//eotf type
enum supported_eotf_type {
        TRADITIONAL_GAMMA_SDR = 0,
        TRADITIONAL_GAMMA_HDR,
        SMPTE_ST2084,  /* HDR10 */
        HLG,           /* HLG */
        FUTURE_EOTF
};

//hdmi_output_colorimetry type
enum supported_hdmi_colorimetry {
	COLOR_METRY_NONE=0,
	COLOR_METRY_ITU_2020=9
};

struct hdr_static_metadata {
       uint16_t eotf;
       uint16_t type;
       uint16_t display_primaries_x[3];
       uint16_t display_primaries_y[3];
       uint16_t white_point_x;
       uint16_t white_point_y;
       uint16_t max_mastering_display_luminance;
       uint16_t min_mastering_display_luminance;
       uint16_t max_fall;
       uint16_t max_cll;
       uint16_t min_cll;
};

#define maxLayerNameLength		100
typedef struct rk_ashmem_t
{
    int32_t alreadyStereo;
    int32_t displayStereo;
    char LayerName[maxLayerNameLength + 1];
} rk_ashmem_t;

/* RK ??? Gralloc 0.3 ????????? usage flag bits. */
enum {
    /* buffer may be used as a cursor */
    GRALLOC_USAGE_ROT_MASK              = 0x0F000000,

    GRALLOC_USAGE_TO_USE_SINGLE_BUFFER  = 0x0B000000,

    /* mali p010 format */
    GRALLOC_USAGE_TO_USE_ARM_P010       = 0x0A000000,
    /* would like to use a fbdc(afbc) format. */
    GRALLOC_USAGE_TO_USE_FBDC_FMT       = 0x09000000,
    /* use Physically Continuous memory */
    GRALLOC_USAGE_TO_USE_PHY_CONT	= 0x08000000,
    /* replacement of GRALLOC_USAGE_EXTERNAL_DISP,
     * which is treated as invalid by frameworks. */
    GRALLOC_USAGE__RK_EXT__EXTERNAL_DISP= 0x07000000U,
};

/*---------------------------------------------------------------------------*/

/* Gralloc 4.0 ???, RK ????????? usage flag bit,
 * ?????? "?????? alloc() ??? client ???????????? ?????? pages ?????????????????? buffer".
 *
 * ??????:
 *	??????????????? hardware/rockchip/libgralloc/bifrost ????????????????????????.
 *	????????????????????? ????????? DDK ???????????????, ???????????? include ??????????????????.
 *	??????????????? ?????? public ??????, ????????? ?????? RK vendor ????????????.
 */

// #define GRALLOC_USAGE_PRIVATE_0         (1ULL << 28)
// #define GRALLOC_USAGE_PRIVATE_1         (1ULL << 29)
// #define GRALLOC_USAGE_PRIVATE_2         (1ULL << 30)
// #define GRALLOC_USAGE_PRIVATE_3         (1ULL << 31)
        // ??????????????? hardware/libhardware/include/hardware/gralloc.h ???.

#define GRALLOC_USAGE_PRIVATE_4         (1ULL << 63)
#define GRALLOC_USAGE_PRIVATE_5         (1ULL << 62)
#define GRALLOC_USAGE_PRIVATE_6         (1ULL << 61)
#define GRALLOC_USAGE_PRIVATE_7         (1ULL << 60)
#define GRALLOC_USAGE_PRIVATE_8         (1ULL << 59)
#define GRALLOC_USAGE_PRIVATE_9         (1ULL << 58)
#define GRALLOC_USAGE_PRIVATE_10        (1ULL << 57)
#define GRALLOC_USAGE_PRIVATE_11        (1ULL << 56)
#define GRALLOC_USAGE_PRIVATE_12        (1ULL << 55)
#define GRALLOC_USAGE_PRIVATE_13        (1ULL << 54)
#define GRALLOC_USAGE_PRIVATE_14        (1ULL << 53)
#define GRALLOC_USAGE_PRIVATE_15        (1ULL << 52)
#define GRALLOC_USAGE_PRIVATE_16        (1ULL << 51)
#define GRALLOC_USAGE_PRIVATE_17        (1ULL << 50)
#define GRALLOC_USAGE_PRIVATE_18        (1ULL << 49)
#define GRALLOC_USAGE_PRIVATE_19        (1ULL << 48)

#define RK_GRALLOC_USAGE_ALLOC_HEIGHT_ALIGN_MASK (GRALLOC_USAGE_PRIVATE_4 | GRALLOC_USAGE_PRIVATE_5)
/* ?????? "???????????? alloc() ??? client ?????? buffer ??? alloc_height ??? 8 ??????. */
#define RK_GRALLOC_USAGE_ALLOC_HEIGHT_ALIGN_8 (GRALLOC_USAGE_PRIVATE_4)
/* 16 ??????. */
#define RK_GRALLOC_USAGE_ALLOC_HEIGHT_ALIGN_16 (GRALLOC_USAGE_PRIVATE_5)
/* 64 ??????. */
#define RK_GRALLOC_USAGE_ALLOC_HEIGHT_ALIGN_64 (GRALLOC_USAGE_PRIVATE_4 | GRALLOC_USAGE_PRIVATE_5)

#define RK_GRALLOC_USAGE_PHY_CONTIG_BUFFER	GRALLOC_USAGE_PRIVATE_3

/* Gralloc 4.0 ???, ?????? "?????? alloc() ??? client ??????????????? buffer ??????????????? page ??????????????? 4G ??????".
*/
#define RK_GRALLOC_USAGE_WITHIN_4G		GRALLOC_USAGE_PRIVATE_11
/* To indicate the buffer to allocate would be accessed by RGA.
 *
 * For the limitation of IP implementation, RGA2 could only access buffers with physical address within 4G.
 * There is no such limitation in RGA3.
 */
#define RK_GRALLOC_USAGE_RGA_ACCESS     RK_GRALLOC_USAGE_WITHIN_4G

/* Gralloc 4.0 ???, ?????? "?????? alloc() ??? client ??????????????? buffer ?????? AFBC ??????".
*/
#define MALI_GRALLOC_USAGE_NO_AFBC		GRALLOC_USAGE_PRIVATE_1

/* ?????? "?????? ?????? alloc() ??? client ?????? width ????????????????????? buffer stride",
 * ????????? gralloc ?????? rk_implicit_alloc_semantic (??? ?????? implicit_requirement_for_rk_gralloc_allocate).
 */
#define RK_GRALLOC_USAGE_SPECIFY_STRIDE         GRALLOC_USAGE_PRIVATE_2

/* ?????? client ?????? buffer (??? plane_0) ??? byte_stride ??? 16 ??????.
 * ??? ?????? HAL_PIXEL_FORMAT_YCrCb_NV12 ????????? rk_video_formats ??????.
 *
 * ??? HAL_PIXEL_FORMAT_YCrCb_NV12, plane_0 ??? byte_stride ?????? pixel_stride.
 */
#define RK_GRALLOC_USAGE_STRIDE_ALIGN_16        GRALLOC_USAGE_PRIVATE_10

/* ?????? client ?????? buffer (??? plane_0) ??? byte_stride ??? 128 ??????.
 * ??? ?????? HAL_PIXEL_FORMAT_YCrCb_NV12 ????????? rk_video_formats ??????.
 */
#define RK_GRALLOC_USAGE_STRIDE_ALIGN_128       GRALLOC_USAGE_PRIVATE_9

/* ?????? client ?????? buffer (??? plane_0) ??? byte_stride ??? 256 ????????????.
 * ??? ?????? HAL_PIXEL_FORMAT_YCrCb_NV12 ????????? rk_video_formats ??????.
 */
#define RK_GRALLOC_USAGE_STRIDE_ALIGN_256_ODD_TIMES     GRALLOC_USAGE_PRIVATE_8

/* ?????? client ?????? buffer (??? plane_0) ??? byte_stride ??? 64 ??????.
 * ??? ?????? HAL_PIXEL_FORMAT_YCrCb_NV12 ????????? rk_video_formats ??????.
 */
#define RK_GRALLOC_USAGE_STRIDE_ALIGN_64        GRALLOC_USAGE_PRIVATE_7

/* YUV-only. */
#define MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_DEFAULT      (0)
#define MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_BT601        GRALLOC_USAGE_PRIVATE_18
#define MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_BT709        GRALLOC_USAGE_PRIVATE_19
#define MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_BT2020       (GRALLOC_USAGE_PRIVATE_18 | GRALLOC_USAGE_PRIVATE_19)
#define MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_MASK         MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_BT2020

#define MALI_GRALLOC_USAGE_RANGE_DEFAULT        (0)
#define MALI_GRALLOC_USAGE_RANGE_NARROW         GRALLOC_USAGE_PRIVATE_16
#define MALI_GRALLOC_USAGE_RANGE_WIDE           GRALLOC_USAGE_PRIVATE_17
#define MALI_GRALLOC_USAGE_RANGE_MASK           (GRALLOC_USAGE_PRIVATE_16 | GRALLOC_USAGE_PRIVATE_17)


/*---------------------------------------------------------------------------*/
__END_DECLS

#endif  // LIBHARDWARE_GRALLOC_ROCKCHIP_H
