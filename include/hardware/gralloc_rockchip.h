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

/* RK 对 Gralloc 0.3 扩展的 usage flag bits. */
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

/* Gralloc 4.0 中, RK 扩展的 usage flag bit,
 * 表征 "调用 alloc() 的 client 要求分配 底层 pages 是物理连续的 buffer".
 *
 * 注意:
 *	原始定义在 hardware/rockchip/libgralloc/bifrost 下的某个头文件中.
 *	但该文件的路径 可能随 DDK 升级而改变, 且外部要 include 该头文件困难.
 *	这里的定义 作为 public 定义, 提供给 其他 RK vendor 模块使用.

 * "GRALLOC_USAGE_PRIVATE_3" : 定义在 hardware/libhardware/include/hardware/gralloc.h 中.
 */
#define RK_GRALLOC_USAGE_PHY_CONTIG_BUFFER	GRALLOC_USAGE_PRIVATE_3

#define GRALLOC_USAGE_PRIVATE_11		(1ULL << 56)
/* Gralloc 4.0 中, 表征 "调用 alloc() 的 client 要求分配的 buffer 的所有物理 page 的地址都在 4G 以内".
*/
#define RK_GRALLOC_USAGE_WITHIN_4G		GRALLOC_USAGE_PRIVATE_11

#define GRALLOC_USAGE_PRIVATE_1			(1ULL << 29)
/* Gralloc 4.0 中, 表征 "调用 alloc() 的 client 要求分配的 buffer 不是 AFBC 格式".
*/
#define MALI_GRALLOC_USAGE_NO_AFBC		GRALLOC_USAGE_PRIVATE_1

#define GRALLOC_USAGE_PRIVATE_2                 (1ULL << 30)
/* 表征 "当前 调用 alloc() 的 client 通过 width 指定了其预期的 buffer stride",
 * 即要求 gralloc 遵循 rk_implicit_alloc_semantic (即 满足 implicit_requirement_for_rk_gralloc_allocate).
 */
#define RK_GRALLOC_USAGE_SPECIFY_STRIDE         GRALLOC_USAGE_PRIVATE_2

#define GRALLOC_USAGE_PRIVATE_10                (1ULL << 57)
/* 表征 client 要求 buffer (的 plane_0) 的 byte_stride 是 16 对齐.
 * 仅 配合 HAL_PIXEL_FORMAT_YCrCb_NV12 等特定 rk_video_formats 使用.
 *
 * 对 HAL_PIXEL_FORMAT_YCrCb_NV12, plane_0 的 byte_stride 就是 pixel_stride.
 */
#define RK_GRALLOC_USAGE_STRIDE_ALIGN_16        GRALLOC_USAGE_PRIVATE_10

#define GRALLOC_USAGE_PRIVATE_9                 (1ULL << 58)
/* 表征 client 要求 buffer (的 plane_0) 的 byte_stride 是 128 对齐.
 * 仅 配合 HAL_PIXEL_FORMAT_YCrCb_NV12 等特定 rk_video_formats 使用.
 */
#define RK_GRALLOC_USAGE_STRIDE_ALIGN_128       GRALLOC_USAGE_PRIVATE_9

#define GRALLOC_USAGE_PRIVATE_8                 (1ULL << 59)
/* 表征 client 要求 buffer (的 plane_0) 的 byte_stride 是 256 的奇数倍.
 * 仅 配合 HAL_PIXEL_FORMAT_YCrCb_NV12 等特定 rk_video_formats 使用.
 */
#define RK_GRALLOC_USAGE_STRIDE_ALIGN_256_ODD_TIMES     GRALLOC_USAGE_PRIVATE_8

#define GRALLOC_USAGE_PRIVATE_7                 (1ULL << 60)
/* 表征 client 要求 buffer (的 plane_0) 的 byte_stride 是 64 对齐.
 * 仅 配合 HAL_PIXEL_FORMAT_YCrCb_NV12 等特定 rk_video_formats 使用.
 */
#define RK_GRALLOC_USAGE_STRIDE_ALIGN_64        GRALLOC_USAGE_PRIVATE_7

/*---------------------------------------------------------------------------*/
__END_DECLS

#endif  // LIBHARDWARE_GRALLOC_ROCKCHIP_H
