/**
 *****************************************************************************************
 *     Copyright(c) 2018, Realtek Semiconductor Corporation. All rights reserved.
 *****************************************************************************************
 * @file    spic_basic.h
 * @brief   RXI-312 SPI controller platform independent implementation header file
 * @author  Yao-Yu
 * @date    2020-07-08
 * @version v0.1
 * ***************************************************************************************
 */

#ifndef _SPIC_H
#define _SPIC_H

#include <stdint.h>
#include <stdbool.h>
#include "rtl876x.h"

/****************************************************************************************
 * SPIC Register R/W
 ****************************************************************************************/
#define SPIC_REG_RD(spic, reg)                                                                                  \
    (spic->reg)

#define SPIC_REG_WR(spic, reg, val)                                                                             \
    do                                                                                                          \
    {                                                                                                           \
        spic->reg = val;                                                                                        \
    }                                                                                                           \
    while (0)

#define SPIC_REG_FIELD_RD(spic, reg, field)                                                                     \
    ((spic->reg & BIT_SPIC_##reg##_##field(0xFFFFFFFF)) >> __builtin_ctz(BIT_SPIC_##reg##_##field(0xFFFFFFFF)))

#define SPIC_REG_FIELD_WR(spic, reg, field, val)                                                                \
    do                                                                                                          \
    {                                                                                                           \
        spic->reg = (spic->reg & ~BIT_SPIC_##reg##_##field(0xFFFFFFFF)) | BIT_SPIC_##reg##_##field(val);        \
    }                                                                                                           \
    while (0)

/* to avoid AUTO_FRQC change which triggers SPIC hang */
#define SPIC_SSIENR_WR(spic, val)                                                                \
    do                                                                                                          \
    {                                                                                                           \
        spic->SSIENR = (spic->SSIENR & 0xFFFFFFFB)| BIT_SPIC_SSIENR_SPIC_EN(val);        \
    }                                                                                                           \
    while (0)

/****************************************************************************************
 * SPIC CTRLR0 (0x000) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_CTRLR0_SIPOL(x)                            (((x) & 0x0000001FUL))
#define BIT_SPIC_CTRLR0_SIPOL_EN(x)                         (((x) & 0x00000001UL) << 5)
#define BIT_SPIC_CTRLR0_SCPH(x)                             (((x) & 0x00000001UL) << 6)
#define BIT_SPIC_CTRLR0_SCPOL(x)                            (((x) & 0x00000001UL) << 7)
#define BIT_SPIC_CTRLR0_TMOD(x)                             (((x) & 0x00000003UL) << 8)
#define BIT_SPIC_CTRLR0_GCLK_DIS(x)                         (((x) & 0x00000001UL) << 10)
#define BIT_SPIC_CTRLR0_DDR_EN(x)                           (((x) & 0x00000007UL) << 13)
#define BIT_SPIC_CTRLR0_ADDR_CH(x)                          (((x) & 0x00000003UL) << 16)
#define BIT_SPIC_CTRLR0_DATA_CH(x)                          (((x) & 0x00000003UL) << 18)
#define BIT_SPIC_CTRLR0_CMD_CH(x)                           (((x) & 0x00000003UL) << 20)
#define BIT_SPIC_CTRLR0_FAST_RD(x)                          (((x) & 0x00000001UL) << 22)
#define BIT_SPIC_CTRLR0_CK_MTIMES(x)                        (((x) & 0x0000001FUL) << 23)
#define BIT_SPIC_CTRLR0_UAR(x)                              (((x) & 0x00000001UL) << 30)
#define BIT_SPIC_CTRLR0_USER_MODE(x)                        (((x) & 0x00000001UL) << 31)

/****************************************************************************************
 * SPIC RX_NDF (0x004) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_RX_NDF_RX_NDF(x)                           (((x) & 0x0000FFFFUL))

/****************************************************************************************
 * SPIC SSIENR (0x008) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_SSIENR_SPIC_EN(x)                          (((x) & 0x00000001UL))
#define BIT_SPIC_SSIENR_ATCK_CMD(x)                         (((x) & 0x00000001UL) << 1)
#define BIT_SPIC_SSIENR_PGM_RST_TEST_EN(x)                  (((x) & 0x00000001UL) << 4)

/****************************************************************************************
 * SPIC SER (0x010) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_SER_SER(x)                                 (((x) & 0xFFFFFFFFUL))

/****************************************************************************************
 * SPIC BAUDR (0x014) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_BAUDR_SCKDV(x)                             (((x) & 0x00000FFFUL))

/****************************************************************************************
 * SPIC TXFTLR (0x018) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_TXFTLR_TFT(x)                              (((x) & 0xFFFFFFFFUL))

/****************************************************************************************
 * SPIC RXFTLR (0x01C) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_RXFTLR_RFT(x)                              (((x) & 0xFFFFFFFFUL))

/****************************************************************************************
 * SPIC TXFLR (0x020) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_TXFLR_TXFLR(x)                             (((x) & 0xFFFFFFFFUL))

/****************************************************************************************
 * SPIC RXFLR (0x024) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_RXFLR_RXFLR(x)                             (((x) & 0xFFFFFFFFUL))

/****************************************************************************************
 * SPIC SR (0x028) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_SR_BUSY(x)                                 (((x) & 0x00000001UL))
#define BIT_SPIC_SR_TFNF(x)                                 (((x) & 0x00000001UL) << 1)
#define BIT_SPIC_SR_TFE(x)                                  (((x) & 0x00000001UL) << 2)
#define BIT_SPIC_SR_RFNE(x)                                 (((x) & 0x00000001UL) << 3)
#define BIT_SPIC_SR_RFF(x)                                  (((x) & 0x00000001UL) << 4)
#define BIT_SPIC_SR_TXE(x)                                  (((x) & 0x00000001UL) << 5)
#define BIT_SPIC_SR_DCOL(x)                                 (((x) & 0x00000001UL) << 6)
#define BIT_SPIC_SR_BOOT_FIN(x)                             (((x) & 0x00000001UL) << 7)

/****************************************************************************************
 * SPIC IMR (0x02C) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_IMR_TXEIM(x)                               (((x) & 0x00000001UL))
#define BIT_SPIC_IMR_TXOIM(x)                               (((x) & 0x00000001UL) << 1)
#define BIT_SPIC_IMR_RXUIM(x)                               (((x) & 0x00000001UL) << 2)
#define BIT_SPIC_IMR_RXOIM(x)                               (((x) & 0x00000001UL) << 3)
#define BIT_SPIC_IMR_RXFIM(x)                               (((x) & 0x00000001UL) << 4)
#define BIT_SPIC_IMR_FSEIM(x)                               (((x) & 0x00000001UL) << 5)
#define BIT_SPIC_IMR_WBEIM(x)                               (((x) & 0x00000001UL) << 6)
#define BIT_SPIC_IMR_BYEIM(x)                               (((x) & 0x00000001UL) << 7)
#define BIT_SPIC_IMR_ACEIM(x)                               (((x) & 0x00000001UL) << 8)
#define BIT_SPIC_IMR_USEIM(x)                               (((x) & 0x00000001UL) << 9)
#define BIT_SPIC_IMR_TFSIM(x)                               (((x) & 0x00000001UL) << 10)
#define BIT_SPIC_IMR_ACSIM(x)                               (((x) & 0x00000001UL) << 11)
#define BIT_SPIC_IMR_DREIM(x)                               (((x) & 0x00000001UL) << 12)

/****************************************************************************************
 * SPIC ISR (0x030) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_ISR_TXEIS(x)                               (((x) & 0x00000001UL))
#define BIT_SPIC_ISR_TXOIS(x)                               (((x) & 0x00000001UL) << 1)
#define BIT_SPIC_ISR_RXUIS(x)                               (((x) & 0x00000001UL) << 2)
#define BIT_SPIC_ISR_RXOIS(x)                               (((x) & 0x00000001UL) << 3)
#define BIT_SPIC_ISR_RXFIS(x)                               (((x) & 0x00000001UL) << 4)
#define BIT_SPIC_ISR_FSEIS(x)                               (((x) & 0x00000001UL) << 5)
#define BIT_SPIC_ISR_WBEIS(x)                               (((x) & 0x00000001UL) << 6)
#define BIT_SPIC_ISR_BYEIS(x)                               (((x) & 0x00000001UL) << 7)
#define BIT_SPIC_ISR_ACEIS(x)                               (((x) & 0x00000001UL) << 8)
#define BIT_SPIC_ISR_USEIS(x)                               (((x) & 0x00000001UL) << 9)
#define BIT_SPIC_ISR_TFSIS(x)                               (((x) & 0x00000001UL) << 10)
#define BIT_SPIC_ISR_ACSIS(x)                               (((x) & 0x00000001UL) << 11)
#define BIT_SPIC_ISR_DREIS(x)                               (((x) & 0x00000001UL) << 12)

/****************************************************************************************
 * SPIC RISR (0x034) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_RISR_TXEIR(x)                              (((x) & 0x00000001UL))
#define BIT_SPIC_RISR_TXOIR(x)                              (((x) & 0x00000001UL) << 1)
#define BIT_SPIC_RISR_RXUIR(x)                              (((x) & 0x00000001UL) << 2)
#define BIT_SPIC_RISR_RXOIR(x)                              (((x) & 0x00000001UL) << 3)
#define BIT_SPIC_RISR_RXFIR(x)                              (((x) & 0x00000001UL) << 4)
#define BIT_SPIC_RISR_FSEIR(x)                              (((x) & 0x00000001UL) << 5)
#define BIT_SPIC_RISR_WBEIR(x)                              (((x) & 0x00000001UL) << 6)
#define BIT_SPIC_RISR_BYEIR(x)                              (((x) & 0x00000001UL) << 7)
#define BIT_SPIC_RISR_ACEIR(x)                              (((x) & 0x00000001UL) << 8)
#define BIT_SPIC_RISR_USEIR(x)                              (((x) & 0x00000001UL) << 9)
#define BIT_SPIC_RISR_TFSIR(x)                              (((x) & 0x00000001UL) << 10)
#define BIT_SPIC_RISR_ACSIR(x)                              (((x) & 0x00000001UL) << 11)
#define BIT_SPIC_RISR_DREIR(x)                              (((x) & 0x00000001UL) << 12)

/****************************************************************************************
 * SPIC TXOICR (0x038) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_TXOICR_TXOICR(x)                           (((x) & 0x00000001UL))

/****************************************************************************************
 * SPIC RXOICR (0x03C) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_RXOICR_RXOICR(x)                           (((x) & 0x00000001UL))

/****************************************************************************************
 * SPIC RXUICR (0x040) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_RXUICR_RXUICR(x)                           (((x) & 0x00000001UL))

/****************************************************************************************
 * SPIC MSTICR (0x044) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_MSTICR_MSTICR(x)                           (((x) & 0x00000001UL))

/****************************************************************************************
 * SPIC ICR (0x048) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_ICR_ICR(x)                                 (((x) & 0x00000001UL))

/****************************************************************************************
 * SPIC DMACR (0x04C) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_DMACR_RX_DMAC_EN(x)                        (((x) & 0x00000001UL))
#define BIT_SPIC_DMACR_TX_DMAC_EN(x)                        (((x) & 0x00000001UL) << 1)

/****************************************************************************************
 * SPIC DMATDLR (0x050) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_DMATDLR_DMATDL(x)                          (((x) & 0xFFFFFFFFUL))

/****************************************************************************************
 * SPIC DMARDLR (0x054) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_DMARDLR_DMARDL(x)                          (((x) & 0xFFFFFFFFUL))

/****************************************************************************************
 * SPIC IDR (0x058) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_IDR_IDCODE(x)                              (((x) & 0xFFFFFFFFUL))

/****************************************************************************************
 * SPIC SPIC_VERSION (0x05C) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_SPIC_VERSION_SPIC_VERSION(x)               (((x) & 0xFFFFFFFFUL))

/****************************************************************************************
 * SPIC DR (0x060 ~ 0x09C) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_DR_DR(x)                                   (((x) & 0xFFFFFFFFUL))

/****************************************************************************************
 * SPIC DM_DR (0x0A0 ~ 0x0DC) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_DM_DR_DATA_MASK_DR(x)                      (((x) & 0x00000001UL))
#define BIT_SPIC_DM_DR_DATA_EN_DR(x)                        (((x) & 0x00000001UL) << 1)

/****************************************************************************************
 * SPIC READ_FAST_SINGLE (0x0E0) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_READ_FAST_SINGLE_FRD_CMD(x)                (((x) & 0x0000FFFFUL))

/****************************************************************************************
 * SPIC READ_DUAL_DATA (0x0E4) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_READ_DUAL_DATA_RD_DUAL_O_CMD(x)            (((x) & 0x000000FFUL))

/****************************************************************************************
 * SPIC READ_DUAL_ADDR_DATA (0x0E8) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_READ_DUAL_ADDR_DATA_RD_DUAL_IO_CMD(x)      (((x) & 0x000000FFUL))

/****************************************************************************************
 * SPIC READ_QUAD_DATA (0x0EC) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_READ_QUAD_DATA_RD_QUAD_O_CMD(x)            (((x) & 0x000000FFUL))

/****************************************************************************************
 * SPIC READ_QUAD_ADDR_DATA (0x0F0) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_READ_QUAD_ADDR_DATA_RD_QUAD_IO_CMD(x)      (((x) & 0x000000FFUL))
#define BIT_SPIC_READ_QUAD_ADDR_DATA_EXIT_PRM_DUM_LEN(x)    (((x) & 0x000000FFUL) << 8)
#define BIT_SPIC_READ_QUAD_ADDR_DATA_PRM_VAL(x)             (((x) & 0x000000FFUL) << 16)
#define BIT_SPIC_READ_QUAD_ADDR_DATA_EXIT_PRM_CMD(x)        (((x) & 0x000000FFUL) << 24)

/****************************************************************************************
 * SPIC WRITE_SINGLE (0x0F4) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_WRITE_SINGLE_WR_CMD(x)                     (((x) & 0x0000FFFFUL))

/****************************************************************************************
 * SPIC WRITE_DUAL_DATA (0x0F8) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_WRITE_DUAL_DATA_WR_DUAL_I_CMD(x)           (((x) & 0x000000FFUL))

/****************************************************************************************
 * SPIC WRITE_DUAL_ADDR_DATA (0x0FC) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_WRITE_DUAL_ADDR_DATA_WR_DUAL_II_CMD(x)     (((x) & 0x000000FFUL))

/****************************************************************************************
 * SPIC WRITE_QUAD_DATA (0x100) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_WRITE_QUAD_DATA_WR_QUAD_I_CMD(x)           (((x) & 0x000000FFUL))

/****************************************************************************************
 * SPIC WRITE_QUAD_ADDR_DATA (0x104) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_WRITE_QUAD_ADDR_DATA_WR_QUAD_II_CMD(x)     (((x) & 0x000000FFUL))

/****************************************************************************************
 * SPIC WRITE_ENABLE (0x108) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_WRITE_ENABLE_WR_EN_CMD_1ST_BYTE(x)         (((x) & 0x000000FFUL))
#define BIT_SPIC_WRITE_ENABLE_WR_EN_CMD_2ND_BYTE(x)         (((x) & 0x000000FFUL) << 8)

/****************************************************************************************
 * SPIC READ_STATUS (0x10C) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_READ_STATUS_RD_ST_CMD_1ST_BYTE(x)          (((x) & 0x000000FFUL))
#define BIT_SPIC_READ_STATUS_RD_ST_CMD_2ND_BYTE(x)          (((x) & 0x000000FFUL) << 8)
#define BIT_SPIC_READ_STATUS_INTERVAL_EN(x)                 (((x) & 0x00000001UL) << 27)
#define BIT_SPIC_READ_STATUS_ADDR_SEL(x)                    (((x) & 0x00000001UL) << 28)
#define BIT_SPIC_READ_STATUS_ADDR_LEN(x)                    (((x) & 0x00000003UL) << 29)
#define BIT_SPIC_READ_STATUS_ADDR_EN(x)                     (((x) & 0x00000001UL) << 31)

/****************************************************************************************
 * SPIC CTRLR2 (0x110) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_CTRLR2_SO_DNUM(x)                          (((x) & 0x00000001UL))
#define BIT_SPIC_CTRLR2_WPN_SET(x)                          (((x) & 0x00000001UL) << 1)
#define BIT_SPIC_CTRLR2_WPN_DNUM(x)                         (((x) & 0x00000001UL) << 2)
#define BIT_SPIC_CTRLR2_FIFO_ENTRY(x)                       (((x) & 0x0000000FUL) << 4)
#define BIT_SPIC_CTRLR2_TX_FIFO_ENTRY(x)                    (((x) & 0x0000000FUL) << 4)
#define BIT_SPIC_CTRLR2_RX_FIFO_ENTRY(x)                    (((x) & 0x0000000FUL) << 8)
#define BIT_SPIC_CTRLR2_DM_ACT(x)                           (((x) & 0x00000001UL) << 12)
#define BIT_SPIC_CTRLR2_FULL_WR(x)                          (((x) & 0x00000001UL) << 13)
#define BIT_SPIC_CTRLR2_RD_VALID_EN(x)                      (((x) & 0x00000001UL) << 16)
#define BIT_SPIC_CTRLR2_RD_WEIGHT(x)                        (((x) & 0x0000001FUL) << 19)

/****************************************************************************************
 * SPIC FBAUDR (0x114) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_FBAUDR_FSCKDV(x)                           (((x) & 0x00000FFFUL))

/****************************************************************************************
 * SPIC USER_LENGTH (0x118) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_USER_LENGTH_USER_RD_DUMMY_LENGTH(x)        (((x) & 0x00000FFFUL))
#define BIT_SPIC_USER_LENGTH_USER_CMD_LENGTH(x)             (((x) & 0x00000003UL) << 12)
#define BIT_SPIC_USER_LENGTH_USER_ADDR_LENGTH(x)            (((x) & 0x0000000FUL) << 16)

/****************************************************************************************
 * SPIC AUTO_LENGTH (0x11C) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_AUTO_LENGTH_RD_DUMMY_LENGTH(x)             (((x) & 0x00000FFFUL))
#define BIT_SPIC_AUTO_LENGTH_IN_PHYSICAL_CYC(x)             (((x) & 0x0000000FUL) << 12)
#define BIT_SPIC_AUTO_LENGTH_AUTO_ADDR_LENGTH(x)            (((x) & 0x0000000FUL) << 16)
#define BIT_SPIC_AUTO_LENGTH_RDSR_DUMMY_LENGTH(x)           (((x) & 0x000000FFUL) << 20)

/****************************************************************************************
 * SPIC VALID_CMD (0x120) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_VALID_CMD_FRD_SINGLE(x)                    (((x) & 0x00000001UL))
#define BIT_SPIC_VALID_CMD_RD_DUAL_O(x)                     (((x) & 0x00000001UL) << 1)
#define BIT_SPIC_VALID_CMD_RD_DUAL_IO(x)                    (((x) & 0x00000001UL) << 2)
#define BIT_SPIC_VALID_CMD_RD_QUAD_O(x)                     (((x) & 0x00000001UL) << 3)
#define BIT_SPIC_VALID_CMD_RD_QUAD_IO(x)                    (((x) & 0x00000001UL) << 4)
#define BIT_SPIC_VALID_CMD_WR_DUAL_I(x)                     (((x) & 0x00000001UL) << 5)
#define BIT_SPIC_VALID_CMD_WR_DUAL_II(x)                    (((x) & 0x00000001UL) << 6)
#define BIT_SPIC_VALID_CMD_WR_QUAD_I(x)                     (((x) & 0x00000001UL) << 7)
#define BIT_SPIC_VALID_CMD_WR_QUAD_II(x)                    (((x) & 0x00000001UL) << 8)
#define BIT_SPIC_VALID_CMD_RM_RDSR(x)                       (((x) & 0x00000001UL) << 9)
#define BIT_SPIC_VALID_CMD_RM_WEN(x)                        (((x) & 0x00000001UL) << 10)
#define BIT_SPIC_VALID_CMD_PRM_EN(x)                        (((x) & 0x00000001UL) << 11)
#define BIT_SPIC_VALID_CMD_CTRLR0_CH(x)                     (((x) & 0x00000001UL) << 12)
#define BIT_SPIC_VALID_CMD_DUM_EN(x)                        (((x) & 0x00000001UL) << 13)
#define BIT_SPIC_VALID_CMD_SEQ_TRANS_EN(x)                  (((x) & 0x00000001UL) << 14)

/****************************************************************************************
 * SPIC FLASH_SIZE (0x124) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_FLASH_SIZE_FLASH_SIZE(x)                   (((x) & 0x0000000FUL))

/****************************************************************************************
 * SPIC FLUSH_FIFO (0x128) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_FLUSH_FIFO_FLUSH_ALL(x)                    (((x) & 0x00000001UL))
#define BIT_SPIC_FLUSH_FIFO_FLUSH_PGM_RST_FIFO(x)           (((x) & 0x00000001UL) << 1)

/****************************************************************************************
 * SPIC DUM_BYTE (0x12C) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_DUM_BYTE_DUM_BYTE_VAL(x)                   (((x) & 0x000000FFUL))

/****************************************************************************************
 * SPIC TX_NDF (0x130) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_TX_NDF_TX_NDF(x)                           (((x) & 0x00FFFFFFUL))

/****************************************************************************************
 * SPIC DEVICE_INFO (0x134) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_DEVICE_INFO_PAGE_SIZE(x)                   (((x) & 0x0000000FUL))
#define BIT_SPIC_DEVICE_INFO_WR_PAGE_EN(x)                  (((x) & 0x00000001UL) << 4)
#define BIT_SPIC_DEVICE_INFO_RD_PAGE_EN(x)                  (((x) & 0x00000001UL) << 5)
#define BIT_SPIC_DEVICE_INFO_ATOM_SIZE(x)                   (((x) & 0x00000003UL) << 6)
#define BIT_SPIC_DEVICE_INFO_NOR_FLASH(x)                   (((x) & 0x00000001UL) << 8)
#define BIT_SPIC_DEVICE_INFO_NAND_FLASH(x)                  (((x) & 0x00000001UL) << 9)
#define BIT_SPIC_DEVICE_INFO_PSRAM(x)                       (((x) & 0x00000001UL) << 10)
#define BIT_SPIC_DEVICE_INFO_DATA_UNIT_2B(x)                (((x) & 0x00000001UL) << 12)

/****************************************************************************************
 * SPIC TPR0 (0x138) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_TPR0_CS_H_RD_DUM_LEN(x)                    (((x) & 0x0000003FUL))
#define BIT_SPIC_TPR0_CS_H_WR_DUM_LEN(x)                    (((x) & 0x0000003FUL) << 6)
#define BIT_SPIC_TPR0_CS_ACTIVE_HOLD(x)                     (((x) & 0x0000000FUL) << 12)
#define BIT_SPIC_TPR0_CS_SEQ_TIMEOUT(x)                     (((x) & 0x000000FFUL) << 16)
#define BIT_SPIC_TPR0_CS_TCEM(x)                            (((x) & 0x000000FFUL) << 24)

/****************************************************************************************
 * SPIC AUTO_LENGTH2 (0x13C) Register Bit Definitions
 ****************************************************************************************/
#define BIT_SPIC_AUTO_LENGTH2_WR_DUMMY_LENGTH(x)            (((x) & 0x00000FFFUL))

/****************************************************************************************
 * SPIC Enumeration
 ****************************************************************************************/
typedef enum
{
    SPIC_DEVICE_NOR_FLASH,
    SPIC_DEVICE_NAND_FLASH,
    SPIC_DEVICE_PSRAM,
} SPIC_DEVICE_TYPE;

typedef enum
{
    SPIC_ATOM_1_BYTE,
    SPIC_ATOM_2_BYTE,
    SPIC_ATOM_4_BYTE,
    SPIC_ATOM_RESERVED,
} SPIC_ATOM_SIZE_TYPE;

typedef enum
{
    SPIC_DATA_BYTE,
    SPIC_DATA_HALF,
    SPIC_DATA_WORD,
} SPIC_CFG_DATA_LEN;



/****************************************************************************************
 * SPIC Structure
 ****************************************************************************************/
typedef struct _SPIC_BACKUP_REG_TYPE
{
    __IO uint32_t CTRLR0;               /* Control reg 0,                         offset: 0x000 */
    __IO uint32_t SSIENR;               /* Enable reg,                            offset: 0x008 */
    __IO uint32_t BAUDR;                /* Baudrate select reg,                   offset: 0x014 */
    __IO uint32_t IMR;                  /* Interrupt mask reg,                    offset: 0x02C */
    __IO uint32_t READ_FAST_SINGLE;     /* Fast read data cmd of flash,           offset: 0x0E0 */
    __IO uint32_t READ_DUAL_DATA;       /* Dual output read cmd of flash,         offset: 0x0E4 */
    __IO uint32_t READ_DUAL_ADDR_DATA;  /* Dual I/O read cmd of flash,            offset: 0x0E8 */
    __IO uint32_t READ_QUAD_DATA;       /* Quad output read cmd of flash,         offset: 0x0EC */
    __IO uint32_t READ_QUAD_ADDR_DATA;  /* Quad I/O read cmd of flash,            offset: 0x0F0 */
    __IO uint32_t WRITE_SINGLE;         /* Page program cmd of flash,             offset: 0x0F4 */
    __IO uint32_t WRITE_DUAL_DATA;      /* Dual data input program cmd of flash,  offset: 0x0F8 */
    __IO uint32_t WRITE_DUAL_ADDR_DATA; /* Dual addr & data program cmd of flash, offset: 0x0FC */
    __IO uint32_t WRITE_QUAD_DATA;      /* Quad data input program cmd of flash,  offset: 0x100 */
    __IO uint32_t WRITE_QUAD_ADDR_DATA; /* Quad addr & data program cmd of flash, offset: 0x104 */
    __IO uint32_t WRITE_ENABLE;         /* Write enabe cmd of flash,              offset: 0x108 */
    __IO uint32_t READ_STATUS;          /* Read status cmd of flash,              offset: 0x10C */
    __IO uint32_t FBAUDR;               /* Fast baudrate select,                  offset: 0x114 */
    __IO uint32_t USER_LENGTH;          /* Addr length reg,                       offset: 0x118 */
    __IO uint32_t AUTO_LENGTH;          /* Auto addr length reg,                  offset: 0x11C */
    __IO uint32_t VALID_CMD;            /* Valid cmd reg,                         offset: 0x120 */
    __IO uint32_t DUM_BYTE;             /* Dummy byte value,                      offset: 0x12C */
    __IO uint32_t DEVICE_INFO;          /* Device info,                           offset: 0x134 */
    __IO uint32_t TPR0;                 /* Timing parameters,                     offset: 0x138 */
    __IO uint32_t AUTO_LENGTH2;         /* Auto addr length reg 2,                offset: 0x13C */
} SPIC_BACKUP_REG_TYPE;

#endif
